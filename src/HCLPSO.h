/*
 * HCLPSO.h
 *
 *  Created on: 2015Äê4ÔÂ21ÈÕ
 *      Author: lenovo
 */

#ifndef HCLPSO_H_
#define HCLPSO_H_
#include"PSO.h"
class HCLPSO: public PSO {
public:
	int RefreshingGap;
	HCLPSO();
	HCLPSO(int m0, int m, int t, int DIM, int GEN, int index, int times);
	void SetG();
	void Run();
	void UpdateExamplar();
	void GetRand(int all[], int* rnd, int size, int times);
	void Refresh(int i);
	void UpdateVelocity(int i);
	void UpdatePosition(int i);
	virtual ~HCLPSO();
protected:
	int m0, m, t;
};

#endif /* HCLPSO_H_ */
