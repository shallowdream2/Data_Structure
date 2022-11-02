#ifndef INPUT_H
#define INPUT_H
#include<string>
#include<iostream>
using namespace std;
class input{
    public:
    int pre_vblock;
    string prevTxID;
    int prevTxOutIndex;
    string scriptSig;
    input(int x1,string x2,int x3,string);
    input();
    void display();
    input(const input& p);    
};
input::input(int x1,string x2,int x3,string str)
{
    pre_vblock=x1;
    prevTxID=x2;
    prevTxOutIndex=x3;
    scriptSig = str;
};

input::input()
{
    pre_vblock=0;
    prevTxID="";
    prevTxOutIndex=0;
    scriptSig="";
}

void input::display()
{
    cout<<pre_vblock<<","<<prevTxID<<","<<prevTxOutIndex<<endl;;
}

input::input(const input& p)
{
    pre_vblock=p.pre_vblock;
    prevTxID=p.prevTxID;
    prevTxOutIndex=p.prevTxOutIndex;
    scriptSig=p.scriptSig;
}
#endif
