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
    const static string SPEND;
};

const string OP_CODES::EARN = "Earn";
const string OP_CODES::PAY_TAX = "PayTax";
const string OP_CODES::COMPUTE_INCOME = "ComputeIncome";
const string OP_CODES::SPEND = "Spend";

pair<size_t, size_t> GetRange(const Date &from, const Date &to) {
    const auto from_day = ComputeDaysDiff(from, FIRST_DAY_OF_THE_CENTURY);
    const auto days_diff = ComputeDaysDiff(to, from) + 1;

    return {from_day, from_day + days_diff};
}

Budget::Budget()
        : income_per_day_(DAYS_IN_21ST_CENTURY),
          expense_per_day_(DAYS_IN_21ST_CENTURY) {}

void Budget::ProcessRequests(std::istream &is, std::ostream &os) {
    os.setf(ios_base::fixed);
    size_t op_count;
    string op_code;

    uint64_t tax_rate;
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
            is >> tax_rate;
            PayTax(from, to, tax_rate * 1.0 /100.0);
        } else if (op_code == OP_CODES::COMPUTE_INCOME) {
            is >> from;
            is >> to;
            os << ComputeIncome(from, to) << "\n";
        } else if (op_code == OP_CODES::SPEND) {
            is >> from;
            is >> to;
            is >> amount;
            Spend(from, to, amount);
        }
    }
}

void Budget::Earn(const Date &from, const Date &to, Budget::Income amount) {
    const auto[from_, to_] = GetRange(from, to);

    for (auto i = from_; i < to_; ++i) {
        income_per_day_[i] += (amount / (to_ - from_));
    }
}

void Budget::PayTax(const Date &from, const Date &to) {
    const auto[from_, to_] = GetRange(from, to);
    for (auto i = from_; i < to_; ++i) {
        income_per_day_[i] = income_per_day_[i] * (1.0 - TAX_RATE);
    }
}

Budget::Income Budget::ComputeIncome(const Date &from, const Date &to) {
    auto[from_, to_] = GetRange(from, to);

    auto income = accumulate(income_per_day_.begin() + from_, income_per_day_.begin() + to_, 0.0);
    auto expense = accumulate(expense_per_day_.begin() + from_, expense_per_day_.begin() + to_, 0.0);

    return income - expense;
}

void Budget::PayTax(const Date &from, const Date &to, double tax_rate) {
    const auto[from_, to_] = GetRange(from, to);
    for (auto i = from_; i < to_; ++i) {
        income_per_day_[i] = income_per_day_[i] * (1.0 - tax_rate);
    }
}

void Budget::Spend(const Date &from, const Date &to, Budget::Income amount) {
    const auto[from_, to_] = GetRange(from, to);

    for (auto i = from_; i < to_; ++i) {
        expense_per_day_[i] += (amount / (to_ - from_));
    }
}
