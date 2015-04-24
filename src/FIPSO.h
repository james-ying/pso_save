/*
 * FIPSO.h
 *
 *  Created on: 2015Äê4ÔÂ20ÈÕ
 *      Author: lenovo
 */

#ifndef FIPSO_H_
#define FIPSO_H_
#include "LPSO.h"
class FIPSO: public LPSO {
public:
//	double **r;
	double **pk;
	FIPSO();
	FIPSO(int N, int DIM, int GEN, int index, int times);
	void UpdateExamplar();
	void UpdateVelocity(int i);
	virtual ~FIPSO();
};

#endif /* FIPSO_H_ */
