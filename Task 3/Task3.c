// STUDENT ASSIGNMENT FILE MANAGEMENT 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int loggedIn = 0;
char role[20];
#define MAX_FILES 20
struct Permission{
    char filename[50];
    int read;
    int write;
    int execute;};
struct Permission permissions[MAX_FILES];
int fileCount = 0;

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
    strcpy(permissions[fileCount].filename, filename);
    permissions[fileCount].read = 1;
    permissions[fileCount].write = 1;
    permissions[fileCount].execute = 0;
    fileCount++;
    printf("Assignment file created successfully.\n");
    fclose(fp);
}
// Read Assignment File
void readFile() {
    char filename[50];
    char ch;
    printf("\nEnter Assignment File Name: ");
    scanf("%s", filename);
    int i;
    int found = 0;
    for(i = 0; i < fileCount; i++) {
        if(strcmp(filename, permissions[i].filename) == 0) {
            found = 1;
            if(permissions[i].read == 0) {
                printf("Read Permission Denied.\n");
                return;
            }
            break;
        }
    }
    if(found == 0){
        printf("Permission record not found.\n");
        return;
    }
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
    int i;
    int found = 0;
    for(i = 0; i < fileCount; i++) {
        if(strcmp(filename, permissions[i].filename) == 0) {
            found = 1;
            if(strcmp(role,"Student")==0 && permissions[i].write==0){
                printf("Write Permission Denied.\n");
                return;
            }
            break;
        }
    }
    if(found == 0){
        printf("Permission record not found.\n");
        return;
    }
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
void executeFile() {
    char filename[50];
    int i;
    printf("\nEnter Assignment File Name: ");
    scanf("%s", filename);
    int found = 0;
    for(i=0;i<fileCount;i++){
        if(strcmp(filename,permissions[i].filename)==0){
            found = 1;
            if(permissions[i].execute==0){
                printf("Execute Permission Denied.\n");
                return;
            }
            printf("Executing %s...\n",filename);
            printf("Execution Complete.\n");
            return;
        }
    }
    if(found==0){
        printf("Permission record not found.\n");
    }
}
// Delete Assignment File
void deleteFile() {

    char filename[50];

    printf("\nEnter Assignment File Name: ");
    scanf("%s", filename);

    if(remove(filename) == 0){
        printf("Assignment file deleted successfully.\n");
    }
    else{
        printf("File not found or unable to delete.\n");
    }
}
void managePermission() {
    char filename[50];
    int i;
    printf("\nEnter Assignment File Name: ");
    scanf("%s", filename);
    for(i=0;i<fileCount;i++){
        if(strcmp(filename, permissions[i].filename)==0){
            printf("Read Permission (1=Yes 0=No): ");
            scanf("%d",&permissions[i].read);
            printf("Write Permission (1=Yes 0=No): ");
            scanf("%d",&permissions[i].write);
            printf("Execute Permission (1=Yes 0=No): ");
            scanf("%d",&permissions[i].execute);
            printf("Permissions Updated Successfully.\n");
            return;
        }
    }
    printf("File not found.\n");
}
void viewPermission(){
    char filename[50];
    int i;
    printf("\nEnter Assignment File Name: ");
    scanf("%s", filename);
    for(i=0;i<fileCount;i++){
        if(strcmp(filename, permissions[i].filename)==0){
            printf("\nPermissions for %s\n", filename);
            printf("Read    : %s\n",
                permissions[i].read ? "Yes" : "No");
            printf("Write   : %s\n",
                permissions[i].write ? "Yes" : "No");
            printf("Execute : %s\n",
                permissions[i].execute ? "Yes" : "No");
            return;
        }
    }
    printf("File not found.\n");
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
                    deleteFile();
                    break;
                case 5:
                    managePermission();
                    break;
                case 6:
                    viewPermission();
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
            printf("2. Write Assignment File\n");
            printf("3. Execute Assignment File\n");
            printf("4. View File Permissions\n");
            printf("5. Logout\n");
            printf("6. Exit\n");
            printf("\nEnter your choice: ");
            scanf("%d",&choice);
            switch(choice){
              case 1:
                  readFile();
                  break;
              case 2:
                  writeFile();
                  break;
              case 3:
                  executeFile();
                  break;
              case 4:
                  viewPermission();
                  break;
              case 5:
                  loggedIn = 0;
                  strcpy(role,"");
                  printf("Logged Out Successfully.\n");
                  break;
              case 6:
                  printf("Thank You!\n");
                  return 0;
              default:
                  printf("Invalid Choice!\n");
          }
        }
    }
    return 0;
}
