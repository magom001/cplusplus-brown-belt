#pragma once

#include <vector>
#include <iostream>
#include "date.h"

class Budget {
using Income = double;
public:
    Budget();
    void ProcessRequests(std::istream&, std::ostream&);
    void Earn(const Date& from, const Date& to, Income amount);
    void PayTax(const Date& from, const Date& to);
    Income ComputeIncome(const Date& from, const Date& to);
private:
    std::vector<Income> income_per_day_;
};