### 命名约定

#### 类型名 [class, struct, enum, typedef]
- 每个单词的首字母大写，其他字母小写，不使用下划线分隔
- 示例

```cpp
class Time {}
class TimeSpan {}
```
#### 变量名
- 首单词小写，其他单词首字母大写，如果使用了前锥，首单词的首字母也要大写
- 如果是内置类型，需要使用前缀
    - 布尔：b
    - 有符号整数：i
    - 无符号整数：n/u 【侧重数量的时候使用n】
    - 浮点数：f
    - 字符串：sz
    - 字符：ch
- 如果STD类型，需要使用前缀
    - string:str
    - vector:vec
    - map:map
    - multimap:mmp
    - set:set
    - list:lst
    - que:que
- 如果是指针类型，附加前缀p
- 示例

```cpp
TimeSpan timeSpan;
bool bEnabled;
int iDataIndex;
unsigned int nRetryTimes;
string strUserName
vector<int> vecUserId;
int* piDataIndex;
```

#### 函数名
- 每个单词的首字母大写，其他字母小写，不使用下划线分隔
- 如果是属性函数，需要使用前锥get或set
- 如果参数列表过长，需要换行时，第一个参数必须另起一行并缩进4字符
- 参数使用缩进格式时，可以适当的在一行中放置多个参数，但是同一行中的参数必须是密切相关的
- 示例

```cpp
bool StartService();
State getState();
void setState(State state);

int SendData(
    Target* pTarget,
    const char* pData, int iDataLen);
{
    // implementation
}
```

#### 类成员声明次序
- 类型定义
- 常量定义
- 静态函数
- 构造函数
- 成员函数
- 运算符重载
