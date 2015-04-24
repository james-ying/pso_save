/*
 * Particle.cpp
 *
 *  Created on: 2015Äê4ÔÂ14ÈÕ
 *      Author: lenovo
 */

#include "Particle.h"
#include "Function.h"
Particle::Particle() {

}
Particle::Particle(int N, int DIM, double **M):
	DIM(DIM),
	N(N),
	x(new double[DIM]),
	v(new double[DIM]),
	fitness(0),
	pbest(new double[DIM]),
	pbestFitness(0),
	fi(new int[DIM]),
	link(new int[N]),
	degree(0),
	PC(0),
	flag(0),
	isUpdate(true),
	xmin(0), xmax(0), xmini(0), xmaxi(0), vmin(0), vmax(0),
	M(M)
{
//	InitRange(index, xmin, xmax, xmini, xmaxi, vmin, vmax);
//	for(int d=0; d<this->DIM; d++){
//		x[d] = Randf()*(xmaxi-xmini)+xmini;//Randf()*(XMAXI-XMINI)+XMINI;
//		v[d] = Randf()*(xmaxi-xmini)+xmini;
//		EvaluateFitness(index);
//		pbest[d] = x[d];
//		pbestFitness = fitness;
//	}
}
void Particle::Initialize(int index, double **M){
	this->M = M;
	InitRange(index, xmin, xmax, xmini, xmaxi, vmin, vmax);
	for(int d=0; d<DIM; d++){
		x[d] = Randf()*(xmaxi-xmini)+xmini;//Randf()*(XMAXI-XMINI)+XMINI;
		v[d] = 0;
		EvaluateFitness(index);
		pbest[d] = x[d];
		pbestFitness = fitness;
	}
}

bool Particle::UpdateMemory(){
	if(fitness<pbestFitness){
		pbestFitness = fitness;
		memcpy(pbest, x, DIM*sizeof(double));
		return true;
	}else{
		return false;
	}
}

//void Particle::UpdatePosition(){
////	memcpy(this->v, v, DIM);
//	for(int d=0; d<DIM; d++){
//		x[d] = v[d] + x[d];
//	}
//}

//double Particle::GetPbestFitness(){
//	return pbestFitness;
//}
//
//void Particle::GetPbestPosition(double *best, int DIM){
//	memcpy(best, pbest, DIM);
//}

Particle::~Particle() {
	// TODO Auto-generated destructor stub
//	delete[] x;
//	delete[] v;
//	delete[] pbest;
//	delete[] link;
}
