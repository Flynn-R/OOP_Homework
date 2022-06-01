#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

// Task 1
class OnlyIntAllowed
{
private:
    stringstream inputstream;
    string input;

    bool calc(const int& base, int* number)
    {
        char c;
        while (inputstream.get(c))
        {
            if (c >= '0' && c <= '9')
                *number = *number * abs(base) + static_cast<int>(c - 48);
            else
            {
                cout << "Wrong input! Try again." << endl << endl;
                inputstream.str("");
                return false;
            }
        }
        *number = (base > 0 ? *number : -(*number));

        return true;
    }
public:
    OnlyIntAllowed()
    {
        input.clear();
        inputstream.str("");
    }

    void in()
    {
        bool check = false;
        int number;
        short base = 10;
        do
        {
            number = 0;
            cout << "Enter an integer number: ";
            cin >> input;
            inputstream << input;
            if (inputstream.get() == '-')
                base = -base;
            else
                inputstream.unget();
        } while (!calc(base, &number));

        cout << "Your integer number is: " << number << endl;
    }
};    

// Task 2
ostream& endll(ostream& out)
{
    out.put('\n'); out.put('\n');
    out.clear();
    out.flush();
    return out;
}

// Blackjack
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
        Eight = 8, Nine = 9, Ten = 10, Jack = 11, Queen = 12, King = 13, Ace = 1
    };
    Card(Suit suit, Value value, bool position = false) : cardSuit(suit), cardValue(value), isFaceUp(position) {}
    void flip() { isFaceUp = !isFaceUp; }
    Value getValue()
    {
        if (cardValue > Ten && cardValue <= King)
            return Ten;
        return cardValue;
    }
    bool isFaceUp;
private:
    Suit cardSuit;
    Value cardValue;

    friend ostream& operator<<(ostream&, Card&);
};

class Hand
{
protected:
    vector<Card*> cards;
public:
    virtual ~Hand() { Clear(); }
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
protected:
    string name;
public:
    GenericPlayer(string _name = "") : name(_name) {}
    virtual ~GenericPlayer() {}
    virtual bool IsHitting() = 0;
    bool IsBoosted() { return (GetValue() > 21); }
    void Bust() { if (IsBoosted()) cout << name << " is busted!" << endl; }

    friend ostream& operator<<(ostream&, GenericPlayer&);
};

// Task 3
class Player : public GenericPlayer
{
public:
    Player(string _name) : GenericPlayer(_name) {}
    virtual bool IsHitting() override
    {
        string response;

        do
        {
            cout << "Do you want a hit? (Y/N): ";
            getline(cin, response);

            if (response.length() > 1)
                cout << "Incorrect input." << endll;
            else
            {
                if (response[0] == 'y' || response[0] == 'Y')
                    return true;
            }

        } while (response[0] != 'N' && response[0] != 'n');

        return false;
    }

    void Win() const { cout << name << " wins!" << endl; }
    void Lose() const { cout << name << " loses!" << endl; }
    void Push() const { cout << name << " pushed!" << endl; }
};

// Task 4
class House : public GenericPlayer
{
public:
    House() : GenericPlayer("House") {}
    virtual bool IsHitting() override { return (GetValue() <= 16 ? true : false); }
    void FlipFirstCard() { cards[0]->flip(); }
};

// Task 5
ostream& operator<<(ostream& out, Card& card)
{
    if (card.isFaceUp)
    {
        switch(card.cardSuit)
        {
        case Card::Heart:
            out << "Heart ";
            break;
        case Card::Spade:
            out << "Spade ";
            break;
        case Card::Diamond:
            out << "Diamond ";
            break;
        case Card::Club:
            out << "Club ";
            break;
        default:;
        }

        switch(card.cardValue)
        {
        case Card::Ace:
            out << "Ace";
            break;
        case Card::Two:
            out << '2';
            break;
        case Card::Three:
            out << '3';
            break;
        case Card::Four:
            out << '4';
            break;
        case Card::Five:
            out << '5';
            break;
        case Card::Six:
            out << '6';
            break;
        case Card::Seven:
            out << '7';
            break;
        case Card::Eight:
            out << '8';
            break;
        case Card::Nine:
            out << '9';
            break;
        case Card::Ten:
            out << "10";
            break;
        case Card::Jack:
            out << "Jack";
            break;
        case Card::Queen:
            out << "Queen";
            break;
        case Card::King:
            out << "King";
            break;
        default:;
        }
    }
    else
        out << "XX";

    return out;
}

ostream& operator<<(ostream& out, GenericPlayer& player)
{
    out << player.name << endl;
    for (vector<Card*>::iterator it = player.cards.begin(); it != player.cards.end(); ++it)
    {
        out << *(*it);
        out << (it + 1 == player.cards.end() ? "\n" : ", ");
    }
    out << player.GetValue() << endl;

    return out;
}

int main()
{
    // Task 1
    {
        cout << "Task 1" << endl;

        OnlyIntAllowed i;
        i.in();

        cout << endl;
    }

    // Task 2
    {
        cout << "Task 2" << endl;

        cout << "Hello" << endll << "world!" << endll;
    }

    // Task 3
    {
        cout << "Task 3" << endl;

        Player player("Arthur Morgan");
        cout << (player.IsHitting() ? "Hit!" : "Enough!") << endll;
    }

    // Task 4
    {
        cout << "Task 4" << endl;

        vector<Card*> deck;
        for (size_t i = 1; i < 14; ++i)
        {
            for (size_t j = 0; j < 4; ++j)
            {
                auto card = new Card(static_cast<Card::Suit>(j), static_cast<Card::Value>(i), true);
                deck.push_back(card);
            }
        }
        
        
        House house;
        for (vector<Card*>::iterator it = deck.begin(); it != deck.end(); ++it)
        {
            if (house.IsHitting())
            {
                house.Add(*it);
                cout << (*it)->getValue() << ' ';
            }
            else
                break;
        }

        for (vector<Card*>::iterator it = deck.begin(); it != deck.end(); ++it)
            delete *it;

        cout << endll;
    }

    // Task 5
    {
        cout << "Task 5" << endl;

        Card card1(Card::Heart, Card::Ace, true);
        Card card2(Card::Diamond, Card::Jack, true);
        Card card3(Card::Spade, Card::Ten);

        Player player("Arthur Morgan");
        player.Add(&card1);
        player.Add(&card2);
        cout << player << endl;

        House house;
        house.Add(&card3);
        cout << house << endl;
        house.FlipFirstCard();
        cout << house << endl;
    }

    return 0;
}
