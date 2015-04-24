/*
 * Particle.h
 *
 *  Created on: 2015年4月14日
 *      Author: lenovo
 */

#ifndef PARTICLE_H_
#define PARTICLE_H_
#include<cstdlib>
#include<cstring>
#include "Function.h"
class Particle {
public:
	int DIM;
	int N;//for link
	double *x;
	double *v;
	double fitness;
	double *pbest;
	double pbestFitness;
	int *fi;//每维向谁学习
	int *link;
	int degree;
	double PC;
	int flag;
	bool isUpdate;
	double xmin, xmax, xmini, xmaxi, vmin, vmax;
	Particle();
	Particle(int N, int DIM, double **M);
//	void SetNbest(const double *nbest);
	void Initialize(int index, double **M);
	bool UpdateMemory();//pbest// and nbest
	inline void EvaluateFitness(int index){//evaluate fitness
		// TODO Set index=1
		fitness = f(x, DIM, index, M);
	};
//	double GetPbestFitness();//get pbest fitness value
//	void GetPbestPosition(double *best, int DIM);//get pbest position
	inline double Randf(){
		return ((double)rand()/(double)RAND_MAX);
	};
	virtual ~Particle();
private:
	double **M;
};
#endif /* PARTICLE_H_ */
