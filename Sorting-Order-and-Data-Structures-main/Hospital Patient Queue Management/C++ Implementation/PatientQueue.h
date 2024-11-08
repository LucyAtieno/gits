#ifndef PATIENTQUEUE_H
#define PATIENTQUEUE_H

#include <queue>
#include <string>

class PatientQueue {
public:
    void enqueue(const std::string& patient);
    std::string dequeue();

private:
    std::queue<std::string> queue;
};

#endif // PATIENTQUEUE_H
