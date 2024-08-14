#include <iostream>

class Date {
private:
  int year;
  int month;
  int day;

public:
  Date(int y, int m, int d) {
    year = y;
    month = m;
    day = d;
  }

  // Getter methods
  int getYear() const { return year; }

  int getMonth() const { return month; }

  int getDay() const { return day; }

  // Date addition operator
  Date operator+(const int days) const {
    Date result = *this;
    result.day += days;
    while (result.day > daysInMonth(result.year, result.month)) {
      result.day -= daysInMonth(result.year, result.month);
      result.month++;
      if (result.month > 12) {
        result.month = 1;
        result.year++;
      }
    }
    return result;
  }

  // Date subtraction operator
  Date operator-(const int days) const {
    Date result = *this;
    result.day -= days;
    while (result.day < 1) {
      result.month--;
      if (result.month < 1) {
        result.month = 12;
        result.year--;
      }
      result.day += daysInMonth(result.year, result.month);
    }
    return result;
  }

  // Date comparison operators
  bool operator==(const Date &other) const {
    return (year == other.year && month == other.month && day == other.day);
  }

  bool operator!=(const Date &other) const { return !(*this == other); }

  bool operator<(const Date &other) const {
    if (year < other.year) {
      return true;
    } else if (year == other.year && month < other.month) {
      return true;
    } else if (year == other.year && month == other.month && day < other.day) {
      return true;
    }
    return false;
  }

  bool operator>(const Date &other) const {
    if (year > other.year) {
      return true;
    } else if (year == other.year && month > other.month) {
      return true;
    } else if (year == other.year && month == other.month && day > other.day) {
      return true;
    }
    return false;
  }

  bool operator<=(const Date &other) const {
    return (*this < other) || (*this == other);
  }

  bool operator>=(const Date &other) const {
    return (*this > other) || (*this == other);
  }

  // Helper method to get number of days in a given month
  static int daysInMonth(int year, int month) {
    if (month == 2) {
      if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) {
        return 29;
      }
      return 28;
    } else if (month == 4 || month == 6 || month == 9 || month == 11) {
      return 30;
    } else {
      return 31;
    }
  }
};

// Overload << operator to print Date object in a user-friendly way
std::ostream &operator<<(std::ostream &os, const Date &date) {
  os << date.getYear() << "-" << date.getMonth() << "-" << date.getDay();
  return os;
}
