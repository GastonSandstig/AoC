#include "../myTools.h"

const char defaultFilePath[] = "AoC_2022/09/input.txt";

struct Instruction{
    char dir;
    int moves;
};

struct Position{
    int x, y;
};

vector<Instruction> parse(const char f[]){

    ifstream inputStream(f);
    if( !inputStream.is_open() ){
        cerr << "fileread failed" << endl;
        abort();
    }

    vector<Instruction> vec;
    while(!inputStream.eof()){
        Instruction tmp;
        inputStream >> tmp.dir >> tmp.moves;
        vec.push_back(tmp);
    }

    inputStream.close();
    return vec;
}

void step(Position &pos, char dir){

    switch (dir){
        case 'R':
            pos.x++;
            break;

        case 'L':
            pos.x--;
            break;

        case 'U':
            pos.y++;
            break;

        case 'D':
            pos.y--;
            break; 

        default:
            cerr << "bad dir: " << dir;
            abort();
    }
}

void updateTailPos(const Position &head, Position &tail){

    int xDiff = head.x - tail.x, yDiff = head.y - tail.y;

    auto secondaryX = [&]{
        if(xDiff > 0)
            tail.x++;
        else if(xDiff < 0)
            tail.x--;
    };
    auto secondaryY = [&]{
        if(yDiff > 0)
            tail.y++;
        else if(yDiff < 0)
            tail.y--;
    };

    if(xDiff > 1){
        tail.x++;
        secondaryY();
    }
    else if(xDiff < -1){
        tail.x--;
        secondaryY();
    }
    else if(yDiff > 1){
        tail.y++;
        secondaryX();
    }
    else if(yDiff < -1){
        tail.y--;
        secondaryX();
    }
}

vector<Position> simulatePath(vector<Instruction> instructions, int ropeLength){

    vector<Position> path = {{0,0}};
    vector<Position> rope(ropeLength);
    for(Position knot : rope){
        knot = {0,0};
    }

    for(Instruction instr : instructions){

        for(int i = 0; i < instr.moves; i++){
            step(rope.front(),instr.dir);
            for(int j = 1; j < ropeLength; j++)
                updateTailPos(rope[j-1], rope[j]);
            path.push_back(rope.back());
        }
    }
    return path;
}

bool operator==(const Position &p1, const Position &p2){
    return ((p1.x == p2.x) && (p1.y == p2.y)) ? true : false;
}

vector<Position> findUniquePos(vector<Position> pos){
    
    vector<Position> uniquePos;
    for(Position qPos : pos){
        bool isUnique = true;
        for(Position cmpPos : uniquePos){
            if(qPos == cmpPos){
                isUnique = false;
                break;
            }
        }
        if(isUnique)
            uniquePos.push_back(qPos);
    }
    return uniquePos;
}

int main(){

    vector<Instruction> instructions = parse(defaultFilePath);

    vector<Position> path1 = simulatePath(instructions,2);
    cout << findUniquePos(path1).size() << endl;

    vector<Position> path2 = simulatePath(instructions,10);
    vector<Position> tmp = findUniquePos(path2);
    cout << tmp.size() << endl;
    return 0;
}