#include <iostream>

using namespace std;

void swap(int &a, int &b);
void bubblesort1A(int A[], size_t n);

int main(int argc, char* argv[])
{
	int A[] = { 3, 2, 1 };
	bubblesort1A(A, end(A) - begin(A));
	for (int a : A)
	{
		cout << a << endl;
	}
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
		for (int i = 1; i < n; i++)
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
