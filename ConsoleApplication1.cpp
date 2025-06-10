#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<Windows.h>
#define MaxWindow 10//窗口最大值
long long IntoBinary(long long n, int num[], long long k) {//将指数转为二进制
	int i = 0;
	while (n > 0) {
		num[i] = n % 2;
		n = n / 2;
		i++;
	}
	k = i;//k表示二进制位数
	return k;
}
long long primary(int a, int b, int m, unsigned long long int result) {//直接进行模幂计算
	//result = pow(a ,b);//% m;
	//result = int(pow(a, b))% m;
	result = pow(a, b);
	result = result % m;
	printf("%llu\n", result);
	return result;
}
long long binary(int a, int b, int m, long long result) {//普通的二进制模幂算法
	if (b == 0) return 1;
	result = 1;
	while (b>0) {
		//if (b & 1) result = (result * a) ;//% m
		if (b & 1) result = (result * a) % m;
		//a = (a * a);//% m;
		a = (a * a)% m;
		b >>= 1;
	}
	printf("%lld\n", result);
	return result;
}
long long SildeWindow(int a,int b,int m, long long result) {//滑动窗口算法
	long long num[10] = {};
	for (int p = 0; p < 10; p++) {
		num[p] = -1;
	}
	long long i = 0;
	long long t = 0;
	long long k = MaxWindow;//窗口最大值
	while (b > 0) {
		num[i] = b % 2;
		b = b / 2;
		i++;
	}//将b转化为二进制
	t = i;//b二进制位数
	//预计算
	long long G[1024] = {0};
	G[0] = 1; G[1] = a; G[2] = a*a;
	long long h = 0;
	h = pow(2, k - 1);
	for (int j = 3; j <= h - 1; j++) {
		//G[2 * j + 1] = G[2 * j - 1] * G[2];
		G[j] = G[j - 1] * a;
	}
	result = 1;
	i = i - 1;
	while (i >= 0) {
		if (num[i] == 0) {
			result = (result*result)%m;
			i = i - 1;//倒序读取，因为数组里的二进制为倒序
		}
		else{
			long long B[MaxWindow] = { -1,-1,-1,-1 };
			//B[0] = 1;
			for (int p = 0; p < MaxWindow; p++) {
				B[p] = -1;
			}
			long long f =0;
			int flag = 0;//标记是否读取到1或者读取结束
			for (int w=i;w>=0&&f<=MaxWindow-1&&flag<2; w--) {//读到1或者等于窗口最大值或者无二进制时停止
				B[f] =num[w];
				//printf("%lld\n", B[f]);
				if (num[w] == 1)flag++;//读取到两次1，flag为2
				f++;
			}
			//printf("%d\n", f);
			long long l = f;//当前截取序列长度
			f = f - 1;
			long long E = 0;
			while (f >= 0) {
				E = E * 2 + B[f];
				//printf("%d\n", E);
				f--;
			}
			//printf("E=%lld\n", E);
			//result = pow(result,(pow(2,(i - l - 1)))) * G[E];
			//result = int(pow(result, (pow(2,l))))%m;
			result = pow(result, (pow(2, l)));
			result = result % m;
			result *= G[E];
			result = result % m;
			i -= l;
		}
	}
	printf("%lld\n", result);
	return result;
}
void test(int a1,int b1,int m1,long long result1) {
	LARGE_INTEGER start_time, end_time, freq;
	double elapsed_time1, elapsed_time2, elapsed_time3;
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&start_time);

	primary(a1, b1, m1, result1);

	QueryPerformanceCounter(&end_time);
	elapsed_time1 = (end_time.QuadPart - start_time.QuadPart) / (double)freq.QuadPart;
	printf("函数执行时间：%.9fs\n", elapsed_time1);
}
int main() {
	int a1 =9;
	int b1 =28;
	int m1 = 13;
	long long result1 = 0;
	test(a1, b1, m1, result1);
	/*LARGE_INTEGER start_time, end_time, freq;
	double elapsed_time1, elapsed_time2, elapsed_time3;
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&start_time);

	primary(a1, b1, m1, result1);

	QueryPerformanceCounter(&end_time);
	elapsed_time1 = (end_time.QuadPart - start_time.QuadPart) / (double)freq.QuadPart;
	printf("函数执行时间：%.9fs\n", elapsed_time1);


	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&start_time);


	binary(a1, b1, m1, result1);

	QueryPerformanceCounter(&end_time);
	elapsed_time2 = (end_time.QuadPart - start_time.QuadPart) / (double)freq.QuadPart;
	printf("函数执行时间：%.9fs\n", elapsed_time2);
	

	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&start_time);


	SildeWindow(a1, b1, m1, result1);

	QueryPerformanceCounter(&end_time);
	elapsed_time3 = (end_time.QuadPart - start_time.QuadPart) / (double)freq.QuadPart;
	printf("函数执行时间：%.9fs\n", elapsed_time3);*/
	
	return 0;
}
