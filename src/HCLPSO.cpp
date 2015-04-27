/*
 * HCLPSO.cpp
 *
 *  Created on: 2015��4��21��
 *      Author: lenovo
 */

#include "HCLPSO.h"
#include <cmath>
HCLPSO::HCLPSO() {
	// TODO Auto-generated constructor stub

}
HCLPSO::HCLPSO(int m0, int m, int t, int DIM, int GEN, int index, int times):
	PSO(m0+t, DIM, GEN, index, times, "HCLPSO"),
	RefreshingGap(7),
	m0(m0),
	m(m),
	t(t)
{
	// TODO Auto-generated constructor stub
}
void HCLPSO::SetG(){
	int i,j,ii,jj;
	for(i=0; i<N; i++){
		for(j=0; j<N; j++){
			G[i][j]=0;
		}
	}
	for (i=0;i<=m0-1;i++)
	{
		for (j=0;j<=m0-1;j++)
		{
			if (j!=i)
			{
				G[i][j]=1;
			}
			else
				continue;
		}
	}
	int count;//���ĵڼ����ߣ�count<=m
	double p[t+m0];//�������������ĸ��ʣ����ظ�ʹ��
	double p1;//�����������
	double p2;//�ۼӵĸ���
	int k_degree[N];
	for (i=m0;i<=t+m0-1;i++)
	{
		//���ȼ���i-1�����Ķ��Լ��������ǵĸ���
		for (ii=0;ii<=t+m0-1;ii++)
		{k_degree[ii]=0;
		}
		for (ii=0;ii<=i-1;ii++)
		{
			for (j=0;j<=i-1;j++)
			{
				k_degree[ii]=k_degree[ii]+G[ii][j];
			}
		}
		int k_sum=0;
		for (ii=0;ii<=i-1;ii++)
		{
			k_sum=k_degree[ii]+k_sum;
		}
		for (ii=0;ii<=i-1;ii++)
		{
			p[ii]=(double)k_degree[ii]/k_sum;
		}
		//��ʼ����
		p1=rand()/(double)RAND_MAX;
		p2=0;
		for (j=0;j<=i-1;j++)
		{
			p2=p2+p[j];
			if (p2>=p1)
			{break;
			}
		}
		G[i][j]=1;
		G[j][i]=1;//�����˵�һ����
		for (count=1;count<=m-1;count++)
		{
			double temp = p[j];
			for(jj=0;jj<=i-1;jj++)
			{
				p[jj]=p[jj]/(1-temp);
			}
			p[j]=0;
			p1=rand()/(double)RAND_MAX;
			p2=0;
			for (j=0;j<=i-1;j++)
			{
				p2=p2+p[j];
				if (p2>=p1)
				{break;
				}
			}
			G[i][j]=1;
			G[j][i]=1;
		}//��������m-1����
	}
}
void HCLPSO::Run() {
	OutputGHead(index, GEN, name);
	for (int t = 0; t < times; t++) {
		InitNeighbor();
		for (int i = 0; i < N; i++) {
			p[i].PC = 1 / (1 + pow(M_E, (2 * m - p[i].degree)));
		}
		for (int tnet = 0; tnet < 5; tnet++) {
			Initialize();
			for (int i = 0; i < N; i++) {
				Refresh(i);
			}
			for (int g = 0; g <= GEN; g++) {
				w = 0.9 - 0.5 * (g + 1) / GEN;
				for (int i = 0; i < N; i++) {
					p[i].isUpdate = true;
				}
				Iterate(g, t);
			}
		}
	}
}

void HCLPSO::UpdateExamplar() {
	for (int i = 0; i < N; i++) {
		if (p[i].flag >= RefreshingGap) {
			Refresh(i);
			p[i].flag = 0;
		}
	}
}
void HCLPSO::GetRand(int all[], int* rnd, int size, int times) {
	for (int i = 0; i < times; i++) {
		int r = rand() % (size - i);
		rnd[i] = all[r];
		int temp = all[r];
		all[r] = all[size - 1 - i];
		all[size - 1 - i] = temp;
	}
}
void HCLPSO::Refresh(int i) {
	int iTemp[N]; //���ѡ���Ƚ���Ӧֵ��������Ӧֵ���õ�iTemp��iTemp�����ӱ��
	int CandidateNumber, c;
	double bestf;
	if (p[i].degree < m * 2) {
		CandidateNumber = 2;
	} else {
		CandidateNumber = 4; //candidatenumber=m;
	}
	for (int d = 0; d < DIM; d++) {
		GetRand(p[i].link, iTemp, p[i].degree, CandidateNumber);
		p[i].fi[d] = iTemp[0];
		bestf = p[p[i].fi[d]].pbestFitness;
		for (c = 0; c < CandidateNumber; c++) {
			if (p[iTemp[c]].pbestFitness < bestf) {
				p[i].fi[d] = iTemp[c];
				bestf = p[iTemp[c]].pbestFitness;
			}
		}
		if (Randf() < p[i].PC) {
			;
		} else { //keep�Լ���pbest��Ҳ����iTemp���Լ���(i)
			p[i].fi[d] = i;
		}
	}
	//�������жϸ��¹���fi����ά�����Ƿ������Լ�������i��
	bool is_i = true; //�������жϸ��¹���fi����ά�����Ƿ������Լ�������i��
	for (int d = 0; d < DIM; d++) {
		if (p[i].fi[d] != i) { //���ĳһά���ǣ��Ϳ��Զ϶����������Լ�
			is_i = false;
			break;
		}
	}
	if (is_i) { //��������������ά��ѧϰ���������Լ�
		int tempd = rand() % DIM; //��������������һά
		do {
			//p[i].fi[tempd]=rand()%N;//������ҵ���ά�ĳ�ѧ�������
			p[i].fi[tempd] = p[i].link[rand() % p[i].degree];
		} while (p[i].fi[tempd] == i);
	}
}

void HCLPSO::UpdateVelocity(int i) {
	for (int d = 0; d < DIM; d++) {
		p[i].v[d] = w * p[i].v[d]
				+ c * Randf() * (p[p[i].fi[d]].pbest[d] - p[i].x[d]);
		if (p[i].v[d] < p[i].vmin) {
			p[i].v[d] = p[i].vmin;
		} else if (p[i].v[d] > p[i].vmax) {
			p[i].v[d] = p[i].vmax;
		}
	}
}

void HCLPSO::UpdatePosition(int i) {
	for (int d = 0; d < DIM; d++) {
		p[i].x[d] = p[i].v[d] + p[i].x[d];
		if (p[i].x[d] < p[i].xmin) {
//			p[i].x[d]=p[i].xmin;
			p[i].isUpdate = false;
		} else if (p[i].x[d] > p[i].xmax) {
//			p[i].x[d]=p[i].xmax;
			p[i].isUpdate = false;
		}
	}
}

HCLPSO::~HCLPSO() {
	// TODO Auto-generated destructor stub
}

