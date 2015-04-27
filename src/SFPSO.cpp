/*
 * SFPSO.cpp
 *
 *  Created on: 2015��4��20��
 *      Author: lenovo
 */

#include "SFPSO.h"
#include "time.h"
#include <iostream>
using namespace std;
SFPSO::SFPSO() {
	// TODO Auto-generated constructor stub

}
SFPSO::SFPSO(int m0, int m, int t, int DIM, int GEN, int index, int times, string name = "SFPSO"):
	PSO(m0+t, DIM, GEN, index, times, name),
	m0(m0),
	m(m),
	t(t)
{
	// TODO Auto-generated constructor stub
}
void SFPSO::SetG(){
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
void SFPSO::Run(){
	OutputGHead(index, GEN, name);
	for(int t=0; t<times; t++){
		InitNeighbor();
//		for(int tnet=0; tnet<5; tnet++){
			Initialize();
			for(int g=0; g<=GEN; g++){
				Iterate(g, t);
			}
//		}
	}
}
SFPSO::~SFPSO() {
	// TODO Auto-generated destructor stub
}

