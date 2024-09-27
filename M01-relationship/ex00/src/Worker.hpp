#pragma once

#include <iostream>
#include <map>
#include <set>
#include <string>
#include <typeinfo>

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
        std::set<Tool*>::const_iterator     it;
        std::set<Tool*>                     tools;

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

    template <typename T>
    Tool* getTool(void) {
        Worker::WorkerTools::iterator it_type;
        T                             tool;
        std::cout << PURPLE
                  << "BONUS getTool<ToolType> with ToolType = " << typeid(tool).name()
                  << RESET << std::endl;

        it_type = this->tools.find(tool.type);
        if (it_type == this->tools.end()) return NULL;
        if (it_type->second.size() == 0) {
            tools.erase(it_type);
            return NULL;
        }

        return *(it_type->second.begin());
    }

    Tool* getTool(void) {
        Worker::WorkerTools::iterator it_map = this->tools.begin();
        std::set<Tool*>::iterator     it;
        std::set<Tool*>*              tools;
        Tool*                         tool = NULL;

        while (it_map != this->tools.end()) {
            tools = &(it_map->second);
            it    = tools->begin();

            while (it != tools->end()) {
                if (!ToolWorker::get(*it)) {
                    tools->erase(it);
                    it = tools->begin();
                } else {
                    tool = *it;
                    break;
                }
            }

            if (tool) break;

            if (tools->size() == 0) {
                this->tools.erase(it_map->first);
                it_map = this->tools.begin();
                std::cout << "passou aqui" << std::endl;
            } else {
                it_map++;
            }
        }

        return tool;
    }

    void work(void) {
        Tool* tool = this->getTool();

        if (!tool) throw Worker::NoTool();
        test::comment("Worker is working with his tool");
        tool->use();
    }

    template <typename T>
    void work(void) {
        if (tools.empty()) throw Worker::NoTool();

        Tool* tool = this->getTool<T>();
        if (!tool) throw Worker::NoTool();

        test::comment("Worker is working with his tool");
        tool->use();
    }

    void takeTool(Tool* tool) {
        Worker* oldWorker = ToolWorker::get(tool);
        if (oldWorker == this) {
            test::comment("Worker already has this tool");
            return;
        }

        if (oldWorker) oldWorker->releaseTool(tool);

        Worker::WorkerTools::iterator it_type = this->tools.find(tool->type);
        if (it_type == this->tools.end()) this->tools[tool->type] = std::set<Tool*>();
        this->tools[tool->type].insert(tool);

        std::cout << GREEN << "Worker gets a tool at " << tool << RESET << std::endl;
        ToolWorker::add(tool, this);
    }

    void releaseTool(Tool* tool) {
        Worker::WorkerTools::iterator it_type;
        std::set<Tool*>::iterator     it;
        std::set<Tool*>               tools;

        it_type = this->tools.find(tool->type);
        if (it_type == this->tools.end()) throw Worker::NoTool();
        if (it_type->second.size() == 0) throw Worker::NoTool();

        tools = it_type->second;
        it    = tools.find(tool);
        if (it == tools.end()) throw Worker::NoTool();

        if (ToolWorker::get(tool)) ToolWorker::remove(tool);
        tools.erase(*it);
        if (tools.size() == 0) this->tools.erase(tool->type);
        std::cout << GREEN << "Worker releases the tool " << (*it)->getType() << RESET
                  << std::endl;
    }

 private:
    typedef std::map<ToolType, std::set<Tool*> > WorkerTools;

    Position    coordonnee;
    Statistic   stat;
    WorkerTools tools;

    friend std::ostream& operator<<(std::ostream& os, Worker const& rhs) {
        Worker::WorkerTools::const_iterator it_map;
        std::set<Tool*>::const_iterator     it;
        std::set<Tool*>                     tools;

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
