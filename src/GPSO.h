/*
 * GPSO.h
 *
 *  Created on: 2015Äê4ÔÂ15ÈÕ
 *      Author: lenovo
 */

#ifndef GPSO_H_
#define GPSO_H_
#include "PSO.h"
class GPSO : public PSO {
public:
	GPSO();
	GPSO(int N, int DIM, int GEN, int index, int times);
	void SetG();
	virtual ~GPSO();
};

#endif /* GPSO_H_ */
