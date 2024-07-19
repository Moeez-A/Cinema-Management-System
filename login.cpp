/*this file is made for the sole purpose of displaying info and GUI. */
/*some important notes : 
So, to summarize:
1.Vehicle() is used to define a constructor inside the class definition.
2. Vehicle::Vehicle() is used to define a constructor outside the class definition, typically in a separate source file.*/
#include <login.h>

#include<iostream>
#include<string>
using namespace std;

login::login():password(){
    int choice;
        void askLogin(int& selectedAccount) {
        cout << "------------------------------------" << endl;
        cout << "Welcome to the Cinema Management System" << endl;
        cout << "------------------------------------" << endl;
        cout << "To login to your already existing user account, enter '1'" << endl;
        cout << "To create a new user account, enter '2'" << endl;
        cout << "To login as a System admin enter '3' " <<endl;
        cout << "To login as a guest enter '4' " <<endl;
        cout << "To exit the program, enter '0'" << endl;
        cout << "Enter your choice: ";
        cin >> selectedAccount;
        system("cls");
}
};