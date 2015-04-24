/*
 * PSO.cpp
 *
 *  Created on: 2015年4月14日
 *      Author: lenovo
 */

#include "PSO.h"
#include "Function.h"
#include "GraphOperation.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include<string>
#include<fstream>
#include<sstream>
#include <cmath>
//#include
using namespace std;
PSO::PSO(){

}
PSO::PSO(int N, int DIM, int GEN, int index, int times, string name = "PSO"):
// TODO Set w and c
		w(0.7298),
		c(1.49445),
	gbest(new double[DIM]),
	gbestFitness(0),
	G(new int *[N]),
	M(new double *[DIM]),
	index(index),
	name(name),
	N(N),
	DIM(DIM),
	GEN(GEN),
	times(times),
	p(new Particle[N])
{
	for(int i=0; i<N; i++){
		G[i] = new int[N];
	}
	for(int i=0; i<DIM; i++){
		M[i] = new double[DIM];
	}
	for(int i=0; i<this->N; i++){
		p[i] = Particle(this->N, this->DIM, M);
	}
}

void PSO::Run(){
	OutputGHead(index, GEN, name);
	InitNeighbor();
	for(int t=0; t<times; t++){
		Initialize();
		for(int g=0; g<=GEN; g++){
			Iterate(g,t);
		}
	}
}

void PSO::InitNeighbor(){//TODO:sort with degree or learning probability

	SetG();
//--------
	int degree[N];
	for(int i=0;i<N;i++){
		degree[i] = 0;
		for(int j=0;j<N;j++){
			p[i].link[j]=-1;
			if(G[i][j]){
				degree[i]++;
			}
		}
	}
//TODO:SortG with degree
	SortG(G,degree,N);
	for(int i=0;i<N;i++){
		int k=0;
		for(int j=0;j<N;j++){
			if(G[i][j]){
				p[i].link[k]=j;
				k++;
				p[i].degree=k;
			}
		}
//		p[i].degree = degree[i];
	}
	for(int i=0; i<N; i++){
		for(int d=0; d<DIM; d++){
			p[i].fi[d] = p[i].link[0];
		}
	}
}

void PSO::SetG(){
	char Gbuf[81];
	ifstream infile;
	string title="FullyNetwork.txt";
	infile.open(title.data());//
	if(infile.is_open()){
		for(int i=0;i<N;i++){
			infile.getline(Gbuf,2*N+1);
			for(int j=0;j<N;j++){
				G[i][j]=Gbuf[j*2]-'0';
			}
//			cout<<endl;
		}
	}else{
		cout<<"Failed opening the file:"<< title <<endl;
	}
}
void PSO::Initialize(){
	InitGoal(this->index, goal);
	if(index<=16){
		CreateM(M, DIM);
	}
	else{
		ResetCompoFunc(DIM);
	}
	for(int i=0; i<this->N; i++){
		p[i].Initialize(index, M);
	}
	memcpy(gbest, p[0].pbest, DIM*sizeof(double));
	gbestFitness = p[0].pbestFitness;
	for(int i=1; i<N; i++){
		if(p[i].pbestFitness<gbestFitness){
			memcpy(gbest, p[i].pbest, DIM*sizeof(double));
			gbestFitness = p[i].pbestFitness;
		}
	}
}

void PSO::Iterate(int g, int t){
//	if(!(g%200)){
//		LearnMat.ClearLearningMatrix();
//	}
	UpdateExamplar();
	for(int i=0; i<N; i++){
		UpdateVelocity(i);
		UpdatePosition(i);
		if(p[i].isUpdate){
			p[i].EvaluateFitness(index);
		}
	}
	for(int i=0; i<N; i++){
		if(p[i].isUpdate){
			if(p[i].UpdateMemory()){
				if(p[i].pbestFitness<gbestFitness){
					gbestFitness = p[i].pbestFitness;
					memcpy(gbest, p[i].pbest, DIM*sizeof(double));
				}
			}else{
				p[i].flag = p[i].flag + 1;
			}
		}
	}

	if(!(g%200)){
		OutputG(g, index, t, gbestFitness, GEN, name);
//		LearnMat.Result(2);//TODO:set dc=2 here
//		OutputN(index,g,2,LearnMat.cnt,gbestFitness, name);
	}
}

void PSO::UpdateExamplar(){
	for(int i=0; i<N; i++){
		for(int j=0;j<p[i].degree;j++){//更新邻居的fi
			if(p[p[i].link[j]].pbestFitness<p[p[i].fi[0]].pbestFitness){
				for(int d=0; d<DIM; d++){
					p[i].fi[d] = p[i].link[j];
				}
			}
		}
	}
}

void PSO::UpdateVelocity(int i){
	for(int d=0; d<DIM; d++){
		p[i].v[d] = w*p[i].v[d]+c*(Randf()*(p[p[i].fi[d]].pbest[d]-p[i].x[d])+Randf()*(p[i].pbest[d]-p[i].x[d]));
		if(p[i].v[d]<p[i].vmin){
			p[i].v[d]=p[i].vmin;
		}else if(p[i].v[d]>p[i].vmax){
			p[i].v[d]=p[i].vmax;
		}
	}
}

void PSO::UpdatePosition(int i){
	for(int d=0; d<DIM; d++){
		p[i].x[d] = p[i].v[d] + p[i].x[d];
		if(p[i].x[d]<p[i].xmin){
			p[i].x[d]=p[i].xmin;
		}else if(p[i].x[d]>p[i].xmax){
			p[i].x[d]=p[i].xmax;
		}
	}
}

void OutputGHead(int index, int GEN, string str)
{
	ofstream outfile;
	string title;
	stringstream stream;
	stream<<"outputF\\"<<str<<"-Func["<<index<<"].txt";
	title=stream.str();
	outfile.open(title.data(),ios::app);//
	if(outfile.is_open()){
//		if(times == 0){
			outfile<<"g:\t";
			for(int i=0;i<=GEN;i+=200){
				outfile<<i<<"\t";
			}
			outfile<<"gGen\t";
			outfile<<endl;
//		}
	}else{
		cout <<"Failed opening the file:" << title << endl;
	}
}

void OutputG(int g, int index, int times, double gbestFitness, int GEN, string str)
{
	ofstream outfile;
	string title;
	stringstream stream;
	stream<<"outputF\\"<<str<<"-Func["<<index<<"].txt";
	title=stream.str();
	outfile.open(title.data(),ios::app);//
	if(outfile.is_open()){
		if(g == 0){
			outfile<<"n="<<times<<":\t";
		}
		outfile<<gbestFitness<<"\t";
		if(g == GEN){
// TODO Set gGen and goal
//			if(gGen<GEN){
//				outfile<<gGen<<"\t";
//			}else{
//				outfile<<"-1\t";
//			}
			outfile<<endl;
		}
	}else{
		cout <<"Failed opening the file:" << title << endl;
	}
}

PSO::~PSO() {
	// TODO Auto-generated destructor stub
	delete p;
}
