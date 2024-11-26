#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "HTTP.h"

int main(){
    int raspi_socket, client_socket;
    struct sockaddr_in raspi_addr, client_addr;
    int client_addr_len;

    int optval = 1;


    raspi_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (raspi_socket == -1)
    {
        perror("socket fail");
        return -1;
    }
    
    //////////////////////////////////  test용  /////////////////////////////////////////////
    setsockopt(raspi_socket, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
    /////////////////////////////////////////////////////////////////////////////////////////

    memset(&raspi_addr, 0, sizeof(raspi_addr));
    raspi_addr.sin_family = AF_INET;
    raspi_addr.sin_port = htons(8080);
    raspi_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(raspi_socket, (struct sockaddr *)&raspi_addr, sizeof(raspi_addr)) == -1)
    {
        perror("bind fail");
        return -1;
    }

    if (listen(raspi_socket, 5) == -1)
    {
        perror("listen fail");
        return -1;
    }
    while(1)
    {
        char requestBuf[BUFSIZ];

        memset(requestBuf, 0, BUFSIZ);

        client_socket = accept(raspi_socket, (struct sockaddr *)&client_addr, &client_addr_len);
        if (client_socket == -1)
        {
            perror("accept fail");
            return -1;
        }

        int pid = fork();
        if (pid > 0){
            close(client_socket);
            waitpid(pid, NULL, 0); // 자식 프로세스 종료 대기
            continue;
        }
        
        read(client_socket, requestBuf, BUFSIZ);

        struct request reqData;

        // request command parsing
        if (splitRequest(&reqData, requestBuf) != SUCCESS)
        {
            printf("fail SplitRequest function : %d\n", getLastErrCode());
            close(client_socket);
            exit(1);
        }
        
        // process request command
        if (strcmp(reqData.startLine.HTTP_method, "GET") == 0)
            processGetRequest(client_socket, reqData);
        // else if (strcmp(reqData.startLine.HTTP_method, "PUT") == 0)
        //     processPutRequest(client_socket, reqData);
        // else if (strcmp(reqData.startLine.HTTP_method, "STAT") == 0)
        //     processStatRequest(client_socket, reqData);
        else
            printf("command not find  : %s\n", reqData.startLine.HTTP_method);

        if (getLastErrCode() != SUCCESS)
            printf("fail process function : %d\n", getLastErrCode());
        
        close(client_socket);
        exit(0);
    }

    close(raspi_socket);
    return 0;
}

