#pragma once

#include <vector>
#include <iostream>
#include "date.h"

class Budget {
using Income = double;
using Expense = double;
public:
    Budget();
    void ProcessRequests(std::istream&, std::ostream&);
    void Earn(const Date& from, const Date& to, Income amount);
    void Spend(const Date& from, const Date& to, Income amount);
    void PayTax(const Date& from, const Date& to);
    void PayTax(const Date& from, const Date& to, double tax_rate);
    Income ComputeIncome(const Date& from, const Date& to);
private:
    std::vector<Income> income_per_day_;
    std::vector<Expense> expense_per_day_;
};