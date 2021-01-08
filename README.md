# method-development-visualizer-backend

![ubuntu-cmake-compile](https://github.com/ianczyko/method-development-visualizer-backend/workflows/ubuntu-cmake-compile/badge.svg) - Odpowiada na pytanie czy projekt się kompiluje

![ubuntu-cmake-compile-and-test](https://github.com/ianczyko/method-development-visualizer-backend/workflows/ubuntu-cmake-compile-and-test/badge.svg) - Odpowiada na pytanie czy projekt przechodzi testy

[![codecov](https://codecov.io/gh/ianczyko/method-development-visualizer-backend/branch/main/graph/badge.svg?token=47IFD5DQNB)](https://codecov.io/gh/ianczyko/method-development-visualizer-backend) - Pokazuje % pokrycia testami kodów źródłowych w /src

## Opis projektu

Projektem jest aplikacja pozwalająca na tworzenie grafu obrazującego rozwój algorytmów
sztucznej inteligencji. Aplikacja umożliwia dodawanie/usuwanie ręczne elementów
grafu oraz oferuje sposób na dodawania elementów automatycznie na podstawie ich nazwy
np. ilSHADE jest być podłączany do węzła SHADE. Interfejs aplikacji jest graficzny
(przeglądarkowy) a logika operacji na grafie jest zaimplementowana w C++.

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

Istnieje jeszcze trzecia opcja generująca dodatkowo pliki coverage, wymaga ona: `cmake -D TEST:BOOL=TRUE -D ENABLE_COVERAGE:BOOL=TRUE ..`

### Przygotowanie wirtualnego środowiska Pythona

W katalogu projektu:

```bash
cd web
pipenv install django==3.1.3
pipenv shell
# następnie wewnąrz wirtualnej powłoki:
python3 manage.py runserver
```

Po wykonaniu powyższych kroków, poniższy adres powinien zwrócić przykładową strukturę (GET):

- [localhost:8000/api/graph/](http://localhost:8000/api/graph/)

Powinien on zwrócić:

```json
{
    "nodes": [
        {
            "name": "DE",
            "description": "Opis algorytmu DE",
            "parent": "",
            "aliases": [
                "de",
                "De",
                "De."
            ]
        },
        {
            "name": "SHADE",
            "description": "Opis algorytmu SHADE",
            "parent": "DE",
            "aliases": [
                "Shade",
                "SHA-DE"
            ]
        },
        {
            "name": "JADE",
            "description": "Opis algorytmu JADE",
            "parent": "DE",
            "aliases": []
        }
    ]
}
```

Lista wszystkich endpointów:

- **api/graph/** (GET) - zwraca strukturę grafu aktualnie znajdującej się w bazie danych w formacie JSON.
- **api/node/\<str:name\>/**
  - GET - zwraca informacje o podanym węźle w formacie JSON.
  - DELETE - zwraca informacje o podanym węźle w formacie JSON.
- **api/add/manual/** (POST) - Dodaję węzeł do struktury grafu.
- **api/add/auto/** (POST) - Dodaję węzeł do struktury grafu automatycznie dedukując rodzica na podstawie nazwy.

Reqesty do endpointów w api/add/ wymagają ustawionych nagłówków `X-CSRFToken` i `Cookie`.

Format `body` dla reqestów do endpointów w api/add/
```json
{
    "name": "JADE",
    "description": "Opis algorytmu JADE",
    "parent": "DE",
    "aliases": ["jade", "ja-de"]
}
```

Uwaga, część kodu źródłowego części Python została wygenerowana przez Django. Wykorzystane zostały komendy:

```bash
django-admin startproject web_config .
python3 manage.py startapp web_api
```

## Frontend

Po skonfigurowaniu backendu, można uruchomić przeglądarkowy interfejs aplikacji, który pobiera dane z endpointów wyżej opisanego bacendu i wyświetla je z pomocą biblioteki cytoscape.js. Po naciśnięciu na węzeł wyświetlają się jego szczegółowe informacje.

Uruchomienie interfejsu wymaga otworzenia client/index.html w przeglądarce.
