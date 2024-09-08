#include "Account.hpp"

int Account::_accountsNb = 0;

Account::Account(void) {
    Account::_accountsNb += 1;
    _id        = Account::_accountsNb;
    _value     = 0.0;
    _loanDebts = 0.0;
}

Account::~Account(void) {}

int const& Account::getId(void) const { return _id; }

float const& Account::getValue(void) const { return _value; }

float const& Account::getTotalLoans(void) const { return _loanDebts; }

std::ostream& operator<<(std::ostream& os, Account const& account) {
    os << "Account: [" << account.getId() << "] - value: [" << account.getValue()
       << "] - total loans debts: [" << account.getTotalLoans() << "]";
    return (os);
}
