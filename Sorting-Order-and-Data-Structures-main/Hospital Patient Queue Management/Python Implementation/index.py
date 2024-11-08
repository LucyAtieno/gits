class PatientQueue:
    def __init__(self):
        self.queue = []

    def enqueue(self, patient):
        """Add a patient to the end of the queue."""
        self.queue.append(patient)
        print(f"Patient '{patient}' added to the queue.")

    def dequeue(self):
        """Remove and return the patient at the front of the queue."""
        if self.queue:
            patient = self.queue.pop(0)
            print(f"Patient '{patient}' removed from the queue.")
            return patient
        else:
            print("No patients in the queue.")
            return None

class EmergencyStack:
    def __init__(self):
        self.stack = []

    def push(self, patient):
        """Add an emergency patient to the top of the stack."""
        self.stack.append(patient)
        print(f"Emergency patient '{patient}' added to the stack.")

    def pop(self):
        """Remove and return the patient at the top of the stack."""
        if self.stack:
            patient = self.stack.pop()
            print(f"Emergency patient '{patient}' removed from the stack.")
            return patient
        else:
            print("No emergency patients in the stack.")
            return None


#Example of its usage
# Create instances
patient_queue = PatientQueue()
emergency_stack = EmergencyStack()

# Add patients
patient_queue.enqueue("John Doe")
patient_queue.enqueue("Jane Smith")
emergency_stack.push("Emergency Patient A")
emergency_stack.push("Emergency Patient B")

# Process patients
emergency_stack.pop()
patient_queue.dequeue()
