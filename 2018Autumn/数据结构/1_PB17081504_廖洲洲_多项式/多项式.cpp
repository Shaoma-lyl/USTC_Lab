#include<stdio.h>
#include<stdlib.h>
#include<math.h>
struct Polyn {
	float coef; //ϵ��
	int expn;   //ָ��
	struct Polyn *next;
};
void CreatPolyn(struct Polyn *p,int m);//����
void AddPolyn(struct Polyn *pa,struct Polyn *pb);//���
void SubtractPolyn(struct Polyn *pa,struct Polyn *pb);//���
struct Polyn *MutilplyPolyn(struct Polyn *pa,struct Polyn *pb);//���
void Print(struct Polyn *p);//��ӡ
struct Polyn *Mutilply(struct Polyn *pa,struct Polyn *pb);//pa��һ������ʽ��ͷָ�룬pb��ֻ��һ��ָ�룬�京����ʽ��һ��
void DestroyPolyn(struct Polyn *pa);//����
void ClearPolyn(struct Polyn *pa);//���
void DPolyn(struct Polyn *pa);//΢��
int Df(int m,int n);//������m*(m-1)*(m-2)...*(m-n+1)
void DefPolyn(struct Polyn *pa,float m,float n);//������
float EvaluationPolyn(struct Polyn *pa,float m);//��ֵ
struct Polyn * IndefPolyn(struct Polyn *pa);//��������
main() {
	int m,flag;float x;float a,b,f;
	struct Polyn *pa,*pb,*la;
	printf("������һ������ʽ������������������\n");
	scanf("%d",&m);
	pa=(struct Polyn *)malloc(sizeof(struct Polyn));
	CreatPolyn(pa,m);
	printf("�����ڶ�������ʽ������������������\n");
	scanf("%d",&m);
	pb=(struct Polyn *)malloc(sizeof(struct Polyn));
	CreatPolyn(pb,m);
	printf("\t���ܱ�\t\n����ʽ���--1\n����ʽ���--2\n����ʽ���--3\n���ٶ���ʽ--4\n��ն���ʽ--5\n�󵼶���ʽ--6\n");
	printf("��������--7\n��ֵ--8\n������--9\n");
	printf("���������ѡ��\n");
	scanf("%d",&flag);
	
	if(flag==1){
		AddPolyn(pa,pb);		printf("�ӷ����\n");
		Print(pa);  }
 	else if(flag==2){
		SubtractPolyn(pa,pb);	printf("�������\n");
		Print(pa);  }
	else if(flag==3) {
		la=MutilplyPolyn(pa,pb);	printf("�˷����\n");
		Print(la);
		}
	else if(flag==4){
		printf("Destroy First--1,Destroy Second--2\n");
		scanf("%d",&flag);
		if(flag==1) DestroyPolyn(pa);
		else if (flag==2) DestroyPolyn(pb);
		else printf("ERROR!");
	}
	else if(flag==5){
		printf("Clear First--1,Clear Second--2\n");
		scanf("%d",&flag);
		if(flag==1) ClearPolyn(pa);
		else if (flag==2) ClearPolyn(pb);
		else printf("ERROR!");
	}
	else if(flag==6){
		printf("�� First--1,�� Second--2\n");
		scanf("%d",&flag);
		if(flag==1)
			DPolyn(pa);
		else if (flag==2)
			DPolyn(pb);
		else printf("ERROR!");
		
	}
	else if(flag==7){
		printf("�������� First--1,�������� Second--2\n");
		scanf("%d",&flag);
		if(flag==1) {
			la=IndefPolyn(pa);	printf("�������ֻ�����ɣ�\n");
			Print(la);}
		else if (flag==2) {
			la=IndefPolyn(pb);	printf("�������ֻ�����ɣ�\n");
			Print(la);}
		else printf("ERROR!");
	}
	else if(flag==8){
		printf(" ����First--1, ���� Second--2\n");
		scanf("%d",&flag);
		printf("������Ҫ�����X��\n");
		scanf("%f",&x);
		if(flag==1) {
			f=EvaluationPolyn(pa,x);
			printf("������ɣ�\n");
			printf("P(x)=%f\n",f);}
		else if (flag==2) {
			f=EvaluationPolyn(pb,x);
			printf("������ɣ�\n");
			printf("P(x)=%f\n",f);}
		else printf("ERROR!");
	}
	else if(flag==9){
		printf("�����֣�First --1,Second --2\n");
		scanf("%d",&flag);
		printf("������������޺����ޣ�\n");
		scanf("%f%f",&a,&b);
		if(flag==1)
			DefPolyn(pa,a,b);
		else if(flag==2)
			DefPolyn(pb,a,b);
		else
			printf("ERROR\n");
	}
		else
		printf("ERROR\n");

}
void Print(struct Polyn *p) {
	printf("�洢�Ķ���ʽΪ��\nP(x)=");
	struct Polyn *h=p->next;
	if(h==NULL) printf("0");
	while(h){
		printf("%fx^%d",h->coef,h->expn);
		h=h->next;
		if(h){
			if(h->coef>0)
				printf("+");}
	}
	printf("\n");
}
void CreatPolyn(struct Polyn *p,int m){
	p->coef=0;p->expn=-1;p->next=NULL;
	printf("����������ÿһ���ϵ����ָ�������һ�������Իس�������\n");
	int i;
	struct Polyn *q;
	struct Polyn *h=p;
	for(i=1;i<=m;i++) {
		q=(struct Polyn *)malloc(sizeof(struct Polyn));
		scanf("%f%d",&q->coef,&q->expn);
		h->next=q;
		h=q;
	}
	h->next=NULL;
	printf("�����ɹ�\n");
	Print(p);
}
void AddPolyn(struct Polyn *pa,struct Polyn *pb){
	struct Polyn *p=pa->next;
	struct Polyn *q=pb->next;
	struct Polyn *h=pa,*x;
	while(p&&q) {
		if(p->expn < q->expn) {
			h->next=p;
			h=p;
			p=p->next;
			}
		else if(p->expn > q->expn) {
			h->next=q;
			h=q;
			q=q->next;
		}
		else {
			float sum=p->coef+q->coef;
			if(sum!=0){
			h->next=p;
			h=p;
			p=p->next;
			x=q;
			q=q->next;
			h->coef=sum;
			free(x);
			}
			else{
			x=p;
			p=p->next;
			free(x);
			x=q;
			q=q->next;
			free(x);
			h->next=p;
			}
		}
	}
	h->next=p?p:q;

}

void SubtractPolyn(struct Polyn *pa,struct Polyn *pb) {
	struct Polyn *p=pa->next;
	struct Polyn *q=pb->next;
	struct Polyn *h=pa,*x;
	while(p&&q) {
		if(p->expn < q->expn) {
			h->next=p;
			h=p;
			p=p->next;
			}
		else if(p->expn > q->expn) {
			h->next=q;
			q->coef=-q->coef;
			h=q;q=q->next;
		}
		else {
			float sum=p->coef-q->coef;
			if(sum!=0){
			h->next=p;
			h=p;
			p=p->next;
			x=q;
			q=q->next;
			h->coef=sum;free(x);
			}
			else{
			x=p;
			p=p->next;
			free(x);
			x=q;
			q=q->next;
			free(x);
			h->next=p;
			}
		}
	}
	if(p)
		h->next=p;
	else{
		x=q;
		while(q){
			q->coef=-q->coef;
			q=q->next;
		}
		h->next=x;
	}
}
struct Polyn *Mutilply(struct Polyn *pa,struct Polyn *pb){//����������ʽpa����pb��pbֻ��һ������ʽ
	struct Polyn *h,*p=pa->next,*q,*la;
	la=h=(struct Polyn *)malloc(sizeof(struct Polyn));
	h->coef=0;h->expn=-1;h->next=NULL;
	while(p){
		q=(struct Polyn *)malloc(sizeof(struct Polyn));
		q->coef=p->coef*pb->coef;
		q->expn=p->expn+pb->expn;
		p=p->next;
		h->next=q;h=q;
	}
	h->next=NULL;
	return la;
}
struct Polyn *MutilplyPolyn(struct Polyn *pa,struct Polyn *pb) {
	struct Polyn *la,*p,*q=pb->next,*Cpa;//la�洢���
	int i;
	la=(struct Polyn *)malloc(sizeof(Polyn));la->coef=0;la->expn=-1;la->next=NULL;
	while(q){
		Cpa=Mutilply(pa,q);
		AddPolyn(la,Cpa);
		q=q->next;
		}
	return la;

}
void DestroyPolyn(struct Polyn *pa){
	struct Polyn *x;
	while(pa){
	x=pa;
	pa=pa->next;
	free(x);
		}
	printf("����ʽ�����٣�\n");
}
void ClearPolyn(struct Polyn *pa){
	struct Polyn *h=pa->next;
	while(h){
		h->coef=0;
		h->expn=0;
		h=h->next;
	}
	printf("�����ɣ�Ŀǰ����Ķ���ʽΪ��\n");
	Print(pa);
}
void DPolyn(struct Polyn *pa){
	struct Polyn *h=pa->next,*x,*p=NULL;
	printf("�������󵼽���\n");
	int n;
	scanf("%d",&n);
	if(n<0)
		printf("ERROR!\n");
	while(h&&h->expn<0){
		p=h;h=h->next;
	}
	while(h&&h->expn<n){
		x=h;h=h->next;free(x);
	}
	if(p==NULL)
		pa->next=h;
	else
		p->next=h;
	h=pa->next;
	while(h){
		h->coef=h->coef*Df(h->expn,n);
		h->expn=h->expn-n;
		h=h->next;
	}
	printf("΢����ɣ�΢�ֺ�\n");
	Print(pa);
}
int Df(int m,int n){
	int i;
	int j=m;
	if(!n)
		return 1;
	for(i=1;i<n;i++)
		j=j*(m-i);
 	return j;
}
struct Polyn * IndefPolyn(struct Polyn *pa){
	struct Polyn *p=pa->next;
	while(p){
		p->expn=p->expn+1;
		p->coef=p->coef/p->expn;
		p=p->next;
	}
	return pa;

}
float EvaluationPolyn(struct Polyn *pa,float m){
	float f=0;
	struct Polyn *p=pa->next;
	while(p){
		f+=p->coef*(pow(m,p->expn));
		p=p->next;
	}
	return f;

}
void DefPolyn(struct Polyn *pa,float m,float n){//mΪ���ޣ�nΪ����
	struct Polyn *p;
	float f;
	p=IndefPolyn(pa);
	f=EvaluationPolyn(p,m)-EvaluationPolyn(p,n);
	printf("�����ּ�����ɣ�\n");
	printf("���Ϊ��%f\n",f);
}
