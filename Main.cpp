#include<malloc.h>
#include<string>
#include<iomanip>
#include<stdio.h>
#define max_ver_num 50
//#define OK 1
#define FALSE 0
#define Error -1
#define A 1000
#define TRUE 1

typedef struct arcnode//设置边的权值信息
{
   int adj;//路径权值
}arcnode,adjarcs[max_ver_num][max_ver_num];

typedef struct verdata//设置景点信息
{
	int  position; //顶点个数
	char name[60];	//顶点名称
	char introduction[1000];	//顶点介绍
}verdata;
typedef struct mgraph	//景点图
{
   verdata vexs[max_ver_num];	//景点数据
   adjarcs arcs;	//路径信息
   int vernum,arcnum;	
}mgraph;

//全局变量
int visited[20];
int d[35];
mgraph g;

//校园导游图的初始化
int initgraph(mgraph& G)
{
	int i,j;
	G.vernum=10;
	G.arcnum=20;
	//初始化景点平面图
	for(i=0;i<G.vernum;i++)
		G.vexs[i].position=i;

	strcpy(G.vexs[0].name,"莞华社区");
    strcpy(G.vexs[1].name,"莞馨社区");
	strcpy(G.vexs[2].name,"莞雅社区");
    strcpy(G.vexs[3].name,"莞逸社区");
    strcpy(G.vexs[4].name,"莞博社区");
    strcpy(G.vexs[5].name,"第一饭堂");
	strcpy(G.vexs[6].name,"第二饭堂");
    strcpy(G.vexs[7].name,"第三饭堂");
    strcpy(G.vexs[8].name,"学生活动中心");
    strcpy(G.vexs[9].name,"理工北门");

	strcpy(G.vexs[0].introduction,"男生社区");
    strcpy(G.vexs[1].introduction,"女生社区");
	strcpy(G.vexs[2].introduction,"女生社区");
    strcpy(G.vexs[3].introduction,"男生社区");
    strcpy(G.vexs[4].introduction,"男生社区");
    strcpy(G.vexs[5].introduction,"学校饭堂");
	strcpy(G.vexs[6].introduction,"学校饭堂");
    strcpy(G.vexs[7].introduction,"学校饭堂");
    strcpy(G.vexs[8].introduction,"学生举行课外活动、会议的场所");
    strcpy(G.vexs[9].introduction,"学生出入人次最多的校门口");

	//初始化边矩阵
	for(i=0;i<G.vernum;i++)
		for(j=0;j<G.vernum;j++)
			G.arcs[i][j].adj=A;
	G.arcs[0][1].adj=15;
	G.arcs[0][2].adj=25;
	G.arcs[0][3].adj=30;
	G.arcs[1][4].adj=15;
	G.arcs[1][7].adj=20;
	G.arcs[1][9].adj=40;
	G.arcs[2][5].adj=10;
	G.arcs[2][8].adj=15;
	G.arcs[3][6].adj=30;
	G.arcs[3][8].adj=20;
	G.arcs[4][7].adj=10;
	G.arcs[4][9].adj=60;
	G.arcs[5][8].adj=25;
	G.arcs[6][8].adj=50;
	G.arcs[7][9].adj=35;
	G.arcs[4][5].adj=20;
	G.arcs[5][6].adj=25;
	G.arcs[5][7].adj=30;
	G.arcs[6][7].adj=15;
	G.arcs[6][9].adj=20;
	G.arcs[7][8].adj=40;
	G.arcs[8][9].adj=10;
	G.arcs[2][9].adj=15;
	G.arcs[3][9].adj=30;
	G.arcs[3][4].adj=20;
	G.arcs[4][8].adj=10;
	G.arcs[4][5].adj=60;
	G.arcs[5][9].adj=25;
	G.arcs[1][8].adj=50;
	G.arcs[1][7].adj=35;
	for(j=0;j<G.vernum;j++)
		for(i=0;i<G.vernum;i++)
			G.arcs[i][j].adj=G.arcs[j][i].adj;
	return 1;
}

//景点的定位
int locatevex(mgraph c,int v)//景点的定位
{
	int i;
	for(i=0;i<c.vernum;i++)
		if(v==c.vexs[i].position) 
			return i;
		return -1; //若无该景点则返回-1
}

//打印图的邻接矩阵；
int printmatrix(mgraph G)
{
	int i,j;
	printf("对应的矩阵为：\n");
	for(i=0;i<G.vernum;i++)
	{
		for(j=0;j<G.vernum;j++)
		{
			if(G.arcs[i][j].adj<A){
				printf("\t%d",G.arcs[i][j].adj);
			}
				
			else{
				printf("\t");
				printf("0");
			}
		}
		printf("\n");
	}
	int x;
	while(1){
		printf("按1返回上一层,按0退出程序：");
		scanf("%d",&x);
		if( x == 1 )
			return 1;
		else if( x == 0 ){
			exit(0);
		}
		else
			printf("输入错误，请重新输入：\n");
	}
}

//求最短路径，弗洛伊德算法
void shortestpath_Floyd(mgraph *G)
{  
	int v,u,i,w,k,j,flag=1,p[10][10][10],D[10][10];//D路径
 
	for(v=0;v<G->vernum;v++)
		for(w=0;w<G->vernum;w++)
		  {
		   D[v][w]=G->arcs[v][w].adj;
		   for(u=0;u<G->vernum;u++)
			p[v][w][u]=0;
		   if(D[v][w]<A)
		   {
			p[v][w][v]=1;p[v][w][w]=1;
		   }
		  }
 for(u=0;u<G->vernum;u++)
  for(v=0;v<G->vernum;v++)
   for(w=0;w<G->vernum;w++)
    if(D[v][u]+D[u][w]<D[v][w])
    {
     D[v][w]=D[v][u]+D[u][w];
     for(i=0;i<G->vernum;i++)
      p[v][w][i]=p[v][u][i]||p[u][w][i];
	 
    }
while(flag)
 {
	 printf("请输入出发点编号:");
	 scanf("%d",&k);
	 printf("请输入目的地的编号:\n");
	 scanf("%d",&j);
	 if(k<0 || k>G->vernum || j<0 || j>G->vernum)
	 {
		 printf("景点编号不存在!请重新输入出发点和目的地的编号:");
		 printf("请输入出发点编号:");
		 scanf("%d",&k);
		 printf("请输入目的地的编号:\n");
		 scanf("%d",&j);
	  }
	 if(k>=0 && k<G->vernum && j>=0 && j<G->vernum)
		flag=0;
}
	 printf("%s",G->vexs[k].name);
	 for(u=0;u<G->vernum;u++)
	  if(p[k][j][u]&&k!=u&&j!=u)
	   printf("-->%s",G->vexs[u].name);
	 printf("-->%s",G->vexs[j].name);
	 printf(" 总路线长%dm\n",D[k][j]);
}

//两个景点间的所有路径
void Allpath(mgraph *G)
{
	int v,w,k,j,flag=1,p[10][10],D[10][10];
	while(flag)
	{
		printf("请输入出发点和目的地的编号:\n");
		printf("请输入出发点编号:");
		scanf("%d",&k);
		printf("请输入目的地的编号:");
		scanf("%d",&j);
		if(k<0||k>G->vernum||j<0||j>G->vernum)
		 {
			printf("景点编号不存在!请重新输入出发点和目的地的编号:\n");
			printf("请输入出发点编号:\n");
			scanf("%d",&k);
			printf("请输入目的地的编号:\n");
			scanf("%d",&j);
		  }	 
		 if(k>=0&&k<G->vernum&&j>=0&&j<G->vernum)
		   flag=0;
	 }
	for(v=0;v<G->vernum;v++)
		for(w=0;w<G->vernum;w++)
		{
			D[v][w]=G->arcs[v][w].adj;
			if(D[v][w]!=A)
			{
			  p[v][w]=1;
			  p[w][v]=1;
			}
		}
		if(p[k][j]==1)
		{
			printf("%s",G->vexs[k].name);
			printf("-->");
			printf("%s",G->vexs[j].name);
			printf("总路线长%d\n",D[k][w]+D[w][j]);
		}
     for(w=0;w<G->vernum;w++)
		 if(p[k][w]==1&&p[w][j]==1) 
			{
				printf("%s",G->vexs[k].name);
				printf("-->");
				printf("%s",G->vexs[w].name);
				printf("-->");
				printf("%s",G->vexs[j].name);
				printf(" 总路线长%d\n",D[k][w]+D[w][j]);
			}
	for(v=0;v<G->vernum;v++)
		for(w=0;w<G->vernum;w++)
			if(p[k][v]==1&&p[v][w]==1&&p[w][j]==1)
			 {
				 printf("%s",G->vexs[k].name);
				 printf("-->");
				 printf("%s",G->vexs[v].name);
				 printf("-->");
				 printf("%s",G->vexs[w].name);
				 printf("-->");
				 printf("%s",G->vexs[j].name);
				 printf(" 总路线长%d\n",D[k][v]+D[w][j]+D[v][w]);
			 }
}

//显示景点信息，显示景点信息平面图
int displaycampus(mgraph G)
{
	int i;
	printf("景点编号\t\t景点名称\t\t景点简介\t\t\n");
	printf("\n");
	for(i=0;i<G.vernum;i++)
	{
		printf("  %d  \t\t\t%s\t\t%s\t\t\n\n",G.vexs[i].position,G.vexs[i].name,G.vexs[i].introduction);
		/*cout<<"    "<<G.vexs[i].position<<"      ";
		cout<<G.vexs[i].name<<"       ";
		cout<<G.vexs[i].introduction<<"       "<<endl;*/
	}
	int x;
	while(1){
		printf("按1返回上一层,按0退出程序：");
		scanf("%d",&x);
		if( x == 1 )
			return 1;
		else if( x == 0 ){
			exit(0);
		}
		else
			printf("输入错误，请重新输入：\n");
	}
}	

//构造无向图的邻接矩阵
int creatgraph(mgraph &G)
{
	int i,n,m,distance,v0,v1;
	printf("请输入矩阵对应的顶点数:");
    scanf("%d",&G.vernum);
	printf("请输入矩阵对应的边数:");
	scanf("%d",&G.arcnum);
	for(i=0;i<G.vernum;i++)
	{
		printf("请输入景点编号：");
	    scanf("%d",&G.vexs[i].position);
        printf("请输入景点名称：");
		scanf("%s",G.vexs[i].name);
        printf("请输入景点简介：");
        scanf("%s",G.vexs[i].introduction);	
	}
	for(i=0;i<G.vernum;i++)
		for(int j=0;j<G.vernum;j++)
			G.arcs[i][j].adj=0;
	for(i=0;i<G.arcnum;i++)
	{
		printf("输入第[%d]条边的起点编号:",i);
        scanf("%d",&v0);
		printf("输入第[%d]条边的终点编号:",i);
        scanf("%d",&v1);
		printf("输入第[%d]条边的长度编号:",i);
		scanf("%d",&distance);
		m=locatevex(G,v0);
		n=locatevex(G,v1);
		if(m>=0&&n>=0)
			G.arcs[m][n].adj=G.arcs[n][m].adj=distance;
	}
	displaycampus(G);
    printmatrix(G);
	return 1;
}

//删除景点信息
int DeleteVertex(mgraph &G)
{
	int i,j,v,m;
	printf("请输入要删除的景点编号:");
	scanf("%d",&v);
	m=locatevex(G,v);
	int flag=1;
	while(flag)
	{
		if(m<0)
		{
			printf("无此景点，请重新输入:");
		    scanf("%d",&v);
		}
		m=locatevex(G,v);
		if(m>0)
		{
			for(i=m;i<G.vernum ;i++)
			{
				strcpy(G.vexs[i].name,G.vexs [i+1].name);
				strcpy(G.vexs[i].introduction,G.vexs[i+1].introduction);
			}
			flag=0;
		}
	}
	for(i=m;i<G.vernum;i++)//删除行
		for(j=0;j<G.vernum;j++)
			G.arcs[i][j]=G.arcs[i+1][j];
   for(i=m;i<G.vernum;i++)//删除列
	   for(j=0;j<G.vernum;j++)
           G.arcs[j][i]=G.arcs[j][i+1];
   G.vernum--;
   displaycampus(G);
   printmatrix(G);
   return 1;
}

//删除图一条路径信息
int  DeleteplanArc(mgraph &G)
{
	int i,j,v0,v1;
	int flag=1;
	while(flag)
	 {
		printf("请输入要删除的一条边对应的两个顶点编号:\n");
		scanf("%d",v0);
		scanf("%d",v1);
		if(v0<0||v0>G.vernum||v0<0||v1>G.vernum)
		{
		  printf("景点编号不存在!请重新输入要删除的一条边对应的两个顶点编号:");
		  scanf("%d",v0);
		  scanf("%d",v1);
		}
		if(v0>=0&&v0<G.vernum&&v1>=0&&v1<G.vernum)
			flag=0; 
	}
	i=locatevex(G,v0);
	j=locatevex(G,v1);
	G.arcs[i][j].adj=A;
	G.arcs[j][i].adj=A;
	G.arcnum--;
    displaycampus(G);
    printmatrix(G);
	return 1;
}

//增加景点
int enverx(mgraph &G)
{
	int i;
	printf("请输入要添加的景点的信息：\n");
	printf("请输入景点编号:");
    scanf("%d",&G.vexs[G.vernum].position);
	printf("请输入景点名称:");
    scanf("%s",&G.vexs[G.vernum].name);
	printf("请输入景点简介:");
    scanf("%s",&G.vexs[G.vernum].introduction);
	printf("\n");
	G.vernum++;
	for(i=0;i<G.vernum;i++)
		G.arcs[i][G.vernum-1].adj=G.arcs[i][G.vernum-1].adj=A;
	displaycampus(G);
	printmatrix(G);
	return 1;
}

//增加路径
int enarc(mgraph &G)
{
	int v0,v1,distance;
	printf("请输入增加路径的起始点编号:");
    scanf("%d",&v0);
	printf("请输入增加路径的终点编号:");
    scanf("%d",&v1);
	printf("请输入增加路径长度");
	scanf("%s",&distance);
	G.arcs[v0][v1].adj=G.arcs[v1][v0].adj=distance;
	displaycampus(G);
	printmatrix(G);
	return 1;
}

//景点信息查询
void seaabout(mgraph G)
{
	int n,flag=1;
	printf("请输入要查询的景点编号：");
	scanf("%d",&n);
	while(flag)
	{
		if(n<0||n>G.vernum)
		{
			printf("该景点不存在，请重新输入：");
     		scanf("%d",&n);
		}
		else
		{
			printf("景点编号\t\t景点名称\t\t景点简介\t\t\n");
			printf("  %d  \t\t\t%s\t\t%s\t\t\n\n",G.vexs[n].position,G.vexs[n].name,G.vexs[n].introduction);
			/*
			cout<<"    "<<G.vexs[n].position<<"      ";
			cout<<G.vexs[n].name<<"       ";
			cout<<G.vexs[n].introduction<<"       "<<endl;
			*/
			flag=0;
		}
	}
}

//更新景点的信息
int newgraph(mgraph &G)
{
	int n,m,t,i;
	printf("请输入要更新的景点数：");
	scanf("%d",&n);
	while(n<0||n>G.vernum)
	{
		printf("该景点不存在，请重新输入：");
		scanf("%d",&n);
	}
	for(i=0;i<n;i++)//修改景点信息
	{
		printf("输入景点的编号：");
		scanf("%d",&m);
		t=locatevex(G,m);
		printf("输入景点的名称：");
		scanf("%s",&G.vexs[t].name);
		printf("输入景点的简介：");
		scanf("%s",&G.vexs[t].introduction);
	}
	printf("请输入要更改的边数：");
	scanf("%d",&n);
	int distance,v0,v1;
	while(n<0||n>G.arcnum)
	{
		printf("该路径不存在，请重新输入：");
		scanf("%d",&n);
	}
	printf("输入更新的路径的信息：");
	for(i=0;i<n;i++)//修改路径信息
	{
		printf("起始景点编号v0:");
        scanf("%d",&v0);
		printf("终点景点编号v1:");
        scanf("%d",&v1);
		printf("路径长度:");
	    scanf("%d",&distance);
		m=locatevex(G,v0);
		t=locatevex(G,v1);
		if(m>=0&&t>=0)
			G.arcs[m][t].adj=G.arcs[t][m].adj=distance;
	}
	displaycampus(G);
	printmatrix(G);
	return 1;
}

//更改图的信息
int changegraph(mgraph G)
{
	int i;
    printf("1、重新建图        2、删除结点  \n");
	printf("3、删除边          4、增加结点  \n");
	printf("5、增加边          6、更新图信息\n");
	printf("7、打印邻接矩阵    8、返回程序  \n");
	while(1)
	{
		printf("请输入要进行的操作:");
	    scanf("%d",&i);
		switch(i)
		{
		case 1:
			printf("重新建图:\n");
			creatgraph(g);
			break;
		case 2:
			printf("删除结点:\n");
			DeleteVertex(g);
			break;
		case 3:
			printf("删除边:\n");
			DeleteplanArc(g);
			break;
		case 4:
			printf("增加结点:\n");
			enverx(g);
			break;
		case 5:
			printf("增加边:\n");
			enarc(g);
			break;
		case 6:
			printf("更新图信息:\n");
			newgraph(g);
			break;
		case 7:
			printf("打印邻接矩阵:\n");
			printmatrix(g);
			break;
		case 8:
			printf("返回程序:\n");
			return 1;
		}
	}
	return 1;
	
}


void main()
{
	initgraph(g);

	printf("学校概况：\n");
		displaycampus(g);

	while(1)
	{
		printf("\n");
		printf("                                     欢迎来到DGUT                               \n");
		printf("                        1、学校景点介绍            2、打印邻接矩阵              \n");
		printf("                        3、查询景点间最短路径      4、查询景点信息              \n");
		printf("                        5、改变图的信息            6、查询景点间可行路径        \n");
		printf("                        7、退出程序                                             \n");

		printf("请输入你要进行的操作:");
		int k;
	    scanf("%d",&k);
		switch(k)
		{
		case 1:
			printf("学校景点介绍:\n");
			displaycampus(g);
			break;
	    case 2:
			printf("打印邻接矩阵:\n");
			printmatrix(g);
			break;
		case 3:
			printf("查询景点间最短路径:\n");
			displaycampus(g);
			shortestpath_Floyd(&g);
			break;
		case 4:
			printf("查询景点信息:\n");
			seaabout(g);
			break;
		case 5:
			printf("改变图的信息:\n");
			changegraph(g);
			break;
		case 6:
			printf("查询景点间可行路径:\n");
			Allpath(&g);
			break;
		case 7:
			printf("退出程序\n");
			//flag=0;
			exit(0);
			break;
		default:
			break;
		}
	}
}
