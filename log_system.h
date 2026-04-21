#pragma once

#include<iostream>
#include<map>
#include <stdexcept>
#include <vector>

using namespace std;

class log_system{
    public:
    struct logFile{
        string type;
        string KEY;
        int OLD_VALUE;
        int NEW_VALUE;
    };
    public:
    vector<logFile> log;  

    public:
    vector<logFile>& getLog();
};