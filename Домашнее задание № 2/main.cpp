#include <iostream>

using namespace std;

// Task 1

class Person
{
protected:
    string name;
    unsigned short age;
    char gender;
    unsigned short weight;
public:
    static unsigned short count;

    Person() : name(""), age(0), gender('M'), weight(0) { count++; }
    Person(string setName, unsigned short setAge, char setGender, unsigned short setWeight)
    {
        set_name(setName);
        set_age(setAge);
        set_gender(setGender);
        set_weight(setWeight);
        count++;
    }

    void set_name(string setName) { name = setName; }
    void set_age(unsigned short setAge) { age = setAge; }
    void set_gender(char setGender) { gender = ((setGender == 'M' || setGender == 'F') ? setGender : 'N'); }
    void set_weight(unsigned short setWeight) { weight = setWeight; }
};

unsigned short Person::count = 0;

class Student : public Person
{
private:
    unsigned short year;
public:
    Student() : Person(), year(2022) {}
    Student(string setName, unsigned short setAge, char setGender, unsigned short setWeight, unsigned short setYear) :
            Person(setName, setAge, setGender, setWeight)
    {
        set_year(setYear);
    }

    void set_year(unsigned short setYear) { year = setYear; }
    void inc_year() { year++; }
    friend void print(Student&);
};

void print(Student& student)
{
    cout << "Name: " << student.name;
    cout << ", age: " << student.age;
    cout << ", gender: " << student.gender;
    cout << ", weight: " << student.weight;
    cout << ", year: " << student.year << endl;
}

// Task 2

class Fruit
{
protected:
    string name;
    string colour;
public:
    Fruit(string setName, string setColour) : name(setName), colour(setColour) {}

    string getName() const { return name; }
    string getColour() const { return colour; }
};

class Apple : public Fruit
{
public:
    Apple() : Fruit("apple", "green") {}
    Apple(string setColour) : Fruit("apple", setColour) {}
    Apple(string setName, string setColour) : Fruit(setName, setColour) {}
};

class Banana : public Fruit
{
public:
    Banana() : Fruit("banana", "yellow") {}
    Banana(string setColour) : Fruit("banana", setColour) {}
    Banana(string setName, string setColour) : Fruit(setName, setColour) {}
};

class GrannySmith : public Apple
{
public:
    GrannySmith() : Apple("Granny Smith apple", "green") {}
    GrannySmith(string setColour) : Apple("Granny Smith apple", setColour) {}
};

int main()
{
    // Task 1
    {
        cout << "Task 1" << endl;
        Student s1, s2("Stepan Razin", 25, 'M', 80, 2020), s3("Chelovek Zagadka", -3, 'J', -10, -2000);

        print(s1);
        print(s2);
        print(s3);

        s3.set_name("Artemis");
        s3.set_age(3000);
        s3.set_gender('F');
        s3.set_weight(55);
        s3.set_year(2021);
        s3.inc_year();

        print(s3);
        cout << "Object counter: " << Person::count << endl << endl;
    }

    // Task 2
    {
        cout << "Task 2" << endl;
        Apple a("red");
        Banana b;
        GrannySmith c;

        cout << "My " << a.getName() << " is " << a.getColour() << "." << endl;
        cout << "My " << b.getName() << " is " << b.getColour() << "." << endl;
        cout << "My " << c.getName() << " is " << c.getColour() << "." << endl << endl;
    }

    return 0;
}

// Task 3
/*
По-моему мнению, потребуются классы "Дилер (Крупье)" и наследованный от него "Игрок",
а также класс "Раунд", в котором и будет описана игра. Необходимо также сделать класс "Раунд"
дружественным к классам "Игрок" и "Дилер" для доступа к текущим наборам карт на руках участников
и добавления новых карт по ходу игры. Игровые правила должны быть описаны в классе "Раунд",
а состояние участников (доступный банк для ставок, текущая ставка и т. д.), их возможное поведение в игре
в соответствующих классах "Игрок" и "Дилер".
В классе "Дилер" должны присутствовать такие поля: "Набор карт", "Состояние"
("Блэк-джек", "Выиграл", "Проиграл", "В процессе"), "Имя", а также метод "Управление", принимающий решение
пользователя о доборе карты, остановке, страховке ставки (при определённом случае) и разделении руки (в определённом случае).
В классе "Игрок" помимо наследованных полей из класса "Дилер" должны быть поля "Банк" и "Текущая ставка";
методы: "Сделать ставку", устанавливающий размер ставки.
Класс "Раунд" будет содержать поля "Колода", из которой будут "раздаваться" карты, "Текущий игрок",
содержащий указатель на объект класса "Игрок", с которым у дилера происходит взаимодействие в данный момент, "Число игроков".
В классе также необходимо создать методы "Раздача", инициализирующий начальный набор карт и ставки игроков, "Выбор игрока", изменяющий
поле "Текущий игрок" и "Проверка", проверяющий состояние всех игроков (если отлично от "В процессе" хотя бы у одного игрока, то игра продолжается).
*/