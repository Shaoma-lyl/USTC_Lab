#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<process.h>

#define max 100000
int *vexs;//��������
int **arc;//�ڽӾ���
int vexnum;//������
int startvex,endvex;
void CreatGraph(){

	printf("�����붥������\n");
	scanf("%d",&vexnum);

	arc=(int **)malloc(vexnum*sizeof(int *));
	for(int i=0;i<vexnum;i++)
		arc[i]=(int *)malloc(vexnum*sizeof(int));

	printf("������·��:\n");
	
	for(int i=0;i<vexnum;i++)
		for(int j=0;j<vexnum;j++)
			scanf("%d",&arc[i][j]);

}
void ShortestPath(){
	int *final,*D;
	int **path;
	final=(int *)malloc(vexnum*sizeof(int));  //final[i]Ϊ1��˵������ô�startvex��vi�����·��
	D=(int *)malloc(vexnum*sizeof(int));      //D[i]�д洢�˴�startvex��vi��·������
	
	path=(int **)malloc(vexnum*sizeof(int *));
	for(int i=0;i<vexnum;i++)
		path[i]=(int *)malloc(vexnum*sizeof(int));//path[v]�洢�˴���㵽v�����·��

	for(int i=0;i<vexnum;i++){
		final[i]=0;
		if(i>startvex)
			D[i]=arc[startvex][i];
		else
			D[i]=arc[i][startvex];
		for(int w=1;w<vexnum;w++)
			path[i][w]=-1;
//		if(D[i]>=0){
//			path[i][startvex]=1;
//			path[i][i]=1;
		path[i][0]=startvex;

	}//for
	int w,v,min;int j;
	D[startvex]=0;final[startvex]=1;  //��ʼʱ��vo����S
	int flag=0;//��ʾδ�ҵ����յ��·��
	//ÿ�����startvex��ĳ��v��������·����������S��
	for(int i=1;i<vexnum&&flag==0;i++){
		min = max;
		for(w=0;w<vexnum;w++){  //�ҳ���ǰ��֪S�����������ĵ�
			if(!final[w])
				if(D[w]>0&&D[w]<min){
					v=w;
					min=D[w];
				}
		}
	final[v]=1;
	for( j=0;path[v][j]!=-1;j++);
	path[v][j]=v;
	int m,n;
	for(w=0;w<vexnum;w++){//�������·��
		if(v<w){
			m=v;n=w;
		}
		else{
			m=w;n=v;
		}
		if(!final[w]&&arc[m][n]>0&& ( (min+arc[m][n])<D[w] || D[w]<0 ) ) {  //��������и��̵�·�����ȣ��޸�D[w]
			D[w]=min+arc[m][n];
		//	for(int j=0;j<vexnum;j++)
		//		path[w][j]=path[v][j];
		//	path[w][w]=1;
			for(int j=0;path[v][j]!=-1;j++)
				path[w][j]=path[v][j];
		}

	}
	if(v==endvex)
		flag=1;
	}
	printf("���·��������ɣ�\n");
	printf("����Ϊ��%d\n",D[endvex]);
	printf("·��Ϊ��\n");
	for(int j=0;path[endvex][j]!=-1;j++)
		printf("%d  ",path[endvex][j]+1);

}

main(){
	int start,end;
	int flag;

	CreatGraph();
	do{
	printf("�����������յ㣺\n");
	scanf("%d%d",&start,&end);
	startvex=start-1;
	endvex=end-1;
	ShortestPath();
	printf("\n��������1���˳�����0��\n");
	scanf("%d",&flag);
	}while(flag);
	

}
