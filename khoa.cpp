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
    void setName(string name){this->name = name;}
    void setNum(int num){this->cnt = num;}
    int getNum(){return cnt;}
    void destroy(){cnt--;}
};

class BattleField{
private:
    Ship* motherShip, *battleShip, *destroyer;
    int cnt;
public:
    bool lose = false;
    BattleField(int a, int b, int c){
        motherShip = new Ship[a];
        battleShip = new Ship[b];
        destroyer = new Ship[c];
        for(int i = 0 ; i < a ; ++i){
            motherShip[i].setName("Mothership");
            motherShip[i].setNum(5);
        }

        for(int i = 0 ; i < b ; ++i){
            battleShip[i].setName("BattleShip");
            battleShip[i].setNum(4);
        }
        for(int i = 0 ; i < c ; ++i){
            destroyer[i].setName("Destroyer");
            destroyer[i].setNum(3);
        }
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


