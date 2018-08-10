#include <iostream>
#include "List.h"

using namespace std;

int main(int argc, char* argv[])
{
	List<int> v;
	v.insertAsFirst(1);
	cout << v[0] << endl;
	system("pause");
	return 0;
}
