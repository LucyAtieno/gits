#include "EmergencyStack.h"
#include <iostream>

void EmergencyStack::push(const std::string& patient) {
    stack.push(patient);
    std::cout << "Emergency patient '" << patient << "' added to the stack." << std::endl;
}

std::string EmergencyStack::pop() {
    if (!stack.empty()) {
        std::string patient = stack.top();
        stack.pop();
        std::cout << "Emergency patient '" << patient << "' removed from the stack." << std::endl;
        return patient;
    } else {
        std::cout << "No emergency patients in the stack." << std::endl;
        return "";
    }
}
