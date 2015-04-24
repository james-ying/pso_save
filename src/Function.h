/*
 * Function.h
 *
 *  Created on: 2015Äê4ÔÂ16ÈÕ
 *      Author: lenovo
 */

#ifndef FUNCTION_H_
#define FUNCTION_H_
#define M_2PI 6.28318530717958647692
#define M_PI 3.14159265358979323846
#define M_PI2 1.57079632679489661923
//#define M_E 2.71828182845904523536
void InitRange(int index, double &XMIN, double &XMAX,
						double &XMINI, double &XMAXI,
						double &VMIN, double &VMAX);
double Randf();
void InitGoal(int index, double &goal);
void CreateM(double **M, int DIM);
void InitCompoFunc(int DIM);
void ResetCompoFunc(int DIM);
double f1(double x[], int DIM);
double f2(double x[], int DIM);
double f3(double x[], int DIM);
double f4(double x[], int DIM);
double f5(double x[], int DIM);
double f6(double x[], int DIM);
double f7(double x[], int DIM);
double f8(double x[], int DIM);
double f9(double x[], int DIM);
double f10(double x[], int DIM);
double f11(double x[], int DIM);
double f12(double x[], int DIM);
double f13(double x[], int DIM);
double f14(double x[], int DIM);
double f15(double x[], int DIM);
double f16(double x[], int DIM);
double f(double x[], int DIM, int index, double **M);
#endif /* FUNCTION_H_ */
