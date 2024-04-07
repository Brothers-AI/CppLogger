<h1 style="text-align: center;">Build Steps</h1>

## Windows Environment

### Pre-Requisits

  - git
  - MSVC
  - cmake
  
### Clone the Repository

    git clone https://github.com/Brothers-AI/CppLogger.git

### Build Options

<div align=center>

| CMake Argument           | Value   | Usage                                           |
| ------------------------ | ------- | ------------------------------------------------|
| BUILD_SHARED_LIBS        | ON      | Builds Shared Library for CppLogger             |
| BUILD_SHARED_LIBS        | OFF     | Builds Static Library for CppLogger             |
| BUILS_EXAMPLES           | ON      | Builds Sample Example for CppLogger             |
| CMAKE_BUILD_TYPE         | Debug   | Builds Library in Debug Mode                    |
| CMAKE_BUILD_TYPE         | Release | Builds Library in Release Mode                  |
| CMAKE_INSTALL_PREFIX     | path    | Copies `include`, `lib` and `bin` to the path   |

</div>

### Build With Shared Library

Go the Directory where the repository is cloned.
```
    mkdir build;cd build
    cmake -DBUILD_SHARED_LIBS=ON -DBUILD_EXAMPLES=ON ..
    cmake --build . --config <Build Type>
```

### Build With Static Library

Go the Directory where the repository is cloned.
```
    mkdir build;cd build
    cmake -DBUILD_SHARED_LIBS=OFF -DBUILD_EXAMPLES=ON ..
    cmake --build . --config <Build Type>
```

### To get Include, Libraries

```
    cmake -DCMAKE_INSTALL_PREFIX=<path to copy include and libs> ..
    cmake --build . --config <Build Type>
    cmake --install .
```

Include folder and libs folder will get copied to the specified path
