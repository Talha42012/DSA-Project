#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Employee // Employee Node
{
    string name, id, password, email, phone, address, role;
    Employee *next;
};

struct Ride  // Ride Node
{
    string name, id, status, capacity, duration, price;
    Ride *next;
};

Ride *ride_head = NULL;
Ride *ride_tail = NULL;

Employee *emp_head = NULL;
Employee *emp_tail = NULL;

class System
{

    const string admin_ID = "100admin";
    const string admin_password = "admin";

    void LoadEmployeeFromFile() // Load data from Employee.txt
    {
        ifstream file("employee.txt");
        if (file.is_open())
        {
            string name, id, password, email, phone, address, role;

            while (file >> name >> id >> password >> email >> phone >> address >> role)
            {

                Employee *new_employee = new Employee;
                new_employee->name = name;
                new_employee->id = id;
                new_employee->password = password;
                new_employee->email = email;
                new_employee->phone = phone;
                new_employee->address = address;
                new_employee->role = role;

                new_employee->next = NULL;

                if (emp_head == NULL)
                {
                    emp_head = emp_tail = new_employee;
                }
                else
                {
                    emp_tail->next = new_employee;
                    emp_tail = new_employee;
                }
            }
            file.close();
        }
        else
        {
            cout << "No file found. Starting with an empty list.\n";
        }
    }

    void SaveEmployeeToFile() // Save data to Employee.txt
    {
        ofstream file("employee.txt");

        if (file.is_open())
        {
            Employee *temp = emp_head;
            while (temp != NULL)
            {
                file << temp->name << " " << temp->id << " " << temp->password << " "
                     << temp->email << " " << temp->phone << " " << temp->address << " "
                     << temp->role << endl;

                Employee *toDelete = temp;
                temp = temp->next;
                delete toDelete;
            }

            emp_head = NULL;

            file.close();
        }
        else
        {
            cout << "Error opening file for saving.\n";
        }
    }

    bool checkEmpID(string ID) // Cross check ID of Employee
    {
        Employee *temp = emp_head;
        bool found = false;

        while (temp != NULL)
        {
            if (temp->id == ID)
            {
                found = true;
            }

            temp = temp->next;
        }

        return found;
    }

    void AddEmployee() // Add new Employee
    {
        string name, id, password, email, phone, address, role;

        cout << "Enter Employee Name: ";
        cin.ignore();
        getline(cin, name);
    IDAgain:
        cout << "Enter Employee ID: ";
        getline(cin, id);

        if (checkEmpID(id))
        {
            cout << "Employee with the same ID already exsist in record\n";
            cout << "Please enter another ID for this employee" << endl;

            goto IDAgain;
        }

        cout << "Enter Employee Password: ";
        getline(cin, password);

        cout << "Enter Employee Email: ";
        getline(cin, email);

        cout << "Enter Employee Phone: ";
        getline(cin, phone);

        cout << "Enter Employee Address: ";
        getline(cin, address);

        cout << "Enter Employee Role: ";
        getline(cin, role);

        Employee *new_employee = new Employee;

        new_employee->name = name;
        new_employee->id = id;
        new_employee->password = password;
        new_employee->email = email;
        new_employee->phone = phone;
        new_employee->address = address;
        new_employee->role = role;

        new_employee->next = NULL;

        if (emp_head == NULL)
        {
            emp_head = emp_tail = new_employee;
        }

        else
        {
            emp_tail->next = new_employee;
            emp_tail = new_employee;
        }

        cout << "Employee added successfully\n";
    }

    void DisplayEmployees() // Diplay All Employees
    {
        if (emp_head == NULL)
        {
            cout << "No employees to display.\n";
            return;
        }

        Employee *temp = emp_head;
        while (temp != NULL)
        {
            cout << "Name: " << temp->name << ", ID: " << temp->id
                 << ", Role: " << temp->role << ", Email: " << temp->email
                 << ", Phone: " << temp->phone << ", Address: " << temp->address << endl;
            temp = temp->next;
        }
    }

    void SearchEmployee() // Search Employee by ID
    {
        if (emp_head == NULL)
        {
            cout << "No employees to search.\n";
            return;
        }

        string id;
        cout << "Enter Employee ID to search: ";
        cin >> id;

        Employee *temp = emp_head;

        while (temp != NULL && temp->id != id)
        {
            temp = temp->next;
        }

        if (temp == NULL)
        {
            cout << "Employee with ID " << id << " not found.\n";
        }
        else
        {

            cout << "Employee Details:\n"
                 << endl;

            cout << "Name: " << temp->name << "\n"
                 << "ID: " << temp->id << "\n"
                 << "Password: " << temp->password << "\n"
                 << "Email: " << temp->email << "\n"
                 << "Phone: " << temp->phone << "\n"
                 << "Address: " << temp->address << "\n"
                 << "Role: " << temp->role << endl;
        }
    }

    void UpdateEmployee() // Update Employee data with ID
    {
        if (emp_head == NULL)
        {
            cout << "No employees to update.\n";
            return;
        }

        string id;
        cout << "Enter Employee ID to update: ";
        cin >> id;

        Employee *temp = emp_head;

        while (temp != NULL && temp->id != id)
        {
            temp = temp->next;
        }

        if (temp == NULL)
        {
            cout << "Employee with ID " << id << " not found.\n";
            return;
        }

        cout << "Updating details for Employee ID " << id << ":\n";

        cout << "Enter New Name (current: " << temp->name << "): ";
        cin.ignore();
        getline(cin, temp->name);

        cout << "Enter New Password (current: " << temp->password << "): ";
        getline(cin, temp->password);

        cout << "Enter New Email (current: " << temp->email << "): ";
        getline(cin, temp->email);

        cout << "Enter New Phone (current: " << temp->phone << "): ";
        getline(cin, temp->phone);

        cout << "Enter New Address (current: " << temp->address << "): ";
        getline(cin, temp->address);

        cout << "Enter New Role (current: " << temp->role << "): ";
        getline(cin, temp->role);

        cout << "Employee details updated successfully.\n";
    }

    void DeleteEmployee() // Delete employee from Employee.txt
    {
        if (emp_head == NULL)
        {
            cout << "No employees to delete.\n";
            return;
        }

        string id;
        cout << "Enter Employee ID to delete: ";
        cin >> id;

        Employee *temp = emp_head;
        Employee *prev = NULL;

        while (temp != NULL && temp->id != id)
        {
            prev = temp;
            temp = temp->next;
        }

        if (temp == NULL)
        {
            cout << "Employee with ID " << id << " not found.\n";
            return;
        }

        if (temp == emp_head)
        {
            emp_head = emp_head->next;

            if (emp_tail == temp)
                emp_tail = NULL;
        }

        else
        {
            prev->next = temp->next;
            if (emp_tail == temp)
            {
                emp_tail = prev;
            }
        }

        delete temp;
        cout << "Employee with ID " << id << " deleted successfully.\n";
    }

    void LoadRidesFromFile() // Load Rides from Rides.txt
    {
        ifstream file("rides.txt");
        if (file.is_open())
        {
            string name, id, status, capacity, duration, price;

            while (file >> name >> id >> status >> capacity >> duration >> price)
            {
                Ride *new_ride = new Ride;
                new_ride->name = name;
                new_ride->id = id;
                new_ride->status = status;
                new_ride->capacity = capacity;
                new_ride->duration = duration;
                new_ride->price = price;

                new_ride->next = NULL;

                if (ride_head == NULL)
                {
                    ride_head = ride_tail = new_ride;
                }
                else
                {
                    ride_tail->next = new_ride;
                    ride_tail = new_ride;
                }
            }
            file.close();
        }
        else
        {
            cout << "No file found. Starting with an empty ride list.\n";
        }
    }

    void SaveRidesToFile() // Save Data to Rides.txt
    {
        ofstream file("rides.txt");
        if (file.is_open())
        {
            Ride *temp = ride_head;
            while (temp != NULL)
            {
                file << temp->name << " " << temp->id << " " << temp->status << " "
                     << temp->capacity << " " << temp->duration << " " << temp->price << endl;
                temp = temp->next;
            }
            file.close();
        }
        else
        {
            cout << "Error opening file for saving rides.\n";
        }
    }

    bool CheckRideID(string ID) // Cross Check Ride ID
    {
        Ride *temp = ride_head;
        while (temp != NULL)
        {
            if (temp->id == ID)
                return true;
            temp = temp->next;
        }
        return false;
    }

    void AddRide() // Add new ID
    {
        string name, id, status, capacity, duration, price;

        cout << "Enter Ride Name: ";
        cin.ignore();
        getline(cin, name);
    IDAgain:
        cout << "Enter Ride ID: ";
        getline(cin, id);
        if (CheckRideID(id))
        {
            cout << "Ride with the same ID already exists.\n";
            cout << "Please enter another ID.\n";
            goto IDAgain;
        }

        cout << "Enter Ride Status (Working, Not Working): ";
        getline(cin, status);

        cout << "Enter Ride Capacity: ";
        getline(cin, capacity);

        cout << "Enter Ride Duration (in minutes): ";
        getline(cin, duration);

        cout << "Enter Ride Price: ";
        getline(cin, price);

        Ride *new_ride = new Ride;
        new_ride->name = name;
        new_ride->id = id;
        new_ride->status = status;
        new_ride->capacity = capacity;
        new_ride->duration = duration;
        new_ride->price = price;
        new_ride->next = NULL;

        if (ride_head == NULL)
        {
            ride_head = ride_tail = new_ride;
        }
        else
        {
            ride_tail->next = new_ride;
            ride_tail = new_ride;
        }

        cout << "Ride added successfully!\n";
    }

    void DisplayRides() // Display All Rides
    {
        if (ride_head == NULL)
        {
            cout << "No rides to display.\n";
            return;
        }

        Ride *temp = ride_head;
        while (temp != NULL)
        {
            cout << "Name: " << temp->name << ", ID: " << temp->id
                 << ", Status: " << temp->status << ", Capacity: " << temp->capacity
                 << ", Duration: " << temp->duration << " mins, Price: " << temp->price << endl;
            temp = temp->next;
        }
    }

    void SearchRide() // Search Rides by ID
    {
        if (ride_head == NULL)
        {
            cout << "No rides to search.\n";
            return;
        }

        string id;
        cout << "Enter Ride ID to search: ";
        cin >> id;

        Ride *temp = ride_head;
        while (temp != NULL && temp->id != id)
        {
            temp = temp->next;
        }

        if (temp == NULL)
        {
            cout << "Ride with ID " << id << " not found.\n";
        }
        else
        {
            cout << "Ride Details:\n"
                 << "Name: " << temp->name << "\n"
                 << "ID: " << temp->id << "\n"
                 << "Status: " << temp->status << "\n"
                 << "Capacity: " << temp->capacity << "\n"
                 << "Duration: " << temp->duration << " mins\n"
                 << "Price: " << temp->price << endl;
        }
    }

    void UpdateRide() // Update Ride by ID
    {
        if (ride_head == NULL)
        {
            cout << "No rides to update.\n";
            return;
        }

        string id;
        cout << "Enter Ride ID to update: ";
        cin >> id;

        Ride *temp = ride_head;
        while (temp != NULL && temp->id != id)
        {
            temp = temp->next;
        }

        if (temp == NULL)
        {
            cout << "Ride with ID " << id << " not found.\n";
            return;
        }

        cout << "Updating details for Ride ID " << id << ":\n";

        cout << "Enter New Name (current: " << temp->name << "): ";
        cin.ignore();
        getline(cin, temp->name);

        cout << "Enter New Status (current: " << temp->status << "): ";
        getline(cin, temp->status);

        cout << "Enter New Capacity (current: " << temp->capacity << "): ";
        getline(cin, temp->capacity);

        cout << "Enter New Duration (current: " << temp->duration << "): ";
        getline(cin, temp->duration);

        cout << "Enter New Price (current: " << temp->price << "): ";
        getline(cin, temp->price);

        cout << "Ride details updated successfully.\n";
    }

    void DeleteRide() // Delete Ride Bt ID
    {
        if (ride_head == NULL)
        {
            cout << "No rides to delete.\n";
            return;
        }

        string id;
        cout << "Enter Ride ID to delete: ";
        cin >> id;

        Ride *temp = ride_head;
        Ride *prev = NULL;

        while (temp != NULL && temp->id != id)
        {
            prev = temp;
            temp = temp->next;
        }

        if (temp == NULL)
        {
            cout << "Ride with ID " << id << " not found.\n";
            return;
        }

        if (temp == ride_head)
        {
            ride_head = ride_head->next;

            if (ride_tail == temp)
            {
                ride_tail = NULL;
            }
        }
        else
        {
            prev->next = temp->next;
            if (ride_tail == temp)
            {
                ride_tail = prev;
            }
        }

        delete temp;
        cout << "Ride with ID " << id << " deleted successfully.\n";
    }

    void AdminEmployeeMenu() // Admin Menu of Employee Functions
    {
        LoadEmployeeFromFile();

        int choice;
        do
        {
        xAgain:
            cout << endl
                 << "1. Add Employee\n"
                 << "2. Display Employees\n"
                 << "3. Search Employee\n"
                 << "4. Update Employee\n"
                 << "5. Delete Employee\n"
                 << "6. Main Menu\n"
                 << endl;
            cout << "Enter your choice: ";
            cin >> choice;
            cout << endl;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                cout << "Invalid input. Please enter a number.\n";
                goto xAgain;
            }

            switch (choice)
            {
            case 1:
                AddEmployee();
                break;
            case 2:
                DisplayEmployees();
                break;
            case 3:
                SearchEmployee();
                break;
            case 4:
                UpdateEmployee();
                break;
            case 5:
                DeleteEmployee();
                break;
            case 6:
                SaveEmployeeToFile();
                AdminMenu();
                break;
            default:
                cout << "Invalid choice. Try again.\n";
            }
        } while (choice != 6);
    }

    void AdminRideMenu() // Admin Menu of Ride Functions
    {
        LoadRidesFromFile();

        int choice;
        do
        {
        xAgain1:
            cout << endl
                 << "1. Add Ride\n"
                 << "2. Display Rides\n"
                 << "3. Search Ride\n"
                 << "4. Update Ride\n"
                 << "5. Delete Ride\n"
                 << "6. Main Menu\n"
                 << endl

                 << "Enter your choice: ";
            cin >> choice;

            if (cin.fail())
            {
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                cout << "Invalid input. Please enter a number.\n";
                goto xAgain1;
            }

            switch (choice)
            {
            case 1:
                AddRide();
                break;
            case 2:
                DisplayRides();
                break;
            case 3:
                SearchRide();
                break;
            case 4:
                UpdateRide();
                break;
            case 5:
                DeleteRide();
                break;
            case 6:
                SaveRidesToFile();
                AdminMenu();
                break;
            default:
                cout << "Invalid choice. Try again.\n";
            }
        } while (choice != 6);
    }

    void ViewBookings() // View Bookings from bookings.txt
    {
        string custName, rideName, id;
        int qunatitity;
        double cost;
        ifstream booking("bookings.txt");
        cout << "Booking ID " << "  " << "Ride Name " << "  " << "Tickets Sold " << "  " << " Total Price " << endl
             << endl;
        while (booking >> custName >> rideName >> qunatitity >> cost >> id)

        {
            cout << id << "  " << rideName << "  " << qunatitity << "  " << cost << " " << endl;
        }

        booking.close();
    }

    void ViewEmpAttendence() // View Employee attendance from attendance.txt
    {
        ifstream attend("attendance.txt");

        string id, name, date;

        int choice;

        cout << "1. View All Employees Attendence" << endl;
        cout << "2. View Individual Employee Attendence" << endl
             << endl;

        cout << "Enter choice: ";
        cin >> choice;
        cout << endl;
        if (choice == 1)
        {

            while (attend >> id >> name)
            {
                attend.ignore();
                getline(attend, date);

                cout << "ID: " << id << " named: " << name << " present on " << date << endl;
            }

            attend.close();
        }

        else
        {
            string ID1;
            bool found = false;

            cout << "Enter Employee ID: ";
            cin >> ID1;

            while (attend >> id >> name)
            {
                attend.ignore();
                getline(attend, date);

                if (id == ID1)
                {
                    found = true;
                    cout << name << " was present on " << date << endl;
                }
            }

            attend.close();

            if (found == false)
            {
                cout << "Employee ID is incorrect. Enter correct ID" << endl;
                return;
            }
        }
        cout << endl;
        cout << endl;
    }

    void ViewSales() // View sales 
    {
        string custName, rideName, id;
        int qunatitity;
        int choice;
        double cost;
        double totalCost = 0;
        ifstream sale("bookings.txt");

        cout << "1. View Single Ride Sale" << endl;
        cout << "2. View All Rides Sale" << endl
             << endl;

        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1)
        {
            totalCost = 0;

            bool found = false;
            string Rname;

            int count = 1;

            cout << "Enter Ride name: ";
            cin >> Rname;

            while (sale >> custName >> rideName >> qunatitity >> cost >> id)
            {

                if (Rname == rideName)
                {
                    found = true;
                    cout << "Sale no: " << count << " is " << cost << endl;
                    count++;
                    totalCost += cost;
                }
            }

            if (found == false)
            {
                cout << "Ride name is incorrect. Enter correct name" << endl;
                return;
            }

            sale.close();

            cout << Rname << " total sale is " << totalCost << endl;
        }

        else
        {
            totalCost = 0;

            while (sale >> custName >> rideName >> qunatitity >> cost >> id)
            {

                cout << rideName << " sale is " << cost << " " << endl;
                totalCost += cost;
            }

            sale.close();

            cout << "Total Sale of All rides is " << totalCost << endl;
        }
    }

    void ViewunorderRides() // View Unordered Rides from rides.txt
    {
        string name, id, status, capacity, duration, price;
        bool found = false;
        ifstream ride("rides.txt");

        while (ride >> name >> id >> status >> capacity >> duration >> price)
        {
            if (status == "Notworking" || status == "notworking")
            {
                found = true;
                cout << name << " is out of order" << endl;
            }
        }
        ride.close();
        if (found == false)
        {
            cout << "No ride is out of order" << endl;
            return;
        }
    }

    void ViewComplaints() // View complaints from complaints.txt
    {
        int count = 1;
        string complaint, name;

        ifstream comp("complaints.txt");

        while (comp >> name)
        {
            comp.ignore();
            getline(comp, complaint);

            cout << name << " have this compliant:  " << complaint << endl
                 << endl;
        }

        comp.close();
    }

    void ClearAttendance() // Empty attendance.txt
    {
        ofstream clear("attendance.txt", ios::trunc);

        clear.close();

        cout<<"Attendance record cleard"<<endl<<endl;
    }

    void ClearCompliants() // empty complaints.txt
    {
        ofstream clear("complaints.txt", ios::trunc);

        clear.close();

         cout<<"Complaints record cleard"<<endl<<endl;
    }

    void StaticticMenu() // Admin Menu of Statictic Functions
    {
        int choice;

        while (true)
        {
        xAgain8:
            cout << endl;
            cout << "1. View Employee Attendance" << endl;
            cout << "2. View Bookings Record" << endl;
            cout << "3. View Daily Sales" << endl;
            cout << "4. View Unorder Rides" << endl;
            cout << "5. View Compliants" << endl;
            cout << "6. Clear Attendance Record" << endl;
            cout << "7. Clear Complaints Record" << endl;
            cout << "8. Main Menu" << endl
                 << endl;
            cout << "Enter your choice: ";

            cin >> choice;
            cout << endl;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                cout << "Invalid input. Please enter a number.\n";
                goto xAgain8;
            }

            switch (choice)
            {
            case 1:
                cout << "You selected View Employees Attendance." << endl
                     << endl;
                ViewEmpAttendence();

                break;
            case 2:
                cout << "You selected View Booking Records." << endl
                     << endl;
                ViewBookings();

                break;
            case 3:
                cout << "You selected View Daily Sales." << endl
                     << endl;
                ViewSales();
                break;

            case 4:
                cout << "You selected View Unordered Rides." << endl
                     << endl;
                ViewunorderRides();
                break;

            case 5:
                cout << "You selected View Complaints." << endl
                     << endl;
                ViewComplaints();
                break;

            case 6:
                cout << "You selected Clear Attendance Record." << endl
                     << endl;
                ClearAttendance();
                break;

            case 7:
                cout << "You selected Clear Complaints Record." << endl
                     << endl;
                     ClearCompliants();
                break;

            case 8:
                cout << "Exiting to Main Menu" << endl
                     << endl;
                AdminMenu();
                break;

            default:
                cout << "Invalid choice, please try again." << endl;
            }
        }
    }

    void AdminMenu() // Main Admin menu
    {
        int choice;

        while (true)
        {

        xAgain2:
            cout << "--------------------------" << endl;
            cout << "       Admin Menu         " << endl;
            cout << "--------------------------" << endl;
            cout << "1. Employees" << endl;
            cout << "2. Rides" << endl;
            cout << "3. Statistics" << endl;
            cout << "4. Exit" << endl
                 << endl;
            cout << "Enter your choice: ";

            cin >> choice;

            cout << endl;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                cout << "Invalid input. Please enter a number.\n";
                goto xAgain2;
            }

            switch (choice)
            {
            case 1:
                cout << "You selected Employees." << endl
                     << endl;
                AdminEmployeeMenu();

                break;
            case 2:
                cout << "You selected Rides." << endl
                     << endl;
                AdminRideMenu();

                break;
            case 3:
                cout << "You selected Statistics." << endl;
                StaticticMenu();
                break;
            case 4:
                cout << "Exiting the admin panel." << endl;
                exit(0);
                break;

            default:
                cout << "Invalid choice, please try again." << endl;
            }
        }
    }

    void EmployeeViewProfile(string ID) // Employee view profile 
    {
        Employee *temp = emp_head;

        while (temp != NULL)
        {
            if (temp->id == ID)
            {
                cout << "Name: " << temp->name << ", ID: " << temp->id
                     << ", Role: " << temp->role << ", Email: " << temp->email
                     << ", Phone: " << temp->phone << ", Address: " << temp->address << endl;
                return;
            }

            temp = temp->next;
        }
    }

    void EmployeeChangePassword(string EmpID) // Change password of employee
    {

        Employee *temp = emp_head;
        string oldPassword, newPassword;

        while (temp != NULL)
        {
            if (temp->id == EmpID)
            {

                cout << "Enter current password: ";
                cin >> oldPassword;

                if (oldPassword == temp->password)
                {
                    cout << "Enter new password: ";
                    cin >> newPassword;

                    temp->password = newPassword;
                    cout << "Password changed successfully!" << endl;
                    return;
                }
                else
                {
                    cout << "Incorrect current password. Please try again." << endl;
                    return;
                }
            }
            temp = temp->next;
        }
        cout << "Employee with ID " << EmpID << " not found." << endl;
    }

    void EmployeeMarkAttendance(string EmpID) // Employee mark attendance
    {
        Employee *temp = emp_head;

        while (temp != NULL)
        {
            if (temp->id == EmpID)
            {
                ofstream attendanceFile("attendance.txt", ios::app);
                if (attendanceFile.is_open())
                {
                    attendanceFile << temp->id << " " <<" "<< temp->name <<" "<< __DATE__ << endl;
                    attendanceFile.close();
                    cout << "Attendance marked successfully!" << endl;
                    return;
                }
                else
                {
                    cout << "Error marking attendance." << endl;
                }
            }
            temp = temp->next;
        }
        cout << "Employee with ID " << EmpID << " not found." << endl;
    }

    void EmployeePortal(string EmpID) // Employee Menu
    {
        LoadEmployeeFromFile();

        int choice;
        while (true)
        {
        xAgain3:
            cout << "------- Employee Portal -------" << endl <<endl;
            cout << "1. View Profile" << endl;
            cout << "2. Change Password" << endl;
            cout << "3. Mark Attendance" << endl;
            cout << "4. Exit" << endl
                 << endl;

            cout << "Enter your choice: ";
            cin >> choice;

            if (cin.fail())
            {
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                cout << "Invalid input. Please enter a number.\n";
                goto xAgain3;
            }
            switch (choice)
            {
            case 1:
                EmployeeViewProfile(EmpID);
                break;
            case 2:
                EmployeeChangePassword(EmpID);
                break;
            case 3:
                EmployeeMarkAttendance(EmpID);
                break;
            case 4:
                SaveEmployeeToFile();
                cout << "Exiting Employee Portal. Goodbye!" << endl;
                exit(0);

            default:
                cout << "Invalid choice, please try again." << endl;
            }
        }
    }

public:
    void login() // Login for employee and admin
    {
        cout << endl;
        string ID, password1;
        string name, id, password, email, phone, address, role;

        bool found = false;

        cout << "Enter ID: ";
        cin >> ID;

        cout << "Enter pssword: ";
        cin >> password1;

        cout << endl;

        if (admin_password == password1 && admin_ID == ID)
        {
            found = true;
            AdminMenu();
        }

        else
        {
            ifstream file("employee.txt");

            while (file >> name >> id >> password >> email >> phone >> address >> role)
            {
                if (ID == id && password1 == password)
                {
                    found = true;
                    EmployeePortal(ID);
                    break;
                }
            }
        }

        if (found == false)
        {
            int choice1;

            cout << endl

                 << "User ID or Password is incorrect" << endl
                 << endl;

            cout << "1. Try Again" << endl;
            cout << "2. Exit" << endl
                 << endl;

            cout << "Enter your choice: ";
            cin >> choice1;

            if (choice1 == 1)
            {
                login();
            }
            else
            {
                cout << "Exiting...";
                exit(0);
            }
        }
        cout << endl;
    }
};

int main()
{

    System obj;
    obj.login();
    return 0;
}
