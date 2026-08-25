#include<bits/stdc++.h>
using namespace std;

class GPAY{
    private:
        string name;
        long long phoneno;
        double balance;
        int pin;
    
    public:
        GPAY(){                     //default constructor
            name="";
            phoneno=0;
            balance=0;
            pin=0;
        }
        GPAY(string n, long long ph, double b, int p){    // parameterized constructor
            name=n;
            phoneno=ph;
            balance=b;
            pin=p;
            cout<<"User "<<name<<" Created "<<endl;
        }
        //Getters
        string getName(){
            return name;
        }
        long long getphoneno(){
            return phoneno;
        }
        double getBalance(){
            return balance;
        }
        int getpin(){
            return pin;
        }

        //Setters
        void setname(string n){
            name=n;
        }
        void setphone(long long p){
            phoneno=p;
        }
        void setbalance(double b){
            balance=b;
        }
        void setpin(int p){
            pin=p;
        }

        void addmoney(double amount){       //uses for adding money
            balance+=amount;
            cout<<amount<<" added to "<<name<<"'s account."<<endl;
        }

        bool Pin(int enteredpin){
            return pin==enteredpin;
        }
        void pay(GPAY &receiver,double amount){     //Uses for payments
            if(balance>=amount){
                balance-=amount;
                receiver.balance+=amount;
                cout<<name<<" paid Rs. "<<amount<<" to "<<receiver.name<<endl;
            }
            else{
                cout<<name<<" does not have enough balance."<<endl;
            }
        }

        void display(){                          //uses for displaying messages
            cout<<"Name: "<<name<<endl;
            cout<<"Phone no: "<<phoneno<<endl;
            cout<<"Balance: "<<balance<<endl;
            cout<<"____________________________"<<endl;
        }
};


int main(){
    int a;
    cout<<"Number of users: ";
    cin>>a;
    cin.ignore();

    GPAY p[a];     //creating a "a users " objects with class GPAY
    for(int i=0;i<a;i++){
        string name;
        long long phoneno;
        double balance;
        int pin;

        cout<<"Enter the User name "<<i+1<<" : ";
        getline(cin,name);

        cout<<"Enter phone number: ";
        cin>>phoneno;

        cout<<"Enter balance: ";
        cin>>balance;

        cout<<"Enter pin: ";
        cin>>pin;

        cin.ignore();

        //usinng setters 
        p[i].setname(name);
        p[i].setphone(phoneno);
        p[i].setbalance(balance);
        p[i].setpin(pin);
    }

    //display all the users
    cout<<"\n\n---User Detail---\n\n";
    for(int i=0;i<a;i++){
        cout<<"User "<<i+1<<endl;
        p[i].display();
    }

    //payment between two users
    cout<<"\n\n---Payment---\n\n";

    long long sender,receiver;
    double amount;

    cout<<"Enter the sender phone number: ";
    cin>>sender;

    cout<<"Enter the receiver phone number: ";
    cin>>receiver;

    cout<<"Enter the amount to be paid: ";
    cin>>amount;

    if(sender==receiver){
        cout<<"Sender and receiver phone no cannot be same!"<<endl;
    }
    else{
        int ma=-1,b=-1;
        for(int i=0;i<a;i++){
            if(p[i].getphoneno()==sender){
                ma=i;
            }
            if(p[i].getphoneno()==receiver){
                b=i;
            }
        }

        //checking whether both user is exist or not
        if(ma==-1){
            cout<<"Sender phone no not found."<<endl;
        }
        else if(b==-1){
            cout<<"Receiver phone no not found."<<endl;
        }
        else{
            int enteredPin;
            cout << "Enter UPI PIN for " << p[ma].getName() << ": ";
            cin >> enteredPin;
            if (p[ma].Pin(enteredPin)) {
                p[ma].pay(p[b], amount);
                //showing the updated user details
                cout<<"\n\n---Updated User Details---\n\n";
                if(ma != -1 && b != -1) {

                    cout << "--- Sender Details ---\n";
                        p[ma].display();

                    cout << "--- Receiver Details ---\n";
                    p[b].display();
                }
            }
        }
    }


    
}