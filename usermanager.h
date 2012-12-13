#ifndef USERMANAGER_H
#define USERMANAGER_H
#include <string>
#include <map>
#include <fstream>
#include <ctime>
#include <sys/types.h>
#include <sys/stat.h>
#include <cstdio>
#include <cstdlib>
#include <vector>
using namespace std;
#define CONFIG_FILE "/home/windcolor/face/user.dat"
#define CONFIG_HOME "/home/windcolor/face/"
#define LENGTH 20
class UserManager
{
public:
    UserManager();
    bool loadSetting();
    bool saveSetting();
    bool addUser(string username);
    string getUser(string username);
    int dataSize();
    string getBaseFloder();
    void print();
    vector<string> getUserList();
private:
    string genRandomString();
    map<string,string> data;
};

#endif // USERMANAGER_H
