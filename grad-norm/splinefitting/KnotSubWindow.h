#pragma once
#include "splineknotsviewer.h"
#include <QMainWindow>
#include <QtCore/QString>
#include <QtCore/QStringList>

class QAction;
class QLabel;


class KnotSubWindow: public QMainWindow
{
	Q_OBJECT
public:
	KnotSubWindow(void);
	~KnotSubWindow(void);
	void clear_data();
	void update_view();
    void set_surface_data(CSurfaceData *data);
signals:
	void window_close();
	//protected:
//	void closeEvent(QCloseEvent *event);
private:
	CSurfaceData *surfacedata;
	SplineKnotsViewer *knotsViewer;
	B_parameter *parameter;
	QAction *indexAction;
	QAction *knotsAction;
	QAction *curvatureAction;
	QAction *domainAction;
	QAction *domainmeshAction;
	QAction *errdomainAction;
	QAction *densitydomainAction;
	QAction *centroidAction;
	QAction *basisAction;
	QAction *basissumAction;
	QAction *interiorAction;
	QAction *delaunayAction;
	QAction *ddtAction;
	QAction *principaldirectionAction;
	QAction *segmentAction;
	QAction *thinAction;
	QAction *angleAction;
	QAction *openAction;
	QAction *saveAsAction;
	QAction *triangluationTestAction;
	QAction *basissupportAction;
	QAction *triangulationAction;
	QMenu *fileMenu;
	QMenu *viewMenu;
	QMenu *verificationMenu;
	QLabel *statusLabel;
	int basisIndex;
	void createActions();
	void createMenus();
	void createContextMenu();
	void createStatusBar();
	void updateStatusBar();

public slots:
		void knots_view(bool kv);
		void set_curvature_show(bool cv);
	/*	void centroid_view(bool cv);
		void basis_view(bool bv);
		void basis_sum_view(bool sv);
		void domain_view(bool dv);
		void basis_index();
		void interior_knots_view(bool iv);
		void open();
		bool saveAs();
		void show_basis_support(bool bv);
		void show_triangulation_view(bool tv);
		void show_delaunay_view(bool dv);
		void show_ddt_view(bool dv);
		void show_error_triangles(bool fv);
		void set_thintriangles_view(bool tv);
		void set_angletriangles_view(bool av);*/
		void set_mesh_view(bool dv);
		void error_domain_view(bool ev);
		void error_fitting_view(bool ev);
		/*void density_domain_view(bool dv);
		void set_principal_direction_view(bool pv);*/
};
