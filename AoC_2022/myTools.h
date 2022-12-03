#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

int sum(vector<int> v){

    int s = 0;
    for(int i : v)
        s += i;
    return s;
}

vector<int> sum(vector<vector<int>> matrix){

    vector<int> s;
    for(vector<int> v : matrix)
        s.push_back( sum(v) );
    return s;
}

int partition(vector<int> &vec, int low, int high){

    int pivot = vec[low];
    int i = low-1, j = high+1;

    while(true){

        do{i++;} while(vec[i] < pivot);
        do{j--;} while(vec[j] > pivot);
        if(i >= j) return j;
        swap(vec[i],vec[j]);
    }
}

void quickSort(vector<int> &vec, int low, int high){

    if(low >= high) return;
    
    int mid = partition(vec, low, high);
    quickSort(vec, low, mid);
    quickSort(vec, mid+1, high);
}
