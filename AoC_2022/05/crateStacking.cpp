#include "../myTools.h"

const char defaultFilePath[] = "AoC_2022/05/input.txt";

vector<vector<char>> parseStacks(ifstream &iStream){

    vector<vector<char>> v;

    for(char tmp[5] = "0000"; tmp[1] != '1'; iStream.clear(), iStream.ignore(1)){

        for(int i = 0; iStream.get(tmp,5); i++){
            
            if(tmp[1] == '1')
                break;

            if(v.size() == i)
                v.push_back({});
            
            if(tmp[1] != ' ')
                v[i].insert(v[i].begin(), tmp[1]);
        }
    }

    return v;
}

vector<vector<int>> parseInstr(ifstream &iStream){

    vector<vector<int>> v;

    string tmp;
    for(int i = 0; !iStream.eof();){
        iStream >> tmp;
        if(tmp == "move"){
            
            v.push_back({0,0,0});
            iStream >> v[i][0] >> tmp >> v[i][1] >> tmp >> v[i][2];
            i++;
        }
        
    }

    return v;
}

void parse(const char f[], vector<vector<char>> &stack, vector<vector<int>> &inst){

    ifstream inputStream(f);
    if( !inputStream.is_open() )
        abort();

    stack  = parseStacks(inputStream);
    inst    = parseInstr(inputStream);

    inputStream.close();
    return;
}

int main(){

    vector<vector<char>> stacks;
    vector<vector<int>> instructions;
    parse(defaultFilePath, stacks, instructions);

    return 0;
}