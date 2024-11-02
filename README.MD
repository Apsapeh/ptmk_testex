
#### До оптимизации:
```sh
$ ./perf_test_ex5.sh
[1]: Elapsed time: 56 ms
[2]: Elapsed time: 58 ms
[3]: Elapsed time: 71 ms
[4]: Elapsed time: 58 ms
[5]: Elapsed time: 63 ms
[6]: Elapsed time: 57 ms
[7]: Elapsed time: 66 ms
[8]: Elapsed time: 54 ms
[9]: Elapsed time: 56 ms
[10]: Elapsed time: 59 ms
```
Среднее время исполнения - 59.8 мс


### После оптимизации:
```sh
$ ./perf_test_ex5.sh
[1]: Elapsed time: 43 ms
[2]: Elapsed time: 40 ms
[3]: Elapsed time: 40 ms
[4]: Elapsed time: 44 ms
[5]: Elapsed time: 38 ms
[6]: Elapsed time: 48 ms
[7]: Elapsed time: 41 ms
[8]: Elapsed time: 47 ms
[9]: Elapsed time: 44 ms
[10]: Elapsed time: 44 ms
```
Среднее время исполнения - 42.9 мс

### О проведённой оптимизации:
1. Тип пола был сменён с "TEXT" на "ENUM (Male, Female)"
    * Уменьшило размер базы данных
    * Ускорило вставку элементов

2. Был добавлен индекс на "sex" и "fullname"
    * Ускорило получение данных т.к. строится дерево, но замедлило вставку, т.к. сортируется

Если использовать "EXPLAIN ANALYZE", то увидим, что до оптимизации
использовался "Parallel Seq Scan" с фильтрами "((fullname ~~ 'F%'::text) AND sex = 'Male'::text)". \

После оптимизации был использован "Bitmap Index Scan" с условием "((sex = 'Male'::sex_enum) AND (fullname >= 'F'::text) AND (fullname < 'G'::text))", что является значительно более быстрым методом.