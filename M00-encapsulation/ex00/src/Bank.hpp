#pragma once

#include <iostream>
#include <map>
#include <sstream>
#include <string>

#include "Account.hpp"

class Bank {
    friend std::ostream& operator<<(std::ostream& os, Bank const& bank);

 public:
    Bank(void);
    ~Bank(void);

    Account const& operator[](int const id) const;

    float const&        getLiquidity(void) const;
    float const&        getTotalLoans(void) const;

    Account const& createAccount(void);
    Account const& createAccount(float const initialDeposit);
    void           deleteAccount(int const id);
    void           deposit(int const id, float const amount);
    void           withdrawal(int const id, float const amount);
    void           loan(int const id, float const amount);
    void           repay(int const id, float const amount);

    class Exception : public std::exception {
        friend class Bank;

     private:
        Exception(void);
    };

    class AccountNotFound : public Bank::Exception {
     public:
        virtual char const* what() const throw();
    };

    class NotEnoughAccountMoney : public Bank::Exception {
     public:
        virtual char const* what() const throw();
    };

    class NotEnoughLiquidity : public Bank::Exception {
     public:
        virtual char const* what() const throw();
    };

    class BankLiquidityLimit : public Bank::Exception {
     public:
        virtual char const* what() const throw();
    };

 private:
    typedef std::map<int, Account*> BankAccounts;

    static float const _inflowTax;
    static float const _min_liquidity_percentage;

    BankAccounts _accounts;
    float        _liquidity;
    float        _totalLoans;

    void checkLiquidity(void);
    void checkLiquidity(float const amount);

    Account&    getAccount(int const id);
};
