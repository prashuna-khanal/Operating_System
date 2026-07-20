#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int loggedIn = 0;
char role[20];
//LOGIN
void login() {
    char username[20];
    char password[20];
    int attempts = 0;

    while (attempts < 3) {
        printf("\nUsername: ");
        scanf("%s", username);
        printf("Password: ");
        scanf("%s", password);
        if (strcmp(username, "lecturer") == 0 && strcmp(password, "lec123") == 0) {
            loggedIn = 1;
            strcpy(role, "Lecturer");
            printf("\nLogin Successful!\n");
            printf("Welcome to the portal !!\n");
            return;
        }
        else if (strcmp(username, "student") == 0 && strcmp(password, "stu123") == 0) {
            loggedIn = 1;
            strcpy(role, "Student");
            printf("\nLogin Successful!\n");
            printf("Welcome Student\n");
            return;
        }
        else {
            attempts++;
            printf("\nInvalid Username or Password.\n");
            if (attempts < 3)
                printf("Attempts Remaining: %d\n", 3 - attempts);
        }
    }
    printf("\nToo many failed login attempts.\n");
    exit(0);
}
// Create Assignment File
void createFile() {
    char filename[50];
    printf("\nEnter Assignment File Name: ");
    scanf("%s", filename);
    FILE *fp = fopen(filename, "w");
    if(fp == NULL){
        printf("Unable to create file.\n");
        return;
    }
    printf("Assignment file created successfully.\n");
    fclose(fp);
}
// Read Assignment File
void readFile() {
    char filename[50];
    char ch;
    printf("\nEnter Assignment File Name: ");
    scanf("%s", filename);
    FILE *fp = fopen(filename, "r");
    if(fp == NULL){
        printf("File not found.\n");
        return;
    }
    printf("\n File Content \n");
    while((ch = fgetc(fp)) != EOF){
        printf("%c", ch);
    }
    fclose(fp);
}
// Write Assignment File
void writeFile() {
    char filename[50];
    char text[1000];
    printf("\nEnter Assignment File Name: ");
    scanf("%s", filename);
    FILE *fp = fopen(filename, "a");
    if(fp == NULL){
        printf("File not found.\n");
        return;
    }
    getchar();   // Clear newline
    printf("Enter text:\n");
    fgets(text, sizeof(text), stdin);
    fprintf(fp, "%s", text);
    fclose(fp);
    printf("Content written successfully.\n");
}

//Main Function
int main() {
    int choice;
    while (1) {
        // LOGIN MENU
        if (!loggedIn) {
            printf(" Student Assignment File Management\n");
            printf("1. Login\n");
            printf("2. Exit\n");
            printf("\nEnter your choice: ");
            scanf("%d", &choice);
            switch(choice){
                case 1:
                    login();
                    break;
                case 2:
                    printf("Thank You!\n");
                    return 0;
                default:
                    printf("Invalid Choice!\n");
            }
        }
        //LECTURER MENU
        else if(strcmp(role,"Lecturer")==0){
            printf("\n Lecturer Menu \n");
            printf("1. Create Assignment File\n");
            printf("2. Read Assignment File\n");
            printf("3. Write Assignment File\n");
            printf("4. Delete Assignment File\n");
            printf("5. Manage File Permissions\n");
            printf("6. View File Permissions\n");
            printf("7. Logout\n");
            printf("8. Exit\n");
            printf("\nEnter your choice: ");
            scanf("%d",&choice);
            switch(choice){
                case 1:
                    createFile();
                    break;
                case 2:
                    readFile();
                    break;
                case 3:
                    writeFile();
                    break;
                case 4:
                    printf("Delete Assignment File feature coming soon.\n");
                    break;
                case 5:
                    printf("Manage File Permissions feature coming soon.\n");
                    break;
                case 6:
                    printf("View File Permissions feature coming soon.\n");
                    break;
                case 7:
                    loggedIn = 0;
                    strcpy(role,"");
                    printf("Logged Out Successfully.\n");
                    break;
                case 8:
                    printf("Thank You!\n");
                    return 0;
                default:
                    printf("Invalid Choice!\n");
            }
        }
        //STUDENT MENU 
        else{
            printf("\n Student Menu \n");
            printf("1. Read Assignment File\n");
            printf("2. View File Permissions\n");
            printf("3. Logout\n");
            printf("4. Exit\n");
            printf("\nEnter your choice: ");
            scanf("%d",&choice);
            switch(choice){
                case 1:
                    readFile();
                    break;
                case 2:
                    printf("View File Permissions feature coming soon.\n");
                    break;
                case 3:
                    loggedIn = 0;
                    strcpy(role,"");
                    printf("Logged Out Successfully.\n");
                    break;
                case 4:
                    printf("Thank You!\n");
                    return 0;
                default:
                    printf("Invalid Choice!\n");
            }
        }
    }
    return 0;
}
