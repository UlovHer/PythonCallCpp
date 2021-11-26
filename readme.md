### 1 Python调用Cpp

Python 因为其是一门解释性语言和动态类型的原因，在计算密集型的操作上非常令人拙计，所以对于计算密集型的操作，可以使用 C/C++ 等在计算上比 Python 快的语言做拓展。**用 C/C++ 对 Python 拓展的主流方式一共有五种，使用 Python 的 ctypes 模块、使用 Python CAPI、使用 Cython 、使用 SWIG以及使用pybind11。**

### 2 use ctypes

`ctypes`是一个用于Python的外部函数库。它提供C兼容的数据类型，并允许在DLL或共享库中调用函数。它可以用来将这些库封装在纯Python中。使用ctypes调用C动态库，如果调用C++动态库，则参数类型必须符合C类型。

- 官方文档：[ctypes --- Python 的外部函数库 — Python 3.7.12 文档](https://docs.python.org/zh-cn/3.7/library/ctypes.html)

#### 2.1 基本数据类型

| ctypes类型   | C类型                                  | Python类型                 |
| :----------- | :------------------------------------- | :------------------------- |
| c_bool       | _Bool                                  | bool (1)                   |
| c_char       | char                                   | 1-character string         |
| c_wchar      | wchar_t                                | 1-character unicode string |
| c_byte       | char                                   | int/long                   |
| c_ubyte      | unsigned char                          | int/long                   |
| c_short      | short                                  | int/long                   |
| c_ushort     | unsigned short                         | int/long                   |
| c_int        | int                                    | int/long                   |
| c_uint       | unsigned int                           | int/long                   |
| c_long       | long                                   | int/long                   |
| c_ulong      | unsigned long                          | int/long                   |
| c_longlong   | __int64 or long long                   | int/long                   |
| c_ulonglong  | unsigned __int64 or unsigned long long | int/long                   |
| c_float      | float                                  | float                      |
| c_double     | double                                 | float                      |
| c_longdouble | long double                            | float                      |
| c_char_p     | char * (NUL terminated)                | string or None             |
| c_wchar_p    | wchar_t * (NUL terminated)             | unicode or None            |
| c_void_p     | void *                                 | int/long or None           |

#### 2.2 动态库编译

- Windows可直接使用CMake
- Linux可直接使用gcc命令编译，也可使用CMake


```python
cat /proc/version
cd c_src
gcc sample.c -shared -fPIC -o libsample.so
mv -f libsample.so ../ctypes/lib
```


```python
cd ../ctypes
python example.py
```

    7
    1
    0
    (5, 2)
    2.0
    4.242640687119285


#### 2.3 基本数据类型参数


```python
# int类型
import ctypes
import os

_path = './lib/libsample.dll'
_mod = ctypes.cdll.LoadLibrary(_path)
# int gcd(int, int)
gcd = _mod.gcd
gcd.argtypes = (ctypes.c_int, ctypes.c_int)
# 指定输入参数类型，将python的int使用ctypes转换为c_int,适合c语言的类型
gcd.restype = ctypes.c_int
# 指定返回参数类型，默认为c_int
print(gcd(35,42))
```

    7


#### 2.4 数组类型参数


```python
# int数组
import ctypes
import os

_path = './lib/libsample.dll'
_mod = ctypes.cdll.LoadLibrary(_path)
get_elem = _mod.get_elem
get_elem.argtypes = (ctypes.Array,ctypes.c_int)
get_elem.restype = ctypes.c_int
int_array_10=ctypes.c_int*10
intput_array=int_array_10()
index =ctypes.c_int(2)
intput_array[2]=ctypes.c_int(5)
elem = get_elem(intput_array,index)
print(elem)
```

    5


#### 2.5 普通指针类型参数


```python
# int指针
import ctypes
import os

_path = './lib/libsample.dll'
_mod = ctypes.cdll.LoadLibrary(_path)
divide = _mod.divide
# int divide(int, int, int *),整型指针转换
# divide.argtypes = (ctypes.c_int,ctypes.c_int,ctypes.c_int)
# 指定输入参数类型
divide.argtypes = (ctypes.c_int,ctypes.c_int,ctypes.POINTER(ctypes.c_int))
# divide.restype
# 若无返回值,或者不接收,可不制定返回值类型
# x = 0 
# x = 0,违反python之中整数不可修改
x = ctypes.c_int()
divide(10,3,x)
```


    3


```python
# bytez转int指针
import ctypes

a = (ctypes.c_byte * 4)()
print(a)
ctypes.cast(a, ctypes.POINTER(ctypes.c_int))
# cast()函数可用于将ctypes实例转换为指向不同ctypes数据类型的指针
```

    <__main__.c_byte_Array_4 object at 0x00000274E91671C8
    
    ctypes.wintypes.LP_c_long at 0x274e9167248>


```python
# double指针
import ctypes

nums = [1, 2, 3]
print(*nums)
# 向函数传递参数，*将变量中可迭代对象的元素拆解出来,
# 作为独立的参数第传给函数

print('列表元素个数：',len(nums))

a = (ctypes.c_double * len(nums))(*nums)
# 将list中每个元素转化为数组中的元素
print(a)
```

    1 2 3
    列表元素个数： 3
    <__main__.c_double_Array_3 object at 0x00000274E86E33C8>

```python
# numpy转double指针
import numpy
import ctypes

a = numpy.array([1,2,3])
print(a)
a = a.ctypes.data_as(ctypes.POINTER(ctypes.c_double))
# ctypes.data_as返回转换为特定c类型对象的数据指针,为其缓冲区地址
# 内部任然是调用cast()
print(a)
```

    [1 2 3]
    <__main__.LP_c_double object at 0x00000274E9167548>


#### 2.6 结构体类型参数


```python
# 结构体
import ctypes
import os

_path = './lib/libsample.dll'
_mod = ctypes.cdll.LoadLibrary(_path)

class Point(ctypes.Structure):
  _fields_ = [('x',ctypes.c_double),('y',ctypes.c_double)]
# 需要定义一个类，包含相应的字段和类型，与c中结构体字段类型相对应

distance = _mod.distance
distance.argtypes = (ctypes.POINTER(Point),ctypes.POINTER(Point))
distance.restype = ctypes.c_double
# 指定返回值类型

p1 = Point(1,2)
p2 = Point(4,5)
distance(p1,p2)
```


    4.242640687119285

#### 2.7 字符串类型参数


```python
# 字符串
import ctypes
import os

_path = './lib/libsample.dll'
_mod = ctypes.cdll.LoadLibrary(_path)
reverse = _mod.reverse
# char* reverse(char *),字符串指针类型转换
# reverse.argtypes = (ctypes.c_char_p,)
# 如果只有1个参数,需要加",",元组特性
reverse.argtypes = [ctypes.c_char_p]
reverse.restype = ctypes.c_char_p

# inptu_str = ctypes.c_char_p("test_demo".encode("utf-8"))
inptu_str = ctypes.c_char_p(bytes("hello", 'utf-8'))
res=reverse(inptu_str).decode('utf-8')
print(res)

```

    olleh


#### 2.8 函数指针类型参数


```python
# 函数指针
import ctypes
import platform

# void qsort (void* base, size_t num, size_t size,int (*compar)(const int*,const int*));
# 回调函数原型int compar(const int*,const int*)
cdll_names={
  'Linux':'lib.dylib',
  'Windows':'msvcrt.dll'
}
path = cdll_names[platform.system()]
print(path)
cdll = ctypes.cdll.LoadLibrary(path)
# 使用CFUNCTYPE创建ctypes的函数指针类型
CMPFUNC = ctypes.CFUNCTYPE(ctypes.c_int, ctypes.POINTER(ctypes.c_int), ctypes.POINTER(ctypes.c_int))

# 回调函数，用于给出元素之间大小的判断方法
def py_func(a, b):
  print(py_func, a, b)
  return a[0] - b[0]

array_5 = ctypes.c_int * 5
a = array_5(1, 6, 3, 2, 5)
for elem in a:
  print(elem,end="\t")
print()
# 调用的是C标准库中的qsort函数
cdll.qsort(a, len(a), ctypes.sizeof(ctypes.c_int), CMPFUNC(py_func))
for elem in a:
  print(elem,end="\t")
print()
```

    msvcrt.dll
    1	6	3	2	5	
    <function py_func at 0x00000274E86C6E58> <ctypes.wintypes.LP_c_long object at 0x00000274E863EE48> <ctypes.wintypes.LP_c_long object at 0x00000274EF6DF9C8>
    <function py_func at 0x00000274E86C6E58> <ctypes.wintypes.LP_c_long object at 0x00000274E863EE48> <ctypes.wintypes.LP_c_long object at 0x00000274EF6DF9C8>
    <function py_func at 0x00000274E86C6E58> <ctypes.wintypes.LP_c_long object at 0x00000274E863EE48> <ctypes.wintypes.LP_c_long object at 0x00000274EF6DF9C8>
    <function py_func at 0x00000274E86C6E58> <ctypes.wintypes.LP_c_long object at 0x00000274E863EE48> <ctypes.wintypes.LP_c_long object at 0x00000274EF6DF9C8>
    <function py_func at 0x00000274E86C6E58> <ctypes.wintypes.LP_c_long object at 0x00000274E863EE48> <ctypes.wintypes.LP_c_long object at 0x00000274EF6DF9C8>
    <function py_func at 0x00000274E86C6E58> <ctypes.wintypes.LP_c_long object at 0x00000274E863EE48> <ctypes.wintypes.LP_c_long object at 0x00000274EF6DF9C8>
    <function py_func at 0x00000274E86C6E58> <ctypes.wintypes.LP_c_long object at 0x00000274E863EE48> <ctypes.wintypes.LP_c_long object at 0x00000274EF6DF9C8>
    <function py_func at 0x00000274E86C6E58> <ctypes.wintypes.LP_c_long object at 0x00000274E863EE48> <ctypes.wintypes.LP_c_long object at 0x00000274E86E37C8>
    <function py_func at 0x00000274E86C6E58> <ctypes.wintypes.LP_c_long object at 0x00000274E863EE48> <ctypes.wintypes.LP_c_long object at 0x00000274E86E37C8>
    <function py_func at 0x00000274E86C6E58> <ctypes.wintypes.LP_c_long object at 0x00000274E863EE48> <ctypes.wintypes.LP_c_long object at 0x00000274E86E37C8>
    1	2	3	5	6	

### 3 use capi

[Python/C API](https://docs.python.org/2/c-api/)提供了给 C/C++ 提供了一套 API ，可以使用 Python 配套的一些设施，完成与 C/C++ 与 Python 的交互，而且可以在C代码中操作你的Python对象。

这种方法需要以特定的方式来编写C代码以供Python去调用它。所有的Python对象都被表示为一种叫做PyObject的结构体，并且`Python.h`头文件中提供了各种操作它的函数。例如，如果PyObject表示为PyListType(列表类型)时，那么我们便可以使用`PyList_Size()`函数来获取该结构的长度，类似Python中的`len(list)`函数。大部分对Python原生对象的基础函数和操作在`Python.h`头文件中都能找到。使用起来比较麻烦。

- 官方文档：[Python/C API Reference Manual — Python 3.10.0 documentation](https://docs.python.org/3/c-api/index.html)

### 4 use cython

Cython基于capi做了包装， 是一种面向 Python 和 Cython 语言的一个优化过的静态编译器。Cython 除了提供 CAPI 之外，还提供了大部分的封装好的模块和函数，像是 C++ 的 STL 等等，而对于 Unicode 或者 Python 的异常机制，Cython 会帮助你自动翻译成 C/C++， Cython 的易用性是较好的。Cython 会将 Python 和 Cython 翻译成 C/C++，然后编译成一个静态链接库供 Python 使用。Cython 是包含 C 数据类型的 Python。Cython 是 Python：几乎所有 Python 代码都是合法的 Cython 代码。 Cython 的编译器会转化 Python 代码为 C 代码，这些 C 代码均可以调用 Python/C 的 API。Cython 可不仅仅包含这些，Cython 中的参数和变量还可以以 C 数据类型来声明。代码中的 Python 值和 C 的值可以自由地交叉混合（intermixed）使用, 所有的转化都是自动进行。Python 中的引用计数维护(Reference count maintenance)和错误检查(error checking)操作同样是自动进行的，并且全面支持 Python 的异常处理工具(facilities)，包括 `try-except` 和 `try-finally`，即便在其中操作 C 数据都是可以的。

- 官方文档：[Welcome to Cython’s Documentation — Cython 3.0.0a9 documentation](https://cython.readthedocs.io/en/latest/)

### 5  use swig

SWIG 是 Simplified Wrapper and Interface Generator 的简称，也是基于capi。SWIG 并不只是提供 C/C++ 对 Python 的拓展，还支持对 Java、Perl 等其他语言的拓展，就是写一个拓展可以在多处使用。如果不需要使用 Python 的异常或者其他特性，使用 SWIG 来拓展 Python 需要做的只是写一个接口文件。使用 SWIG 的最大优点是可以使同一套代码拓展多种语言，但是对于某些特性，依然还是要针对 Python 在配置文件中显式地写出一些 Python CAPI 相关的调用，在调试方面，也是只能使用 C/C++ 配套的调试工具。

- 官方文档：[SWIG and Python](http://www.swig.org/Doc3.0/Python.html#Python)

### 6 use pybind11

pybind11 是一个 `header-only` 的库，换句话说，只需要 C++ 项目里直接 include pybind11 的头文件就能使用。将已经存在的C++代码绑定到Python。pybind11的目标和语法都类似于boost.python库。利用编译时的内省来推断类型信息。使用起来比cython简单。

- 官方文档：[Intro — pybind11 documentation](https://pybind11.readthedocs.io/en/stable/)
