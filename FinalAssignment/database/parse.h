#pragma once

#include <string_view>
#include <sstream>
#include <vector>


std::string_view Strip(std::string_view s);
std::vector<std::string_view> SplitBy(std::string_view s, char sep);