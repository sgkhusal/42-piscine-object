#pragma once

#include <iostream>
#include <map>
#include <vector>

#include "Position.hpp"
#include "Statistic.hpp"
#include "Tool.hpp"
#include "ToolWorker.hpp"
#include "test_utils.hpp"

class Worker {
 public:
    Worker(void) : coordonnee(Position()), stat(Statistic()), tool(NULL) {
        test::comment("Worker constructor called");
    }
    Worker(Position const& p, Statistic const& s)
        : coordonnee(p), stat(s), tool(NULL) {
        test::comment("Worker constructor called");
    }
    Worker(int x, int y, int z, int level, int exp)
        : coordonnee(Position(x, y, z)), stat(Statistic(level, exp)), tool(NULL) {
        test::comment("Worker constructor called");
    }
    ~Worker(void) {
        test::comment("Worker destructor called");
        if (this->tool && ToolWorker::get(this->tool))
            ToolWorker::remove(this->tool);
    }

    class Exception : public std::exception {
     private:
        Exception(void) {}
        friend class Worker;
    };

    class NoTool : public Worker::Exception {
     public:
        virtual char const* what() const throw() { return "Worker has no tool"; }
    };

    void work(void) {
        if (!tool) throw Worker::NoTool();
        if (!ToolWorker::get(this->tool)) {
            this->tool = NULL;
            throw Worker::NoTool();
        }
        test::comment("Worker is working with his tool");
        tool->use();
    }

    void takeTool(Tool* tool) {
        Worker* oldWorker = ToolWorker::get(tool);

        if (oldWorker) oldWorker->releaseTool();
        std::cout << GREEN << "Worker gets a tool at " << tool << RESET
                  << std::endl;
        this->tool = tool;
        ToolWorker::add(tool, this);
    }

    void releaseTool(void) {
        if (this->tool && ToolWorker::get(this->tool)) {
            ToolWorker::remove(this->tool);
            this->tool = NULL;
            test::comment("Worker releases the tool");
        } else {
            throw Worker::NoTool();
        }
    }

 private:
    Position  coordonnee;
    Statistic stat;
    Tool*     tool;

    friend std::ostream& operator<<(std::ostream& os, Worker const& rhs) {
        os << "Worker:\n"
           << "- Position: " << rhs.coordonnee << "\n- Statistics: " << rhs.stat
           << "\n- Tool pointer at: " << rhs.tool;
        return os;
    }
};
