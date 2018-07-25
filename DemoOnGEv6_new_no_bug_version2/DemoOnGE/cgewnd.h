#ifndef CGEWND_H
#define CGEWND_H

#include <QtGui/QMainWindow>
#include <QLabel>
#include <QPainter>
#include "ui_cgewnd.h"
#include "GEWidget.h"
#include "./computenode/cgecomputenode.h"
#include "serverSet.h"
#include "Thread.h"
#include "ThreadShow.h"
class CGEwnd : public QMainWindow
{
	Q_OBJECT

public:
	CGEwnd(QWidget *parent = 0, Qt::WFlags flags = 0);
	~CGEwnd();

public:
	//exit the hidden GoogleEarth application
	void GoogleEarthAppExit();
private:
	Ui::CGEwndClass ui;
	GeWidget *geWidget;
	vector<CGEComputeNode*> comnode;
	CGEComputeNode* comnodetmp;	
	//save KML data file path
	QString           m_strKmlFile;
	QString           m_strScrnShotFile;
	QLabel*			  m_title;
	Thread myTrace;
	ThreadShow myShow;
	ServerSet *ooo;
private:
	QMenu *settingMenu;	//���ò˵�
	QMenu *fileMenu;		//�ļ��˵�
	QMenu *showMenu;		//��ʾ�˵�
	QMenu *viewMenu;		//��ͼ�˵�
	QMenu *helpMenu;		//�����˵�

	QAction *loadKMLAction;		//��kml�ļ�
	QAction *inputFileAction;		//�������ļ�
	QAction *loadAllKmlAction;		//������kml
	QAction *traceRouteAction;      //open traceRoute.kml
	QAction *topoAction;            //open topo.kml
	QAction *exitAction;		//�˳�����
	QAction *stsBarAction;	//״̬��������ʾ
	QAction *gotoDefaultViewAction;		//��ʾĬ���ӽ�
	QAction *aboutAction;	//���ڲ˵�
	QAction *aboutQtAction;	//����Qt�˵�
	QAction *routetopoAction;
	QAction *AStopoAction;
	QAction *serverSetting; //����������

private:
	void creatActions();			//��������
	void createMenus();				//�����˵���
	void createToolBars();			//����������

private slots:
	void about();
	void threadFinish();
	void myShowfinish();
	void slot_loadKML();			//��kml�ļ�
	void slot_inputFile();				//���������ļ�
	void slot_traceRoute();			//show traceRoute process
	void slot_exit();				//�˳�����
	void slot_gotoDefaultView();		//��ʾĬ���ӽ�
	void setStsBarVisibleOrNot();	//����״̬���Ƿ���ʾ
	void slot_serverSetting();			//�������������ô���
};

#endif // CGEWND_H
