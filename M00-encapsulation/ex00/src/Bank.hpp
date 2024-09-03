#pragma once

#include <iostream>
#include <map>

#include "Account.hpp"

class Bank {
 public:
    Bank(void);
    ~Bank(void);

    Account const& operator[](int const id) const;

    Account const& createAccount(void);
    Account const& createAccount(float const initialDeposit);
    void           deleteAccount(int const id);
    void           makeDeposit(int const id, float const amount);
    void           makeLoan(int const id, float const amount);
    void           makeWithdrawal(int const id, float const amount);

    // float const&          getLiquidity(void) const;

 private:
    typedef std::map<int, Account*> BankAccounts;
    float                           _liquidity;
    BankAccounts                    _accounts;

    Account& getAccount(int const id);

    class AccountNotFound : public std::exception {
     public:
        virtual const char* what() const throw();
    };

    class NotEnoughBankLiquidity : public std::exception {
     public:
        virtual const char* what() const throw();
    };

    class NotEnoughAccountMoney : public std::exception {
     public:
        virtual const char* what() const throw();
    };

    // friend std::ostream& operator<<(std::ostream& os, const Bank& bank) {
    //     BankAccounts::const_iterator it;

    //     os << "Bank informations : " << std::endl;
    //     os << "Liquidity : " << bank._liquidity << std::endl;
    //     for (it = bank._accounts.begin(); it != bank._accounts.end(); it++)
    //         os << "it" << std::endl;
    //     return (os);
    // }
};
