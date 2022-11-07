#include "HashTableList.h"

class HashTableArray
{
    int insert_count;
    int hashtable_size;
    Employee *hashtable;
    int collision_count;

public:
    HashTableArray();

    HashTableArray(int hashtable_size_);

    long long Hash(string str);
    void insert(Employee employee);

    void remove(Employee employee);

    void print();

    double calColissionRate();
};
