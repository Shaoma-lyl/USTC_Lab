#define N 500000
#define NUM_THREADS 1
#include<stdio.h>
#include<omp.h>
#include<math.h>


int isPrime(int num) {
	int i, flag = 1;
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
	int i;
	double startTime, endTime;
	int localSum = 0, sum=0;
	startTime = omp_get_wtime();
	omp_set_num_threads(NUM_THREADS);
#pragma omp parallel private(i,localSum)
	{
	int id = omp_get_thread_num();
	for (i = id,localSum=0; i <= N; i = i + NUM_THREADS) {
		localSum += isPrime(i);
	}
#pragma omp critical
	sum += localSum;
	}
	endTime = omp_get_wtime();
	//�Ƴ�0��1��0��1�Ȳ�������Ҳ���Ǻ���
	printf("��������Ϊ:%d\n", sum - 2);
	printf("����ʱ��:%f\n", endTime - startTime);
	
	return 0;

}