安装 protobuf-cpp（Ubuntu）
-----------

1. 安装依赖

   ```shell
   sudo apt-get install autoconf automake libtool curl make g++ unzip
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

4. 安装完成，验证 protoc 命令，若出现 libprotoc 版本信息，则安装成功。

   ```shell
   protoc-c --version
   ```



参考资料
-----------

[protobuf cpp Install](https://github.com/protocolbuffers/protobuf/tree/master/src)