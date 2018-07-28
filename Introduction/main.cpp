#include <iostream>

using namespace std;

void swap(int&, int&);//数值交换
void bubblesort1A(int[], size_t);//低效率冒泡排序
int ordinaryElement(int[], int);//随机选出一个非最大最小值
int countOnes(unsigned int);//计算数的该二进制串中1的数量
int sumI(int[], size_t);//数组求和（迭代版）
__int64 power2BF_I(int);//幂函数2^n算法（蛮力迭代）
int sum(int[], size_t);//数组求和（线性递归）减而治之
void reverse(int*, size_t, size_t);//倒置算法接口
void reverse(int *A, size_t n) { reverse(A, 0, n - 1); }
inline __int64 sqr(__int64 a) { return a * a; }
__int64 power2(int);//幂函数（优化递归版）
int sum(int[], size_t, size_t);//分而治之
__int64 fib(int);//fib二分递归


int main(int argc, char* argv[])
{
	//1.1.3
	int A[] = { 3, 2, 1 };
	bubblesort1A(A, end(A) - begin(A));
	for (int a : A)
	{
		cout << a << ' ';
	}
	cout << endl;
	//1.3.1
	int S[] = { 1, 3, 2 };
	cout << ordinaryElement(S, 3) << endl;
	//1.3.2
	cout << countOnes(441) << endl;
	//1.3.3
	cout << sumI(A, end(A) - begin(A)) << endl;
	//1.3.5
	cout << power2BF_I(5) << endl;
	//1.4.1
	cout << sum(A, end(A) - begin(A)) << endl;
	//1.4.3
	reverse(A, end(A) - begin(A));
	for (int a : A)
	{
		cout << a << ' ';
	}
	cout << endl;
	cout << power2(6) << endl;
	//1.4.5
	cout << sum(A, 0, end(A) - begin(A) - 1) << endl;
}

void swap(int &a, int &b)
{
	a = a + b;
	b = a - b;
	a = a - b;
}

void bubblesort1A(int A[], size_t n)
{
	bool sorted = false;
	while (!sorted)
	{
		sorted = true;
		for (size_t i = 1; i < n; i++)
		{
			if (A[i - 1] > A[i])
			{
				swap(A[i - 1], A[i]);
				sorted = false;
			}
		}
		n--;
	}
}

int ordinaryElement(int S[], int n)
{
	bubblesort1A(S, 3);
	return S[1];
}

int countOnes(unsigned n)
{
	int ones = 0;
	while (0 < n)
	{
		ones += (n & 1);
		n >>= 1;
	}
	return ones;
}

int sumI(int A[], size_t n)
{
	int sum = 0;
	for (size_t i = 0; i < n; i++)
		sum += A[i];
	return sum;
}

__int64 power2BF_I(int n)
{
	__int64 pow = 1;
	while (0 < n--)
	{
		pow <<= 1;
	}
	return pow;
}

int sum(int A[], size_t n)
{
	if (1 > n)
	{
		return 0;
	}
	else
	{
		return sum(A, n - 1) + A[n - 1];
	}
}

void reverse(int *A, size_t lo, size_t hi)
{
	if (lo < hi)
	{
		swap(A[lo], A[hi]);
		reverse(A, lo + 1, hi - 1);
	}
	//下面是迭代版
/*next:
	if (lo < hi)
	{
		swap(A[lo++], A[hi--]);
		goto next;
	}*/
}

__int64 power2(int n)
{
	if (n == 0) return 1;
	else return (n & 1) ? sqr(power2(n >> 1)) << 1 : sqr(power2(n >> 1));
}

int sum(int A[], size_t lo, size_t hi)
{
	if (lo == hi)
	{
		return A[lo];
	}
	else
	{
		int mi = (lo + hi) >> 1;
		return sum(A, lo, mi) + sum(A, mi + 1, hi);
	}
}

__int64 fib(int n)
{
	return (2 > n) ?
		(__int64)n
		: fib(n - 1) + fib(n - 2);
}
