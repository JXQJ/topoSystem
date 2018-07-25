#include "cgewnd.h"
#include <comdef.h>
#include <QMessageBox>
#include <QResizeEvent>
#include <QFileDialog>
#include <fstream>
#include <string>
#include<QtGui>
#include"serverSet.h"

#import "C:/Program Files (x86)/Google/Google Earth/client/googleearth.exe"  named_guids
using namespace EARTHLib;
extern IApplicationGEPtr gGoogleEarthApp;
extern char **nowFile;
ICameraInfoGEPtr defaultCamera;

CGEwnd::CGEwnd(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{

	ui.setupUi(this);
	this->setWindowTitle(tr("ȫ���������˲�����ʾϵͳ  �汾��V1.0"));
	this->setWindowIcon(QIcon(":/CGEwnd/Resources/logo.png"));
	creatActions();
	createMenus();
	createToolBars();
	//��Google Earth����CentralWidget��
	comnodetmp=new CGEComputeNode;
	geWidget = new GeWidget(this);
	setCentralWidget(geWidget);
	connect(&myTrace,SIGNAL(finished()),this,SLOT(threadFinish()));
	connect(&myShow,SIGNAL(finished()),this,SLOT(myShowfinish()));
	ooo = new ServerSet(this,&myTrace);
	
}

CGEwnd::~CGEwnd()
{
	
}
/*��������*/
void CGEwnd::creatActions()
{
	loadKMLAction = new QAction(tr("��KML�ļ�(&O)"),this);
	loadKMLAction->setIcon(QIcon(":/CGEwnd/Resources/open.png"));
	loadKMLAction->setToolTip(tr("�� .kml�� .kmz�ļ�..."));
	loadKMLAction->setShortcut(tr("Ctrl+O"));
	connect(loadKMLAction, SIGNAL(triggered()), this, SLOT(slot_loadKML()));

	inputFileAction = new QAction(tr("�����������ļ�"), this);
	connect(inputFileAction, SIGNAL(triggered()), this, SLOT(slot_inputFile()));


	traceRouteAction=new QAction(tr("������Ϣ�ռ���ʾ"),this);
	traceRouteAction->setIcon(QIcon(":/CGEwnd/Resources/tance.png"));
	connect(traceRouteAction,SIGNAL(triggered()), this, SLOT(slot_traceRoute()));
	exitAction = new QAction(tr("�˳�(&X)"),this);
	exitAction->setIcon(QIcon(":/CGEwnd/Resources/close.png"));
	exitAction->setToolTip(tr("�˳�����"));
	exitAction->setShortcut(tr("Ctrl+Q"));
	connect(exitAction, SIGNAL(triggered()), this, SLOT(slot_exit()));
	gotoDefaultViewAction = new QAction(tr("Ĭ���ӽ�"), this);
	gotoDefaultViewAction->setIcon(QIcon(":/CGEwnd/Resources/earth.png"));
	gotoDefaultViewAction->setToolTip(tr("Ĭ���ӽ�"));
	gotoDefaultViewAction->setShortcut(tr("Ctrl+0"));
	connect(gotoDefaultViewAction, SIGNAL(triggered()), this, SLOT(slot_gotoDefaultView()));

	stsBarAction = new QAction(tr("״̬��(&S)"),this);
	stsBarAction->setCheckable(true);			//���ÿ�ѡ
	stsBarAction->setChecked(true);				//��ʼ��ʱ������ʾ״̬���������ó���ֵΪѡ��
	connect(stsBarAction, SIGNAL(triggered()), this, SLOT(setStsBarVisibleOrNot()));

	aboutAction = new QAction(tr("�������(&A)"),this);
	connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));

	aboutQtAction = new QAction(tr("����QT(&Q)"),this);
	connect(aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

	serverSetting = new QAction(tr("���ݲɼ�����������"),this);
	connect(serverSetting,SIGNAL(triggered()),this,SLOT(slot_serverSetting()));
}

void CGEwnd::slot_serverSetting()
{
	if (myTrace.isRunning())
	{
		QMessageBox::information(this, tr("��ʾ"),
			QString(tr("���ڽ���traceroute�������traceroute���֮���ٽ���traceroute")));
		return;
	}
	else
	{
		//ServerSet*ooo = new ServerSet(this,&myTrace);
		ooo->show();
	}
	return;
}
void CGEwnd::threadFinish()
{
	QMessageBox::information(this, tr("��ʾ"),
		QString(tr("traceroute��ϣ�")));
}
void CGEwnd::myShowfinish()
{
	QMessageBox::information(this, tr("��ʾ"),
		QString(tr("traceroute���������ϣ�")));
}
void CGEwnd::slot_inputFile()
{
	comnodetmp->initialize();
	string useLessString;

    if(comnodetmp->ReadPointFromFile(useLessString,0))
	{
		comnodetmp->createTreeRoot(TREENUM);		//����TREENUM����
		comnodetmp->solute();
		comnodetmp->traceRoute();
	}
}

/*�˳����*/
void CGEwnd::slot_traceRoute()
{
	QString IP_file = QFileDialog::getOpenFileName(this, QObject::tr("��IP�ļ�"),"",QObject::tr("")); 
	QMessageBox::information(this, tr("��ʾ"),
		QString(tr("����traceroute����,������ɺ�����ͬ�ļ��´򿪽��")));
	myShow.setFile(IP_file);
	myShow.start();
}


void CGEwnd::createMenus()
{
	//fileMenu = menuBar()->addMenu(tr("�ļ�(&F)"));//menuBar()��QMainWindow�еĺ���,����QMenuBar*,addMenu()��QMenuBar�еĺ���������QMenu*;
	settingMenu = menuBar()->addMenu(tr("�ɼ�(&S)"));
	settingMenu ->addAction(serverSetting);

	showMenu = menuBar()->addMenu(tr("����(&S)"));
	showMenu->addAction(gotoDefaultViewAction);
	showMenu->addSeparator();
	showMenu->addAction(traceRouteAction);

	fileMenu = ui.menuBar->addMenu(tr("�ļ�(&F)"));//ui.menuBar�������menuBar��ָ�Ķ���Ϊͬһ������*this�Ĳ˵���
	fileMenu->addAction(loadKMLAction);
	fileMenu->addSeparator();
	fileMenu->addAction(exitAction);

	viewMenu = menuBar()->addMenu(tr("��ͼ(&V)"));
	viewMenu->addAction(ui.mainToolBar->toggleViewAction());
	viewMenu->addAction(stsBarAction);

	helpMenu = menuBar()->addMenu(tr("����(&H)"));
	helpMenu->addAction(aboutAction);
	//helpMenu->addAction(aboutQtAction);

}
/*����������*/
void CGEwnd::createToolBars()
{
	ui.mainToolBar->setWindowTitle(tr("������"));
	ui.mainToolBar->addAction(loadKMLAction);
    ui.mainToolBar->addSeparator();
	ui.mainToolBar->addAction(gotoDefaultViewAction);
	ui.mainToolBar->addAction(traceRouteAction);
	ui.mainToolBar->addSeparator();
	ui.mainToolBar->addAction(exitAction);
}
/*�˳�Google earth*/
void CGEwnd::GoogleEarthAppExit()
{
	//�˳�Google earth
	geWidget->Exit();
}

void CGEwnd::about()
{
	//��ȡGoogle����İ汾��Ϣ
	int verMajor = gGoogleEarthApp->GetVersionMajor();
	int verMinor = gGoogleEarthApp->GetVersionMinor();

	QMessageBox::about(this, tr("���ڱ����"),
		QString(tr("�����ϵͳʹ��QT������\n"
		"QT�汾4.4.0\n"
		"������Google Earth������ʾ���ܣ�\n"
		"Google Earth�汾��Ϊ%1.%2")).arg(verMajor).arg(verMinor));
}

void CGEwnd::setStsBarVisibleOrNot()
{
	//���stsBarAction��ѡ��״̬��ѡ������ʾ״̬����������ʾ
	if (stsBarAction->isChecked())
	{
		ui.statusBar->setVisible(true);
	}
	else
	{
		ui.statusBar->setVisible(false);
	}
}
/*����KML�ļ�*/
void CGEwnd::slot_loadKML()
{
	QString strPath;
	if (m_strKmlFile.isEmpty())
	{
		strPath = "";
	}
	else
	{
		strPath = m_strKmlFile.left(m_strKmlFile.lastIndexOf('\\'));
	}
	m_strKmlFile = QFileDialog::getOpenFileName(this, tr("��.kml �� kmz�ļ�..."),
		strPath,
		tr("KML (*.kml *.kmz)")); 

	//_bstr_t strFileName = L"E:/path.kml";


	if (!m_strKmlFile.isEmpty())
	{
		//this string format conversion exits
		// for OpenKmlFile takes wchar_t array as input
		//MAX_PATH is a constant defined by windows
		wchar_t wchPath[MAX_PATH];
		memset(wchPath, 0, sizeof (wchar_t) * MAX_PATH);
		m_strKmlFile.toWCharArray(wchPath);
		gGoogleEarthApp->OpenKmlFile(wchPath, 1);

	}
}
/*���������ļ�*/

/*�˳����*/
void CGEwnd::slot_exit()
{
	if (QMessageBox::Yes != QMessageBox::information(this, tr("��ʾ"),
		QString(tr("�Ƿ��˳�������")),QMessageBox::Yes |QMessageBox::Cancel))
	{
		return;
	}

	close();
}
/*��ʾĬ����ͼ*/
void CGEwnd::slot_gotoDefaultView()
{

	defaultCamera = gGoogleEarthApp->GetCamera(1);

	// ����camera����
	defaultCamera->PutRange(1000);
	defaultCamera->PutFocusPointLongitude(108.535353);
	defaultCamera->PutFocusPointLatitude(33.717171);
	defaultCamera->PutFocusPointAltitude(12000000);
	defaultCamera->PutFocusPointAltitudeMode(RelativeToGroundAltitudeGE);
	defaultCamera->PutTilt(0);
	defaultCamera->PutAzimuth(0);
	gGoogleEarthApp->SetCamera(defaultCamera, 0.2);

}