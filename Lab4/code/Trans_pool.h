#ifndef TRANS_POOL_H
#define TRANS_POOL_H
#include "transaction.h"
const int size = 100;
class Trans_pool
{
public:
    int length;
    vector<string> TRANS;
    Trans_pool()
    {
        length = 0;
    }
    inline int push(string id)
    {
        TRANS.push_back(id);
        length++;
        return 1;
    }
    int Del(string id);
    int DEL(vector<string> &id);
    vector<string> get_trans(int n);
    int exist(string id);
};

vector<string> Trans_pool::get_trans(int n)
{
    vector<string> t;
    for (int i=0; i<n; ++i)
    {
        int index = TRANS.size()-1;
        t.push_back(TRANS[index]);
        TRANS.pop_back();
        length--;
    }
    return t;
}
int Trans_pool::Del(string id)
{
    for (auto i = TRANS.begin(); i != TRANS.end(); ++i)
    {
        if (*i == id)
        {
            TRANS.erase(i);
            length--;
            return 1;
        }
    }
    return 0;
}

int Trans_pool::exist(string id)
{
    for(auto i:TRANS)
    {
        if(i==id)return 1;
    }
    return 0;
}
int Trans_pool::DEL(vector<string>&id)
{
    for (auto i = id.begin(); i != id.end(); ++i)
    {
        Del(*i);
    }
    return 1;
}
#endif