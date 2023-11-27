// Points towards exams/quizzes

#include <iostream>
// Including library for formatting
#include <iomanip>

// Creating a base class that represents a generic account
class Account {
protected:
    std::string accountNumber;
    std::string accountHolder;
    double balance;

public:
    // Creating a constructor to initalize account info
    Account(const std::string& number, const std::string& holder, double initialBalance)
        : accountNumber(number), accountHolder(holder), balance(initialBalance) {}

    // Creating a function for the current balance
    double getBalance() const {
        return balance;
    }

    // Creating a function to display account dets
    virtual void displayDetails() const {
        std::cout << "   Holder: " << accountHolder << "\n"
                  << "   Balance: $" << std::fixed << std::setprecision(2) << balance;
    }

    // Creating a function to deposit money into the account
    virtual void deposit(double amount) {
        balance += amount;
    }

    // Creating a function to withdraw money from the account
    virtual void withdraw(double amount) {
        if (amount <= balance) {
            balance -= amount;
        } else {
            std::cout << "Insufficient funds for withdrawal\n";
        }
    }
};

// Creating a derived class that represents a savings account, it inherits from the account class
class SavingsAccount : public Account {
private:
    double interestRate;

public:
    // Creating a constructor to initialize savings account info
    SavingsAccount(const std::string& number, const std::string& holder, double initialBalance, double rate)
        : Account(number, holder, initialBalance), interestRate(rate) {}

    // Creating an override function to display savings account dets
    void displayDetails() const override {
        std::cout << "Account Details for Savings Account (ID: " << accountNumber << "):\n";
        Account::displayDetails();
        std::cout << "\n   Interest Rate: " << std::fixed << std::setprecision(2) << interestRate * 100 << "%";
        std::cout << "\n";
    }

    // Creating an ovveride function to withdraw money from a savings account
    void withdraw(double amount) override {
        const double minBalance = 100;
        if (getBalance() - amount >= minBalance) {
            balance -= amount;
        } else {
            std::cout << "Withdrawal failed minimum balance not met\n";
        }
    }
};

// Creating a derived class that respresents a current account, it inherits from the account class
class CurrentAccount : public Account {
private:
    double overdraftLimit;

public:
    // Creating a constructor to initalize current account info
    CurrentAccount(const std::string& number, const std::string& holder, double initialBalance, double limit)
        : Account(number, holder, initialBalance), overdraftLimit(limit) {}

    // Creating an override function to display current account dets
    void displayDetails() const override {
        std::cout << "Account Details for Current Account (ID: " << accountNumber << "):\n";
        Account::displayDetails();
        std::cout << "\n   Overdraft Limit: $" << std::fixed << std::setprecision(2) << overdraftLimit;
    }

    // Creating an override function to withdraw money from a current account
    void withdraw(double amount) override {
        if (getBalance() - amount >= -overdraftLimit) {
            balance -= amount;
        } else {
            std::cout << "Withdrawal failed overdraft limit exceeded\n";
        }
    }
};

// Overloaded operator+ to perform a transfer between a current and a savings account
CurrentAccount operator+(CurrentAccount current, SavingsAccount& savings) {
    const double transferAmount = 300;

    if (savings.getBalance() >= transferAmount) {
        current.deposit(transferAmount);
        savings.withdraw(transferAmount);
    } else {
        std::cout << "Transfer failed insufficient funds in savings account\n";
    }

    return current;
}

int main() {
    // Instances of savings and current acccounts
    SavingsAccount savings("S123", "John Doe", 1000, 0.02);
    CurrentAccount current("C456", "Jane Doe", 2000, 500);

    // Display initial account dets
    savings.displayDetails();
    std::cout << "\n";
    current.displayDetails();
    std::cout << "\n\n";

    // Perform deposit and withdrawal operations
    savings.deposit(500);
    current.withdraw(1000);

    // Display account dets after deposit and withdrawal
    std::cout << "Account Details after deposit and withdrawal:\n";
    savings.displayDetails();
    std::cout << "\n";
    current.displayDetails();
    std::cout << "\n\n";

    // Perform a transfer between current and savings accounts
    current = current + savings;

    // Display account details after transfer
    std::cout << "Account Details after transfer:\n";
    savings.displayDetails();
    std::cout << "\n";
    current.displayDetails();
    std::cout << "\n\n";

    return 0;
}