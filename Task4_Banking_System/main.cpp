#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <limits>
#include <ctime>
#include <algorithm>
using namespace std;

struct Transaction {
    string type;
    double amount;
    double balanceAfter;
    string timestamp;
};

string getCurrentTime() {
    time_t now = time(nullptr);
    tm* localTime = localtime(&now);

    char buffer[30];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localTime);
    return string(buffer);
}

class Account {
private:
    int accountNumber;
    string accountType;
    double balance;
    vector<Transaction> transactions;

    void addTransaction(const string& type, double amount) {
        transactions.push_back({
            type,
            amount,
            balance,
            getCurrentTime()
        });
    }

public:
    Account(int number, const string& type, double initialDeposit)
        : accountNumber(number), accountType(type), balance(initialDeposit) {
        if (initialDeposit > 0)
            addTransaction("Account Opening Deposit", initialDeposit);
    }

    int getAccountNumber() const {
        return accountNumber;
    }

    double getBalance() const {
        return balance;
    }

    string getAccountType() const {
        return accountType;
    }

    bool deposit(double amount) {
        if (amount <= 0)
            return false;

        balance += amount;
        addTransaction("Deposit", amount);
        return true;
    }

    bool withdraw(double amount) {
        if (amount <= 0 || amount > balance)
            return false;

        balance -= amount;
        addTransaction("Withdrawal", amount);
        return true;
    }

    bool transferTo(Account& receiver, double amount) {
        if (!withdraw(amount))
            return false;

        receiver.deposit(amount);

        // Make the latest sender transaction clearly identify a transfer.
        transactions.back().type = "Transfer to Account " +
                                   to_string(receiver.accountNumber);
        return true;
    }

    void displayAccountInfo() const {
        cout << "\n----------------------------------------\n";
        cout << "Account Number : " << accountNumber << '\n';
        cout << "Account Type   : " << accountType << '\n';
        cout << "Balance        : Rs. " << fixed << setprecision(2)
             << balance << '\n';
        cout << "----------------------------------------\n";
    }

    void displayTransactions() const {
        cout << "\n========== TRANSACTION HISTORY ==========\n";

        if (transactions.empty()) {
            cout << "No transactions available.\n";
            return;
        }

        for (const auto& t : transactions) {
            cout << t.timestamp << " | "
                 << left << setw(30) << t.type
                 << " | Amount: Rs. " << fixed << setprecision(2)
                 << setw(10) << t.amount
                 << " | Balance: Rs. " << t.balanceAfter << '\n';
        }
    }
};

class Customer {
private:
    int customerId;
    string name;
    string phone;
    vector<Account> accounts;

public:
    Customer(int id, const string& customerName, const string& customerPhone)
        : customerId(id), name(customerName), phone(customerPhone) {}

    int getCustomerId() const {
        return customerId;
    }

    void displayCustomerInfo() const {
        cout << "\n========== CUSTOMER ==========\n";
        cout << "Customer ID : " << customerId << '\n';
        cout << "Name        : " << name << '\n';
        cout << "Phone       : " << phone << '\n';
        cout << "Accounts    : " << accounts.size() << '\n';
    }

    void createAccount(int accountNumber, const string& type, double deposit) {
        accounts.emplace_back(accountNumber, type, deposit);
        cout << "Account created successfully. Account No: "
             << accountNumber << '\n';
    }

    Account* findAccount(int accountNumber) {
        for (auto& account : accounts) {
            if (account.getAccountNumber() == accountNumber)
                return &account;
        }
        return nullptr;
    }

    void showAccounts() const {
        if (accounts.empty()) {
            cout << "No accounts found for this customer.\n";
            return;
        }

        for (const auto& account : accounts)
            account.displayAccountInfo();
    }
};

class Bank {
private:
    vector<Customer> customers;
    int nextCustomerId = 1001;
    int nextAccountNumber = 50001;

    Customer* findCustomer(int id) {
        for (auto& customer : customers) {
            if (customer.getCustomerId() == id)
                return &customer;
        }
        return nullptr;
    }

    Account* findAccount(int accountNumber, Customer** owner = nullptr) {
        for (auto& customer : customers) {
            Account* account = customer.findAccount(accountNumber);
            if (account != nullptr) {
                if (owner)
                    *owner = &customer;
                return account;
            }
        }
        return nullptr;
    }

public:
    void createCustomer() {
        string name, phone;

        cout << "\n========== CREATE CUSTOMER ==========\n";
        cout << "Customer name: ";
        cin >> ws;
        getline(cin, name);

        cout << "Phone number: ";
        getline(cin, phone);

        customers.emplace_back(nextCustomerId, name, phone);

        cout << "Customer created successfully.\n";
        cout << "Customer ID: " << nextCustomerId << '\n';
        ++nextCustomerId;
    }

    void createAccount() {
        int customerId;
        string type;
        double initialDeposit;

        cout << "\nCustomer ID: ";
        cin >> customerId;

        Customer* customer = findCustomer(customerId);
        if (!customer) {
            cout << "Customer not found.\n";
            return;
        }

        cout << "Account type (Savings/Current): ";
        cin >> type;

        cout << "Initial deposit: Rs. ";
        cin >> initialDeposit;

        if (cin.fail() || initialDeposit < 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid deposit amount.\n";
            return;
        }

        customer->createAccount(nextAccountNumber, type, initialDeposit);
        ++nextAccountNumber;
    }

    void deposit() {
        int accountNumber;
        double amount;

        cout << "\nAccount number: ";
        cin >> accountNumber;
        cout << "Deposit amount: Rs. ";
        cin >> amount;

        Account* account = findAccount(accountNumber);

        if (!account) {
            cout << "Account not found.\n";
            return;
        }

        if (account->deposit(amount))
            cout << "Deposit successful.\n";
        else
            cout << "Invalid deposit amount.\n";
    }

    void withdraw() {
        int accountNumber;
        double amount;

        cout << "\nAccount number: ";
        cin >> accountNumber;
        cout << "Withdrawal amount: Rs. ";
        cin >> amount;

        Account* account = findAccount(accountNumber);

        if (!account) {
            cout << "Account not found.\n";
            return;
        }

        if (account->withdraw(amount))
            cout << "Withdrawal successful.\n";
        else
            cout << "Withdrawal failed. Check amount or available balance.\n";
    }

    void transfer() {
        int senderNumber, receiverNumber;
        double amount;

        cout << "\nSender account number: ";
        cin >> senderNumber;
        cout << "Receiver account number: ";
        cin >> receiverNumber;
        cout << "Transfer amount: Rs. ";
        cin >> amount;

        if (senderNumber == receiverNumber) {
            cout << "Sender and receiver accounts must be different.\n";
            return;
        }

        Account* sender = findAccount(senderNumber);
        Account* receiver = findAccount(receiverNumber);

        if (!sender || !receiver) {
            cout << "One or both accounts were not found.\n";
            return;
        }

        if (sender->transferTo(*receiver, amount))
            cout << "Transfer successful.\n";
        else
            cout << "Transfer failed. Check amount or available balance.\n";
    }

    void showAccount() {
        int accountNumber;
        cout << "\nAccount number: ";
        cin >> accountNumber;

        Account* account = findAccount(accountNumber);

        if (!account) {
            cout << "Account not found.\n";
            return;
        }

        account->displayAccountInfo();
    }

    void showTransactions() {
        int accountNumber;
        cout << "\nAccount number: ";
        cin >> accountNumber;

        Account* account = findAccount(accountNumber);

        if (!account) {
            cout << "Account not found.\n";
            return;
        }

        account->displayTransactions();
    }

    void showCustomer() {
        int customerId;
        cout << "\nCustomer ID: ";
        cin >> customerId;

        Customer* customer = findCustomer(customerId);

        if (!customer) {
            cout << "Customer not found.\n";
            return;
        }

        customer->displayCustomerInfo();
        customer->showAccounts();
    }
};

int main() {
    Bank bank;
    int choice;

    do {
        cout << "\n========================================\n";
        cout << "           BANKING SYSTEM\n";
        cout << "========================================\n";
        cout << "1. Create Customer\n";
        cout << "2. Create Account\n";
        cout << "3. Deposit Money\n";
        cout << "4. Withdraw Money\n";
        cout << "5. Transfer Funds\n";
        cout << "6. Show Account Information\n";
        cout << "7. Show Transaction History\n";
        cout << "8. Show Customer Information\n";
        cout << "9. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input.\n";
            continue;
        }

        switch (choice) {
            case 1: bank.createCustomer(); break;
            case 2: bank.createAccount(); break;
            case 3: bank.deposit(); break;
            case 4: bank.withdraw(); break;
            case 5: bank.transfer(); break;
            case 6: bank.showAccount(); break;
            case 7: bank.showTransactions(); break;
            case 8: bank.showCustomer(); break;
            case 9: cout << "Thank you for using the Banking System.\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 9);

    return 0;
}
