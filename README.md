demo_protobuf
-----------
This is a demo about protobuf with c, c++ and python

protobuf简介
-----------
> Protocol Buffers（protobuf） 是一种语言无关、平台无关、可扩展的序列化结构数据的方法，它可用于（数据）通信协议、数据存储等。\
Protocol Buffers 是一种具有灵活，高效，自动化机制的结构数据序列化方法－可类比 XML，但是比 XML 更小（3 ~ 10倍）、更快（20 ~ 100倍）、更为简单。
用户可以定义数据的结构，然后使用 **Protocol Buffer compiler** 生成的源代码轻松的在各种数据流中使用各种语言进行编写和读取定义的结构数据。用户甚至可以更新数据结构，而不破坏由旧数据结构编译的已部署程序。

总的来说，protobuf 是一种将结构数据**序列化**、**反序列化**的方法,以便于对结构数据进行存储、传输。并且 protobuf 只需要定义一个.proto 的数据结构文件。即可通过 protoc (Protocol Buffer Compiler) 自动生成各种语言对应的 API，方便快捷的完成对数据的序列化、反序列化。

安装 protobuf
-----------

* [protobuf-python](python)
* [protobuf-c](c)
* [protobuf-cpp](cpp)

Quick Start
-----------

Protocol Buffers 官方代码示例:

* [python](https://developers.google.com/protocol-buffers/docs/pythontutorial)
* [C++](https://developers.google.com/protocol-buffers/docs/cpptutorial)

Documentation
-------------

Protocol Buffers 完整文档：

https://developers.google.com/protocol-buffers/
