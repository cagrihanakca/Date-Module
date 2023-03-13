#include "date.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define             PRIVATE                         static
#define             PUBLIC

#define             IS_LEAP(y)                      ((y) % 4 == 0 && ((y) % 100 != 0 || (y) % 400 == 0))
#define             NO_OF_DAYS(y, m)                (daytabs[IS_LEAP(y)][m])
#define             MAX_YEAR                        2022
#define             MIN_YEAR                        1900

PRIVATE Date *set(Date *p, int day, int mon, int year);
PRIVATE int is_valid_date(int day, int mon, int year);
PRIVATE int total_days(const Date *p);
PRIVATE Date *i_to_date(Date *p, int total_days);

PRIVATE const int daytabs[][13] = {
    { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
    { 0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }
};

// public function implementations

PUBLIC Date *set_date(Date *p, int day, int mon, int year)
{
    return set(p, day, mon, year);
}

PUBLIC Date *set_date_by_str(Date *p, const char *pfm)
{
    int day = atoi(pfm);
    int mon = atoi(pfm + 3);
    int year = atoi(pfm + 6);

    return set(p, day, mon, year);
}

PUBLIC Date *set_date_today(Date *p)
{
    time_t timer;
    time(&timer);

    struct tm *ptr = localtime(&timer);

    return set(p, ptr->tm_mday, ptr->tm_mon + 1, ptr->tm_year + 1900);
}

PUBLIC Date *set_date_random(Date *p)
{
    int year = rand() % (MAX_YEAR - MIN_YEAR + 1) + MIN_YEAR;
    int mon = rand() % 12 + 1;
    int day = rand() % NO_OF_DAYS(year, mon) + 1;

    return set(p, day, mon, year);
}

PUBLIC int get_day(const Date *p)
{
    return p->md;
}

PUBLIC int get_month(const Date *p)
{
    return p->mm;
}

PUBLIC int get_year(const Date *p)
{
    return p->my;
}

PUBLIC Date *set_day(Date *p, int day)
{
    return set(p, day, get_month(p), get_year(p));
}

PUBLIC Date *set_month(Date *p, int mon)
{
    return set(p, get_day(p), mon, get_year(p));
}

PUBLIC Date *set_year(Date *p, int year)
{
    return set(p, get_day(p), get_month(p), year);
}

PUBLIC int get_week_day(const Date *p)
{
    return day_of_the_week(get_day(p), get_month(p), get_year(p));
}

PUBLIC int get_year_day(const Date *p)
{
    int sum = get_day(p);
    int mon = get_month(p);
    int year = get_year(p);

    for (int i = 1; i < mon; ++i)
        sum += NO_OF_DAYS(year, i);
    
    return sum;
}

PUBLIC int cmp_date(const Date *p1, const Date *p2)
{
    int p1_year = get_year(p1);
    int p2_year = get_year(p2);

    if (p1_year != p2_year)
        return p1_year - p2_year;
    
    int p1_month = get_month(p1);
    int p2_month = get_month(p2);

    if (p1_month != p2_month)
        return p1_month - p2_month;
    
    return get_day(p1) - get_day(p2);
}

PUBLIC int date_diff(const Date *p1, const Date *p2)
{
    return abs(total_days(p1) - total_days(p2));
}

PUBLIC Date *ndays_after(Date *pdest, const Date *psource, int n)
{
    return i_to_date(pdest, total_days(psource) + n);
}

PUBLIC void print_date(const Date *p)
{
    static const char* const pmons[] = {
        "",
        "January",
        "February",
        "March",
        "April",
        "May",
        "June",
        "July",
        "August",
        "September",
        "October",
        "November",
        "December"
    };

    static const char* const pdays[] = {
        "Sunday",
        "Monday",
        "Tuesday",
        "Wednesday",
        "Thursday",
        "Friday",
        "Saturday"
    };

    printf("%d %s %d %s\n", p->md, pmons[p->mm], p->my, pdays[get_week_day(p)]);
}

PUBLIC Date *scan_date(Date *p)
{
    int day, mon, year;

    scanf("%d%d%d", &day, &mon, &year);

    return set(p, day, mon, year);
}

// private function implementations

PRIVATE Date *set(Date *p, int day, int mon, int year)
{
    if (!is_valid_date(day, mon, year)) {
        printf("Date %02d %02d %d is an invalida date.\n", day, mon, year);
        exit(EXIT_FAILURE);
    }

    p->md = day;
    p->mm = mon;
    p->my = year;

    return p;
}

PRIVATE int is_valid_date(int day, int mon, int year)
{
    return year >= YEAR_BASE &&
           mon > 0 && mon <= 12 &&
           day <= NO_OF_DAYS(year, mon);
}

PRIVATE int total_days(const Date *p)
{
    int sum = get_year_day(p);
    int year = get_year(p);

    for (int i = YEAR_BASE; i < year; ++i)
        sum += IS_LEAP(i) ? 366 : 365;
    
    return sum;
}

PRIVATE Date *i_to_date(Date *p, int total_days)
{
    int year = YEAR_BASE;

    while (total_days > (IS_LEAP(year) ? 366 : 365)) {
        total_days -= (IS_LEAP(year) ? 366 : 365);
        ++year;
    }

    int mon = 1;

    while (total_days > NO_OF_DAYS(year, mon)) {
        total_days -= NO_OF_DAYS(year, mon);
        ++mon;
    }

    int day = total_days;

    return set(p, day, mon, year);
}
