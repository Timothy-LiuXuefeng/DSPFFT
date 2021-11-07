# DSPFFT

## 概述

数字信号处理第一次课程设计——快速傅里叶变换  

## 支持的编译工具

|    编译工具     |       平台       | 目标平台 |        C++11        |        C++14        |        C++17        |
| :-------------: | :--------------: | :------: | :-----------------: | :-----------------: | :-----------------: |
| GCC 7 \~ GCC 11 |   Linux x86-64   |  `-m64`  | Perfectly supported | Perfectly supported | Perfectly supported |
|    Clang 12     |   Linux x86-64   |  `-m64`  | Perfectly supported | Perfectly supported | Perfectly supported |
|    MSVC 19.2    | Windows (64-bit) |   x64    |    Not supported    |      Supported      |      Supported      |
|    MSVC 19.2    | Windows (64-bit) |   x86    |    Not supported    |  Compiler warnings  |      Supported      |

## 如何构建

### Linux

+ 构建静态库  

  ```sh
  make build [options]
  ```

  `options` 可以是：  

  + `COMPILER`：指定构建所用的编译工具。值可以是 `g++` 或 `clang++`，默认为`g++`  
  + `CPP_STANDARD`：指定 C++ 语言标准，值可以是 `-std=c++11`、`-std=c++14`、`-std=c++17`、`-std=gnu++11`、`-std=gnu++14`、`-std=gnu++17` 等。默认为 `-std=c++11`  
  + `OPTIMIZATION`：指定优化等级。值可以是 `-O0`、`-O1`、`-Os` 等，默认为 `-O2`  
  + `WARNING_LEVEL`：指定警告等级。默认值为 `-Wall -Wpedantic -Wextra`  
  + `PREDEFINED_MACRO`：指定预定义宏，例如 `-DUNICODE`，默认为空

  例如：  

    ```sh
    make build CPP_STANDARD=-std=c++17 COMPILER=clang++
    ```

  然后，生成的库将会位于 `build` 文件夹内。二进制库文件为 `build/bin/libdspfft.a`，头文件位于 `build/include` 文件夹内。  

+ 构建测试程序  

  ```sh
  make test [options]
  ```

  `options` 与构建静态库相同。此外，当 `PREDEFINED_MACRO` 包含 `-DTRANSFORM_TO_CRLF_NEWLINE` 选项时，程序会生成行尾为 CRLF 的 MATLAB 代码（用来支持 Windows 平台的 MATLAB），否则生成的行尾是 LF。  

  可执行文件为 `build/test/main.out`。  

+ 全部构建  

  ```sh
  make build_and_test [options]
  ```

  此命令与下面的命令等价：  

  ```sh
  make build [options] && make test [options]
  ```

+ 清理  

  ```sh
  make clean
  ```

  将会清理所有构建过程中产生的文件。 

### Windows

进入文件夹 `src`，使用 Visual Studio 2019 或更高版本打开 `DSPFFT.sln`，并选择一个目标平台（建议为 Release | x64），再生成解决方案。然后运行 `publish.cmd` 来发布库文件和测试程序。二进制库文件为 `publish\bin\dspfft.lib`，其头文件位于 `publish\publish\include` 文件夹内，可执行文件为 `publish\test\homework.exe`。需要注意，`publish.cmd` 默认为 Release | x64 平台，如果要改变平台，请编辑该脚本，修改变量 `BINARY_DIR` 的值。  

如果要清理发布的文件，可以运行 `clean_publish.cmd`。  

## 如何运行测试程序

在 Linux 上，可执行文件为 `build/test/main.out`；在 Windows 上，可执行文件为 `homework.exe`。运行程序时可以传递下面的参数：  

+ `--enable-time-comparing`：比较 FFT 与直接运行 DFT 的时间  
+ `--writing-matlab-code-to-file`：生成 MATLAB 代码，并写入 MATLAB 脚本文件 `result.m`  

## 如何使用该库  

C++ 语言应当包含头文件 `dspfft.hpp`，C 语言应当包含 `dspfft.h`。在 Linux 上需链接 `libdspfft.a`，在 Windows 上需链接 `dspfft.lib`。  

库的接口如下：  

### C++ 接口

接口在 `<dspfft.hpp>` 中声明，所有的接口都在命名空间 `dspfft` 中。  

+ `template <typename floating_type> ::std::vector<::std::complex<floating_type>> base_2_fft(const ::std::vector<::std::complex<floating_type>>& x)`  
+ `template <typename floating_type> ::std::vector<::std::complex<floating_type>> dft(const ::std::vector<::std::complex<floating_type>>& x)`  

### C 接口

接口在 `<dspfft.h>` 中生命。当使用 C++ 语言包含时，所有接口都定义在 `dspfft` 命名空间中，所有函数都被声明为具有 C 语言链接（`extern "C"`）。  

+ `complexf`, `complexl`, `complexll`：实部和虚部分别为`float`, `double` and `long double` 的复数结构体  
+ `complexf *base_2_fftf(complexf *, size_t)`, `complexl *base_2_fftl(complexl *, size_t)`, `complexll *base_2_fftll(complexll *, size_t)`
+ `complexf *dftf(complexf *, size_t)`, `complexl *dftl(complexl *, size_t)`, `complexll *dftll(complexll *, size_t)`

## 注意事项  

+ 由于 dspfft 库是用 C++ 编写的，因此当使用 C 语言调用该库时，应当链接 C++ 运行时  
+ 如果要在 Linux 上运行测试程序，并用 Windows 平台的 MATLAB 运行生成的脚本，需要确保在构建时定义了 `TRANSFORM_TO_CRLF_NEWLINE` 宏，以保证生成的脚本行尾是 CRLF

