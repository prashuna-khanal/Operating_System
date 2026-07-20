#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void *handleClient(void *socket_desc)
{
    int clientSocket = *(int *)socket_desc;
    free(socket_desc);
    char buffer[BUFFER_SIZE];
    char username[50];
    char password[50];

    // Ask username
    send(clientSocket, "Username: ", 10, 0);
    memset(username, 0, sizeof(username));
    recv(clientSocket, username, sizeof(username), 0);
    username[strcspn(username, "\n")] = 0;

    // Ask password
    send(clientSocket, "Password: ", 10, 0);
    memset(password, 0, sizeof(password));
    recv(clientSocket, password, sizeof(password), 0);
    password[strcspn(password, "\n")] = 0;

    // Authentication
    if (strcmp(username, "admin") != 0 || strcmp(password, "1234") != 0)
    {
        send(clientSocket, "Authentication Failed\n", 22, 0);
        close(clientSocket);
        pthread_exit(NULL);
    }
    send(clientSocket, "Authentication Successful\n", 26, 0);

    while (1)
    {
        memset(buffer, 0, BUFFER_SIZE);
        int bytes = recv(clientSocket, buffer, BUFFER_SIZE, 0);
        if (bytes <= 0)
            break;
        buffer[strcspn(buffer, "\n")] = 0;
        if (strcmp(buffer, "TIME") == 0)
        {
            send(clientSocket, "Server Time Feature\n", 20, 0);
        }
        else if (strncmp(buffer, "ECHO ", 5) == 0)
        {
            send(clientSocket, buffer + 5, strlen(buffer + 5), 0);
        }
        else if (strcmp(buffer, "QUIT") == 0)
        {
            send(clientSocket, "Goodbye\n", 8, 0);
            break;
        }
        else
        {
            send(clientSocket, "Invalid Command\n", 16, 0);
        }
    }
    close(clientSocket);
    printf("Client disconnected.\n");
    pthread_exit(NULL);
}
int main()
{
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t clientLen = sizeof(clientAddr);
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0)
    {
        printf("Socket creation failed.\n");
        return 1;
    }
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
    listen(serverSocket, 5);
    printf("Server is running on port %d...\n", PORT);
    while (1)
    {
        clientSocket = accept(serverSocket,
                              (struct sockaddr *)&clientAddr,&clientLen);

        if (clientSocket < 0)
            continue;
        printf("Client connected.\n");
        pthread_t tid;
        int *newSocket = malloc(sizeof(int));
        *newSocket = clientSocket;
        pthread_create(&tid, NULL, handleClient, (void *)newSocket);
        pthread_detach(tid);
    }
    close(serverSocket);
    return 0;
}
