#include "block.h"

block::block(int x1, string x2, string x3)
{
   height = x1;
   hash = x2;
   preHash = x3;
   size = 0;
};

block::block()
{
   height = 0;
   hash = "";
   preHash = "";
   size = 0;
};

int block::search_trans_index(string txid)
{
   for (int i = 0; i < size; ++i)
   {
      if (txid == transactions[i].txid)
         return i;
   }
   return -1;
};

void block::display()
{
   cout << "block" << endl;
   cout << "height: " << height << endl;
   cout << "hash: " << hash << endl;
   cout << "prehash: " << preHash << endl;
   cout << "size of transaction: " << size << endl;
   /*
   for(int i=0;i<size;++i)
   {
      transactions[i].display();
   }
   */
   cout << endl;
}

void block::set_data(string data_base)
{
   ifstream file(data_base+"transactions.csv");
   int len = Trans.size();
   int i = 0;
   string str;
   getline(file, str);
   while (getline(file, str))
   {
      if (i == len)
         break;
      ++i;
      int height;
      string txid;
      int is_coinbase;
      int input_count;
      int output_count;
      string str2;
      stringstream ss(str);
      getline(ss, str2, ','); // height
      height = stoi(str2);

      getline(ss, txid, ',');

      getline(ss, str2, ',');
      is_coinbase = stoi(str2);

      getline(ss, str2, ',');
      input_count = stoi(str2);

      getline(ss, str2);
      output_count = stoi(str2);
      if(Trans[i]==txid)
      {
         transactions[i]=transaction(txid, is_coinbase, input_count, output_count);
         transactions[i].set_data(data_base);
      }
   }
}