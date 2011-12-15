/* Prints a one-month reminder list (dynamic string version) */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_REMIND 50           /* maximum number of reminders */
#define MSG_LEN 60              /* maximum length of reminder message */

/* prototypes */
struct vstring {
    int day;
    int len;
    char reminder_msg[];
};

int read_line(char str[], int n);

int main(void)
{
    struct vstring *reminders[MAX_REMIND];
    char msg_str[MSG_LEN+1];
    int day, i, j, num_remind = 0;

    for (;;) {
        if (num_remind == MAX_REMIND) {
            printf("-- no space left --\n");
            break;
        }

        printf("Enter day and reminder: ");
        scanf("%2d", &day);
        if (day == 0) {
            break;
        } 

        read_line(msg_str, MSG_LEN);

        for (i = 0; i < num_remind; i++) {
            if (day < reminders[i]->day) {
                break;
            }
        }
        for (j = num_remind; j > i; j--) {
            reminders[j] = reminders[j-1];
        }

        reminders[i] = malloc(sizeof(struct vstring) + strlen(msg_str) + 1);
        if (reminders[i] == NULL) {
            printf("-- No Space Left --\n");
            break;
        }

        reminders[i]->day = day;
        reminders[i]->len = strlen(msg_str);
        strcpy(reminders[i]->reminder_msg, msg_str);

        num_remind++;
    }

    printf("\nDay Reminder\n");
    for (i = 0; i < num_remind; i++) {
        printf(" \n%d %s\n", reminders[i]->day, reminders[i]->reminder_msg);
        printf("\nAnd your reminder is %d characters long, in case you "
               "want to know.\n", reminders[i]->len);
    }

    return 0;
}
int read_line(char str[], int n) {
    int ch, i = 0;

    while ((ch = getchar()) != '\n') {
        if (i < n) {
            str[i++] = ch;
        }
    }
    str[i] = '\0';
    return i;
}
