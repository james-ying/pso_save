/*
 * FIPSO.cpp
 *
 *  Created on: 2015Äê4ÔÂ20ÈÕ
 *      Author: lenovo
 */

#include "FIPSO.h"

FIPSO::FIPSO() {
	// TODO Auto-generated constructor stub

}
FIPSO::FIPSO(int N, int DIM, int GEN, int index, int times):
	LPSO(N, DIM, GEN, index, times),
//	r(new double *[N]),
	pk(new double *[N])
{
	for(int i=0; i<N; i++){
//		r[i] = new double[DIM];
		pk[i] = new double[DIM];
	}
}

void FIPSO::UpdateExamplar()
{
	for(int i=0; i<N; i++){
		int l, j;
		for (l=0;l<=N-1;l++)
		{
			for (j=0;j<=DIM-1;j++)
			{
				pk[i][j]=0;
			}
		}
//		for(l=0;l<=N-1;l++)
//		{
//			if(G[i][l]==1)
//			{
//				for (j=0;j<=DIM-1;j++)
//				{
//					r[l][j]=Randf()*4.1;//fai=4.1
//				}
//			}
//			else
//			{
//				for (j=0;j<=DIM-1;j++)
//				{
//					r[l][j]=0;
//				}
//			}
//		}
		for (l=0;l<=N-1;l++)
		{
			if(G[i][l]==1)
			{
				for (j=0;j<=DIM-1;j++)
				{
//					pk[i][j]=r[l][j]*(p[l].pbest[j]-p[i].x[j])+pk[i][j];
					pk[i][j]=Randf()*4.1*(p[l].pbest[j]-p[i].x[j])+pk[i][j];
				}
			}
		}
	}
}

void FIPSO::UpdateVelocity(int i){
	for(int d=0; d<DIM; d++){
		p[i].v[d]=0.729*(p[i].v[d]+pk[i][d]/p[i].degree);
	}
}
//void FIPSO
FIPSO::~FIPSO() {
	// TODO Auto-generated destructor stub
}

