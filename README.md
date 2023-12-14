# Autorzy
- Marcin Łobacz
- Aleksandr Rahacheuski

# ZPR - Porównywanie plików tekstowych

Stworzyliśmy szkielet narzędzia. Aplikacja ma możliwość wczytywania, modyfikowania i zapisywania plików.

Proces budowania został zautomatyzowany. Dodaliśmy także automatyczną generacje dokumentacji - doxygen.

Ponadto wykonaliśmy przykładowe testy jednostkowe.


## Podstawowa  funkconalnosć

Program wczytuje pliki tekstowe, i oblicza hashe jak całego pliku, tak i pojedyńczej linijki, program wczytywuje plik binarnie, co pozwala mu   odnależć koniec linii

Program może obliczyć hash całego pliku i porównać go z drugim,  jeśli pliki są identycznę to program będzie kończył się, Dodatkowo jest możliwoć obliczeia hashu linijka po linijce i zapisywania go do hashmap.Hashmap jako klucz przyjmuje hash linijki, a jako znaczenie vector, w którym  są zapisywane numery linijek, dodatkowo program liczy ilość linijek, co w przyszłosci pomoże na identyfikacje działania [modify,add, delete], Hashe każdego pliku liczą się jednocześnie dzięki wątkom



## Podgląd aplikacji
![](readme_files/Podglad.png)

## Budowanie

Do budowania potrzebny jest cmake, doxygen, boost, openssl, qt6.

Mając świeżą instalację Ubuntu 22.04 musimy wykonać komendę: <br>
    - sudo apt-get install qt6-base-dev libgl1-mesa-dev libboost-test-dev doxygen libssl-dev  g++ cmake

### Kompilacja

```
mkdir build && cd build
cmake ..
make
make docs
```
Dokumentacja po kompilacji znajduje się w folderze docs.

### Uruchomienie
Aplikacja - ```cd src && ./ZPR```

Test jednostkowe - ```cd tests && ./MyTests```




