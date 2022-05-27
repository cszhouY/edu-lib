# edu-lib
This is a example designed after learning the static library. It realized some function of an  educational administration system. 
## 声明一个课程

~~~c
course_t csapp;
~~~

## 声明一个班级

~~~c
class_t jk2002;
~~~

# 初始化

## 定义class_t变量后需要初始化。

~~~c
void class_init(class_t* class, id_t classID, int num);
~~~

+ `class_t* class`	指向一个班级的指针
+ `id_t classID  `     班级ID号，必须是四位正整型数
+ `int num   `           班级人数，在区间[1, 50]

## 定义course_t变量后需要初始化。

~~~c
void course_init(course_t* course, id_t id, char* course_name, score_t credit, type_t type);
~~~

+ `course_t* course`   指向课程变量的指针
+ `id_t id`   课程ID号，正整型
+ `char* course_name`   课程名字，长度不超过14的字符串
+ `score_t credit`   学分，正整型，**在区间[1,5]，超出范围会被置为1**
+ `type_t type`  类型，有两种：core——核心课，general——通识课

# 导入

## 导入班级成员信息

~~~c
int class_import(class_t* class, char* file);
~~~

+ `class_t* class`指向一个班级的指针
+ `char* file`文件，有两种来源：
  1. `文件名`：从文件中读取
  2. `NULL`：从命令行输入

注意格式为

~~~c
<学号>  <姓名>
~~~

学号为六位：

+ 高四位班级ID
+ 低两位流水号，从1开始，在班级人数范围内

例：

~~~
200201 as
200202 dc
200203 sd
200204 ss
200205 sh 
~~~

## 导入课程信息

将某一课程导入到某一班级，该班级所有成员均有该课程

~~~c
int course_import(course_t* course, class_t* class);
~~~

+ `course_t* course`指向课程的指针，需要被导入的课程
+ `class_t* class`指向班级的指针，需要被导入的班级

## 导入成绩

将某一个班的某一的成绩

~~~c
int grade_import(course_t* course, class_t* class, char* file);
~~~

+ `course_t* course`指向课程的指针，需要被导入成绩的课程
+ `class_t* class`指向班级的指针，需要被导入成绩的班级
+ `char* file`文件名

文件格式

~~~c
<学号> <成绩>
~~~

+ 学号格式同上
+ 成绩为正整型数，在区间[0, 100]

例：

~~~
200201 75
200202 75
200203 100
200204 55
200205 60
~~~

# 查看

## 查看班级成员信息

包括学号和姓名

~~~c
void class_info(class_t* class);
~~~

## 查看某一学生成绩

包括总成绩和课程成绩

~~~c
void stu_info(class_t *class, id_t id);
~~~

+ `class_t *class` 指向班级变量的指针，该学生所在班级
+ `id_t id`学生学号

**需要注意，学生成绩和排名都是动态变化的，受排序影响。需要刷新排名再查看才能看到最新排名，即调用_update族函数。否则会出现排名为0或者排名不对的情况。**

# 分析

## 刷新课程排名

刷新某一个班级某一门课程的排名

~~~c
void course_rank_update(course_t* course, class_t* class)
~~~

+ course_t* course指向课程的指针，需要被分析的课程
+ class_t* class指向班级的指针，需要被分析的班级

## 刷新学生总分排名

刷新某一个班级的学生总排名

~~~c
void stu_rank_update(class_t* class, int mod)
~~~

+ class_t* class指向班级的指针，需要被分析的班级
+ int mod排名方法，有如下几种方法可用（可以用 | 符），**其它值无效**
  1. `0`总成绩算术平均
  2. `CORE_AVE`仅考虑核心课
  3. `WEIGH_AVE`采用加权平均

## 课程成绩

分析某一个班级某一个课程的成绩

~~~c
void course_score_analyze(course_t* course, class_t* class, int mod)
~~~

+ course_t* course指向课程的指针，需要被分析的课程
+ class_t* class指向班级的指针，需要被分析的班级
+ int mod分析方法，有如下几种方法可用（可以用 | 符），**其它值无效**
  1.  `AVE`平均分
  2.  `PAS `及格率
  3.  `SEG` 分段
  4.  `LIST`排名表

# 析构

## 析构班级

在程序最后需要删除班级变量

~~~c
void class_delete(class_t* class)
~~~

+ class_t* class指向需要被析构的班级变量的指针
