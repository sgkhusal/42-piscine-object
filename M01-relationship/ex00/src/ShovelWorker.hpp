#pragma once

#include <iostream>
#include <map>

#include "test_utils.hpp"

class Shovel;
class Worker;

class ShovelWorker {
 private:
    ShovelWorker(void) {
        throw std::runtime_error("Can not instantiate ShovelWorker table");
    }

    typedef std::map<Shovel*, Worker*> Table;

    static Table table;

    static Worker* get(Shovel* shovel) {
        test::comment("ShovelWorker table static method 'get' called");
        if (!shovel)
            throw std::runtime_error("ShovelWorker table: null shovel pointer");

        Table::iterator it;
        it = ShovelWorker::table.find(shovel);

        if (it == ShovelWorker::table.end())
            return NULL;

        return it->second;
    }

    static void add(Shovel* shovel, Worker* worker) {
        test::comment("ShovelWorker table static method 'add' called");
        if (!shovel)
            throw std::runtime_error("ShovelWorker table: null shovel pointer");
        if (!worker)
            throw std::runtime_error("ShovelWorker table: null worker pointer");

        ShovelWorker::table[shovel] = worker;
    }

    static void remove(Shovel* shovel) {
        test::comment("ShovelWorker table static method 'remove' called");
        if (!shovel)
            throw std::runtime_error("ShovelWorker table: null shovel pointer");

        Table::iterator it;
        it = ShovelWorker::table.find(shovel);

        if (it != ShovelWorker::table.end())
            ShovelWorker::table.erase(it);
    }

    friend class Worker;
    friend class Shovel;
};

ShovelWorker::Table ShovelWorker::table = ShovelWorker::Table();
