#include <stdio.h>
#include <time.h>
#include <string.h>

enum { START_YEAR = 1900, WEEK = 7, FST_THU = 1, SND_THU = 2, FTH_THU = 4 };

int main(void)
{
    int year;
    int month = 0;
    int thu_num = 0;
    scanf("%d", &year);

    struct tm date;
    //set the first day of year
    memset(&date, 0, sizeof(date));
    date.tm_mon = 0;
    date.tm_mday = 1;
    date.tm_year = year - START_YEAR;
    timegm(&date);

    switch (date.tm_wday) { //set the first day as Thursday
    case 0:
        date.tm_mday += 4;
        break;
    case 1:
        date.tm_mday += 3;
        break;
    case 2:
        date.tm_mday += 2;
        break;
    case 3:
        date.tm_mday += 1;
        break;
    case 5:
        date.tm_mday += 6;
        break;
    case 6:
        date.tm_mday += 5;
        break;
    }
    timegm(&date);

    while (date.tm_mon >= month) {
        if (date.tm_mon == month) {
            thu_num++;
            if (thu_num == SND_THU || thu_num == FTH_THU) {
                if (date.tm_mday % 3) { // "% 3" to check the multiplicity of the date to three
                    printf("%d %d\n", date.tm_mon + 1, date.tm_mday); // "+ 1" for human-readable view
                }
            }
        } else {
            month = date.tm_mon;
            thu_num = FST_THU;
        }
        date.tm_mday += WEEK;
        timegm(&date);
    }
}
