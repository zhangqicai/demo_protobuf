demo_protobuf
-----------
This is a demo about protobuf with c, c++ and python

protobuf简介
-----------
> Protocol Buffers（protobuf） 是一种语言无关、平台无关、可扩展的序列化结构数据的方法，它可用于（数据）通信协议、数据存储等。\
Protocol Buffers 是一种具有灵活，高效，自动化机制的结构数据序列化方法－可类比 XML，但是比 XML 更小（3 ~ 10倍）、更快（20 ~ 100倍）、更为简单。
用户可以定义数据的结构，然后使用 **Protocol Buffer compiler** 生成的源代码轻松的在各种数据流中使用各种语言进行编写和读取定义的结构数据。用户甚至可以更新数据结构，而不破坏由旧数据结构编译的已部署程序。

总的来说，`protobuf` 是一种将结构数据**序列化**、**反序列化**的方法,以便于对结构数据进行存储、传输。并且`protobuf` 只需要定义一个`.proto` 的数据结构文件。即可通过 `protoc` (Protocol Buffer Compiler) 自动生成各种语言对应的 API，方便快捷的完成对数据的序列化、反序列化。

安装 protoc
-----------

1. 使用 `pre-built binary` 的 `protoc` 。
通过[下载地址](https://github.com/protocolbuffers/protobuf/releases/) 选择对应平台的预编译二进制文件压缩包。将压缩包解压后，将可执行文件所在目录添加到系统环境变量。执行以下命令，出现版本信息则表示安装成功。

```
protoc --version
```

2. 下载 `protoc` 源码，在本地编译 `protoc` 工具。具体方法见[官方说明](https://github.com/protocolbuffers/protobuf)。

安装 Protobuf Runtime
-----------

Protobuf 支持一系列不同的编程语言。对于每种编程语言，你都能在下方表格中找到对应的方法说明以安装 protobuf runtime。（表格仅列出与demo相关的部分）

| Language                             | Source                                                      | Ubuntu | Windows |
|--------------------------------------|-------------------------------------------------------------|--------|---------|
| C++ (include C++ runtime and protoc) | [src](src)                                                  | [![Build status](https://storage.googleapis.com/protobuf-kokoro-results/status-badge/linux-cpp_distcheck.png)](https://fusion.corp.google.com/projectanalysis/current/KOKORO/prod:protobuf%2Fgithub%2Fmaster%2Fubuntu%2Fcpp_distcheck%2Fcontinuous)<br/>[![Build status](https://storage.googleapis.com/protobuf-kokoro-results/status-badge/linux-bazel.png)](https://fusion.corp.google.com/projectanalysis/current/KOKORO/prod:protobuf%2Fgithub%2Fmaster%2Fubuntu%2Fbazel%2Fcontinuous)<br/>[![Build status](https://storage.googleapis.com/protobuf-kokoro-results/status-badge/linux-dist_install.png)](https://fusion.corp.google.com/projectanalysis/current/KOKORO/prod:protobuf%2Fgithub%2Fmaster%2Fubuntu%2Fdist_install%2Fcontinuous) | [![Build status](https://ci.appveyor.com/api/projects/status/73ctee6ua4w2ruin?svg=true)](https://ci.appveyor.com/project/protobuf/protobuf) |
| Python                               | [python](python)                                            | [![Build status](https://storage.googleapis.com/protobuf-kokoro-results/status-badge/linux-python27.png)](https://fusion.corp.google.com/projectanalysis/current/KOKORO/prod:protobuf%2Fgithub%2Fmaster%2Fubuntu%2Fpython27%2Fcontinuous)<br/>[![Build status](https://storage.googleapis.com/protobuf-kokoro-results/status-badge/linux-python35.png)](https://fusion.corp.google.com/projectanalysis/current/KOKORO/prod:protobuf%2Fgithub%2Fmaster%2Fubuntu%2Fpython35%2Fcontinuous)<br/>[![Build status](https://storage.googleapis.com/protobuf-kokoro-results/status-badge/linux-python36.png)](https://fusion.corp.google.com/projectanalysis/current/KOKORO/prod:protobuf%2Fgithub%2Fmaster%2Fubuntu%2Fpython36%2Fcontinuous)<br/>[![Build status](https://storage.googleapis.com/protobuf-kokoro-results/status-badge/linux-python37.png)](https://fusion.corp.google.com/projectanalysis/current/KOKORO/prod:protobuf%2Fgithub%2Fmaster%2Fubuntu%2Fpython37%2Fcontinuous)<br/>[![Build status](https://storage.googleapis.com/protobuf-kokoro-results/status-badge/linux-python_compatibility.png)](https://fusion.corp.google.com/projectanalysis/current/KOKORO/prod:protobuf%2Fgithub%2Fmaster%2Fubuntu%2Fpython_compatibility%2Fcontinuous)<br/>[![Build status](https://storage.googleapis.com/protobuf-kokoro-results/status-badge/linux-python27_cpp.png)](https://fusion.corp.google.com/projectanalysis/current/KOKORO/prod:protobuf%2Fgithub%2Fmaster%2Fubuntu%2Fpython27_cpp%2Fcontinuous)<br/>[![Build status](https://storage.googleapis.com/protobuf-kokoro-results/status-badge/linux-python35_cpp.png)](https://fusion.corp.google.com/projectanalysis/current/KOKORO/prod:protobuf%2Fgithub%2Fmaster%2Fubuntu%2Fpython35_cpp%2Fcontinuous)<br/>[![Build status](https://storage.googleapis.com/protobuf-kokoro-results/status-badge/linux-python36_cpp.png)](https://fusion.corp.google.com/projectanalysis/current/KOKORO/prod:protobuf%2Fgithub%2Fmaster%2Fubuntu%2Fpython36_cpp%2Fcontinuous)<br/>[![Build status](https://storage.googleapis.com/protobuf-kokoro-results/status-badge/linux-python37_cpp.png)](https://fusion.corp.google.com/projectanalysis/current/KOKORO/prod:protobuf%2Fgithub%2Fmaster%2Fubuntu%2Fpython37_cpp%2Fcontinuous)<br/>[![Build status](https://storage.googleapis.com/protobuf-kokoro-results/status-badge/linux-python-release.png)](https://fusion.corp.google.com/projectanalysis/current/KOKORO/prod:protobuf%2Fgithub%2Fmaster%2Fubuntu%2Fpython_release%2Fcontinuous) | [![Build status](https://storage.googleapis.com/protobuf-kokoro-results/status-badge/windows-python-release.png)](https://fusion.corp.google.com/projectanalysis/current/KOKORO/prod:protobuf%2Fgithub%2Fmaster%2Fwindows%2Fpython_release%2Fcontinuous) |
| Objective-C                          | [objectivec](objectivec)                                    | | |
| C                                  | [protocolbuffers/protobuf-go](https://github.com/protocolbuffers/protobuf-go)       | | |

安装示例（Linux Python）
-----------

1. 下载 ProtoBuf 源代码
```shell
wget https://github.com/protocolbuffers/protobuf/releases/download/v3.13.0/protobuf-python-3.13.0.tar.gz

```

2. 解压，编译，安装。
```shell
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
   
   * pip安装
    ``` shell
    pip install protobuff
    ```

4. 安装完成，验证protoc命令,若出现版本信息，则安装成功。
```shell
protoc --version
```
5. 验证Python模块是否被正确安装，若无报错，则安装成功。
```shell
python
import google.protobuf
```

Quick Start
-----------

Protocol Buffers 官方代码示例:

* [python](https://developers.google.com/protocol-buffers/docs/pythontutorial)
* [C++](https://developers.google.com/protocol-buffers/docs/cpptutorial)

Documentation
-------------

Protocol Buffers 完整文档：

https://developers.google.com/protocol-buffers/
