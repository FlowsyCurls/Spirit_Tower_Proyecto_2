#include <winsock2.h>

#include <Ws2tcpip.h>

#include <stdio.h>

#include <string.h>



int main(int argc, char **argv)

{

    // Declare and initialize variables

    WSADATA            wsaData;

    SOCKET        slisten[16], NewConnection;

    char     *szPort = "7777";

    struct addrinfo            hints, * res=NULL, * ptr=NULL;

    int        count=0, rc;

    char     recvbuff[1024];

    int                    ByteReceived, i;



    // Initialize Winsock

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)

    {

        printf("Server: WSAStartup() failed with error code %ld\n", WSAGetLastError());

        return 1;

    }

    else

        printf("Server: WSAStartup() looks fine!\n");



    memset(&hints, 0, sizeof(hints));

    hints.ai_family = AF_UNSPEC;

    hints.ai_socktype = SOCK_STREAM;

    hints.ai_protocol = IPPROTO_TCP;

    hints.ai_flags = AI_PASSIVE;



    rc = getaddrinfo(NULL, szPort, &hints, &res);

    if (rc != 0)

    {

        printf("Server: getaddrinfo() failed with error code %ld\n", WSAGetLastError());

        WSACleanup();

        return 1;

    }

    else

        printf("Server: getaddrinfo() is OK...\n");



    ptr = res;



    while (ptr)

    {

        printf("\nServer: count value = %d\n", count);

        // Use the res struct info for listening...

        slisten[count] = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

        if (slisten[count] == INVALID_SOCKET)

        {

            printf("Server: socket() failed with error code %ld\n", WSAGetLastError());

            WSACleanup();

            return 1;

        }

        else

            printf("Server: socket() is OK...\n");



        // The res struct info

        printf("\n The address family: %d\n", res->ai_family);

        printf(" The socket type: %d\n", res->ai_socktype);

        printf(" The protocol: %d\n\n", res->ai_protocol);



        // Then bind

        rc = bind(slisten[count], ptr->ai_addr, ptr->ai_addrlen);



        if (rc == SOCKET_ERROR)

        {

            printf("Server: bind() failed with error code %ld\n", WSAGetLastError());

            WSACleanup();

            return 1;

        }

        else

            printf("Server: bind() is OK...\n");



        // Next, listen

        rc = listen(slisten[count], 10);



        if (rc == SOCKET_ERROR)

        {

            printf("Server: listen() failed with error code %ld\n", WSAGetLastError());

            WSACleanup();

            return 1;

        }

        else

        {

            printf("Server: listen() is OK...\n");

            NewConnection = SOCKET_ERROR;

            // While the NewConnection socket equal to SOCKET_ERROR

            // which is always true in this case...

            while(NewConnection == SOCKET_ERROR)

            {

                // Accept connection on the slisten[count] socket and assign

                // it to the NewConnection socket, let the slisten[count]

                // do the listening for more connection

                NewConnection = accept(slisten[count], NULL, NULL);

                printf("Server: accept() is OK...\n");

                printf("Server: New client got connected, ready to receive and send data...\n");



                // Wait for more connections by calling accept again on ListeningSocket (loop)

                // or start sending or receiving data on NewConnection.

                ByteReceived = recv(NewConnection, recvbuff, sizeof(recvbuff), 0);



                // When there is problem

                if ( ByteReceived == SOCKET_ERROR )

                {

                    printf("Server: recv() failed with error code %ld\n", WSAGetLastError());

                    WSACleanup();

                    break;

                }

                else

                {

                    printf("Server: recv() is OK....\n");

                    // Print the received bytes. Take note that this is the total

                    // byte received, it is not the size of the declared buffer

                    printf("Server: Bytes received: %d\n", ByteReceived);

                    // Print what those bytes represent

                    printf("Server: Those bytes are: \"");

                    // Print the string only, discard other

                    // remaining 'rubbish' in the 1024 buffer size

                    for(i=0;i < ByteReceived;i++)

                        printf("%c", recvbuff[i]);

                    printf("\"\n");

                }

            }

        }



        if(res->ai_protocol == 6)

        {

            printf("Doing the TCP shutdown on the receiving part...\n");

            shutdown(slisten[count], SD_RECEIVE);

        }



        closesocket(slisten[count]);

        count++;

        ptr = ptr->ai_next;

    }



    freeaddrinfo(res);

    WSACleanup();

    return 0;

}