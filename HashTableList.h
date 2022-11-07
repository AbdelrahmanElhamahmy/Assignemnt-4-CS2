#include "LinkedList.h"

class HashTableList
{
    int hashtable_size;
    LinkedList *hashtable;
    int insert_count;

public:
    HashTableList();
    HashTableList(int hashtable_size_);
    long long Hash(string str);

    void insert(Employee employee);

    void remove(Employee employee);

    void print();

    double calColissionRate();
};
