/*
 * GraphOperation.cpp
 *
 *  Created on: 2015Äê4ÔÂ22ÈÕ
 *      Author: lenovo
 */

#include "GraphOperation.h"
void Swap(int **G, int N, int i, int j){
	int *temp = new int[N];
	memcpy(temp, G[i], N*sizeof(int));
	memcpy(G[i], G[j], N*sizeof(int));
	memcpy(G[j], temp, N*sizeof(int));
	for(int k=0; k<N; k++){
		temp[k] = G[k][i];
		G[k][i] = G[k][j];
		G[k][j] = temp[k];
	}
	delete temp;
}

void SortG(int **G, int *idx, int N){
	int temp;
	for(int i=0; i<N; i++){
		temp=i;
		for(int j=i; j<N; j++){
			if(idx[j]>idx[temp]){
				temp = j;
			}
		}
		if(temp>i){
			Swap(G, N, i, temp);
			int t=idx[i];
			idx[i]=idx[temp];
			idx[temp]=t;
		}
	}
}
