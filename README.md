# Authors
- Marcin Ł.
- Aleksandr R.

# ZPR - Porównywanie plików tekstowych

## Functionality

Helps merging two txt files 

## Building

Requirements cmake, doxygen, boost, openssl, qt6.

If you have fresh install of Ubuntu 22.04 you can run command: <br>
    - sudo apt-get install qt6-base-dev libgl1-mesa-dev libboost-test-dev doxygen libssl-dev graphviz  g++ cmake 

If you want to generate a docs you need to run first command: <br>
    - sudo apt-get install gcovr lcov

### Compilation

```
    mkdir build && cd build
    cmake ..
    make
    make docs
```
Documentation is stored in docs folder.

If you want to calculate test coverage, we have to run:
```
    mkdir build && cd build
    cmake -DCMAKE_BUILD_TYPE=Debug -DENABLE_COVERAGE=ON ..
    cmake --build . --config Debug --target coverage
```
Documentation will be generated in build/coverage
### Launching
Application - ```cd src && ./ZPR```

Unit tests - ```cd tests && ./MyTests```




