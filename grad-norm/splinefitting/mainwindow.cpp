#include <OpenMesh/Core/IO/MeshIO.hh>//必须放在首行
#include "mainwindow.h"
#include <QtGui/QtGui>
#include <QtGui/QInputDialog>
mainwindow::mainwindow(void)
{
	mdi=new QMdiArea(this);
	setCentralWidget(mdi);

	meshwindow = new MeshSubWindow();
	meshwindow->setAttribute(Qt::WA_DeleteOnClose);
	mesh = mdi->addSubWindow(meshwindow);
	meshwindow->setWindowTitle("Mesh Window");
	

	knotswindow = new KnotSubWindow();
	knotswindow->setAttribute(Qt::WA_DeleteOnClose);
	knots = mdi->addSubWindow(knotswindow);
    knotswindow->setWindowTitle("Knot Window");


	fitwindow=new FitSubWindow();
	fitwindow->setAttribute(Qt::WA_DeleteOnClose);
	fitting=mdi->addSubWindow(fitwindow);
	fitwindow->setWindowTitle("Fitting Window");
   


	QStatusBar *statusBar = this->statusBar();//创建状态栏
    is_ever_open=false;
	//mesh->showMaximized();

	surfacedata = new CSurfaceData();//可以加(),也可以不加
	meshwindow->set_surface_data(surfacedata);
	knotswindow->set_surface_data(surfacedata);
	fitwindow->set_surface_data(surfacedata);

	createActions();
	createMenus();
	createToolBars();

	//connect(meshwindow, SIGNAL(current_file_changed()), this, SLOT(updateRecentFileActions()));
	connect(meshwindow, SIGNAL(window_close()), this, SLOT(meshwindow_close()));
	connect(knotswindow, SIGNAL(window_close()), this, SLOT(knotswindow_close()));
    connect(fitwindow, SIGNAL(window_close()), this, SLOT(fitwindow_close()));
	setWindowTitle("B_Spline Fitting");
}

mainwindow::~mainwindow(void)
{
	
}
void mainwindow::createActions()
{
	
	newAction = new QAction(QIcon(":/splinefitting/images/new.png"), tr("&New"), this);
	newAction->setShortcut(tr("Ctrl+N"));
	newAction->setStatusTip(tr("Create a new file"));
    connect(newAction, SIGNAL(triggered()), this, SLOT(newFile()));

	openAction = new QAction(QIcon(":/splinefitting/images/open.png"),tr("&Open..."), this);
    openAction->setShortcut(QKeySequence::Open);
    openAction->setStatusTip(tr("Open an existing mesh file"));
    connect(openAction, SIGNAL(triggered()), this, SLOT(open()));

    saveAction = new QAction(QIcon(":/splinefitting/images/save.png"),tr("&Save"), this);
    saveAction->setShortcut(QKeySequence::Save);
    saveAction->setStatusTip(tr("Save the mesh to disk"));
   //connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));

    saveCurvatureAction = new QAction(tr("Save &Curvature Mesh..."), this);
    saveCurvatureAction->setStatusTip(tr("Save the mesh under a new "
                                  "name"));
    connect(saveCurvatureAction, SIGNAL(triggered()), this, SLOT(saveAs()));

	saveFitAction = new QAction(tr("Save &Fitted Mesh..."), this);
    saveFitAction->setStatusTip(tr("Save the mesh under a new "
                                  "name"));
    connect(saveFitAction, SIGNAL(triggered()), this, SLOT(saveAs()));

	saveErrorAction = new QAction(tr("Save &Error Mesh..."), this);
    saveErrorAction->setStatusTip(tr("Save the mesh under a new "
                                  "name"));
    connect(saveErrorAction, SIGNAL(triggered()), this, SLOT(saveAs()));

	saveDensityAction = new QAction(tr("Save &Density Mesh..."), this);
    saveDensityAction->setStatusTip(tr("Save the mesh under a new "
                                  "name"));
   // connect(saveDensityAction, SIGNAL(triggered()), this, SLOT(saveAs()));

	saveCEAction = new QAction(tr("Save &Control Edges..."), this);
    saveCEAction->setStatusTip(tr("Save the mesh under a new "
                                  "name"));
   // connect(saveCEAction, SIGNAL(triggered()), this, SLOT(saveAs()));

	saveCMAction = new QAction(tr("Save &Control Mesh..."), this);
    saveCMAction->setStatusTip(tr("Save the mesh under a new "
                                  "name"));
    //connect(saveCMAction, SIGNAL(triggered()), this, SLOT(saveAs()));

	saveparaAction = new QAction(tr("Save Mesh with Parametrization..."), this);
	//connect(saveparaAction, SIGNAL(triggered()), this, SLOT(savePara()));

	saveGCAction =  new QAction(tr("Save Global Costs"), this);
	//connect(saveGCAction, SIGNAL(triggered()), this, SLOT(save_global_costs()));

	saveKnotsAction =  new QAction(tr("Save Knots"), this);
	//connect(saveKnotsAction, SIGNAL(triggered()), this, SLOT(save_knots()));

    for (int i = 0; i < MaxRecentFiles; ++i) {
        recentFileActions[i] = new QAction(this);
        recentFileActions[i]->setVisible(false);
      //  connect(recentFileActions[i], SIGNAL(triggered()),
         //       this, SLOT(openRecentFile()));
    }

    exitAction = new QAction(QIcon(":/splinefitting/images/exit.png"),tr("E&xit"), this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    exitAction->setStatusTip(tr("Exit the application"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

	aboutAction = new QAction(tr("&About"), this);
    aboutAction->setStatusTip(tr("Show the application's About box"));
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));

    aboutQtAction = new QAction(tr("About &Qt"), this);
    aboutQtAction->setStatusTip(tr("Show the Qt library's About box"));
    connect(aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

	samplingAction_1 = new QAction(tr("Surface 1"), this);
	//connect(samplingAction_1, SIGNAL(triggered()), this, SLOT(surface_sampling()));
	samplingAction_2 = new QAction(tr("Surface 2"), this);
	//connect(samplingAction_2, SIGNAL(triggered()), this, SLOT(surface_sampling()));
	samplingAction_3 = new QAction(tr("Surface 3"), this);
	//connect(samplingAction_3, SIGNAL(triggered()), this, SLOT(surface_sampling()));

	surfacefittingAction = new QAction(tr("Surface Fitting"), this);
	//connect(surfacefittingAction, SIGNAL(triggered()), this, SLOT(surface_fitting()));
	knotsAction = new QAction(tr("Add Knots"), this);
	//connect(knotsAction, SIGNAL(triggered()), this, SLOT(add_knots()));
	parametrizationAction = new QAction(tr("Mesh Parametrization"), this);
	parametrizationAction->setCheckable(true);
	connect(parametrizationAction, SIGNAL(triggered()), this, SLOT(mesh_parametrization()));
	meshfittingAction = new QAction(tr("Mesh Fitting"), this);
	connect(meshfittingAction, SIGNAL(triggered()), this, SLOT(mesh_fitting()));

     //***********************　　　　附加功能　　　　　　　　　**************/

	//meshAddKnotsAction = new QAction(tr("Add knots"), this);
	//connect(meshAddKnotsAction, SIGNAL(triggered()), this, SLOT(add_knots()));

	//retriangulationAction = new QAction(tr("Knots Retriangulation"), this);
	//connect(retriangulationAction, SIGNAL(triggered()), this, SLOT(knots_retriangulation()));

	//meshRefittingAction = new QAction(tr("Mesh Refitting"), this);
	//connect(meshRefittingAction, SIGNAL(triggered()), this, SLOT(mesh_refitting()));

	//******************************　　　　*********************************************//



	mean_errorAction =  new QAction(tr("DDT-Mean Error Minimization"), this);
	mean_errorAction->setCheckable(true);
	//connect(mean_errorAction, SIGNAL(triggered()), this, SLOT(set_triangulation_type()));

	sco_Action = new QAction(tr("DDT-SCO Minimization"), this);
	sco_Action->setCheckable(true);
	//connect(sco_Action, SIGNAL(triggered()), this, SLOT(set_triangulation_type()));

	variance_ddtAction = new QAction(tr("DDT-Deviation Minimization"), this);
	variance_ddtAction->setCheckable(true);
	variance_ddtAction->setStatusTip(tr("Data Dependent Triangulation"));
	//connect(variance_ddtAction, SIGNAL(triggered()), this, SLOT(set_triangulation_type()));

	delaunayAction = new QAction(tr("Delaunay"), this);
	delaunayAction->setCheckable(true);
	delaunayAction->setStatusTip(tr("Delaunay Triangulation"));
	//connect(delaunayAction, SIGNAL(triggered()), this, SLOT(set_triangulation_type()));

	local_ddtAction = new QAction(tr("Local DDT"), this);
	local_ddtAction->setCheckable(true);
	//connect(local_ddtAction, SIGNAL(toggled(bool)), this, SLOT(set_triangulation_type(bool)));
	local_ddtAction->setChecked(false);


	CurvatureUpperboundAction=new QAction(tr("Adjust Curvature Upper Bound"),this);
	CurvatureUpperboundAction->setCheckable(true);
	connect(CurvatureUpperboundAction, SIGNAL(triggered()), this, SLOT(adjust_upper()));

	outputAction = new QAction(tr("Add vertical knots"), this);
	outputAction->setCheckable(true);
	connect(outputAction, SIGNAL(triggered()), this, SLOT(add_knots()));

	addAction = new QAction(tr("Add horizon knots"), this);
	addAction->setCheckable(true);
	connect(addAction, SIGNAL(triggered()), this, SLOT(add_horizon_knots()));

	CurvatureLoadingAction=new QAction(tr("Loading Curvature"),this);
	CurvatureLoadingAction->setCheckable(true);
	connect(CurvatureLoadingAction, SIGNAL(triggered()), this, SLOT(load_curvature()));


	ParaInputAction=new QAction(tr("Parameters Input"),this);
	ParaInputAction->setCheckable(true);
	connect(ParaInputAction, SIGNAL(triggered()), this, SLOT(input_parameter()));

	KnotIterationAction=new QAction(tr("Adjust  knots  by curvature"),this);
	KnotIterationAction->setCheckable(true);
	connect(KnotIterationAction, SIGNAL(triggered()), this, SLOT(adjust_knots()));
    
    KnotAdjustAction=new QAction(tr("Adjust knots by fitting_error"),this);
    KnotAdjustAction->setCheckable(true);
	connect(KnotAdjustAction,SIGNAL(triggered()),this,SLOT(adjust_knots_by_fitting_error()));
    

	meshAction = new QAction(tr("Mesh Window"), this);
	meshAction->setCheckable(true);
	meshAction->setStatusTip(tr("Show or hide the mesh window's"));
	connect(meshAction, SIGNAL(toggled(bool)), this, SLOT(set_window_visible(bool)));

	pointsAction = new QAction(tr("Knots Window"), this);
	pointsAction->setCheckable(true);
	pointsAction->setStatusTip(tr("Show or hide the knots window's"));
	connect(pointsAction, SIGNAL(toggled(bool)), this, SLOT(set_window_visible(bool)));

	fittingAction = new QAction(tr("fitting Window"), this);
	fittingAction->setCheckable(true);
	fittingAction->setStatusTip(tr("Show or hide the fitting window's"));
	connect(fittingAction, SIGNAL(toggled(bool)), this, SLOT(set_window_visible(bool)));

	windowActionGroup = new QActionGroup(this);
	windowActionGroup->addAction(meshAction);
	windowActionGroup->addAction(pointsAction);
	windowActionGroup->addAction(fittingAction);
	meshAction->setChecked(true);

	triangulationActionGroup  = new QActionGroup(this);
	triangulationActionGroup->addAction(delaunayAction);
	triangulationActionGroup->addAction(mean_errorAction);
	triangulationActionGroup->addAction(sco_Action);
	triangulationActionGroup->addAction(variance_ddtAction);
	mean_errorAction->setChecked(true);


	onestepAction = new QAction(tr("One Step"), this);
	onestepAction->setCheckable(true);
	//connect(onestepAction, SIGNAL(triggered()), this, SLOT(set_sa_type()));

	saAction = new QAction(tr("Simulated Annealing"), this);
	saAction->setCheckable(true);
	//connect(saAction, SIGNAL(triggered()), this, SLOT(set_sa_type()));

	lopAction = new QAction(tr("Local Optimization"), this);
	lopAction->setCheckable(true);
	//connect(lopAction, SIGNAL(triggered()), this, SLOT(set_sa_type()));

	combinationAction =new QAction(tr("Combination(LOP+SA)"), this);
	combinationAction->setCheckable(true);
	//connect(combinationAction, SIGNAL(triggered()), this, SLOT(set_sa_type()));

	saActionGroup = new QActionGroup(this);
	saActionGroup->addAction(lopAction);
	saActionGroup->addAction(onestepAction);
	saActionGroup->addAction(saAction);
	saActionGroup->addAction(combinationAction);
	//combinationAction->setChecked(true);
	lopAction->setChecked(true);
}

void mainwindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAction);
    fileMenu->addAction(openAction);
	fileMenu->addAction(saveAction);
	saveMenu = fileMenu->addMenu(QIcon(":/splinefitting/images/saveAs.png"),tr("Save As"));
	saveMenu->addAction(saveCurvatureAction);
	saveMenu->addAction(saveDensityAction);
	saveMenu->addAction(saveFitAction);
	saveMenu->addAction(saveErrorAction);
	saveMenu->addAction(saveCEAction);
	saveMenu->addAction(saveCMAction);
	saveMenu->addAction(saveparaAction);
	saveMenu->addAction(saveGCAction);
	saveMenu->addAction(saveKnotsAction);
	separatorAction = fileMenu->addSeparator();
	for (int i = 0; i < MaxRecentFiles; ++i)
		fileMenu->addAction(recentFileActions[i]);
	fileMenu->addSeparator();
	fileMenu->addAction(exitAction);
   

    samplingMenu = menuBar()->addMenu(tr("&Sampling"));
    samplingMenu->addAction(samplingAction_1);
    samplingMenu->addAction(samplingAction_2);
    samplingMenu->addAction(samplingAction_3);

    fittingMenu = menuBar()->addMenu(tr("&Fitting"));
	surfaceMenu = fittingMenu->addMenu(tr("&Surface"));
	surfaceMenu->addAction(knotsAction);
	surfaceMenu->addAction(surfacefittingAction);
	meshMenu = fittingMenu->addMenu(tr("&Mesh"));
    meshMenu->addAction(parametrizationAction);
	meshMenu->addAction(knotsAction);
    meshMenu->addAction(meshfittingAction);
	//meshMenu->addAction(meshAddKnotsAction);
	//meshMenu->addAction(retriangulationAction);
	//meshMenu->addAction(meshRefittingAction);
	fittingMenu->setDisabled(true);//设置菜单灰色，不可用

	/*testMenu  = menuBar()->addMenu(tr("&Test"));
	testMenu->addAction(testAction);*/

	optionsMenu = menuBar()->addMenu(tr("&Options"));

	optionsMenu->addSeparator();
	triangulationMenu = optionsMenu->addMenu(tr("Triangulation type"));
	triangulationMenu->addAction(delaunayAction);
	triangulationMenu->addAction(mean_errorAction);
	triangulationMenu->addAction(sco_Action);
	triangulationMenu->addAction(variance_ddtAction);
	optionsMenu->addSeparator();
	saMenu = optionsMenu->addMenu(tr("Optimization"));
	saMenu->addAction(lopAction);
	saMenu->addAction(onestepAction);
	saMenu->addAction(saAction);
	saMenu->addAction(combinationAction);
	optionsMenu->addSeparator();
	optionsMenu->addAction(local_ddtAction);
	optionsMenu->addSeparator();
	optionsMenu->addAction(CurvatureUpperboundAction);
	optionsMenu->addSeparator();
	optionsMenu->addAction(CurvatureLoadingAction);
	optionsMenu->addAction(ParaInputAction);
	optionsMenu->addAction(KnotIterationAction);
	optionsMenu->addAction(outputAction);
	optionsMenu->addAction(addAction);
	optionsMenu->addAction(KnotAdjustAction);
	/*optionsMenu->addAction(genericAction);*/

	windowMenu = menuBar()->addMenu(tr("&Windows"));
	windowMenu->addAction(pointsAction);
	windowMenu->addAction(meshAction);
	windowMenu->addAction(fittingAction);

    menuBar()->addSeparator();

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAction);
    helpMenu->addAction(aboutQtAction);
}
void mainwindow::createToolBars()
{
	//fileToolBar = addToolBar(tr("File"));
	//fileToolBar->setObjectName("fileToolBar");
	//fileToolBar->addAction(openAction);
	
	

    


}
 void mainwindow::newFile()
{
	//surfacedata->clear_data();
	//knotswindow->clear_data();
	//meshwindow->clear_data();
	//meshwindow->setCurrentFile("");
	surfaceMenu->setEnabled(true);
	meshMenu->setEnabled(true);
	openAction->setEnabled(true);
	samplingMenu->setEnabled(true);
	fittingMenu->setDisabled(true);
	knotsAction->setEnabled(true);
	surfacefittingAction->setEnabled(true);
	parametrizationAction->setEnabled(true);
	CurvatureUpperboundAction->setEnabled(true);
	CurvatureLoadingAction->setEnabled(true);
	ParaInputAction->setEnabled(true);
	KnotIterationAction->setEnabled(true);
	KnotAdjustAction->setEnabled(true);
	meshfittingAction->setEnabled(true);
	samplingAction_1->setEnabled(true);
	samplingAction_2->setEnabled(true);
	samplingAction_3->setEnabled(true);
}

void mainwindow::open()
{
	if(meshwindow == NULL)
	{
		meshwindow = new MeshSubWindow;
		meshwindow->setAttribute(Qt::WA_DeleteOnClose);
		mesh = mdi->addSubWindow(meshwindow);
		meshwindow->showMaximized();
	}
    if(is_ever_open)
	{
		meshwindow->clear_data();
		knotswindow->clear_data();
		fitwindow->clear_data();
		//delete surfacedata ;
		surfacedata = new CSurfaceData();
		surfacedata->iter_num=1;
		meshwindow->set_surface_data(surfacedata);
		knotswindow->set_surface_data(surfacedata);
		fitwindow->set_surface_data(surfacedata);

	}
	QString fileName = QFileDialog::getOpenFileName(this, 
		tr("Select File..."), "./splinefitting/model", tr("Model Files(*.off *.obj *.stl)"));
	if(!fileName.isEmpty())
	{
		if (!surfacedata->read_mesh(fileName))
		{
			statusBar()->showMessage(tr("Loading mesh unsuccessfully"), 2000);
			return;
		}
		statusBar()->showMessage(tr("Loading mesh successfully"), 2000);
		//meshwindow->setCurrentFile(fileName);
		meshwindow->update_view();
		fittingMenu->setEnabled(true);
		samplingMenu->setDisabled(true);
		surfaceMenu->setDisabled(true);
		knotsAction->setDisabled(true);
		meshfittingAction->setDisabled(true);
		meshwindow->showMaximized();
		is_ever_open=true;
	}
	return;
}

//bool mainwindow::save()
//{
//	QString curFile = meshwindow->get_cur_file();
//    if (curFile.isEmpty()) 
//	{
//        return saveAs();
//    } 
//	else 
//	{
//        return surfacedata->write_mesh(curFile);
//    }
//}

void mainwindow::saveAs()
{
	bool ret;
    QString fileName = QFileDialog::getSaveFileName(this,
                               tr("Save Mesh"), ".",
                               tr("Mesh files (*.off *.obj)"));
    if (fileName.isEmpty())
	{
		ret=false;
		return ;
	}
	
	QObject *send = sender();
	if(send==saveCurvatureAction)
		ret =  meshwindow->write_mesh(fileName, Curvature_Mesh);
	/*if(send==saveDensityAction)
		ret =  meshwindow->write_mesh(fileName, Density_Mesh);*/
	if(send==saveFitAction)
		ret =  fitwindow->write_mesh(fileName, Fitted_Mesh);
	if(send==saveErrorAction)
		ret =  fitwindow->write_mesh(fileName, Error_Mesh);
	/*if(send==saveCEAction)
		ret =  meshwindow->write_mesh(fileName, Control_Edges);
	if(send==saveCMAction)
		ret =  meshwindow->write_mesh(fileName, Control_Mesh);*/
    if (ret==true)
		statusBar()->showMessage(tr("Writing mesh successfully"), 2000);
	else
		statusBar()->showMessage(tr("Writing mesh Unsuccessfully"), 2000);

	
}
void mainwindow::about()
{
	QMessageBox::about(this, tr("About B-spline fitting"),
		tr("The <b>B-spline</b> example demonstrates how to "
		"use B-splie to fitting we-known mesh, "
		"It's very easy,but so perfect! "));
}
//bool mainwindow::savePara()
//{
//	 QString fileName = QFileDialog::getSaveFileName(this,
//                               tr("Save Mesh"), ".",
//                               tr("Mesh files (*.obj)"));
//	  if (fileName.isEmpty())
//        return false;
//	  return surfacedata->write_para(fileName);
//}
//
//void mainwindow::save_knots()
//{
//	QString fileName = QFileDialog::getSaveFileName(this,
//                               tr("Save Knots"), "./Knots",
//                               tr("Mesh files (*.txt)"));
//	surfacedata->write_knots(fileName);
//}
//
//void mainwindow::updateRecentFileActions()
//{
//	if(meshwindow = NULL)
//	{
//		return;
//	}
//	QStringList recentFiles = meshwindow->get_recent_files();
//    QMutableStringListIterator i(recentFiles);
//    while (i.hasNext()) {
//        if (!QFile::exists(i.next()))
//            i.remove();
//    }
//
//   /* for (int j = 0; j < MaxRecentFiles; ++j) {
//        if (j < recentFiles.count()) {
//            QString text = tr("&%1 %2")
//                           .arg(j + 1)
//                           .arg(strippedName(recentFiles[j]));
//            recentFileActions[j]->setText(text);
//            recentFileActions[j]->setData(recentFiles[j]);
//            recentFileActions[j]->setVisible(true);
//        } else {
//            recentFileActions[j]->setVisible(false);
//        }
//    }
//    separatorAction->setVisible(!recentFiles.isEmpty());*/
//}



void mainwindow::openRecentFile()
{
        QAction *action = qobject_cast<QAction *>(sender());
		if (action)
		{
            surfacedata->read_mesh(action->data().toString());
		}
}

//QString mainwindow::strippedName(const QString &fullFileName)
//{
//    return QFileInfo(fullFileName).fileName();
//}
//
//void mainwindow::set_window_visible(bool bVisible)
//{
//	if(mesh!=NULL)
//	{
//		QObject *send = sender();
//		if(send == pointsAction)
//		{
//			mdi->setActiveSubWindow(qobject_cast<QMdiSubWindow *>(knotswindow));
//			knots->showMaximized();
//		}
//		else
//		{
//			mdi->setActiveSubWindow(qobject_cast<QMdiSubWindow *>(meshwindow));
//			mesh->showMaximized();
//		}
//	}
//}
//
//void mainwindow::set_boundary_condition(bool bBoundary)
//{
//	if(surfacedata!=NULL)
//	{
//		surfacedata->set_boundary_condition(bBoundary);
//	}
//}
//
void mainwindow::meshwindow_close()
{
	delete meshwindow;
	meshwindow = NULL;
}
void mainwindow::knotswindow_close()
{
	delete knotswindow;
	knotswindow = NULL;
}
void mainwindow::fitwindow_close()
{
	delete fitwindow;
	fitwindow = NULL;
}
void mainwindow::mesh_fitting()
{
	if(fitwindow == NULL)
	{
		return;
	}
	if(surfacedata->get_original_mesh() != NULL)
	{
		if(fitwindow->mesh_fitting())
		{
			surfacedata->set_fitting_completed(true);
			fitwindow->update_fitting_view();
		}
		else
		{
          QMessageBox::critical(this,tr("Fitting Completing:"),tr("Fitting Failure,please check error."),QMessageBox::Ok);

		}
		//meshfittingAction->setDisabled(true);
		knotsAction->setEnabled(true);
	}
}

//void mainwindow::set_triangulation_type()
//{
//	QObject *send = sender();
//	if(send == delaunayAction)
//	{
//		surfacedata->set_triangulation_type(Delaunay);
//	}
//	else
//	{
//		if(send == variance_ddtAction)
//		{
//			surfacedata->set_triangulation_type(DDT_Variance);
//		}
//		else 
//		{
//			if(send == mean_errorAction)
//			{
//				surfacedata->set_triangulation_type(DDT_Mean_Error);
//			}
//			else
//			{
//				surfacedata->set_triangulation_type(DDT_SCO);
//			}
//		}
//	}
//}
//
//void mainwindow::set_sa_type()
//{
//	QObject *send = sender();
//	if(send == onestepAction)
//	{
//		surfacedata->set_sa_type(OneStep);
//	}
//	else
//	{
//		if(send == saAction)
//			surfacedata->set_sa_type(SA);
//		else
//			if(send == lopAction)
//				surfacedata->set_sa_type(Lop);
//			else
//				surfacedata->set_sa_type(Combination);
//	}
//}
//
//void mainwindow::surface_sampling()
//{
//	QObject *send = sender();
//	int index;
//	if(send == samplingAction_1)
//	{
//		index = 1;
//	}
//	else
//	{
//		if(send == samplingAction_2)
//		{
//			index = 2;
//		}
//		else
//		{
//			index = 3;
//		}
//	}
//	
//	meshwindow->surface_sampling(index);
//	meshwindow->update_view();
//	knotswindow->update_view();
//	openAction->setDisabled(true);
//	fittingMenu->setEnabled(true);
//	meshMenu->setDisabled(true);
//	samplingAction_1->setDisabled(true);
//	samplingAction_2->setDisabled(true);
//	samplingAction_3->setDisabled(true);
//}
//

void mainwindow::mesh_parametrization()
{
	
		if(meshwindow == NULL)
		{
			return;
		}
		if(surfacedata->get_original_mesh() != NULL)
		{
			if(meshwindow->mesh_parametrization())
				knotswindow->update_view();
			//parametrizationAction->setDisabled(true);
			knotsAction->setEnabled(true);
			/*meshfittingAction->setEnabled(true);*/
		}
	
	
}


void mainwindow::adjust_upper()
{
	double max_meancur = surfacedata->get_max_meancurvature();
	QString str = "The maximal mean curvature of original surface is ";
	str.append(QString::number(max_meancur));
	QMessageBox::information(this, "maximal curvature of Original Surface", str, QMessageBox::Yes, QMessageBox::Yes);
	bool ok = false;
	double uppercur = 
		QInputDialog::getDouble(this, 
		tr("Curvature Upper bound"),
		tr("Please input number:"),
		0.00,
		-500,
		500,
		8,
		&ok);//设置曲率上界，一旦我们计算的最大曲率点比较孤立，比如只有一个，则我们需要降低曲率上界的标准，默认最大曲率=曲率上界
	//使之整体曲率比较大的点突出来。
	if(!ok)
		uppercur = max_meancur;
	surfacedata->set_max_curvature(uppercur);

}
void  mainwindow::load_curvature()
{
	QStringList files = QFileDialog::getOpenFileNames(this, 
                tr("Load two curvature files:"), "./splinefitting/model", tr("Curvature Files(*.txt)"));
	if (files.size()==2&& surfacedata->compute_curvature(files))
	{
		statusBar()->showMessage(tr("Loading curvature successfully"), 2000);
		surfacedata->set_curvature_loadingstate(true);
	}
	else
	{
		statusBar()->showMessage(tr("Loading curvature unsuccessfully"), 2000);
		surfacedata->set_curvature_loadingstate(false);
	}


}

void mainwindow::input_parameter()
{
	bool ok;
	
	B_parameter *parameter=new B_parameter(0,0,0,0);
	int value1=QInputDialog::getInt(this,tr("parameter inputting"),tr("Please input parameter p:"),3,1,100,1,&ok);

	if (ok){	
		parameter->setp(value1);
		int value2=QInputDialog::getInt(this,tr("parameter inputting"),tr("Please input parameter q:"),3,1,100,1,&ok);
		if (ok)
		{
			parameter->setq(value2);
			int value3=QInputDialog::getInt(this,tr("parameter inputting"),tr("Please input parameter m:"),3,1,100,1,&ok);
			if (ok)
			{
				parameter->setm(value3);
				int value4=QInputDialog::getInt(this,tr("parameter inputting"),tr("Please input parameter n:"),3,1,100,1,&ok);
				if (ok)
				{
					parameter->setn(value4);
				}
			}
		}

	}
	int a=parameter->getm()+2-parameter->getp();
	int b=parameter->getn()+2-parameter->getq();
	parameter->setnum(a,b);
	if (surfacedata==NULL)
		return;
	surfacedata->setparameter(parameter);
	meshfittingAction->setEnabled(true);
}

void mainwindow::add_knots()
{
	if (surfacedata==NULL)
		return;
	bool ok;
	int value1=QInputDialog::getInt(this,tr("Knots adding num every time"),tr("Please input Vertical_Knots_adding num:"),10,0,100,1,&ok);
	if(!ok)
		return;
	surfacedata->set_knots_adding_num(value1);
	if(!surfacedata->add_knots())
	{
		QMessageBox::critical(this,tr("Knots Updating:"),tr("Knots has NOT been updated yet,please check error."),QMessageBox::Ok);
		return;
	}
	QMessageBox::information(this,tr("Knots Updating:"),tr("Knots has  been updated ,please check knots configuration in the Knot Window."),QMessageBox::Ok);


}
void mainwindow::add_horizon_knots()
{
	if (surfacedata==NULL)
		return;
	bool ok;
	int value1=QInputDialog::getInt(this,tr("Knots adding num every time"),tr("Please input Horizon_Knots_adding num:"),10,0,100,1,&ok);
	if(!ok)
		return;
	surfacedata->set_horizon_knots_addnum(value1);
	if(!surfacedata->add_horizon_knots())
	{
		QMessageBox::critical(this,tr("Knots Updating:"),tr("Horizonal  knots has NOT been updated yet,please check error."),QMessageBox::Ok);
		return;
	}
	QMessageBox::information(this,tr("Knots Updating:"),tr("Horizonal  Knots has  been updated ,please check knots configuration in the Knot Window."),QMessageBox::Ok);



}
void  mainwindow::adjust_knots()
{
	bool ok;
	int value1=QInputDialog::getInt(this,tr("Iteration Times inputting"),tr("Please input iteration times :"),0,0,100,1,&ok);
	if(!ok)
		return;
	int ret=QMessageBox::question(this,tr("Curvature Loding:"),tr("Curvature lodded successfully?  If not,please Loading Curvature."),QMessageBox::Yes,QMessageBox::No);
	if(ret==QMessageBox::No)
		return;
   surfacedata->set_knots_iteration_times(value1);
	if(!surfacedata->adjust_knots())
   {
	   QMessageBox::critical(this,tr("Knots Updating:"),tr("Knots has NOT been updated yet,please check error."),QMessageBox::Ok);
	   return;
   }
 QMessageBox::information(this,tr("Knots Updating:"),tr("Knots has  been updated ,please check knots configuration in the Knot Window."),QMessageBox::Ok);
  

}
void mainwindow::adjust_knots_by_fitting_error()
{
	bool ok;
	int value1=QInputDialog::getInt(this,tr("Iteration Times inputting"),tr("Please input iteration times :"),-1,-1,100,1,&ok);
	if(!ok)
		return;
	surfacedata->set_knots_iteration_times(value1);
	if(!surfacedata->adjust_knots_by_fitting_error())
	{
		QMessageBox::critical(this,tr("Knots Updating:"),tr("Knots has NOT been updated yet,please check error."),QMessageBox::Ok);
		return;
	}
	QMessageBox::information(this,tr("Knots Updating:"),tr("Knots has  been updated ,please check knots configuration in the Knot Window."),QMessageBox::Ok);


}
//bool mainwindow::save_global_costs()
//{
//	surfacedata->save_global_costs();
//	return true;
//}::save()
//{
//	QString curFile = meshwindow->get_cur_file();
//	if (curFile.isEmpty()) 
//	{
//		return saveAs();
//	} 
//	else 
//	{
//		return surfacedata->write_mesh(curFile);
//	}
//}
//

//void mainwindow::updateRecentFileActions()
//{
//	if(meshwindow = NULL)
//	{
//		return;
//	}
//	QStringList recentFiles = meshwindow->get_recent_files();
//	QMutableStringListIterator i(recentFiles);
//	while (i.hasNext()) {
//		if (!QFile::exists(i.next()))
//			i.remove();
//	}
//
//	for (int j = 0; j < MaxRecentFiles; ++j) {
//		if (j < recentFiles.count()) {
//			QString text = tr("&%1 %2")
//				.arg(j + 1)
//				.arg(strippedName(recentFiles[j]));
//			recentFileActions[j]->setText(text);
//			recentFileActions[j]->setData(recentFiles[j]);
//			recentFileActions[j]->setVisible(true);
//		} else {
//			recentFileActions[j]->setVisible(false);
//		}
//	}
//	separatorAction->setVisible(!recentFiles.isEmpty());
//}
//
//
//
//void mainwindow::openRecentFile()
//{
//	QAction *action = qobject_cast<QAction *>(sender());
//	if (action)
//	{
//		surfacedata->read_mesh(action->data().toString());
//	}
//}
//
//QString mainwindow::strippedName(const QString &fullFileName)
//{
//	return QFileInfo(fullFileName).fileName();
//}
//
void mainwindow::set_window_visible(bool bVisible)
{
	if(mesh!=NULL)
	{
		QObject *send = sender();
		if(send == pointsAction)
		{
			mdi->setActiveSubWindow(qobject_cast<QMdiSubWindow *>(knotswindow));
		    knotswindow->showMaximized();
		}
		else if(send == meshAction)
		{
			mdi->setActiveSubWindow(qobject_cast<QMdiSubWindow *>(meshwindow));
			 meshwindow->showMaximized();
		}
		else
		{
			mdi->setActiveSubWindow(qobject_cast<QMdiSubWindow *>(fitwindow));
			fitwindow->showMaximized();
		}
	}
}

//void mainwindow::set_boundary_condition(bool bBoundary)
//{
//	if(surfacedata!=NULL)
//	{
//		surfacedata->set_boundary_condition(bBoundary);
//	}
//}
//
//void mainwindow::meshwindow_close()
//{
//	delete meshwindow;
//	meshwindow = NULL;
//}
//void mainwindow::knotswindow_close()
//{
//	delete knotswindow;
//	knotswindow = NULL;
//}
//
//void mainwindow::mesh_fitting()
//{
//	if(meshwindow == NULL)
//	{
//		return;
//	}
//	if(surfacedata->get_original_mesh() != NULL)
//	{
//		meshwindow->mesh_fitting();
//		meshfittingAction->setDisabled(true);
//		knotsAction->setEnabled(true);
//	}
//}
//
//void mainwindow::set_triangulation_type()
//{
//	QObject *send = sender();
//	if(send == delaunayAction)
//	{
//		surfacedata->set_triangulation_type(Delaunay);
//	}
//	else
//	{
//		if(send == variance_ddtAction)
//		{
//			surfacedata->set_triangulation_type(DDT_Variance);
//		}
//		else 
//		{
//			if(send == mean_errorAction)
//			{
//				surfacedata->set_triangulation_type(DDT_Mean_Error);
//			}
//			else
//			{
//				surfacedata->set_triangulation_type(DDT_SCO);
//			}
//		}
//	}
//}
//
//void mainwindow::set_sa_type()
//{
//	QObject *send = sender();
//	if(send == onestepAction)
//	{
//		surfacedata->set_sa_type(OneStep);
//	}
//	else
//	{
//		if(send == saAction)
//			surfacedata->set_sa_type(SA);
//		else
//			if(send == lopAction)
//				surfacedata->set_sa_type(Lop);
//			else
//				surfacedata->set_sa_type(Combination);
//	}
//}
//
//void mainwindow::surface_sampling()
//{
//	QObject *send = sender();
//	int index;
//	if(send == samplingAction_1)
//	{
//		index = 1;
//	}
//	else
//	{
//		if(send == samplingAction_2)
//		{
//			index = 2;
//		}
//		else
//		{
//			index = 3;
//		}
//	}
//
//	meshwindow->surface_sampling(index);
//	meshwindow->update_view();
//	knotswindow->update_view();
//	openAction->setDisabled(true);
//	fittingMenu->setEnabled(true);
//	meshMenu->setDisabled(true);
//	samplingAction_1->setDisabled(true);
//	samplingAction_2->setDisabled(true);
//	samplingAction_3->setDisabled(true);
//}
//
//void mainwindow::add_knots()
//{
//	if(meshwindow == NULL)
//	{
//		return;
//	}
//	if(surfacedata->get_original_mesh() != NULL)
//	{
//		meshwindow->add_knots();	
//		knotsAction->setDisabled(true);
//		meshfittingAction->setEnabled(true);
//	}
//}
//
//void mainwindow::mesh_parametrization()
//{
//	if(meshwindow == NULL)
//	{
//		return;
//	}
//	if(surfacedata->get_original_mesh() != NULL)
//	{
//		if(meshwindow->mesh_parametrization())
//			knotswindow->update_view();
//		parametrizationAction->setDisabled(true);
//		knotsAction->setEnabled(true);
//		meshfittingAction->setDisabled(true);
//	}
//}
//
//void mainwindow::surface_fitting()
//{
//	if(meshwindow == NULL)
//	{
//		return;
//	}
//	if(surfacedata->get_original_mesh() != NULL)
//	{
//		meshwindow->surface_fitting();
//		meshwindow->mesh_fitting();
//		knotswindow->set_surface_data(surfacedata);
//	}
//}
//
//void mainwindow::set_output(bool bo)
//{
//	if(!surfacedata)
//	{
//		return;
//	}
//	surfacedata->set_output(bo);
//}
//
//void mainwindow::set_triangulation_type(bool tv)
//{
//	surfacedata->set_triangulation_type(tv);
//}
//
//void mainwindow::set_ann(bool av)
//{
//	surfacedata->set_ann(av);
//}
//
//void mainwindow::set_knot_input(bool ki)
//{
//	surfacedata->set_knots_input(ki);
//}
//
//bool mainwindow::save_global_costs()
//{
//	surfacedata->save_global_costs();
//	return true;
//}