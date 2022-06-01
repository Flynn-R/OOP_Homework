#include <iostream>
#include <vector>

using namespace std;

// Task1
template<typename T> class Pair1
{
private:
    T f;
    T s;
public:
    Pair1(T _f, T _s) : f(_f), s(_s) {}
    T first() const { return f; }
    T second() const { return s; }
};

// Task 2
template<typename T, typename U> class Pair
{
private:
    T f;
    U s;
public:
    Pair(T _f, U _s) : f(_f), s(_s) {}
    T first() const { return f; }
    U second() const { return s; }
};

// Task 3
template<typename T> class Pair<string, T>
{
protected:
    string f;
    T s;
public:
    Pair(string _f, T _s) : f(_f), s(_s) {}
    string first() const { return f; }
    T second() const { return s; }
};

template<typename T> class StringValuePair : public Pair<string, T>
{
public:
    StringValuePair(string _f, T _s) : Pair<string, T>(_f, _s) {}
};

// Task 4
class Card
{
public:
    enum Suit
    {
        Heart, Spade, Diamond, Club
    };
    enum Value
    {
        Two = 2, Three = 3, Four = 4, Five = 5, Six = 6, Seven = 7,
        Eight = 8, Nine = 9, Ten = 10, Jack = 10, Queen = 10, King = 10, Ace = 1
    };
    Card(Suit suit, Value value, bool position = true) : cardSuit(suit), cardValue(value), isFaceUp(position) {}
    void flip() { isFaceUp = !isFaceUp; }
    Value getValue() { return cardValue; }
    bool isFaceUp;
private:
    Suit cardSuit;
    Value cardValue;
};

class Hand
{
private:
    vector<Card*> cards;
public:
    void Add(Card* card) { cards.push_back(card); }
    void Clear() { cards.clear(); }
    
    int GetValue()
    {
        int sum = 0;
        int aceCount = 0;
        for (int i = 0; i < cards.size(); i++)
        {
            if (cards[i]->isFaceUp)
            {
                sum += cards[i]->getValue();
                if (cards[i]->getValue() == Card::Ace)
                    aceCount++;
            }
        }

        if (aceCount > 0)
        {
            while (aceCount != 0)
            {
                if (sum + 10 <= 21)
                {
                    sum += 10;
                    aceCount--;
                }
                else
                    aceCount = 0;
            }
        }

        return sum;
    }
};

class GenericPlayer : public Hand
{
private:
    string name;
public:
    virtual bool IsHitting() = 0;
    bool IsBoosted() { return ((GetValue() > 21) ? true : false); }
    void Bust() { if (IsBoosted()) cout << name << " is busted!" << endl; }
};

int main()
{
    // Task 1
    {
        cout << "Task 1" << endl;

        Pair1<int> p1(6, 9);
        cout << "Pair: " << p1.first() << ' ' << p1.second() << '\n';
        const Pair1<double> p2(3.4, 7.8);
        cout << "Pair: " << p2.first() << ' ' << p2.second() << '\n';
        
        cout << endl;
    }

    // Task 2
    {
        cout << "Task 2" << endl;

        Pair<int, double> p1(6, 7.8);
        cout << "Pair: " << p1.first() << ' ' << p1.second() << '\n';
        const Pair<double, int> p2(3.4, 5);
        cout << "Pair: " << p2.first() << ' ' << p2.second() << '\n';

        cout << endl;
    }

    // Task 3
    {
        cout << "Task 3" << endl;

        StringValuePair<int> svp("Amazing", 7);
        cout << "Pair: " << svp.first() << ' ' << svp.second() << '\n';

        cout << endl;
    }

    return 0;
}