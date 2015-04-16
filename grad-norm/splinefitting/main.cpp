

#include <QApplication>
#include <QtGui>
#include "mainwindow.h"
#include <windows.h>
#include <iostream>
using namespace std;
int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	app.setApplicationName("B-spline fitting");
	std::cout.precision(10);
	//std::cout << std::scientific;
	std::cout<<"B-spline fitting begin ..."<<std::endl;
	//全程计时开始
	_LARGE_INTEGER time_start;    /*开始时间*/
	_LARGE_INTEGER time_over;        /*结束时间*/
	double dqFreq;                /*计时器频率*/
	LARGE_INTEGER f;            /*计时器频率*/
	QueryPerformanceFrequency(&f);
	dqFreq=(double)f.QuadPart;
	QueryPerformanceCounter(&time_start);
	
	mainwindow w; 
	w.show();
	int r=app.exec();
	//计时结束
	QueryPerformanceCounter(&time_over); 
	cout<<"全程耗时:"<<((time_over.QuadPart-time_start.QuadPart)/dqFreq)<<endl;//单位为秒，精度为1000 000/（cpu主频）微秒
   return r;
}
