#include "usermanager.h"

UserManager::UserManager()
{
    srand((unsigned)time(NULL));
}

bool UserManager::loadSetting()
{
    ifstream f1(CONFIG_FILE);
    if(f1)
    {
        int totalsize=0;
        this->data.clear();
        f1>>totalsize;
        int i=0;
        for(i=0;i<totalsize;i++)
        {

            string name;
            getline(f1, name);

            string path;
            getline(f1, path);


            this->data[name]=path;
        }
        return true;
    }
    else
    {
        ofstream f2(CONFIG_FILE);
        if(f2)
        {
            f2<<0;
            this->data.clear();
            return true;
        }
        else
            return false;
    }
}

bool UserManager::saveSetting()
{
    ofstream f1(CONFIG_FILE);
    if(f1)
    {
        f1<<data.size();
        map<string,string>::iterator it=this->data.begin();

        while(it!=this->data.end())
        {
            f1<<(*it).first<<endl;
            f1<<(*it).second<<endl;
            it++;
        }
        return true;
    }
    else return false;
}

string UserManager::getUser(string username)
{
    map<string,string>::iterator it=this->data.find(username);
    if(it==this->data.end())
    {
        string emptystring;
        return emptystring;
    }
    else
    {
        string path= this->data[username];
        return path;
    }
}

bool UserManager::addUser(string username)
{
    map<string,string>::iterator it=this->data.find(username);
    if(it==this->data.end())
    {
        string path=this->genRandomString();
        this->data[username]=path;
        char* setDir  = new char[200];
        sprintf(setDir,"%s/%s", CONFIG_HOME,path. c_str());
        mkdir(setDir, S_IRWXU );
        return true;
    }
    else return false;
}

string UserManager::genRandomString()
{
    string ans;
    for(int i=0;i<LENGTH;i++)
    {
        if (rand()%2==0)
        {
            ans+='a'+rand()%26;
        }
        else
        {
            ans+='A'+rand()%26;
        }
    }
    return ans;
}

int UserManager::dataSize()
{
    return this->data.size();
}

void UserManager::print()
{

     map<string,string>::iterator it=this->data.begin();
     while(it!=this->data.end())
     {

         printf("name:%s,path:%s\n",(*it).first.c_str(),(*it).second.c_str());
         it++;
     }
}
string UserManager::getBaseFloder()
{
    return CONFIG_HOME;
}

vector<string> UserManager::getUserList()
{
    vector <string> v;
    map<string,string>::iterator it=this->data.begin();
    while(it!=this->data.end())
    {
        v.push_back((*it).first);
        it++;
    }
    return v;
}
