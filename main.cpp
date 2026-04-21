#include "database.h"
#include "transaction.h"
#include "log_system.h"
#include <sstream>


#include <iostream>
using namespace std;

int main(){
    db database;
    database.AddData("A", 1000);
    database.AddData("B", 1000);
    database.AddData("C", 1000);

    vector<transaction :: LogFile> log;
    transaction t(database.getDB() , log);

    string line;

    while(true){
        cout << "> ";
        getline(cin, line);

        stringstream ss(line);
        string command;
        ss >> command;

        try {
            if(command == "WRITE"){
                string key;
                int value;
                ss >> key >> value;

                if(key == "" || ss.fail()){
                    cout << "Invalid WRITE syntax\n";
                    continue;
                }

                t.WRITE(key, value);
            }

            else if(command == "READ"){
                string key;
                ss >> key;

                if(key == ""){
                    cout << "Invalid READ syntax\n";
                    continue;
                }

                int val = t.READ(key);
                cout << val << endl;
            }

            else if(command == "COMMIT"){
                t.COMMIT();
                cout << "Committed\n";
            }

            else if(command == "ABORT"){
                t.ABORT();
                cout << "Aborted\n";
            }

            else if(command == "SHOW"){
                database.showDB();
            }
            else if(command == "LOG"){
                t.SHOW_LOG();
            }

            else if(command == "EXIT"){
                cout << "Exiting...\n";
                break;
            }

            else if(command == "SHOW_BUFFER"){
                t.SHOWBUFFER();
            }

            else{
                cout << "Unknown command\n";
            }
        }
        catch(exception &e){
            cout << "Error: " << e.what() << endl;
        }
    }

    return 0;
}