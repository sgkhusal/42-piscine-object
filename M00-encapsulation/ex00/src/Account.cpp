#include "Account.hpp"

int Account::_accountsNb = 0;

Account::Account(void) {
    Account::_accountsNb += 1;
    _id         = Account::_accountsNb;
    _value      = 0.0;
    _totalLoans = 0.0;
}

Account::Account(const int id) : _id(id), _value(0.0), _totalLoans(0.0) {}

Account::Account(const int id, const float initialDeposit)
    : _id(id), _value(initialDeposit), _totalLoans(0.0) {}

Account::~Account(void) {}

Account::Account(Account const& account) {
    Account::_accountsNb += 1;
    _id         = Account::_accountsNb;
    _value      = account.getValue();
    _totalLoans = account.getTotalLoans();
}

Account& Account::operator=(Account const& rhs) {
    if (this != &rhs) {
        _value = rhs.getValue();
    }
    return *this;
}

int const& Account::getId(void) const { return _id; }

float const& Account::getValue(void) const { return _value; }

float const& Account::getTotalLoans(void) const { return _totalLoans; }
