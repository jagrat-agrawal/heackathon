#include <stdio.h>
struct students {
    char name[30];
    int roll;
    int present;
    char attendance[50];
};
int main() {
    struct students s[10];
    int i, j, choice;
    char status;
    int totalclasses = 0;
    float percentage;
    printf(" ==== student registeration ==== \n");
    for(i = 0; i < 10; i++) {
        s[i].present = 0;
        s[i].roll = 101 + i;
        printf("roll no -%d- enter name of student: " , s[i].roll);
        scanf("%s", s[i].name);
    }
    do {
        printf("\n ==== attendance analyzer ==== \n");
        printf("1. mark attendance \n");
        printf("2. attendance report\n");
        printf("3. defaulters\n");
        printf("4. exit\n");
        printf("enter choice: ");
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                if(totalclasses >= 50) {
                    printf("maximum classes reached");
                    break;
                }
                printf("P for present and A for absent \n");
                for(i = 0; i < 10; i++) {
                    printf("%s: ", s[i].name);
                    scanf(" %c", &status);

                    if(status != 'P' && status != 'A') {
                        i--;
                        printf("invalid credential\n");
                        continue;
                    }
                    s[i].attendance[totalclasses] = status;

                    if(status == 'P') {
                        s[i].present++;
                    }
                }
                totalclasses++;
                break;
            case 2:
                if(totalclasses == 0) {
                    printf("no classes held yet");
                    break;
                }
                printf("\n=====attendance report=====\n");

                for(i = 0; i < 10; i++) {
                    printf("%s- ", s[i].name);
                    for(j = 0; j < totalclasses; j++) {
                        printf("%c  ", s[i].attendance[j]);
                    }
                    percentage = (float)s[i].present / totalclasses * 100;
                    printf(" %.2f%%\n", percentage);
                }
                break;
            case 3:
                if(totalclasses == 0) {
                    printf("no classes held yet");
                    break;
                }
                printf("\n ==== defaulters ==== \n");
                for(i = 0; i < 10; i++) {
                    percentage = (float)s[i].present / totalclasses * 100.00;

                    if(percentage < 75) {
                        printf("%s %.2f%%\n", s[i].name, percentage);
                    }
                }
                break;
            case 4:
                printf("thank you! ");
                break;
            default:
                printf("invalid credentials");
                break;
        }
    } while(choice != 4);
    return 0;
}