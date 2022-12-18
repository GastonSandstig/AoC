#include "../myTools.h"

const char defaultFilePath[] = "AoC_2022/10/input.txt";

struct Instruction {
    int cycles, value;
};

vector<Instruction> parse(const char f[]){

    ifstream inputStream(f);
    if( !inputStream.is_open() ){
        cerr << "fileread failed" << endl;
        abort();
    }

    vector<Instruction> vec;

    string tmp;
    while(inputStream >> tmp){
        if(tmp == "noop")
            vec.push_back({1,0});
        else{
            vec.push_back({2,0});
            inputStream >> vec.back().value;
        }
    }

    inputStream.close();
    return vec;
}

vector<int> getSignalStrenghts(vector<Instruction> program, int startVal = 1, int reportFreq = 40){

    vector<int> reportStrength;

    int X = startVal;
    int cycle = 0;
    for(Instruction instr : program){
        
        for(int i = 0; i < instr.cycles; i++)
            if((++cycle + 20) % reportFreq == 0)
                reportStrength.push_back(X * cycle);

        X += instr.value;
    }
    return reportStrength;
}

void draw(vector<Instruction> program){

    int X = 1;
    int cycle = 0;
    for(Instruction instr : program){
        
        for(int i = 0; i < instr.cycles; i++){

            cout << ( btw(cycle++, X-2, X+2) ? '#' : '.' );

            if( cycle % 40 == 0 ){
                cycle = 0;
                cout << '\n';
            }
        }
        X += instr.value;
    }
    cout << endl;
}

int main(){

    vector<Instruction> program = parse(defaultFilePath);
    
    cout << sum(getSignalStrenghts(program)) << endl;

    draw(program);

    return 0;
}