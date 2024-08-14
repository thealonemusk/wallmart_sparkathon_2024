#include <iostream>

class Time {
private:
    int hours;
    int minutes;
    int seconds;

public:
    Time() {
        hours = 0;
        minutes = 0;
        seconds = 0;
    }
    Time(int h, int m, int s) {
        hours = h;
        minutes = m;
        seconds = s;
    }
    Time (int seconds) {

        hours = seconds / 3600;
        int remaining_seconds = seconds % 3600;

        minutes = remaining_seconds / 60;
        remaining_seconds = remaining_seconds % 60;

        this->seconds = remaining_seconds;
    }

    // Getter methods
    int getHours() const { return hours; }

    int getMinutes() const { return minutes; }

    int getSeconds() const { return seconds; }

    // Time addition operator

    int inSeconds() const {
        return hours * 3600  + minutes * 60 + seconds;
    }

    Time operator+(const int seconds) const {
        Time result = *this;
        result.seconds += seconds;
        while (result.seconds >= 60) {
            result.seconds -= 60;
            result.minutes++;
            if (result.minutes >= 60) {
                result.minutes = 0;
                result.hours++;
            }
        }
        return result;
    }

    // Time subtraction operator
    Time operator-(const int seconds) const {
        Time result = *this;
        result.seconds -= seconds;
        while (result.seconds < 0) {
            result.seconds += 60;
            result.minutes--;
            if (result.minutes < 0) {
                result.minutes = 59;
                result.hours--;
            }
        }
        return result;
    }

    Time operator-(const Time t) const {
        return {this->inSeconds() - t.inSeconds()};
    }

    Time operator+(const Time t) const {
        return {this->inSeconds() + t.inSeconds()};
    }

        // Time comparison operators
    bool operator==(const Time &other) const {
        return (hours == other.hours && minutes == other.minutes &&
                seconds == other.seconds);
    }

    bool operator!=(const Time &other) const { return !(*this == other); }

    bool operator<(const Time &other) const {
        if (hours < other.hours) {
            return true;
        } else if (hours == other.hours && minutes < other.minutes) {
            return true;
        } else if (hours == other.hours && minutes == other.minutes &&
                   seconds < other.seconds) {
            return true;
        }
        return false;
    }

    bool operator>(const Time &other) const {
        if (hours > other.hours) {
            return true;
        } else if (hours == other.hours && minutes > other.minutes) {
            return true;
        } else if (hours == other.hours && minutes == other.minutes &&
                   seconds > other.seconds) {
            return true;
        }
        return false;
    }

    bool operator<=(const Time &other) const {
        return (*this < other) || (*this == other);
    }

    bool operator>=(const Time &other) const {
        return (*this > other) || (*this == other);
    }
};

// Overload << operator to print Time object in a user-friendly way
std::ostream &operator<<(std::ostream &os, const Time &time) {
    os << "[" << time.getHours() << ":" << time.getMinutes() << ":" << time.getSeconds() << "]";
    return os;
}

std::ostream &operator<<(std::ostream &os, const std::pair<Time, Time> &time) {
    os << "[ " << time.first << " -> " << time.second << " ]";
    return os;
}


/*
int main() {
  Time time1(10, 30, 45);
  Time time2(13, 45, 20);

  std::cout << "Time 1: " << time1 << std::endl;
  std::cout << "Time 2: " << time2 << std::endl;

  Time time3 = time1 + 3600; // Add 1 hour (3600 seconds) to time1
  std::cout << "Time 3 (time1 + 1 hour): " << time3 << std::endl;

  Time time4 = time2 - 1800; // Subtract 30 minutes (1800 seconds) from time2
}
*/
