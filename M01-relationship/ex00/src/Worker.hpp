#pragma once

#include "Position.hpp"
#include "Shovel.hpp"
#include "ShovelWorker.hpp"
#include "Statistic.hpp"
#include "test_utils.hpp"

class Worker {
 public:
    Worker(void) : coordonnee(Position()), stat(Statistic()), shovel(NULL) {
        test::comment("Worker constructor called");
    }
    Worker(Position const& p, Statistic const& s)
        : coordonnee(p), stat(s), shovel(NULL) {
        test::comment("Worker constructor called");
    }
    Worker(int x, int y, int z, int level, int exp)
        : coordonnee(Position(x, y, z)), stat(Statistic(level, exp)), shovel(NULL) {
        test::comment("Worker constructor called");
    }
    ~Worker(void) {
        test::comment("Worker destructor called");
        if (this->shovel && ShovelWorker::get(this->shovel))
            ShovelWorker::remove(this->shovel);
    }

    class Exception : public std::exception {
        friend class Worker;

     private:
        Exception(void) {}
    };

    class NoShovel : public Worker::Exception {
     public:
        virtual char const* what() const throw() { return "Worker has no shovel"; }
    };

    void work(void) {
        if (!shovel) throw Worker::NoShovel();
        if (!ShovelWorker::get(this->shovel)) {
            this->shovel = NULL;
            throw Worker::NoShovel();
        }
        test::comment("Worker is working with his shovel");
        shovel->use();
    }

    void takeShovel(Shovel* shovel) {
        Worker* oldWorker = ShovelWorker::get(shovel);

        if (oldWorker) oldWorker->releaseShovel();
        std::cout << GREEN << "Worker gets a shovel at " << shovel << RESET
                  << std::endl;
        this->shovel = shovel;
        ShovelWorker::add(shovel, this);
    }

    void releaseShovel(void) {
        if (this->shovel && ShovelWorker::get(this->shovel)) {
            ShovelWorker::remove(this->shovel);
            this->shovel = NULL;
            test::comment("Worker releases the shovel");
        } else {
            throw Worker::NoShovel();
        }
    }

 private:
    Position  coordonnee;
    Statistic stat;
    Shovel*   shovel;

    friend std::ostream& operator<<(std::ostream& os, Worker const& rhs) {
        os << "Worker:\n"
           << "- Position: " << rhs.coordonnee << "\n- Statistics: " << rhs.stat
           << "\n- Shovel pointer at: " << rhs.shovel;
        return os;
    }
};
