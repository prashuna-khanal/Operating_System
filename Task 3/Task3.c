#include <stdio.h>

int main() {
    int choice;

    do {
        printf("\n Secure File Management System \n");
        printf("1. Login\n");
        printf("2. Create File\n");
        printf("3. Read File\n");
        printf("4. Write File\n");
        printf("5. Delete File\n");
        printf("6. Set Permissions\n");
        printf("7. View Permissions\n");
        printf("8. Logout\n");
        printf("9. Exit\n");

        printf("\nEnter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                printf("Login.\n");
                break;
            case 9:
                printf("Thankyou.The END\n");
                break;
            default:
                printf("....\n");
        }

    } while(choice != 9);

    return 0;
}
