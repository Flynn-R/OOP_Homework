#include <iostream>
#include <typeinfo>

using namespace std;

// Task 1
template<typename T, typename U> void div(T a, U b)
{
    try
    {
        cout << "The result of \"" << a << " / " << b << " is ";
        cout << (b == 0 ? throw 1 : static_cast<double>(a) / b) << endl;
    }
    catch(const int)
    {
        cerr << "error, because you can't divide by zero, silly!" << endl;
    }
    
}

// Task 2
class Ex
{
private:
    double x;
public:
    explicit Ex(double _x) : x(_x) {}
    friend ostream& operator<<(ostream&, const Ex&);
};

ostream& operator<<(ostream& out, const Ex& exc)
{
    out << exc.x;
    return out;
}

class Bar
{
private:
    double y;
public:
    Bar(double _y = 0) : y(_y) {}
    void set(double a)
    {
        if (y + a > 100)
            throw Ex(y * a);
        y = a;
    }
};

// Task 3
enum Directions
{
    UP, DOWN, RIGHT, LEFT
};

class IllegalCommand
{
private:
    int xPos;
    int yPos;
    string illegalCommand;
public:
    IllegalCommand(string input, int _x, int _y) : illegalCommand(input), xPos(_x), yPos(_y) {}
    friend ostream& operator<<(ostream&, IllegalCommand&);
};

ostream& operator<<(ostream& out, IllegalCommand& IC)
{
    out << "Current position: (" << IC.xPos << ", " << IC.yPos << ")" << endl;
    out << "Your input: " << IC.illegalCommand << endl;
    return out;
}

class OffTheField
{
private:
    int xPos;
    int yPos;
    Directions direction;
public:
    OffTheField(int _x, int _y, Directions _direction) : xPos(_x), yPos(_y), direction(_direction) {}
    friend ostream& operator<<(ostream&, OffTheField&);
};

ostream& operator<<(ostream& out, OffTheField& OF)
{
    out << "Current position: (" << OF.xPos << ", " << OF.yPos << ")" << endl;
    out << "Impossible move: ";
    switch (OF.direction)
    {
        case UP:
            out << "UP" << endl;
            break;
        case DOWN:
            out << "DOWN" << endl;
            break;
        case RIGHT:
            out << "RIGHT" << endl;
            break;
        case LEFT:
            out << "LEFT" << endl;
            break;
        default:;
    }
    return out;
}

class Robot
{
private:
    int xPos;
    int yPos;
    int field[10][10] { 0 };
public:
    Robot(int _x = 0, int _y = 0) : xPos(_x), yPos(_y) {}
    
    // Возвращаемый тип Robot& для возможных сцепленных вызовов
    Robot& move(Directions direction)
    {
        switch (direction)
        {
            case UP:
                if (xPos == 0)
                    throw OffTheField(getX(), getY(), direction);
                --xPos;
                break;
            case DOWN:
                if (xPos == 9)
                    throw OffTheField(getX(), getY(), direction);
                ++xPos;
                break;
            case RIGHT:
                if (yPos == 9)
                    throw OffTheField(getX(), getY(), direction);
                ++yPos;
                break;
            case LEFT:
                if (yPos == 0)
                    throw OffTheField(getX(), getY(), direction);
                --yPos;
                break;
            default:;
        }

        return *this;
    }

    void printField()
    {
        int i, j = 0;
        for (i = 0; i < xPos; ++i)
        {
            for (; j < 10; ++j)
                cout << "\t[]";
            cout << endl;
            j = 0;
        }

        for (j = 0; j < yPos; ++j)
            cout << "\t[]";
        cout << "\tX";
        ++j;

        for (; i < 10; ++i)
        {
            for (; j < 10; ++j)
                cout << "\t[]";
            cout << endl;
            j = 0;
        }
    }

    int getX() { return xPos; }
    int getY() { return yPos; }
};

int main()
{
    // Task 1
    {
        cout << "Task 1" << endl;

        int a1 = 25, b1 = 4;
        int a2 = 0;
        float b2 = 0;
        float a3 = 0, b3 = 4.5;
        float a4 = 66;
        double b4 = 1.1111;
        double a5 = 9.1234, b5 = 0.0;

        div<int, int>(a1, b1);
        div<int, float>(a2, b2);
        div<float, float>(a3, b3);
        div<float, double>(a4, b4);
        div<double, double>(a5, b5);

        cout << endl;
    }

    // Task 2
    {
        cout << "Task 2" << endl;

        Bar bar;

        int n;
        do
        {
            cout << "Enter a number: ";
            cin >> n;
            if (n != 0)
            {
                try
                {
                    bar.set(n);
                }
                catch (const Ex& exc)
                {
                    cerr << "Exception value: " << exc << endl;
                }    
            }
        } while (n != 0);

        cout << endl;
    }

    // Task 3
    {
        cout << "Task 3" << endl;

        const string up = "UP";
        const string down = "DOWN";
        const string right = "RIGHT";
        const string left = "LEFT";
        const string zero = "0";

        Robot robot;

        string input;
        do
        {
            robot.printField();
            cout << "Enter direction: ";
            getline(cin, input);
            system("cls");
            try
            {
                if (input != up && input != down && input != right && input != left && input != zero)
                    throw IllegalCommand(input, robot.getX(), robot.getY());
                
                if (input == up)
                    robot.move(UP);
                else if (input == down)
                    robot.move(DOWN);
                else if (input == right)
                    robot.move(RIGHT);
                else if (input == left)
                    robot.move(LEFT);
            }
            catch (IllegalCommand& IC)
            {
                cerr << "Illegal Command! " << endl << IC << endl;
            }
            catch (OffTheField& OF)
            {
                cerr << "Off the field! " << endl << OF << endl;
            }
        } while (input != zero);

        cout << endl;
    }

    return 0;
}
