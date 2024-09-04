#pragma once

#include <iostream>

class Account {
    friend class Bank;
    friend std::ostream& operator<<(std::ostream& os, Account const& account);

 private:
    Account(void);
    ~Account(void);

    int   _id;
    float _value;
    float _loanDebts;

    static int _accountsNb;

    int const&   getId(void) const;
    float const& getValue(void) const;
    float const& getTotalLoans(void) const;
};
