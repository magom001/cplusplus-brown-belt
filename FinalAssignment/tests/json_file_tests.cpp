//#include <catch2/catch.hpp>
//
//#include <iostream>
//#include <fstream>
//#include "json_runner.h"
//
//using namespace std;
//
//TEST_CASE( "Program runner with json file input" ) {
//    SECTION (" failure test ") {
//        string filename = "input.json";
//        fstream fs(filename);
//        ofstream ofs;
//        ofs.open("output.json");
//
//        if (!fs.is_open()) {
//            cout << "Failed to open input.json" << endl;
//        } else {
//            Json::Start(fs, ofs);
//        }
//
//        fs.close();
//        ofs.close();
//    }
//}