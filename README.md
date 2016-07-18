# MessageQueue

简单的消息队列实现。

共三个版本

### 1. C/nonthreadsafe
C语言非线程安全版本

### 2. C/theadsafe
C语言线程安全版本

### 3. CPP
C++版本使用C11特性

<hr>
由于C未提供List容器，所以C/nonthreadsafe中是一个List的实现。

以下简述实现思路
```
struct student_t{
    char name[100];
    int id;
}

struct node_t{
    struct node_t* prev;
    struct node_t* next;
    char payload[1];
    //
    char name[100];
    int id;
}

+----------------+
|    prev[4]     |
+----------------+
|    next[4]     |
+----------------+                +----------+
|   payload[1]   | <- overlap ->  | name[100]|
+----------------+                +----------+
                                  | id[4]    |
                                  +----------+
```


