/*
 * SFPSO.h
 *
 *  Created on: 2015Äê4ÔÂ20ÈÕ
 *      Author: lenovo
 */

#ifndef SFPSO_H_
#define SFPSO_H_
#include "PSO.h"
class SFPSO :public PSO {
public:
	SFPSO();
//	SFPSO(int N, int DIM, int GEN, int index, int times);
	SFPSO(int m0, int m, int t, int DIM, int GEN, int index, int times, string name);
	void SetG();
	void Run();
	virtual ~SFPSO();
protected:
	int m0, m, t;
};

#endif /* SFPSO_H_ */
