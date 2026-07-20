#include <stdio.h>
#include <string.h>

//Login Details
void login() {
    char username[20];
    char password[20];
    printf("\nUsername: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);
    //strcmp is used for comparison of each characters
    if(strcmp(username, "lecturer") == 0 && strcmp(password, "lec123") == 0) {
        loggedIn = 1;
        strcpy(role, "Lecturer");
        printf("\nLogin Successful!\n");
        printf("Welcome Lecturer\n");
    }
    else if(strcmp(username, "student") == 0 && strcmp(password, "stu123") == 0) {
        loggedIn = 1;
        strcpy(role, "Student");
        printf("\nLogin Successful!\n");
        printf("Welcome Student\n");
    }
    else {
        printf("\nInvalid Username or Password\n");
    }
}

int main() {
    int choice;
    int loggedIn = 0;
    char role[20];

    do {
        printf(" Student Assignment File Management\n");
        printf("1. Login\n");
        printf("2. Create Assignment File\n");
        printf("3. Read Assignment File\n");
        printf("4. Write Assignment File\n");
        printf("5. Delete Assignment File\n");
        printf("6. Manage File Permissions\n");
        printf("7. View File Permissions\n");
        printf("8. Logout\n");
        printf("9. Exit\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                login();
                break;
            case 2:
                printf("Create File feature coming soon.\n");
                break;
            case 3:
                printf("Read File feature coming soon.\n");
                break;
            case 4:
                printf("Write File feature coming soon.\n");
                break;
            case 5:
                printf("Delete File feature coming soon.\n");
                break;
            case 6:
                printf("Permission feature coming soon.\n");
                break;
            case 7:
                printf("View Permission feature coming soon.\n");
                break;
            case 8:
                loggedIn = 0;
                strcpy(role, "");
                printf("Logged Out Successfully.\n");
                break;
            case 9:
                printf("Exiting System...\n");
                break;
            default:
                printf("Invalid Choice!\n");
        }

    } while(choice != 9);

    return 0;
}
