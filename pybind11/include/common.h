#pragma once
#ifndef _COMMON_H_
#define _COMMON_H_
#include <vector>
#include <queue>
#include <map>
#include <string>
#include <iostream>
// int add(int i, int j);
// bool isPalindrome(const std::string s);
// std::vector<int> maxSlidingWindow(std::vector<int> &nums, int k);
extern void writeJson(std::map<std::string, std::string> content_map, std::string file_path);
extern std::map<std::string, std::string> loadJson(std::string file_path);
#endif