#pragma once
#include "SurfaceData.h"
#include <QGLViewer/qglviewer.h>
#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>
#include <QGLViewer/vec.h>
#include <QtGui/QPaintEvent>
#include <QtGui/QVector3D>
#include <CGAL/Bbox_2.h>


using namespace qglviewer;


//typedef OpenMesh::TriMesh_ArrayKernelT<>  Mesh;

class MeshViewer:
	public QGLViewer
{
	Q_OBJECT        //只有定义了这个才能使用信号-槽机制
public:
	MeshViewer();
	~MeshViewer(void);
	void set_surface_data(CSurfaceData *data);
	void update_view();
	//void update_fitting_view();
	void clear_data();
	void set_origin_mesh_view(bool ov);
	//void set_fitted_mesh_view(bool fv);
	//void set_error_show(bool ev);
	void set_curvature_show(bool cv);
	//void set_density_show(bool dv);
	//void set_controlmesh_show(bool cm);
	//void set_controledge_show(bool cv);
	void set_adjustpoints_enabled(bool av);
	void set_adjustedmesh_enabled(bool av);
	bool write_mesh(QString &fileName, Mesh_Type type);
	/*void set_adjusted_control_enabled(bool av);
	void set_max_error_point_show(bool mv);
	int &get_index();
	Point_3 &get_postion();
	void set_sparsemesh_view(bool sv);
	void set_sparsecurves_view(bool sv);
	void set_featureline_view(bool fv);*/
signals:
	void position_changed();
protected:
	virtual void draw();
	virtual void init();
	virtual void paintGL() { update(); };
    virtual void paintEvent(QPaintEvent *event);
	void draw_curvature_colorbar(QPainter *painter);
	/*void draw_error_colorbar(QPainter *painter);
	void draw_density_colorbar(QPainter *painter);
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);*/

private:
	void setDefaultMaterial();
	void draw_original_mesh();
	//void draw_fitted_mesh();
	//void draw_density_mesh();
	//void draw_error_mesh();
	void draw_curvature_mesh();
	/*void draw_control_mesh();
	void draw_control_mesh_orginal();
	void draw_adjusted_control_mesh();
	void draw_adjusted_mesh();*/
	void set_scene(Bbox_3 &box);
	/*void colormap(int* color, double x, double min, double max);
	int check_selected(Point_3 &pt, double dist);
	void draw_max_error_point();
	void draw_sparsemesh();
	void draw_sparsecurves();
	void draw_featurelines();*/

	CSurfaceData *surfacedata;
	//double *error;
	//double max_err;
	//int *dens_ind;
	//int *err_ind;
	bool borigina_mesh_view;
//	bool bfitted_mesh_view;
	//bool bdensityshow;
	//bool berror_show;
	bool bcurvature_show;
	//bool bcontrolmesh_show;
	//bool bcontroledge_show;
	//bool bmax_error_point_show;
	  bool badjustedmesh_show;
	  bool badjust;
	//bool badjusted_control_mesh;
	//Point_3 pos;

	//int index;
	//GLfloat winZ;//Depth

	//int basis_size;
	double radius;
	/*bool bsparsemeshview;
	bool bsparsecurvesview;
	bool bfeaturelineview;*/
	Bbox_3 bBox;













};
