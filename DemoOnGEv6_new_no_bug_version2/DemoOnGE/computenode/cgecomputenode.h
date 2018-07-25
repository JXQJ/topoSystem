#pragma once

#include <QtGui>
#include <QObject>
#include <vector>
#include "cgedataformatdefine.h"
#include "cgepublicmath.h"
#include <iostream>
#include <string>
#include <fstream>
#include <math.h>
#include <iomanip>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <iomanip>

#define EMAX 2000 // ������
#define TREENUM 3 //������������
#define PATHNUM 20//·������
#define portCircleRadius 0.3
#define portSize 0.3
#define INF 0x7ffffff
using namespace std;

typedef struct City
{
	string cityName;
	string countryDomain;
	double m,l;	
}City;

typedef struct Point
{
	double l,m;
	Point& operator=(const City& cityToPoint)
	{
		l=cityToPoint.l;
		m=cityToPoint.m;
		return *this;
	}
	Point& operator=(const SpacePoint& spacepointtopoint)
	{
		l=spacepointtopoint.y;
		m=spacepointtopoint.x;
		return *this;
	}
}Point;

typedef struct Circle
{
	Point center;double radius;
}Circle;


typedef struct Simtime
{
	int date;
	int month;
	int year;
	int hour;
    friend bool operator<(const Simtime &,const Simtime &);
	friend Simtime operator+(const Simtime&,const int&);
	friend Simtime operator+(const Simtime&,const Simtime&);
}Simtime;


class CGEComputeNode :public QObject
{
	Q_OBJECT

public:
	CGEComputeNode();
	~CGEComputeNode();
   
	//��ʼ������
	void initialize();
	//���뾭�ȵ㣬���Ա���
	bool ReadPointFromFile(string&,int);
	void InitSimtime(Simtime&,int,int,int,int);
	
	//�����㷨�����������
	void CreatGrid(Points _points, Triangles &_triangles);
	void UpdataNeighbor(Points _points, Triangles &_triangles);
	void Deletetriangles();
	
	//�õ�ĳ���ڵ�(���)����״����
	void UpdataTree(Triangles &_triangles,/*TreeNode* fathernode*/vector<TreeNode *>t_vec);
	void createTreeRoot(int num);
	void createCircleGridandTreeRoot(int num);
    void changeBagIcon(char[]);
	void drawAsIcon(Point,Simtime,int);


	//�������ɵ���������
	void SaveGridPoint();
	
	//�����淵�ظ��ڵ�vector
	vector<TreeNode*> getTreeNodevec(){return m_headNodevec;}

	//��ȡ���ڵ��·��
	vector<int> TreePathToDstNode(int index);
	//����·��
	void createPathToTheROOTnode(TreeNode* edgeNode);
	//��ȡ��������Ҷ�ڵ�
	void createAllEdgeNodes();
	//��ȡ������������Ҷ�ڵ�
	void createAllEdgeNodesofSingleTree(TreeNode* rootTreeNode);
	//��������·��
	void createSomePathes();


	void solute();//Ȧ���������ɹ���
	void toporoute();
	
	double getDistance(Point _pt1, Point _pt2);
	void topographyformtraceroute();//Ȧ��traceroute���ɹ��̣�����������
	void topographyFormTraceRoute(TreeNode*,Simtime &);// Ȧ��traceroute���ɹ��̼�����topographyformtraceroute
	void topographyFormTopo();//Ȧ���������ɵĹ��̣�����������
	void process1(int idRoot,int idChild,Simtime &st);//�����߶ε������˵㣨Ϊ����id�ţ������ǵ����ߣ����з���ʱ��
	void showTraceRouteDfs(TreeNode* ,Simtime &);//��ʾ�շ�����traceroute����
	void drawBag(int,int,Simtime &);//������֮���շ���ʱ�����
	void drawPoint(int,Simtime);//����һ���㣨·������������
	void drawPoint(Point);//Ϊ��������ר��д�Ļ��㺯��
	void getCircle(int circlenum,int citynum);//Ϊ������ŷ�޻�ò�������������Բ
	double deal(double i);//û�б�Ҫ֪�����庬��ĺ���
	double deal2(double i);//ͬ��
	void dfs(TreeNode* root,Simtime &st);//����������
	void getPoint(double slong,double smag,double elong,double emag,int &size);//����߶��ϵĶ���ڵ㣬�Է��㻭��
	void drawLine(double a1,double b1,double c1,double d1,Simtime &st);//����һ����ʵ/�飩�ߣ�ʵ����traceroute������ֵ����
	bool incircle(Circle blackhole,Point input);//�ж�һ�����Ƿ���Բ��
	void traceRoute(void);//traceroute����
	void addSpacetime(Simtime &st1);
	double change(double l);//û�б�Ҫ֪��������������� 
	bool isLeapYear(int);//�ж�һ���Ƿ�Ϊ����
	void generateOutAndIn(int,int);//����Ȧ��Ȧ��Ľڵ㣬����������
	void routedfs(void);
	int continentId;//��øö���������Ĵ��޺�
	bool InCircle(Point);//�ж�һ�����Ƿ���Բ��
	bool InCircle(int);//�ж�һ�����е��������Ƿ���Բ��
	bool InCircle(Point,Point,double);
	void changeIcon(char[],double);//����ͼ���ͼ���С������Ϊͼ����ļ�������Ҫ������allcity�ļ�����
	void drawPointport(Point,Simtime);
	void getAllAsDomain(void);
	void astopoForm(void); 
	void drawTerminal(Point,char[],double,Simtime,Simtime _endtime);
	void changeLookAt(double,double,double,Simtime);
	//double getDistance(Point _pt1,Point _pt2);
	bool ifLineCross(Point startPoint1,Point endPoint1,Point startPoint2,Point endPoint2);
	inline int crossProduct(Point _pt1,Point _pt2,Point _pt3)
	{
		return (_pt2.l-_pt1.l)*(_pt3.m-_pt1.m)-(_pt3.l-_pt1.l)*(_pt2.m-_pt1.m);
	}
    void changeLineStyle(int colorid,int lineWidth,double alpha=1);
	bool ifHeight;
	bool ifStatic;
	bool ifDotLine;
	bool ifaslevel;
	bool ifastoas;
	bool ifTerminalDisappear;
	bool ifbfs;
	bool ifneedoutincirclepoint;
	double minLongitude;
	double maxLongitude;
	double minLatitude;
	double maxLatitude;
	Point lastPoint;
	Point prevPoint;

	void GetPointsInCircle(TreeNode* rootNode,Points& in_points, Points& out_points);
	void UpdateCircleTree(vector<TreeNode *>);
	Point getCrossPoint(int nextcityindex,int precityindex,double radius=portCircleRadius); 
	
	void drawLine(int startPointIndex,int endPointIndex,Simtime &st);//���ߣ�ʵ�ֻ����ߣ��������Ϊ��ʼ�����˽ڵ�ĳ���������

    int cityNum;//��¼�˸ô������г��и���
	string outputfile;//������ļ���
	Simtime simtime;
    Simtime begintime;
	Simtime endtime;//����Ľ���ʱ��
	vector<Point> outCityIndex;//the city go out of the topo
	vector<vector<vector<SpacePoint>>> getAllTreePathPoints(){return m_AllTreePathPoints;}

	struct VariousAs
	{
		Point asCenter;
		vector<int> cityInAS;
		int Height;
	}ASNo[200];

private:
	//��������
	inline bool ifExist(vector<int>vec, int index); 
	static const int Height=150000;
	static const int heightlevel1=150000;
	static const int heightlevel2=1500000;

	inline bool ifExistEdge(SpacePoint tp1, SpacePoint tp2);
	inline bool ifPointsCirclrExist(int index);
	inline bool ifPointsInCircle(int index);
	inline bool ifPointsOutCircle(int index);
	bool getPointParameter;

private:

	Points m_inPoints;                                         //in Points
	PublicMath *m_publicMath;                                  //public math
	Triangles m_triangles;                                     //public triangles
	vector<pair<SpacePoint, SpacePoint> > m_inseaPoints;       //the Points in the sea   

	City city[1000];        //city in a continent

	Point portPoint;
	vector<Circle> circle;
	vector<int>m_allnodesindex;
	vector<int>m_pathIndex;			//·���ϵĵ��������
	vector<SpacePoint>		m_NodePathPoints;	//��Ե�ڵ㵽���ڵ�·�������еĵ�
	vector<vector<SpacePoint>> m_TreePathPoints;//�������б�Ե�ڵ㵽�������ڵ�·���ϵĵ�
	vector<vector<vector<SpacePoint>>> m_AllTreePathPoints;//������<TREENUM��>��ÿ����<N >��
	vector<int> CityUsed;
	TreeNode* m_headNode;

	vector<TreeNode*>m_headNodevec;                 //������ڵ�
	vector<TreeNode*>m_nodesvec;                    //һ��ĸ��ڵ�
	vector<vector<TreeNode*>> m_EdgeNodesVct;//���������Ҷ�ڵ�,TREENUM��,ÿ�е�Ԫ��Ϊ�����ı�Ե�ڵ�
	vector<TreeNode*> vct_Node;								//���������Ҷ�ӽڵ�
	int circlenum;
	int traceroute;
	int leafNum;
	int AsNum;
	string nowPenColor;
	string nowColor;	
	vector<int> routeStack;
	vector<int> routeStack2;
	vector<Point> pointStack;
	ofstream fout;
	vector<TreeNode *> rootVector;
	
	Simtime timeRecord;
	Simtime anotherTimeRecord;
	int sameTimeTraceRoute;
    vector<Point> pointVector;

	Points m_incirclePoints;                                   // a continent may have some trees and a circle, some points may in the circle and ,of course some are not;
	Points m_outcirclePoints;                                  // a continent may have some trees and a circle, some points may in the circle and ,of course some are not;
	Points m_circlePoints;                                     // the sum of the above two
	Triangles m_circletriangles;                               // the triangles with the points
	vector<TreeNode *> m_circletreevec;                        // the points with the circle may generate some trees
	vector<int> m_allcirclenodeindex;
};