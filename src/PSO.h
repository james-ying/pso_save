/*
 * PSO.h
 *
 *  Created on: 2015年4月14日
 *      Author: lenovo
 */

#ifndef PSO_H_
#define PSO_H_
#include "Particle.h"
#include <string>
using namespace std;
class PSO {
public:
	double w;
	double c;
	double *gbest;
	double gbestFitness;
	int **G;
	double **M;
	int index;
	string name;
public:
	PSO();
	PSO(int N, int DIM, int GEN, int index, int times, string name);//vector版本
	void Initialize();
	void InitNeighbor();
	virtual void SetG();
	virtual void Run();
	virtual void UpdateVelocity(int i);//overload
	virtual void UpdatePosition(int i);
	void Iterate(int g, int t);
	virtual void UpdateExamplar();//overload
	inline double Randf(){
		return ((double)rand()/(double)RAND_MAX);
	};
	virtual ~PSO();
protected:
	int N;
	int DIM;
	int GEN;
	int times;
	double goal;
	Particle *p;
};
void OutputGHead(int index, int GEN, string str);
void OutputG(int g, int index, int times, double gbestFitness, int GEN, string str);
#endif /* PSO_H_ */
