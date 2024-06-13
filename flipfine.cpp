#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <queue> // Include queue for waitlist
using namespace std;

// Forward declaration of Patient class
class Patient;

class Slot {
public:
    string date;
    int startTime;
    int endTime;
    Slot(int startTime, int endTime) : startTime(startTime), endTime(endTime) {}
    ~Slot() {}
};

class Appointment {
public:
    string patientName;
    string doctorName;
    Slot* slotBooked;
    Appointment(string patientName, string doctorName, Slot* slotBooked) : patientName(patientName), doctorName(doctorName), slotBooked(slotBooked) {}
    ~Appointment() {}
};

class Doctor {
public:
    string name;
    int id;
    string speciality;
    vector<Appointment*> bookedAppointments;
    vector<Slot*> availableSlots;
    queue<Patient*> waitlist; // Waitlist for patients
    Doctor(string name, int id, string speciality) : name(name), id(id), speciality(speciality) {}
    ~Doctor() {
        for (auto slot : availableSlots)
            delete slot;
        for (auto appointment : bookedAppointments)
            delete appointment;
    }
};

class Patient {
public:
    string name;
    int id;
    vector<Appointment*> bookedAppointments;
    Patient(string name, int id) : name(name), id(id) {}
    ~Patient() {
        for (auto appointment : bookedAppointments)
            delete appointment;
    }
};

class DoctorController {
public:
    unordered_map<string, Doctor*> doctors;
    ~DoctorController() {
        for (auto& pair : doctors)
            delete pair.second;
    }

    void AddDoctor(string name, int id, string speciality) {
        Doctor* doctor = new Doctor(name, id, speciality);
        doctors[name] = doctor;
        cout<<"Doctor Added: "<<name<<"\n";
    }

    void AddSlot(string doctorName, int startTime, int endTime) {
        if (endTime - startTime != 30 && endTime - startTime != 70) {
            cout << "Slot duration should be 30 or 70 minutes\n";
            return;
        }

        Doctor* doctor = doctors[doctorName];
        for (auto existingSlot : doctor->availableSlots) {
            if (existingSlot->startTime == startTime && existingSlot->endTime == endTime) {
                cout << "Slot already exists\n";
                return;
            }
        }
        Slot* slot = new Slot(startTime, endTime);
        doctor->availableSlots.push_back(slot);
        cout<<"Slot Added for Doctor: "<<doctorName<<"\n";
    }
};

class PatientController {
public:
    unordered_map<string, Patient*> patients;
    DoctorController* doctorController;

    PatientController(DoctorController* doctorController) : doctorController(doctorController) {}
    ~PatientController() {
        for (auto& pair : patients)
            delete pair.second;
    }

    void AddPatient(string name, int id) {
        Patient* patient = new Patient(name, id);
        patients[name] = patient;
        cout<<"Patient Added: "<<name<<"\n";
    }

    void BookAppointment(string patientName, string doctorName, int startTime, int endTime) {
        if (endTime - startTime != 30 && endTime - startTime != 70) {
            cout << "Appointment duration should be 30 or 70 minutes\n";
            return;
        }

        Patient* patient = patients[patientName];
        Doctor* doctor = doctorController->doctors[doctorName];
        Slot* slot = nullptr;

        for (auto availableSlot : doctor->availableSlots) {
            if (availableSlot->startTime == startTime && availableSlot->endTime == endTime) {
                slot = availableSlot;
                break;
            }
        }

        if (slot != nullptr) {
            Appointment* appointment = new Appointment(patientName, doctorName, slot);
            doctor->bookedAppointments.push_back(appointment);
            patient->bookedAppointments.push_back(appointment);
            doctor->availableSlots.erase(remove(doctor->availableSlots.begin(), doctor->availableSlots.end(), slot), doctor->availableSlots.end());
            cout << "Appointment booked "<<doctor->name<<" for Patient "<<patient->name<<"\n";
        } else {
            // Add patient to waitlist if slot not available
            doctor->waitlist.push(patient);
            cout << "Added to waitlist for "<<doctorName<<"\n";
        }
    }

    void CancelAppointment(string patientName, string doctorName, int startTime, int endTime) {
        Patient* patient = patients[patientName];
        Doctor* doctor = doctorController->doctors[doctorName];
        Slot* slotToRemove = nullptr;

        for (int i = 0; i < doctor->bookedAppointments.size(); i++) {
            if (doctor->bookedAppointments[i]->slotBooked->startTime == startTime && doctor->bookedAppointments[i]->slotBooked->endTime == endTime) {
                slotToRemove = doctor->bookedAppointments[i]->slotBooked;
                doctor->bookedAppointments.erase(doctor->bookedAppointments.begin() + i);
                doctor->availableSlots.push_back(slotToRemove);
                break;
            }
        }

        if (slotToRemove == nullptr) {
            cout <<"Appointment not found\n";
            return;
        }

        // Check and assign appointments from waitlist
        if (!doctor->waitlist.empty()) {
            Patient* nextPatient = doctor->waitlist.front();
            doctor->waitlist.pop();
            BookAppointment(nextPatient->name, doctorName, startTime, endTime);
            cout<<"Appointment booked for Patient from waitlist: "<<nextPatient->name<<" with Doctor "<<doctorName<<"\n";
        }

        for (int i = 0; i < patient->bookedAppointments.size(); i++) {
            if (patient->bookedAppointments[i]->slotBooked->startTime == startTime && patient->bookedAppointments[i]->slotBooked->endTime == endTime) {
                delete patient->bookedAppointments[i];
                patient->bookedAppointments.erase(patient->bookedAppointments.begin() + i);
                break;
            }
        }
        cout<<"Cancelled appointment for Patient:"<<patientName<<" with Doctor "<<doctorName<<"\n";
    }

    void GetAppointments(string patientName) {
        Patient* patient = patients[patientName];
        cout<<endl;
        cout << "Appointments for " << patientName<<":" << endl;
        for (auto appointment : patient->bookedAppointments) {
            cout << "Doctor Name: " << appointment->doctorName << endl;
            cout << "Start Time: " << appointment->slotBooked->startTime << endl;
            cout << "End Time: " << appointment->slotBooked->endTime << endl;
            cout << endl;
        }
    }
};

class Search{
public:
    virtual void search() = 0;
    virtual ~Search() {}
};

class SearchBySpecialityStratergy : public Search {
    DoctorController* doctorController;
    string speciality;

public:
    SearchBySpecialityStratergy(DoctorController* doctorController, string speciality) : doctorController(doctorController), speciality(speciality) {}
    void search() override {
        cout << "Doctors with Speciality: " << speciality << endl;
        for (auto doctor : doctorController->doctors) {
            if (doctor.second->speciality == speciality) {
                Doctor* doc = doctor.second;
                vector<Slot*> slots = doc->availableSlots;
                sort(slots.begin(), slots.end(), [](Slot* a, Slot* b) {
                    return a->startTime < b->startTime;
                });
                for (auto slot : slots) {
                    cout << "Doctor: " << doc->name << " Slot: " << slot->startTime << " - " << slot->endTime << endl;
                }
            }
        }
    }
};

class FlipFineService {
public:
    DoctorController* doctorController;
    PatientController* patientController;
    unordered_map<Doctor*, int> DoctorAppointmentCount;

    FlipFineService() {
        doctorController = new DoctorController();
        patientController = new PatientController(doctorController);
    }

    ~FlipFineService() {
        delete doctorController;
        delete patientController;
    }

    void registerDoctor(string name, int id, string speciality) {
        doctorController->AddDoctor(name, id, speciality);
    }

    void registerPatient(string name, int id) {
        patientController->AddPatient(name, id);
    }

    void markDoctorAvailability(string doctorName, int startTime, int endTime) {
        doctorController->AddSlot(doctorName, startTime, endTime);
    }

    void getPatientAppointments(string patientName) {
        patientController->GetAppointments(patientName);
    }

    void bookAppointment(string patientName, string doctorName, int startTime, int endTime) {
        patientController->BookAppointment(patientName, doctorName, startTime, endTime);
        Doctor* doctor = doctorController->doctors[doctorName];
        DoctorAppointmentCount[doctor]++;
    }

    void cancelAppointment(string patientName, string doctorName, int startTime, int endTime) {
        patientController->CancelAppointment(patientName, doctorName, startTime, endTime);
        Doctor* doctor = doctorController->doctors[doctorName];
        DoctorAppointmentCount[doctor]--;
    }

    void searchDoctorBySpeciality(string speciality) {
        Search* searchDoctorBySpeciality = new SearchBySpecialityStratergy(doctorController, speciality);
        searchDoctorBySpeciality->search();
    }

    void trendingDoctors() {
        int maxcount = 0;
        Doctor* trendingDoctors = nullptr;
        for (auto docAppointCnt : DoctorAppointmentCount) {
            if (maxcount < docAppointCnt.second) {
                maxcount = docAppointCnt.second;
                trendingDoctors = docAppointCnt.first;
            }
        }
        cout << "Trending Doctor : " << trendingDoctors->name << " with Appointments: " << maxcount << endl;
    }
};

int main() {
    FlipFineService* flipFineService = new FlipFineService();
    flipFineService->registerDoctor("Dr. A", 1, "Dermatologist");
    flipFineService->registerDoctor("Dr. B", 2, "Cardiologist");
    flipFineService->markDoctorAvailability("Dr. A", 1030, 1100);
    flipFineService->markDoctorAvailability("Dr. A", 1130, 1200);
    flipFineService->markDoctorAvailability("Dr. B", 1230, 1300);
    flipFineService->markDoctorAvailability("Dr. B", 1300, 1330);
    flipFineService->markDoctorAvailability("Dr. A", 1430, 1500);
    flipFineService->markDoctorAvailability("Dr. B", 1400, 1430);
    flipFineService->markDoctorAvailability("Dr. B", 1500, 1530);

    flipFineService->registerPatient("P3", 3);
    flipFineService->registerPatient("P1", 1);
    flipFineService->registerPatient("P2", 2);
    flipFineService->bookAppointment("P1", "Dr. A", 1030, 1100);
    flipFineService->bookAppointment("P2", "Dr. B", 1230, 1300);
    flipFineService->bookAppointment("P3", "Dr. A", 1130, 1200);
    flipFineService->bookAppointment("P1", "Dr. B", 1300, 1330);
    flipFineService->bookAppointment("P1", "Dr. A", 1130, 1200);
    flipFineService->searchDoctorBySpeciality("Dermatologist");
    flipFineService->searchDoctorBySpeciality("Cardiologist");
    flipFineService->trendingDoctors();
    flipFineService->getPatientAppointments("P1");
    flipFineService->getPatientAppointments("P2");
    flipFineService->getPatientAppointments("P3");
    flipFineService->cancelAppointment("P1", "Dr. A", 1030, 1100);
    flipFineService->getPatientAppointments("P1");

    delete flipFineService; // Freeing the allocated memory

    return 0;
}
