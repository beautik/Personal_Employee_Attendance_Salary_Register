#include <iostream>     // It is Used For Basic I/O Operations.
#include<conio.h>
#include <fstream>      // It is Used For File I/O Operations.
#include <limits>       // It is Used For Get Numeric Limits.
#include <cstring>      // It is Used For C String Handling.
using namespace std;

const bool isEmpty(ifstream &file);
const bool validateInput();
const char *fileName = "file1.dat";

const bool validateInput()
{
    if (cin.fail())
    {
        // Restore input stream
        cin.clear();
        // Clear The All Previous Input Before the '\n' Character
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // Throwing Error and Again Input Value From User
        cout << "\n\tError : inValid Value Detected! Please Enter Valid Value Again\n\n";
        return true;
    }
    else
    {
        return false;
    }
}
const bool isEmpty(ifstream &file)
{
    return (file.peek() == ifstream::traits_type::eof());
}

class Admin
{
    private:
    int id;
    char name[100], post[100], department[100];
    double salary;
    int total_w_d,leave_d,half_l_d;
    float work_h,total_w_h,hour_l,total_l_h,t_l_d,e_t_w_d;
    int wages;
	double days,basic,HRA,DA,PF,netsalary;

public:
    // default constructor function
    Admin()
    {
        // Default Initialization Except Garbage Value
        id = 0;
        strcpy(name, "no name");
        strcpy(name, "no post");
        strcpy(name, "no department");
        salary = 0;
    }
public:
    // member function
    void login();
    int submenu();
    void getData();             // function to get Employees Record From User.
    void writeFile();           // function to Write Employees Records in a file that get From User.
    void readFile();            // function to Read Employees Records from a file.
    void showData();
    void showAllData();            // function to Print All Employees Records that Read From a File.
    void searchData(int input); // function to search Data from file.
    void updateData(int input); // function to Update Data from file.
    void deleteData(int input); // function to Delete Data from file.
    void sortData();            // function to Sorts Employees Data in Desending Order w.r.t Salary.
    void addAttendance(int input);
    void showAttendance(int input);
    void showSalary(int input);

};

void Admin::getData()
{
//    system("cls");
    bool flag = false;

 //   cout<<"\n\t<<============Enter Employee Record=============>>";
label1:
    cout << "\n\n\tEnter Employee Name : ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.getline(name, 100);
    flag = validateInput();
    if (flag)
        goto label1;


label2:
    cout << "\tEnter Employee Unique ID : ";
    cin >> id;
    flag = validateInput();
    if (flag)
        goto label2;


label3:
    cout << "\tEnter Employee Post : ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.getline(post, 100);
    flag = validateInput();
    if (flag)
        goto label3;


label4:
    cout << "\tEnter Employee Department : ";
    cin.getline(department, 100);
    flag = validateInput();
    if (flag)
        goto label4;


label5:
    cout << "\tEnter Employee Salary per day : ";
    cin >> salary;
    flag = validateInput();
    if (flag)
        goto label5;
}

void Admin::writeFile()
{
        system("cls");
    if (name == "no name" && id == 0)
    {
        cout << "\tEmployee Record is not initalized" << endl;
    }
    else
    {
        fstream file;
        file.open("E://emp_sal//emp1.txt", ios::out | ios::app | ios::binary);

        file.write((char *)this, sizeof(*this));

        file.close();

        if (!file.good()) {
            // For Check Any Error After Writing the file. For Example File Memory Full, File Format Errors.
            cout << "\tError occurred at writing time!" << endl;
        }
    }
}

void Admin::readFile()
{
        system("cls");
    ifstream file;
    file.open("E://emp_sal//emp1.txt", ios::in | ios::binary);

    if (!file)
    {
        cout << "\tFile can not Open";
    }
    else
    {
        if (isEmpty(file))
        {
            cout << "\n\tYour File is Empty! No Record is Avialable to Show\n";
        }
        else
        {
            file.read((char *)this, sizeof(*this));

            while (!file.eof())
            {
                showData();
                file.read((char *)this, sizeof(*this));
            }

            file.close();
        }
    }
}

void Admin::showData()
{
 //       system("cls");
//    cout<<"\n\t<<============All Employee Record=============>>";
    cout << "\n\n\tEmployee Name is : ";
    cout << name << endl;

    cout << "\tEmployee ID is : ";
    cout << id << endl;

    cout << "\tEmployee post is : ";
    cout << post << endl;

    cout << "\tEmployee Department is : ";
    cout << department << endl;

    cout << "\tEmployee Salary per day (wages) is : ";
    cout << salary << endl;
}

void Admin::searchData(int input)
{
//        system("cls");
//    cout<<"\n\t<<============Search Employee Record=============>>\n\n";

    bool flag = false;
    fstream file;
    file.open("E://emp_sal//emp1.txt", ios::in | ios::binary);

    if (!file)
    {
        cout << "\tFile Cannot be Open";
    }
    else
    {
        file.read((char *)this, sizeof(*this));
        while (!file.eof())
        {
            if (input == id)
            {
                showData();
                cout<<"\n\tTotal Working day of Employee : "<<e_t_w_d;
                cout<<"\n\tNet Salary of Employee is: "<<netsalary;

                flag = true;
            }
            file.read((char *)this, sizeof(*this));
        }

        file.close();

        if (!flag)
        {
            cout << "\tRecord For This ID Does Not Exist";
        }
    }
}

void Admin::updateData(int input)
{
  //      system("cls");
 //   cout<<"\n\t<<============Update Employee Record=============>>\n\n";
    bool flag = false;
    fstream file;
    file.open("E://emp_sal//emp1.txt", ios::in | ios::out | ios::ate | ios::binary);

    if (!file)
    {
        cout << "\tFile Cannot Open Successfully!";
    }
    else
    {
        file.seekg(0, ios::beg);
        file.read((char *)this, sizeof(*this));
        while (!file.eof())
        {
            if (input == id)
            {
                showData();
                cout << "\n\tEnter Updated Record :- \n\n";
                getData();
                int position = (-1) * static_cast<int>(sizeof(*this));
                file.seekp(position, ios::cur);
                file.write((char *)this, sizeof(*this));
                flag = true;
            }
            file.read((char *)this, sizeof(*this));
        }

        if (!flag)
        {
            cout << "\tRecord For This ID Does Not Exist";
        }
        else
        {
            cout << "\n\tNew Records Has Been Updated Successfully\n";
        }
    }
}

void Admin::deleteData(int input)
{
  //      system("cls");
 //   cout<<"\n\t<<============Delete Employee Record=============>>\n\n";
    int c1, c2;
    bool flag = true;
    ofstream fout;
    ifstream fin;
    fin.open("E://emp_sal//emp1.txt", ios::in | ios::binary);

    if (!fin)
    {
        cout << "\tFile Cannot Open Successfully!";
    }
    else
    {
        fin.read((char *)this, sizeof(*this));
        fout.open("E://emp_sal//tempfile1.dat", ios::out | ios::binary);
        while (!fin.eof())
        {
            if (input != id)
            {
                fout.write((char *)this, sizeof(*this));
            }
            fin.read((char *)this, sizeof(*this));
        }
        fin.close();
        fout.close();

        fstream f1, f2;
        f1.open("E://emp_sal//emp1.txt", ios::in | ios::binary);
        f2.open("E://emp_sal//tempfile1.dat", ios::in | ios::binary);

        while (true)
        {
            c1 = f1.get();
            c2 = f2.get();
            if (c1 != c2)
            {
                flag = false;
                break;
            }
            if ((c1 == EOF) || (c2 == EOF))
                break;
        }

        f1.close();
        f2.close();

        if (flag)
        {
            cout << "\tRecord For This ID Does Not Exist";
        }
        else
        {
            label:
            fstream file;
            file.open("E://emp_sal//emp1.txt", ios::in | ios::binary);
            int choice;
            while (file.read((char *)this, sizeof(*this)))
            {
                if (input == id)
                {
                    showData();
                }
            }
            file.close();
            cout << "\n\tAre Your Sure to Delete The Above Record\n";
            cout << "\t1 : Yes\n";
            cout << "\t2 : No\n";
            cout << "\tEnter Your Choice : ";
            cin >> choice;
            if (choice == 1)
            {
                remove("E://emp_sal//emp1.txt");
                rename("E://emp_sal//tempfile1.dat", "E://emp_sal//emp1.txt");
                cout << "\n\n\tRecord is Deleted Successfully";
            }
            else if (choice == 2)
            {
                remove("E://emp_sal//tempfile1.dat");
            }
            else
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "\tError : Invalid Choice Detected! Please Enter Valid Choice";
                goto label;
            }
        }
    }
}

void Admin::sortData()
{
  //      system("cls");
 //   cout<<"\n\t<<============Employee Record w r s. Salary=============>>\n\n";
    int size, fileSize, objSize, position;
    Admin *ptr = NULL;

    ifstream file;
    file.open("E://emp_sal//emp1.txt", ios::in | ios::binary);

    if (isEmpty(file))
    {
        cout << "\n\tYour File is Empty! No Record is Avialable to Show\n";
    }
    else
    {
        file.seekg(0, ios::end);

        fileSize = static_cast<int>(file.tellg());
        objSize = static_cast<int>(sizeof(*this));
        size = fileSize / objSize;

        ptr = new Admin[size];

        file.seekg(0, ios::beg);

        for (int i = 0; i < size; i++)
        {
            file.read((char *)&ptr[i], sizeof(*this));
        }
        file.close();

        for (int i = 0; i < size; i++)
        {
            for (int j = i + 1; j < size; j++)
            {
                if (ptr[i].salary < ptr[j].salary)
                {
                    swap(ptr[i], ptr[j]);
                }
            }
        }

        cout << "\n\n\t======== Sorted Employee Details With Respect to Salary ========\n\n";

        for (int i = 0; i < size; i++)
        {
            ptr[i].showData();
        }

        delete [] ptr;   // Explicitly Delete Memory Location From Heap.
    }
}


void Admin::addAttendance(int input)
{

    bool flag = false;
    fstream file,file2;
    file.open("E://emp_sal//emp1.txt", ios::in | ios::out | ios::ate | ios::binary);
//    file2.open("E://emp_sal//att.txt", ios::in | ios::out | ios::ate | ios::binary);
    if (!file)
    {
        cout << "\tFile Cannot Open Successfully!";
    }
    else
    {
        file.seekg(0, ios::beg);
        file.read((char *)this, sizeof(*this));
        while (!file.eof())
        {
            if (input == id)
            {
                Admin::showData();
                cout << "\n\tEnter Attendance Record :- \n\n";
//                Admin::getData();
                cout<<"\tTotal Working day : ";
                cin>>total_w_d;
                cout<<"\tTotal Work hour : ";
                cin>>work_h;
                cout<<"\tLeave as per day : ";
                cin>>leave_d;
                cout<<"\tHalf leave : ";
                cin>>half_l_d;
                cout<<"\tLeave as per hour : ";
                cin>>hour_l;

                int position = (-1) * static_cast<int>(sizeof(*this));
                file.seekp(position, ios::cur);
                file.write((char *)this, sizeof(*this));
                flag = true;
            }
            file.read((char *)this, sizeof(*this));
        }

        if (!flag)
        {
            cout << "\tRecord For This ID Does Not Exist";
        }
        else
        {
            cout << "\n\tAttendance Has Been Added Successfully\n";
        }
    }
}


void Admin::showAttendance(int input)
{
          bool flag = false;
    fstream file;
    file.open("E://emp_sal//emp1.txt", ios::in | ios::out | ios::ate | ios::binary);
//    file.open("E://emp_sal//att.txt", ios::in | ios::out | ios::ate | ios::binary);
    if (!file)
    {
        cout << "\tFile Cannot Open Successfully!";
    }
    else
    {
        file.seekg(0, ios::beg);
        file.read((char *)this, sizeof(*this));
        while (!file.eof())
        {
            if (input == id)
            {
                Admin::showData();

                cout << "\n\tAttendance Record :- \n\n";
                cout<<"\n\tTotal Working day : "<<total_w_d;
                cout<<"\n\tWork hour : "<<work_h;
                total_w_h=total_w_d*work_h;
                cout<<"\n\tTotal Working hour : "<<total_w_h;
                cout<<"\n\n\tLeave as per day : "<<leave_d;
                cout<<"\n\tHalf leave : "<<half_l_d;
                cout<<"\n\tLeave as per hour : "<<hour_l;
                total_l_h=(leave_d*work_h)+(half_l_d*work_h/2)+hour_l;
                cout<<"\n\tTotal Leave hour : "<<total_l_h;
                t_l_d=total_l_h/work_h;
                cout<<"\n\tTotal Leave day : "<<t_l_d;
                e_t_w_d=total_w_d-t_l_d;
                cout<<"\n\n\tTotal Working day of Employee : "<<e_t_w_d;

                int position = (-1) * static_cast<int>(sizeof(*this));
                file.seekp(position, ios::cur);
                file.write((char *)this, sizeof(*this));
                flag = true;
            }
            file.read((char *)this, sizeof(*this));
        }

        if (!flag)
        {
            cout << "\tRecord For This ID Does Not Exist";
        }
  }
}



void Admin::showSalary(int input)
{
      bool flag = false;
    fstream file;
    file.open("E://emp_sal//emp1.txt", ios::in | ios::out | ios::ate | ios::binary);
//    file2.open("E://emp_sal//emp1.txt", ios::in | ios::out | ios::ate | ios::binary);
    if (!file)
    {
        cout << "\tFile Cannot Open Successfully!";
    }
    else
    {
        file.seekg(0, ios::beg);
        file.read((char *)this, sizeof(*this));
        while (!file.eof())
        {
            if (input == id)
            {
                Admin::showData();
        wages=salary;
        days=e_t_w_d;
        basic=wages*days;
        HRA=basic*0.1;
        DA=basic*0.05;
        PF=basic*0.12;
        netsalary=basic+HRA+DA-PF;

        cout<<"\tTotal Working day of Employee : "<<e_t_w_d;
        cout<<"\n\n\tBasic:\t"<<basic<<"\n\tHRA:\t"<<HRA<<"\n\tDA:\t"<<DA<<"\n\tPF:\t"<<PF<<"\n\tNet Salary of Employee is: "<<netsalary;

                int position = (-1) * static_cast<int>(sizeof(*this));
                file.seekp(position, ios::cur);
                file.write((char *)this, sizeof(*this));
                flag = true;
            }
            file.read((char *)this, sizeof(*this));
        }

        if (!flag)
        {
            cout << "\tRecord For This ID Does Not Exist";
        }
  }
}



class User:public Admin
{
public:
    // member function
    int display();
    int dispAtt();
    int dispSal();
    int dispAttSal();
};
int User::display()
{
//    searchData(int input);
//    showData();
    cout<<"----------------";
}
int User::dispAtt()
{
    cout<<"----------------";
}
int User::dispSal()
{
    cout<<"----------------";
}
int User::dispAttSal()
{
    cout<<"----------------";
}

class Emp:public User
{

    public:
    int intro();
    int login();
    int mainu();                        // function that print the Menu on Console Screen.
    int mainmenu();                     // function that print the Main Menu on Console Screen.
    int submenu();
    int childmenu();                      // function that print the Sub Menu on Console Screen.
    int usermenu();

};
int Emp::mainu()
{
    system("cls");
    int choice;
    bool flag;
    cout<<"\n\n\t==================================================="<<endl;
    cout<<"\n\t\t\t CONTROL PANEL"<<endl;
    cout<<"\n\t==================================================="<<endl;
    cout << "\n\tPlease Select Your Choice :- \n\n";
    cout << "\n\t1 : Admin\n";
    cout << "\t2 : User\n";
    cout << "\t0 : Exit\n";

    label:
    cout << "\n\tEnter Your Choice : ";
    cin >> choice;

    flag = validateInput();
    if (flag)
        goto label;
    else
        return choice;

}
int Emp::mainmenu()
{
    system("cls");
    int choice;
    bool flag;
    cout << "\n\n\t<================= Admin Portal =================>\n\n";
    cout << "\tPlease Select Your Choice :- \n\n";
    cout << "\t1 : Insert Employees Records\n";
    cout << "\t2 : View All Employees Records\n";
    cout << "\t3 : Search Employees Records\n";
    cout << "\t4 : Update Employee Records\n";
    cout << "\t5 : Delete Employee Records\n";
    cout << "\t6 : Add Attendance in Employee Records\n";
    cout << "\t7 : Show Attendance of Employee\n";
    cout << "\t8 : Show Salary of Employee\n";
    cout << "\t9 : Sort Employee Records w.r.t Salary\n";
    cout << "\t0 : Goto Back\n";

label:
    cout << "\n\tEnter Your Choice : ";
    cin >> choice;

        flag = validateInput();
    if (flag)
        goto label;
    else
        return choice;

}

Emp::submenu()
{
    system("cls");
    bool check = true;
    int search;
    int size;
    bool flag;
    Admin *ptr = NULL;
    Admin filedata;

    while (check)
    {
       system("cls");
        switch (Emp::mainmenu())
        {
        case 1:
            label:
            cout << "\tHow Many Employees Records that You Want to Store : ";
            cin >> size;

            flag = validateInput();

            if (flag)
            {
                goto label;
            }
            else
            {
                ptr = new Admin[size];
                    system("cls");
                for (int i = 0; i < size; i++)
                {
                    cout << "\n\n\tEnter the Details For the Employee # " << i + 1 << endl;
                    ptr[i].Admin::getData();
                }

                for (int i = 0; i < size; i++)
                {
                    ptr[i].Admin::writeFile();
                }

                delete [] ptr;

                cout << "\n\tNew Records Has Been Added Successfully\n";
                break;
            }
            case 2:
            system("cls");
            cout << "\n\n\t=============== Employee Details ==================\n\n";
            filedata.Admin::readFile();
            break;
        case 3:
            system("cls");
            cout << "\n\tPlease Enter Employee Unique ID That you Want to Search its Record : ";
            cin >> search;
            filedata.Admin::searchData(search);
            break;
        case 4:
            system("cls");
            cout << "\n\tPlease Enter Employee Unique ID That you Want to Update its Record : ";
            cin >> search;
            filedata.Admin::updateData(search);
            break;
        case 5:
            system("cls");
            cout << "\n\tPlease Enter Employee Unique ID you Want to Delete its Record : ";
            cin >> search;
            filedata.Admin::deleteData(search);
            break;
        case 6:
            system("cls");
            cout << "\n\tPlease Enter Employee Unique ID That you Want to Search its Record : ";
            cin >> search;
            filedata.Admin::addAttendance(search);
            break;
        case 7:
            system("cls");
            cout << "\n\tPlease Enter Employee Unique ID That you Want to Search its Record : ";
            cin >> search;
            filedata.Admin::showAttendance(search);
            break;
        case 8:
            system("cls");
            cout << "\n\tPlease Enter Employee Unique ID That you Want to Search its Record : ";
            cin >> search;
            filedata.Admin::showSalary(search);
            break;

        case 9:
            system("cls");
//            cout<<"===========Record Sort by Salary==========";
            filedata.Admin::sortData();
            break;
        case 0:
            cout << "\n\tGo Back\n";
            check = false;
            break;
        default:
            cout << "\tInvalid Choice! Please Select Valid Choice.";
            break;
        }
        getch();
        }
}


int Emp::login()
{

         system("cls");
    string user,pass;
    cout<<"\n\n\t==============================";
    cout<<"\n\n\t\tLogin Process";
    cout<<"\n\n\t==============================";
    cout<<"\n\n\tEnter Username : ";
    cin>>user;
    cout<<"\n\tEnter Password : ";
    cin>>pass;
    if(user=="beauti"&&pass=="b123")
    {
        system("cls");
        Emp::submenu();

    }
        else
    {
    cout<<"\n\tUser name or password is invailid...";
    }
    getch();
    //goto login();
}

int Emp::childmenu()
{
    system("cls");
    int choice;
    bool flag;
    cout << "\n\n\t<================= User Portal =================>\n\n";
    cout << "\tPlease Select Your Choice :- \n\n";
    cout << "\t1 : View Employees Records\n";
    cout << "\t2 : View Attendance Records\n";
    cout << "\t3 : View Salary Records\n";
    cout << "\t4 : View Salary with Attendance\n";
    cout << "\t5 : Goto Back\n";
label:
    cout << "\n\tEnter Your Choice : ";
    cin >> choice;

    flag = validateInput();
    if (flag)
        goto label;
    else
        return choice;
}

int Emp::usermenu()
{
    system("cls");
    bool check = true;
    int search;
    int size;
    bool flag;
    //Admin *ptr = NULL;
    User filedata2;

    while (check)
    {
       system("cls");
        switch (Emp::childmenu())
        {
        case 1:
            system("cls");
            cout << "\n\tPlease Enter Employee Unique ID That you Want to Sea your Record : ";
            cin >> search;
            filedata2.User::display();
            break;
        case 2:
            system("cls");
            cout << "\n\tPlease Enter Employee Unique ID That you Want to your Attendance Record : ";
            cin >> search;
            filedata2.User::dispAtt();
            break;
        case 3:
            system("cls");
            cout << "\n\tPlease Enter Employee Unique ID That you Want to Salary Record : ";
            cin >> search;
            filedata2.User::dispSal();
            break;
        case 4:
            system("cls");
            cout << "\n\tPlease Enter Employee Unique ID That you Want to Sea Attendance with Salary Record : ";
            cin >> search;
            filedata2.User::dispAttSal();
            break;
        case 5:
            cout << "\n\tGo back\n";
            check = false;
            break;
        default:
            cout << "\tInvalid Choice! Please Select Valid Choice.";
            break;
        }
        getch();
        }
}

int Emp::intro()
{
    system("cls");
    cout<<"\n\n\n\n\n";
    cout<<"\n\n\t================================================="<<endl;
    cout<<"\n\tEmployee Personal Attendance and Salary Register"<<endl;
    cout<<"\n\n\t\t\t Version : 1.1";
    cout<<"\n\n\t================================================="<<endl;
    getch();
  bool check = true;
    while (check)
    {
        system("cls");
        switch (mainu())
        {
        case 1:
            login();
            break;
        case 2:
            usermenu();
            break;
        case 0:
            cout << "\n\tThank You For Using This Application\n";
            check = false;
            break;
        default:
            cout << "\tInvalid Choice! Please Select Valid Choice.";
            break;
        } getch();

    }

}


int main()
{
        system("cls");
    Emp e;
    //system("color f5");
    system("title Employeees Salary Managment System by Beauti");
    e.intro();
    cout << "\n";
    cout << "\t" << system("pause");
}
