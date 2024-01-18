# Autorzy
- Marcin Łobacz
- Aleksandr Rahacheuski

# ZPR - Porównywanie plików tekstowych

## Podstawowa  funkconalnosć

Program umożliwia scalanie plików poprzez kolorowanie róznić między nimi.

## Budowanie

Do budowania potrzebny jest cmake, doxygen, boost, openssl, qt6.

Mając świeżą instalację Ubuntu 22.04 musimy wykonać komendę: <br>
    - sudo apt-get install qt6-base-dev libgl1-mesa-dev libboost-test-dev doxygen libssl-dev  g++ cmake

W przypadku checi wygenerowania dokumentacji pokrycia kodu dokumentacji.
    - sudo apt-get install gcovr lcov

### Kompilacja

```
mkdir build && cd build
cmake ..
make
make docs
```
Dokumentacja po kompilacji znajduje się w folderze docs.

Jeżeli chcemy obliczyć pokrycie testami musimy wykonać:
```
    mkdir build && cd build
    cmake -DCMAKE_BUILD_TYPE=Debug -DENABLE_COVERAGE=ON ..
    cmake --build . --config Debug --target coverage
```
Dokumentacja lconv zostanie wygenerowana w build/coverage
### Uruchomienie
Aplikacja - ```cd src && ./ZPR```

Test jednostkowe - ```cd tests && ./MyTests```




