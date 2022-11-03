#ifndef SERVER_H
#define SERVER_H
#include "Trans_pool.h"
#include "List.cpp"
#include "Myque.h"
#include "Guest_msg.h"
#include "Block_msg.h"
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <iostream>
using namespace std;

class server
{
public:
    List L; // The block list
    Myque<msgNode> G_que;
    Myque<Block_msg> B_que;
    Trans_pool myTrans;
    string targetDir;
    string database;
    server(string dir = "", string str = "", string database = "");
    void Run();
};
server::server(string dir, string str, string database) : G_que(dir + "G_que\\"), B_que(dir + "B_que\\")
{
    targetDir = str;
    this->database = database;
};
void server::Run()
{
    srand((unsigned)time(NULL));
    int count = 0;
    while (1)
    {
        if (count == 100)
            break;
        ++count;
        int cnt = rand() % 100;
        if (cnt <= 50 && cnt >= 0) //中奖
        {

            if (myTrans.length > 0)
            {
                cout << "Get new block!" << endl;
                vector<string> ans = myTrans.get_trans(1);
                block msg = L.push_newNode(ans);
                Block_msg Msg(msg);
                //暂时关闭发送功能
                Msg.sendmsg(targetDir);
            }
        }
        else
        {
            if (!B_que.isempty())
            {
                Block_msg bm = B_que.get_top();
                B_que.pop();
                block b = bm.to_block();
                if (!L.exist(b))
                {
                    Node *node = new Node;
                    node->data = b;
                    node->data.height = L.length;
                    L.insert(node, L.length + 1); //插入区块
                    //更新交易池
                    myTrans.DEL(b.Trans);
                }
            }
            else
            {
                if (!G_que.isempty())
                {
                    msgNode msg = G_que.get_top();
                    cout << "type: " << msg.type << "\n"
                         << "data: " << msg.data << endl;
                    if (!G_que.isempty())
                        G_que.pop();
                    if (msg.type == "0") //交易
                    {
                        if (!myTrans.exist(msg.data))
                        {
                            myTrans.push(msg.data);
                        }
                    }
                    else if (msg.type == "1") //按height查询区块
                    {
                        L.set_data(this->database);
                        Node *node = L.getNode(stoi(msg.data));
                        if (node == NULL)
                        {
                            cout << "Can not found the block." << endl;
                        }
                        else
                        {
                            node->data.display();
                        }
                        cout << endl;
                    }
                    else if (msg.type == "2") //按id查询交易
                    {
                        L.set_data(this->database);
                        transaction *tr = L.search_transaction(msg.data);
                        if (tr == NULL)
                        {
                            cout << "Can not found the transaction." << endl;
                        }
                        else
                        {
                            tr->display();
                        }
                        cout << endl;
                    }
                    else if (msg.type == "3")
                    {
                        L.set_data(this->database);
                        L.display();
                        cout << endl;
                    }
                }
            }
        }
        Sleep(200);
    }
}

#endif
