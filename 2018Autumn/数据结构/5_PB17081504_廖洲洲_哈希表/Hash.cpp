#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<process.h>

int *HT1;
int len,p;
int Search(int data,int *times);//���ң��ɹ����ص�ַ��ʧ�ܷ���-1
void CreatHash1();
void CreatHash1(){
	int *num,Hkey,Hkey2,d;
	char file[100];
	FILE  *fp;
	//���ݵ�����
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
	//��ϣ��Ľ���
	HT1=(int *)malloc(p*sizeof(int));
	for(int i=0;i<p;i++)
		HT1[i]=-1;
	for(int i=0;i<len;i++){
		Hkey=num[i]%p;
		if(HT1[Hkey]==-1)
			HT1[Hkey]=num[i];
		else{
			for(d=2,Hkey2=(Hkey+1)%p;HT1[Hkey2]!=-1&&d<=p-1;d++)
				Hkey2=(Hkey+d)%p;
			HT1[Hkey2]=num[i];
		}
	}
	printf("\n��ϣ��ĵ�ַ�� ");
	for(int i=0;i<p;i++)
		printf("%d\t",i);
	printf("\n���еĹؼ��֣� ");
	for(int i=0;i<p;i++)
		printf("%d\t",HT1[i]);
}

int Search(int data,int *times){
	int Hkey,Hkey2,d;
	*times=1;

	Hkey=data%p;
	if(HT1[Hkey]==data){
		*times=1;
		return Hkey;
	}
	else{
		for(d=2,Hkey2=(Hkey+1)%p;HT1[Hkey2]!=data&&HT1[Hkey2]!=-1;d++)
			Hkey2=(Hkey+d)%p;
		*times=d;
		if(HT1[Hkey2]==-1){
			return -1;
			}
		else if(HT1[Hkey2]==data){
			return Hkey2;
		}
	}

}
main() {
	int times,total1=0,total2=0,j,flag,data;
	float ave1,ave2;
	CreatHash1();
	printf("\n�ɹ����Ҵ����� ");
	for(int i=0;i<p;i++){
		if(HT1[i]==-1)
			printf("0\t");
		else{
			Search(HT1[i],&times);
			printf("%d\t",times);
			total1=total1+times;
		}
	}
	printf("\nʧ�ܲ��Ҵ����� ");
	for(int i=0;i<p;i++){
		if(HT1[i]==-1){
			printf("1\t");\
			total2++;
		}
		else{
			for( j=i+1;j<p&&HT1[j]!=-1;j++);
			printf("%d\t",j-i+1);
			total2=total2+(j-i+1);
		}
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
			printf("���ݵ�ַ:%d   ���Ҵ�����%d\n",j,times);
		printf("���ҡ���1���˳�����0\n");
		scanf("%d",&flag);
	}
}

