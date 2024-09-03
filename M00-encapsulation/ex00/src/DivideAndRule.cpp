#include <iostream>
#include <vector>

struct Account {
    int _id;
    int _value;

    Account() : _id(-1), _value(0) {}

    friend std::ostream& operator<<(std::ostream& p_os, const Account& p_account) {
        p_os << "[" << p_account._id << "] - [" << p_account._value << "]";
        return (p_os);
    }
};

struct Bank {
    int                   _liquidity;
    std::vector<Account*> _clientAccounts;

    Bank() : _liquidity(0) {}

    friend std::ostream& operator<<(std::ostream& p_os, const Bank& p_bank) {
        std::vector<Account*>::const_iterator it;
        p_os << "Bank informations : " << std::endl;
        p_os << "Liquidity : " << p_bank._liquidity << std::endl;
        for (it = p_bank._clientAccounts.begin(); it != p_bank._clientAccounts.end();
             it++)
            p_os << **it << std::endl;
        return (p_os);
    }
};

int main() {
    Account accountA = Account();
    accountA._id     = 0;
    accountA._value  = 100;

    Account accountB = Account();
    accountB._id     = 1;
    accountB._value  = 100;

    Bank bank       = Bank();
    bank._liquidity = 999;
    bank._clientAccounts.push_back(&accountA);
    bank._clientAccounts.push_back(&accountB);

    bank._liquidity -= 200;
    accountA._value += 400;

    std::cout << "Account : " << std::endl;
    std::cout << accountA << std::endl;
    std::cout << accountB << std::endl;

    std::cout << " ----- " << std::endl;

    std::cout << "Bank : " << std::endl;
    std::cout << bank << std::endl;

    return (0);
}
