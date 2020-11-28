# method-development-visualizer-backend (Work in progress)

![ubuntu-cmake-compile](https://github.com/ianczyko/method-development-visualizer-backend/workflows/ubuntu-cmake-compile/badge.svg) - Odpowiada na pytanie czy projekt się kompiluje

![ubuntu-cmake-compile-and-test](https://github.com/ianczyko/method-development-visualizer-backend/workflows/ubuntu-cmake-compile-and-test/badge.svg) - Odpowiada na pytanie czy projekt przechodzi testy

[![codecov](https://codecov.io/gh/ianczyko/method-development-visualizer-backend/branch/main/graph/badge.svg?token=47IFD5DQNB)](https://codecov.io/gh/ianczyko/method-development-visualizer-backend) - Pokazuje % pokrycia testami kodów źródłowych w /src

## Opis projektu

Projektem jest aplikacja pozwalająca na tworzenie grafu obrazującego rozwój algorytmów
sztucznej inteligencji. Aplikacja powinna umożliwiać dodawanie/usuwanie ręczne elementów
grafu oraz oferować sposób dodawania elementów automatycznie na podstawie ich nazwy
np. ilSHADE powinien być podłączony do węzła SHADE. Interfejs aplikacji ma być graficzny
(przeglądarkowy) a backend ma być zaimplementowany w C++ i dane ma przechowywać w
bazie danych.

### Zależności

- Boost (z skompilowanym Boost.Python i Boost.Test)
- CMake
- python3 wraz z:
  - python3-dev
  - pipenv

Instalacja wszystkich zależności:

```bash
sudo apt-get install libboost-all-dev # Boost
sudo apt-get install cmake # cmake
sudo apt-get install python3-dev # python3-dev
pip3 install pipenv # pipenv
```

### Sposob kompilacji części C++

Przy pomocy cmake:

```bash
cd method-development-visualizer ; mkdir build ; cd build ; cmake .. ; make
# opcjonoalnie w celu wygenerowania testów
cd method-development-visualizer ; mkdir build ; cd build ; cmake -D TEST:BOOL=TRUE .. ; make
# uruchomienie testów
ctest
```

Testy na ten moment pokrywają tylko część napisaną w "czystym" C++.

### Przygotowanie wirtualnego środowiska Pythona

W katalogu projektu:

```bash
cd web
pipenv shell
# następnie wewnąrz wirtualnej powłoki:
python manage.py runserver
```

Po wykonaniu powyższych kroków, powinny zacząć działać poniższe adresy:

- [localhost:8000/api/graph/](http://localhost:8000/api/graph/)
- [localhost:8000/api/cpp_hello_world/](http://localhost:8000/api/cpp_hello_world/)

Na ten moment:

- **/graph/** zwraca strukturę grafu aktualnie znajdującej się w bazie danych w formacie JSON.
- **/cpp_hello_world/** zwraca zawartość przykładowej funkcji w C++.
