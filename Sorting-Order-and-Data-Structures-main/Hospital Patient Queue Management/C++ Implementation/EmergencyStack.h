#ifndef EMERGENCYSTACK_H
#define EMERGENCYSTACK_H

#include <stack>
#include <string>

class EmergencyStack {
public:
    void push(const std::string& patient);
    std::string pop();

private:
    std::stack<std::string> stack;
};

#endif // EMERGENCYSTACK_H
