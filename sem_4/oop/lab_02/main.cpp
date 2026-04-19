#include "Set.h"
#include "Exceptions.h"

#include <iostream>
#include <ranges>
#include <vector>

void test_constructor()
{
    std::cout << "======= ------------ =======" << std::endl;
    std::cout << "======= Конструкторы =======" << std::endl;

    // 1) Без параметров
    Set<int> s1;
    s1.add(1);
    s1.add(2);
    s1.add(3);
    std::cout << "1) Без параметров – " << s1 << std::endl;

    // 2) Из массива
    int *arr = new int[5]{ 1, 2, 3, 4, 5 };
    Set<int> s2(5, arr);
    std::cout << "2) Из массива – " << s2 << std::endl;
    delete[] arr;

    // 3) Из списка инициализации
    Set<int> s3{ 1, 2, 3, 4 };
    std::cout << "3) Из списка инициализации – " << s3 << std::endl;

    // 4) Копирование
    Set<int> s4(s3);
    std::cout << "4) Копирование – " << s4 << std::endl;

    // 5) Перенос
    Set<int> tmp{ 1, 2, 3, 4 };
    Set<int> s5(std::move(tmp));
    std::cout << "5) Перенос – " << s5 << std::endl;

    // 6) Итераторы
    Set<int> s6(s5.begin(), s5.end());
    std::cout << "6) Итераторы – " << s6 << std::endl;

    // 7) Из контейнера
    std::vector<int> v{ 1, 2, 3, 4, 2, 4, 1 };
    Set<int> s7(v);
    std::cout << "7) Из контейнера vector – " << s7 << std::endl;

    std::cout << "======= ------------ =======\n" << std::endl;
}

void test_assign()
{
    std::cout << "======= ------------ =======" << std::endl;
    std::cout << "======= Присваивание =======" << std::endl;

    // 1) Другого множества
    Set<int> s1, s2{ 1, 2, 3, 4 };
    std::cout << "1) Другого множества. До " << s1 << ". После ";
    s1 = s2;
    std::cout << s1 << std::endl;

    // 2) Переносом
    Set<int> s3;
    std::cout << "2) Переносом. До " << s3 << ". После ";
    s3 = std::move(s2);
    std::cout << s3 << std::endl;

    // 3) Список инициализаторов
    Set<int> s4;
    std::cout << "3) Список инициализаторов. До " << s4 << ". После ";
    s4 = { 1, 2, 3, 4 };
    std::cout << s4 << std::endl;

    // 4) Последовательное присваивание
    Set<int> s5;
    std::cout << "4) Последовательное присваивание\nДо:\n\ts1: " << s1 << "\n\ts2: " << s2 << "\n\ts5: " << s5
        << std::endl;
    s1 = s2 = s5 = { 1, 2, 3, 4 };
    std::cout << "После\n\ts1: " << s1 << "\n\ts2: " << s2 << "\n\ts5: " << s5 << std::endl;
    std::cout << "======= ------------ =======\n" << std::endl;
}

void test_add()
{
    std::cout << "======= ------------ =======" << std::endl;
    std::cout << "=======  Добавление  =======" << std::endl;

    Set<int> s1, s2;

    std::cout << "Изначальное множество:\n" << "\ts1: " << s1 << "\n\ts2: " << s2 << std::endl;

    // 1) Добавление в пустое множество
    s1.add(3);
    s2.add(Set<int> {1, 2, 3});
    std::cout << "1) Добавление в пустое множество" << std::endl;
    std::cout << "\tДобавлен элемент 3 в s1: " << s1 << std::endl;
    std::cout << "\tДобавлено множество {1, 2, 3} в s2: " << s2 << std::endl;

    // 2) Добавление в непустое
    s1.add(7);
    s2.add(Set<int> {5, 6, 7});
    std::cout << "2) Добавление в непустое множество" << std::endl;
    std::cout << "\tДобавлен элемент 7 в s1: " << s1 << std::endl;
    std::cout << "\tДобавлено множество {5, 6, 7} в s2: " << s2 << std::endl;

    // 3) Добавление в непустое значения которое уже есть в множестве
    s1.add(3);
    s2.add(Set<int> {2, 5, 10});
    std::cout << "3) Добавление в непустое множество, элементов которые уже есть" << std::endl;
    std::cout << "\tДобавлен элемент 3 в s1: " << s1 << std::endl;
    std::cout << "\tДобавлено множество {2, 5, 10} в s2: " << s2 << std::endl;

    std::cout << "======= ------------ =======\n" << std::endl;
}

void test_erase()
{
    std::cout << "======= ------------ =======" << std::endl;
    std::cout << "=======   Удаление   =======" << std::endl;

    Set<int> s = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    std::cout << "Исходное множества s: " << s << std::endl;

    // 1) удаление произвольного элемента
    std::cout << "1) удаление произвольного элемента (4)" << std::endl;
    s.erase(4);
    std::cout << "\ts: " << s << std::endl;

    // 2) удаление первого элемента
    std::cout << "2) удаление 'первого' элемента (9)" << std::endl;
    s.erase(9);
    std::cout << "\ts: " << s << std::endl;

    // 3) удаление последнего элемента
    std::cout << "3) удаление 'последнего' элемента (1)" << std::endl;
    s.erase(1);
    std::cout << "\ts: " << s << std::endl;

    // 4) удаление по элементам контейнера
    std::cout << "4) удаление по элементам множества {8, 6, 5, 2}" << std::endl;
    s.erase(Set<int>{8, 6, 5, 2});
    std::cout << "\ts: " << s << std::endl;

    std::cout << "======= ------------ =======\n" << std::endl;
}

void test_clear()
{
    std::cout << "======= ------------ =======" << std::endl;
    std::cout << "=======    Очистка   =======" << std::endl;

    Set<int> s = {1, 2, 3, 4};
    // 1) Очистка множества
    std::cout << "1) Очистка не пустого множества: " << s << std::endl;
    s.clear();
    std::cout << "\ts: " << s << std::endl;

    // 2) Очистка пустого множества
    std::cout << "2) Очистка пустого множества: " << s << std::endl;
    s.clear();
    std::cout << "\ts: " << s << std::endl;

    std::cout << "======= ------------ =======\n" << std::endl;
}

void test_unite()
{
    std::cout << "======= ------------ =======" << std::endl;
    std::cout << "======= Объединение  =======" << std::endl;

    Set<int> s1{1, 2, 3, 4, 5}, s2{4, 5, 6, 7,}, s3;
    std::cout << "Исходные множества:\n" << "\ts1: " << s1 << "\n\ts2: " << s2 << std::endl;

    // 1) Объединение множеств (создание нового)
    std::cout << "1) Объединение множеств (создание нового)" << std::endl;
    s3 = s1 | s2;
    std::cout << "\ts1 | s2: " << s3 << std::endl;

    s3 = s1 + s2;
    std::cout << "\ts1 + s2: " << s3 << std::endl;

    s3 = s1.unite(s2);
    std::cout << "\ts1.unite(s2): " << s3 << std::endl;

    // 2) Объединение множеств (изменение старого)
    std::cout << "2) Объединение множеств (изменение старого)" << std::endl;
    s3 = s1;
    s3 |= s2;
    std::cout << "\ts3 |= s2: " << s3 << std::endl;

    s3 = s1;
    s3 += s2;
    std::cout << "\ts3 += s2: " << s3 << std::endl;

    s3 = s1;
    s3.unite_update(s2);
    std::cout << "\ts3.unite_update(s2): " << s3 << std::endl;

    // 3) последовательное объединение
    std::cout << "3) Последовательное объединение {1, 2} | {3, 4} | {1, 4}" << std::endl;
    Set<int> s4{1, 2}, s5{3 ,4}, s6{1, 4}, s7 = s4 | s5 | s6;
    std::cout << "\t" << s7 << std::endl;

    std::cout << "======= ------------ =======\n" << std::endl;
}

void test_intersect()
{
    std::cout << "======= ------------ =======" << std::endl;
    std::cout << "======= Пересечение  =======" << std::endl;

    Set<int> s1{1, 2, 3, 4, 5}, s2{4, 5, 6, 7,}, s3;
    std::cout << "Исходные множества:\n" << "\ts1: " << s1 << "\n\ts2: " << s2 << std::endl;

    // 1) Пересечение множеств (создание нового)
    std::cout << "1) Пересечение множеств (создание нового)" << std::endl;
    s3 = s1 & s2;
    std::cout << "\ts1 & s2: " << s3 << std::endl;

    s3 = s1.intersect(s2);
    std::cout << "\ts1.intersect(s2): " << s3 << std::endl;

    // 2) Пересечение множеств (изменение старого)
    std::cout << "2) Пересечение множеств (изменение старого)" << std::endl;
    s3 = s1;
    s3 &= s2;
    std::cout << "\ts3 &= s2: " << s3 << std::endl;

    s3 = s1;
    s3.intersect_update(s2);
    std::cout << "\ts3.intersect_update(s2): " << s3 << std::endl;

    // 3) Последовательное пересечение
    std::cout << "3) Последовательное пересечение {1, 2, 4, 6} & {3, 4, 2, 10} & {1, 4, 2}" << std::endl;
    Set<int> s4{1, 2, 4, 6}, s5{3 ,4, 2, 10}, s6{1, 4, 2}, s7 = s4 & s5 & s6;
    std::cout << "\t" << s7 << std::endl;

    std::cout << "======= ------------ =======\n" << std::endl;
}

void test_diff()
{
    std::cout << "======= ------------ =======" << std::endl;
    std::cout << "=======  Вычитание   =======" << std::endl;

    Set<int> s1{ 1, 2, 3, 4 }, s2{ 3, 4, 5, 6 }, s3 {5, 6, 7, 8}, s4;
    std::cout << "Исходные множества:\n" << "\ts1: " << s1 << "\n\ts2: " << s2 << "\n\ts3: " << s3 << std::endl;

    // 1) вычитание множества из множества ()
    std::cout << "1) Есть пересечение" << std::endl;
    s4 = s1 - s2;
    std::cout << "\ts1 - s2: " << s4 << std::endl;
    s4 = s1;
    s4 -= s2;
    std::cout << "\ts1 -= s2: " << s4 << std::endl;

    // 2) вычитание множества из множества (нет пересечения)
    std::cout << "2) Нет пересечение" << std::endl;
    s4 = s1 - s3;
    std::cout << "\ts1 - s3: " << s4 << std::endl;
    s4 = s1;
    s4 -= s3;
    std::cout << "\ts1 -= s3: " << s4 << std::endl;
    // 3) вычитание множества из множества (одинаковые множества)
    std::cout << "3) Одинаковые множества" << std::endl;
    s4 = s1 - s1;
    std::cout << "\ts1 - s1: " << s4 << std::endl;
    s4 = s1;
    s4 -= s1;
    std::cout << "\ts1 -= s1: " << s4 << std::endl;

    std::cout << "======= ------------ =======\n" << std::endl;
}

void test_symm_diff()
{
    std::cout << "======= ------------- =======" << std::endl;
    std::cout << "======= Сим.вычитание =======" << std::endl;

    Set<int> s1{ 1, 2, 3, 4 }, s2{ 3, 4, 5, 6 }, s3 {5, 6, 7, 8}, s4;
    std::cout << "Исходные множества:\n" << "\ts1: " << s1 << "\n\ts2: " << s2 << "\n\ts3: " << s3 << std::endl;

    // 1) вычитание множества из множества ()
    std::cout << "1) Есть пересечение" << std::endl;
    s4 = s1 ^ s2;
    std::cout << "\ts1 ^ s2: " << s4 << std::endl;
    s4 = s1;
    s4 ^= s2;
    std::cout << "\ts1 ^= s2: " << s4 << std::endl;

    // 2) вычитание множества из множества (нет пересечения)
    std::cout << "2) Нет пересечение" << std::endl;
    s4 = s1 ^ s3;
    std::cout << "\ts1 ^ s3: " << s4 << std::endl;
    s4 = s1;
    s4 ^= s3;
    std::cout << "\ts1 ^= s3: " << s4 << std::endl;
    // 3) вычитание множества из множества (одинаковые множества)
    std::cout << "3) Одинаковые множества" << std::endl;
    s4 = s1 ^ s1;
    std::cout << "\ts1 ^ s1: " << s4 << std::endl;
    s4 = s1;
    s4 ^= s1;
    std::cout << "\ts1 ^= s1: " << s4 << std::endl;

    std::cout << "======= ------------ =======\n" << std::endl;
}

void test_relation()
{
    std::cout << "======= -------------- =======" << std::endl;
    std::cout << "======= Отношения мн-в =======" << std::endl;

    Set<int> s1 {1, 2, 3, 4, 5}, s2 {2, 5}, s3 = s1, s4{10, 11};
    // 1) Подмножества
    std::cout << "1) Подмножество" << std::endl;
    std::cout << "s2: " << s2 << " – подмножества s1: " << s1 << "\n";
    std::cout << "\ts2.subset_of(s1): " << (s2.subset_of(s1) ? "Да" : "Нет") << std::endl;
    std::cout << "s4: " << s4 << " – подмножества s1: " << s1 << "\n";
    std::cout << "\ts4.subset_of(s1): " << (s4.subset_of(s1) ? "Да" : "Нет") << std::endl;
    // 2) Надмножества
    std::cout << "2) Надмножества" << std::endl;
    std::cout << "s1: " << s1 << " – надмножества s2: " << s2 << "\n";
    std::cout << "\ts1.superset_of(s2): " << (s1.superset_of(s2) ? "Да" : "Нет") << std::endl;
    // 3) Равные
    std::cout << "3) Равенство" << std::endl;
    std::cout << "s1: " << s1 << " – равно s3: " << s3 << "\n";
    std::cout << "\ts1.equal(s3): " << (s1.equal(s3) ? "Да" : "Нет") << std::endl;
    std::cout << "\ts1 == s3: " << (s1 == s3 ? "Да" : "Нет") << std::endl;
    // 4) Неравные
    std::cout << "4) Неравенство" << std::endl;
    std::cout << "s1: " << s1 << " – равно s2: " << s2 << "\n";
    std::cout << "\ts1.equal(s2): " << (s1.not_equal(s2) ? "Да" : "Нет") << std::endl;
    std::cout << "\ts1 == s2: " << (s1 != s2 ? "Да" : "Нет") << std::endl;

    std::cout << "======= -------------- =======\n" << std::endl;
}

void test_exceptions()
{
    std::cout << "======= ------------ =======" << std::endl;
    std::cout << "=======  Исключения  =======" << std::endl;

    // 1) Конструктор из массива — nullptr
    std::cout << "1) Set(size, nullptr)" << std::endl;
    try
    {
        Set<int> s(5, static_cast<int *>(nullptr));
    }
    catch (const SetArrayNullptrException &ex)
    {
        std::cout << "\tПойман SetArrayNullptrException: " << ex.what() << std::endl;
    }

    // 2) Конструктор из массива — size = 0
    std::cout << "2) Set(0, array)" << std::endl;
    try
    {
        int arr[] = {1, 2, 3};
        Set<int> s(0, arr);
    }
    catch (const SetArrayZeroSizeException &ex)
    {
        std::cout << "\tПойман SetArrayZeroSizeException: " << ex.what() << std::endl;
    }

    // 3) Разыменование невалидного итератора
    std::cout << "3) *iterator после удаления элемента" << std::endl;
    try
    {
        Set<int> s{1, 2, 3};
        auto it = s.begin();
        s.clear();
        auto val = *it;
        std::cout << "\tНе должно дойти сюда: " << val << std::endl;
    }
    catch (const IteratorPointerExpiredException &ex)
    {
        std::cout << "\tПойман IteratorPointerExpiredException: " << ex.what() << std::endl;
    }

    std::cout << "======= ------------ =======\n" << std::endl;
}

int main()
{
    static_assert(std::forward_iterator<SetConstIterator<int> >);

    static_assert(Container<Set<int>>);
    static_assert(Container<std::vector<int> >);

    // test_constructor();
    // test_assign();
    // test_add();
    // test_erase();
    // test_clear();
    // test_unite();
    // test_intersect();
    // test_diff();
    // test_symm_diff();
    // test_relation();
    // test_exceptions();


    Set<int> a = { 1, 2, 3};
    Set<double> b = { 2.0, 5.3, 7.0 };
    std::vector<int> v{ 3, 4, 5 };
    auto c = a | b;
    auto d = v | a;

    std::cout << c << std::endl;
    std::cout << d << std::endl;

    // std::cout << typeid(c).name() << std::endl;
    // std::cout << typeid(a).name();
}
