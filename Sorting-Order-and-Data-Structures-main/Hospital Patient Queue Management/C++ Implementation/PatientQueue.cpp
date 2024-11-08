#include "PatientQueue.h"
#include <iostream>

void PatientQueue::enqueue(const std::string& patient) {
    queue.push(patient);
    std::cout << "Patient '" << patient << "' added to the queue." << std::endl;
}

std::string PatientQueue::dequeue() {
    if (!queue.empty()) {
        std::string patient = queue.front();
        queue.pop();
        std::cout << "Patient '" << patient << "' removed from the queue." << std::endl;
        return patient;
    } else {
        std::cout << "No patients in the queue." << std::endl;
        return "";
    }
}
