

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
	//ȫ�̼�ʱ��ʼ
	_LARGE_INTEGER time_start;    /*��ʼʱ��*/
	_LARGE_INTEGER time_over;        /*����ʱ��*/
	double dqFreq;                /*��ʱ��Ƶ��*/
	LARGE_INTEGER f;            /*��ʱ��Ƶ��*/
	QueryPerformanceFrequency(&f);
	dqFreq=(double)f.QuadPart;
	QueryPerformanceCounter(&time_start);
	
	mainwindow w; 
	w.show();
	int r=app.exec();
	//��ʱ����
	QueryPerformanceCounter(&time_over); 
	cout<<"ȫ�̺�ʱ:"<<((time_over.QuadPart-time_start.QuadPart)/dqFreq)<<endl;//��λΪ�룬����Ϊ1000 000/��cpu��Ƶ��΢��
   return r;
}
