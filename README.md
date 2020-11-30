# method-development-visualizer-backend

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

- Boost 1.71+, wraz z skompilowanymi:
  - Boost.Python 
  - Boost.Test
- CMake
- python3 wraz z:
  - python3-dev
  - pip3
  - pipenv
  - Django (instalowane później w pipenv)

Instalacja wszystkich zależności:

```bash
sudo apt-get install libboost-all-dev # Boost
sudo apt-get install cmake # cmake
sudo apt-get install python3-dev # python3-dev
sudo apt-get install pip3 # pip3
pip3 install pipenv # pipenv
```

Uwaga, na dzień dzisiejszy libboost-all-dev zainstaluje Boost 1.71 jedynie na ubuntu 20.04 z aktualnym apt-get.

### Sposob kompilacji części C++

Przy pomocy cmake:

```bash
cd methodDevelopment ; mkdir build ; cd build ; cmake .. ; make
```

Alternatywnie w celu wygenerowania testów

```bash
cd methodDevelopment ; mkdir build ; cd build ; cmake -D TEST:BOOL=TRUE .. ; make
# uruchomienie testów
ctest
```

### Przygotowanie wirtualnego środowiska Pythona

W katalogu projektu:

```bash
cd web
pipenv install django==3.1.3
pipenv shell
# następnie wewnąrz wirtualnej powłoki:
python3 manage.py runserver
```

Po wykonaniu powyższych kroków, powinny zacząć działać poniższe adresy:

- [localhost:8000/api/graph/](http://localhost:8000/api/graph/)
- [localhost:8000/api/cpp_hello_world/](http://localhost:8000/api/cpp_hello_world/)

Na ten moment:

- **api/graph/** zwraca strukturę grafu aktualnie znajdującej się w bazie danych w formacie JSON.
- **api/cpp_hello_world/** zwraca zawartość przykładowej funkcji w C++.

Uwaga, część kodu źródłowego części Python została wygenerowana przez Django. Wykorzystane zostały komendy:

```bash
django-admin startproject web_config .
python3 manage.py startapp web_api
```

## Frontend

Po skonfigurowaniu backendu, można uruchomić przeglądarkowy interfejs aplikacji, który pobiera dane z endpointu /api/graph/ i wyświetla je z pomocą biblioteki cytoscape.js. Po naciśnięciu na węzeł wyświetlają się jego szczegółowe informacje.

W tym momencie uruchomienie interfejsu wymaga otworzenia client/index.html w przeglądarce.
