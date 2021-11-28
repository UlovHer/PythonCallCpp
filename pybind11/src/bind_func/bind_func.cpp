#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include "pybind11/pybind11.h"
#include "pybind11/stl.h"

namespace py = pybind11;

std::string vowelOrConsonant(char &c)
{
    int isLowercaseVowel, isUppercaseVowel;
    // 小写字母元音
    isLowercaseVowel = (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');

    // 大写字母元音
    isUppercaseVowel = (c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U');

    // if 语句判断
    if (isLowercaseVowel || isUppercaseVowel)
        return "vowel";
    else
        return "consonant";
}

int add(int i, int j)
{
    return i + j;
}

bool isPalindrome(const std::string s)
{
    std::string LowerStr;
    for (char ch : s)
    {
        if (isalnum(ch))
        {
            LowerStr += tolower(ch);
        }
    }
    //cout << LowerStr << endl;
    int right = LowerStr.length() - 1;
    if (right == 0)
    {
        return true;
    }
    else
    {
        //int right = LowerStr.length();
        for (int left = 0; left < right; left++, right--)
        {
            if (LowerStr[left] != LowerStr[right])
            {
                return false;
            }
        }
        return true;
    }
}

std::vector<int> maxSlidingWindow(std::vector<int> &nums, int k)
{
    int n = nums.size();
    std::priority_queue<std::pair<int, int>> q;
    for (int i = 0; i < k; ++i)
    {
        q.emplace(nums[i], i);
    }
    std::vector<int> ans = {q.top().first};
    for (int i = k; i < n; ++i)
    {
        q.emplace(nums[i], i);
        while (q.top().second <= i - k)
        {
            q.pop();
        }
        ans.push_back(q.top().first);
    }
    return ans;
}

std::map<std::string, float> solvingEquations(float a, float b, float c)
{
    float x1, x2, discriminant, realPart, imaginaryPart;
    discriminant = b * b - 4 * a * c;
    std::map<std::string, float> ans;
    if (discriminant > 0)
    {
        x1 = (-b + sqrt(discriminant)) / (2 * a);
        x2 = (-b - sqrt(discriminant)) / (2 * a);
        // std::cout << "Roots are real and different." << std::endl;
        // std::cout << "x1 = " << x1 << std::endl;
        // std::cout << "x2 = " << x2 << std::endl;
        ans.insert(std::pair<std::string, float>("X1_real", x1));
        ans.insert(std::pair<std::string, float>("X2_real", x2));
    }
    else if (discriminant == 0)
    {
        // std::cout << "Real roots are the same" << std::endl;
        x1 = (-b + sqrt(discriminant)) / (2 * a);
        // std::cout << "x1 = x2 =" << x1 << std::endl;
        ans.insert(std::pair<std::string, float>("X1_real", x1));
        ans.insert(std::pair<std::string, float>("X2_real", x2));
    }
    else
    {
        realPart = -b / (2 * a);
        imaginaryPart = sqrt(-discriminant) / (2 * a);
        // std::cout << "Roots are image and different" << std::endl;
        // std::cout << "x1 = " << realPart << "+" << imaginaryPart << "i" << std::endl;
        // std::cout << "x2 = " << realPart << "-" << imaginaryPart << "i" << std::endl;
        ans.insert(std::pair<std::string, float>("X1_real", realPart));
        ans.insert(std::pair<std::string, float>("X1_image", imaginaryPart));
        ans.insert(std::pair<std::string, float>("X2_real", realPart));
        ans.insert(std::pair<std::string, float>("X2_image", -imaginaryPart));
    }
    return ans;
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

struct Student
{
    std::string name;
    void setName(const std::string &_name) { name = _name; }
    const std::string &getName() { return name; }
    Student(const std::string &name) : name(name) {}
};

PYBIND11_MODULE(bind_func, m)
{
    m.doc() = "test bind function";
    m.def("vowelOrConsonant", &vowelOrConsonant, py::arg("input_char"));
    m.def("add", &add, "A function which adds two numbers");
    m.def("isPalindrome", &isPalindrome);
    // 使用Lambda表达式
    // m.def("isPalindrome", [](const std::string &input_str)
    //       {
    //           std::cout << "input str is:" << input_str << std::endl;
    //           if (isPalindrome(input_str))
    //           {
    //               std::cout << "input str is palindrome" << std::endl;
    //           }
    //           else
    //           {
    //               std::cout << "input str is not palindrome" << std::endl;
    //           }
    //       });
    m.def("maxSlidingWindow", &maxSlidingWindow, py::return_value_policy::reference);
    // 引用现有对象，但不取得所有权。 C++ 端负责管理对象的生命周期并在不再使用时释放它
    m.def("solvingEquations", &solvingEquations, py::arg("a"), py::arg("b"), py::arg("c"), py::return_value_policy::reference);
    // m.def("swap", &swap, "A function which swap two numbers");
    // 直接绑定无效
    m.def("swap", [](py::buffer a, py::buffer b)
          {
              py::buffer_info a_info = a.request();
              py::buffer_info b_info = b.request();
              swap(static_cast<int *>(a_info.ptr), static_cast<int *>(b_info.ptr));
          });

    py::class_<Student>(m, "Student").def(py::init<const std::string &>()).def("setName", &Student::setName).def("getName", &Student::getName);
}