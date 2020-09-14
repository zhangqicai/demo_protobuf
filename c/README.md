## 安装 protobuf-c（Ubuntu）

1. 安装依赖

   ```shell
   sudo apt-get install autoconf automake libtool curl make g++ unzip pkg-config pkgconf
   ```

2. 安装 protobuf 编译器 protoc 

   ```shell
   git clone https://github.com/protocolbuffers/protobuf.git
   cd protobuf
   git submodule update --init --recursive
   ./autogen.sh
	```
3. 安装 protobuf runtime
	```shell
   ./configure
   make
   make check  # make check 失败的话没关系，继续下面的安装
   sudo make install
   sudo ldconfig
   ```

4. 安装protobuf-c 的 protoc-c 和 protobuf-c runtime 

   ```shell
   git clone https://github.com/protobuf-c/protobuf-c.git
   cd protobuf-c
   ./autogen.sh && ./configure && make && make install
   ```

4. 安装完成，验证 protoc-c 命令，若出现 protobuf-c 和 libprotoc 版本信息，则安装成功。

   ```shell
   protoc-c --version
   ```
   

## 使用说明

1. 编写 demo.proto 文件

2. 使用 protoc 编译 demo.proto 文件，生成 demo_pb2.py 文件。

   ```shell
   protoc -I=../common --c_out=. demo.proto
   ```

   * **-I**： 指定 .proto 文件所在路径，未指定默认为当前目录。
   * **--c_out**：指定输出 c 的接口文件路径。

3. 调用自动生成的 API 完成相应功能。 

## 基本 API 说明

定义一个名为 demo.proto 文件，如下所示
```C
message Person {
    int32 id = 1;
    string name = 2;
    string email = 3;

    enum PhoneType {
        MOBILE = 0;
        HOME = 1;
        WORK = 2;
    } 

    message PhoneNumber {
        string number = 1;
        PhoneType type = 2;
    }

    repeated PhoneNumber phones = 4;
}

message demo_info {
    repeated Person people = 1;
}
```

自动生成的 API 命名为： 文件名__message名__api; 以下为demo.proto文件中根据 person message自动生成的 api
```C

typedef struct _Demo__Person Demo__Person;
typedef struct _Demo__Person__PhoneNumber Demo__Person__PhoneNumber;

/* --- enums --- */

typedef enum _Demo__Person__PhoneType {
  DEMO__PERSON__PHONE_TYPE__MOBILE = 0,
  DEMO__PERSON__PHONE_TYPE__HOME = 1,
  DEMO__PERSON__PHONE_TYPE__WORK = 2
    PROTOBUF_C__FORCE_ENUM_TO_BE_INT_SIZE(DEMO__PERSON__PHONE_TYPE)
} Demo__Person__PhoneType;

/* --- messages --- */

struct  _Demo__Person__PhoneNumber
{
  ProtobufCMessage base;
  char *number;
  Demo__Person__PhoneType type;
};
#define DEMO__PERSON__PHONE_NUMBER__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&demo__person__phone_number__descriptor) \
    , (char *)protobuf_c_empty_string, DEMO__PERSON__PHONE_TYPE__MOBILE }


struct  _Demo__Person
{
  ProtobufCMessage base;
  int32_t id;
  char *name;
  char *email;
  size_t n_phones;
  Demo__Person__PhoneNumber **phones;
};
#define DEMO__PERSON__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&demo__person__descriptor) \
    , 0, (char *)protobuf_c_empty_string, (char *)protobuf_c_empty_string, 0,NULL }


/* Demo__Person__PhoneNumber methods */
// 初始化一个嵌套的 message 对象，在为其分配内存后，必须初始化。
void   demo__person__phone_number__init
                     (Demo__Person__PhoneNumber         *message);

/* Demo__Person methods */
// 初始化一个 message 对象，在为 message 分配内存后，必须初始化。 
void   demo__person__init
                     (Demo__Person         *message);

// 获取 message 序列化后的实际大小。
size_t demo__person__get_packed_size
                     (const Demo__Person   *message);

// 将 message 序列化，out内存可根据 *__get_packed_size获取的大小来分配。 
size_t demo__person__pack
                     (const Demo__Person   *message,
                      uint8_t             *out);
size_t demo__person__pack_to_buffer
                     (const Demo__Person   *message,
                      ProtobufCBuffer     *buffer);
// 将数据反序列化。若无特殊需求，则 ProtobufCAllocator 可指定为 NULL。message 使用完成后需要通过 demo__person_free_unpacked 释放内存。
Demo__Person *
       demo__person__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   demo__person__free_unpacked
                     (Demo__Person *message,
                      ProtobufCAllocator *allocator);
```



参考资料
-----------

[安装和使用protobuf-c](https://www.jianshu.com/p/a7e88cb17031)

[protobuf-c](https://github.com/protobuf-c/protobuf-c)