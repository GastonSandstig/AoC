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

int min(int a, int b){ return (a<b)?a:b; }

int max(int a, int b){ return (a>b)?a:b; }

int max(vector<int> vec){
    
    int maxInt = vec[0];
    for(int tmp : vec){
        maxInt = max(maxInt, tmp);
    }
    return maxInt;
}

int max(vector<vector<int>> grid){

    int maxInt = grid[0][0];
    for(vector<int> row : grid){
        maxInt = max(maxInt, max(row));
    }
    return maxInt;    
}

int product(const vector<int> &vec){

    int p = 1;
    for(const int factor : vec)
        p *= factor;
    return p;
}

vector<int> factorize(int num){

    vector<int> factors;

    int divisor = 1;
    while(divisor++){

        if(num < 2)
            return factors;

        if(divisor*divisor > num){
            factors.push_back(num);
            return factors;
        }

        while(num % divisor == 0){
            num /= divisor;
            factors.push_back(divisor);
        }
    }
    return factors;
}

int leastCommonMultiple(int a, int b){

    vector<int>
        vecA = factorize(a),
        vecB = factorize(b);

    for(int aFactor : vecA)
        for(int i = 0; i < vecB.size(); i++)
            if(aFactor == vecB[i]){
                vecB.erase( vecB.begin() + i-- );
                break;
            }
    vecA.insert( vecA.end(), vecB.begin(), vecB.end() );

    return product(vecA);
}

int leastCommonMultiple(vector<int> vec){

    int lcm = 1;
    for(int number : vec)
        lcm = leastCommonMultiple(lcm, number);
    return lcm;
}

int clamp(int val, int lb, int ub){
    if(val < lb)
        return lb;
    else if(val > ub)
        return ub;
    else
        return val;
}

bool btw(int val, int lb, int ub){
    return (lb < val && val < ub) ? true : false;
}

vector<string> split2vec(string str, string delim = " "){

    vector<string> v;

    int start = 0, end = 0;
    while(end != -1){

        end = str.find(delim);
        v.push_back( str.substr(start,end) );
        str = str.substr(end + delim.size());
    }

    return v;
}