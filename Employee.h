using namespace std;

class Employee
{
    int salary, age, experience;
    string name;
public:
    Employee();
    Employee(string name, int age, int salary, int experience);
    int get_experience();
    string get_name();
    int get_salary();
    int get_age();
};
