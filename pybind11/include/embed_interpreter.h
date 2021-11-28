#pragma once
#ifndef _EMBED_INTERPRETER_
#define _EMBED_INTERPRETER_
#include <map>
#include <string>
// void writeJson(std::map<std::string, std::string> content_map, std::string file_path);
// void loadJson(std::string file_path);

// void writeJson(std::map<std::string, T> content_map, std::string file_path);
template <typename T>
void writeJson(std::map<std::string, T> content_map, std::string file_path);
// void writeJson<int>(std::map<std::string, T> content_map, std::string file_path);

// void writeJson<float>(std::map<std::string, T> content_map, std::string file_path);

template <typename T>
void loadJson(std::string file_path,std::map<std::string,T> &content_map);
// void testModuel(std::string file_path);
#endif