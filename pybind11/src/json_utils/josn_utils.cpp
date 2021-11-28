#include <iostream>
#include "pybind11/embed.h"
#include "json_utils.h"

namespace py = pybind11;
using namespace py::literals;
template <typename T>
py::dict mapToDict(std::map<std::string, T> content_map)
{
    py::dict content_dict = py::dict();
    for (auto item : content_map)
    {
        // std::cout << item.first << ":" << item.second << std::endl;
        content_dict[py::str(item.first)] = item.second;
        // key为const类型,需要转成非const
    }
    return content_dict;
}

template <typename T>
std::map<std::string, T> dictToMap(py::dict content_dict)
{
    std::map<std::string, T> content_map;
    for (auto item : content_dict)
    {
        std::string key = py::str(item.first);
        T value = py::str(item.second);

        content_map.insert(std::pair<std::string, T>(key, value));
    }
    return content_map;
}

template <typename T>
bool writeJson(std::map<std::string, T> content_map, std::string file_path)
{
    py::scoped_interpreter guard{};
    py::dict content = mapToDict(content_map);
    bool status_code = false;
    try
    {   
        // 使用**kwargs 
        auto open_kwargs = py::dict("encoding"_a = "utf-8");
        auto filePtr = py::module_::import("io").attr("open")(file_path, "w+", **open_kwargs);
        auto dump_kwargs = py::dict("indent"_a = 4);
        py::module_::import("json").attr("dump")(content, filePtr, **dump_kwargs);
        status_code = true;
        filePtr.attr("close");
    }
    catch (py::error_already_set &e)
    {
        if (e.matches(PyExc_FileNotFoundError))
        {
            py::print("file not found");
        }
        else
        {
            throw;
        }
    }
    return status_code;
}

std::map<std::string, std::string> loadJson(std::string file_path)
{
    py::scoped_interpreter guard{};
    py::dict content = py::dict();
    try
    {
        auto filePtr = py::module_::import("io").attr("open")(file_path, "r");
        content = py::module_::import("json").attr("load")(filePtr);
        filePtr.attr("close");
    }
    catch (py::error_already_set &e)
    {
        if (e.matches(PyExc_FileNotFoundError))
        {
            py::print("file not found");
        }
        else if (e.matches(PyExc_PermissionError))
        {
            py::print("file found but not accessible");
        }
        else
        {
            throw;
        }
    }
    std::map<std::string, std::string> content_map = dictToMap<std::string>(content);
    return content_map;
}

template bool writeJson(std::map<std::string, std::string> content_map, std::string file_path);