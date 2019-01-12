//
// Created by Arkady Magomedov on 2019-01-12.
//

#include "budget.h"
#include <numeric>
#include <iterator>
#include <utility>
#include <string>

using namespace std;

constexpr static size_t DAYS_IN_21ST_CENTURY = 36525;
constexpr static Date FIRST_DAY_OF_THE_CENTURY = Date(2000, 1, 1);
const double TAX_RATE = 0.13;

struct OP_CODES {
    const static string EARN;
    const static string PAY_TAX;
    const static string COMPUTE_INCOME;
};

const string OP_CODES::EARN = "Earn";
const string OP_CODES::PAY_TAX = "PayTax";
const string OP_CODES::COMPUTE_INCOME = "ComputeIncome";

pair<size_t, size_t> GetRange(const Date &from , const Date& to) {
    const auto from_day = ComputeDaysDiff(from, FIRST_DAY_OF_THE_CENTURY);
    const auto days_diff = ComputeDaysDiff(to, from) + 1;

    return {from_day, from_day + days_diff};
}

Budget::Budget(): income_per_day_(DAYS_IN_21ST_CENTURY) {}

void Budget::ProcessRequests(std::istream &is, std::ostream &os) {
    os.setf(ios_base::fixed);
    size_t op_count;
    string op_code;

    Income amount;
    Date from;
    Date to;

    is >> op_count;

    for (auto i = 0; i < op_count; ++i) {
        is >> op_code;

        if (op_code == OP_CODES::EARN) {
            is >> from;
            is >> to;
            is >> amount;
            Earn(from, to, amount);
        } else if (op_code == OP_CODES::PAY_TAX) {
            is >> from;
            is >> to;
            PayTax(from ,to);
        } else if (op_code == OP_CODES::COMPUTE_INCOME) {
            is >> from;
            is >> to;
            os << ComputeIncome(from, to) << "\n";
        }
    }
}

void Budget::Earn(const Date &from, const Date &to, Budget::Income amount) {
    const auto [from_, to_] = GetRange(from, to);

    for (auto i = from_; i < to_; ++i) {
        income_per_day_[i] += (amount / (to_ - from_));
    }
}

void Budget::PayTax(const Date &from, const Date &to) {
    const auto [from_, to_] = GetRange(from, to);
    for (auto i = from_; i < to_; ++i) {
        income_per_day_[i] = income_per_day_[i] * (1.0 - TAX_RATE);
    }
}

Budget::Income Budget::ComputeIncome(const Date &from, const Date &to) {
    auto [from_, to_] = GetRange(from, to);

    return accumulate(income_per_day_.begin() + from_, income_per_day_.begin() + to_, 0.0);
}
