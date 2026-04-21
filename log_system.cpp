#include<iostream>
#include<map>
#include <stdexcept>
#include <vector>
#include "log_system.h"

using namespace std;

vector<log_system ::logFile>& log_system::getLog(){
    return log;
}