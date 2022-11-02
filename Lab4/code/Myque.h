#ifndef MYQUE_H
#define MYQUE_H
#include <iostream>
#include <windows.h>
using namespace std;
string preName = "_msg_"; //消息文件前缀
string headname = "Header.txt";

template <class T>
class Myque
{
public:
    int length;           //队列长度
    int top;              //队首
    int tail;             //队尾
    const int size = 100; // the size of queue
    Myque(string str = "");
    int isempty();
    int get_info();
    int pop();
    string dir;
    T get_top();
    void upgradeInfo();
    void set_dir(string str)
    {
        dir = str;
    }
    void clear();
};
template <class T>
Myque<T>::Myque(string str) // top指向节点，tail指向尾节点前一个位置
{

    dir = str;
    length = 0;
    top = 0;
    tail = 0;
    clear();
    upgradeInfo();
}
template <class T>
int Myque<T>::isempty()
{
    get_info();
    if (length == 0)
        return 1;
    return 0;
}
template <class T>
int Myque<T>::get_info()
{
    string fname = dir + headname;
    ifstream file(fname);
    while (file.fail())
    {
        Sleep(50);
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
    return 1;
}
template <class T>
void Myque<T>::upgradeInfo()
{
    string fname = dir + headname;
    ofstream file(fname);
    while (file.fail())
    {
        Sleep(50);
    }
    if (!file.fail())
    {
        file << to_string(length) << "\n"
             << to_string(top) << "\n"
             << to_string(tail) << "\n";
        file.close();
        file.clear();
    }
}
template <class T>
int Myque<T>::pop()
{
    get_info();
    if (length == 0 || tail == top)
    {
        cout << "pop erro! The queue is empty" << endl;
        return 0;
    }
    length--;
    string filename = dir + preName + to_string(top) + ".txt";
    remove(filename.data());
    top = (top + size - 1) % size;
    upgradeInfo();
    return tail != top;
}
template <class T>
T Myque<T>::get_top()
{
    get_info();
    if (!isempty())
    {
        string filename = dir + preName + to_string(top) + ".txt";
        return T(filename);
    }
    return T();
}

template <class T>
void Myque<T>::clear()
{
    for (int i = 0; i < size; ++i)
    {
        string filename = dir + preName + to_string(i) + ".txt";
        ifstream ss(filename);
        if (!ss.fail())
        {
            ss.close();
            ss.clear();
            remove(filename.data());
        }
    }
}
#endif