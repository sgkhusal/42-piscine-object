#pragma once

#include <iostream>
#include <vector>

class Account {
 public:
    int const&   getId(void) const;
    float const& getValue(void) const;
    float const& getTotalLoans(void) const;

    friend class Bank;

    friend std::ostream& operator<<(std::ostream& os, const Account& account) {
        os << "[" << account._id << "] - [" << account._value << "]";
        return (os);
    }

 private:
    Account(void);
    explicit Account(const int id);
    explicit Account(const int id, const float initialDeposit);
    ~Account(void);
    Account(Account const& account);
    Account& operator=(Account const& b);

    int   _id;
    float _value;
    float _totalLoans;

    static int _accountsNb;
};
