/*
 * CLPSO.h
 *
 *  Created on: 2015Äê4ÔÂ20ÈÕ
 *      Author: lenovo
 */

#ifndef CLPSO_H_
#define CLPSO_H_
#include "PSO.h"
class CLPSO:public PSO {
public:
	int RefreshingGap;
	CLPSO();
	CLPSO(int N, int DIM, int GEN, int index, int times);
	void UpdateExamplar();
	void Refresh(int i);
	void UpdateVelocity(int i);//overload
	void UpdatePosition(int i);
	void Run();
	virtual ~CLPSO();
};

#endif /* CLPSO_H_ */
