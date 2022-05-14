#include <iostream>
#include <cstdint>

using namespace std;

// Task 1

class Power
{
private:
    float base;
    float power;
public:
    Power() : base(0), power(1) {}
    void set()
    {
        cout << "Enter the base: ";
        cin >> base;
        cout << "Enter the power: ";
        cin >> power;
    }
    float calculate()
    {
        float result = 1;
        if (power >= 0)
        {
            while (power != 0)
            {
                result *= base;
                power--;
            }
        }
        else
        {
            while (power != 0)
            {
                result /= base;
                power++;
            }
        }
        return result;
    }
};

// Task 2

class RGBA
{
private:
    uint8_t m_red, m_green, m_blue, m_alpha;
public:
    RGBA() : m_red(0), m_green(0), m_blue(0), m_alpha(255) {}
    RGBA(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) :
    m_red(red), m_green(green), m_blue(blue), m_alpha(alpha) {}

    void print()
    {
        cout << "Red:\t" << +m_red << endl;
        cout << "Green:\t" << +m_green << endl;
        cout << "Blue:\t" << +m_blue << endl;
        cout << "Alpha:\t" << +m_alpha << endl;
    }
};

// Task 3

class Stack
{
private:
    int array[10];
    uint8_t size;
public:
    Stack() { reset(); }

    void reset()
    {
        for (uint8_t i = 0; i < 10; ++i)
            array[i] = 0;
        size = 0;
    }

    bool push(int data)
    {
        if (size == 10)
        {
            cout << "The stack is full!" << endl;
            return false;
        }
        else
        {
            array[size++] = data;
            return true;
        }
    }

    void pop()
    {
        if (size != 0)
            array[--size] = 0;
        else
            cout << "The stack is empty!" << endl;
    }

    void print()
    {
        cout << "( ";
        for (uint8_t i = 0; i < size; ++i)
            cout << array[i] << " ";
        cout << ")" << endl;
    }
};

int main()
{
    // Task 1
    {
        cout << "Task 1" << endl;
        Power pow;
        pow.set();
        cout << "The result is " << pow.calculate() << endl << endl;
    }

    // Task 2
    {
        cout << "Task 2" << endl;
        RGBA colour_1;
        colour_1.print();
        RGBA colour_2(255, 255, 255, 0);
        colour_2.print();
        cout << endl;
    }

    // Task 3
    {
        cout << "Task 3" << endl;
        Stack stack;
        stack.reset();
        stack.print();

        stack.push(3);
        stack.push(7);
        stack.push(5);
        stack.print();

        stack.pop();
        stack.print();

        stack.pop();
        stack.pop();
        stack.print();
    }

    return 0;
}