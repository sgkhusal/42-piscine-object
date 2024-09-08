#include <cassert>
#include <iostream>

#include "Bank.hpp"
#include "test.hpp"

int main() {
    test::title("CREATE A BANK");
    Bank bank = Bank();
    std::cout << bank << std::endl;
    assert(bank.getLiquidity() == 0);
    assert(bank.getTotalLoans() == 0);

    test::title("THE BANK CAN CREATE ACCOUNTS");
    // Account acc = Account();  // not compile
    Account acc1 = bank.createAccount();
    int     id1  = acc1.getId();
    std::cout << "Created: " << acc1 << std::endl;
    assert(acc1.getValue() == 0.0);
    assert(acc1.getTotalLoans() == 0.0);
    assert(bank[id1].getValue() == 0.0);
    assert(bank[id1].getTotalLoans() == 0.0);

    Account acc2 = bank.createAccount(500);
    int     id2  = acc2.getId();
    std::cout << "Created: " << acc2 << std::endl;
    assert(acc2.getValue() == 475.0);
    assert(acc2.getTotalLoans() == 0.0);
    assert(bank[id2].getValue() == 475.0);
    assert(bank[id2].getTotalLoans() == 0.0);

    Account acc3 = bank.createAccount();
    std::cout << "Created: " << acc3 << std::endl;

    std::cout << bank << std::endl;
    assert(bank.getLiquidity() == 500);
    assert(bank.getTotalLoans() == 0);

    test::title("THE BANK CAN DELETE ACCOUNTS");
    int id = acc3.getId();
    bank.deleteAccount(id);
    try {
        std::cout << bank[id] << std::endl;
    } catch (Bank::AccountNotFound& e) {
        test::error(e.what());
    }
    try {
        bank.deposit(id, 100);
    } catch (Bank::AccountNotFound& e) {
        test::error(e.what());
    }

    test::title("THE BANK CAN MODIFY ACCOUNTS");
    // not compile
    // acc1._id = 10;
    // acc1._value = 100;
    // acc1._loanDebts = 100;
    bank.deposit(acc1.getId(), 100);
    std::cout << "After deposit: " << bank << std::endl;
    assert(bank.getLiquidity() == 600);
    assert(bank[id1].getValue() == 95.0);

    bank.withdrawal(acc2.getId(), 100);
    std::cout << "After withdrawal: " << bank << std::endl;
    assert(bank.getLiquidity() == 500);
    assert(bank[id2].getValue() == 375.0);

    try {
        bank.withdrawal(id1, 200);
    } catch (Bank::NotEnoughAccountMoney& e) {
        test::error(e.what());
    }

    test::title("THE BANK MUST BE ABLE TO GIVE A LOAN TO A CUSTOMER");
    // within the limits of its funds
    bank.loan(acc1.getId(), 200);
    std::cout << "After loan: " << bank << std::endl;
    assert(bank.getLiquidity() == 300);
    assert(bank.getTotalLoans() == 210);
    assert(bank[id1].getValue() == 95.0);
    assert(bank[id1].getTotalLoans() == 210.0);

    try {
        bank.loan(acc2.getId(), 500);
    } catch (Bank::NotEnoughLiquidity& e) {
        test::error(e.what());
    }
    try {
        bank.loan(acc2.getId(), 200);
    } catch (Bank::BankLiquidityLimit& e) {
        test::error(e.what());
    }

    test::title("PLUS: repay debt");
    try {
        bank.repay(id1, 200);
    } catch (Bank::NotEnoughAccountMoney& e) {
        test::error(e.what());
    }
    bank.deposit(acc1.getId(), 150);
    bank.repay(id1, 200);
    std::cout << bank << std::endl;
    assert(bank.getLiquidity() == 650);
    assert(bank.getTotalLoans() == 10);
    assert(bank[id1].getValue() == 37.50);
    assert(bank[id1].getTotalLoans() == 10.0);

    return 0;
}
