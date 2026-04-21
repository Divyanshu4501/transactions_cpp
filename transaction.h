#pragma once
#include<iostream>
#include<map>
#include <stdexcept>
#include <vector>
#include <string>
using namespace std;

class transaction{
    public:
    enum class State{ACTIVE,COMMITTED,ABORTED};
    enum class LogType{WRITE, COMMIT};
    
    string ID;
    State state;
    
    public:
    struct LogFile {
        LogType type;
        string key;
        int old_value;
        int new_value;
    };

    map<string,int> buffer;
    map<string, int> &database;
    vector<LogFile> &log;

    public:
    transaction(map<string, int> &db, vector<LogFile> &lg);
    int READ(string KEY);
    void WRITE(string KEY, int VALUE);
    void COMMIT();
    void ABORT();
    void SHOWBUFFER();
    void SHOW_LOG();
};