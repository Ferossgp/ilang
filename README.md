# iLang Compiler Project

## Overview

iLang is a simple imperative language for which this compiler is created.

## Requirements

1. LLVM 4.0.1 - install from source is preferable, check [llvm installation guide](./LLVM_INSTALL.md) for instructions
2. C++14 compatible compiler (gcc or clang)
3. CMake 3.6+

## Installation

CMake is used as a build system. Here is the installation process:

### Linux/OS X

1. Create directory where all build files will be placed.

   ```mkdir build && cd build```

2. Generate build files, if you are missing some dependencies, cmake will fail.

   ```cmake ../src```

3. Build executable

   ```make```

4. Check that everything works by running

   ```./voc```
