#pragma once
#ifndef _JOSN_UTILS_
#define _JOSN_UTILS_
#include <map>
#include <string>
// void writeJson(std::map<std::string, std::string> content_map, std::string file_path);
// void loadJson(std::string file_path);

template <typename T>
bool writeJson(std::map<std::string, T> content_map, std::string file_path);
std::map<std::string, std::string> loadJson(std::string file_path);
#endif