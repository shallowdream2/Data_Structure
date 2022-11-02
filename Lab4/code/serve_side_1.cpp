#include"Server.h"
#include"Guest.h"
using namespace std;
int main()
{
    string dir1="D:\\Working\\Project\\HomeWork\\Data_Structure\\Lab4\\server1\\";
    string dir2="D:\\Working\\Project\\HomeWork\\Data_Structure\\Lab4\\server2\\";
    string database="D:\\Working\\Project\\HomeWork\\Data_Structure\\Lab4\\demo\\demo\\";
    server ser1(dir1,dir2,database);
    ser1.Run();
    //测试结果表明客户交易功能没问题
    system("pause");

}