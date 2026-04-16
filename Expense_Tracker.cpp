#include <iostream>
#include <string>
using namespace std;

// -------------Color Codes-------------
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"

// -------------------Class--------------
class ExpenseTracker {
private:
    string username;
    string password;
    double balance;
    string* descriptions;
    double* amounts;
    int expenseCount;

public:
//---------------Default Constructor------------
    ExpenseTracker() {
        this->username = "Guest";
        this->password = "123";
        this->balance = 0;
        this->descriptions = nullptr;
        this->amounts = nullptr;
        this->expenseCount = 0;
    }
//---------------Parameterized Constructor------------
    ExpenseTracker(string uname, string pwd, double bal) {
        this->username = uname;
        this->password = pwd;
        this->balance = bal;
        this->descriptions = nullptr;
        this->amounts = nullptr;
        this->expenseCount = 0;
    }
//---------------Copy Constructor------------
    ExpenseTracker(const ExpenseTracker& other) {
        this->username = other.username;
        this->password = other.password;
        this->balance = other.balance;
        this->expenseCount = other.expenseCount;

        if (this->expenseCount > 0) {
            this->descriptions = new string[this->expenseCount];
            this->amounts = new double[this->expenseCount];
            for (int i = 0; i < this->expenseCount; i++) {
                this->descriptions[i] = other.descriptions[i];
                this->amounts[i] = other.amounts[i];
            }
        } else {
            this->descriptions = nullptr;
            this->amounts = nullptr;
        }
    }
//---------------Assignment Operator------------
    ExpenseTracker& operator=(const ExpenseTracker& other) {
        if (this != &other) {
            this->username = other.username;
            this->password = other.password;
            this->balance = other.balance;

            delete[] this->descriptions;
            delete[] this->amounts;

            this->expenseCount = other.expenseCount;

            if (this->expenseCount > 0) {
                this->descriptions = new string[this->expenseCount];
                this->amounts = new double[this->expenseCount];
                for (int i = 0; i < this->expenseCount; i++) {
                    this->descriptions[i] = other.descriptions[i];
                    this->amounts[i] = other.amounts[i];
                }
            } else {
                this->descriptions = nullptr;
                this->amounts = nullptr;
            }
        }
        return *this;
    }
//---------------Destructor--------------
    ~ExpenseTracker() {
        delete[] this->descriptions;
        delete[] this->amounts;
        cout << RED << "\n[Destructor called for User: " << this->username << "]" << RESET << endl;
    }

    bool login(string uname, string pwd) {
        return (this->username == uname && this->password == pwd);
    }

    void deposit(double amt) {
        if (amt <= 0) {
            cout << RED << "Invalid deposit amount!" << RESET << endl;
            return;
        }
        this->balance += amt;
        cout << GREEN << "Amount Deposited: $" << amt << RESET << endl;
    }

    void spend(double amt) {
        if (amt <= 0 || amt > this->balance) {
            cout << RED << "Invalid transaction!" << RESET << endl;
            return;
        }
        this->balance -= amt;
        cout << YELLOW << "Spent: $" << amt << RESET << endl;
    }

    void addExpense(string desc, double amt) {
        if (amt <= 0 || amt > this->balance) {
            cout << RED << "Invalid expense!" << RESET << endl;
            return;
        }

        spend(amt);
//-------------Dynamic Memory Allotation---------
        string* newDesc = new string[this->expenseCount + 1];
        double* newAmt = new double[this->expenseCount + 1];

        for (int i = 0; i < this->expenseCount; i++) {
            newDesc[i] = this->descriptions[i];
            newAmt[i] = this->amounts[i];
        }

        newDesc[this->expenseCount] = desc;
        newAmt[this->expenseCount] = amt;

        delete[] this->descriptions;
        delete[] this->amounts;

        this->descriptions = newDesc;
        this->amounts = newAmt;

        this->expenseCount++;

        cout << CYAN << "\nExpense added successfully!" << RESET << endl;
    }

    void showBalance() {
        cout << BLUE << "\n=== " << this->username << "'s Balance ===" << RESET << endl;
        cout << "$" << this->balance << endl;
    }

    void showExpenses() {
        cout << MAGENTA << "\n===== Expense History =====" << RESET << endl;
        if (this->expenseCount == 0) {
            cout << "No expenses recorded." << endl;
            return;
        }
        cout << "No.  Description               Amount" << endl;
        cout << "-----------------------------------------" << endl;
        for (int i = 0; i < this->expenseCount; i++) {
            cout << (i+1) << "    " << descriptions[i] << "               $" << amounts[i] << endl;
        }
    }
//---------------Friend Fuction--------------
    friend void showSummary(ExpenseTracker& user);
};

void showSummary(ExpenseTracker& user) {
    cout << MAGENTA << "\n===== Expense Summary =====" << RESET << endl;
    cout << "Username      : " << user.username << endl;
    cout << "Balance       : $" << user.balance << endl;
    cout << "Total Expenses: " << user.expenseCount << endl;

    double totalSpent = 0;
    for (int i = 0; i < user.expenseCount; i++)
        totalSpent += user.amounts[i];

    cout << "Total Spent   : $" << totalSpent << endl;
}

// ----------------------Main Function------------
int main() {
    system("cls");
    string uname, pwd;
    double bal;

//------------------SignUp------------
    cout <<"\t\t"<< GREEN << "========== SIGN UP ==========" << RESET << endl;
    cout << "Enter Username: "; 
    cin >> uname;
    cout << "Enter Password: ";
     cin >> pwd;
while (true) {
    cout << "Enter Initial Balance: $";
    if (cin >> bal) {
        if (bal >= 0) {
            break;
        } else {
            cout << RED << "Balance cannot be negative. Try again." << RESET << endl;
        }
    } else {
        cout << RED << "Invalid input! Please enter a number." << RESET << endl;
        cin.clear();
        cin.ignore(1000, '\n');
    }
}


    ExpenseTracker* user = new ExpenseTracker(uname, pwd, bal);


    cout << GREEN << "\nAccount Created Successfully!\n" << RESET << endl;

//------------------SignIn------------
    string loginUser, loginPass;
    cout <<"\t\t" BLUE << "========== SIGN IN ==========" << RESET << endl;
    while (true) {
        cout << "Enter Username: ";
         cin >> loginUser;
        cout << "Enter Password: ";
         cin >> loginPass;

        if (user->login(loginUser, loginPass)) {
            cout << GREEN << "\nLogin Successful!" << RESET << endl;
            break;
        } else {
            cout << RED << "Invalid Username or Password. Try again.\n" << RESET;
        }
    }
                    //----Main Menu----
    int choice;
    do {
        cout <<"\t\t"<<YELLOW << "====================================================" << endl;
        cout <<"\t\t" "|                EXPENSE TRACKER MENU              |" << endl;
        cout <<"\t\t" "====================================================" << RESET << endl;
        cout << "1. Show Balance" << endl;
        cout << "2. Deposit Money" << endl;
        cout << "3. Spend Money" << endl;
        cout << "4. Add Expense" << endl;
        cout << "5. Show Expense History" << endl;
        cout << "6. Show Summary" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter Choice: "; cin >> choice;

        switch (choice) {
            case 1: user->showBalance(); break;
            case 2: {
                double amt; 
                cout << "Enter Deposit Amount: $";  
                cin >> amt;
                user->deposit(amt); 
                break;
            }
            case 3: {
                double amt; 
                cout << "Enter Spend Amount: $"; 
                cin >> amt; 
                user->spend(amt); 
                break;
            }
            case 4: {
                string desc; double amt;
                cin.ignore();
                cout << "Enter Expense Description: "; 
                getline(cin, desc);
                cout << "Enter Amount: $"; 
                cin >> amt;
                user->addExpense(desc, amt); 
                break;
            }
            case 5:
                 user->showExpenses(); break;
            case 6: 
                   showSummary(*user); break;
            case 7: 
                    cout << GREEN << "\nExiting Program..." << RESET << endl; break;
            default: 
                     cout << RED << "Invalid Choice!" << RESET << endl;
        }
    } while (choice != 7);

    delete user;
    return 0;
}
