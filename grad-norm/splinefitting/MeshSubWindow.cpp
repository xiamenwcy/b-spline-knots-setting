#include "MeshSubWindow.h"
#include <QtGui/QtGui>

MeshSubWindow::MeshSubWindow(void)
{
	m_pMeshViewer = new MeshViewer;
	m_pMeshViewer->setAttribute(Qt::WA_OpaquePaintEvent);
	m_pMeshViewer->setAttribute(Qt::WA_NoSystemBackground);
	setCentralWidget(m_pMeshViewer);
	setWindowTitle("Mesh Viewer");

	surfacedata = NULL;
	createActions();
	createMenus();
	createContextMenus();
	createStatusBar();
	setCurrentFile("");

	connect(m_pMeshViewer, SIGNAL(position_changed()), this, SLOT(updateStatusBar()));
	//connect(m_pMeshViewer,SIGNAL(CSurfaceData_changed(CSurfaceData*)),this,SLOT(emit_changed_surfacedata(CSurfaceData*)));
}

MeshSubWindow::~MeshSubWindow(void)
{
	clear_data();
}
void MeshSubWindow::clear_data()
{
	originalmeshAction->setChecked(true);
	//fittedmeshAction->setChecked(false);
	errorAction->setChecked(false);
	adjustableAction->setChecked(false);
	adjustmeshAction->setChecked(false);
	curvatureAction->setChecked(false);
	controlmeshAction->setChecked(false);
	m_pMeshViewer->clear_data();
}

MeshViewer *MeshSubWindow::get_mesh_viewer()
{
	return m_pMeshViewer;
}

void MeshSubWindow::createActions()
{
	originalmeshAction = new QAction(tr("Original Mesh"), this);
	originalmeshAction->setCheckable(true);
	originalmeshAction->setChecked(true);
	connect(originalmeshAction, SIGNAL(toggled(bool)), this, SLOT(set_origin_mesh_view(bool)));
	/*fittedmeshAction = new QAction(tr("Fitted Mesh"), this);
	fittedmeshAction->setCheckable(true);
	connect(fittedmeshAction, SIGNAL(toggled(bool)), this, SLOT(set_fitted_mesh_view(bool)));*/
	errorAction = new QAction(tr("Error Mesh"), this);
	errorAction->setCheckable(true);
	//connect(errorAction, SIGNAL(toggled(bool)), this, SLOT(set_error_show(bool)));

	max_error_pointAction = new QAction(tr("Max Error Point"), this);
	max_error_pointAction->setCheckable(true);
	//connect(max_error_pointAction, SIGNAL(toggled(bool)), this, SLOT(set_max_error_point_show(bool)));

	curvatureAction = new QAction(tr("Curvature Mesh"), this);
	curvatureAction->setCheckable(true);
	connect(curvatureAction, SIGNAL(toggled(bool)), this, SLOT(set_curvature_show(bool)));

	sparseMeshAction = new QAction(tr("Sparse Mesh"), this);
	sparseMeshAction->setCheckable(true);
	//connect(sparseMeshAction, SIGNAL(toggled(bool)), this, SLOT(set_sparsemesh_show(bool)));

	sparseCurvesAction = new QAction(tr("Sparse Curves"), this);
	sparseCurvesAction->setCheckable(true);
	//connect(sparseCurvesAction, SIGNAL(toggled(bool)), this, SLOT(set_sparsecurves_show(bool)));


	densityAction = new QAction(tr("Density Mesh"), this);
	densityAction->setCheckable(true);
	//connect(densityAction, SIGNAL(toggled(bool)), this, SLOT(set_density_show(bool)));

	controlmeshAction = new QAction(tr("Control Mesh"), this);
	controlmeshAction->setCheckable(true);
//	connect(controlmeshAction, SIGNAL(toggled(bool)), this, SLOT(set_controlmesh_show(bool)));

	controledgesAction = new QAction(tr("Control Edges"), this);
	controledgesAction->setCheckable(true);
	//connect(controledgesAction, SIGNAL(toggled(bool)), this, SLOT(set_controledges_show(bool)));

	adjustableAction = new QAction(tr("Adjustable"), this);
	adjustableAction->setCheckable(true);
	connect(adjustableAction, SIGNAL(toggled(bool)), this, SLOT(set_adjustpoints_enabled(bool)));

	adjustmeshAction = new QAction(tr("Adjusted Mesh"), this);
	adjustmeshAction->setCheckable(true);
	connect(adjustmeshAction, SIGNAL(toggled(bool)), this, SLOT(set_adjusted_enabled(bool)));

	adjustedcontrolmeshAction = new QAction(tr("Adjusted Control Mesh"), this);
	adjustedcontrolmeshAction->setCheckable(true);
	//connect(adjustedcontrolmeshAction, SIGNAL(toggled(bool)), this, SLOT(set_adjusted_control_enabled(bool)));

	featureCurvesAction = new QAction(tr("Feature Curves"), this);
	featureCurvesAction->setCheckable(true);
	//connect(featureCurvesAction, SIGNAL(toggled(bool)), this, SLOT(set_featurecurves_enabled(bool)));
}

void MeshSubWindow::createMenus()
{
	viewMenu = menuBar()->addMenu(tr("&View"));
	viewMenu->addAction(originalmeshAction);
	viewMenu->addAction(curvatureAction);
	viewMenu->addAction(sparseCurvesAction);
	viewMenu->addAction(sparseMeshAction);
	viewMenu->addAction(sparseCurvesAction);
	viewMenu->addAction(densityAction);
	//viewMenu->addAction(fittedmeshAction);
	viewMenu->addAction(errorAction);
	viewMenu->addAction(max_error_pointAction);
	viewMenu->addAction(controledgesAction);
	viewMenu->addAction(controlmeshAction);
	viewMenu->addAction(adjustedcontrolmeshAction);
	viewMenu->addAction(adjustmeshAction);
	editMenu = menuBar()->addMenu(tr("&Option"));
	editMenu->addAction(adjustableAction);
}

void MeshSubWindow::createContextMenus()
{
	m_pMeshViewer->addAction(originalmeshAction);
	m_pMeshViewer->addAction(curvatureAction);
	m_pMeshViewer->addAction(sparseMeshAction);
	m_pMeshViewer->addAction(sparseCurvesAction);
	m_pMeshViewer->addAction(densityAction);
	//m_pMeshViewer->addAction(fittedmeshAction);
	m_pMeshViewer->addAction(errorAction);
	m_pMeshViewer->addAction(max_error_pointAction);
	m_pMeshViewer->addAction(controledgesAction);
	m_pMeshViewer->addAction(controlmeshAction);
	m_pMeshViewer->addAction(adjustedcontrolmeshAction);
	m_pMeshViewer->addAction(adjustmeshAction);
	m_pMeshViewer->setContextMenuPolicy(Qt::ActionsContextMenu);
}

void MeshSubWindow::createStatusBar()
{
	filenameLabel = new QLabel;
	pointsLabel = new QLabel;
	faceLabel = new QLabel;
	controlnumLabel = new QLabel;
	controlindexLabel = new QLabel;

	statusBar()->addWidget(filenameLabel, 1);
	statusBar()->addWidget(pointsLabel, 1);
	statusBar()->addWidget(faceLabel, 1);
	statusBar()->addWidget(controlnumLabel, 1);
	statusBar()->addWidget(controlindexLabel, 1);
	updateStatusBar();
}

QString &MeshSubWindow::get_cur_file()
{
	return curFile;
}

void MeshSubWindow::setCurrentFile(const QString &fileName)
{
	curFile = fileName;
	setWindowModified(false);

	QString shownName = tr("Untitled");
	if (!curFile.isEmpty()) 
	{
		shownName = strippedName(curFile);
		recentFiles.removeAll(curFile);
		recentFiles.prepend(curFile);
		//emit current_file_changed();
	}

	setWindowTitle(tr("%1[*] - %2").arg(shownName)
		.arg(tr("Simplex Spline")));
	updateStatusBar();
}

QStringList &MeshSubWindow::get_recent_files()
{
	return recentFiles;
}

QString MeshSubWindow::strippedName(const QString &fullFileName)
{
	return QFileInfo(fullFileName).fileName();
}

void MeshSubWindow::updateStatusBar()
{
	/*if(surfacedata!=NULL)
	{
		QString points = "Point: ";
		int pointNum = surfacedata->get_mesh_vertex_num();
		if(pointNum == -1)
		{
			points = "";
		}
		else
		{
			points.append(QString::number(pointNum, 10));
		}
		QString faces = "Face: ";
		int faceNum = surfacedata->get_mesh_face_num();
		if(faceNum == -1)
		{
			faces = "";
		}
		else
		{
			faces.append(QString::number(faceNum, 10));
		}
		QString fileName = "Mesh: ";
		QString meshName = surfacedata->get_mesh_name();
		if(meshName.isEmpty())
		{
			fileName = "";
		}
		else
		{
			fileName = fileName.append(meshName);
		}
		filenameLabel->setText(fileName);
		pointsLabel->setText(points);
		faceLabel->setText(faces);
		QString controlstr = "Num of C.V.: ";
		int controlNum = surfacedata->get_basis_size();
		if(controlNum ==0)
		{
			controlstr = "";
		}
		else
		{
			controlstr.append(QString::number(controlNum, 10));
		}
		controlnumLabel->setText(controlstr);
		QString indexstr = "C.V. ";
		int index = m_pMeshViewer->get_index();
		if(index ==-1)
		{
			indexstr = "Pos:(";
		}
		else
		{
			indexstr.append(QString::number(index, 10));
			indexstr.append(": (");
		}
		Point_3 pos = m_pMeshViewer->get_postion();
		indexstr.append(QString::number(pos.x(), 'g', 3));
		indexstr.append(", ");
		indexstr.append(QString::number(pos.y(), 'g', 3));
		indexstr.append(", ");
		indexstr.append(QString::number(pos.z(), 'g', 3));
		indexstr.append(")");
		controlindexLabel->setText(indexstr);
	}*/
}

void MeshSubWindow::closeEvent(QCloseEvent *event)
{
	event->accept();
	emit window_close();
}

void MeshSubWindow::set_surface_data(CSurfaceData *data)
{
	surfacedata = data;
	updateStatusBar();
	m_pMeshViewer->set_surface_data(data);
}
void MeshSubWindow::update_view()
{
	updateStatusBar();
	m_pMeshViewer->update_view();
}
//void MeshSubWindow::update_fitting_view()
//{
//	updateStatusBar();
//	m_pMeshViewer->update_fitting_view();
//}
//void MeshSubWindow::surface_sampling(int index)
//{
//	int nRow;
//	int nCol;
//	RowColumnDialog rowcolumn;
//	if(rowcolumn.exec() == QDialog::Accepted)
//	{
//		nRow = rowcolumn.rowspin->value();
//		nCol = rowcolumn.columnspin->value();
//		nRow += 1;
//		nCol += 1;
//		surfacedata->set_row_col(nRow, nCol);
//		surfacedata->surface_sampling(index);
//	}
//}

//bool MeshSubWindow::mesh_fitting()
//{
//	return surfacedata->mesh_fitting();
//}

//void MeshSubWindow::surface_fitting()
//{
//	surfacedata->surface_fitting();
//}
//
bool MeshSubWindow::mesh_parametrization()
{
	return surfacedata->mesh_parameterization();
}

//void MeshSubWindow::add_knots()
//{
//	int nseed = get_nseed();
//	if(nseed==0)
//	{
//		return;
//	}
//
//	int iter_num = surfacedata->get_iterator_num();
//	if(iter_num==0)
//	{
//		surfacedata->set_nseed(nseed);
//
//		int degree = get_degree();
//		if(degree == -1)
//		{
//			return;
//		}
//		surfacedata->set_degree(degree);
//		//surfacedata->knots_generation();
//	}
//	else
//	{
//		surfacedata->add_knots(nseed);
//	}
//
//}
//
//int MeshSubWindow::get_nseed()
//{
//	bool ok = false;
//	int num = surfacedata->get_mesh_vertex_num();
//	if(num<40000)
//		num = 40;
//	else
//		num = (surfacedata->get_mesh_vertex_num()/10000+1)*10;
//	int nseed = 
//		QInputDialog::getInteger(this, 
//		tr("Number of seeds"),
//		tr("What is the number of seeds you want to add?"),
//		num,
//		1,
//		surfacedata->get_mesh_vertex_num(),
//		10,
//		&ok);
//	if(ok)
//		return nseed;
//	else
//		return 0;
//}
//
//int MeshSubWindow::get_degree()
//{
//	bool ok = false;
//	int degree = 
//		QInputDialog::getInteger(this, 
//		tr("Degree"),
//		tr("Degree of triangulation configurations that wants to elevate:"),
//		4,
//		0,
//		10,
//		1,
//		&ok);
//	if(ok)
//		return degree;
//	else
//		return -1;
//}

void MeshSubWindow::set_origin_mesh_view(bool ov)
{
	m_pMeshViewer->set_origin_mesh_view(ov);
}

//void MeshSubWindow::set_fitted_mesh_view(bool fv)
//{
//	m_pMeshViewer->set_fitted_mesh_view(fv);
//}

//void MeshSubWindow::set_error_show(bool ev)
//{
//	m_pMeshViewer->set_error_show(ev);
//}
//
void MeshSubWindow::set_curvature_show(bool cv)
{
	if (cv)
	{
		if (!surfacedata->curvature_loading())
		{
			QMessageBox::critical(this,tr("Curvature Loading Error:"),tr("Curvature has not been loadded yet,please loading curvature."),QMessageBox::Ok);
			return;
		}
		
	}
	m_pMeshViewer->set_curvature_show(cv);

}
//void MeshSubWindow::emit_changed_surfacedata(CSurfaceData* data)
//{
//	emit surfacedata_changed(data);
//}
//void MeshSubWindow::set_sparsemesh_show(bool sv)
//{
//	m_pMeshViewer->set_sparsemesh_view(sv);
//}
//
//void MeshSubWindow::set_sparsecurves_show(bool sv)
//{
//	m_pMeshViewer->set_sparsecurves_view(sv);
//}
//
//void MeshSubWindow::set_density_show(bool dv)
//{
//	m_pMeshViewer->set_density_show(dv);
//}
//
//void MeshSubWindow::set_controlmesh_show(bool cm)
//{
//	m_pMeshViewer->set_controlmesh_show(cm);
//}
//
void MeshSubWindow::set_adjusted_enabled(bool av)
{
	m_pMeshViewer->set_adjustedmesh_enabled(av);
}

void MeshSubWindow::set_adjustpoints_enabled(bool av)
{
	m_pMeshViewer->set_adjustpoints_enabled(av);
}

//void MeshSubWindow::set_adjusted_control_enabled(bool av)
//{
//	m_pMeshViewer->set_adjusted_control_enabled(av);
//}
//
bool MeshSubWindow::write_mesh(QString &fileName, Mesh_Type type)
{
	return m_pMeshViewer->write_mesh(fileName, type);
}

//void MeshSubWindow::set_max_error_point_show(bool mv)
//{
//	m_pMeshViewer->set_max_error_point_show(mv);
//}
//
//void MeshSubWindow::set_controledges_show(bool cv)
//{
//	m_pMeshViewer->set_controledge_show(cv);
//}
//
//void MeshSubWindow::set_featurecurves_enabled(bool fv)
//{
//	m_pMeshViewer->set_featureline_view(fv);
//}