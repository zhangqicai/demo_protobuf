安装 protobuf-python（Ubuntu）
-----------

1. 安装依赖

   ```shell
   sudo apt-get install autoconf automake libtool curl make g++ unzip
   ```

2. 安装 protobuf 编译器 protoc

   ```shell
   wget https://github.com/protocolbuffers/protobuf/releases/download/v3.13.0/protobuf-python-3.13.0.tar.gz
   tar zxvf protobuf-python-3.13.0.tar.gz
   cd protobuf-3.13.0
   ./configure
   make
   make check
   sudo make install
   sudo ldconfig
   ```
   
3. 安装 protobuf 的 Python 模块

   * 脚本安装
	``` shell
	cd ./python
	python setup.py build
	python setup.py test
	sudo python setup.py install
	```

	* pip安装（版本要保证与 protoc 一致）
	``` shell
	 pip install protobuff
	```

5. 安装完成，验证 protoc 命令,若出现版本信息，则安装成功。

	```shell
	protoc --version
	```
6. 验证Python模块是否被正确安装，若无报错，则安装成功。

	```shell
	python
	import google.protobuf
	```

使用说明
-----------

1. 编写 demo.proto 文件

2. 使用 protoc 编译 demo.proto 文件，生成 demo_pb2.py 文件。

   ```shell
   protoc -I=../common --python_out=. demo.proto
   ```

   * **-I**： 指定 .proto 文件所在路径，未指定默认为当前目录。
   * **--python_out**：指定输出python的接口文件路径。

3. 


参考资料
-----------

[Protobuf Python Install](https://github.com/protocolbuffers/protobuf/tree/master/python)

