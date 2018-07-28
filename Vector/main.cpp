#include <iostream>
#include "Vector.h"

using namespace std;
int main(){
    Vector<int> v(5, 3, 1);
    cout << v.size() << endl;
    return 0;
}