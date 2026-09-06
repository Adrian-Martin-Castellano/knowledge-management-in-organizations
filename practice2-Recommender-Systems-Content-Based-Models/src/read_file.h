#pragma once

#include <string>
#include <set>
#include <map>

std::set<std::string> readStopWords(const std::string& filepath);
std::map<std::string, std::string> readLemmas(const std::string& filepath);