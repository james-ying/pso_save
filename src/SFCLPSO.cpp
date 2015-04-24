/*
 * SFCLPSO.cpp
 *
 *  Created on: 2015年4月20日
 *      Author: lenovo
 */

#include "SFCLPSO.h"
#include <cmath>
SFCLPSO::SFCLPSO() {
	// TODO Auto-generated constructor stub

}
SFCLPSO::SFCLPSO(int m0, int m, int t, int DIM, int GEN, int index, int times) :
		SFPSO(m0, m, t, DIM, GEN, index, times, "SFCLPSO"), RefreshingGap(7), m0(m0), m(m), t(
				t) {
	// TODO Auto-generated constructor stub
}

void SFCLPSO::Run() {
	OutputGHead(index, GEN, name);
	for (int t = 0; t < times; t++) {
		InitNeighbor();
		for (int i = 0; i < N; i++) {
			p[i].PC = 1 / (1 + pow(M_E, (2 * m - p[i].degree)));
		}
//		for (int tnet = 0; tnet < 5; tnet++) {
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
//		}
	}
}

void SFCLPSO::UpdateExamplar() {
	for (int i = 0; i < N; i++) {
		if (p[i].flag >= RefreshingGap) {
			Refresh(i);
			p[i].flag = 0;
		}
	}
}
void SFCLPSO::GetRand(int all[], int* rnd, int size, int times) {
	for (int i = 0; i < times; i++) {
		int r = rand() % (size - i);
		rnd[i] = all[r];
		int temp = all[r];
		all[r] = all[size - 1 - i];
		all[size - 1 - i] = temp;
	}
}
void SFCLPSO::Refresh(int i) {
	int iTemp[N]; //随机选俩比较适应值，记下适应值更好的iTemp，iTemp是粒子编号
	int CandidateNumber, cnt;
	double bestf;
	if (p[i].degree < m * 2) {
		CandidateNumber = 2;
	} else {
		CandidateNumber = 4; //candidatenumber=m;
	}
	for (int d = 0; d < DIM; d++) {// for each dimension
		GetRand(p[i].link, iTemp, p[i].degree, CandidateNumber); //random sort
		p[i].fi[d] = iTemp[0];
		bestf = p[p[i].fi[d]].pbestFitness;
		for (cnt = 0; cnt < CandidateNumber; cnt++) {
			if (p[iTemp[cnt]].pbestFitness < bestf) {
				p[i].fi[d] = iTemp[cnt];
				bestf = p[iTemp[cnt]].pbestFitness;
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

void SFCLPSO::UpdateVelocity(int i) {
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

void SFCLPSO::UpdatePosition(int i) {
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

SFCLPSO::~SFCLPSO() {
	// TODO Auto-generated destructor stub
}
