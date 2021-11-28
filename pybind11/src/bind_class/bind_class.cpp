#include <String>
#include "pybind11/pybind11.h"

class Animal
{
public:
    virtual ~Animal()
    {
    }
    virtual std::string go(int n_times) = 0;
};

class Dog : public Animal
{
public:
    std::string go(int n_times) override
    {
        std::string result;
        for (int i = 0; i < n_times; i++)
        {
            result = "wooof!";
        }
        return result;
    }
};

std::string call_go(Animal *animal)
{
    return animal->go(3);
}

namespace py = pybind11;
// PYBIND11_MODULE(bind_class, m)
// {
//     py::class_<Animal>(m, "animal").def("go", &Animal::go);
//     py::class_<Dog, Animal>(m, "Dog").def(py::init<>());
//     m.def("call_go", &call_go);
// }

/*
这种绑定是不能扩展的：Animal是只能使用Dog构造，
*/

class PyAnimal : public Animal
{
public:
    using Animal::Animal;
    std::string go(int n_times) override
    {
        PYBIND11_OVERRIDE_PURE(
            std::string,
            Animal,
            go,
            n_times);
    }
};

PYBIND11_MODULE(bind_class, m)
{
    // py::class_<Animal,PyAnimal>(m, "Animal").def(py::init<>()).def("go", &Animal::go);
    
    py::class_<Animal, PyAnimal>(m, "Animal")
        .def(py::init<>())
        .def("go", &Animal::go);
        // 绑定需要针对实际类,而不是中间类
    py::class_<Dog, Animal>(m, "Dog").def(py::init<>());
    m.def("call_go", &call_go);
}
