// TODO: make two vector, one for treated, one for remaining.

#include <iostream>
#include <vector>
#include "Patient.h"
#define all(c) (c).begin(), (c).end()

using namespace std;
using namespace std::chrono;

bool comparator_score(const Patient &patient1, const Patient &patient2) {
    if (patient1.score == patient2.score) {
        return patient1.appointment < patient2.appointment;
    }
    return patient1.score < patient2.score;
}

void re_order(vector<Patient> &patients) {
    sort(patients.begin(), patients.end(), comparator_score);
}

bool comparator_arrival_time(const Patient &patient1, const Patient &patient2) {
    if (patient1.time_arrival == patient2.time_arrival) {
        return patient1.appointment < patient2.appointment;
    }
    return patient1.time_arrival <= patient2.time_arrival;
}

bool comparator_appointment(const Patient &patient1, const Patient &patient2) {
    return patient1.appointment < patient2.appointment;
}

int main() {
    vector<Patient> patients(200);

    for (int i = 0; i < patients.size(); i++) {
        patients[i].fillRandom(i, (int) patients.size());
    }

    sort(all(patients), comparator_arrival_time);


//    for (const auto &patient: patients) {
//        cout << patient << '\n';
//    }

    for (int i = 1; i < patients.size(); i++) {
//        cout << patients[i].time_arrival << ' ' << patients[i - 1].time_arrival << '\n';
        while (patients[i].time_arrival - patients[i - 1].time_arrival <= Time(0, 6, 0)) {
            int diff = 12 - abs((patients[i].time_arrival - patients[i - 1].time_arrival).inSeconds());
            diff = 12;
            patients[i].time_arrival = patients[i].time_arrival + Time(0, 4, 0);
        }
//        cout << patients[i].time_arrival << ' ' << patients[i -  1].time_arrival << "\n\n";
    }

    sort(all(patients), comparator_appointment);

    Time start_time = Time(9, 0, 0);
    Time end_time = Time(18, 0, 0);

    re_order(patients);

    Time time_stacked;


    for (Time i = start_time; i <= end_time + 60; i = i + 60) {

        time_stacked = Time(0, 0, 0);
        for (int current_patient = 0; current_patient < patients.size();) {

            if (current_patient < patients.size() && patients[current_patient].treated) {
                current_patient++;
                continue;
            }

            if (patients[current_patient].time_arrival <= i) {
                patients[current_patient].set_time(time_stacked);

                time_stacked = time_stacked + patients[current_patient].time_consulting;
                current_patient++;

            } else {

                if (patients[current_patient].score >= 2000) {
                    current_patient++;
                } else {

                    patients[current_patient].change_score();
                    re_order(patients);
                }
            }
        }

//        cout << "End of one cycle\n";

        for (auto &patient: patients) {
            if ((!patient.treated) && patient.score >= 2000) {
                patient.score = 20;
                patient.count_late = 2;
            }
        }

    }

//    for (const auto &patient: patients) {
//        cout << patient << '\n';
//    }

    cout << "\n*******************************************\n\n";
    sort(patients.begin(), patients.end(), comparator_arrival_time);


//    for (auto& patient: patients) {
//        patient.leaving_time = patient.time_arrival + patient.time_consulting;
//    }

    Time total_first_patient = patients[0].time_arrival + patients[0].time_consulting;
    patients[0].leaving_time = total_first_patient;

    for (int i = 1; i < patients.size(); i++) {
        // babu's
        if (patients[i].time_arrival <= total_first_patient) {
//            cout << "Yes : " << patients[i].time_arrival << ' ' << total_first_patient << '\n';

            patients[i].response_time = max(Time(0), total_first_patient - patients[i].time_arrival);

            patients[i].leaving_time = total_first_patient + patients[i].time_consulting;
            total_first_patient = patients[i].leaving_time;

        } else {
            patients[i].response_time = 0;
            patients[i].leaving_time = patients[i].time_arrival + patients[i].time_consulting;
            total_first_patient = patients[i].leaving_time;
        }

    }

    for (const auto &patient: patients) {
        cout << patient << '\n';
    }
}


/*
  every patient consult time: 20 min.

 10:00 --> 10:20
 10:05 --> 10:40 --> previous_leaving + consult
 10:10
 03:15 -->


 */