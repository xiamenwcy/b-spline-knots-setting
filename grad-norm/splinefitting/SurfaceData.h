#pragma once

#include <CGAL/Bbox_2.h>
#include <CGAL/Bbox_3.h>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QObject>
#include "BSplineView.h"
#include "B_parameter.h"
#include "data_types.h"
#include <vector>
#include <math.h>
#include <iostream>
#include <algorithm>
#include <assert.h>
//cgal
#include <CGAL/Segment_2.h>
#include <CGAL/Triangle_2.h>
#include <CGAL/Iso_rectangle_2.h>
#include <CGAL/Triangle_2_Iso_rectangle_2_intersection.h>
#include <CGAL/Segment_2_Triangle_2_intersection.h>
#include <CGAL/Cartesian.h>
#include <CGAL/Point_2.h>
#include <CGAL/Polygon_2.h>

//ANN
#include <ANN/ANN.h>					// ANN declarations
using namespace std;

const double  EPSILON = 10e-16;
const double  EPSILON2 = 10e-5;

typedef CGAL::Cartesian<double>                           Kernel;
typedef CGAL::Point_2<Kernel>                          Point_2; 
typedef CGAL::Segment_2<Kernel>                        Segment_2;
typedef  CGAL::Triangle_2<Kernel>                      Triangle_2;
typedef  CGAL::Iso_rectangle_2<Kernel>                 Iso_rectangle_2;
typedef CGAL::Polygon_2<Kernel>                           Polygon_2;
typedef CGAL::Bbox_2                                        Bbox_2;
typedef CGAL::Bbox_3                                        Bbox_3;

class CSurfaceData :
	public  QObject
{
	Q_OBJECT
public:
	CSurfaceData(void);
	~CSurfaceData(void);
	bool read_mesh(const QString &fileName);

	int get_mesh_vertex_num();
	int get_mesh_face_num();

	QString get_mesh_name();
	Mesh *get_original_mesh();
	void setparameter(B_parameter *parameter_2);
	//���ӽڵ���
	void set_knots_adding_num(int num);//ÿ��Ӧ�����ӵ���ֱ�ڵ����������û�ָ��
	void set_horizon_knots_addnum(int num);//ÿ��Ӧ�����ӵ�ˮƽ�ڵ����������û�ָ��
	bool add_knots();
    bool add_horizon_knots();
	void  adjust_vertical_knots();//����ʵʩ��ֱ�ڵ������
	void  adjust_horizon_knots();//����ʵʩˮƽ�ڵ������
	void range_query();//��ѯÿ�����εĶ���
	void range_query2();//�޶��ڵ���
	bool  rangequery_vertical;//ָ��adjust_vertical_knots()����range_query()��ִ�����
	bool  rangequery_horizon;//ָ��adjust_horizon_knots()����range_query()��ִ�����

	int   sum(std::vector<KnotData> &vec);
	void   set_max_curvature(double curvature);
	double get_max_meancurvature();
    double get_min_meancurvature();
	B_parameter *getparameter();
	Mesh *get_fitted_mesh();

	bool mesh_fitting();
    CBSplineSurfaceView* getbspline();
	vector<TexCoord>  get_domain();

	Bbox_2 &get_box();
	Bbox_3 get_original_box();
	Bbox_3 get_fitting_box();
    Bbox_3 get_error_box();
	void   set_original_box(Bbox_3 box);
    void   set_fitting_box(Bbox_3 box);

	bool mesh_parameterization();
	void compute_error();
	bool curvature_loading();
	bool fitting_completed();
	bool curvature_error_completed();
	void set_fitting_completed(bool state);
	void set_curvature_loadingstate(bool state);
	bool compute_curvature(QStringList files);
    int  label;


	 bool interection_st( Triangle_2 tri,Segment_2 seg,double *length);//����������ཻ
	 bool  intersection_rt(Triangle_2 tri,Iso_rectangle_2 rec,double *Area);//������������εĽ���

	void  update_curvature_color();
	//�����������
	 void  update_knots(int k);
    //����������
     void  update_knots2(int k);
	
	//�����ڵ���
	bool  adjust_knots();
	bool  adjust_knots_by_fitting_error();
	void  modification();//�޶������ʵĽڵ�

    vector<double> uknots;
	vector<double> vknots;
	vector<knot_info> uknots_new;
	vector<knot_info> vknots_new;//��������ÿ�������ӵĽڵ���

	
	int unum;
	int vnum;
	static int iter_num;
	 ANNkd_tree*			kdTree;					// search structure
	 double curaverage_;//���ʻ���ƽ��ֵ
	 double erroraverage_;//������ƽ��ֵ

    vector<vector<int> >  horizon_index;//ˮƽ���Σ��洢˳���Ǵ����浽���棬��С���󣬴洢�ڲ��ͱ߽�ڵ����
    vector<vector<int> >  vertical_index;//��ֱ���Σ��洢˳���Ǵ����ң���С���󣬴洢�ڲ��ͱ߽�ڵ����
   // vector<int>   test;//���������ĵ���
   

	void set_max_error(double &err);//�������������Ϊÿ����ϵ���ɫ
    void  set_knots_iteration_times(int n);

	double &get_mean_error();
	Max_Error &get_max_error();
	double  get_max_knotcurerror();
    double  get_min_knotcurerror();

	Mesh *get_error_fitted_mesh();
	void update_polymesh();
	MyMesh get_polymesh();

signals:
	void mesh_changed();
//
private:

	Mesh *m_pOriginalMesh;
	int iter_times;
	int add_num;//ÿ��Ӧ�����ӵ���ֱ�ڵ����������û�ָ��
    int add_horizon_num;//ÿ��Ӧ�����ӵ�ˮƽ�ڵ����������û�ָ��
    B_parameter *parameter1;
	bool  error_compute_ok;
	CBSplineSurfaceView *bsurface;
	Mesh  *m_pFittedMesh;
	Mesh *m_pErrorMesh;
	MyMesh polymesh;

	QString fileName;

	vector<TexCoord> domain;
   

	Bbox_2 box;
	Bbox_3 originalbox;
	Bbox_3 fittingbox;
	Bbox_3 errorbox;

	int sample_num;

	double err_threshold;
    Max_Error max_err;//���޸ĵ�������
	double   max_err_real;//��ʵ��δ�޸ĵ�������
	double max_meancurvature;
	double min_meancurvature;
	double max_curerror;
	double min_curerror;
	double mean_err;//���������
	double mean_e;
     bool   Curvature_loading;
	 bool   fitting_completed_;
	 bool    curvature_error;
	void compute_box();

};