#include<iostream>
#include<map>
#include <stdexcept>
#include <vector>
#include "transaction.h"

using namespace std;

transaction :: transaction(map<string, int> &db, vector<LogFile> &lg): database(db), log(lg){
    state = State :: ACTIVE;
}
int transaction :: READ(string KEY){
    auto it = buffer.find(KEY);
    if(it != buffer.end()){
        return it->second;
    }
    auto it2 = database.find(KEY); //pass database by reference
    if(it2 != database.end()){
        return it2->second;
    }
    else throw runtime_error("Key not found in database");
}
void transaction :: WRITE(string KEY, int VALUE){
    int OLD_VALUE;
    if(state == State :: ACTIVE){
        auto it = buffer.find(KEY);
        if(it != buffer.end()){
            OLD_VALUE = it->second;
        }
        else{
            auto it2 = database.find(KEY); //pass database by reference
            if (it2 != database.end())
                OLD_VALUE = it2->second;
            
            else throw runtime_error("Key not found in database");
        }
        log.push_back({LogType::WRITE,KEY, OLD_VALUE, VALUE});
        buffer[KEY] = VALUE;
    }
    else throw runtime_error("State not matched");
}

void transaction::SHOW_LOG(){
    cout << "\n--- LOG FILE ---\n";

    for(auto &entry : log){
        if(entry.type == LogType::WRITE){
            cout << "WRITE "
                 << entry.key << " "
                 << entry.old_value << " -> "
                 << entry.new_value << endl;
        }
        else if(entry.type == LogType::COMMIT){
            cout << "COMMIT" << endl;
        }
    }

    cout << "----------------\n";
}
void transaction :: COMMIT(){
    if(state == State :: ACTIVE){
        for(auto &it: buffer){
            database[it.first] = it.second;
        }
        log.push_back({LogType::COMMIT, "", 0, 0});
        this->state = State :: COMMITTED;
        buffer.clear();
    }
    else throw runtime_error("State not matched");
}
void transaction ::SHOWBUFFER(){
    cout<<"Name" << " "<< "Value"<<endl;
    for(auto& p: transaction::buffer){
        cout<< p.first<< " "<< p.second<<endl;
    }
}

void transaction :: ABORT(){
    if(state == State :: ACTIVE){
        for(int i = log.size()-1; i >= 0; i--){
            if(log[i].type == LogType::COMMIT)
                    break;
                    
            if(log[i].type == LogType::WRITE){
                database[log[i].key] = log[i].old_value;
            }
        }
        this->state = State :: ABORTED;
        buffer.clear();
    }
    else throw runtime_error("State not matched");
}