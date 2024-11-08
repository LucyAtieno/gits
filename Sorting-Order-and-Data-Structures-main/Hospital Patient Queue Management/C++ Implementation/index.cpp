#include "PatientQueue.h"
#include "EmergencyStack.h"

int main() {
    PatientQueue patientQueue;
    EmergencyStack emergencyStack;

    // Add patients
    patientQueue.enqueue("John Doe");
    patientQueue.enqueue("Jane Smith");
    emergencyStack.push("Emergency Patient A");
    emergencyStack.push("Emergency Patient B");

    // Process patients
    emergencyStack.pop();
    patientQueue.dequeue();

    return 0;
}
