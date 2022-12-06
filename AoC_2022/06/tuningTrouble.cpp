#include "../myTools.h"

const char defaultFilePath[] = "AoC_2022/06/input.txt";

const int MARKER_LENGTH = 14;

string parse(const char f[]){

    ifstream inputStream(f);
    if( !inputStream.is_open() )
        abort();

    string str;
    getline(inputStream, str);

    inputStream.close();
    return str;
}

bool containsDuplicate(string str){

    for(int i = 0; i < str.length(); i++){
        char &c = str[i];
        if(str.rfind(c) != i)
            return true;
    }        
    return false;
}

int main(){

    string datastream = parse(defaultFilePath);
    for(int i = 0; i < datastream.length() - (MARKER_LENGTH - 1); i++){

        if( !containsDuplicate( datastream.substr(i,MARKER_LENGTH) ) ){
            cout << "Message starts at: " << i + MARKER_LENGTH << endl;
            break;
        }
    }

    return 0;
}