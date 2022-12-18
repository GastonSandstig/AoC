#include "../myTools.h"

const char defaultFilePath[] = "AoC_20XX/YY/input.txt";

void parse(const char f[]){

    ifstream inputStream(f);
    if( !inputStream.is_open() ){
        cerr << "fileread failed" << endl;
        abort();
    }

    inputStream.close();
    return;
}

int main(){

    parse(defaultFilePath);

    return 0;
}