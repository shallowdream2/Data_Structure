#ifndef TRANSACTION_H
#define TRANSACTION_H
using namespace std;
#include <string>
#include <vector>
#include <fstream>
#include<sstream>
#include "input.h"
#include "output.h"
#include <set>
#include <map>
#include<iostream>

//用动态线性表来存储
class transaction
{
public:
    string txid;
    int input_count;
    int output_count;
    int input_size;
    int output_size;
    input *inputs; // maxLen=100
    output *outputs;
    int is_coinbase;
    int legal;
    transaction(string s1, int x1, int x2, int is);
    void display();
    void insert_input(input p);
    void insert_output(output p);
    int is_legal(set<pair<string, int>> &s1, map<pair<string, int>, int> &v);
    void set_data(string database);
};
transaction::transaction(string s1 = "", int is = 0, int x1 = 0, int x2 = 0)
{
    txid = s1;
    input_count = x1;
    output_count = x2;
    is_coinbase = is;
    legal = 1;
    inputs = new input[x1];
    outputs = new output[x2];
    input_size=0;
    output_size=0;
};

void transaction::display()
{
    cout << "txid: " << txid << endl
         << "is_coinbase: " << is_coinbase << endl;
    cout << "input_count: " << input_count << endl;
    cout << "output_count: " << output_count << endl;

    cout << "inputs:" << endl;
    for (int i = 0; i < input_count; ++i)
    {
        cout << "input_" << i << endl;
        inputs[i].display();
    }

    cout << "outputs: " << endl;
    for (int i = 0; i < output_count; ++i)
    {
        cout << "output_" << i << endl;
        outputs[i].display();
    }
    cout << endl;
}
void transaction::insert_input(input p)
{
    inputs[input_size++] = p;
}
void transaction::insert_output(output p)
{
    outputs[output_size++] = p;
    
}
int transaction::is_legal(set<pair<string, int>> &s1, map<pair<string, int>, int> &v)
{
    if (is_coinbase)
        return 1;
    int value1 = 0;
    int value2 = 0;
    for (int i = 0; i < input_count; ++i)
    {
        pair<string, int> p;
        p.first = inputs[i].prevTxID;
        p.second = inputs[i].prevTxOutIndex;
        if (s1.count(p))
        {
            s1.erase(p);
        }
        else
        {
            legal = 0;
            return 0;
        }
        value1 += v[p];
    }
    for (int i = 0; i < output_count; ++i)
    {
        value2 += outputs[i].value;
    }

    if (value1 < value2)
    {
        legal = 0;
        return 0;
    }
    return 1;
}

void transaction::set_data(string str_d)//按txid设置input和output
{
    ifstream f1(str_d+"inputs.csv");
    ifstream f2(str_d+"outputs.csv");
    while (f1.fail()||f2.fail())
    {
        f1.open(str_d+"inputs.csv");
        f2.open(str_d+"outputs.csv");
    }
    
    string str;
    getline(f1,str);
    while(getline(f1,str))
    {
        int height;
        string prevTxID;
        string txid;
        int prev_block;
        int index;
        string str2;
        stringstream ss(str);

        getline(ss, str2, ','); // height
        height = stoi(str2);

        getline(ss, txid, ',');

        getline(ss, str2, ',');
        prev_block = stoi(str2);

        getline(ss, prevTxID, ',');

        getline(ss, str2, ',');
        index = stoi(str2);
        
        str2="";
        getline(ss,str2);
        if(txid==this->txid)
        {
            insert_input(input(prev_block, prevTxID, index,str2));
        }
    }
    f1.close();
    f1.clear();
    getline(f2, str);
    while (getline(f2, str))
    {
        int height;
        string txid;
        int value;
        int index;
        string str2;
        stringstream ss(str);
        getline(ss, str2, ','); // height
        height = stoi(str2);

        getline(ss, txid, ',');

        getline(ss, str2, ',');
        index = stoi(str2);

        getline(ss, str2, ',');
        value = stoi(str2);
        
        str2="";
        getline(ss,str2);

        if(txid==this->txid)
        {
            insert_output(output(txid,index,value,str2));
        }
    }
    f2.close();
    f2.clear();
    

}
#endif