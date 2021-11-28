#include <iostream>
#include "pybind11/embed.h"
#include "common.h"
namespace py = pybind11;

void writeJson(std::map<std::string, std::string> content_map, std::string file_path)
{
    py::scoped_interpreter guard{};
    py::module_ josnUtils = py::module_::import("json_utils");
    std::cout << "write json" << std::endl;
    auto content_dict = py::dict();
    for (auto item : content_map)
    {
        std::cout << item.first << ":" << item.second << std::endl;
        content_dict[py::str(item.first)] = item.second;
        // key为const类型,需要转成非const
    }
    // py::object content_dict= py::cast<>(content_map);

    // py::print(content_dict);
    // std::cout << "test" << std::endl;
    josnUtils.attr("write_json")(content_dict, file_path);
}

std::map<std::string, std::string> loadJson(std::string file_path)
{
    py::scoped_interpreter guard{};
    py::module_ josnUtils = py::module_::import("json_utils");
    py::dict content = josnUtils.attr("load_json")(file_path);
    // py::print(content);
    std::map<std::string, std::string> content_map;
    for (auto item : content)
    {
        std::string key = py::str(item.first);
        std::string value = py::str(item.second);
        content_map.insert(std::pair<std::string, std::string>(key, value));
    }
    return content_map;
}
