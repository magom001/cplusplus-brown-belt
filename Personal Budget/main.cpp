#include <iostream>

#include "budget.h"

using namespace std;

int main() {
    Budget budget;
    
    budget.ProcessRequests(cin, cout);
    
    return 0;
}