#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

using namespace std;

// Task 1
class Date
{
private:
    uint8_t day;
    uint8_t month;
    uint16_t year;
public:
    Date(uint8_t _day = 1, uint8_t _month = 1, uint16_t _year = 1970) :
    day(_day), month(_month), year(_year) {}

    unsigned short Day() { return static_cast<unsigned short>(day); }
    unsigned short Month() { return static_cast<unsigned short>(month); }
    unsigned short Year() { return static_cast<unsigned short>(year); }
};

ostream& operator<<(ostream& out, Date& date)
{
    out << date.Day() << '/';
    out << date.Month() << '/';
    out << date.Year();

    return out;
}

// Task 2
Date& newer(const shared_ptr<Date>& date1, const shared_ptr<Date>& date2)
{
    if (date1->Year() < date2->Year())
        return *date2;
    else if (date1->Year() == date2->Year())
    {
        if (date1->Month() < date2->Month())
            return *date2;
        else if (date1->Month() == date2->Month())
        {
            if (date1->Day() < date2->Day())
                return *date2;
        }
    }

    return *date1;
}

void exchange(shared_ptr<Date>& date1, shared_ptr<Date>& date2)
{
    shared_ptr<Date> temp = date1;
    date1 = date2;
    date2 = temp;
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
        Ace = 1, Two = 2, Three = 3, Four = 4, Five = 5, Six = 6, Seven = 7,
        Eight = 8, Nine = 9, Ten = 10, Jack = 11, Queen = 12, King = 13
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
    void Clear()
    {
        cards.clear();
    }
    
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

class Player : public GenericPlayer
{
public:
    Player(string _name = "-") : GenericPlayer(_name) {}
    virtual bool IsHitting() override
    {
        string response;

        do
        {
            cout << "Do you want a hit? (Y/N): ";
            getline(cin, response);

            if (response.length() > 1)
                cout << "Incorrect input." << endl << endl;
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

class House : public GenericPlayer
{
public:
    House() : GenericPlayer("House") {}
    virtual bool IsHitting() override { return (GetValue() <= 16 ? true : false); }
    void FlipFirstCard() { cards[0]->flip(); }
};

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

// Task 3
Card::Value& operator++(Card::Value& rank)
{
    rank = static_cast<Card::Value>(rank + 1);
    return rank;
}

Card::Suit& operator++(Card::Suit& suit)
{
    suit = static_cast<Card::Suit>(suit + 1);
    return suit;
}

class Deck : public Hand
{
private:
    void Populate()
    {
        for (auto i = Card::Ace; i <= Card::King; ++i)
        {
            for (auto j = Card::Heart; j <= Card::Club; ++j)
                Add(new Card(j, i));
        }
    }
public:
    Deck() { Populate(); }

    void Shuffle()
    {
        random_shuffle(cards.begin(), cards.end());
    }
    void Deal(Hand& hand)
    {
        if (!cards.empty())
        {
            Card* card = cards.back();
            card->flip();
            hand.Add(card);
            cards.pop_back();
        }
        else
            cout << "Out of cards!" << endl;
    }
    void AdditionalCards(GenericPlayer& player)
    {
        while(!player.IsBoosted() && player.IsHitting())
        {
            Deal(player);
            cout << player << endl;

            if (player.GetValue() == 21)
                break;

            if (player.IsBoosted())
                player.Bust();
        }
    }
};

// Task 4
class Game
{
private:
    Deck deck;
    House house;
    vector<Player> players;
public:
    Game(vector<string> player_names)
    {
        for (auto& it : player_names)
            players.push_back(it);
        
        deck.Shuffle();
    }

    void Play()
    {
        for (auto& it : players)
        {
            deck.Deal(it);
            deck.Deal(it);
        }

        deck.Deal(house);
        house.FlipFirstCard();
        deck.Deal(house);

        for (auto& it : players)
            cout << it << endl << endl;
        cout << house << endl << endl;

        for (auto& it : players)
            deck.AdditionalCards(it);
        house.FlipFirstCard();
        deck.AdditionalCards(house);

        for (auto& it : players)
        {
            if (!it.IsBoosted())
            {
                if (it.GetValue() > house.GetValue())
                    it.Win();
                else if (house.GetValue() == it.GetValue())
                    it.Push();
                else
                    it.Lose();
            }
            else if (house.IsBoosted())
                it.Push();
            else
                it.Lose();
            
            it.Clear();
        }
        house.Clear();
    }
};

int main()
{
    // Task 1
    // {
    //     cout << "Task 1" << endl;

    //     shared_ptr<Date> today(new Date(2, 6, 2022));
    //     shared_ptr<Date> date(new Date);
    //     cout << today->Day() << '/' << today->Month() << '/' << today->Year() << endl;
    //     cout << *today << endl;
    //     date = today;
    //     cout << "today address: " << today << endl;
    //     cout << "date address: " << date << endl;
    //     cout << "today " << (today == nullptr ? "=" : "!=") << " nullptr" << endl;
    //     cout << "date " << (date == nullptr ? "=" : "!=") << " nullptr" << endl;

    //     cout << endl;
    // }

    // Task 2
    // {
    //     cout << "Task 2" << endl;

    //     shared_ptr<Date> date1(new Date);
    //     shared_ptr<Date> date2(new Date(1, 3, 1998));
    //     cout << "date1: " << *date1 << endl;
    //     cout << "date2: " << *date2 << endl;
    //     cout << "Newer: " << newer(date1, date2) << endl;

    //     exchange(date1, date2);
    //     cout << "date1: " << *date1 << endl;
    //     cout << "date2: " << *date2 << endl;

    //     cout << endl;
    // }

    // Task 3
    // {
    //     cout << "Task 3" << endl;

    //     srand(static_cast<unsigned int>(time(0)));
    //     Deck deck;
    //     deck.Shuffle();
    //     Player player("Arthur Morghan");
    //     deck.AdditionalCards(player);

    //     cout << endl;
    // }

    // Task 4 and 5
    {
        /* code */
    }

    return 0;
}