#define N 500000
#include<stdio.h>
#include<mpi.h>
#include<math.h>

int isPrime(int num) {
	int i,flag=1;
	int max = int(sqrt(num));
	for (i = 2; i <= max; i++) {
		if (num%i == 0) {
			flag = 0;
			break;
		}
	}
	return flag;
}

int main(int argc, char *argv[])

{
	int i, rank, size;
	double startTime, endTime;
	int localSum = 0, sum;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	startTime = MPI_Wtime();
	for (i = rank; i <= N; i = i + size) {
		localSum += isPrime(i);
	}
	MPI_Reduce(&localSum, &sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	if (rank == 0) {
		//�Ƴ�0��1��0��1�Ȳ�������Ҳ���Ǻ���
		printf("��������Ϊ:%d\n", sum-2);
		endTime = MPI_Wtime();
		printf("����ʱ��:%fs\n", endTime - startTime);
	}
	MPI_Finalize();
	return 0;

}