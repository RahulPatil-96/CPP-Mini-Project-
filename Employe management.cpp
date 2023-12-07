#include <iostream>
#include <fstream>
#include <limits>
using namespace std;

struct Employee
{
    int id;
    string name;
    string position;
    string salary;
};

bool isNum(const string &str)
{
    for (int c : str)
    {
        if (!isdigit(c))
         return false;
    }
    return true;
}

void AddEmployee(Employee *employee, int n)
{
    try
    {
        if (isNum(employee[n].salary))
         cout << "Record saved.";
        else
         throw employee[n].salary;
    }
    catch(string)
    {
        cout << "Invalid salary input.\nRecord not saved.\n";
    }
   
    ofstream outFile("employee.txt", ios::app);
    outFile.write((char *)&employee[n], sizeof(Employee));
    outFile.close();
}

void ViewEmployee()
{
    ifstream inFile("employee.txt");
    Employee employee;
    cout << "\nEmployee ID\tName\t\tPosition\tSalary\n";
    while (inFile.read((char *)&employee, sizeof(Employee)))
    {
        cout << employee.id << "\t\t" << employee.name << "\t\t" << employee.position << "\t\t" << employee.salary << "\n";
    }
    inFile.close();
}

void SearchRecord(int empId)
{
    ifstream inFile("employee.txt");
    Employee employee;
    bool found = false;

    while (inFile.read((char *)&employee, sizeof(Employee)))
    {
        if (employee.id == empId)
        {
            found = true;
            cout << "\nEmployee found:\n";
            cout << "Employee ID\tName\t\tPosition\tSalary\n";
            cout << employee.id << "\t\t" << employee.name << "\t\t" << employee.position << "\t\t" << employee.salary << "\n";
            break;
        }
    }

    inFile.close();

    if (!found)
    {
        cout << "\nEmployee with ID " << empId << " not found.\n";
    }
}

void DeleteRecord(int empId)
{
    ifstream inFile("employee.txt");
    ofstream tempFile("temp.txt");

    Employee employee;
    bool found = false;

    while (inFile.read((char *)&employee, sizeof(Employee)))
    {
        if (employee.id == empId)
        {
            found = true;
            cout << "\nEmployee with ID " << empId << " deleted.\n";
        }
        else
        {
            tempFile.write((char *)&employee, sizeof(Employee));
        }
    }

    inFile.close();
    tempFile.close();

    remove("employee.txt");
    rename("temp.txt", "employee.txt");

    if (!found)
    {
        cout << "\nEmployee with ID " << empId << " not found.\n";
    }
}

int main()
{
    int choice, n, i = 0;
    Employee employee[50];
    cout << "\n**********MENU**********\n";
    cout << "\n1. Add Employee";
    cout << "\n2. View Employee";
    cout << "\n3. Search Record";
    cout << "\n4. Delete Record";
    cout << "\n5. Exit";

    while (1)
    {
        cout << "\n\nEnter your choice: ";
        cin >> choice;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice)
        {
        case 1:
            cout << "\nEnter the number of employees: ";
            cin >> n;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            for (i = 0; i < n; i++)
            {
                cout << "\n**********Enter details of employee " << i + 1 << "**********\n";
                cout << "ID: ";
                cin >> employee[i].id;
                cout << "Name: ";
                cin.ignore();
                getline(cin, employee[i].name);
                cout << "Position: ";
                getline(cin, employee[i].position);
                cout << "Salary: ";
                getline(cin, employee[i].salary);
                AddEmployee(employee, i);
            }
            break;

        case 2:
            ViewEmployee();
            break;

        case 3:
            int empId;
            cout << "Enter the Employee ID to search: ";
            cin >> empId;
            SearchRecord(empId);
            break;

        case 4:
            cout << "Enter the Employee ID to delete: ";
            cin >> empId;
            DeleteRecord(empId);
            break;  

        case 5:
            cout << "EXIT....";
            break;

        default:
            cout << "\nWrong choice. Try again.";
        }
    }
    return 0;
}
