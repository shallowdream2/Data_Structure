#ifndef LIST_H
#define LIST_H
#include"block.cpp"
#include<string>
#include<set>
#include<map>
#include<vector>
#include<time.h>
#include<stdlib.h>
using namespace std;

struct Node{
    block data;
    Node*pre=NULL;
    Node*next=NULL;
};

class List{
    public:
    int length;
    Node* head=NULL;
    Node* rear=NULL;
    List();
    int getLegal();
    int getIllegal();
    void insert(Node* x,int i);//将x插入到位置i之前
    void del(int i);//删除i位置的节点
    Node* getNode(int height);//以高度查询区块
    transaction* search_transaction(string txID);//以txID查询交易
    void display();
    void clear();
    block push_newNode(vector<string>Trans);
    int exist(block& b);//查询是否在链中
    void set_data(string database);//设置数据
};

#endif