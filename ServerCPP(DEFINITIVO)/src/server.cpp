#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include "algorithms/A_Star.h"
#include "algorithms/Bresenham.h"
#include <chrono>

#define BUFFERSIZE 2000

void algoritmTests();
void timeTest();
void printBuffer();

// Declare and initialize variables

WSADATA wsaData;
SOCKET s, NewConnection;
char *szPort = "7777";
struct addrinfo hints, * res=NULL, * ptr=NULL;
char buffer[BUFFERSIZE];
int ByteReceived, i;
int rc;

/**
 * Inicializa Winsock
 * @return 1 en caso de error y 0 si todo sale bien
 */
int initWinsock(){
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0){

        printf("Server: WSAStartup() failed with error code %ld\n", WSAGetLastError());
        return 1;
    }else{
        printf("Server: WSAStartup() looks fine!\n");
        return 0;
    }
}

void initHints(){
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;
}
/**
 * Limpia el buffer
 */
void clearBuffer(){

    fill_n(buffer, BUFFERSIZE, 0);
}
/**
 * Manda un mensaje al cliente
 * @param msg
 */
void sendMessage(string msg){

    strcpy(buffer,msg.c_str());

    ByteReceived = send( NewConnection, buffer, sizeof(buffer), 0 );
    cout << "Se ha enviado un mensaje al cliente: " << buffer << endl;

}
/**
 * Recibe un mensaje del cliente y lo almacena en el buffer de texto
 */
void receiveMessage(){

    cout << "En espera de un mensaje del cliente..." << endl;
    ByteReceived = recv(NewConnection, buffer, sizeof(buffer), 0);
    printBuffer();

}

int main(int argc, char **argv){

    //timeTest();

    // Initialize Winsock
    initWinsock();
    initHints();
    rc = getaddrinfo(NULL, szPort, &hints, &res);

    if (rc != 0){
        printf("Server: getaddrinfo() failed with error code %ld\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }else
        printf("Server: getaddrinfo() is OK...\n");

    ptr = res;

    while (ptr){


        // Use the res struct info for listening...
        s = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

        // Then bind
        rc = bind(s, ptr->ai_addr, ptr->ai_addrlen);

        // Next, listen
        rc = listen(s, 10);


        if (rc == SOCKET_ERROR){

            printf("Server: listen() failed with error code %ld\n", WSAGetLastError());
            WSACleanup();
            return 1;
        }else{

            printf("Server: listen() is OK...\n");
            NewConnection = SOCKET_ERROR;
            // While the NewConnection socket equal to SOCKET_ERROR
            // which is always true in this case...

            while(NewConnection == SOCKET_ERROR){

                // Accept connection on the s socket and assign
                // it to the NewConnection socket, let the s
                // do the listening for more connection


                NewConnection = accept(s, NULL, NULL);

                clearBuffer();

                receiveMessage();

                clearBuffer();

                sendMessage("Mensaje recibido");

                clearBuffer();

                receiveMessage();

                if(strcmp(buffer, "1") == 0){

                    cout << "opcion 1" << endl;

                }

            }

        }

        closesocket(s);

    }

    freeaddrinfo(res);
    WSACleanup();
    return 0;
}
/**
 * Imprime lo que tenga el buffer de texto
 */
void printBuffer(){

    printf("Se ha recibido un mensaje del cliente: %s\n",buffer );

}

/**
 * Test de tiempo que tarda en ejecutarse un algoritmo
 */
void timeTest(){
    auto start = std::chrono::high_resolution_clock::now();

    // operation to be timed ...
    algoritmTests();

    auto finish = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count() << "ns\n";
}

/**
 * Tests para los algoritmos a realizar
 */
void algoritmTests() {
    /* Description of the Grid-
    1--> The cell is not blocked
    0--> The cell is blocked */
    int grid[ROW][COL] =
            {
                    { 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
                    { 1, 1, 1, 0, 1, 1, 1, 0, 1, 1 },
                    { 1, 1, 1, 0, 1, 1, 0, 1, 0, 1 },
                    { 0, 0, 1, 0, 1, 0, 0, 0, 0, 1 },
                    { 1, 1, 1, 0, 1, 1, 1, 0, 1, 0 },
                    { 1, 0, 1, 1, 1, 1, 0, 1, 0, 0 },
                    { 1, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
                    { 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
                    { 1, 1, 1, 0, 0, 0, 1, 0, 0, 1 }
            };

    // Source is the left-most bottom-most corner
    Pair src = make_pair(8, 0);

    // Destination is the left-most top-most corner
    Pair dest = make_pair(0, 0);

    aStarSearch(grid, src, dest);

    //Bresenham
    Bresenham* b = new Bresenham;
    b->bresenham(3,2, 15,5);
}
