#include<bits/stdc++.h>
using namespace std;

class Employee{
    // Creating Variables inside the private sector
    private:
        int id;
        string name;
        string depart;
        double basesal;

    public:
    // Constructor 1 -> Default
        Employee(){
            id=0;
            name="";
            depart="Not Assigned";
            basesal=0.0;
        }
    // Constructor 2 -> with id, name;
        Employee(int id, string name){
            this->id=id;
            this->name=name;
            depart="Not Assigned";
            basesal=0.0;
        }
    // Constructor 3 -> with id , name, department, base salary details ;
        Employee(int id, string name, string depart, double basesal){
            this->id=id;
            this->name=name;
            this->depart=depart;
            this->basesal=basesal;
        }
    // Copy Constructor
        Employee(const Employee &a){
            id=a.id;
            name=a.name;
            depart=a.depart;
            basesal=a.basesal;
        }

    // Function Overloading 
    // Fuction -> 1 calculated the salary one 

    double calculatePay(){
        return basesal;
    }

    // Function -> 2 calculated the salary + bonus

    double calculatePay(double bonus){
        return basesal+bonus;
    }

    // Function -> 3 calculate the base salary + overtime service

    double calculatePay(int hours, double hourrate){
        return basesal+(hours*hourrate);
    }

    // Function -> 4 calculate the base salary + bonus - tax charge

    double calculatePay(double bonus, double taxpercent){
        double tax = bonus* (taxpercent/100);
    }

    //function overloading 
    // Function -> 1 update the profile only department

    void updateProfile(string de){
        depart = de;
    }

    // Function -> 2 update the profile only salary

    void updateProfile(double base){
        basesal=base;
    }

    // Function -> 3 update the profile both salary and department

    void updateProfile(string de, double base){
        depart=de;
        basesal=base;
    }

    // Display all the details of the employee

    void display(){
        cout<<" ID         : "<<id<<endl;
        cout<<" NAME       : "<<name<<endl;
        cout<<" DEPARTMENT : "<<depart<<endl;
        cout<<" SALARY     : "<<basesal<<endl;
    }
};


//Main role of this program

int main(){
    // Constructor Overloading

    cout<<"\n\n----------Constuctor Overloading-----------\n\n";

    // For Default Constructor

    Employee e1;

    cout<<"\nEmployee 1:\n";
    e1.display();

    // For Constructor 2 case 
    // Only Employee id and name only

    Employee e2(101,"Hardhik Sai");
    cout<<"\nEmployee 2: \n";
    e2.display();

    // For Constructor 3 case
    // all details like id, name, salary, and department name

    Employee e3(102,"Padma Raju","Software Engineer",100000.00);
    cout<<"\nEmployee 3: \n";
    e3.display();

    // For Constructor 4 case
    // copy constructor 

    Employee e4(e3);

    cout<<"\nEmployee 4 (Copy of Employee 3): \n";
    e4.display();



    // Function Overloading

    cout<<"\n\n---------------Function Overloading------------------\n\n";

    cout<<"\nBase Salary Only:\n";
    double p=e3.calculatePay();
    cout<<p<<endl;

    cout<<"\nBase Salary + Bonus: \n";
    double q=e3.calculatePay(5000);
    cout<<q<<endl;

    cout<<"\nBase Salary + Overtime: \n";
    double r=e3.calculatePay(10, 500);
    cout<<r<<endl;

    cout<<"\nBase Salary + Bonus - Tax: \n";
    double s=e3.calculatePay(10000,10);
    cout<<s<<endl;

    // Update Profile Overloading

    cout<<"\n\n--------------Update Profile Oberloading-------------\n\n";

    cout<<"\nOriginal Profile: \n";
    e3.display();

    cout<<"\nUpdate the details of Department only\n";
    e3.updateProfile("Marketing");
    cout<<" \nAfter Department Update: \n";
    e3.display();

    cout<<"\nUpdate the details of Salary only\n";
    e3.updateProfile(85000);
    cout<<" \nAfter Salary Update: \n";
    e3.display();

    cout<<"\nUpdate the details of Salary and Department only\n";
    e3.updateProfile("Finance",150000);
    cout<<" \nAfter Department and Salary Update: \n";
    e3.display();

    return 0;
}