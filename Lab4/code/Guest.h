#ifndef GUEST_H
#define GUEST_H
#include <vector>
#include <string>
#include <time.h>
#include <stdlib.h>
#include <windows.h>
#include "Trans_pool.h"
#include "Guest_msg.h"
#include <fstream>
#include<iostream>
using namespace std;

/*
客户节点自身也维护一个交易池，发50个交易
*/
class guest
{
public:
    int interval; //发送时间间隔
    vector<string> target;
    string Database;
    Trans_pool gTrans;
    void Run();
    guest(vector<string> &t, string data = "", int period = 0);
};

guest::guest(vector<string> &t, string data, int period)
{
    target = t;
    Database = data;
    interval = period;
    ifstream file(data);
    if (!file.fail())
    {
        string str;
        getline(file, str);
        while (getline(file, str))
        {
            if (gTrans.length == 50)
                break;
            int height;
            string txid;
            int is_coinbase;
            int input_count;
            int output_count;
            string str2;
            stringstream ss(str);

            getline(ss, str2, ','); // height
            height = stoi(str2);

            getline(ss, txid, ',');

            getline(ss, str2, ',');
            is_coinbase = stoi(str2);

            getline(ss, str2, ',');
            input_count = stoi(str2);

            getline(ss, str2);
            output_count = stoi(str2);
            gTrans.push(txid);
        }
    }
}
void guest::Run()
{
    srand((unsigned)time(NULL));
    int now = gTrans.TRANS.size()-1;
    int count = 0;
    while (1)
    {
        count++;
        if(count==100)break;
        int cnt = rand() % 100;
        if (0<=cnt&&cnt < 25) //交易
        {   
            cout<<"0"<<endl;
            if(now<0)
            {
                cout<<"The guest has nothing to send"<<endl;
                continue;
            }
            string str = gTrans.TRANS[now];
            now--;
            msgNode temp("0", str);
            temp.sendmsg(target[cnt & 1]);
        }
        else if (cnt >= 25 && cnt < 50) //按高度查询区块
        {
            cout<<"1"<<endl;
            //随机一个高度进行查询,查询范围：0到50
            int index = rand() % 50;
            msgNode temp("1", to_string(index));
            temp.sendmsg(target[cnt & 1]);
        }
        else if (cnt >= 50 && cnt < 75)//按id查询
        {
            cout<<"2"<<endl;
            int index = rand()%(gTrans.length);
            msgNode temp("2",gTrans.TRANS[index]);
            temp.sendmsg(target[cnt & 1]);
        }
        else if(cnt>=75&&cnt<100)//展示所有区块高度和哈希
        {
            cout<<"3"<<endl;
            msgNode temp("3","");
            temp.sendmsg(target[cnt & 1]);
        }
        Sleep(interval);
    }
}

#endif