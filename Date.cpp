// Final Project Milestone 1
//
// Version 1.0
// Date: Thursday, May 24th, 2018
// Author: Alan Vuong
// Seneca E-mail: avuong19@myseneca.ca
// Student Number: 149004178
// Description
//
//
//
//
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
/////////////////////////////////////////////////////////////////
#include "Date.h"
#include <iomanip>

namespace AMA {

  // number of days in month mon_ and year year_
  //
  int Date::mdays(int mon, int year)const {
    int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
    int month = mon >= 1 && mon <= 12 ? mon : 13;
    month--;
    return days[month] + int((month == 1)*((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
  }

  void Date::errCode(int num) {
    errState = num;
  }

  Date::Date() {
    year = 0;
    month = 0;
    day = 0;
    cmp = 0;
    errState = NO_ERROR;
  }

  Date::Date(int yr, int mn, int dy) {
    *this = Date();

    // Validate year
    if (!(yr >= min_year && yr <= max_year)) {
      errCode(YEAR_ERROR);
    }

    // Validate month
    if (!(errState || (mn >= 1 && mn <= 12))) {
      errCode(MON_ERROR);
    }

    // Validate day
    if (!(errState || dy <= mdays(mn, yr))) {
      errCode(DAY_ERROR);
    }

    // Set values if no errors
    if (!errState) {
      year = yr;
      month = mn;
      day = dy;
      cmp = year * 372 + month * 13 + day;
    }
  }

  bool Date::operator==(const Date& rhs) const {
    return (year && rhs.year && cmp == rhs.cmp);
  }

  bool Date::operator!=(const Date& rhs) const {
    return (year && rhs.year && cmp != rhs.cmp);
  }

  bool Date::operator<(const Date& rhs) const {
    return (year && rhs.year && cmp < rhs.cmp);
  }

  bool Date::operator>(const Date& rhs) const {
    return (year && rhs.year && cmp > rhs.cmp);
  }

  bool Date::operator<=(const Date& rhs) const {
    return (year && rhs.year && cmp <= rhs.cmp);
  }

  bool Date::operator>=(const Date& rhs) const {
    return (year && rhs.year && cmp >= rhs.cmp);
  }

  int Date::errCode() const {
    return errState;
  }

  bool Date::bad() const {
    return errState;
  }

  std::istream& Date::read(std::istream& istr) {
    char ch;
    int yr;
    int mn;
    int dy;

    istr.clear();
    istr >> yr >> ch >> mn >> ch >> dy;

    if (istr.fail()) {
      errCode(CIN_FAILED);
    }
    else {
      Date temp(yr, mn, dy);
      if (year == 0 || (temp.cmp != 0 && temp.cmp != cmp)) {
        *this = temp;
      }
    }
    return istr; // None of the changes here are actually being saved into class object
  }

  std::ostream& Date::write(std::ostream& ostr) const {
    return ostr << setw(1) << setfill('0') << year << "/" << setw(2) << month << "/" << setw(2) << day;
  }

  ostream& operator<<(ostream& ostr, const Date d) {
    return d.write(ostr);
  }
  istream& operator>>(istream& istr, Date& d) {
    return d.read(istr);
  }
}
