#include<stdio.h>
#include<mpi.h>
#include<time.h>
#include<stdlib.h>

#define N 10000000

void quickSort(double *num, int len) {
	//��������
	if (len <= 1) {
		return;
	}
	int i = 0, j = 0;
	double temp;
	double p = num[len - 1];
	for (j = 0; j < len - 1; j++) {
		if (num[j] < p) {
			temp = num[i];
			num[i] = num[j];
			num[j] = temp;
			i = i + 1;
		}
	}
	temp = num[len - 1];
	num[len - 1] = num[i];
	num[i] = temp;
	quickSort(num, i);
	quickSort(num + i + 1, len - i - 1);
}

void merge(double *num,int p,int q,int r) {
	//��������num��num[p]~num[q]����num[q+1]~num[r]���򣬽�num�鲢Ϊһ����������
	int n1 = q - p + 1;
	int n2 = r - q;
	int len = n1 + n2;
	int i, j, k;
	double *temp = (double *)malloc(sizeof(double)*len);
	for (i = 0; i < len; i++) {
		temp[i] = num[i];
	}
	i = p;
	j = q + 1;
	for (k = 0; k < len&&i <=q && j <=r; k++) {
		if (temp[i] < temp[j]) {
			num[k] = temp[i];
			i++;
		}
		else {
			num[k] = temp[j];
			j++;
		}
	}
	if (i == q+1) {
		for (; k < len; k++) {
			num[k] = temp[j];
			j++;
		}
		return;
	}
	for (; k < len; k++) {
		num[k] = temp[i];
		i++;
	}
	return;
}

int main(int argc, char ** argv) {
	int rank, size;
	int i,j;
	int partition;
	double startTime, endTime;
	double *num = (double *)malloc(sizeof(double)*N);
	srand(time(NULL));
	//�����������
	for (i = 0; i < N; i++) {
		num[i] = rand() * 10000 / RAND_MAX;
	}
	/*printf("Before sort:\n");
	for (i = 0; i < N; i++) {
		printf("%.2f  ", num[i]);
	}
	printf("\n");*/
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	/*if (rank == 0) {
		printf("Before sort:\n");
		for (i = 0; i < N; i++) {
			printf("%.2f  ", num[i]);
		}
		printf("\n");
	}*/
	startTime = MPI_Wtime();
	//���Ȼ��֣������������ݾ���Ϊsize�ݣ�����rank�����±�rank*partition~(rank+1)*partiton-1������
	partition = N / size;
	int start = rank*partition;
	//�ֲ�����ʹ�ÿ�������Ա������ݽ�������
	quickSort(num + rank*partition, partition);
	//ѡȡ������������õ���������ѡȡsize������,�����͸�0�Ž��̣�0�Ž���ʹ��Gather�ռ�����
	double *cbuffer = (double *)malloc(sizeof(double)*size);
	int space = partition / size;
	for (i = 0; i < size; i++) {
		cbuffer[i] = (num + rank*partition)[i*space];
	}
	double *pivotbuffer = (double *)malloc(sizeof(double)*size*size);
	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Gather(cbuffer, size, MPI_DOUBLE, pivotbuffer, size, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	//�������򣬶�ѡȡ��size*size���������ж�ι鲢����
	if (rank == 0) {
		/*for (i = 0; i < size*size; i++) {
			printf("%.2f  ", pivotbuffer[i]);
		}*/
		for (i = 1; i < size; i++) {
			merge(pivotbuffer, 0, i*size-1, (i + 1)*size-1);
		}
		/*printf("\n");
		for (i = 0; i < size*size; i++) {
			printf("%.2f  ", pivotbuffer[i]);
		}*/
		//ѡ��size-1����Ԫ
		for (i = 1; i < size; i++) {
			cbuffer[i] = pivotbuffer[i*size - 1];
		}
	}
	//ʹ�ù㲥����Ԫ���͸���������
	MPI_Bcast(cbuffer, size, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	/*printf("\n");
	for (i = 0; i < size; i++) {
		printf("%.2f  ", cbuffer[i]);
	}*/
	//��Ԫ���֣�������Ԫ���������ݻ���Ϊsize��
	int *classStart = (int *)malloc(sizeof(int)*size);
	int *classLength = (int *)malloc(sizeof(int)*size);
	for (i = 0; i < size; i++) {
		classStart[i] = 0;
		classLength[i] = 0;
	}
	int index = 0;
	j = 1;
	for (i = 0; i < partition; i ++ ) {
		if (j<size&& num[start + i] > cbuffer[j]) {
			classStart[j] = i;
			j++;
			index++;
		}
		classLength[index]++;
	}
	/*printf("\n");
	for (i = 0; i < size; i++) {
		printf("@%d@start:%d,length:%d\n", rank,classStart[i], classLength[i]);
	}
	printf("@%d@\n", rank);
	for (i = 0; i < partition; i++) {
		printf("%.2f@%d@  ", num[start + i],rank);
	}*/
	//���ո��γ���
	int *recvLength = (int *)malloc(sizeof(int)*size);
	int *recvStart = (int *)malloc(sizeof(int)*size);
	for (i = 0; i < size; i++) {
		MPI_Gather(classLength + i, 1, MPI_INT, recvLength, 1, MPI_INT, i, MPI_COMM_WORLD);
	}
	recvStart[0] = 0;
	//������յĸ��ε���ʼ��ַ
	for (i = 1; i < size; i++) {
		recvStart[i] = recvStart[i - 1] + recvLength[i-1];
	}
	/*printf("\n");
	for (i = 0; i < size; i++) {
		printf("@%d@recvstart:%d,recvlength:%d\n", rank, recvStart[i], recvLength[i]);
	}*/
	//ȫ�ֽ���������������������ΰ��κŽ�������Ӧ�Ĵ�������
	double *recvBuffer = (double *)malloc(sizeof(double)*N);
	for (i = 0; i < size; i++) {
		MPI_Gatherv(num + start + classStart[i], classLength[i], MPI_DOUBLE, recvBuffer , recvLength, recvStart, MPI_DOUBLE, i, MPI_COMM_WORLD);
	}
	MPI_Barrier(MPI_COMM_WORLD);
	//�鲢���򣬸����������յ���Ԫ�ؽ��й鲢����
	/*for (i = 0; i < N; i++) {
		printf("%.2f  ", recvBuffer[i]);
	}*/
	for (i = 1; i < size; i++) {
		merge(recvBuffer, 0, recvStart[i] - 1, recvStart[i]+recvLength[i]-1);
	}
	
	//�ռ���0�Ž����ռ������̴��������
	int len = 0;
	for (i = 0; i < size; i++) {
		len += recvLength[i];
	}
	/*for (i = 0; i < len; i++) {
		printf("__%.2f__  ", recvBuffer[i]);
	}*/
	//���������̹鲢��������ݳ��ȷ���0�Ž���
	MPI_Gather(&len, 1, MPI_INT, recvLength, 1, MPI_INT, 0, MPI_COMM_WORLD);
	recvStart[0] = 0;
	for (i = 1; i < size; i++) {
		recvStart[i] = recvStart[i - 1] + recvLength[i-1];
	}
	MPI_Gatherv(recvBuffer, len, MPI_DOUBLE, num, recvLength, recvStart, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	endTime = MPI_Wtime();
	if (rank == 0) {
		/*printf("After sort:\n");
		for (i = 0; i < N; i++) {
			printf("%.2f  ", num[i]);
		}*/
		printf("\n\nTime:%f\n", endTime - startTime);
	}
	MPI_Finalize();
	return 0;
}