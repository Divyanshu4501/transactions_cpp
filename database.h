#pragma once
#include <map>
#include <string>
using namespace std;

class db{
    public:
    map<string, int> database;

    public:
    void AddData(string key, int value);
    void showDB();
    map<string, int>& getDB();
};