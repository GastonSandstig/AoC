#include "../myTools.h"

const char defaultFilePath[] = "AoC_2022/02/input.txt";

enum Shape {ROCK = 1, PAPER = 2, SCISSOR = 3};
enum Result {LOSE = -1, DRAW = 0, WIN = 1};

vector<vector<char>> parse(const char f[]){

    ifstream inputStream(f);
    if( !inputStream.is_open() )
        abort();

    vector<vector<char>> v;
    vector<char> tmp = {'_', '_'};
    while( (inputStream >> tmp[0] >> tmp[1]) && !inputStream.eof() )
        v.push_back(tmp);

    inputStream.close();
    return v;
}

Shape c2s(char c){

    switch (c){
        case 'A': case 'B': case 'C':
            return Shape(c - 'A' + 1);

        case 'X': case 'Y': case 'Z':
            return Shape(c - 'X' + 1);
    
        default:
            abort();
    }
}

Result c2r(char c){

    return Result(c - 'X' - 1);
}

int score(Shape opp, Shape p){

    switch ( (3 + p - opp)%3 ){

        case 0: return p + 3;
        case 1: return p + 6;
        case 2: return p + 0;
        default: abort();
    }

}

Shape determineShape(Shape opp, Result r){

    switch ( (3 + opp + r)%3 ){

        case 1: return ROCK;
        case 2: return PAPER;
        case 0: return SCISSOR;
        default: abort();
    }
}

int main(){

    vector<vector<char>> cheatSheet = parse(defaultFilePath);

    //part one
    int total = 0;
    for(vector<char> round : cheatSheet)
        total += score( c2s(round[0]), c2s(round[1]) );

    cout << "Your total score in part one is " << total << " points" << endl;

    //part two
    total = 0;
    for(vector<char> round : cheatSheet){
        Shape p = determineShape( c2s(round[0]), c2r(round[1]) );
        total += score( c2s(round[0]), p );
    }

    cout << "Your total score in part two is " << total << " points" << endl;

    return 0;
}