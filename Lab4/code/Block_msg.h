#ifndef BLOCK_MSG_H
#define BLOCK_MSG_H
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "block.h"
#include<windows.h>
using namespace std;

class Block_msg
{
public:
    string b_hash;
    string b_prehash;
    vector<string> trans;
    Block_msg(block &b);    // set from data
    Block_msg(string fstr); // set from file
    Block_msg(const Block_msg &p);
    Block_msg(){};
    int sendmsg(string targetDir); //创建文件
    string preName = "_msg_";
    const int size = 100;
    block to_block();
};

Block_msg::Block_msg(block &p) // set from data
{
    b_hash = p.hash;
    b_prehash = p.preHash;
    for (int i = 0; i < p.size; ++i)
    {
        trans.push_back(p.transactions[i].txid);
    }
}

Block_msg::Block_msg(string filename)
{
    ifstream file(filename);
    while(file.fail())
    {
        Sleep(200);
        file.open(filename);
    }
    if (!file.fail())
    {
        getline(file, b_hash);
        getline(file, b_prehash);
        string str;
        while (getline(file, str))
        {
            trans.push_back(str);
        }
        file.close();
        file.clear();
    }
}

int Block_msg::sendmsg(string targetDir)
{
    string fname = targetDir + "B_que\\" + "header.txt";
    int length, tail, top;
    ifstream file(fname);

    while(file.fail())
    {
        cout<<"send error! Retry after 50ms"<<endl;
        Sleep(50);
        file.open(fname);
    }
    string str;
    getline(file, str);
    length = stoi(str);
    getline(file, str);
    top = stoi(str);
    getline(file, str);
    tail = stoi(str);
    file.close();
    file.clear();
    if (length >= size)
        return 0;
    length++;

    // data
    string curName = targetDir + "B_que\\" + preName + to_string(tail) + ".txt";
    ofstream out1(curName);
    out1 << b_hash << "\n"
         << b_prehash << "\n";
    for (auto i : trans)
    {
        out1 << i << "\n";
    }
    out1.close();
    out1.clear();

    tail = (tail + size - 1) % size;
    // upgrade
    ofstream ofile(fname);
    if (!ofile.fail())
    {
        ofile << to_string(length) << "\n"
              << to_string(top) << "\n"
              << to_string(tail) << "\n";
        ofile.close();
        ofile.clear();
    }
    return 1;
}

Block_msg::Block_msg(const Block_msg &p)
{
    b_hash = p.b_hash;
    b_prehash = p.b_prehash;
    trans = p.trans;
}

block Block_msg::to_block()
{
    block p;
    p.hash = this->b_hash;
    p.preHash = this->b_prehash;
    p.Trans = this->trans;
    return p;
}
#endif