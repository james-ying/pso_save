/*
 * HCLPSO.cpp
 *
 *  Created on: 2015年4月21日
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
	int count;//连的第几条边，count<=m
	double p[t+m0];//与各个结点相连的概率，可重复使用
	double p1;//产生的随机数
	double p2;//累加的概率
	int k_degree[N];
	for (i=m0;i<=t+m0-1;i++)
	{
		//首先计算i-1个结点的度以及连到它们的概率
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
		//开始连边
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
		G[j][i]=1;//连好了第一条边
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
		}//连好其余m-1条边
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
	int iTemp[N]; //随机选俩比较适应值，记下适应值更好的iTemp，iTemp是粒子编号
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
		} else { //keep自己的pbest，也就是iTemp是自己的(i)
			p[i].fi[d] = i;
		}
	}
	//这里是判断更新过的fi各个维度上是否都是它自己（粒子i）
	bool is_i = true; //这里是判断更新过的fi各个维度上是否都是它自己（粒子i）
	for (int d = 0; d < DIM; d++) {
		if (p[i].fi[d] != i) { //如果某一维不是，就可以断定不都是它自己
			is_i = false;
			break;
		}
	}
	if (is_i) { //如果这个例子所有维的学习对象都是它自己
		int tempd = rand() % DIM; //给这个粒子随机找一维
		do {
			//p[i].fi[tempd]=rand()%N;//让随机找的这维改成学别的粒子
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

