
#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 10
#define MAX_CLASSES 50

struct students {
    char name[30];
    int roll;
    int present;
    char attendance[MAX_CLASSES + 1];
};

int main() {

    struct students s[MAX_STUDENTS];

    int i, j, choice;
    int studentCount, totalclasses;
    int defaulterCount;
    float percentage;

    char record[MAX_CLASSES + 1];

    FILE *fp;

    // READ ATTENDANCE RECORD FILE

    fp = fopen("attendance_record.txt", "r");

    if(fp == NULL) {
        printf("Error opening attendance_record.txt!\n");
        return 1;
    }

    // Read number of students and total classes

    if(fscanf(fp, "%d %d", &studentCount, &totalclasses) != 2) {
        printf("Invalid file format!\n");
        fclose(fp);
        return 1;
    }

    if(studentCount < 1 || studentCount > MAX_STUDENTS ||
       totalclasses < 0 || totalclasses > MAX_CLASSES) {

        printf("Invalid student count or class count!\n");
        fclose(fp);
        return 1;
    }

    // Read student details and attendance

    for(i = 0; i < studentCount; i++) {

        if(fscanf(fp, "%d %29s %50s",
                  &s[i].roll, s[i].name, record) != 3) {

            printf("Error reading student record!\n");
            fclose(fp);
            return 1;
        }

        s[i].present = 0;

        if(totalclasses == 0) {

            if(strcmp(record, "-") != 0) {
                printf("Invalid attendance record!\n");
                fclose(fp);
                return 1;
            }

            s[i].attendance[0] = '\0';
        }
        else {

            if(strlen(record) != (size_t)totalclasses) {
                printf("Attendance history length error for %s!\n",
                       s[i].name);
                fclose(fp);
                return 1;
            }

            for(j = 0; j < totalclasses; j++) {

                if(record[j] == 'p')
                    record[j] = 'P';

                else if(record[j] == 'a')
                    record[j] = 'A';

                if(record[j] != 'P' && record[j] != 'A') {
                    printf("Invalid attendance character for %s!\n",
                           s[i].name);
                    fclose(fp);
                    return 1;
                }

                s[i].attendance[j] = record[j];

                if(record[j] == 'P') {
                    s[i].present++;
                }
            }

            s[i].attendance[totalclasses] = '\0';
        }
    }

    fclose(fp);

    printf("\nAttendance records loaded successfully!\n");
    printf("Total students: %d\n", studentCount);
    printf("Total classes: %d\n", totalclasses);


    // MAIN MENU

    do {

        printf("\n===== ATTENDANCE ANALYZER =====\n");
        printf("1. Attendance report\n");
        printf("2. Defaulters\n");
        printf("3. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {

            // ATTENDANCE REPORT

            case 1:

                if(totalclasses == 0) {
                    printf("No attendance records available!\n");
                    break;
                }

                fp = fopen("attendance_report.txt", "w");

                if(fp == NULL) {
                    printf("Error opening attendance report file!\n");
                    break;
                }

                printf("\n===== ATTENDANCE REPORT =====\n");

                fprintf(fp, "===== ATTENDANCE REPORT =====\n");
                fprintf(fp, "Total classes: %d\n\n", totalclasses);

                for(i = 0; i < studentCount; i++) {

                    percentage =
                        (float)s[i].present / totalclasses * 100;

                    printf("%d %s | ", s[i].roll, s[i].name);

                    fprintf(fp, "%d %s | ", s[i].roll, s[i].name);

                    for(j = 0; j < totalclasses; j++) {

                        printf("%c ", s[i].attendance[j]);

                        fprintf(fp, "%c ", s[i].attendance[j]);
                    }

                    printf("| %.2f%%\n", percentage);

                    fprintf(fp, "| %.2f%%\n", percentage);
                }

                fclose(fp);

                printf("\nReport saved to attendance_report.txt\n");

                break;


            // DEFAULTERS

            case 2:

                if(totalclasses == 0) {
                    printf("No attendance records available!\n");
                    break;
                }

                fp = fopen("defaulters.txt", "w");

                if(fp == NULL) {
                    printf("Error opening defaulters file!\n");
                    break;
                }
                printf("\n===== DEFAULTERS =====\n");
                fprintf(fp, "===== DEFAULTERS REPORT =====\n");
                fprintf(fp, "Required attendance: 75%%\n\n");
                defaulterCount = 0;
                for(i = 0; i < studentCount; i++) {

                    percentage =
                        (float)s[i].present / totalclasses * 100;

                    if(percentage < 75) {

                        printf("%s - %.2f%%\n",
                               s[i].name, percentage);

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
                printf("\nDefaulters saved to defaulters.txt\n");
                break;
            // EXIT
            case 3:
                printf("Thank you!\n");
                break;
            default:
                printf("Invalid choice!\n");
                break;
        }
    } while(choice != 3);
    return 0;
}
