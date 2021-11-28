## use pybind11
- 绑定函数
- 绑定class
- 绑定异常
- 调用python
- 嵌入解释器



```python
pip list
```

    Note: you may need to restart the kernel to use updated packages.
    

    WARNING: You are using pip version 19.2.3, however version 21.3.1 is available.
    You should consider upgrading via the 'python -m pip install --upgrade pip' command.
    

    Package             Version
    ------------------- -------
    argcomplete         1.12.3 
    attrs               21.2.0 
    backcall            0.2.0  
    bleach              4.1.0  
    colorama            0.4.4  
    debugpy             1.5.1  
    decorator           5.1.0  
    defusedxml          0.7.1  
    entrypoints         0.3    
    importlib-metadata  4.8.2  
    importlib-resources 5.4.0  
    ipykernel           6.5.1  
    ipython             7.29.0 
    ipython-genutils    0.2.0  
    jedi                0.18.1 
    Jinja2              3.0.3  
    jsonschema          4.2.1  
    jupyter-client      7.1.0  
    jupyter-core        4.9.1  
    jupyterlab-pygments 0.1.2  
    MarkupSafe          2.0.1  
    matplotlib-inline   0.1.3  
    mistune             0.8.4  
    nbclient            0.5.9  
    nbconvert           6.3.0  
    nbformat            5.1.3  
    nest-asyncio        1.5.1  
    numpy               1.21.4 
    packaging           21.3   
    pandocfilters       1.5.0  
    parso               0.8.2  
    pickleshare         0.7.5  
    pip                 19.2.3 
    prompt-toolkit      3.0.22 
    Pygments            2.10.0 
    pyparsing           3.0.6  
    pyrsistent          0.18.0 
    python-dateutil     2.8.2  
    pywin32             302    
    pyzmq               22.3.0 
    setuptools          41.2.0 
    six                 1.16.0 
    testpath            0.5.0  
    tornado             6.1    
    traitlets           5.1.1  
    typing-extensions   4.0.0  
    wcwidth             0.2.5  
    webencodings        0.5.1  
    zipp                3.6.0  
    

### 绑定函数


```python
from lib import bind_func
```

#### 位置参数


```python
input_char='F'
bind_func.vowelOrConsonant(input_char=input_char)
# 使用位置参数
```




    'consonant'




```python
#### 基本数据类型
```


```python
res = bind_func.add(1,2)
print(res)
```

    3
    

#### 字符串类型


```python
input_str = "teet"
# std::string s
# string映射为string
p_flag=bind_func.isPalindrome(input_str)
print(p_flag)
```

    True
    

#### vector类型


```python
nums = [1,3,-1,-3,5,3,6,7]
k = 3
# std::vector<int> &nums, int k
# vector映射为list
res = bind_func.maxSlidingWindow(nums,k)
print(res)
```

    [3, 3, 5, 5, 6, 7]
    


```python
#### map类型
```


```python
a = 2
b = 4
c = 9
equations_ans=bind_func.solvingEquations(a=a, b=b, c=c)
print(equations_ans)
# 返回值std::map<std::string, float>映射为dict
# type(equations_ans)
```

    {'X1_image': 1.8708287477493286, 'X1_real': -1.0, 'X2_image': -1.8708287477493286, 'X2_real': -1.0}
    




    dict



#### 指针类型


```python
import numpy as np
# int *a, int *b
# buffer类型映射为指针
a= np.array(1)
b =np.array(10)
bind_func.swap(a,b)
print(a)
```

    10
    

#### 结构体


```python
stu = bind_func.Student("Tom")
stu.getName()
stu.setName("Jack")
stu.getName()
```




    'Jack'



### 绑定类


```python
from lib import bind_class
dog = bind_class.Dog()
# 直接使用已经定义的Dog类
bind_class.call_go(dog)
```




    'wooof!'




```python
class Cat(bind_class.Animal):
    def go(self,n_times):
        return "meow!"*n_times
```


```python
cat=Cat()
bind_class.call_go(cat)
```




    'meow!meow!meow!'




```python
# 在Python中派生子类时,父类构造必须显示调用,不能使用super
class Dachshund(bind_class.Dog):
    def __init__(self,name) -> None:
        # super().__init__()
        bind_class.Dog.__init__(self)
        self.name=name
    def bark(self):
        return "yap!"
```


```python
dachshund=Dachshund(name="腊肠犬")
dachshund.bark()
```




    'yap!'



### 绑定异常

### 调用python

### 嵌入解释器

