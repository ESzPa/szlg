//
// Hi
//

#include <iostream>

#include "dumbq.h"
#include "linkedq.h"
#include "realq.h"

#define testq(var)                                                                                      \
    do {                                                                                                \
        std::cout << "Testing " << #var << ":\n";                                                       \
        bool empty_ok = (var).empty() && (var).size() == 0;                                             \
        std::cout << "\tInitially empty? " << (empty_ok ? "\033[32myes\033[0m" : "\033[31mno\033[0m")   \
                  << " (size=" << (var).size() << ")\n";                                                \
                                                                                                        \
        bool push_ok = false;                                                                           \
        try {                                                                                           \
            (var).push(25);                                                                             \
            push_ok = !(var).empty() && (var).size() == 1;                                              \
            std::cout << "\tPush 25: " << (push_ok ? "\033[32mOK\033[0m" : "\033[31mFAIL\033[0m")       \
                      << " (size=" << (var).size() << ")\n";                                            \
        } catch(...) {                                                                                  \
            std::cout << "\tPush: \033[31mFAIL\033[0m\n";                                               \
        }                                                                                               \
                                                                                                        \
        if(push_ok) {                                                                                   \
            try {                                                                                       \
                bool front_ok = (var).front() == 25;                                                    \
                bool back_ok = (var).back() == 25;                                                      \
                std::cout << "\tFront/Back: "                                                           \
                          << (front_ok && back_ok ? "\033[32mOK\033[0m" : "\033[31mFAIL\033[0m")        \
                          << " (front=" << (var).front() << ", back=" << (var).back() << ")\n";         \
            } catch(...) {                                                                              \
                std::cout << "\tFront/Back: \033[31mFAIL\033[0m\n";                                     \
            }                                                                                           \
        }                                                                                               \
                                                                                                        \
        if(push_ok) {                                                                                   \
            try {                                                                                       \
                (var).push(50);                                                                         \
                bool size_ok = (var).size() == 2;                                                       \
                bool back_ok = (var).back() == 50;                                                      \
                std::cout << "\tPush 50: "                                                              \
                          << (size_ok && back_ok ? "\033[32mOK\033[0m" : "\033[31mFAIL\033[0m")         \
                          << " (size=" << (var).size() << ", back=" << (var).back() << ")\n";           \
            } catch(...) {                                                                              \
                std::cout << "\tPush 50: \033[31mFAIL\033[0m\n";                                        \
            }                                                                                           \
        }                                                                                               \
                                                                                                        \
        if(push_ok && (var).size() >= 2) {                                                              \
            try {                                                                                       \
                auto old_front = (var).front();                                                         \
                auto old_size = (var).size();                                                           \
                (var).pop();                                                                            \
                bool size_ok = (var).size() == old_size - 1;                                            \
                bool front_ok = (var).front() == 50;                                                    \
                std::cout << "\tPop " << old_front << ": "                                              \
                          << (size_ok && front_ok ? "\033[32mOK\033[0m" : "\033[31mFAIL\033[0m")        \
                          << " (size=" << (var).size() << ", front=" << (var).front() << ")\n";         \
            } catch(...) {                                                                              \
                std::cout << "\tPop: \033[31mFAIL\033[0m\n";                                            \
            }                                                                                           \
        }                                                                                               \
                                                                                                        \
        while(!(var).empty()) {                                                                         \
            try {                                                                                       \
                (var).pop();                                                                            \
            } catch(...) {                                                                              \
                break;                                                                                  \
            }                                                                                           \
        }                                                                                               \
        bool empty_final = (var).empty() && (var).size() == 0;                                          \
        std::cout << "\tAfter pops, empty? "                                                            \
                  << (empty_final ? "\033[32myes\033[0m" : "\033[31mno\033[0m")                         \
                  << " (size=" << (var).size() << ")\n\n";                                              \
    } while(0)

int main(int argc, char** argv) {
    // How dumb, anyways:
    dumb_queue<int> dumbq;
    testq(dumbq);

    // A real one:
    real_queue<int, 256> realq;
    testq(realq);

    // Memory eater one:
    linked_queue<int> linkedq;
    testq(linkedq);

    return 0;
}
