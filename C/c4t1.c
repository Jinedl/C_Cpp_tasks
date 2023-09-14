
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

enum { PARTIES = 6 };

int
main(int argc, char *argv[])
{
    unsigned short i, j;
    unsigned short sum_1s = 0, sum_without_1s = 0;
    int  votes[PARTIES] = {0};
    unsigned short votes_block[PARTIES];
    unsigned short count_record, sum_record, vote;
    
    int f = open(argv[1], O_RDONLY);
    
    while (1) {
        read(f, &count_record, 2);
        read(f, &sum_record, 2);
        
        if (sum_record && sum_record == sum_1s + sum_without_1s) {
            for (i = 0; i < PARTIES; i++) {
                votes[i] += votes_block[i];
            }
        } else if (sum_record) {
            sum_record -= sum_without_1s;
            for (i = 2; i < PARTIES; i++) {
                votes[i] += votes_block[i - 1];
                sum_record -=  votes_block[i - 1];
            }
            votes[1] += sum_record - sum_1s;
            votes[0] += sum_1s - (sum_record - sum_1s);
        }
        
        if (! count_record) {
            break;
        } else {
            for (j = 0; j < PARTIES; j++) votes_block[j] = 0;
            sum_1s = 0;
            sum_without_1s = 0;
            for (i = 0; i < count_record; i++) {
                read(f, &vote, 2);
                if (vote == 1) {
                    sum_1s++;
                    votes_block[0]++;
                } else {
                    sum_without_1s += vote;
                    votes_block[vote - 1]++;
                }
            }
        }
    }
    
    close(f);
    
    for (i = 0; i < PARTIES; i++) {
        printf("%d ", votes[i]);
    }
    printf("\n");
}
