#ifndef OUTPUT_H
#define OUTPUT_H
#include<string>
#include<iostream>
class output{
    public:
    string txid;
    int index;
    int value;
    string script;
    output(string s,int,int,string);
    output();
    output(const output& p);
    void display();
    
};
output::output(string s,int x1,int x2,string str)
{
    txid=s;
    index=x1;
    value=x2; 
    script =str;
};
output::output()
{
    txid="";
    index=0;
    value=0;
    script="";
}

void output::display()
{
    cout<<txid<<","<<index<<","<<value<<endl;
}

output::output(const output& p)
{
    txid=p.txid;
    index=p.index;
    value=p.value;
    script=p.script;
}
#endif