安装 protobuf-c（Ubuntu）
-----------

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
   



参考资料
-----------

[安装和使用protobuf-c](https://www.jianshu.com/p/a7e88cb17031)

[protobuf-c](https://github.com/protobuf-c/protobuf-c)