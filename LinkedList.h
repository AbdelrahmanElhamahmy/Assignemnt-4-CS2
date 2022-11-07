#include "Employee.h"

using namespace std;

struct Node
{
    Employee employee;
    Node* next_node;

    Node()
    {
        this->employee = Employee();
        next_node = NULL;
    }

    Node(Employee employee)
    {
        next_node = NULL;
        this->employee = employee;
    }
};


class LinkedList
{
    Node* start;
    Node* end;
    int size_of_list;

public:
    LinkedList();

    void insertNode(Employee employee);

    void printList();

    void removeNode(Employee employee);

    int get_size_of_list();
};
