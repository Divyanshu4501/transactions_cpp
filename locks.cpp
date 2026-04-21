#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <algorithm>
#include "transaction.h"

using namespace std;

class lockManager{
    private:
    enum class MODE {NONE, S, X};
    struct lockInfo
    {
        MODE lock_type = MODE::NONE;
        vector<string> holders;
        queue<pair<string, MODE>> waiting_queue;
    };
    map<string, lockInfo> lockTable;
    lockInfo l;

    public:
    void addLockInfo(string key, string M, string transaction){
        
        MODE mode = MODE ::NONE;
        if(M == "S"){mode = MODE ::S;}
        if(M == "X"){mode = MODE ::X;}

        auto it = lockTable.find(key);

        if(it == lockTable.end()){
            lockTable[key] = {mode, {transaction}};
            return;
        }

        auto &info = it->second;

        if(!info.waiting_queue.empty()){
            info.waiting_queue.push({transaction, mode});
            return;
        }
        else{
            auto &holders = info.holders;
            if (info.lock_type == MODE :: NONE){          //If current mode is NONE then holders is empty but the queue may not.
                if(info.waiting_queue.empty()){
                    info.lock_type = mode;
                    holders.push_back(transaction);
                }
            }
            else if(info.lock_type == MODE :: S && mode == MODE :: S){ // If current mode is S and new mode is also S
                if(info.waiting_queue.empty()){
                    if(find(holders.begin(), holders.end(), transaction) == holders.end()){
                        holders.push_back(transaction);
                    }
                    else return;
                }
            }
            else if(info.lock_type == MODE :: S && mode == MODE :: X  && holders.size() == 1 &&  holders[0] == transaction){ //current S and new X
                if(info.waiting_queue.empty())
                    info.lock_type = mode;
                else info.waiting_queue.push({transaction, mode});
            }
            else{
            info.waiting_queue.push({transaction, mode});
}
        }
    }

    void showLockTable(){
    for(auto &it: lockTable){
        const string &key = it.first;
        auto &info = it.second;

        // Mode
        string mode;
        if(info.lock_type == MODE::S) mode = "S";
        else if(info.lock_type == MODE::X) mode = "X";
        else mode = "NONE";

        cout << "\nKey: " << key << "\n";
        cout << "Mode: " << mode << "\n";

        // Holders
        cout << "Holders: [ ";
        for(auto &h : info.holders){
            cout << h << " ";
        }
        cout << "]\n";

        // Queue
        cout << "Waiting Queue: [ ";
        auto q = info.waiting_queue;
        while(!q.empty()){
            auto &p = q.front();
            cout << "(" << p.first << ","
                 << (p.second == MODE::S ? "S":"X") << ") ";
            q.pop();
        }
        cout << "]\n";
}
    }
};

int main(){ 
    lockManager L;
    queue<pair<string, string>> waiting_queue;
    L.addLockInfo("A", "S", "T1");
    L.showLockTable();
    L.addLockInfo("A", "S", "T2");
    L.showLockTable();
    L.addLockInfo("A", "X", "T3");
    L.showLockTable();
    L.addLockInfo("A", "S", "T4");
    L.showLockTable();
    L.addLockInfo("A", "S", "T1");
    L.showLockTable();
    L.addLockInfo("A", "X", "T2");
    L.showLockTable();
    L.addLockInfo("B", "X", "T5");
    L.showLockTable();
    L.addLockInfo("B", "S", "T6");
    L.showLockTable();
    L.addLockInfo("B", "X", "T7");
    L.showLockTable();
    L.addLockInfo("C", "S", "T8");
    L.showLockTable();
    L.addLockInfo("C", "X", "T8");
    L.showLockTable();
}