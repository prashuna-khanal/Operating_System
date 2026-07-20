#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main()
{
    int clientSocket;
    struct sockaddr_in serverAddr;

    char buffer[BUFFER_SIZE];

    clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(clientSocket,
                (struct sockaddr *)&serverAddr,
                sizeof(serverAddr)) < 0)
    {
        printf("Connection Failed.\n");
        return 1;
    }

    // Username
    memset(buffer, 0, BUFFER_SIZE);
    recv(clientSocket, buffer, BUFFER_SIZE, 0);
    printf("%s", buffer);

    fgets(buffer, BUFFER_SIZE, stdin);
    send(clientSocket, buffer, strlen(buffer), 0);

    // Password
    memset(buffer, 0, BUFFER_SIZE);
    recv(clientSocket, buffer, BUFFER_SIZE, 0);
    printf("%s", buffer);

    fgets(buffer, BUFFER_SIZE, stdin);
    send(clientSocket, buffer, strlen(buffer), 0);

    // Authentication result
    memset(buffer, 0, BUFFER_SIZE);
    recv(clientSocket, buffer, BUFFER_SIZE, 0);
    printf("%s", buffer);

    if (strstr(buffer, "Failed"))
    {
        close(clientSocket);
        return 0;
    }

    while (1)
    {
        printf("\nCommands:\n");
        printf("TIME\n");
        printf("ECHO <message>\n");
        printf("QUIT\n");

        printf("Enter Command: ");

        fgets(buffer, BUFFER_SIZE, stdin);

        send(clientSocket, buffer, strlen(buffer), 0);

        memset(buffer, 0, BUFFER_SIZE);

        recv(clientSocket, buffer, BUFFER_SIZE, 0);

        printf("Server: %s\n", buffer);

        if (strncmp(buffer, "Goodbye", 7) == 0)
            break;
    }

    close(clientSocket);

    return 0;
}
