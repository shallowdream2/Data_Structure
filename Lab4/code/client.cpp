#include"Guest.h"
using namespace std;
int main()
{
    string dir1="D:\\Working\\Project\\HomeWork\\Data_Structure\\Lab4\\server1\\";
    string dir2="D:\\Working\\Project\\HomeWork\\Data_Structure\\Lab4\\server2\\";
    string database="D:\\Working\\Project\\HomeWork\\Data_Structure\\Lab4\\demo\\demo\\";
    vector<string>t;
    t.push_back(dir1);
    t.push_back(dir1);
    guest myGuest(t,database+"transactions.csv",200);
    myGuest.Run();
    system("pause");

}