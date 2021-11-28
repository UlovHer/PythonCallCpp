#include <iostream>
#include "pybind11/embed.h"
#include "embed_interpreter.h"
namespace py = pybind11;

// 将模块嵌入到C++中,不形成py文件
PYBIND11_EMBEDDED_MODULE(json_utils, m)
{
    m.doc()="json utils";
    m.def("write_json", [](py::dict content, std::string file_path)
          {
              bool status_code = false;
              try
              {
                  auto filePtr = py::module_::import("io").attr("open")(file_path, "w+");
                  py::module_::import("json").attr("dump")(content, filePtr);
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
              py::gil_scoped_release release;
              return status_code;
          });

    m.def("load_json", [](std::string file_path)
          {
              py::dict content = py::dict();
              try
              {
                  auto filePtr = py::module_::import("io").attr("open")(file_path, "r");
                  content = py::module_::import("json").attr("load")(filePtr);
                //   py::print(content);
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
              py::gil_scoped_release release;
              return content;
          });
}

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
void writeJson(std::map<std::string, T> content_map, std::string file_path)
{
     std::cout << "write begin" << std::endl;
    py::dict content_dict = mapToDict(content_map);

    py::scoped_interpreter guard{};
    py::gil_scoped_acquire acquire;
    // py::print(content_dict);
    py::module_ josn_utils = py::module_::import("json_utils");
    py::bool_ status_code = josn_utils.attr("write_json")(content_dict, file_path);
   
    if (status_code)
    {
        std::cout << "write end" << std::endl;
    }
}

template <typename T>
void loadJson(std::string file_path, std::map<std::string, T> &content_map)
{
    std::cout << "load begin" << std::endl;
    
    py::scoped_interpreter guard{};
    py::gil_scoped_acquire acquire;
    py::module_ josn_utils = py::module_::import("json_utils");
    py::dict content_dict = josn_utils.attr("load_json")(file_path);
    // py::print(content_dict);
    content_map = dictToMap<T>(content_dict);

    std::cout << "load end" << std::endl;
}

// 显示实例化模板
template void writeJson(std::map<std::string, std::string> content_map, std::string file_path);
template void loadJson(std::string file_path, std::map<std::string, std::string> &content_map);
template void writeJson(std::map<std::string, int> content_map, std::string file_path);
template void writeJson(std::map<std::string, float> content_map, std::string file_path);
