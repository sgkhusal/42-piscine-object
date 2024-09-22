#pragma once

#include <string>
#include <iostream>

#include "ToolWorker.hpp"
#include "test_utils.hpp"

enum ToolType { TOOL, SHOVEL, HAMMER };

class Tool {
 public:
    Tool(void) : numberOfUses(0), type(TOOL) {
        test::comment("Tool constructor called");
    }
    explicit Tool(ToolType type) : numberOfUses(0), type(type) {
        test::comment("Tool constructor called");
    }
    virtual ~Tool(void) {
        test::comment("Tool destructor called");
        ToolWorker::remove(this);
    }

 protected:
    int      numberOfUses;
    ToolType type;

    virtual void use(void) = 0;
    std::string  getType(void) const {
        switch (this->type) {
            case SHOVEL:
                return "shovel";
            case HAMMER:
                return "hammer";
            default:
                return "tool";
        }
    }

    friend class Worker;

    friend std::ostream& operator<<(std::ostream& os, Tool const& rhs) {
        os << rhs.getType() << " used " << rhs.numberOfUses << " times";
        return os;
    }
};
