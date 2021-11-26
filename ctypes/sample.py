# sample.py
import ctypes
import os
import platform

# .so file is located in the directory above. See Makefile for
# build instructions
if(platform.system()=="Windows"):
    _path = './lib/libsample.dll'
elif(platform.system()=="Linux"):
    _path = './lib/libsample.so'
else:
    print("other system, compile again")
_mod = ctypes.cdll.LoadLibrary(_path)

# int gcd(int, int)
gcd = _mod.gcd
gcd.argtypes = (ctypes.c_int, ctypes.c_int)
# 指定输入参数类型，将python的int使用ctypes转换为c_int,适合c语言的类型
gcd.restype = ctypes.c_int
# 指定返回参数类型，默认为c_int

# int in_mandel(double, double, int)
# 测试点是否在Mandelbrot集中
in_mandel = _mod.in_mandel
in_mandel.argtypes = (ctypes.c_double, ctypes.c_double, ctypes.c_int)
in_mandel.restype = ctypes.c_int

# int divide(int, int, int *)
_divide = _mod.divide
_divide.argtypes = (ctypes.c_int, ctypes.c_int, ctypes.POINTER(ctypes.c_int))
# 返回参数为int指针，需要使用POINTER包装,.value属性可被用来获取或更改指针所指向的值
_divide.restype = ctypes.c_int

def divide(x, y):
    rem = ctypes.c_int()
    quot = _divide(x,y,rem)
    return quot,rem.value

# void avg(double *, int n)

# Define a special type for the 'double *' argument
class DoubleArrayType:
    def from_param(self, param):
        typename = type(param).__name__
        if hasattr(self, 'from_'+typename):
        # hasattr() 函数用于判断对象是否包含对应的属性
            return getattr(self, 'from_'+typename)(param)
        # getattr() 函数用于返回一个对象属性值
        # 可以通过变量参数调用函数,self为实例对象，'from_'+typename为函数名,param为关键自参数
        elif isinstance(param, ctypes.Array):
        # isinstance() 函数来判断一个对象是否是一个已知的类型
            return param
        else:
            raise TypeError("Can't convert %s" % typename)

    # Cast from array.array objects
    def from_array(self, param):
        if param.typecode != 'd':
            raise TypeError('must be an array of doubles')
        ptr, _ = param.buffer_info()
        # buffer_info返回一个元组(address, length)
        # 以给出用于存放数组内容的缓冲区元素的当前内存地址和长度
        return ctypes.cast(ptr, ctypes.POINTER(ctypes.c_double))
        # cast()函数可用于将ctypes实例转换为指向不同ctypes数据类型的指针。 
        # cast()采用两个参数，一个或者可以转换为某种指针的ctypes对象，以及一个ctypes指针类型。
        # 它返回第二个参数的实例，它引用与第一个参数相同的内存块

    # Cast from lists/tuples
    def from_list(self, param):
        val = ((ctypes.c_double)*len(param))(*param)
        #将list转换为一个ctypes的数组对象 
        return val

    from_tuple = from_list

    # Cast from a numpy array
    def from_ndarray(self, param):
        return param.ctypes.data_as(ctypes.POINTER(ctypes.c_double))
        # ctypes.data_as返回转换为特定c类型对象的数据指针,为其缓冲区地址
        
DoubleArray = DoubleArrayType()
_avg = _mod.avg
_avg.argtypes = (DoubleArray, ctypes.c_int)
_avg.restype = ctypes.c_double

def avg(values):
    return _avg(values, len(values))

# struct Point { }
class Point(ctypes.Structure):
    _fields_ = [('x', ctypes.c_double),
                ('y', ctypes.c_double)]
# 需要定义一个类，包含相应的字段和类型，与c中结构体字段类型相对应

# double distance(Point *, Point *)
distance = _mod.distance
distance.argtypes = (ctypes.POINTER(Point), ctypes.POINTER(Point))
distance.restype = ctypes.c_double
