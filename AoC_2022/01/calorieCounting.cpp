#include "../myTools.h"

const char defaultFilePath[] = "AoC_2022\\01\\input.txt";

vector< vector<int> > parse(const char f[]){

    ifstream inputStream(defaultFilePath);
    if( !inputStream.is_open() )
        abort();

    vector<vector<int>> v;

    for(int i = 0; !inputStream.eof(); i++){
        
        v.push_back( vector<int>() );

        string tmp = "";
        while( getline(inputStream, tmp) && tmp != "")
            v[i].push_back( stoi(tmp) );
    }

    inputStream.close();
    return v;
}

vector<int> kMostCalorific(vector<int> cal, int k){

    return vector<int>( cal.rbegin(), cal.rbegin()+k );
}

int main(){

    vector<vector<int>> elfList = parse(defaultFilePath);
    vector<int> elfCalories = sum(elfList);
    quickSort(elfCalories, 0, elfCalories.size()-1);

    cout << "The most calorific elf has " << elfCalories.back() << " cal" << endl;
    cout << "The 3 most calorific elves have " << sum(kMostCalorific(elfCalories,3)) << " cal" << endl;

    return 0;
}