proto3 语法

简述怎样使用 protobuf 语言编写 .proto 文件去构建自己的 protobu 数据结构。

## 定义 Message 类型

 一个简单的例子，定义一个搜索请求报文格式，每个搜索请求都有一个查询字符串，感兴趣的特定结果页数以及每页的结果数。下面就是定义这个请求的 .proto 文件：

```shell
syntax = "proto3";

message SearchRequest {
  string query = 1;  // 查询字符串
  int32 page_number = 2;  // 第几页
  int32 result_per_page = 3;  // 每页的结果数
}
```

* 文件的第一行指定了使用的语法版本为 `proto3`，默认为 `proto2`。其中第一行是指非空、非注释的第一行。
* `SearchRequest` message 定义了三个字段，每个字段对应着要包含在 message 中的数据。

### 指定字段类型

在上面的示例中，所有字段都是 [标量类型](https://developers.google.com/protocol-buffers/docs/proto#scalar)：两个整数（`page_number` 和 `result_per_page`）和一个字符串（`query`）。除此之晚，还可以为字段指定复合类型，包括 [枚举](https://developers.google.com/protocol-buffers/docs/proto#enum) 和其它的 message 类型。

### 分配字段编号

message 定义中的每个字段都有**唯一编号**。这些数字以 [message 二进制格式](https://www.jianshu.com/p/82ff31c6adc6) 标识字段，并且一旦 message 被使用，这些编号就无法再更改。注意1 到 15 范围内的字段编号需要一个字节进行编码，编码结果将同时包含编号和类型（可以在 [Protocol Buffer 编码](https://www.jianshu.com/p/82ff31c6adc6) 中找到更多相关信息）。16 到 2047 范围内的字段编号占用两个字节。因此，应该为非常频繁出现的 message 元素保留字段编号 1 到 15。请记住为将来可能添加的常用元素预留出一些空间。

注：可以指定的最小字段数为 1，最大字段数为 229   -  1 或 536,870,911。其中19000 到 19999 范围内的数字为保留数字不能使用。如果使用，protobuf编译器会报错。并且，已经定义过的字段编号也不能使用。

### 指定字段规则

指定的 message 字段可以是下面几种情况之一：

-   **singular** :  message 可以有零个或一个此字段（但不能超过一个）。这是proto3语法的默认字段规则。
-  **repeated**: 在 message 中，此字段可以重复任意次数（包括零）。将保留重复值的顺序。可看作可变长度的数组。

### 添加更多 message 类型

可以在单个 .proto 文件中定义多种 message 类型。在需要定义多个相关 message 的时候会很有用 - 例如，如果要定义与搜索请求相应的搜索回复 message - SearchResponse message，则可以将其添加到相同的 .proto：

```
message SearchRequest {
  singular string query = 1;
  repeated int32 page_number = 2;
  repeated int32 result_per_page = 3;
}

message SearchResponse {
 ...
}
```



### 添加注释

为你的 .proto 文件添加注释，可以使用 C/C++ 语法风格的注释 // 和 /* ... */ 。

```
/* SearchRequest represents a search query, with pagination options to
 * indicate which results to include in the response. */

message SearchRequest {
  singular string query = 1;
  singular int32 page_number = 2;  // Which page number do we want?
  singular int32 result_per_page = 3;  // Number of results to return per page.
}
```

### Reserved 保留字段

如果你通过完全删除字段或将其注释掉来更新 message 类型，则未来一些用户在做他们的修改或更新时就可能会再次使用这些字段编号。如果以后加载相同 `.proto` 的旧版本，这可能会导致一些严重问题，包括数据损坏，隐私错误等。确保不会发生这种情况的一种方法是指定已删除字段的字段编号（有时也需要指定名称为保留状态，英文名称可能会导致 JSON 序列化问题）为 “保留” 状态。如果将来的任何用户尝试使用这些字段标识符，protocol buffer 编译器将会抱怨。

```
message Foo {
  reserved 2, 15, 9 to 11;
  reserved "foo", "bar";
}
```

 注：不能在同一 "reserved" 语句中将字段名称和字段编号混合在一起指定。 

### .proto文件生成结果

通过protobuf 编译器编译 .proto 文件时，编译器将会生成所需语言的代码，这些代码可以操作文件中描述的 message 类型，包括获取和设置字段值、将 message 序列化为输出流、以及从输入流中解析出 message。

其中：

* 对于 **c**， 编译器从每个 .proto 生成一个 .pb-c.c 和 .pb-c.h 文件，其中包含文件中描述的每种 message 类型对应的结构体声明和定义。

* 对于 **c++** ，编译器从每个 .proto 生成一个 .h 和 .cc文件，其中包含文件中描述的每种 message 类型对应的类。

* 对于**python** ，编译器从每个 .proto 生成一个 _pb2.py文件，其中包含文件中每种 message 类型的静态描述符，然后与元类一起使用以创建必要的python 数据访问类。

更多关于 API 详细信息，参阅相关的 [API参考](https://developers.google.com/protocol-buffers/docs/reference/overview) 。

### 默认值

* string：默认值为空。
* bytes：默认为空。
* bools：默认为false。
* numeric types：默认为0.
* enums：默认为第一个定义的枚举值，必为0。
* message：该字段未设置默认值，实际值取决于依赖的语言。因解析出的 message 字段无法判断是显式设置的值，还是根本没有设置。

对于 repeated 字段，默认值为空（通常为相应语言的空列表）。



### 枚举

可以通过向 message 定义添加枚举来简单地执行此操作 - 具有枚举类型的字段只能将一组指定的常量作为其值（如果你尝试提供不同的值，则解析器会将其视为一个未知的领域）。在下面的例子中，我们添加了一个名为 Corpus 的枚举，其中包含所有可能的值，之后定义了一个类型为 Corpus 枚举的字段：

```
message SearchRequest {
  string query = 1;
  int32 page_number = 2;
  int32 result_per_page = 3;
  enum Corpus {
    UNIVERSAL = 0;
    WEB = 1;
    IMAGES = 2;
    LOCAL = 3;
    NEWS = 4;
    PRODUCTS = 5;
    VIDEO = 6;
  }
  Corpus corpus = 4;
}

```

