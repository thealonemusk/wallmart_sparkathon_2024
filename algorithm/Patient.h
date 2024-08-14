
#include <string>
#include <iostream>


#include "Date.h"
#include "Time.h"
#include "Utility.h"

vector<int> Tribonacci{1, 3, 5, 9, 17, 31, 55, 81, 149, 274, 504, 927, 1705, 3136, 5768};

Time start_time = Time(9, 0, 0);
Time end_time = Time(18, 0, 0);

class Patient {
public:
    int age;
    int appointment;
    int score;
    int count_late;
    int time_consulting;
    int total_late;

    Time response_time;
    Time time_arrival;
    Time leaving_time;

    pair<Time, Time> expected_time;

    static int count_patients;

    bool treated;

    void set_time(Time &stacked_time) {
        this->response_time = stacked_time;
        this->treated = true;
    }

    void change_score() {
        if (count_late < Tribonacci.size()) {
            this->score += Tribonacci[this->count_late];
        }

        this->score = min(this->score, 2000);
        this->count_late += 1;
        this->total_late ++;
    }

    Patient() : time_arrival(Time(0)),
                expected_time({Time(0), Time(0)}),
                response_time(Time(0)),
                leaving_time(Time(0)) {

        this->age = 0;
        this->appointment = 0;
        this->score = 0;
        this->count_late = 0;
        this->total_late = 0;
        this->time_consulting = 0;
        this->treated = false;

    }

    Patient(const Patient &patient)
            : time_arrival(patient.time_arrival),
              expected_time(patient.expected_time),
              response_time(patient.response_time),
              leaving_time(patient.leaving_time) {

        this->age = patient.age;
        this->appointment = patient.appointment;
        this->score = patient.score;
        this->count_late = patient.count_late;
        this->total_late = patient.total_late;
        this->time_consulting = patient.time_consulting;
        this->response_time = patient.response_time;
        this->treated = patient.treated;
    }

    void fillRandom(int i, int total_size) {

        pair<Time, Time> _expected_time;

        int total_hrs = (end_time - start_time).getHours();
        for (int t = 1; t <= total_hrs; t ++ ) {
            int _t = t - 1;

            if (_t * total_size / total_hrs <= i && i < t * total_size / total_hrs) {
                Time one = Time((t - 1) * 3600) + start_time;
                Time two = Time(t * 3600) + start_time;

                _expected_time.first = one;
                _expected_time.second = two;
                break;
            }
        }

        auto _arrival_time = Time(getRandomNumber(_expected_time.first.getHours(), end_time.getHours()),
                                  getRandomNumber(0, 59), 0);

        this->appointment = ++Patient::count_patients;
        this->age = getRandomNumber(20, 75);
        this->expected_time.first = _expected_time.first;
        this->expected_time.second = _expected_time.second;
        this->time_arrival = _arrival_time;

        this->score = this->appointment;
        if (40 <= this->age && this->age <= 65) {
            this->score += 2;
        } else {
            this->score += 4;
        }

        this->time_consulting = getRandomNumber(3 * 60, 15 * 60);
    }

    Patient &operator=(const Patient &patient) = default;
};

std::ostream &operator<<(std::ostream &COUT, const Patient &patient) {
    COUT << "initial order: " << patient.appointment << ' '
         << ",score: " << patient.score << ' '
         << ",count late : " << patient.total_late << ' '
         << ",response time: " << patient.response_time << ' '
         << ",time of arrival: " << patient.time_arrival << ' '
         << ",time of leaving: " << patient.leaving_time << ' '
         << ",consult time: " << patient.time_consulting / 60 << "m " << patient.time_consulting % 60 << "s " << ' '
         << ",expected time: " << patient.expected_time << ' '
         << ",treated: " << patient.treated << ' ';

    return COUT;
}

int Patient::count_patients = 0;

