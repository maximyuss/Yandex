// https://contest.yandex.ru/contest/59539/problems/I/

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

struct Day { 
    int day; int month;
    bool operator<(const Day& a) const {
        if (month == a.month)
            return day < a.day;
        else
            return month < a.month;
    }    
};
set<Day> Holidays;
int Year = 0;
int FirstDayOfWeek = 0;

bool IsDayIsHoliday(int day, int month) {
    return (Holidays.contains({ day, month }));
}

int GetDaysInMonth(int month, int year) {
    int res = 0;
    switch (month) {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            res = 31;
            break;
        case 2:
            if ((year % 400 == 0 || year % 100 != 0) && year % 4 == 0)
                res = 29;
            else
                res = 28;
            break;
        default:
            res = 30;
    }
    return res;
}

int GetMonthIndex(const string& monthName) {
    static const std::map<string, int> months {
        { "January", 1 },
        { "February", 2 },
        { "March", 3 },
        { "April", 4 },
        { "May", 5 },
        { "June", 6 },
        { "July", 7 },
        { "August", 8 },
        { "September", 9 },
        { "October", 10 },
        { "November", 11 },
        { "December", 12 }
    };
    const auto iter(months.find(monthName));
    return (iter != std::cend(months)) ? iter->second : -1;
}

int GetDayOfWeekIndex(const string& dayOfWeekName) {
    static const std::map<string, int> daysOfWeek {
        { "Monday", 0 },
        { "Tuesday", 1 },
        { "Wednesday", 2 },
        { "Thursday", 3 },
        { "Friday", 4 },
        { "Saturday", 5 },
        { "Sunday", 6 },
    };
    const auto iter(daysOfWeek.find(dayOfWeekName));
    return (iter != std::cend(daysOfWeek)) ? iter->second : -1;
}

string GetDayOfWeekName(const int dayOfWeekIndex) {
    static const std::map<int, string> daysOfWeek {
        { 0, "Monday"},
        { 1, "Tuesday" },
        { 2, "Wednesday" },
        { 3, "Thursday" },
        { 4, "Friday" },
        { 5, "Saturday" },
        { 6, "Sunday" },
    };
    const auto iter(daysOfWeek.find(dayOfWeekIndex));
    return (iter != std::cend(daysOfWeek)) ? iter->second : "";
}

void taskI(){
    map<int, int> countWorkDays;
    int currDayOfWeek = FirstDayOfWeek;
    for (size_t month = 1; month < 13; month++) {
        for (size_t day = 1; day <= GetDaysInMonth(month, Year); day++) {
            if (!IsDayIsHoliday(day, month))
                countWorkDays[currDayOfWeek]++;
            currDayOfWeek++;
            if (currDayOfWeek == 7)
                currDayOfWeek = 0;
        }
    }
    int bestDay = 0,
        worstDay = 0;
    for (auto e : countWorkDays) {
        if (e.second > countWorkDays[bestDay])
            bestDay = e.first;
        if (e.second < countWorkDays[worstDay])
            worstDay = e.first;
    }
    cout << GetDayOfWeekName(bestDay) << " " << GetDayOfWeekName(worstDay) << endl;
}

void input() {
    int n = 0,
        day = 0;
    string input;

    cin >> n;
    cin >> Year;
    for (size_t i = 0; i < n; i++) {
        cin >> day;
        cin >> input;
        Holidays.insert({ day,GetMonthIndex(input) });
    }
    cin >> input;
    FirstDayOfWeek = GetDayOfWeekIndex(input);
}

int main() {
    input();
    taskI();
}

/*
11
2024
13 January
30 May
19 June
1 January
13 February
4 July
10 September
2 October
25 December
30 November
11 November
Monday
*/
