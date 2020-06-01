cd ~ && mkdir LLVM && mkdir LLVM/source # setup directories
cd ~/LLVM/source # cd into your llvm source directory 
git clone https://github.com/llvm/llvm-project.git # git tag -l to get a specific version
cd llvm-project
mkdir build
cd build
cmake -DLLVM_ENABLE_PROJECTS=clang -G "Unix Makefiles" ../llvm
make -j 8 #(from within the build directory to start the process)
