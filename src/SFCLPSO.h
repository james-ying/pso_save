/*
 * SFCLPSO.h
 *
 *  Created on: 2015Äê4ÔÂ20ÈÕ
 *      Author: lenovo
 */

#ifndef SFCLPSO_H_
#define SFCLPSO_H_
#include "SFPSO.h"
class SFCLPSO: public SFPSO {
public:
	int RefreshingGap;
	SFCLPSO();
	SFCLPSO(int m0, int m, int t, int DIM, int GEN, int index, int times);
	void UpdateExamplar();
	void GetRand(int all[], int* rnd, int size, int times);
	void Refresh(int i);
	void UpdateVelocity(int i); //overload
	void UpdatePosition(int i);
	void Run();
	virtual ~SFCLPSO();
protected:
	int m0, m, t;
};
#endif /* SFCLPSO_H_ */

