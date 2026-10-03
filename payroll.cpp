#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Employee
{
public:
    int id;
    string name;
    string department;
    float basicSalary;

    float calculateSalary()
    {
        float hra = basicSalary * 0.20;
        float da = basicSalary * 0.10;
        float bonus = basicSalary * 0.05;

        return basicSalary + hra + da + bonus;
    }
};

vector<Employee> employees;

void saveToFile()
{
    ofstream fout("employees.txt");

    for(auto e : employees)
    {
        fout << e.id << endl;
        fout << e.name << endl;
        fout << e.department << endl;
        fout << e.basicSalary << endl;
    }

    fout.close();
}

void loadFromFile()
{
    employees.clear();

    ifstream fin("employees.txt");

    Employee e;

    while(fin >> e.id)
    {
        fin.ignore();

        getline(fin, e.name);
        getline(fin, e.department);

        fin >> e.basicSalary;
        fin.ignore();

        employees.push_back(e);
    }

    fin.close();
}

void addEmployee()
{
    Employee e;

    cout << "\nEnter Employee ID : ";
    cin >> e.id;

    cin.ignore();

    cout << "Enter Name : ";
    getline(cin, e.name);

    cout << "Enter Department : ";
    getline(cin, e.department);

    cout << "Enter Basic Salary : ";
    cin >> e.basicSalary;

    employees.push_back(e);

    saveToFile();

    cout << "\nEmployee Added Successfully\n";
}

void displayEmployees()
{
    if(employees.size()==0)
    {
        cout << "\nNo Records Found\n";
        return;
    }

    cout << "\n===== EMPLOYEE RECORDS =====\n";

    for(auto e : employees)
    {
        cout << "\nID : " << e.id;
        cout << "\nName : " << e.name;
        cout << "\nDepartment : " << e.department;
        cout << "\nBasic Salary : " << e.basicSalary;
        cout << "\nTotal Salary : " << e.calculateSalary();
        cout << "\n----------------------------\n";
    }
}

void searchEmployee()
{
    int searchId;

    cout << "\nEnter Employee ID : ";
    cin >> searchId;

    bool found=false;

    for(auto e : employees)
    {
        if(e.id==searchId)
        {
            cout << "\nEmployee Found\n";

            cout << "ID : " << e.id << endl;
            cout << "Name : " << e.name << endl;
            cout << "Department : " << e.department << endl;
            cout << "Salary : " << e.calculateSalary() << endl;

            found=true;
        }
    }

    if(!found)
    {
        cout << "\nEmployee Not Found\n";
    }
}

void updateEmployee()
{
    int searchId;

    cout << "\nEnter Employee ID To Update : ";
    cin >> searchId;

    bool found=false;

    for(int i=0;i<employees.size();i++)
    {
        if(employees[i].id==searchId)
        {
            cin.ignore();

            cout << "Enter New Name : ";
            getline(cin, employees[i].name);

            cout << "Enter New Department : ";
            getline(cin, employees[i].department);

            cout << "Enter New Salary : ";
            cin >> employees[i].basicSalary;

            saveToFile();

            found=true;

            cout << "\nRecord Updated Successfully\n";
        }
    }

    if(!found)
    {
        cout << "\nEmployee Not Found\n";
    }
}

void deleteEmployee()
{
    int searchId;

    cout << "\nEnter Employee ID To Delete : ";
    cin >> searchId;

    bool found=false;

    for(int i=0;i<employees.size();i++)
    {
        if(employees[i].id==searchId)
        {
            employees.erase(employees.begin()+i);

            saveToFile();

            found=true;

            cout << "\nEmployee Deleted Successfully\n";
            break;
        }
    }

    if(!found)
    {
        cout << "\nEmployee Not Found\n";
    }
}

void generatePayslip()
{
    int searchId;

    cout << "\nEnter Employee ID : ";
    cin >> searchId;

    bool found=false;

    for(auto e : employees)
    {
        if(e.id==searchId)
        {
            float hra=e.basicSalary*0.20;
            float da=e.basicSalary*0.10;
            float bonus=e.basicSalary*0.05;

            cout << "\n========== PAY SLIP ==========\n";

            cout << "Employee ID : " << e.id << endl;
            cout << "Name : " << e.name << endl;
            cout << "Department : " << e.department << endl;

            cout << "\nBasic Salary : " << e.basicSalary << endl;
            cout << "HRA (20%)    : " << hra << endl;
            cout << "DA (10%)     : " << da << endl;
            cout << "Bonus (5%)   : " << bonus << endl;

            cout << "------------------------------\n";

            cout << "Net Salary   : "
                 << e.calculateSalary() << endl;

            cout << "==============================\n";

            found=true;
        }
    }

    if(!found)
    {
        cout << "\nEmployee Not Found\n";
    }
}

int main()
{
    loadFromFile();

    int choice;

    do
    {
        cout << "\n\n===== PAYROLL MANAGEMENT SYSTEM =====";

        cout << "\n1. Add Employee";
        cout << "\n2. Display Employees";
        cout << "\n3. Search Employee";
        cout << "\n4. Update Employee";
        cout << "\n5. Delete Employee";
        cout << "\n6. Generate Pay Slip";
        cout << "\n7. Exit";

        cout << "\nEnter Choice : ";
        cin >> choice;

        switch(choice)
        {
            case 1:
                addEmployee();
                break;

            case 2:
                displayEmployees();
                break;

            case 3:
                searchEmployee();
                break;

            case 4:
                updateEmployee();
                break;

            case 5:
                deleteEmployee();
                break;

            case 6:
                generatePayslip();
                break;

            case 7:
                cout << "\nThank You!";
                break;

            default:
                cout << "\nInvalid Choice";
        }

    } while(choice!=7);

    return 0;
}