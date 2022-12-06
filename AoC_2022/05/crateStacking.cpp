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

void createMover9000(vector<vector<char>> &s, vector<int> instr){

    int noCrates = instr[0];
    vector<char> &source    = s[instr[1] - 1];//correct for one-indexing -> zero-indexing
    vector<char> &dest      = s[instr[2] - 1];

    dest.insert(dest.end(), source.rbegin(), source.rbegin() + noCrates);
    source.erase(source.end() - noCrates, source.end());
}

void createMover9000(vector<vector<char>> &s, vector<vector<int>> instrList){

    for(vector<int> instr : instrList)
        createMover9000(s, instr);
}

void createMover9001(vector<vector<char>> &s, vector<int> instr){

    int noCrates = instr[0];
    vector<char> &source    = s[instr[1] - 1];//correct for one-indexing -> zero-indexing
    vector<char> &dest      = s[instr[2] - 1];

    dest.insert(dest.end(), source.end() - noCrates, source.end());
    source.erase(source.end() - noCrates, source.end());
}

void createMover9001(vector<vector<char>> &s, vector<vector<int>> instrList){

    for(vector<int> instr : instrList)
        createMover9001(s, instr);
}

int main(){

    vector<vector<char>> stacks;
    vector<vector<int>> instructions;
    parse(defaultFilePath, stacks, instructions);

    vector<vector<char>> theoreticalStacks = stacks;
    createMover9000(theoreticalStacks, instructions);
    cout << "CrateMover 9000 would arrange the crates in order: ";
    for(vector<char> s : theoreticalStacks)
        cout << s.back();
    cout << endl;

    createMover9001(stacks, instructions);
    cout << "CrateMover 9001 instead arranges the crates in order: ";
    for(vector<char> s : stacks)
        cout << s.back();
    cout << endl;

    return 0;
}