# DSPFFT

## Description

The first curriculum design of Digital Signal Processing.  

## Supported Compiler

|    Compiler     |     Platform     | Target |        C++11        |        C++14        |        C++17        |
| :-------------: | :--------------: | :----: | :-----------------: | :-----------------: | :-----------------: |
| GCC 7 \~ GCC 11 |   Linux x86-64   | `-m64` | Perfectly supported | Perfectly supported | Perfectly supported |
|    Clang 12     |   Linux x86-64   | `-m64` | Perfectly supported | Perfectly supported | Perfectly supported |
|     MSVC 19     | Windows (64-bit) |  x64   |    Not supported    |      Supported      |      Supported      |
|     MSVC 19     | Windows (64-bit) |  x86   |    Not supported    |  Compiler warnings  |      Supported      |

## How to build

### Linux

+ Build library

  ```sh
  make build [options]
  ```

  The `options` canbe:

  + `COMPILER`: Specify the compiler you want t build with. The value can be `g++` or `clang++`. `g++` by default.
  + `CPP_STANDARD`: Specify the C++ language standard. The value can be `-std=c++11`, `-std=c++14`, `-std=c++17`, `-std=gnu++11`, `-std=gnu++14`, `-std=gnu++17`, etc. The default value is `-std=c++11`.
  + `OPTIMIZATION`: Specify the level of optimization. The value can be `-O0`, `-O1`, `-Os`, etc. `-O2` by default.  
  + `WARNING_LEVEL`: Specify the warning level. The default value is `-Wall -Wpedantic -Wextra`
  + `PREDEFINED_MACRO`: Specify predefined macros, such as `-DUNICODE`. Empty by default.  

  Then the library will be in the "build" directory. The binary library will be `build/bin/libdspfft.a` and its header file will be in the `build/include` directory.  

+ Build execuation

  ```sh
  make test [options]
  ```

  The options are the same as that in 'Building library'. And when `PREDEFINED_MACRO` contains `-DTRANSFORM_TO_CRLF_NEWLINE`  , the program will generate MATLAB code with CRLF newline character (which is essential for MATLAB for Windows to run). Otherwise, the newline character will be LF.  

  The execuation will be `build/test/main.out`.  

+ Build all

  ```sh
  make build_and_test [options]
  ```

  This command is equivalent to:  

  ```sh
  make build [options] && make test [options]
  ```

+ Clean  

  ```sh
  make clean
  ```

  This will clean up all files built. 

### Windows

Enter the directory `src`, open `DSPFFT.sln` with Visual Studio 2019 or later versions, choose a platfrom (Release x64 recommended) and then build the solution. Then run `publish.cmd` to publish libraries and execuations. The binary library will be `publish\bin\dspfft.lib`, whose header files will be in `publish\include`, and the execuation will be `publish\test\homework.exe`. Notice that `publish.cmd` is used for Release | x64 platfrom by default. To change platform, please edit it and change the value of the variable `BINARY_DIR`.  

To clean up, you can run `clean_publish.cmd`.  

## How to run test program

The execuation is `build/test/main.out` on Linux and `homework.exe` on Windows. When running this program, you can pass parameters as follows: 

+  `--enable-time-comparing`: Compare time consumed using FFT and that using DFT directly.  
+ `--writing-matlab-code-to-file`: Generate MATLAB Code and write it into `result.m`, which can be run by MATLAB.  

## How to use library

You should include the header file `dspfft.hpp` in C++ and include `dspfft.h` in C. And link the library `libdspfft.a` on Linux and `dspfft.lib` on Windows.  

The APIs are as follows: 

### C++ APIs

Declared in `<dspfft.hpp>`. All APIs are in the namespace `dspfft`.  

+ `template <typename floating_type> ::std::vector<::std::complex<floating_type>> base_2_fft(const ::std::vector<::std::complex<floating_type>>& x)`  
+ `template <typename floating_type> ::std::vector<::std::complex<floating_type>> dft(const ::std::vector<::std::complex<floating_type>>& x)`  

### C APIs

Declared in `<dspfft.h>`. When included by C++ files, all APIs are in the namespace `dspfft` and all functions are declared with C linkage (`extern "C"`).  

+ `complexf`, `complexl`, `complexll`: Structures of complex number for `float`, `double` and `long double`.  
+ `complexf *base_2_fftf(complexf *, size_t)`, `complexl *base_2_fftl(complexl *, size_t)`, `complexll *base_2_fftll(complexll *, size_t)`
+ `complexf *dftf(complexf *, size_t)`, `complexl *dftl(complexl *, size_t)`, `complexll *dftll(complexll *, size_t)`

