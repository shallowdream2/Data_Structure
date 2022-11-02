#ifndef GUESTMSG_H
#define GUESTMSG_H
#include <string>
#include <iostream>
#include<sstream>
#include<fstream>
#include"transaction.h"
#include<windows.h>
using namespace std;
/*
用文件来初始化一个节点，每个文件对应一个节点
数据部分只存储交易的id，如果要查询再从数据库中取出这个交易
*/

class msgNode
{
public:
    string type;
    // 0:交易
    // 1:按height查询区块
    // 2:按id查询交易
    // 3:展示所有区块高度和哈希
    string data;
    string preName ="_msg_";//消息文件前缀
    const int size = 100;
    msgNode(){};
    msgNode(string str);
    msgNode(string s1, string s2);
    msgNode(const msgNode& p);// copy fuction
    int sendmsg(string targetDir);

};
msgNode::msgNode(string str) // set node from file
{
    ifstream file(str);
    if (!file.fail())
    {
        getline(file, type);
        getline(file,data);
        
        file.close();
    }
    
}

msgNode::msgNode(string s2,string d) // set node from data
{
    type = s2;
    data = d;
}

int msgNode::sendmsg(string targetDir)
{
    // the information of target queue
    string fname = targetDir+"G_que\\"+"header.txt";
    int length,tail,top;
    ifstream file(fname);
    while(file.fail())
    {
        Sleep(50);
        cout<<"send error! Retry after 50ms"<<endl;
    }
    string str;
    getline(file, str);
    length = stoi(str);
    getline(file, str);
    top = stoi(str);
    getline(file,str);
    tail = stoi(str);
    file.close();
    file.clear();

    if(length>=size)
    {
        cout<<"The target queue is full"<<endl;
        return 0;
    }
    length++;
    

    //data
    string curName=targetDir +"G_que\\"+preName + to_string(tail)+".txt";
    ofstream out(curName);
    out<<type<<"\n"<<data<<"\n";
    out.close();
    tail=(tail+size-1)%size;
    //upgrade
    ofstream ofile(fname);
    if(!ofile.fail())
    {
        ofile<< to_string(length) << "\n"
             << to_string(top) << "\n"
             << to_string(tail) << "\n";
        ofile.close();
        ofile.clear();
    }
    return 1;

}

msgNode::msgNode(const msgNode& p)
{
    type = p.type;
    data = p.data;
}

#endif