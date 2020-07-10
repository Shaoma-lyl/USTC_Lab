#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<process.h>
typedef struct Chain{
	int data;
	Chain *next;
}Chain;
Chain *ChainHash;
int len,p;
int Search(int data,int *times);//���ң��ɹ����ص�ַ��ʧ�ܷ���-1
void CreatHash1();

void CreatHash1(){
	int *num,Hkey;
	Chain *chain;
	char file[100];
	FILE  *fp;
	//��������
	printf("����������ļ�����\n");
	scanf("%s",file);
	if ((fp = fopen(file, "r")) == NULL) {
		printf("can't open this file!\n ");
		exit(0);
	}
	fscanf(fp,"%d",&len);
	num=(int *)malloc(len*sizeof(int));
	for(int i=0;i<len;i++)
		fscanf(fp,"%d",&num[i]);
	printf("�����������Ϊ��\n");
	for(int i=0;i<len;i++)
		printf("%d  ",num[i]);
	fscanf(fp,"%d",&p);
	//��ʼ����
	ChainHash=(Chain *)malloc(p*sizeof(Chain));
	for(int i=0;i<p;i++)
		ChainHash[i].next=NULL;
	for(int i=0;i<len;i++){
		Hkey=num[i]%p;
		chain=(Chain *)malloc(sizeof(Chain));
		chain->data=num[i];
		chain->next=ChainHash[Hkey].next;
		ChainHash[Hkey].next=chain;
	}
	printf("\n��ַ\t");
	printf("�ؼ���");
	for(int i=0;i<p;i++){
		printf("\n%d",i);
		for(chain=ChainHash[i].next;chain;chain=chain->next)
			printf("\t%d",chain->data);
	}
}

int Search(int data,int *times){
	int Hkey;
	Chain *chain;
	*times=1;

	Hkey=data%p;
	for(chain=ChainHash[Hkey].next;chain&&chain->data!=data;chain=chain->next)
		(*times)++;
	if(chain==NULL)
		return -1;
	else
		return Hkey;
}

main() {
	int times,total1=0,total2=0,j=1,flag,data;
	float ave1,ave2;
	Chain *chain;
	CreatHash1();
	printf("\n�ɹ����Ҵ�����\n ");
	for(int i=0;i<p;i++){
		if(ChainHash[i].next==NULL)
			printf("\t0");
		else
			for(chain=ChainHash[i].next;chain;chain=chain->next){
				Search(chain->data,&times);
				total1=total1+times;
				printf("\t%d",times);
				}
		printf("\n");
	}
	printf("\nʧ�ܲ��Ҵ�����\n ");
	for(int i=0;i<p;i++){
		j=1;
		for(chain=ChainHash[i].next;chain;chain=chain->next)
			j++;
		printf("%d\t",j);
		total2=total2+j;
		}

	ave1=(float)total1/len;
	ave2=(float)total2/p;
	printf("\n���ҳɹ���ƽ�����ҳ��ȣ� %f",ave1);
	printf("\n����ʧ�ܵ�ƽ�����ҳ��ȣ� %f",ave2);
	printf("\n��ϣ��������Ϣ�����ɣ������룺���ҡ���1���˳�����0\n");
	scanf("%d",&flag);
	while(flag==1){
		printf("��������ҵ����ݣ�\n");
		scanf("%d",&data);
		j=Search(data,&times);
		if(j==-1)
			printf("�����޴����ݣ�\n");
		else
			printf("���ݵ�ַ:%d->%d   ���Ҵ�����%d\n",j,times,times);
		printf("���ҡ���1���˳�����0\n");
		scanf("%d",&flag);
	}
}

