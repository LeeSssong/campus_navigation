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

typedef struct arcnode//���ñߵ�Ȩֵ��Ϣ
{
   int adj;//·��Ȩֵ
}arcnode,adjarcs[max_ver_num][max_ver_num];

typedef struct verdata//���þ�����Ϣ
{
	int  position; //�������
	char name[60];	//��������
	char introduction[1000];	//�������
}verdata;
typedef struct mgraph	//����ͼ
{
   verdata vexs[max_ver_num];	//��������
   adjarcs arcs;	//·����Ϣ
   int vernum,arcnum;	
}mgraph;

//ȫ�ֱ���
int visited[20];
int d[35];
mgraph g;

//У԰����ͼ�ĳ�ʼ��
int initgraph(mgraph& G)
{
	int i,j;
	G.vernum=10;
	G.arcnum=20;
	//��ʼ������ƽ��ͼ
	for(i=0;i<G.vernum;i++)
		G.vexs[i].position=i;

	strcpy(G.vexs[0].name,"ݸ������");
    strcpy(G.vexs[1].name,"ݸܰ����");
	strcpy(G.vexs[2].name,"ݸ������");
    strcpy(G.vexs[3].name,"ݸ������");
    strcpy(G.vexs[4].name,"ݸ������");
    strcpy(G.vexs[5].name,"��һ����");
	strcpy(G.vexs[6].name,"�ڶ�����");
    strcpy(G.vexs[7].name,"��������");
    strcpy(G.vexs[8].name,"ѧ�������");
    strcpy(G.vexs[9].name,"������");

	strcpy(G.vexs[0].introduction,"��������");
    strcpy(G.vexs[1].introduction,"Ů������");
	strcpy(G.vexs[2].introduction,"Ů������");
    strcpy(G.vexs[3].introduction,"��������");
    strcpy(G.vexs[4].introduction,"��������");
    strcpy(G.vexs[5].introduction,"ѧУ����");
	strcpy(G.vexs[6].introduction,"ѧУ����");
    strcpy(G.vexs[7].introduction,"ѧУ����");
    strcpy(G.vexs[8].introduction,"ѧ�����п���������ĳ���");
    strcpy(G.vexs[9].introduction,"ѧ�������˴�����У�ſ�");

	//��ʼ���߾���
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

//����Ķ�λ
int locatevex(mgraph c,int v)//����Ķ�λ
{
	int i;
	for(i=0;i<c.vernum;i++)
		if(v==c.vexs[i].position) 
			return i;
		return -1; //���޸þ����򷵻�-1
}

//��ӡͼ���ڽӾ���
int printmatrix(mgraph G)
{
	int i,j;
	printf("��Ӧ�ľ���Ϊ��\n");
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
		printf("��1������һ��,��0�˳�����");
		scanf("%d",&x);
		if( x == 1 )
			return 1;
		else if( x == 0 ){
			exit(0);
		}
		else
			printf("����������������룺\n");
	}
}

//�����·�������������㷨
void shortestpath_Floyd(mgraph *G)
{  
	int v,u,i,w,k,j,flag=1,p[10][10][10],D[10][10];//D·��
 
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
	 printf("�������������:");
	 scanf("%d",&k);
	 printf("������Ŀ�ĵصı��:\n");
	 scanf("%d",&j);
	 if(k<0 || k>G->vernum || j<0 || j>G->vernum)
	 {
		 printf("�����Ų�����!����������������Ŀ�ĵصı��:");
		 printf("�������������:");
		 scanf("%d",&k);
		 printf("������Ŀ�ĵصı��:\n");
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
	 printf(" ��·�߳�%dm\n",D[k][j]);
}

//��������������·��
void Allpath(mgraph *G)
{
	int v,w,k,j,flag=1,p[10][10],D[10][10];
	while(flag)
	{
		printf("������������Ŀ�ĵصı��:\n");
		printf("�������������:");
		scanf("%d",&k);
		printf("������Ŀ�ĵصı��:");
		scanf("%d",&j);
		if(k<0||k>G->vernum||j<0||j>G->vernum)
		 {
			printf("�����Ų�����!����������������Ŀ�ĵصı��:\n");
			printf("�������������:\n");
			scanf("%d",&k);
			printf("������Ŀ�ĵصı��:\n");
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
			printf("��·�߳�%d\n",D[k][w]+D[w][j]);
		}
     for(w=0;w<G->vernum;w++)
		 if(p[k][w]==1&&p[w][j]==1) 
			{
				printf("%s",G->vexs[k].name);
				printf("-->");
				printf("%s",G->vexs[w].name);
				printf("-->");
				printf("%s",G->vexs[j].name);
				printf(" ��·�߳�%d\n",D[k][w]+D[w][j]);
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
				 printf(" ��·�߳�%d\n",D[k][v]+D[w][j]+D[v][w]);
			 }
}

//��ʾ������Ϣ����ʾ������Ϣƽ��ͼ
int displaycampus(mgraph G)
{
	int i;
	printf("������\t\t��������\t\t������\t\t\n");
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
		printf("��1������һ��,��0�˳�����");
		scanf("%d",&x);
		if( x == 1 )
			return 1;
		else if( x == 0 ){
			exit(0);
		}
		else
			printf("����������������룺\n");
	}
}	

//��������ͼ���ڽӾ���
int creatgraph(mgraph &G)
{
	int i,n,m,distance,v0,v1;
	printf("����������Ӧ�Ķ�����:");
    scanf("%d",&G.vernum);
	printf("����������Ӧ�ı���:");
	scanf("%d",&G.arcnum);
	for(i=0;i<G.vernum;i++)
	{
		printf("�����뾰���ţ�");
	    scanf("%d",&G.vexs[i].position);
        printf("�����뾰�����ƣ�");
		scanf("%s",G.vexs[i].name);
        printf("�����뾰���飺");
        scanf("%s",G.vexs[i].introduction);	
	}
	for(i=0;i<G.vernum;i++)
		for(int j=0;j<G.vernum;j++)
			G.arcs[i][j].adj=0;
	for(i=0;i<G.arcnum;i++)
	{
		printf("�����[%d]���ߵ������:",i);
        scanf("%d",&v0);
		printf("�����[%d]���ߵ��յ���:",i);
        scanf("%d",&v1);
		printf("�����[%d]���ߵĳ��ȱ��:",i);
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

//ɾ��������Ϣ
int DeleteVertex(mgraph &G)
{
	int i,j,v,m;
	printf("������Ҫɾ���ľ�����:");
	scanf("%d",&v);
	m=locatevex(G,v);
	int flag=1;
	while(flag)
	{
		if(m<0)
		{
			printf("�޴˾��㣬����������:");
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
	for(i=m;i<G.vernum;i++)//ɾ����
		for(j=0;j<G.vernum;j++)
			G.arcs[i][j]=G.arcs[i+1][j];
   for(i=m;i<G.vernum;i++)//ɾ����
	   for(j=0;j<G.vernum;j++)
           G.arcs[j][i]=G.arcs[j][i+1];
   G.vernum--;
   displaycampus(G);
   printmatrix(G);
   return 1;
}

//ɾ��ͼһ��·����Ϣ
int  DeleteplanArc(mgraph &G)
{
	int i,j,v0,v1;
	int flag=1;
	while(flag)
	 {
		printf("������Ҫɾ����һ���߶�Ӧ������������:\n");
		scanf("%d",v0);
		scanf("%d",v1);
		if(v0<0||v0>G.vernum||v0<0||v1>G.vernum)
		{
		  printf("�����Ų�����!����������Ҫɾ����һ���߶�Ӧ������������:");
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

//���Ӿ���
int enverx(mgraph &G)
{
	int i;
	printf("������Ҫ��ӵľ������Ϣ��\n");
	printf("�����뾰����:");
    scanf("%d",&G.vexs[G.vernum].position);
	printf("�����뾰������:");
    scanf("%s",&G.vexs[G.vernum].name);
	printf("�����뾰����:");
    scanf("%s",&G.vexs[G.vernum].introduction);
	printf("\n");
	G.vernum++;
	for(i=0;i<G.vernum;i++)
		G.arcs[i][G.vernum-1].adj=G.arcs[i][G.vernum-1].adj=A;
	displaycampus(G);
	printmatrix(G);
	return 1;
}

//����·��
int enarc(mgraph &G)
{
	int v0,v1,distance;
	printf("����������·������ʼ����:");
    scanf("%d",&v0);
	printf("����������·�����յ���:");
    scanf("%d",&v1);
	printf("����������·������");
	scanf("%s",&distance);
	G.arcs[v0][v1].adj=G.arcs[v1][v0].adj=distance;
	displaycampus(G);
	printmatrix(G);
	return 1;
}

//������Ϣ��ѯ
void seaabout(mgraph G)
{
	int n,flag=1;
	printf("������Ҫ��ѯ�ľ����ţ�");
	scanf("%d",&n);
	while(flag)
	{
		if(n<0||n>G.vernum)
		{
			printf("�þ��㲻���ڣ����������룺");
     		scanf("%d",&n);
		}
		else
		{
			printf("������\t\t��������\t\t������\t\t\n");
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

//���¾������Ϣ
int newgraph(mgraph &G)
{
	int n,m,t,i;
	printf("������Ҫ���µľ�������");
	scanf("%d",&n);
	while(n<0||n>G.vernum)
	{
		printf("�þ��㲻���ڣ����������룺");
		scanf("%d",&n);
	}
	for(i=0;i<n;i++)//�޸ľ�����Ϣ
	{
		printf("���뾰��ı�ţ�");
		scanf("%d",&m);
		t=locatevex(G,m);
		printf("���뾰������ƣ�");
		scanf("%s",&G.vexs[t].name);
		printf("���뾰��ļ�飺");
		scanf("%s",&G.vexs[t].introduction);
	}
	printf("������Ҫ���ĵı�����");
	scanf("%d",&n);
	int distance,v0,v1;
	while(n<0||n>G.arcnum)
	{
		printf("��·�������ڣ����������룺");
		scanf("%d",&n);
	}
	printf("������µ�·������Ϣ��");
	for(i=0;i<n;i++)//�޸�·����Ϣ
	{
		printf("��ʼ������v0:");
        scanf("%d",&v0);
		printf("�յ㾰����v1:");
        scanf("%d",&v1);
		printf("·������:");
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

//����ͼ����Ϣ
int changegraph(mgraph G)
{
	int i;
    printf("1�����½�ͼ        2��ɾ�����  \n");
	printf("3��ɾ����          4�����ӽ��  \n");
	printf("5�����ӱ�          6������ͼ��Ϣ\n");
	printf("7����ӡ�ڽӾ���    8�����س���  \n");
	while(1)
	{
		printf("������Ҫ���еĲ���:");
	    scanf("%d",&i);
		switch(i)
		{
		case 1:
			printf("���½�ͼ:\n");
			creatgraph(g);
			break;
		case 2:
			printf("ɾ�����:\n");
			DeleteVertex(g);
			break;
		case 3:
			printf("ɾ����:\n");
			DeleteplanArc(g);
			break;
		case 4:
			printf("���ӽ��:\n");
			enverx(g);
			break;
		case 5:
			printf("���ӱ�:\n");
			enarc(g);
			break;
		case 6:
			printf("����ͼ��Ϣ:\n");
			newgraph(g);
			break;
		case 7:
			printf("��ӡ�ڽӾ���:\n");
			printmatrix(g);
			break;
		case 8:
			printf("���س���:\n");
			return 1;
		}
	}
	return 1;
	
}


void main()
{
	initgraph(g);

	printf("ѧУ�ſ���\n");
		displaycampus(g);

	while(1)
	{
		printf("\n");
		printf("                                     ��ӭ����DGUT                               \n");
		printf("                        1��ѧУ�������            2����ӡ�ڽӾ���              \n");
		printf("                        3����ѯ��������·��      4����ѯ������Ϣ              \n");
		printf("                        5���ı�ͼ����Ϣ            6����ѯ��������·��        \n");
		printf("                        7���˳�����                                             \n");

		printf("��������Ҫ���еĲ���:");
		int k;
	    scanf("%d",&k);
		switch(k)
		{
		case 1:
			printf("ѧУ�������:\n");
			displaycampus(g);
			break;
	    case 2:
			printf("��ӡ�ڽӾ���:\n");
			printmatrix(g);
			break;
		case 3:
			printf("��ѯ��������·��:\n");
			displaycampus(g);
			shortestpath_Floyd(&g);
			break;
		case 4:
			printf("��ѯ������Ϣ:\n");
			seaabout(g);
			break;
		case 5:
			printf("�ı�ͼ����Ϣ:\n");
			changegraph(g);
			break;
		case 6:
			printf("��ѯ��������·��:\n");
			Allpath(&g);
			break;
		case 7:
			printf("�˳�����\n");
			//flag=0;
			exit(0);
			break;
		default:
			break;
		}
	}
}
