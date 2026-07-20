#include <stdio.h>

int main() {
    int choice;

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
                printf("Login feature coming soon.\n");
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
                printf("Logout feature coming soon.\n");
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
