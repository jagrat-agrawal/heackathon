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
    int totalclasses = 0;
    int defaulterCount;
    char status;
    float percentage;
    FILE *fp;

    printf(" ==== student registration ==== \n");

    for(i = 0; i < 10; i++) {
        s[i].present = 0;
        s[i].roll = 101 + i;

        printf("Roll no -%d- enter name of student: ", s[i].roll);
        scanf("%29s", s[i].name);
    }

    do {
        printf("\n ==== attendance analyzer ==== \n");
        printf("1. Mark attendance \n");
        printf("2. Attendance report\n");
        printf("3. Defaulters\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {

            case 1:
                if(totalclasses >= 50) {
                    printf("Maximum classes reached\n");
                    break;
                }

                printf("P for present and A for absent\n");

                for(i = 0; i < 10; i++) {
                    printf("%s: ", s[i].name);
                    scanf(" %c", &status);

                    if(status != 'P' && status != 'A') {
                        i--;
                        printf("Invalid input! Try again.\n");
                        continue;
                    }

                    s[i].attendance[totalclasses] = status;

                    if(status == 'P') {
                        s[i].present++;
                    }
                }

                totalclasses++;
                printf("Attendance marked successfully!\n");
                break;


            case 2:
                if(totalclasses == 0) {
                    printf("No classes held yet.\n");
                    break;
                }

                // Open attendance report file
                fp = fopen("attendance_report.txt", "w");

                if(fp == NULL) {
                    printf("Error opening attendance report file!\n");
                    break;
                }

                printf("\n===== ATTENDANCE REPORT =====\n");

                fprintf(fp, "===== ATTENDANCE REPORT =====\n");
                fprintf(fp, "Total classes held: %d\n\n", totalclasses);

                for(i = 0; i < 10; i++) {

                    printf("%s - ", s[i].name);
                    fprintf(fp, "%s - ", s[i].name);

                    for(j = 0; j < totalclasses; j++) {
                        printf("%c  ", s[i].attendance[j]);
                        fprintf(fp, "%c  ", s[i].attendance[j]);
                    }

                    percentage = (float)s[i].present / totalclasses * 100;

                    printf(" Attendance: %.2f%%\n", percentage);
                    fprintf(fp, " Attendance: %.2f%%\n", percentage);
                }

                fclose(fp);

                printf("\nAttendance report saved to attendance_report.txt\n");
                break;


            case 3:
                if(totalclasses == 0) {
                    printf("No classes held yet.\n");
                    break;
                }

                // Open defaulters file
                fp = fopen("defaulters.txt", "w");

                if(fp == NULL) {
                    printf("Error opening defaulters file!\n");
                    break;
                }

                printf("\n===== DEFAULTERS =====\n");

                fprintf(fp, "===== DEFAULTERS REPORT =====\n");
                fprintf(fp, "Minimum required attendance: 75%%\n\n");

                defaulterCount = 0;

                for(i = 0; i < 10; i++) {

                    percentage = (float)s[i].present / totalclasses * 100;

                    if(percentage < 75) {
                        printf("%s - %.2f%%\n", s[i].name, percentage);

                        fprintf(fp, "%s - %.2f%%\n",
                                s[i].name, percentage);

                        defaulterCount++;
                    }
                }

                if(defaulterCount == 0) {
                    printf("No defaulters found!\n");
                    fprintf(fp, "No defaulters found!\n");
                }

                fclose(fp);

                printf("\nDefaulters report saved to defaulters.txt\n");
                break;


            case 4:
                printf("Thank you!\n");
                break;


            default:
                printf("Invalid choice!\n");
                break;
        }

    } while(choice != 4);

    return 0;
}
