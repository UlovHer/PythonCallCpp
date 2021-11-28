#include <iostream>
#include "embed_interpreter.h"

int main(int, char **)
{
    std::cout << "Hello, world!\n";
    std::map<std::string, std::string> content;
    content.insert(std::pair<std::string, std::string>("project_name", "Test"));
    content.insert(std::pair<std::string, std::string>("pybind_version", "11"));
    std::string file_path = "./test.json";

    // std::map<std::string, std::string> result;
    // loadJson(file_path,result);

    std::cout << "test embed interpreter" << std::endl;
    // writeJson(content, file_path);
    std::cout << "write json string into file successed" << std::endl;

    std::map<std::string, std::string> result;
    loadJson(file_path,result);
    std::cout << "load json string from file finished" << std::endl;
    for (auto item : result)
    {
        std::cout << item.first << ":" << item.second << std::endl;
    }
    system("pause");
}
