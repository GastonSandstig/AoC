#include "../myTools.h"

const char defaultFilePath[] = "AoC_2022/04/input.txt";

vector<vector<int>> parse(const char f[]){

    ifstream inputStream(f);
    if( !inputStream.is_open() )
        abort();

    vector<vector<int>> v;

    string tmp;
    while(getline(inputStream, tmp) && !inputStream.eof()){

        vector<int> pair;
        for(string range : split2vec(tmp,","))
            for(string section : split2vec(range, "-"))
                pair.push_back( stoi(section) );

        v.push_back(pair);
    }

    inputStream.close();
    return v;
}

int main(){

    vector<vector<int>> overlapList = parse(defaultFilePath);

    int noFullOverlaps = 0;
    for(vector<int> pair : overlapList){

        int low = min(pair[0], pair[2]);
        int high = max(pair[1], pair[3]);
        if( (low == pair[0] && high == pair[1]) || (low == pair[2] && high == pair[3]) )
            noFullOverlaps++;
    }
    cout << noFullOverlaps << endl;

    int noPartialOverlaps = 0;
    for(vector<int> pair : overlapList){

        if( (pair[0] <= pair[2] && pair[2] <= pair[1]) ||
            (pair[0] <= pair[3] && pair[3] <= pair[1]) ||
            (pair[2] <  pair[0] && pair[1] <  pair[3]) )
            noPartialOverlaps++;
    }
    cout << noPartialOverlaps << endl;

    return 0;
}