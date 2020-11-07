# method-development-visualizer-backend

(niektualne linki)

[![Ubuntu g++ build](https://github.com/ianczyko/PROE2020L_gr_102_zadanieprogramistyczne1/workflows/Ubuntu%20g++%20build/badge.svg)](https://github.com/ianczyko/PROE2020L_gr_102_zadanieprogramistyczne1/actions) - Odpowiada na pytanie czy projekt się kompiluje

[![Build Status](https://travis-ci.com/ianczyko/PROE2020L_gr_102_zadanieprogramistyczne1.svg?branch=master)](https://travis-ci.com/ianczyko/PROE2020L_gr_102_zadanieprogramistyczne1) - Odpowiada na pytanie czy projekt przechodzi testy

[![codecov](https://codecov.io/gh/ianczyko/PROE2020L_gr_102_zadanieprogramistyczne1/branch/master/graph/badge.svg)](https://codecov.io/gh/ianczyko/PROE2020L_gr_102_zadanieprogramistyczne1) - Pokazuje % pokrycia testami kodów źródłowych w ./src

## Opis projektu

### Sposob kompilacji (i uruchomienia)

Przy pomocy cmake:

```bash
mkdir build ; cd build ; cmake .. ; make ; ./main
# opcjonoalnie w celu wygenerowania i uruchomienia testów
mkdir build ; cd build ; cmake -D TEST:BOOL=TRUE .. ; make ; ./tester