#include "../myTools.h"

const char defaultFilePath[] = "AoC_2022/11/input.txt";

struct Item{

    int lcm;
    vector<int> factors;

    unsigned long long lcmProduct(vector<int> vec){
        unsigned long long product = 1;
        for(int num : vec){
            product *= num;
            product %= lcm;
        }
        return product;
    }

    Item operator*(const Item &mult){
        factors.insert(factors.end(), mult.factors.begin(), mult.factors.end());
        return *this;
    };

    Item operator+(const Item &term){
        factors = factorize(lcmProduct(factors) + lcmProduct(term.factors));
        return *this;
    };

    Item operator-(const Item &term){
        factors = factorize(lcmProduct(factors) + lcmProduct(term.factors));
        return *this;
    };

    Item operator/(const int devisor){
        if(devisor != 1){
            factors = factorize(lcmProduct(factors) / devisor);
        }
        return *this;
    };

    Item(int val){
        factors = factorize(val);
    }
};

struct Monkey{
    vector<Item> inventory;
    char binaryOperator;
    string operand;
    int testVal;
    int trueTargetIdx, falseTargetIdx;
    int noInspections;
    Monkey(){
        noInspections = 0;
    }
    int inspectItem(int devisor = 1){
        
        noInspections++;

        Item &item = inventory[0];
        Item val = (operand == "old") ? item : stoi(operand);

        switch(binaryOperator){
            
            case '+':
                item = item + val;
                break;
            
            case '-':
                item = item - val;
                break;
            
            case '*':
                item = item * val;
                break;

            default:
                cerr << "faulty operator " << binaryOperator << endl;
                abort();         
        }

        item = item / devisor;

        for(int &factor : item.factors)
            if(factor == testVal)
                return trueTargetIdx;
        return falseTargetIdx;
    }
    void throwItem(Monkey *catcher){
        
        catcher->inventory.push_back( inventory.front() );
        inventory.erase( inventory.begin() );
    }
};

vector<Monkey> parse(const char f[]){

    vector<Monkey> monkeys;

    ifstream inputStream(f);
    if( !inputStream.is_open() ){
        cerr << "fileread failed" << endl;
        abort();
    }
 
    while(!inputStream.eof()){
        
        monkeys.emplace_back();
        Monkey &newMonkey = monkeys.back();

        inputStream.ignore(255, ':'); //skip monkey line

        inputStream.ignore(255, ':'); //skip to items
        string tmp;
        while( (inputStream >> tmp) && tmp != "Operation:"){
            newMonkey.inventory.emplace_back( stoi(tmp) );
        }

        inputStream.ignore(255, '='); //skip to vars
        inputStream >> newMonkey.operand >>
            newMonkey.binaryOperator >> newMonkey.operand;

        inputStream.ignore(255, 'y'); //skip to test value
        inputStream >> newMonkey.testVal;

        inputStream.ignore(255, 'y'); //skip to true-target index
        inputStream >> newMonkey.trueTargetIdx;

        inputStream.ignore(255, 'y'); //skip to false-target index
        inputStream >> newMonkey.falseTargetIdx;

        inputStream.ignore(255, 'M'); //skip to next monkey line
    }

    inputStream.close();
    return monkeys;
}

int monkeyLCM(vector<Monkey> &monkeys){
    
    vector<int> testValues;
    for(Monkey &m : monkeys)
        testValues.push_back(m.testVal);
    
    return leastCommonMultiple(testValues);
}

void simulate(vector<Monkey> &monkeys, int noRounds, int divisor = 1){

    int lcm = monkeyLCM(monkeys);
    for(Monkey &m : monkeys)
        for(Item &i : m.inventory)
            i.lcm = lcm;

    for(int i = 0; i < noRounds; i++)
        for(Monkey &m : monkeys)
            while(!m.inventory.empty())
                m.throwItem( &monkeys[ m.inspectItem(divisor) ] );
}

void printMonkeyBusiness(const vector<Monkey> &vec){

    vector<int> inspectCount;
    for(const Monkey &m : vec){
        inspectCount.push_back(m.noInspections);
    }

    quickSort(inspectCount, 0, inspectCount.size()-1);
    cout << (unsigned long long)inspectCount.end()[-1] * (unsigned long long)inspectCount.end()[-2] << endl;
} 

int main(){

    vector<Monkey> monkeys = parse(defaultFilePath);
    simulate(monkeys, 20, 3);
    printMonkeyBusiness(monkeys);

    monkeys = parse(defaultFilePath);
    simulate(monkeys, 10000);
    printMonkeyBusiness(monkeys);

    return 0;
}