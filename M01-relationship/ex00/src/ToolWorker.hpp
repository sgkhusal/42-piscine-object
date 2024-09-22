#pragma once

#include <iostream>
#include <map>

#include "test_utils.hpp"

class Tool;
class Worker;

class ToolWorker {
 private:
    ToolWorker(void) {
        throw std::runtime_error("Can not instantiate ToolWorker table");
    }

    typedef std::map<Tool*, Worker*> Table;

    static Table table;

    static Worker* get(Tool* tool) {
        test::comment("ToolWorker table static method 'get' called");
        if (!tool)
            throw std::runtime_error("ToolWorker table: null tool pointer");

        Table::iterator it;
        it = ToolWorker::table.find(tool);

        if (it == ToolWorker::table.end())
            return NULL;

        return it->second;
    }

    static void add(Tool* tool, Worker* worker) {
        test::comment("ToolWorker table static method 'add' called");
        if (!tool)
            throw std::runtime_error("ToolWorker table: null tool pointer");
        if (!worker)
            throw std::runtime_error("ToolWorker table: null worker pointer");

        ToolWorker::table[tool] = worker;
    }

    static void remove(Tool* tool) {
        test::comment("ToolWorker table static method 'remove' called");
        if (!tool)
            throw std::runtime_error("ToolWorker table: null tool pointer");

        Table::iterator it;
        it = ToolWorker::table.find(tool);

        if (it != ToolWorker::table.end())
            ToolWorker::table.erase(it);
    }

    friend class Worker;
    friend class Tool;
};

ToolWorker::Table ToolWorker::table = ToolWorker::Table();
