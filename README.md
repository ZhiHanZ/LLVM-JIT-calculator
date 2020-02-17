# LLVM JIT calculator documents`
## prerequisite
TODO vargant or docker version of LLVM JIT
1. install cmake 3.12+:
follow the instruction made by this  website to install cmake
https://vitux.com/how-to-install-cmake-on-ubuntu-18-04/
2. install LLVM 9.0 version
* https://apt.llvm.org/ install the latest stable version of llvm through the link
* install signature
```asm
wget -O - https://apt.llvm.org/llvm-snapshot.gpg.key|sudo apt-key add -
```
* install all key package
```bash
# LLVM
apt-get install libllvm-9-ocaml-dev libllvm9 llvm-9 llvm-9-dev llvm-9-doc llvm-9-examples llvm-9-runtime
# Clang and co
apt-get install clang-9 clang-tools-9 clang-9-doc libclang-common-9-dev libclang-9-dev libclang1-9 clang-format-9 python-clang-9 clangd-9
# libfuzzer
apt-get install libfuzzer-9-dev
# lldb
apt-get install lldb-9
# lld (linker)
apt-get install lld-9
# libc++
apt-get install libc++-9-dev libc++abi-9-dev
# OpenMP
apt-get install libomp-9-dev
```
* prioritize llvm 9 llvm config
```bash
sudo update-alternatives --install /usr/bin/llvm-conifg llvm-config /usr/bin/llvm-config-9 100
sudo update-alternatives --install /usr/bin/clang clang /usr/bin/clang-9 100
sudo update-alternatives --install /usr/bin/clang++ clang++ /usr/bin/clang++-9 100
```
* install other packages in use
```bash
sudo apt install zlib1g-dev
sudo apt-get install autoconf autogen
sudo apt-get install libtool
```
3. install glog, gflag and gtest
```bash
sudo apt-get install -y libgtest-dev
sudo apt-get install -y cmake # install cmake
cd /usr/src/gtest
sudo cmake CMakeLists.txt
sudo make
sudo cp *.a /usr/local/lib
git clone https://github.com/google/glog.git
cd glog/
./autogen.sh && ./configure && make && make install
sudo cmake CMakeLists.txt
sudo make
sudo make install prefix=/usr/local/
sudo apt-get install -y autoconf automake libtool curl make g++ unzip
```
## How to use the current calculator
### in source dir
```bash
mkdir build
cd build
cmake ..
make
```
### to run the source code
in build dir
```bash
cd source 
./testTest_run
``` 
### to run all unit tests made in gtest
in build dir
```bash
cd tests
./testTest_tests
```

### simple way to explain how to use it
in build dir, run command like (1 + 1) to run the program
```bash
cd source 
./testTest_run
1 + 1
``` 

