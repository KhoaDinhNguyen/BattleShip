#include <bits/stdc++.h>

using namespace std;

class Ship{
private:
    string name;
    int cnt; // number of cells
public:
    Ship(){name = "", cnt = 0;}
    Ship(string name, int cnt){this->name = name; this->cnt = cnt;}
    string getName(){return name;}
    int getNum(){return cnt;}
    void destroy(){cnt--;}
};


class MotherShip:public Ship{
    public:
    MotherShip():Ship("Mothership",5){}
};

class BattleShip:public Ship{
    public:
    BattleShip():Ship("Battleship",4){}
};

class Destroyer:public Ship{
    public:
    Destroyer():Ship("Destroyer",3){}
};

class BattleField{
private:
    MotherShip* motherShip;
    BattleShip* battleShip;
    Destroyer* destroyer;
    int cnt;
public:
    bool lose = false;
    BattleField(int a, int b, int c){
        motherShip = new MotherShip[a];
        battleShip = new BattleShip[b];
        destroyer = new Destroyer[c];
        cnt = a + b + c;
    }
    ~BattleField(){
        delete[] motherShip;
        delete[] battleShip;
        delete[] destroyer;
    }
    void remove(string s, string** mp, int i ,int j){
        //s = "M1" || s = "M2";
        int idx = s[1] - '0';

        mp[i][j] = "X";

        if(s[0] == 'M'){
            motherShip[idx].destroy();
            if(motherShip[idx].getNum() == 0){
                cout << "Mothership " << idx + 1 << " has been destroyed" << endl;
                this->cnt--;
            }
        }

        if(cnt == 0){
            cout << "VICTORY";
            lose = true;
        }
        
    }
};


int main(){


    return 0;
}


