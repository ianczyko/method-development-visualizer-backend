# method-development-visualizer-backend (Work in progress)

![ubuntu-cmake-compile](https://github.com/ianczyko/method-development-visualizer-backend/workflows/ubuntu-cmake-compile/badge.svg) - Odpowiada na pytanie czy projekt się kompiluje

[![Build Status](https://travis-ci.org/ianczyko/method-development-visualizer-backend.svg?branch=main)](https://travis-ci.org/ianczyko/method-development-visualizer-backend) - Odpowiada na pytanie czy projekt przechodzi testy

[![codecov](https://codecov.io/gh/ianczyko/method-development-visualizer-backend/branch/main/graph/badge.svg?token=47IFD5DQNB)](https://codecov.io/gh/ianczyko/method-development-visualizer-backend) - Pokazuje % pokrycia testami kodów źródłowych w method-development-visualizer/src

## Opis projektu

### Sposob kompilacji części c++

Przy pomocy cmake:

```bash
cd method-development-visualizer ; mkdir build ; cd build ; cmake .. ; make
# opcjonoalnie w celu wygenerowania i uruchomienia testów
cd method-development-visualizer ; mkdir build ; cd build ; cmake -D TEST:BOOL=TRUE .. ; make
