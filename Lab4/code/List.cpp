#include "List.h"
#include <iostream>
using namespace std;
List::List() //初始化
{
    length = 0;
    head = new Node;
    rear = head;
    head->next = head;
    head->pre = head;
}

void List::insert(Node *x, int i)
{

    Node *p = head;
    int j = 0;
    while (j < i - 1 && p->next != head) //找到i节点的前驱
    {
        p = p->next;
        j++;
    }
    if (j >= i)
    {
        cout << "error insert" << endl;
        return;
    }

    x->next = p->next;
    x->next->pre = x;
    p->next = x; //指向x
    x->pre = p;

    length++;
    //调整rear节点
    rear = head->pre;
};

void List::del(int i)
{
    Node *p = head;
    int j = 0;
    while (j < i - 1 && p->next != head) //找到i节点的前驱
    {
        p = p->next;
        j++;
    }
    if (j >= i)
    {
        cout << "error delete" << endl;
        return;
    }
    Node *temp = p->next;
    p->next = p->next->next;
    p->next->pre = p;

    length--;
    rear = head->pre;
    delete temp;
}

Node *List::getNode(int height)
{
    Node *p = head->next;
    while (p->next != head)
    {
        if (p->data.height == height)
            return p;
        p = p->next;
    }
    cout << "Not Found the Node" << endl;
    return NULL; //表示没有找到
};

transaction *List::search_transaction(string txID)
{
    Node *p = head->next;

    while (p != head)
    {

        int index = p->data.search_trans_index(txID);

        if (index != -1)
        {
            return p->data.transactions + index;
        }
        p = p->next;
    }

    return NULL; //表示没有找到
}

int List::getLegal()
{
    int count = 0;
    set<pair<string, int>> s1; //存储所有交易的输出
    map<pair<string, int>, int> v;
    //用交易的 txid和index 来唯一标识一个输出

    //遍历所有区块
    Node *p = head->next;
    for (int i = 1; i <= length; ++i)
    {
        int size = p->data.size;
        for (int j = 0; j < size; ++j)
        {
            int flag;
            flag = p->data.transactions[j].is_legal(s1, v);
            if (flag)
            {
                for (int k = 0; k < (p->data.transactions[j]).output_count; ++k)
                {
                    s1.emplace(make_pair((p->data.transactions[j]).txid, k));
                    v[make_pair((p->data.transactions[j]).txid, k)] = p->data.transactions[j].outputs[k].value;
                }
            }
            count += flag;
        }
        p = p->next;
    }

    return count;
}

void List::display()
{
    cout << "length: " << length << endl;
    Node *p = head->next;
    while (p != head)
    {
        cout << "height:" << p->data.height << endl
             << "hash: " << p->data.hash << "\n\n";
        p = p->next;
    }
}

int List::getIllegal()
{
    Node *p = head->next;
    int sum = 0;
    for (int i = 1; i <= length; ++i)
    {
        for (int j = 0; j < p->data.size; ++j)
            sum += !(p->data.transactions[j].legal);
        p = p->next;
    }
    return sum;
}

void List::clear()
{
    while (length > 0)
    {
        del(1);
    }
}

block List::push_newNode(vector<string> Trans)
{
    hash<int> h;
    Node *node = new Node;
    node->data.preHash = rear->data.hash;
    node->data.hash = to_string(h(rand())); //随机哈希值
    node->data.height = length;
    node->data.Trans = Trans;

    node->next = head;
    head->pre = node;
    rear->next = node; //指向x
    node->pre = rear;
    rear = node;
    length++;
    return node->data;
}

int List::exist(block &b)
{
    Node *p = head;
    for (int i = 0; i < length; ++i)
    {
        p = p->next;
        if (p->data.preHash == b.preHash)
            return 1;
    }
    return 0;
}
void List::set_data(string database)
{
    Node *p = head->next;
    while (p != head)
    {
        p->data.set_data(database);
        p=p->next;
    }
}