#include "../myTools.h"

const char defaultFilePath[] = "AoC_2022/03/input.txt";

vector<vector<int>> parse(const char f[]){

    ifstream inputStream(f);
    if( !inputStream.is_open() )
        abort();

    vector<vector<int>> v;

    string str;
    while( getline(inputStream, str) && !inputStream.eof() ){

        vector<int> tmp;

        for(char c : str){
            if( c >= 'a' ){
                tmp.push_back(c - 'a' + 1);
            } else
                tmp.push_back(c - 'A' + 27);
        }

        v.push_back(tmp);
    }

    inputStream.close();
    return v;
}

vector<int> findCommonElements(vector<int> v){

    vector<int> common;
    for(int i = 0; i < v.size()/2; i++)
        for(int j = v.size()/2; j < v.size(); j++)
            if(v[i] == v[j])
                common.push_back(v[i]);
    
    return common;
}

vector<int> findCommonElements(vector<int> a, vector<int> b){

    vector<int> common;
    for(int aEle : a)
        for(int bEle : b)
            if(aEle == bEle)
                common.push_back(aEle);
    
    return common;
}

vector<int> findCommonElements(vector<int> a, vector<int> b, vector<int> c){

    vector<int> tmp = findCommonElements(a,b);
    return findCommonElements(tmp,c);
}

int main(){

    vector<vector<int>> rucksacks = parse(defaultFilePath);

    int sum = 0;
    for(vector<int> v : rucksacks)
        sum += findCommonElements(v)[0];

    cout << sum << endl;

    sum = 0;
    for(int i = 0; i < rucksacks.size(); i += 3)
        sum += findCommonElements(rucksacks[i],rucksacks[i+1],rucksacks[i+2])[0];

    cout << sum << endl;

    return 0;
}