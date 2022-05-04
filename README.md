Написать функцию для поиска дубликатов среди списка файлов. Функция одним из параметров должна принимать функцию хеширования.

def find_duplicates(files: list[str], hash_function: callable) -> list[str]:
Реализовать следующие hash функции:

* CRC

highorder = h & 0xf8000000
h = h << 5
h = h ^ (highorder >> 27)
h = h ^ ki
* PJW

h = (h << 4) + ki
g = h & 0xf0000000
if (g != 0)
    h = h ^ (g >> 24)
    h = h ^ g
* BUZ

highorder = h & 0x80000000
h = h << 1
h = h ^ (highorder >> 31)
h = h ^ R[ki]
, где ki - входная последовательность символов, R - функция, которая для ki символа, дает случайное число.



На выходе количество дубликатов и время работы для каждой hash функции. В выходной результат добавить результат для работы встроенной функции hash.



Код должен запускаться через make run
