/*
 * LPSO.h
 *
 *  Created on: 2015��4��16��
 *      Author: lenovo
 */

#ifndef LPSO_H_
#define LPSO_H_
#include "PSO.h"
class LPSO :public PSO {
public:
	LPSO();
	LPSO(int N, int DIM, int GEN, int index, int times);
	void SetG();
	virtual ~LPSO();
};

#endif /* LPSO_H_ */
