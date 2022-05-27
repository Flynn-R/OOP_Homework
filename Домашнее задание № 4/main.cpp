#include <iostream>
#include <cassert>
#include <vector>

using namespace std;

// Task 1
class ArrayInt
{
private:
    int m_length;
    int *m_data;
public:
    ArrayInt(): m_length(0), m_data(nullptr) {}
    ArrayInt(int length) : m_length(length)
    {
        assert(length >= 0);
        if (length > 0)
            m_data = new int[length];
        else
            m_data = nullptr;
    }

    void erase()
    {
        delete[] m_data;
        m_data = nullptr;
        m_length = 0;
    }

    int getLength() { return m_length; }

    int& operator[](int index)
    {
        assert(index >= 0 && index < m_length);
        return m_data[index];
    }

    void resize(int newLength)
    {
        if (newLength == m_length)
        return;

        if (newLength <= 0)
        {
            erase();
            return;
        }

        int *data = new int[newLength];
        if (m_length > 0)
        {
            int elementsToCopy = (newLength > m_length) ? m_length : newLength;
            for (int index=0; index < elementsToCopy ; ++index)
                data[index] = m_data[index];
        }
        
        delete[] m_data;
        m_data = data;
        m_length = newLength;
    }

    void insertBefore(int value, int index)
    {
        assert(index >= 0 && index <= m_length);
        int *data = new int[m_length+1];
        for (int before=0; before < index; ++before)
            data[before] = m_data[before];
        
        data [index] = value;
        
        for (int after = index; after < m_length; ++after)
            data[after + 1] = m_data[after];
        
        delete[] m_data;
        m_data = data;
        ++m_length;
    }

    void pop_back()
    {
        assert(m_length > 0);
        resize(m_length - 1);
    }

    void pop_front()
    {
        assert(m_length > 0);
        for (int i = 0; i < m_length - 1; i++)
            m_data[i] = m_data[i + 1];
        resize(m_length - 1);
    }

    void insertionSort(bool isAscending)
    {
        int i, j, temp;
    
        for (i = 1; i < m_length; i++)
        {
            temp = m_data[i];
            for (j = i - 1; j >= 0; j--)
            {
                if (isAscending)
                {
                    if (m_data[j] < temp)
                        break;
                }
                else
                    if (m_data[j] > temp)
                        break;
  
                m_data[j + 1] = m_data[j];
                m_data[j] = temp;
            }
        }
    }

    void printArr()
    {
        for (int i = 0; i < m_length; i++)
            cout << m_data[i] << " ";
        cout << endl;
    }

    ~ArrayInt() { delete[] m_data; }
};

// Task 2
class Vector
{
private:
    vector<int> v;
public:
    Vector() { v.resize(0); }
    Vector(int size) { v.resize(size); }

    void fill()
    {
        for (int i = 0; i < v.size(); i++)
            v[i] = rand() % 10;
    }

    void print()
    {
        for (int elem : v)
            cout << elem << " ";
        cout << endl;
    }

    void sort(vector<int>& sortedVector)
    {
        int i, j, temp;
    
        for (i = 1; i < sortedVector.size(); i++)
        {
            temp = sortedVector[i];
            for (j = i - 1; j >= 0; j--)
            {
                if (sortedVector[j] < temp)
                    break;
  
                sortedVector[j + 1] = sortedVector[j];
                sortedVector[j] = temp;
            }
        }
    }

    void differentCount()
    {
        vector<int> v_temp = v;
        sort(v_temp);

        int counter = 0;
        cout << "Different numbers: ";
        for (vector<int>::iterator it = v_temp.begin(); it != v_temp.end() - 1; it++)
        {
            if (it == v_temp.begin())
            {
                if (*it != *(it + 1))
                {
                    cout << *it << ' ';
                    counter++;
                }
            }
            else if (it == v_temp.end() - 2)
            {
                if (*it != *(it + 1))
                {
                    cout << *(it + 1);
                    counter++;
                }
            }
            else
            {
                if (*it != *(it - 1) && *it != *(it + 1))
                {
                    cout << *it << ' ';
                    counter++;
                }
            }
        }

        cout << endl << "Number of different numbers: " << counter << endl;
    }
};

// Task 3

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
private:
    Suit cardSuit;
    Value cardValue;
    bool cardPosition;
public:
    Card(Suit suit, Value value, bool position = false) : cardSuit(suit), cardValue(value), cardPosition(position) {}
    bool flip() { cardPosition = !cardPosition; return cardPosition; }
    Value getValue() { return cardValue; }
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
            sum += cards[i]->getValue();
            if (cards[i]->getValue() == Ace)
                aceCount++;
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

int main()
{
    // Task 1
    {
        cout << "Task 1" << endl;
        ArrayInt array(10);
        for (int i = 0; i < array.getLength(); i++)
            array[i] = rand() % 10;
        array.printArr();
        array.pop_back();
        array.printArr();
        array.pop_front();
        array.printArr();

        array.insertionSort(true);
        array.printArr();
        array.insertionSort(false);
        array.printArr();

        cout << endl;
    }

    // Task 2
    {
        cout << "Task 2" << endl;
        Vector vec(10);
        vec.fill();
        vec.print();
        vec.differentCount();
        cout << endl;
    }

    // Task 3
    {
        cout << "Task 3" << endl;
        Card heartJack(Heart, Jack), spade2(Spade, Two), heartAce(Heart, Ace), clubAce(Club, Ace);
        Card spadeAce(Spade, Ace), diamondAce(Diamond, Ace);
        Hand hand;

        hand.Add(&heartJack);
        cout << hand.GetValue() << endl;
        hand.Add(&spade2);
        cout << hand.GetValue() << endl;
        hand.Add(&heartAce);
        cout << hand.GetValue() << endl;
        hand.Add(&clubAce);
        cout << hand.GetValue() << endl;
        hand.Add(&spadeAce);
        cout << hand.GetValue() << endl;
        hand.Add(&diamondAce);
        cout << hand.GetValue() << endl;

        hand.Clear();
        cout << hand.GetValue() << endl;
        cout << endl;
    }

    return 0;
}