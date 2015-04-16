#pragma once
#include "meshviewer.h"
#include "surfacedata.h"
#include <QtGui/QMainWindow>
#include <QtCore/QString>
#include <QtCore/QStringList>


class QLabel;
class QAction;
class QMenu;

class MeshSubWindow: public QMainWindow
{
	Q_OBJECT
public:
	MeshSubWindow(void);
	~MeshSubWindow(void);
	MeshViewer *get_mesh_viewer();
	void setCurrentFile(const QString &fileName);
	QString &get_cur_file();
	QStringList &get_recent_files();
	void set_surface_data(CSurfaceData *data);
	//bool mesh_fitting();
	//void surface_fitting();
	bool mesh_parametrization();
	//void add_knots();
	//void surface_sampling(int index);
	void update_view();
	//void update_fitting_view();
	void clear_data();
	bool write_mesh(QString &fileName, Mesh_Type type);
  
signals:
	//void current_file_changed();
	void window_close();
	void surfacedata_changed(CSurfaceData *surfacedata);

protected:
	void closeEvent(QCloseEvent *event);

private:
	void createStatusBar();
	void createActions();
	void createMenus();
	void createContextMenus();
	/*int get_nseed();
	int get_degree();*/
	QString strippedName(const QString &fullFileName);
	MeshViewer *m_pMeshViewer;
	QLabel *filenameLabel;
	QLabel *pointsLabel;
	QLabel *faceLabel;
	QLabel *controlnumLabel;
	QLabel *controlindexLabel;
	QString curFile;
	QStringList recentFiles;
	CSurfaceData *surfacedata;

	QAction *originalmeshAction;
	//QAction *fittedmeshAction;
	QAction *controlmeshAction;
	QAction *controledgesAction;
	QAction *adjustedcontrolmeshAction;
	QAction *errorAction;
	QAction *max_error_pointAction;
	QAction *curvatureAction;
	QAction *sparseMeshAction;
	QAction *sparseCurvesAction;
	QAction *densityAction;
	QAction *adjustableAction;
	QAction *adjustmeshAction;
	QAction *featureCurvesAction;

	QMenu *viewMenu;
	QMenu *editMenu;

private slots:
		void set_origin_mesh_view(bool ov);
		//void emit_changed_surfacedata(CSurfaceData* data);
		//void set_fitted_mesh_view(bool fv);
		//void set_error_show(bool ev);
		  void set_curvature_show(bool cv);
		//void set_controlmesh_show(bool cm);
		void set_adjustpoints_enabled(bool av);
		void set_adjusted_enabled(bool av);
	/*	void set_adjusted_control_enabled(bool av);
		void set_density_show(bool dv);
		void set_max_error_point_show(bool mv);
		void set_controledges_show(bool cv);*/
		void updateStatusBar();
	/*	void set_sparsemesh_show(bool sv);
		void set_sparsecurves_show(bool sv);
		void set_featurecurves_enabled(bool fv);*/
};
