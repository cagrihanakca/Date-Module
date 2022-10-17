#ifndef DATE_H_
#define DATE_H_

typedef struct {
    int md; // day 
    int mm; // month
    int my; // year
}Date;

#define             YEAR_BASE           1900

// set functions

Date *set(Date *p, int day, int mon, int year);
Date *set_date_by_str(Date *p, const char *pfm);
Date *set_date_today(Date *p);
Date *set_date_random(Date *p);
Date *set_day(Date *p, int day);
Date *set_month(Date *p, int month);
Date *set_year(Date *p, int year);

// get functions

int get_day(const Date *p);
int get_month(const Date *p);
int get_year(const Date *p);
int get_week_day(const Date *p);
int get_year_day(const Date *p);

// utility functions

int cmp_date(const Date *p1, const Date *p2);
int date_diff(const Date *p1, const Date *p2);
Date *ndays_after(Date *pdest, const Date *psource, int n);

// input-output functions

void print_date(const Date *p);
Date *scan_date(Date *p);

#endif