# Test_task_yadro

## Задание:
Устройство хранения данных типа лента (Таре) предназначено для последовательной записи и чтения данных. Считывающая/записывающая магнитная головка неподвижна во время чтения и записи, а лента имеет возможность двигаться в
обоих направлениях. Запись и чтение информации возможны в ячейку ленты, на которой в данный момент находится магнитная головка.
Перемещения ленты - затратная по времени операция - лента не предназначена для произвольного доступа.
Имеется входная лента длины N (где N - велико), содержащая элементы типа integer.
Имеется выходная лента такой же длины. Необходимо записать в выходную ленту отсортированные по возрастанию элементы с входной ленты. Есть ограничение по использованию оперативной памяти - не более М байт (М может быть < N, т. > е. загрузить все данные с ленты в оперативную память не получится). Для реализации алгоритма можно использовать разумное количество временных лент, т.е. лент, на которых можно хранить какую-то временную информацию, необходимую в процессе работы алгоритма.
- Необходимо создать проект С++, компилируемый в консольное приложение, которое реализует алгоритм сортировки данных с входной ленты на выходную. Необходимо сделать следующее:
- Определить интерфейс для работы с устройством типа лента.
- Написать класс, реализующий этот интерфейс и эмулирующий работу с лентой посредством обычного файла. Должно быть возможно сконфигурировать (без перекомпиляции - например, через внешний конфигурационный файл, который будет прочитан на старте приложения) задержки по записи/чтению элемента с ленты, перемотки ленты, и сдвига ленты на одну позицию.
- Файлы временных лент можно сохранять в директорию tmp.
- Написать класс, реализующий алгоритм сортировки данных с входной ленты на выходную.
- Консольное приложение должно принимать на вход имя входного и выходного файлов и производить сортировку.
- Желательно написать юнит-тесты.

## Решение:
### Algorithm
```
В данном задании основная проблема заключалась в том, чтобы поддержать сортировка при ограничении на оперативную память RAM, я подошел к этому следующим образом:
Считываем tape, пока у нас есть запас по RAM, как только он заканчивается, мы делаем qsort и после создаем временную ленту и так далее, пока мы не дойдем до конца tape,
после же мы проходимся по этим лентам и выставляем в нужном нам порядке на конечный tape, и если мы бы это делали наивно, то у нас бы получилось, O(nk), где n - количество считанных элементов с изначальной tape, а k количество временных лент, поэтому я решил соптимизировать до O(nlogk), а именно создал heap благодаря библиотеке algorithm и после положил k элементов, и после на каждой итерации мы будем доставать и снова класть в heap элемент, так как наша куча всегда не будет превышать k -> logk на каждый запрос, который у нас n.
```
### Syntax
В config был добавлен параметр ram_size, который регулирует максимальный размер tape, по дефолту, если написать в файле 0, то выставлено значение, при котором вектор из int будет весить +- 100mb, также у config файла есть api
// API: "command <time_in_seconds>" после command требуется пробел.


