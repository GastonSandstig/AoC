#include "../myTools.h"

const char defaultFilePath[] = "AoC_2022/08/input.txt";

enum Direction {NORTH, WEST, SOUTH, EAST};

constexpr uint8_t OBSC_N{ 1 << 0 };
constexpr uint8_t OBSC_W{ 1 << 1 };
constexpr uint8_t OBSC_S{ 1 << 2 };
constexpr uint8_t OBSC_E{ 1 << 3 };
constexpr uint8_t OBSCURED = OBSC_N | OBSC_W | OBSC_S | OBSC_E;

vector<vector<int>> parse(const char f[]){

    vector<vector<int>> v;

    ifstream inputStream(f);
    if( !inputStream.is_open() )
        abort();

    string line;
    while(getline(inputStream, line)){
        vector<int> row;
        for(char c : line)
            row.push_back(c-'0');
        v.push_back(row);
    }

    inputStream.close();
    return v;
}

vector<vector<uint8_t>> getVisibility(vector<vector<int>> tGrid){
    
    vector<vector<uint8_t>> vGrid;

    //west and east
    for(vector<int> tRow : tGrid){
        vector<uint8_t> vRow(tRow.size());
        int i = 1;
        for(int highestTree = tRow.front(); i < tRow.size() - 1; i++){
            if (tRow[i] > highestTree)
                highestTree = tRow[i];
            else
                vRow[i] |= OBSC_W;
        }
        i = i - 1;
        for(int highestTree = tRow.back(); i > 0; i--){
            if (tRow[i] > highestTree)
                highestTree = tRow[i];
            else
                vRow[i] |= OBSC_E;
        }
        vGrid.push_back(vRow);
    }
    //north and south
    for(int j = 1; j < tGrid[0].size() - 1; j++){
        int i = 1;
        for(int highestTree = tGrid[0][j]; i < vGrid.size() - 1; i++){
            if (tGrid[i][j] > highestTree)
                highestTree = tGrid[i][j];
            else
                vGrid[i][j] |= OBSC_N;
        }
        for(int highestTree = tGrid[i--][j]; i > 0; i--){
            if (tGrid[i][j] > highestTree)
                highestTree = tGrid[i][j];
            else
                vGrid[i][j] |= OBSC_S;
        }
    }
    return vGrid;
}

int countVisible(vector<vector<uint8_t>> vGrid){

    int sum = 0;

    for(vector<uint8_t> vRow : vGrid)
        for(uint8_t v : vRow)
            if(v != OBSCURED)
                sum++;

    return sum;
}

int cardinalGTEDist(vector<vector<int>> tGrid, int x, int y, Direction dir){

    int qHeight = tGrid[x][y];
    int dist = 0;
    while(++dist){

        switch(dir){
            case NORTH:
                if(x - dist < 0)
                    return --dist;
                else if (qHeight <= tGrid[x-dist][y])
                    return dist;
                else break;
            
            case WEST:
                if(y - dist < 0)
                    return --dist;
                else if (qHeight <= tGrid[x][y-dist])
                    return dist;
                else break;

            case SOUTH:
                if(x + dist >= tGrid.size())
                    return --dist;
                else if (qHeight <= tGrid[x+dist][y])
                    return dist;
                else break;
            
            case EAST:
                if(y + dist >= tGrid[0].size())
                    return --dist;
                else if (qHeight <= tGrid[x][y+dist])
                    return dist;
                else break;
        }
    }
}

vector<vector<int>> getScenicScores(vector<vector<int>> tGrid){
    
    vector<vector<int>> sGrid;

    for(int i = 1; i < tGrid.size() - 1; i++){
        
        vector<int> tRow = tGrid[i], sRow;
        for(int j = 1; j < tRow.size() - 1; j++){

            int score = 1;
            for(int k = 0; k < 4; k++)
                score *= cardinalGTEDist(tGrid, i, j, Direction(k)); 

            sRow.push_back(score);
        }
        sGrid.push_back(sRow);
    }
    return sGrid;
}

int main(){

    vector<vector<int>> treeGrid = parse(defaultFilePath);

    //part 1
    vector<vector<uint8_t>> visibilityGrid = getVisibility(treeGrid);;
    cout << countVisible(visibilityGrid) << endl;

    //part 2
    vector<vector<int>> scenicScores = getScenicScores(treeGrid);
    cout << max(scenicScores) << endl;
    return 0;
}