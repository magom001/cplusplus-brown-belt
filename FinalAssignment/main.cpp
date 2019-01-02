#include <iostream>
#include "json_runner.h"
#include "graph.h"
#include "router.h"

using namespace std;
using namespace Graph;

int main() {
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    Json::Start(cin, cout);

    return 0;
}