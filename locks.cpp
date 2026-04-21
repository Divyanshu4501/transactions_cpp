#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include "transaction.h"

using namespace std;

class lockManager{
    private:
    enum class MODE {NONE, S, X};
    struct lockInfo
    {
        MODE lock_type = MODE::NONE;
        vector<string> holders;
        // queue<pair<string, MODE>> waiting_queue;
    };
    map<string, lockInfo> lockTable;
    lockInfo l;

    public:
    void addLockInfo(string key, string M, vector<string> holders){
        MODE mode = MODE ::NONE;
        if(M == "S"){mode = MODE ::S;}
        if(M == "X"){mode = MODE ::X;}

        if(lockTable.find(key) == lockTable.end()){
            lockTable[key] = {mode, holders};
        }
    }

    void showLockTable(){
        for(auto &it: lockTable){
            string m = "";
            const string &key = it.first;
            auto &lockinfo = it.second;
            auto mode = lockinfo.lock_type;
            if(mode == MODE :: S){m = "S";}
            else if(mode == MODE :: X){m = "X";}

            auto &holder = lockinfo.holders;

            cout << key << " : " << m << "  {";
            for(auto &h : holder){
                 cout << h << " ";
            }
            cout << "}"<<endl;
        }
    }
};

int main(){ 
    lockManager L;
    queue<pair<string, string>> waiting_queue;
    L.addLockInfo("A", "S", {"T1"});
    L.addLockInfo("B", "S", {"T2", "T3"});
    L.showLockTable();
}