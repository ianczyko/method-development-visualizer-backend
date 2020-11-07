# method-development-visualizer-backend

![Ubuntu g++ build](https://github.com/ianczyko/method-development-visualizer-backend/workflows/Ubuntu%20g++%20build/badge.svg) - Odpowiada na pytanie czy projekt się kompiluje

[![Build Status](https://travis-ci.org/ianczyko/method-development-visualizer-backend.svg?branch=main)](https://travis-ci.org/ianczyko/method-development-visualizer-backend) - Odpowiada na pytanie czy projekt przechodzi testy

[![codecov](https://codecov.io/gh/ianczyko/method-development-visualizer-backend/branch/main/graph/badge.svg?token=47IFD5DQNB)](https://codecov.io/gh/ianczyko/method-development-visualizer-backend) - Pokazuje % pokrycia testami kodów źródłowych w ./src

## Opis projektu

### Sposob kompilacji (i uruchomienia)

Przy pomocy cmake:

```bash
mkdir build ; cd build ; cmake .. ; make ; ./main
# opcjonoalnie w celu wygenerowania i uruchomienia testów
mkdir build ; cd build ; cmake -D TEST:BOOL=TRUE .. ; make ; ./tester