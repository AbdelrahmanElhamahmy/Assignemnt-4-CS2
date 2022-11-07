#include <iostream>
#include "HashTableArray.h"

using namespace std;


Employee::Employee()
{
    salary = age = experience = 0;
    name = "";
}
Employee::Employee(string name, int age, int salary, int experience)
{
    this->experience = experience;
    this->age = age;
    this->salary = salary;
    this->name = name;
}
int Employee::get_experience()
{
    return experience;
}
string Employee::get_name()
{
    return name;
}
int Employee::get_salary()
{
    return salary;
}
int Employee::get_age()
{
    return age;
}



LinkedList::LinkedList()
{
    start = end = NULL;
    size_of_list = 0;
}

void LinkedList::insertNode(Employee employee)
{
    size_of_list++;
    if (start != NULL)
    {
        end->next_node = new Node(employee);
        end = end->next_node;
    }
    else
    {
        start = new Node(employee);
        end = start;
    }
    return;
}

void LinkedList::printList()
{
    Node* n = start;
    for(int i = 0 ; i < size_of_list; ++i)
    {
        if (n == NULL)
        {
            break;
        }

        cout << "name = " << n->employee.get_name() << ", age = " << n->employee.get_age() << ", salary = " << n->employee.get_salary() << ", experience = " << n->employee.get_experience() << endl;
        n = n->next_node;
    }

    cout << endl;
}


bool compareEmployees(Employee employee1, Employee employee2)
{
     if(employee1.get_salary() == employee2.get_salary() && employee1.get_experience() == employee2.get_experience() && employee1.get_age() == employee2.get_age() && employee1.get_name() == employee2.get_name())
     {
         return true;
     }
     else
     {
         return false;
     }
}


HashTableArray::HashTableArray()
{
}

HashTableArray::HashTableArray(int hashtable_size_)
{
    hashtable = new Employee[hashtable_size_];
    collision_count = insert_count = 0;
    hashtable_size = hashtable_size_;
}

long long HashTableArray::Hash(string str)
{
    long long s = 193, h = 0, sz = str.size();
    for(int i = 0 ; i < sz ; ++i)
        h = (h * s) + str[i];
    return s % hashtable_size;
}

void HashTableArray::insert(Employee employee)
{
    int new_index = (Hash(employee.get_name()) + Hash(to_string(employee.get_age())) + Hash(to_string(employee.get_salary())) + Hash(to_string(employee.get_experience()))) % hashtable_size;

    for(int j = 0, i = new_index; j < hashtable_size ; j++)
    {
        i = (i + 1) % hashtable_size;
        if(hashtable[i].get_age() == 0)
        {
            insert_count++;
            hashtable[i] = employee;
            if(i != new_index)
            {
                collision_count++;
            }
            break;
        }
    }
}

void HashTableArray::remove(Employee employee)
{
    int new_index = (Hash(employee.get_name()) + Hash(to_string(employee.get_age())) + Hash(to_string(employee.get_salary())) + Hash(to_string(employee.get_experience()))) % hashtable_size;

    for(int i = new_index, j = 0 ; j < hashtable_size ; j++)
    {
        i = (i + 1) % hashtable_size;
        if(compareEmployees(hashtable[i], employee))
        {
            insert_count--;
            hashtable[i] = Employee();
            if(i != new_index)
            {
                collision_count--;
            }
            break;
        }
    }
}

void HashTableArray::print()
{
    for(int i = 0 ; i < hashtable_size ; ++i)
    {
        cout << "data of Hash ( " << i << " )" << endl << "name = " << hashtable[i].get_name() << ", age = " << hashtable[i].get_age() << ", salary = " << hashtable[i].get_salary() << ", experience = " << hashtable[i].get_experience() << endl;
        cout << endl;
    }
    cout << endl << endl;
}

double HashTableArray::calColissionRate()
{
    if(!insert_count)
    {
        return 0;
    }

    double result = collision_count;
    result /= insert_count;
}



void LinkedList::removeNode(Employee employee)
{
    size_of_list--;
    if (compareEmployees(start->employee, employee))
    {
        Node* deletedNode = start;
        start = start->next_node;
        delete deletedNode;
    }
    else
    {
        Node* n = start;
        while (true)
        {
            if (n == NULL)
            {
                break;
            }
            else if (!compareEmployees(n->next_node->employee, employee))
            {
                n = n->next_node;
            }
            else
            {
                break;
            }
        }

        Node* nodeToBeDeleted = n->next_node;
        Node* n_node = nodeToBeDeleted->next_node;
        if (nodeToBeDeleted == end)
            end = n;
        n->next_node = n_node;
        delete nodeToBeDeleted;
    }

    return;

}

int LinkedList::get_size_of_list()
{
    return size_of_list;
}




HashTableList::HashTableList()
{
}

HashTableList::HashTableList(int hashtable_size_)
{
    insert_count = 0;
    hashtable = new LinkedList[hashtable_size_];
    hashtable_size = hashtable_size;
}

long long HashTableList::Hash(string str)
{
    long long s = 193, h = 0, sz = str.size();
    for(int i = 0 ; i < sz ; ++i)
        h = (h * s) + str[i];
    return s % hashtable_size;
}

void HashTableList::insert(Employee employee)
{
    int hashResult = (Hash(employee.get_name()) + Hash(to_string(employee.get_age())) + Hash(to_string(employee.get_salary())) + Hash(to_string(employee.get_experience()))) % hashtable_size;

    hashtable[hashResult].insertNode(employee);
    insert_count++;
}

void HashTableList::remove(Employee employee)
{
    int hashResult = (Hash(employee.get_name()) + Hash(to_string(employee.get_age())) + Hash(to_string(employee.get_salary())) + Hash(to_string(employee.get_experience()))) % hashtable_size;

    hashtable[hashResult].removeNode(employee);
    insert_count--;
}

void HashTableList::print()
{
    for(int i = 0 ; i < hashtable_size ; i++)
    {
        cout << "data of hash ( " << i << " )";
        cout << endl << endl;
        hashtable[i].printList();
    }
}

double HashTableList::calColissionRate()
{
    if(insert_count == 0)
    {
        return 0;
    }
    double collision_count = 0;
    for(int i = 0 ; i < hashtable_size ; i++)
    {
        int current_size = hashtable[i].get_size_of_list();
        if(current_size >= 1)
        {
            collision_count += (current_size - 1);
        }
    }

    return collision_count / insert_count;
}



int main()
{

    Employee Employee1 = Employee("Mina", 30, 10000, 4);
    Employee Employee2 = Employee("Fawzy", 45, 5000, 8);
    Employee Employee3 = Employee("Yara", 19, 2000, 0);

    HashTableArray ht_array(10);

    ht_array.insert(Employee1);
    ht_array.insert(Employee2);
    ht_array.insert(Employee3);

    ht_array.print();


    HashTableList ht_list(10);

    ht_list.insert(Employee1);
    ht_list.insert(Employee2);
    ht_list.insert(Employee3);

    ht_list.print();

    return 0;
}
