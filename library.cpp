//reference code .. inspiration taken from here 
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>

using namespace std;

const int cuAccLimit = 20000;
const int saAccLimit = 50000;

class id {
    int password;
    int cnic;
    int initialAmount;

public:
    string firstName;
    string lastName;
    string fatherName;
    string address;
    string email;
    int accountNo;

    id() : initialAmount(0), password(0) , cnic(0){}

    void set_initialAmount( const int& Ia) {
        initialAmount = Ia;
    }

    int get_initialAmount() const {
        return initialAmount;
    }

    void set_cnic(const int& em) {
        cnic = em;
    }

    int get_cnic() const {
        return cnic;
    }

    void set_password(const int& pa) {
        password = pa;
    }

    int get_password() const {
        return password;
    }

    void generateAccountNo() {
        accountNo = rand() % 90000 + 10000;
        cout << "Your account number is: " << accountNo << endl;
    }

    void passSetting() {
        cout << "------------------------------------" << endl;
        cout << "Account Creation" << endl;
        cout << "------------------------------------" << endl;
        cout << "Enter Your First Name: ";
        cin >> firstName;
        cout << "Enter Your Last Name: ";
        cin >> lastName;
        cout << "Enter Father Name: ";
        cin >> fatherName;
        cin.ignore();
        cout << "Enter Your Current Address: ";
        getline(cin, address);
        cout << "Enter Your Email: ";
        cin >> email;
        cout << endl;
        cout << "Set Your CNIC: ";
        int em;
        cin >> em;
        set_cnic(em);
        cout << "Create a Password (integer only): ";
        int c;
        cin >> c;
        set_password(c);
        cout << "------------------------------------" << endl;
    }

};

void displayLoading(int boxCount = 5, int delay_ms = 100) {
    while (boxCount >= 0) {
        system("cls");
        for (int i = 0; i < boxCount; ++i) {
            cout << "[<*>] ";
        }
        cout << endl;
        this_thread::sleep_for(chrono::milliseconds(delay_ms));
        boxCount--;
    }
}

class bankAccountType : public id {
public:
    int accountType;

    void accountTYPE() {
        int TT;
        cout << "------------------------------------" << endl;
        cout << "Account Type Selection" << endl;
        cout << "------------------------------------" << endl;
        cout << "Enter 1 to create 'Current Account'" << endl;
        cout << "Enter 2 to create 'Saving Account'" << endl;
        cin >> TT;
        system("cls");
        if (TT == 1) {
            accountType = 1;
            passSetting();
            displayLoading();
            cout << "Current Account Created." << endl;
            generateAccountNo();
            cout << "------------------------------------" << endl;
        }
        else if (TT == 2) {
            accountType = 2;
            passSetting();
            displayLoading();
            cout << "Saving Account Created." << endl;
            generateAccountNo();
            cout << "------------------------------------" << endl;
        }
    }
};

class password : public bankAccountType {
public:
    void check_access1() {
        int p;
        int em;

        cout << "------------------------------------" << endl;
        cout << "Account Access" << endl;
        cout << "------------------------------------" << endl;
        cout << "Enter your CNIC: ";
        cin >> em;
        cout << "Enter Password (integer only): ";
        cin >> p;
        if (em == get_cnic() && p == get_password()) {
            cout << "Access Granted." << endl;
            cout << "------------------------------------" << endl;
        }
        else {
            cout << "Access Denied." << endl;
            exit(0);
        }
    }

    bool check_access2(int precnic, int prepass, int cnicInput, int passInput) {
        cout << "------------------------------------" << endl;
        if (cnicInput == precnic && passInput == prepass) {
            cout << "Access Granted." << endl;
            cout << "------------------------------------" << endl;
            return true;
        }
        else {
            return false;
        }
    }
};

class login : public password {
public:
    int choice;
    void askLogin(int& selectedAccount, int precnic1, int prepass1, int precnic2, int prepass2) {
        cout << "------------------------------------" << endl;
        cout << "Welcome to the Banking System" << endl;
        cout << "------------------------------------" << endl;
        cout << "To login to your already existing account, enter '1'" << endl;
        cout << "To create a new account, enter '2'" << endl;
        cout << "To exit the program, enter '0'" << endl;
        cin >> choice;
        system("cls");

        if (choice == 1) {
            int cnicInput, passInput;
            cout << "Enter your CNIC: ";
            cin >> cnicInput;
            cout << "Enter your Password: ";
            cin >> passInput;
            system("cls");

            if (check_access2(precnic1, prepass1, cnicInput, passInput)) {
                selectedAccount = 1;
            }
            else if (check_access2(precnic2, prepass2, cnicInput, passInput)) {
                selectedAccount = 2;
            }
            else {
                cout << "Access Denied." << endl;
                exit(0);
            }
        }
        else if (choice == 2) {
            accountTYPE();
            check_access1();
        }
        else {
            cout << "Exiting program." << endl;
            exit(0);
        }
    }
};

class deposit {
public:
    void add(int* ptr, int value, int maxLimit) {
        if (ptr) {
            if (*ptr + value > maxLimit) {
                cout << "Deposit amount exceeds account limit of PKR " << maxLimit << ". Deposit denied." << endl;
            }
            else {
                *ptr += value;
                cout << "After deposit: PKR " << *ptr << endl;
            }
        }
    }
};

class withdraw {
public:
    void subtract(int* ptr, int value) {
        if (*ptr < value) {
            cout << "Insufficient funds." << endl;
        }
        else {
            *ptr -= value;
        }
    }
};

class transaction {
public:
    void transact(int* ptr, int* otherPtr, int value, bool isTransfer = false) {
        if (*ptr < value) {
            cout << "Insufficient Balance." << endl;
        }
        else {
            
            if (isTransfer && otherPtr) {
                *ptr -= value;
                *otherPtr += value;
                cout << "Transfer successful." << endl;
                cout << endl;
                cout << "Current Account updated balance: PKR " << *ptr << endl;
                cout << endl;
                cout << "Other Account new balance: PKR " << *otherPtr << endl;
            }
            else {
                cout << "Transaction unsuccessful." << endl;
                cout << "Remaining balance: PKR " << *ptr << endl;
            }
        }
    }
};

int generate4dcode() {
    return rand() % 9000 + 1000;
}

void performOperations(int& balance, int& otherBalance, int accountType) {
    deposit addition;
    withdraw subtraction;
    transaction transact;
    int option, amount, raccNo;

    int maxLimit;
    if (accountType == 1) {
        maxLimit = cuAccLimit;
    }
    else {
        maxLimit = saAccLimit;
    }


    do {
        cout << "------------------------------------" << endl;
        cout << "Current balance: PKR " << balance << endl;
        cout << "------------------------------------" << endl;
        cout << "Enter 1 to deposit" << endl;
        cout << "Enter 2 to withdraw" << endl;
        cout << "Enter 3 for Bill transaction" << endl;
        cout << "Enter 4 to transfer to Other account" << endl;
        cout << "Enter 5 for Bill payments" << endl;
        cout << "Enter 0 to return to main menu" << endl;
        cin >> option;

        if (option == 1) {
            cout << "Enter amount to deposit: PKR ";
            cin >> amount;
            displayLoading();
            addition.add(&balance, amount, maxLimit);
        }
        else if (option == 2) {
            cout << "Enter amount to withdraw: PKR ";
            cin >> amount;
            displayLoading();
            subtraction.subtract(&balance, amount);
            cout << "After withdrawal: PKR " << balance << endl;
        }
        else if (option == 3) {
            cout << "Enter the recipient Account Number: ";
            cin >> raccNo;
            cout << "Enter the amount to send: PKR ";
            cin >> amount;
            displayLoading();
            transact.transact(&balance, nullptr, amount);
        }
        else if (option == 4) {
            cout << "Enter amount to transfer to Other account: PKR ";
            cin >> amount;
            displayLoading();
            transact.transact(&balance, &otherBalance, amount, true);
        }
        else if (option == 5) {
            string billType;
            cout << "Enter the type of utility bill (e.g., water, gas, rent, electricity): ";
            cin.ignore();
            getline(cin, billType);
           
            cout << endl;
            displayLoading();
            int generatedCode = generate4dcode();
            cout << "You have chosen to pay the " << billType << " bill." << endl;
            cout << "Generated 4-digit code: " << generatedCode << endl;
            cout << endl;
            int inputCode;
            cout << "Enter the 4 digit code displayed above: ";
            cin >> inputCode;
            if (inputCode != generatedCode) {
                cout << "Invalid code. Transaction aborted." << endl;
                continue;
            }
            cout << "Enter the amount to pay: PKR ";
            cin >> amount;
            displayLoading();
            transact.transact(&balance, nullptr, amount);
        }
        else if (option != 0) {
            cout << "Invalid option!" << endl;
        }
    } while (option != 0);

    cout << "------------------------------------" << endl;
    cout << "Returning to main menu..." << endl;
    cout << "------------------------------------" << endl;
}

int main() {
    srand(time(0));
    int precnic1 = 1111;
    int prepass1 = 1111;
    int predefBalance1 = 10000;

    int precnic2 = 2222;
    int prepass2 = 2222;
    int predefBalance2 = 20000;

    int selectedAccount = 0;

    login AL;

    while (true) {
        AL.askLogin(selectedAccount, precnic1, prepass1, precnic2, prepass2);

        int balance;
        int otherBalance;
        if (AL.choice == 1) {
            if (selectedAccount == 1) {
                balance = predefBalance1;
                otherBalance = predefBalance2;
            }
            else {
                balance = predefBalance2;
                otherBalance = predefBalance1;
            }
            cout << "Logged in with existing balance: PKR " << balance << endl;
            cout << "------------------------------------" << endl;
        }
        else if (AL.choice == 2) {
            cout << "Enter the initial balance for your new account: PKR ";
            cin >> balance;
            if (AL.accountType == 1 && balance > cuAccLimit) {
                cout << "Initial balance exceeds the limit for Current Account (PKR 20000)." << endl;
                continue;
            }
            if (AL.accountType == 2 && balance > saAccLimit) {
                cout << "Initial balance exceeds the limit for Saving Account (PKR 50000)." << endl;
                continue;
            }
            AL.set_initialAmount(balance);
            cout << "Your initial balance is: PKR " << balance << endl;
            cout << "------------------------------------" << endl;
            otherBalance = 0;
        }

        performOperations(balance, otherBalance, AL.accountType);

        if (AL.choice == 1) {
            if (selectedAccount == 1) {
                predefBalance1 = balance;
                predefBalance2 = otherBalance;
            }
            else {
                predefBalance2 = balance;
                predefBalance1 = otherBalance;
            }
        }
    }
    return 0;

}