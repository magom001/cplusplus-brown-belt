#pragma once

#include <iostream>
#include <ctime>

class Date {

public:
    using u_short = unsigned short int;
    Date() = default;

    constexpr Date(u_short year, u_short month, u_short day) : year_(year), month_(month), day_(day) {}

    time_t AsTimestamp() const;

private:
    u_short year_;
    u_short month_;
    u_short day_;
};

std::istream& operator>>(std::istream&, Date&);

int ComputeDaysDiff(const Date& date_to, const Date& date_from);

