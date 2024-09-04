#include "Bank.hpp"

float const Bank::_inflowTax                = 0.05;
float const Bank::_min_liquidity_percentage = 0.5;

Bank::Bank(void) : _accounts(BankAccounts()), _liquidity(0), _totalLoans(0.0) {}

Bank::~Bank(void) {
    BankAccounts::const_iterator it;

    for (it = this->_accounts.begin(); it != this->_accounts.end(); it++) {
        delete (*it).second;
    }
}

Account const& Bank::operator[](int const id) const {
    BankAccounts::const_iterator it = _accounts.find(id);

    if (it == _accounts.end()) throw AccountNotFound();
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
    Account* account = new Account();

    if (_accounts.find(account->getId()) != _accounts.end())
        throw std::logic_error("Account with the same id already exists");

    this->_accounts[account->getId()] = account;
    this->deposit(account->getId(), initialDeposit);
    return *account;
}

void Bank::deleteAccount(int const id) {
    BankAccounts::iterator it = _accounts.find(id);

    if (it == _accounts.end()) throw AccountNotFound();
    delete it->second;
    _accounts.erase(it);
}

void Bank::deposit(int const id, float const amount) {
    Account&    account  = *(_accounts[id]);
    float const discount = amount * _inflowTax;

    _liquidity += amount;
    account._value += (amount - discount);
}

void Bank::withdrawal(int const id, float const amount) {
    Account& account = *(_accounts[id]);

    if (account.getValue() < amount) throw NotEnoughAccountMoney();
    checkLiquidity(amount);
    account._value -= amount;
    _liquidity -= amount;
}

void Bank::loan(int const id, float const amount) {
    Account& account = *(_accounts[id]);

    checkLiquidity(amount);
    account._value += amount;

    float loan_fees = amount * _inflowTax;
    float debt      = amount + loan_fees;
    account._loanDebts += debt;
    _totalLoans += debt;
}

void Bank::repay(int const id, float const amount) {
    Account& account = *(_accounts[id]);

    if (account.getValue() < amount) throw NotEnoughAccountMoney();
    account._value -= amount;
    account._loanDebts -= amount;
    _totalLoans -= amount;
}

void Bank::checkLiquidity(void) { checkLiquidity(0.0); }
void Bank::checkLiquidity(float const amount) {
    BankAccounts::const_iterator it;
    float                        bankDebts = 0.0;

    if (_liquidity - amount < 0) throw NotEnoughLiquidity();

    for (it = _accounts.begin(); it != _accounts.end(); it++)
        bankDebts += it->second->_value;

    if ((_liquidity - amount) / bankDebts < _min_liquidity_percentage)
        throw BankLiquidityLimit();
}

Bank::Exception::Exception(void) {}

char const* Bank::AccountNotFound::what() const throw() { return "Account Not Found"; }

char const* Bank::NotEnoughAccountMoney::what() const throw() {
    return "The account does not have enough money";
}

char const* Bank::NotEnoughLiquidity::what() const throw() {
    return "Bank has no liquidity";
}

char const* Bank::BankLiquidityLimit::what() const throw() {
    float             percentage = Bank::_min_liquidity_percentage * 100;
    std::stringstream ss;
    std::string       text;

    ss << percentage;
    ss >> text;

    return (text + std::string("% liquidity limit reached")).c_str();
}

std::ostream& operator<<(std::ostream& os, Bank const& bank) {
    Bank::BankAccounts::const_iterator it;

    os << "Bank informations : " << std::endl;
    os << "Liquidity : " << bank._liquidity << std::endl;
    for (it = bank._accounts.begin(); it != bank._accounts.end(); it++)
        os << it->second << std::endl;
    return (os);
}
