// TODO: make two vector, one for treated, one for remaining.

#include <iostream>
#include <vector>
#include "Customer.h"
#define all(c) (c).begin(), (c).end()

using namespace std;
using namespace std::chrono;

bool comparator_score(const Customer &customer1, const Customer &customer2) {
    if (customer1.score == customer2.score) {
        return customer1.appointment < customer2.appointment;
    }
    return customer1.score < customer2.score;
}

void re_order(vector<Customer> &customers) {
    sort(customers.begin(), customers.end(), comparator_score);
}

bool comparator_arrival_time(const Customer &customer1, const Customer &customer2) {
    if (customer1.time_arrival == customer2.time_arrival) {
        return customer1.appointment < customer2.appointment;
    }
    return customer1.time_arrival <= customer2.time_arrival;
}

bool comparator_appointment(const Customer &customer1, const Customer &customer2) {
    return customer1.appointment < customer2.appointment;
}

int main() {
    vector<Customer> customers(200);

    for (int i = 0; i < customers.size(); i++) {
        customers[i].fillRandom(i, (int) customers.size());
    }

    sort(all(customers), comparator_arrival_time);


//    for (const auto &customer: customers) {
//        cout << customer << '\n';
//    }

    for (int i = 1; i < customers.size(); i++) {
//        cout << customers[i].time_arrival << ' ' << customers[i - 1].time_arrival << '\n';
        while (customers[i].time_arrival - customers[i - 1].time_arrival <= Time(0, 6, 0)) {
            int diff = 12 - abs((customers[i].time_arrival - customers[i - 1].time_arrival).inSeconds());
            diff = 12;
            customers[i].time_arrival = customers[i].time_arrival + Time(0, 4, 0);
        }
//        cout << customers[i].time_arrival << ' ' << customers[i -  1].time_arrival << "\n\n";
    }

    sort(all(customers), comparator_appointment);

    Time start_time = Time(9, 0, 0);
    Time end_time = Time(18, 0, 0);

    re_order(customers);

    Time time_stacked;


    for (Time i = start_time; i <= end_time + 60; i = i + 60) {

        time_stacked = Time(0, 0, 0);
        for (int current_customer = 0; current_customer < customers.size();) {

            if (current_customer < customers.size() && customers[current_customer].treated) {
                current_customer++;
                continue;
            }

            if (customers[current_customer].time_arrival <= i) {
                customers[current_customer].set_time(time_stacked);

                time_stacked = time_stacked + customers[current_customer].time_consulting;
                current_customer++;

            } else {

                if (customers[current_customer].score >= 2000) {
                    current_customer++;
                } else {

                    customers[current_customer].change_score();
                    re_order(customers);
                }
            }
        }

//        cout << "End of one cycle\n";

        for (auto &customer: customers) {
            if ((!customer.treated) && customer.score >= 2000) {
                customer.score = 20;
                customer.count_late = 2;
            }
        }

    }

//    for (const auto &customer: customers) {
//        cout << customer << '\n';
//    }

    cout << "\n*******************************************\n\n";
    sort(customers.begin(), customers.end(), comparator_arrival_time);


//    for (auto& customer: customers) {
//        customer.leaving_time = customer.time_arrival + customer.time_consulting;
//    }

    Time total_first_customer = customers[0].time_arrival + customers[0].time_consulting;
    customers[0].leaving_time = total_first_customer;

    for (int i = 1; i < customers.size(); i++) {
        // babu's
        if (customers[i].time_arrival <= total_first_customer) {
//            cout << "Yes : " << customers[i].time_arrival << ' ' << total_first_customer << '\n';

            customers[i].response_time = max(Time(0), total_first_customer - customers[i].time_arrival);

            customers[i].leaving_time = total_first_customer + customers[i].time_consulting;
            total_first_customer = customers[i].leaving_time;

        } else {
            customers[i].response_time = 0;
            customers[i].leaving_time = customers[i].time_arrival + customers[i].time_consulting;
            total_first_customer = customers[i].leaving_time;
        }

    }

    for (const auto &customer: customers) {
        cout << customer << '\n';
    }
}


/*
  every customer consult time: 20 min.

 10:00 --> 10:20
 10:05 --> 10:40 --> previous_leaving + consult
 10:10
 03:15 -->


 */