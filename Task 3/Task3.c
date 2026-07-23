// STUDENT ASSIGNMENT FILE MANAGEMENT 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int loggedIn = 0;
char role[20];
#define MAX_FILES 20
struct Permission{
    char filename[50];
    char lecturer[4];   // rwx
    char student[4];    // rwx
    int encrypted;
};
struct Permission permissions[MAX_FILES];
int fileCount = 0;
void writeLog(char action[], char filename[]);

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
            writeLog("Lecturer Login","System");
            return;
        }
        else if (strcmp(username, "student") == 0 && strcmp(password, "stu123") == 0) {
            loggedIn = 1;
            strcpy(role, "Student");
            printf("\nLogin Successful!\n");
            printf("Welcome Student to the portal\n");
            writeLog("Student Login","System");
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
    strcpy(permissions[fileCount].lecturer,"rwx");
    strcpy(permissions[fileCount].student,"r--");
    permissions[fileCount].encrypted = 0;
    fileCount++;
    printf("Assignment file created successfully.\n");
    writeLog("Created", filename);
    fclose(fp);
}
// Read Assignment File
void readFile()
{
    char filename[50];
    char ch;
    int i;
    int found = 0;
    printf("\nEnter Assignment File Name: ");
    scanf("%49s", filename);
    for(i = 0; i < fileCount; i++){
        if(strcmp(filename, permissions[i].filename) == 0){
            found = 1;
            if(strcmp(role, "Lecturer") == 0){
                if(strchr(permissions[i].lecturer, 'r') == NULL){
                    printf("Read Permission Denied.\n");
                    return;}
                    }
            else{
                if(strchr(permissions[i].student, 'r') == NULL){
                    printf("Read Permission Denied.\n");
                    return;
                }
            }
            break;
        }
    }
    if(!found){
        printf("Permission record not found.\n");
        return;}
    FILE *fp = fopen(filename, "r");
    if(fp == NULL){
        printf("File not found.\n");
        return;}
    printf("\nFile Content\n");
    while((ch = fgetc(fp)) != EOF)
        putchar(ch);
    fclose(fp);
    writeLog("Read", filename);
}
// Write Assignment File
void writeFile()
{
    char filename[50];
    char text[1000];
    int i;
    int found = 0;
    printf("\nEnter Assignment File Name: ");
    scanf("%49s", filename);
    for(i = 0; i < fileCount; i++)
    {
        if(strcmp(filename, permissions[i].filename) == 0)
        {
            found = 1;
            if(strcmp(role, "Lecturer") == 0)
            {
                if(strchr(permissions[i].lecturer, 'w') == NULL)
                {
                    printf("Write Permission Denied.\n");
                    return;
                }
            }
            else
            {
                if(strchr(permissions[i].student, 'w') == NULL)
                {
                    printf("Write Permission Denied.\n");
                    return;
                }
            }
            break;
        }
    }
    if(!found)
    {
        printf("Permission record not found.\n");
        return;
    }
    FILE *fp = fopen(filename, "a");
    if(fp == NULL)
    {
        printf("File not found.\n");
        return;
    }
    getchar();
    printf("Enter text:\n");
    fgets(text, sizeof(text), stdin);
    fprintf(fp, "%s", text);
    fclose(fp);
    writeLog("Written", filename);
    printf("Content written successfully.\n");
}
//EXECUTE
void executeFile() {
    char filename[50];
    int i;
    printf("\nEnter Assignment File Name: ");
    scanf("%s", filename);
    int found = 0;
    for(i=0;i<fileCount;i++){
        if(strcmp(filename,permissions[i].filename)==0){
            found = 1;
                if(strcmp(role,"Lecturer")==0)
                {
                    if(strchr(permissions[i].lecturer,'x')==NULL)
                    {
                        printf("Execute Permission Denied.\n");
                        return;
                    }
                }
                else
                {
                    if(strchr(permissions[i].student,'x')==NULL)
                    {
                        printf("Execute Permission Denied.\n");
                        return;
                    }
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
        writeLog("Deleted", filename);
    }
    else{
        printf("File not found or unable to delete.\n");
    }
}
void managePermission()
{
    char filename[50];
    int i;
    printf("\nEnter Assignment File Name: ");
    scanf("%s", filename);
    for(i=0;i<fileCount;i++)
    {
        if(strcmp(filename,permissions[i].filename)==0)
        {
            printf("Lecturer Permission (e.g. rwx): ");
            scanf("%3s", permissions[i].lecturer);
            printf("Student Permission (e.g. r--): ");
            scanf("%3s", permissions[i].student);
            printf("Permissions Updated Successfully.\n");
            writeLog("Permission Changed", filename);
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
            printf("Lecturer : %s\n", permissions[i].lecturer);
            printf("Student  : %s\n", permissions[i].student);
            printf("Encrypted : %s\n",
            permissions[i].encrypted ? "Yes" : "No");
            return;
        }
    }
    printf("File not found.\n");
}
//ENCRYPTION (Caesar-Cipher)
void encryptFile()
{
    char filename[50];
    int i,j;
    printf("\nEnter Assignment File Name: ");
    scanf("%s", filename);
    for(i=0;i<fileCount;i++)
    {
        if(strcmp(filename,permissions[i].filename)==0)
        {
            FILE *fp=fopen(filename,"r+");
            if(fp==NULL)
            {
                printf("File not found.\n");
                return;
            }
            char ch;
            while((ch=fgetc(fp))!=EOF)
            {
                fseek(fp,-1,SEEK_CUR);
                if(ch>='A'&&ch<='Z')
                    ch=((ch-'A'+3)%26)+'A';
                else if(ch>='a'&&ch<='z')
                    ch=((ch-'a'+3)%26)+'a';
                fputc(ch,fp);
            }
            fclose(fp);
            permissions[i].encrypted=1;
            printf("File encrypted successfully.\n");
            writeLog("Encrypted", filename);
            return;
        }
    }
    printf("File not found.\n");
}
//decryption
void decryptFile()
{
    char filename[50];
    int i;
    printf("\nEnter Assignment File Name: ");
    scanf("%s", filename);
    for(i=0;i<fileCount;i++)
    {
        if(strcmp(filename,permissions[i].filename)==0)
        {
            FILE *fp=fopen(filename,"r+");
            if(fp==NULL)
            {
                printf("File not found.\n");
                return;
            }
            char ch;
            while((ch=fgetc(fp))!=EOF)
            {
                fseek(fp,-1,SEEK_CUR);
                if(ch>='A'&&ch<='Z')
                    ch=((ch-'A'-3+26)%26)+'A';
                else if(ch>='a'&&ch<='z')
                    ch=((ch-'a'-3+26)%26)+'a';
                fputc(ch,fp);
            }
            fclose(fp);
            permissions[i].encrypted=0;
            printf("File decrypted successfully.\n");
            writeLog("Decrypted", filename);
            return;
        }
    }
    printf("File not found.\n");
}
//Logging
void writeLog(char action[],char filename[])
{
    FILE *fp=fopen("audit.log","a");
    if(fp==NULL)
        return;
    fprintf(fp,"%s : %s\n",action,filename);
    fclose(fp);
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
            printf("7. Encrypt Assignment File\n");
            printf("8. Decrypt Assignment File\n");
            printf("9. Logout\n");
            printf("10. Exit\n");
            printf("\nEnter your choice: ");
            if(scanf("%d", &choice) != 1){
              printf("Invalid Input!\n");
              while(getchar() != '\n');
              continue;}                      
            switch(choice)
            {
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
                    encryptFile();
                    break;
                case 8:
                    decryptFile();
                    break;
                case 9:
                    loggedIn = 0;
                    strcpy(role, "");
                    printf("Logged Out Successfully.\n");
                    break;
                case 10:
                    printf("Thank You!\n");
                    return 0;
                default:
                    printf("Invalid Choice!\n");
            }
        }
        //STUDENT MENU 
        else if(strcmp(role,"Student")==0){
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
