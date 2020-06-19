# AStar
В данном проекте приведены реализации алгоритмов A*, WA* и Дейкстры.
# Сборка
Для сборки проекта можно использовать qmake с помощью файла Makefile. Также файлы могут быть открыты и скомпилированы в Qt Creator с помощью файлов проекта и файла с расширением .pro.
# Входнне данные
* Mode:  A*, WA* и Дейкстры, задаются с помощью их первой буквы: "A", "W", "D". По умолчанию используется алгоримт Дейкстры, т.е. если ввести любое другое обозначение, именно он будет применен.
* Heuristic function: Euclidean, Manhatan и Chevyshev доступны для A* и WA*, задаются с помощью первых букв соответственно "E", "M", "C". По умолчанию используется евклидово расстояние.
* Epsilon > 1: доступен только для WA*.
* Имя файла с расшиерением (test.txt) для ввода карты. 0-проходимый элемент, 1-препяствие. Любое другое обозначение считается проходимым элементом.
* Start: точка старта.
* End: точка финиша.
# РЕЗУЛЬТАТЫ
Если путь найден и точки старта и финиша заданы правильно, то программа выводит на экран карту местности вместе с пройденным путем. А также, последовательность смежных проходимых элементов.
