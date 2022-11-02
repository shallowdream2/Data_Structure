#ifndef BLOCK_H
#define BLOCK_H

#include<string>
#include<vector>
#include"transaction.h"
#include<iostream>
#include<fstream>
#include<sstream>
#define maxLen 10
class block{

    public:
    int height;//区块高度
    string hash;//hash值
    string preHash;//之前的hash值
    string merkleRoot="";
    int nonce=0;
    transaction transactions[maxLen];//交易集合
    int size;// size of the transactions
    vector<string>Trans;//交易的txid
    block(int,string,string);
    block();
    int search_trans_index(string txid);// index
    void display();//展示
    void set_data(string data_base);//从数据库中获取数据

    

};

#endif