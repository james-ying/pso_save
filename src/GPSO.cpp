/*
 * GPSO.cpp
 *
 *  Created on: 2015Äê4ÔÂ15ÈÕ
 *      Author: lenovo
 */

#include "GPSO.h"
#include<fstream>
#include<iostream>
using namespace std;
GPSO::GPSO(){
	// TODO Auto-generated constructor stub

}
GPSO::GPSO(int N, int DIM, int GEN, int index, int times):
	PSO(N, DIM, GEN, index,times, "GPSO") {
	// TODO Auto-generated constructor stub

}
void GPSO::SetG(){
	char Gbuf[81];
	ifstream infile;
	string title="FullyNetwork.txt";
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
GPSO::~GPSO() {
	// TODO Auto-generated destructor stub
}

