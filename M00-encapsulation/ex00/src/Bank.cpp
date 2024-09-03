#include "Bank.hpp"

Bank::Bank(void) : _liquidity(0), _accounts(Bank::BankAccounts()) {}

Bank::~Bank(void) {
    BankAccounts::const_iterator it;

    for (it = this->_accounts.begin(); it != this->_accounts.end(); it++) {
        delete (*it).second;
    }
}

Account const& Bank::operator[](int const id) const {
    BankAccounts::const_iterator it = _accounts.find(id);

    if (it == _accounts.end()) throw Bank::AccountNotFound();
    return *(it->second);
}

Account const& Bank::createAccount(void) {
    Account* account = new Account();

    if (_accounts.find(account->getId()) != _accounts.end())
        throw std::logic_error("Account with the same id already exists");

    this->_accounts[account->getId()] = account;
    return *account;
}

Account const& Bank::createAccount(float const initialDeposit) {
    Account* account = new Account(initialDeposit);

    if (_accounts.find(account->getId()) != _accounts.end())
        throw std::logic_error("Account with the same id already exists");

    this->_accounts[account->getId()] = account;
    return *account;
}

void Bank::deleteAccount(int const id) {
    BankAccounts::iterator it = _accounts.find(id);

    // if (it == _accounts.end()) throw Bank::AccountNotFound();
    delete it->second;
    _accounts.erase(it);
}

void Bank::makeDeposit(int const id, float const amount) {
    Account& account  = this->getAccount(id);
    float    discount = amount * 0.05;

    _liquidity += discount;
    // _liquidity += amount;
    account._value += (amount - discount);
}

void Bank::makeLoan(int const id, float const amount) {
    Account& account = this->getAccount(id);

    // if (_liquidity < amount) throw Bank::NotEnoughBankLiquidity();
    _liquidity -= amount;
    account._value += amount;
    account._totalLoans += amount;
}

void Bank::makeWithdrawal(int const id, float const amount) {
    Account& account = this->getAccount(id);

    // if (account.getValue() < amount) throw Bank::NotEnoughAccountMoney();
    account._value -= amount;
}

Account& Bank::getAccount(int const id) {
    BankAccounts::iterator it = _accounts.find(id);

    // if (it == _accounts.end()) throw Bank::AccountNotFound();
    return *(it->second);
}

// float const& Bank::getLiquidity(void) const { return this->_liquidity; }

// const char* Account::UnavailableMoney::what() const throw() {
//     return "Unavailable money in account";
// }

const char* Bank::AccountNotFound::what() const throw() { return "Account Not Found"; }
