/*
 * LPSO.cpp
 *
 *  Created on: 2015Äê4ÔÂ16ÈÕ
 *      Author: lenovo
 */

#include "LPSO.h"
#include<fstream>
#include<iostream>
using namespace std;
LPSO::LPSO() {
	// TODO Auto-generated constructor stub

}
LPSO::LPSO(int N, int DIM, int GEN, int index, int times):
	PSO(N, DIM, GEN, index, times, "LPSO") {
	// TODO Auto-generated constructor stub
}

void LPSO::SetG(){
	char Gbuf[81];
	ifstream infile;
	string title="RingNetwork.txt";
	infile.open(title.data());//
	if(infile.is_open()){
		for(int i=0;i<N;i++){
			infile.getline(Gbuf,2*N+1);
			for(int j=0;j<N;j++){
				G[i][j]=Gbuf[j*2]-'0';
			}
//			cout<<endl;
		}
	}else{
		cout<<"Failed opening the file:"<< title <<endl;
	}

}
LPSO::~LPSO() {
	// TODO Auto-generated destructor stub
}

