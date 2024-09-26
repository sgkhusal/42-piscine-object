#pragma once

#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "Position.hpp"
#include "Statistic.hpp"
#include "Tool.hpp"
#include "ToolWorker.hpp"
#include "test_utils.hpp"

class Worker {
 public:
    Worker(void) : coordonnee(Position()), stat(Statistic()), tools(WorkerTools()) {
        test::comment("Worker constructor called");
    }
    Worker(Position const& p, Statistic const& s)
        : coordonnee(p), stat(s), tools(WorkerTools()) {
        test::comment("Worker constructor called");
    }
    Worker(int x, int y, int z, int level, int exp)
        : coordonnee(Position(x, y, z)),
          stat(Statistic(level, exp)),
          tools(WorkerTools()) {
        test::comment("Worker constructor called");
    }
    ~Worker(void) {
        Worker::WorkerTools::const_iterator it_map;
        std::vector<Tool*>::const_iterator  it;
        std::vector<Tool*>                  tools;

        test::comment("Worker destructor called");

        for (it_map = this->tools.begin(); it_map != this->tools.end(); it_map++) {
            tools = it_map->second;
            for (it = tools.begin(); it != tools.end(); it++) {
                if (ToolWorker::get(*it)) ToolWorker::remove(*it);
            }
        }
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

    Tool* getTool(ToolType type) {
        Worker::WorkerTools::iterator it_type;

        it_type = this->tools.find(type);
        if (it_type == this->tools.end()) return NULL;
        if (it_type->second.size() == 0) {
            tools.erase(it_type);
            return NULL;
        }

        return it_type->second[0];
    }

    void work(void) {
        if (tools.empty()) throw Worker::NoTool();

        Worker::WorkerTools::iterator it_map = this->tools.begin();
        std::vector<Tool*>::iterator  it;
        std::vector<Tool*>            tools;
        Tool*                         tool = NULL;

        while (it_map != this->tools.end()) {
            tools = it_map->second;
            for (it = tools.begin(); it != tools.end(); it++) {
                // if (!ToolWorker::get(*it)) {
                //     tools.erase(it);
                //     if (tools.size() == 0) tools.erase(it);
                //     continue;
                // }
                tool = *it;
            }
            if (tool) break;
            it_map++;
        }
        if (!tool) throw Worker::NoTool();

        test::comment("Worker is working with his tool");
        tool->use();
    }

    void work(ToolType type) {
        if (tools.empty()) throw Worker::NoTool();
        Tool* tool = this->getTool(type);
        if (!tool) throw Worker::NoTool();

        test::comment("Worker is working with his tool");
        tool->use();
    }

    void takeTool(Tool* tool) {
        Worker* oldWorker = ToolWorker::get(tool);
        if (oldWorker == this) return;

        if (oldWorker) oldWorker->releaseTool(tool);

        Worker::WorkerTools::iterator it_type = this->tools.find(tool->type);
        if (it_type == this->tools.end()) {
            this->tools[tool->type] = std::vector<Tool*>();
        } else {
            std::vector<Tool*>::iterator it;
            std::vector<Tool*>           tools = it_type->second;
            for (it = tools.begin(); it != tools.end(); it++) {
                if (*it == tool) return;  // this should not happen! throw error?
            }
        }
        this->tools[tool->type].push_back(tool);

        std::cout << GREEN << "Worker gets a tool at " << tool << RESET << std::endl;
        ToolWorker::add(tool, this);
    }

    void releaseTool(Tool* tool) {
        Worker::WorkerTools::iterator it_type;
        std::vector<Tool*>::iterator  it;
        std::vector<Tool*>            tools;
        bool                          has_tool = false;

        it_type = this->tools.find(tool->type);
        if (it_type == this->tools.end()) throw Worker::NoTool();
        if (it_type->second.size() == 0) throw Worker::NoTool();

        tools = it_type->second;
        for (it = tools.begin(); it != tools.end(); it++) {
            if (*it == tool) {
                has_tool = true;
                if (ToolWorker::get(tool)) ToolWorker::remove(tool);
                tools.erase(it);
                std::cout << GREEN << "Worker releases the tool " << (*it)->getType()
                          << RESET << std::endl;
                if (this->getTool(HAMMER))  // remove this
                    throw std::runtime_error("Não ficou vazio...");
                break;
            }
        }

        if (!has_tool) throw Worker::NoTool();
    }

 private:
    typedef std::map<ToolType, std::vector<Tool*> > WorkerTools;

    Position    coordonnee;
    Statistic   stat;
    WorkerTools tools;

    friend std::ostream& operator<<(std::ostream& os, Worker const& rhs) {
        Worker::WorkerTools::const_iterator it_map;
        std::vector<Tool*>::const_iterator  it;
        std::vector<Tool*>                  tools;

        os << "Worker:\n"
           << "- Position: " << rhs.coordonnee << "\n- Statistics: " << rhs.stat
           << "\n- Tools:";
        if (rhs.tools.empty()) os << " None";
        for (it_map = rhs.tools.begin(); it_map != rhs.tools.end(); it_map++) {
            tools = it_map->second;
            for (it = tools.begin(); it != tools.end(); it++) os << "\n   - " << **it;
        }
        return os;
    }
};
