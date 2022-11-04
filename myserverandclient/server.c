#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#define SER_PORT 1200
int main()
{
    int port = 50000;
    int a, sersock, newsock, n;
    char str[25], str2[25];
    char buffer[1024];
    struct sockaddr_in ServerAddress;
    struct sockaddr_in CliInfo;
    socklen_t Csize = sizeof(CliInfo);
    ServerAddress.sin_family = AF_INET;
    ServerAddress.sin_port = port;
    ServerAddress.sin_addr.s_addr = INADDR_ANY;
    if ((sersock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("\n socket");
        exit(1);
    }
    if (bind(sersock, (struct sockaddr *)&ServerAddress, sizeof(ServerAddress)) < 0)
    {
        perror("\nBIND");
        exit(1);
    }
    if (listen(sersock, 1) < 0)
    {
        perror("\n LISTEN");
    }
    printf("Listening...");
    if ((newsock = accept(sersock, (struct sockaddr *)&CliInfo, &Csize)) < 0)
    {
        perror("\n ACCEPT");
        exit(1);
    }
    else
        printf("\n now connected to %s\n", inet_ntoa(CliInfo.sin_addr));
    recv(newsock, str, sizeof(str),0);
    do
    {
        printf("\n client msg:%s", str);
        printf("\n server msg:");
        scanf("%s", str2);
        write(newsock, str2, sizeof(str2));
        listen(newsock, 1);
        read(newsock, str, sizeof(str));
        n = strcmp(str, "BYE");
        a = strcmp(str2, "BYE");
    } while (n != 0 || a != 0);
    close(newsock);
    close(sersock);
    return 0;
}