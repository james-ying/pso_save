/*
 * CLPSO.cpp
 *
 *  Created on: 2015��4��20��
 *      Author: lenovo
 */

#include "CLPSO.h"
#include <iostream>
#include<cmath>
CLPSO::CLPSO() {
	// TODO Auto-generated constructor stub

}
CLPSO::CLPSO(int N, int DIM, int GEN, int index, int times):
	PSO(N, DIM, GEN, index, times, "CLPSO"),
	RefreshingGap(7)
{
	for(int i=0; i<this->N; i++){
		p[i].PC=0.05+0.45*(exp((double)10*i/(N-1))-1)/(exp((double)10)-1);
	}
	// TODO Auto-generated constructor stub
}

void CLPSO::Run(){
	OutputGHead(index, GEN, name);
	InitNeighbor();
	for(int t=0; t<times; t++){
		Initialize();
		for(int i=0; i<N; i++){
			Refresh(i);
		}
		for(int g=0; g<=GEN; g++){
			w=0.9-0.5*(g+1)/GEN;
			for(int i=0; i<N; i++){
				p[i].isUpdate = true;
			}
			Iterate(g, t);
		}
	}
}

void CLPSO::UpdateExamplar(){
	for(int i=0;i<N;i++){
		if(p[i].flag>=RefreshingGap){
			Refresh(i);
			p[i].flag=0;
		}
	}
}
void CLPSO::Refresh(int i){
	for(int d=0;d<DIM;d++){
		if(Randf()<p[i].PC){//PC��һ��Ԥ���趨�ĸ��ʣ����������Զ�����keep itself
			//���ѡ���Ƚ���Ӧֵ��������Ӧֵ���õ�i_temp��i_temp�����ӱ��
			int i1_temp,i2_temp;
			do{
				i1_temp=rand()%N;
			}while((i1_temp==i));
			do{
				i2_temp=rand()%N;
			}while((i2_temp==i)||(i1_temp==i2_temp));//
/*			//TODO:randomly choose two particles out of the population which (excludes the particle whose velocity is Updated)
			if(i<N-2){
				i1_temp=i+1+rand()%(N-i-1);
				do{
					i2_temp=i+1+rand()%(N-i-1);
				}while(i2_temp==i1_temp);
			}else{
				i1_temp=N-1;
				i2_temp=N-1;
			}*/
			if(p[i1_temp].pbestFitness<p[i2_temp].pbestFitness){
				p[i].fi[d]=i1_temp;
			}else{
				p[i].fi[d]=i2_temp;
			}
		}else{//keep�Լ���pbest��Ҳ����i_temp���Լ���(i)
			p[i].fi[d]=i;
		}
	}
	//�������жϸ��¹���fi����ά�����Ƿ������Լ�������i��
	bool is_i=true;
	for(int d=0;d<DIM;d++){
		if(p[i].fi[d]!=i){//���ĳһά���ǣ��Ϳ��Զ϶����������Լ�
			is_i=false;
			break;
		}
	}
	if(is_i){//��������������ά��ѧϰ���������Լ�
		int tempd=rand()%DIM;//��������������һά
		do{
			p[i].fi[tempd]=rand()%N;//������ҵ���ά�ĳ�ѧ�������
		}while(p[i].fi[tempd]==i);
	}
}

void CLPSO::UpdateVelocity(int i){
	for(int d=0; d<DIM; d++){
		p[i].v[d]=w*p[i].v[d]+c*Randf()*(p[p[i].fi[d]].pbest[d]-p[i].x[d]);
		if(p[i].v[d]<p[i].vmin){
			p[i].v[d]=p[i].vmin;
		}else if(p[i].v[d]>p[i].vmax){
			p[i].v[d]=p[i].vmax;
		}
	}
}

void CLPSO::UpdatePosition(int i){
	for(int d=0; d<DIM; d++){
		p[i].x[d] = p[i].v[d] + p[i].x[d];
		if(p[i].x[d]<p[i].xmin){
//			p[i].x[d]=p[i].xmin;
			p[i].isUpdate = false;
		}else if(p[i].x[d]>p[i].xmax){
//			p[i].x[d]=p[i].xmax;
			p[i].isUpdate = false;
		}
	}
}
CLPSO::~CLPSO() {
	// TODO Auto-generated destructor stub
}

