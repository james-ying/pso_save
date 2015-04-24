/*
 * Function.cpp
 *
 *  Created on: 2015年4月16日
 *      Author: lenovo
 */
#include <cmath>
#include "Function.h"
#include <cstdlib>

const int NUM=10;
static double bias[NUM], *o[NUM], **M[NUM], wt[NUM], z[NUM];

double Randf()
{
	return ((double)rand()/(double)RAND_MAX);
	//return (double)(rand()%10000)/10000;
}
double abs(double x){
	return x<0?-x:x;
}
void InitRange(int index, double &XMIN, double &XMAX, double &XMINI, double &XMAXI, double &VMIN, double &VMAX)
{
	switch(index){
	case 1:
		XMIN=-100;XMAX=100;XMINI=-100;XMAXI=50;break;
	case 2:
		XMIN=-2.048;XMAX=2.048;XMINI=-2.048;XMAXI=2.048;break;
	case 3:
		XMIN=-32.768;XMAX=32.768;XMINI=-32.768;XMAXI=16;break;
	case 4:
		XMIN=-600;XMAX=600;XMINI=-600;XMAXI=200;break;
//		XMIN=-600;XMAX=600;XMINI=-600;XMAXI=600;break;
	case 5:
		XMIN=-0.5;XMAX=0.5;XMINI=-0.5;XMAXI=0.2;break;//--------
	case 6:
		XMIN=-5.12;XMAX=5.12;XMINI=-5.12;XMAXI=2;break;
	case 7:
		XMIN=-5.12;XMAX=5.12;XMINI=-5.12;XMAXI=2;break;
	case 8:
		XMIN=-500;XMAX=500;XMINI=-500;XMAXI=500;break;//OLPSO
	case 9:
		XMIN=-32.768;XMAX=32.768;XMINI=-32.768;XMAXI=16;break;
	case 10:
		XMIN=-600;XMAX=600;XMINI=-600;XMAXI=200;break;
	case 11:
		XMIN=-0.5;XMAX=0.5;XMINI=-0.5;XMAXI=0.2;break;//
	case 12:
		XMIN=-5.12;XMAX=5.12;XMINI=-5.12;XMAXI=2;break;
	case 13:
		XMIN=-5.12;XMAX=5.12;XMINI=-5.12;XMAXI=2;break;
	case 14:
		XMIN=-500;XMAX=500;XMINI=-500;XMAXI=500;break;
	case 15:
		XMIN=-10;XMAX=10;XMINI=-10;XMAXI=5;break;
	case 16:
		XMIN=-1.28;XMAX=1.28;XMINI=-1.28;XMAXI=0.64;break;
	case 17:
		XMIN=-500;XMAX=500;XMINI=-5;XMAXI=5;break;
	case 18:
		XMIN=-500;XMAX=500;XMINI=-5;XMAXI=5;break;
/*	case :
		XMIN=
		XMAX=
		XMINI=
		XMAXI=
		break;*/
	default:
		break;
	}
	VMAX=0.25*(XMAX-XMIN);
	VMIN=0.25*(XMIN-XMAX);
}
void InitGoal(int index, double &goal)
{
	switch(index){
	case 1:
		goal=0.01;break;
	case 2:
		goal=100;break;
	case 3:
		goal=0.01;break;
	case 4:
		goal=0.05;break;
	case 5:
		goal=0.01;break;//--------
	case 6:
		goal=100;break;
	case 7:
		goal=100;break;
	case 8:
		goal=2000;break;//OLPSO
	case 9:
		goal=0.01;break;
	case 10:
		goal=0.05;break;
	case 11:
		goal=0.01;break;//
	case 12:
		goal=100;break;
	case 13:
		goal=100;break;
	case 14:
		goal=2000;break;
	case 15:
		goal=0.01;break;
	case 16:
		goal=0.05;break;
	case 17:
		goal=0.01;break;
	case 18:
		goal=0.01;break;
/*	case :
		XMIN=
		XMAX=
		XMINI=
		XMAXI=
		break;*/
	default:
		break;
	}
}
void CreateM(double **M, int DIM)
{
	double ME[DIM][DIM],MTurn[DIM][DIM],Mtemp[DIM][DIM];
	double alpha;
	int h,i,j,k;
	for(i=0;i<DIM;i++)//M和ME初始化为单位阵
		for(j=0;j<DIM;j++){
			if(i==j){
				ME[i][j]=1;
				M[i][j]=1;
			}else{
				ME[i][j]=0;
				M[i][j]=0;
			}
		}
	for(h=1;h<DIM;h++){
		alpha=0.5*M_PI*(Randf()-0.5);//
		for(i=0;i<DIM;i++)//Mtemp清零，MTurn初始化为单位阵
			for(j=0;j<DIM;j++){
				MTurn[i][j]=ME[i][j];
				Mtemp[i][j]=0;
			}
		MTurn[0][0]=cos(alpha);//旋转两个维度
		MTurn[h][h]=cos(alpha);
		MTurn[0][h]=sin(alpha);
		MTurn[h][0]=-sin(alpha);
		for(i=0;i<DIM;i++)//相乘
			for(j=0;j<DIM;j++)
				for(k=0;k<DIM;k++)
					Mtemp[i][j]+=M[i][k]*MTurn[k][j];
		for(i=0;i<DIM;i++)
			for(j=0;j<DIM;j++)
				M[i][j]=Mtemp[i][j];
	}
	for(h=1;h<DIM-1;h++){
		alpha=0.5*M_PI*(Randf()-0.5);//
		for(i=0;i<DIM;i++)
			for(j=0;j<DIM;j++){
				MTurn[i][j]=ME[i][j];
				Mtemp[i][j]=0;
			}
		MTurn[h][h]=cos(alpha);
		MTurn[DIM-1][DIM-1]=cos(alpha);
		MTurn[h][DIM-1]=sin(alpha);
		MTurn[DIM-1][h]=-sin(alpha);
		for(i=0;i<DIM;i++)
			for(j=0;j<DIM;j++)
				for(k=0;k<DIM;k++)
					Mtemp[i][j]+=M[i][k]*MTurn[k][j];
		for(i=0;i<DIM;i++)
			for(j=0;j<DIM;j++)
				M[i][j]=Mtemp[i][j];
	}
}
void InitCompoFunc(int DIM){
	for(int n=0; n<NUM; n++){
		o[n] = new double [DIM];
		M[n] = new double *[DIM];
		for(int d=0; d<DIM; d++){
			M[n][d] = new double [DIM];
		}
	}
}

void CreateMforCF(int DIM)
{
	double alpha;
	int h,i,j,k;
	double ME[DIM][DIM],MTurn[DIM][DIM],Mtemp[DIM][DIM];
	for(int num=0; num<NUM; num++){
		for(i=0;i<DIM;i++){//M和ME初始化为单位阵
			for(j=0;j<DIM;j++){
				if(i==j){
					ME[i][j]=1;
					M[num][i][j]=1;
				}else{
					ME[i][j]=0;
					M[num][i][j]=0;
				}
			}
		}
		for(h=1;h<DIM;h++){
			alpha=0.5*M_PI*(Randf()-0.5);
			for(i=0;i<DIM;i++){//Mtemp清零，MTurn初始化为单位阵
				for(j=0;j<DIM;j++){
					MTurn[i][j]=ME[i][j];
					Mtemp[i][j]=0;
				}
			}
			MTurn[0][0]=cos(alpha);//旋转两个维度
			MTurn[h][h]=cos(alpha);
			MTurn[0][h]=sin(alpha);
			MTurn[h][0]=-sin(alpha);
			for(i=0;i<DIM;i++)//相乘
				for(j=0;j<DIM;j++)
					for(k=0;k<DIM;k++)
						Mtemp[i][j]+=M[num][i][k]*MTurn[k][j];
			for(i=0;i<DIM;i++)
				for(j=0;j<DIM;j++)
					M[num][i][j]=Mtemp[i][j];
		}
		for(h=1;h<DIM-1;h++){
			alpha=0.5*M_PI*(Randf()-0.5);
			for(i=0;i<DIM;i++){
				for(j=0;j<DIM;j++){
					MTurn[i][j]=ME[i][j];
					Mtemp[i][j]=0;
				}
			}
			MTurn[h][h]=cos(alpha);
			MTurn[DIM-1][DIM-1]=cos(alpha);
			MTurn[h][DIM-1]=sin(alpha);
			MTurn[DIM-1][h]=-sin(alpha);
			for(i=0;i<DIM;i++)
				for(j=0;j<DIM;j++)
					for(k=0;k<DIM;k++)
						Mtemp[i][j]+=M[num][i][k]*MTurn[k][j];
			for(i=0;i<DIM;i++)
				for(j=0;j<DIM;j++)
					M[num][i][j]=Mtemp[i][j];
		}
	}
}

void ResetCompoFunc(int DIM)
{
	//TODO: should be udi and ldi from Particle class
	double ud=5,ld=-5;
	CreateMforCF(DIM);
	for(int num=0;num<NUM-1;num++){
		for(int d=0;d<DIM;d++)
			o[num][d]=Randf()*(ud-ld)+ld;
	}
	for(int d=0;d<DIM;d++)
		o[NUM-1][d]=0;
	for(int num=0;num<NUM;num++){
		bias[num]=num*100;
		z[num]=ud;
	}
}


double round(double x)
{
	return (x>0.0)?floor(x+0.5):ceil(x-0.5);
}
//Sphere function
double f1(double x[], int DIM)
{
	double fx=0;
	int d;
	for(d=0;d<DIM;d++){
		fx+=pow(x[d],2);
	}
	return fx;
}
//Rosenbrock's function
double f2(double x[], int DIM)
{
	double fx=0;
	int d;
	for(d=0;d<DIM-1;d++){
		fx+=100*(x[d+1]-x[d]*x[d])*(x[d+1]-x[d]*x[d])+(x[d]-1)*(x[d]-1);
	}
	return fx;
}
//Ackley's function
double f3(double x[], int DIM)
{
	double fx=0;
	double fx1=0,fx2=0;
	int d;
	for(d=0;d<DIM;d++){
		fx1=fx1+pow(x[d],2);
		fx2=fx2+cos(M_2PI*x[d]);//
	}
//	fx1=fx1/DIM;
//	fx2=fx2/DIM;
	//fx=20+E-20*exp(-0.2*sqrt((double)fx1/DIM))-exp((double)fx2/DIM);
	fx=-20*exp(-0.2*sqrt(fx1/DIM))-exp(fx2/DIM)+20+M_E;
	return fx;
}
//Griewanks's function
double f4(double x[], int DIM)
{
	double fx=0;
	double fx1=0;
	double fx2=1;
	int d;
	for(d=0;d<DIM;d++){
		fx1=fx1+x[d]*x[d];
		fx2=fx2*cos(x[d]/sqrt((double)d+1));//d=>d+1
	}
	fx=fx1/4000-fx2+1;
	return fx;
}
//Weierstrass function
double f5(double x[], int DIM)
{
	double fx=0;
	int d,k;
	const int kmax=20;
	double ea[kmax+1];
	double eb[kmax+1];
	//int ebint[kmax+1];
	for(int k=0;k<kmax+1;k++){
		ea[k]=pow((double)0.5,k);
		eb[k]=pow(3.0,k);

	}
	for(k=kmax;k>=0;k--){
		for(d=0;d<DIM;d++)
			fx+=ea[k]*(cos(eb[k]*(x[d]+0.5)*M_2PI)-cos(M_PI*eb[k]));
	}
	return fx;
}
//Rastrigin's function
double f6(double x[], int DIM)
{
	double fx=0;
//	double fx1=0,fx2=0;
	int d;
	for(d=0;d<DIM;d++){
		fx=fx+(x[d]*x[d]-10*cos(M_2PI*x[d])+10);
//		fx1=fx1+pow(x[d],2.0);
//		fx2=fx2-cos(M_2PI*x[d]);
//		fx=fx+10;
	}
//	fx=fx+fx1+fx2*10;
	return fx;
}
//Noncontinuous Rastrigin's function
double f7(double x[], int DIM)
{
	double fx=0;;
	double y;
	int d;
	for(d=0;d<DIM;d++){
		if(abs(x[d])<0.5){
			y=x[d];
		}else{
			y=round(2.0*x[d])/2;
		}
		fx+=y*y-10*cos(M_2PI*y)+10;
	}
	return fx;
}
//Schwefel's function
double f8(double x[], int DIM)
{
	double fx1=0;
	fx1=0;
	for(int d=0; d<DIM; d++){
		fx1=fx1+418.9829-x[d]*sin(sqrt(abs(x[d])));
	}
	return fx1;
//	double fx=0;
//	int d;
//	double temp;
//	for(d=0;d<DIM;d++){
//		fx=fx+418.9829-x[d]*sin(sqrt(abs(x[d])));
//	}
//	return fx;
}
//Rotated Ackley's function
double f9(double x[], int DIM, double **M)
{
	double fx=0;
	double fx1=0,fx2=0;
	int d;
	double y[DIM];
	for(d=0;d<DIM;d++){
		y[d]=0;
		for(int j=0;j<DIM;j++)
			y[d]+=M[d][j]*x[j];
	}
	for(d=0;d<DIM;d++){
		fx1=fx1+y[d]*y[d];
		fx2=fx2+cos(M_2PI*y[d]);
	}
	fx=(20-20*exp(-0.2*sqrt(fx1/(double)DIM)))+(M_E-exp(fx2/(double)DIM));
	return fx;
}
//Rotated Griewanks's function
double f10(double x[], int DIM, double **M)
{
	double fx=0;
	double fx1=0;
	double fx2=1;
	int d;
	double y[DIM];
	for(d=0;d<DIM;d++){
		y[d]=0;
		for(int j=0;j<DIM;j++)
			y[d]+=M[d][j]*x[j];//x[j]*M[j][d];
	}
	for(d=0;d<DIM;d++){
		fx1=fx1+y[d]*y[d];
		fx2=fx2*cos(x[d]/sqrt((double)d+1));//d=>d+1
	}
	fx=fx1/4000-fx2+1;
	return fx;
}
//Rotated Weierstrass function
double f11(double x[], int DIM, double **M)
{
	double fx=0,fx1=0;
	int d,j,k,kmax=20;
	double a=0.5,b=3;
	double ak;
	int bk;
	double y[DIM];
	for(d=0;d<DIM;d++){
	//	y[d]=x[d];
		y[d]=0;
		for(j=0;j<DIM;j++)
			y[d]+=M[d][j]*x[j];//x[j]*M[j][d];
	}
	for(k=0;k<kmax+1;k++){
		ak=pow(a,k);
		bk=pow(b,k);
		for(d=0;d<DIM;d++){
			fx1=cos(M_2PI*bk*(y[d]+0.5))-cos(M_PI*bk);
			fx+=fx1*ak;
		}
	}
	return fx;
}
//Rotated Rastrigin's function
double f12(double x[], int DIM, double **M)
{
	double fx=0;
	int d,j;
	double y;
	for(d=0;d<DIM;d++){
		y=0;
		for(j=0;j<DIM;j++)
			y=y+M[d][j]*x[j];//x[j]*M[j][d];
		fx=fx+pow(y,(double)2)-10*cos(M_2PI*y)+10;
	}
	return fx;
}
//Rotated noncontinuous Rastrigin's function
double f13(double x[], int DIM, double **M)
{
	double fx=0;;
	double z;
	int d;
	double y[DIM];
	for(d=0;d<DIM;d++){
		y[d]=0;
		for(int j=0;j<DIM;j++)
			y[d]+=M[d][j]*x[j];//x[j]*M[j][d];
	}
	for(d=0;d<DIM;d++){
		if(abs(y[d])<0.5)
			z=y[d];
		else
			z=round(2.0*y[d])/2;
		fx+=z*z-10*cos(M_2PI*z)+10;
	}
	return fx;
}
//Rotated Schwefel's function
double f14(double x[], int DIM, double **M)
{
	double fx=0;
	int d,j;
	double z;
	double y[DIM];
	for(d=0;d<DIM;d++){
		y[d]=0;
		for(j=0;j<DIM;j++)
			y[d]+=M[d][j]*(x[j]-420.96);
		y[d]+=420.96;
	}
	fx=418.9829*DIM;
	for(d=0;d<DIM;d++){
		if(abs(y[d])<=500)
			z=y[d]*sin(sqrt(abs(y[d])));
		else
			z=0.001*pow((abs(y[d])-500),2);
		fx=fx-z;
	}
	return fx;
}
//Schwefel's P2.22
double f15(double x[], int DIM)
{
	double fx=0,fx1=0,fx2=1;
	int d;
	for(d=0;d<DIM;d++){
		fx1=fx1+abs(x[d]);
		fx2=fx2*abs(x[d]);
	}
	fx=fx1+fx2;
	return fx;
}
//Noise
double f16(double x[], int DIM)
{
	double fx=0;
	int d;
	for(d=0;d<DIM;d++){
		fx=fx+pow(x[d],4)*(d+1);
	}
	fx=fx+Randf();
	return fx;
}

double f17(double x[], int DIM)
{
	int d,num;
	double fit[NUM],fmax[NUM],ff[NUM],lambda[NUM];
	double fx=0,sigmax[NUM];
	double y[DIM];
	double temp;
	//
	for(num=0;num<NUM;num++){
		sigmax[num]=0;
		lambda[num]=5.0/100;
	}
	for(num=0;num<NUM;num++){
		for(d=0;d<DIM;d++)
			sigmax[num]+=(x[d]-o[num][d])*(x[d]-o[num][d]);
		wt[num]=exp(-sigmax[num]/(2*DIM));
		//cout<<"wt["<<num<<"]="<<wt[num]<<"\t";//
		//
		for(d=0;d<DIM;d++){
			y[d]=0;
			for(int j=0;j<DIM;j++){
				temp=M[num][d][j]*(x[j]-o[num][j])/lambda[num];
			//	cout<<"M["<<num<<"]["<<j<<"]["<<d<<"]"<<M[num][j][d]<<endl;
			//	cout<<"lambda["<<num<<"]="<<lambda[num]<<endl;
				y[d]+=temp;//Mi改过来
			}
			//cout<<"y["<<d<<"]="<<y[d]<<endl;////////
		}
		fit[num]=f1(y,DIM);//cout<<"fit["<<num<<"]="<<fit[num]<<endl;
		//
		for(d=0;d<DIM;d++){
			y[d]=0;
			for(int j=0;j<DIM;j++)
				y[d]+=M[num][d][j]*z[num]/lambda[num];
		}
		fmax[num]=f1(y,DIM);//cout<<"fmax["<<num<<"]="<<fmax[num]<<endl;
		//
		ff[num]=2000*fit[num]/fmax[num];//cout<<"ff["<<num<<"]="<<ff[num]<<endl;

	}
	double SumW=0;
	double MaxW=wt[0];
	for(num=0;num<NUM;num++){
		SumW+=wt[num];
		//
		if(wt[num]>MaxW)
			MaxW=wt[num];
	}
	for(num=0;num<NUM;num++){
		if(wt[num]!=MaxW)
			wt[num]=wt[num]*(1-pow(MaxW,10));
		wt[num]/=SumW;
	}
	for(num=0;num<NUM;num++){
		fx+=wt[num]*(ff[num]+bias[num]);
	}
	//cout<<endl;//////
	return fx;
}

double f18(double x[],int DIM)
{
	int d,num;
	double fit[NUM],fmax[NUM],ff[NUM],lambda[NUM];
	double fx=0,sigmax[NUM];
	double y[DIM];
	double temp;
	//
	for(num=0;num<NUM;num++){
		sigmax[num]=0;
		switch(num){
		case 0:lambda[num]=1.0/5;break;
		case 1:lambda[num]=1.0/5;break;
		case 2:lambda[num]=5.0/0.5;break;
		case 3:lambda[num]=5.0/0.5;break;
		case 4:lambda[num]=5.0/100;break;
		case 5:lambda[num]=5.0/100;break;
		case 6:lambda[num]=5.0/32;break;
		case 7:lambda[num]=5.0/32;break;
		case 8:lambda[num]=5.0/100;break;
		case 9:lambda[num]=5.0/100;break;
		default:break;
		}
	}
	for(num=0;num<NUM;num++){
		for(d=0;d<DIM;d++)
			sigmax[num]+=(x[d]-o[num][d])*(x[d]-o[num][d]);
		wt[num]=exp(-sigmax[num]/(2*DIM));
		//cout<<"wt["<<num<<"]="<<wt[num]<<"\t";//
		//
		for(d=0;d<DIM;d++){
			y[d]=0;
			for(int j=0;j<DIM;j++){
				temp=M[num][d][j]*(x[j]-o[num][j])/lambda[num];
			//	cout<<"M["<<num<<"]["<<j<<"]["<<d<<"]"<<M[num][j][d]<<endl;
			//	cout<<"lambda["<<num<<"]="<<lambda[num]<<endl;
				y[d]+=temp;//Mi改过来
			}
			//cout<<"y["<<d<<"]="<<y[d]<<endl;////////
		}
		//fit[num]=f1(y,dim);//cout<<"fit["<<num<<"]="<<fit[num]<<endl;
		switch(num){
		case 0:fit[num]=f6(y,DIM);break;
		case 1:fit[num]=f6(y,DIM);break;
		case 2:fit[num]=f5(y,DIM);break;
		case 3:fit[num]=f5(y,DIM);break;
		case 4:fit[num]=f4(y,DIM);break;
		case 5:fit[num]=f4(y,DIM);break;
		case 6:fit[num]=f3(y,DIM);break;
		case 7:fit[num]=f3(y,DIM);break;
		case 8:fit[num]=f1(y,DIM);break;
		case 9:fit[num]=f1(y,DIM);break;
		default:break;
		}
		//
		for(d=0;d<DIM;d++){
			y[d]=0;
			for(int j=0;j<DIM;j++)
				y[d]+=M[num][d][j]*z[num]/lambda[num];
		}
		//fmax[num]=f1(y,dim);//cout<<"fmax["<<num<<"]="<<fmax[num]<<endl;
		switch(num){
		case 0:fmax[num]=f6(y,DIM);break;
		case 1:fmax[num]=f6(y,DIM);break;
		case 2:fmax[num]=f5(y,DIM);break;
		case 3:fmax[num]=f5(y,DIM);break;
		case 4:fmax[num]=f4(y,DIM);break;
		case 5:fmax[num]=f4(y,DIM);break;
		case 6:fmax[num]=f3(y,DIM);break;
		case 7:fmax[num]=f3(y,DIM);break;
		case 8:fmax[num]=f1(y,DIM);break;
		case 9:fmax[num]=f1(y,DIM);break;
		default:break;
		}
		//
		ff[num]=2000*fit[num]/fmax[num];//cout<<"ff["<<num<<"]="<<ff[num]<<endl;

	}
	double SumW=0;
	double MaxW=wt[0];
	for(num=0;num<NUM;num++){
		SumW+=wt[num];
		//
		if(wt[num]>MaxW)
			MaxW=wt[num];
	}
	for(num=0;num<NUM;num++){
		if(wt[num]!=MaxW)
			wt[num]=wt[num]*(1-pow(MaxW,10));
		wt[num]/=SumW;
	}
	for(num=0;num<NUM;num++){
		fx+=wt[num]*(ff[num]+bias[num]);
	}
	//cout<<endl;//////
	return fx;
}

double f(double *x, int DIM, int index, double **M)
{
	switch(index){
	case 1:
		return f1(x,DIM);break;
	case 2:
		return f2(x,DIM);break;
	case 3:
		return f3(x,DIM);break;
	case 4:
		return f4(x,DIM);break;
	case 5:
		return f5(x,DIM);break;
	case 6:
		return f6(x,DIM);break;
	case 7:
		return f7(x,DIM);break;
	case 8:
		return f8(x,DIM);break;
	case 9:
		return f9(x,DIM,M);break;
	case 10:
		return f10(x,DIM,M);break;
	case 11:
		return f11(x,DIM,M);break;
	case 12:
		return f12(x,DIM,M);break;
	case 13:
		return f13(x,DIM,M);break;
	case 14:
		return f14(x,DIM,M);break;
	case 15:
		return f15(x,DIM);break;
	case 16:
		return f16(x,DIM);break;
	case 17:
		return f17(x,DIM);break;
	case 18:
		return f18(x,DIM);break;
	default:
		 return -1;break;
	}
}
