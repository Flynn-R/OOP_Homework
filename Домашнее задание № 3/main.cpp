#include <iostream>

using namespace std;

// Task 1

class Figure
{
protected:
    int a, b;
public:
    Figure(int _a, int _b) : a(_a), b(_b) {}
    virtual void area() = 0;
};

class Circle : public Figure
{
private:
    int radius;
    static constexpr long double PI = 3.141592653589793;
public:
    Circle(int x, int y, int r) : Figure(x, y), radius(r) {}
    void area() override { cout << "Area of the circle: " <<  PI * radius * radius << endl; }
};

class Parallelogram : virtual public Figure
{
public:
    Parallelogram(int _a, int h) : Figure(_a, h) {}
    void area() override { cout << "Area of the parallelogram: " << a * b << endl; }
};

class Rectangle : public Parallelogram
{
public:
    Rectangle(int _a, int _b) : Parallelogram(_a, _b), Figure(_a, _b) {}
    void area() override { cout << "Area of the rectangle: " << a * b << endl; }
};

class Square : virtual public Parallelogram
{
public:
    explicit Square(int _a) : Parallelogram(_a, _a), Figure(_a, _a) {}
    void area() override { cout << "Area of the square: " << a * b << endl; }
};

class Rhombus : virtual public Parallelogram
{
public:
    Rhombus(int d1, int d2) : Parallelogram(d1, d2), Figure(d1, d2) {}
    void area() override { cout << "Area of the rhombus: " << static_cast<long double>(a * b) / 2 << endl; }
};

// Task 2

class Car
{
protected:
    string company;
    string model;
public:
    Car(string _company, string _model) : company(_company), model(_model)
    {
        cout << "Class Car: company - " << company << ", model - " << model << endl;
    }
};

class PassengerCar : virtual public Car
{
public:
    PassengerCar(string _company, string _model) : Car(_company, _model)
    {
        cout << "Class PassengerCar: company - " << company << ", model - " << model << endl;
    }
};

class Bus : virtual public Car
{
public:
    Bus(string _company, string _model) : Car(_company, _model)
    {
        cout << "Class Bus: company - " << company << ", model - " << model << endl;
    }
};

class Minivan : public PassengerCar, public Bus
{
public:
    Minivan(string _company, string _model) : Car(_company, _model),
    PassengerCar(_company, _model), Bus(_company, _model)
    {
        cout << "Class Minivan: company - " << company << ", model - " << model << endl;
    }
};

// Task 3

class Fraction
{
protected:
    int numerator, denominator;
public:
    Fraction(int _numerator, int _denominator)
    {
        if (_denominator <= 0)
            cout << "Error!" << endl;
        else
        {
            numerator = _numerator;
            denominator = _denominator;
        }
    }

    friend Fraction operator+(const Fraction&, const Fraction&);
    friend Fraction operator+(const Fraction&, int);
    friend float operator+(const Fraction&, float);

    friend Fraction operator-(const Fraction&, const Fraction&);
    friend Fraction operator-(const Fraction&, int);
    friend float operator-(const Fraction&, float);

    friend Fraction operator*(const Fraction&, const Fraction&);
    friend Fraction operator*(const Fraction&, int);
    friend float operator*(const Fraction&, float);

    friend Fraction operator/(const Fraction&, const Fraction&);
    friend Fraction operator/(const Fraction&, int);
    friend Fraction operator/(int, const Fraction&);
    friend float operator/(const Fraction&, float);
    friend float operator/(float fl, const Fraction& f);

    Fraction operator-() const
    {
        return { -numerator, denominator };
    }

    friend bool operator==(const Fraction&, const Fraction&);
    friend bool operator==(const Fraction&, int);
    friend bool operator==(const Fraction&, float);

    friend bool operator<(const Fraction&, const Fraction&);
    friend bool operator<(const Fraction&, int);
    friend bool operator<(int, const Fraction&);
    friend bool operator<(const Fraction&, float);
    friend bool operator<(float, const Fraction&);

    friend ostream& operator<<(ostream&, const Fraction&);
};

int gcd(int a, int b)
{
    int divisor;
    if (a == b) return a;

    int d = a - b;
    if (d < 0)
    {
        d = -d;
        divisor = gcd(a, d);
    }
    else
        divisor = gcd(b, d);
    return divisor;
}

int lcm(int a, int b)
{
    return abs(a * b) / gcd(a, b);
}

Fraction operator+(const Fraction& f1, const Fraction& f2)
{
    const int LCM = lcm(f1.denominator, f2.denominator);
    int resultNumerator = f1.numerator * LCM / f1.denominator + f2.numerator * LCM / f2.denominator;
    int GCD = gcd(abs(resultNumerator), LCM);
    return { resultNumerator / GCD, LCM / GCD };
}

Fraction operator+(const Fraction& f, const int i)
{
    const int LCM = f.denominator;
    int resultNumerator = f.numerator + LCM * i;
    int GCD = gcd(abs(resultNumerator), LCM);
    return { resultNumerator / GCD, LCM / GCD };
}

float operator+(const Fraction& f, const float fl)
{
    return fl + static_cast<float>(f.numerator) / static_cast<float>(f.denominator);
}

float operator+(float fl, const Fraction& f)
{
    return f + fl;
}

Fraction operator+(const int i, const Fraction& f)
{
    return f + i;
}

Fraction operator-(const Fraction& f1, const Fraction& f2)
{
    return f1 + (-f2);
}

Fraction operator-(const Fraction& f, const int i)
{
    return f + (-i);
}

Fraction operator-(const int i, const Fraction& f)
{
    return i + (-f);
}

float operator-(const Fraction& f, const float fl)
{
    return f + (-fl);
}

float operator-(const float fl, const Fraction& f)
{
    return fl + (-f);
}

Fraction operator*(const Fraction& f1, const Fraction& f2)
{
    int resultNumerator = f1.numerator * f2.numerator;
    int resultDenominator = f1.denominator * f2.denominator;
    int GCD = gcd(abs(resultNumerator), abs(resultDenominator));
    return { resultNumerator / GCD, resultDenominator / GCD };
}

Fraction operator*(const Fraction& f, const int i)
{
    int resultNumerator = f.numerator * i;
    int GCD = gcd(abs(resultNumerator), f.denominator);
    return { resultNumerator / GCD, f.denominator / GCD };
}

Fraction operator*(const int i, const Fraction& f)
{
    return f * i;
}

float operator*(const Fraction& f, const float fl)
{
    return (static_cast<float>(f.numerator) / static_cast<float>(f.denominator)) * fl;
}

float operator*(const float fl, const Fraction& f)
{
    return f * fl;
}

Fraction operator/(const Fraction& f1, const Fraction& f2)
{
    int resultNumerator = f1.numerator * f2.denominator;
    int resultDenominator = f1.denominator * f2.numerator;
    int GCD = gcd(abs(resultNumerator), abs(resultDenominator));
    return { resultNumerator / GCD, resultDenominator / GCD };
}

Fraction operator/(const Fraction& f, const int i)
{
    int resultDenominator = f.denominator * i;
    int GCD = gcd(f.numerator, abs(resultDenominator));
    return { f.numerator / GCD, resultDenominator / GCD };
}

Fraction operator/(const int i, const Fraction& f)
{
    int resultNumerator = f.denominator * i;
    int GCD = gcd(abs(resultNumerator), f.numerator);
    return { resultNumerator, f.numerator };
}

float operator/(const Fraction& f, const float fl)
{
    return (static_cast<float>(f.numerator) / static_cast<float>(f.denominator)) / fl;
}

float operator/(const float fl, const Fraction& f)
{
    return fl * (static_cast<float>(f.denominator) / static_cast<float>(f.numerator));
}

bool operator==(const Fraction& f1, const Fraction& f2)
{
    int LCM = lcm(f1.denominator, f2.denominator);
    return ((LCM / f1.denominator) * f1.numerator == (LCM / f2.denominator) * f2.numerator);
}

bool operator==(const Fraction& f, const int i)
{
    int LCM = f.denominator;
    return (f.numerator == LCM * i);
}

bool operator==(const int i, const Fraction& f)
{
    return f == i;
}

bool operator==(const Fraction& f, const float fl)
{
    // Практически невозможно сравнить числа с плавающей точкой на равенство
    return (static_cast<float>(f.numerator) / static_cast<float>(f.denominator) == fl);
}

bool operator==(const float fl, const Fraction& f)
{
    // Практически невозможно сравнить числа с плавающей точкой на равенство
    return f == fl;
}

bool operator!=(const Fraction& f1, const Fraction& f2)
{
    return !(f1 == f2);
}

bool operator!=(const Fraction& f, const int i)
{
    return !(f == i);
}

bool operator!=(const int i, const Fraction& f)
{
    return f != i;
}

bool operator!=(const Fraction& f, const float fl)
{
    // Практически невозможно сравнить числа с плавающей точкой на неравенство
    return !(f == fl);
}

bool operator!=(const float fl, const Fraction& f)
{
    // Практически невозможно сравнить числа с плавающей точкой на неравенство
    return f != fl;
}

bool operator<(const Fraction& f1, const Fraction& f2)
{
    int LCM = lcm(f1.denominator, f2.denominator);
    return ((LCM / f1.denominator) * f1.numerator < (LCM / f2.denominator) * f2.numerator);
}

bool operator<(const Fraction& f, const int i)
{
    int LCM = f.denominator;
    return (f.numerator < LCM * i);
}

bool operator<(const int i, const Fraction& f)
{
    int LCM = f.denominator;
    return (LCM * i < f.numerator);
}

bool operator<(const Fraction& f, const float fl)
{
    // Не всегда удаётся верно сравнить числа с плавающей точкой
    return (static_cast<float>(f.numerator) / static_cast<float>(f.denominator) < fl);
}

bool operator<(const float fl, const Fraction& f)
{
    // Не всегда удаётся верно сравнить числа с плавающей точкой
    return fl < static_cast<float>(f.numerator) / static_cast<float>(f.denominator);
}

bool operator>(const Fraction& f1, const Fraction& f2)
{
    return f2 < f1;
}

bool operator>(const Fraction& f, const int i)
{
    return i < f;
}

bool operator>(const int i, const Fraction& f)
{
    return f < i;
}

bool operator>(const Fraction& f, const float fl)
{
    // Не всегда удаётся верно сравнить числа с плавающей точкой
    return fl < f;
}

bool operator>(const float fl, const Fraction& f)
{
    // Не всегда удаётся верно сравнить числа с плавающей точкой
    return f < fl;
}

bool operator<=(const Fraction& f1, const Fraction& f2)
{
    return !(f1 > f2);
}

bool operator<=(const Fraction& f, const int i)
{
    return !(f > i);
}

bool operator<=(const int i, const Fraction& f)
{
    return !(i > f);
}

bool operator<=(const Fraction& f, const float fl)
{
    return !(f > fl);
}

bool operator<=(const float fl, const Fraction& f)
{
    return !(fl > f);
}

bool operator>=(const Fraction& f1, const Fraction& f2)
{
    return !(f1 < f2);
}

bool operator>=(const Fraction& f, const int i)
{
    return !(f < i);
}

bool operator>=(const int i, const Fraction& f)
{
    return !(i < f);
}

bool operator>=(const Fraction& f, const float fl)
{
    return !(f < fl);
}

bool operator>=(const float fl, const Fraction& f)
{
    return !(fl < f);
}

ostream& operator<<(ostream& c_out, const Fraction& f)
{
    c_out << f.numerator << "/" << f.denominator;
    return c_out;
}

void test(const Fraction& f1, const Fraction& f2)
{
    cout << "3/7 + 9/2 = " << f1 + f2 << endl;
    cout << "3/7 + 2 = " << f1 + 2 << endl;
    cout << "3/7 + 2.0 = " << f1 + 2.0f << endl;
    cout << "2 + 9/2 = " << 2 + f2 << endl;
    cout << "2.0 + 9/2 = " << 2.0f + f2 << endl << endl;

    cout << "3/7 - 9/2 = " << f1 - f2 << endl;
    cout << "3/7 - 2 = " << f1 - 2 << endl;
    cout << "3/7 - 2.0 = " << f1 - 2.0f << endl;
    cout << "2 - 9/2 = " << 2 - f2 << endl;
    cout << "2.0 - 9/2 = " << 2.0f - f2 << endl << endl;

    cout << "3/7 * 9/2 = " << f1 * f2 << endl;
    cout << "3/7 * 2 = " << f1 * 2 << endl;
    cout << "3/7 * 2.0 = " << f1 * 2.0f << endl;
    cout << "2 * 9/2 = " << 2 * f2 << endl;
    cout << "2.0 * 9/2 = " << 2.0f * f2 << endl << endl;

    cout << "3/7 / 9/2 = " << f1 / f2 << endl;
    cout << "3/7 / 2 = " << f1 / 2 << endl;
    cout << "3/7 / 2.0 = " << f1 / 2.0f << endl;
    cout << "2 / 9/2 = " << 2 / f2 << endl;
    cout << "2.0 / 9/2 = " << 2.0f / f2 << endl << endl;

    cout << "-(3/7) = " << -f1 << endl;
    cout << "-(9/2) = " << -f2 << endl << endl;

    cout << "3/7 == 9/2 = " << ((f1 == f2) ? "true" : "false") << endl;
    cout << "3/7 == 2 = " << ((f1 == 2) ? "true" : "false") << endl;
    cout << "3/7 == 2.0 = " << ((f1 == 2.0f) ? "true" : "false") << endl;
    cout << "2 == 9/2 = " << ((2 == f2) ? "true" : "false") << endl;
    cout << "2.0 == 9/2 = " << ((2.0f == f2) ? "true" : "false") << endl << endl;

    cout << "3/7 != 9/2 = " << ((f1 != f2) ? "true" : "false") << endl;
    cout << "3/7 != 2 = " << ((f1 != 2) ? "true" : "false") << endl;
    cout << "3/7 != 2.0 = " << ((f1 != 2.0f) ? "true" : "false") << endl;
    cout << "2 != 9/2 = " << ((2 != f2) ? "true" : "false") << endl;
    cout << "2.0 != 9/2 = " << ((2.0f != f2) ? "true" : "false") << endl << endl;

    cout << "3/7 < 9/2 = " << ((f1 < f2) ? "true" : "false") << endl;
    cout << "3/7 < 2 = " << ((f1 < 2) ? "true" : "false") << endl;
    cout << "3/7 < 2.0 = " << ((f1 < 2.0f) ? "true" : "false") << endl;
    cout << "2 < 9/2 = " << ((2 < f2) ? "true" : "false") << endl;
    cout << "2.0 < 9/2 = " << ((2.0f < f2) ? "true" : "false") << endl << endl;

    cout << "3/7 > 9/2 = " << ((f1 > f2) ? "true" : "false") << endl;
    cout << "3/7 > 2 = " << ((f1 > 2) ? "true" : "false") << endl;
    cout << "3/7 > 2.0 = " << ((f1 > 2.0f) ? "true" : "false") << endl;
    cout << "2 > 9/2 = " << ((2 > f2) ? "true" : "false") << endl;
    cout << "2.0 > 9/2 = " << ((2.0f > f2) ? "true" : "false") << endl << endl;

    cout << "3/7 <= 9/2 = " << ((f1 <= f2) ? "true" : "false") << endl;
    cout << "3/7 <= 2 = " << ((f1 <= 2) ? "true" : "false") << endl;
    cout << "3/7 <= 2.0 = " << ((f1 <= 2.0f) ? "true" : "false") << endl;
    cout << "2 <= 9/2 = " << ((2 <= f2) ? "true" : "false") << endl;
    cout << "2.0 <= 9/2 = " << ((2.0f <= f2) ? "true" : "false") << endl << endl;

    cout << "3/7 >= 9/2 = " << ((f1 >= f2) ? "true" : "false") << endl;
    cout << "3/7 >= 2 = " << ((f1 >= 2) ? "true" : "false") << endl;
    cout << "3/7 >= 2.0 = " << ((f1 >= 2.0f) ? "true" : "false") << endl;
    cout << "2 >= 9/2 = " << ((2 >= f2) ? "true" : "false") << endl;
    cout << "2.0 >= 9/2 = " << ((2.0f >= f2) ? "true" : "false") << endl << endl;
}

// Task 4

enum Suit
{
    Heart, Spade, Diamond, Club
};

enum Value
{
    Two = 2, Three = 3, Four = 4, Five = 5, Six = 6, Seven = 7,
    Eight = 8, Nine = 9, Ten = 10, Jack = 10, Queen = 10, King = 10, Ace = 1
};

class Card
{
protected:
    Suit cardSuit;
    Value cardValue;
    bool cardPosition;
public:
    Card(Suit suit, Value value, bool position = false) : cardSuit(suit), cardValue(value), cardPosition(position) {}
    bool flip() { cardPosition = !cardPosition; return cardPosition; }
    Value getValue() { return cardValue; }
};

int main()
{
    // Task 1
    {
        cout << "Task 1" << endl;
        auto* parallelogram = new Parallelogram(5, 3);
        parallelogram->area();
        Parallelogram* rectangle = new Rectangle(5, 4);
        rectangle->area();
        Parallelogram* square = new Square(5);
        square->area();
        Parallelogram* rhombus = new Rhombus(5, 2);
        rhombus->area();
        auto* circle = new Circle(0, 0, 5);
        circle->area();

        delete circle;
        delete rhombus;
        delete square;
        delete rectangle;
        delete parallelogram;
        cout << endl;
    }

    // Task 2
    {
        cout << "Task 2" << endl;
        auto* car = new Car("Audi", "TT");
        cout << endl;
        auto* passengerCar = new PassengerCar("BMW", "E38");
        cout << endl;
        auto* bus = new Bus("Icarus", "Tsoi");
        cout << endl;
        auto* minivan = new Minivan("Volkswagen", "T1");
        cout << endl << endl;

        delete minivan;
        delete bus;
        delete passengerCar;
        delete car;
    }

    // Task 3
    {
        cout << "Task 3" << endl;
        Fraction f1(3, 7), f2(9, 2);
        test(f1, f2);

        cout << endl;
    }

    // Task 4
    {
        cout << "Task 4" << endl;
        Card heartJack(Heart, Jack), spade2(Spade, Two);
        cout << heartJack.getValue() << " flip up " << heartJack.flip() << " flip down " << heartJack.flip() << endl;
        cout << spade2.getValue() << " flip up " << spade2.flip() << " flip down " << spade2.flip() << endl << endl;
    }

    return 0;
}