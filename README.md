# method-development-visualizer-backend

![ubuntu-cmake-compile](https://github.com/ianczyko/method-development-visualizer-backend/workflows/ubuntu-cmake-compile/badge.svg) - Odpowiada na pytanie czy projekt się kompiluje

[![Build Status](https://travis-ci.org/ianczyko/method-development-visualizer-backend.svg?branch=main)](https://travis-ci.org/ianczyko/method-development-visualizer-backend) - Odpowiada na pytanie czy projekt przechodzi testy

[![codecov](https://codecov.io/gh/ianczyko/method-development-visualizer-backend/branch/main/graph/badge.svg?token=47IFD5DQNB)](https://codecov.io/gh/ianczyko/method-development-visualizer-backend) - Pokazuje % pokrycia testami kodów źródłowych w ./src

## Opis projektu

### Sposob kompilacji (i uruchomienia)

Przy pomocy cmake:

```bash
mkdir build ; cd build ; cmake .. ; make ; ./method-development-visualizer-backend
# opcjonoalnie w celu wygenerowania i uruchomienia testów
mkdir build ; cd build ; cmake -D TEST:BOOL=TRUE .. ; make ; ./tester