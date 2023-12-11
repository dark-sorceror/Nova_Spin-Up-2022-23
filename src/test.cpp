#include "stdio.h"
#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<double> abc = {1,2,3};
    int n = abc.size();
    for (int i=0; i < n; i++) {
        cout << abc[i] << " ";
    }
}