#include<iostream>
#include<map>
#include <vector>
#include "database.h"

using namespace std;

void db :: AddData(string key, int value){
    database[key] = value;
}
void db :: showDB(){
    cout<<"Name" << " "<< "Value"<<endl;
    for(auto& p: database){
        cout<< p.first<< " "<< p.second<<endl;
    }
}
map<string, int>& db ::getDB(){
    return database;
}
