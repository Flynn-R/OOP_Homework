#include <iostream>
#include <vector>
#include <memory>

using namespace std;

// Task 1
class Date
{
private:
    uint8_t day;
    uint8_t month;
    uint16_t year;
public:
    explicit Date(uint8_t _day = 1, uint8_t _month = 1, uint16_t _year = 1970) :
    day(_day), month(_month), year(_year) {}

    unsigned short Day() const { return static_cast<unsigned short>(day); }
    unsigned short Month() const { return static_cast<unsigned short>(month); }
    unsigned short Year() const { return static_cast<unsigned short>(year); }
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

int main()
{
    // Task 1
     {
         cout << "Task 1" << endl;

         shared_ptr<Date> today(new Date(2, 6, 2022));
         shared_ptr<Date> date(new Date);
         cout << today->Day() << '/' << today->Month() << '/' << today->Year() << endl;
         cout << *today << endl;
         date = today;
         cout << "today address: " << today << endl;
         cout << "date address: " << date << endl;
         cout << "today " << (today == nullptr ? "=" : "!=") << " nullptr" << endl;
         cout << "date " << (date == nullptr ? "=" : "!=") << " nullptr" << endl;

         cout << endl;
     }

    // Task 2
     {
         cout << "Task 2" << endl;

         shared_ptr<Date> date1(new Date);
         shared_ptr<Date> date2(new Date(1, 3, 1998));
         cout << "date1: " << *date1 << endl;
         cout << "date2: " << *date2 << endl;
         cout << "Newer: " << newer(date1, date2) << endl;

         exchange(date1, date2);
         cout << "date1: " << *date1 << endl;
         cout << "date2: " << *date2 << endl;

         cout << endl;
     }

    return 0;
}