//
// Created by Arkady Magomedov on 2019-01-12.
//

#include "date.h"


time_t Date::AsTimestamp() const {
    std::tm t{
            .tm_sec  = 0,
            .tm_min  = 0,
            .tm_hour = 0,
            .tm_mday = day_,
            .tm_mon  = month_ - 1,
            .tm_year = year_ - 1900,
            .tm_isdst = 0,
    };
    return mktime(&t);
}

int ComputeDaysDiff(const Date &date_to, const Date &date_from)  {
    const time_t timestamp_to = date_to.AsTimestamp();
    const time_t timestamp_from = date_from.AsTimestamp();
    static const int SECONDS_IN_DAY = 60 * 60 * 24;
    return (timestamp_to - timestamp_from) / SECONDS_IN_DAY;
}

std::istream &operator>>(std::istream &is, Date &date) {
    unsigned short int year, month, day;

    is >> year;
    is.ignore(1);
    is >> month;
    is.ignore(1);
    is >> day;

    date = {year, month, day};

    return is;
}
