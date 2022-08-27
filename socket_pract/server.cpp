//
//  main.cpp
//  socket_pract
//
//  Created by Kat hernandez on 10/28/21.
//

#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <vector>
#include <stack>
#include <sys/wait.h>



struct myanswer {
    int answer1;
    char answer2[30];
};


struct grandChild{
    int digit;
    int portnum, mysock, newsock, x;
    struct grandChild * grand;
    struct myanswer ans;
    struct hostent * server;
    struct sockaddr_in serv_addr;
    char kui[30];
   
};

struct thz {
    int num; //whole number
    char who [30];
    int portnum;
    struct sockaddr_in serv_addr;
    struct grandChild gc;
    int mysock, newsock;
};

void* printout(void* meme)
{
    struct grandChild *pth = (struct grandChild *) meme;
    int k = *(int*) meme;
    switch(k)
    {
        case 0 : strcpy(pth->kui, "0 = 1 1 1 1 1 1 0\n");
        break;
        case 1 : strcpy(pth->kui,"1 = 0 1 1 0 0 0 0\n");
        break;
        case 2 : strcpy(pth->kui, "2 = 1 1 0 1 1 0 1\n");
        break;
        case 3 : strcpy(pth->kui, "3 = 1 1 1 1 0 0 1\n");
        break;
        case 4 : strcpy(pth->kui, "4 = 0 1 1 0 0 1 1\n");
        break;
        case 5 : strcpy(pth->kui, "5 = 1 0 1 1 0 1 1\n");
        break;
        case 6 : strcpy(pth->kui, "6 = 1 0 1 1 1 1 1\n");
        break;
        case 7 : strcpy(pth->kui,"7 = 1 1 1 0 0 0 0\n");
        break;
        case 8 : strcpy(pth->kui, "8 = 1 1 1 1 1 1 1\n");
        break;
        case 9 : strcpy(pth->kui, "9 = 1 1 1 1 0 1 1\n");
        break;

        default : strcpy(pth->kui," no numbers here \n");
        break;

    }
    return NULL;
}


void fireman(int)
{//fireman code taken from Rincon Blackboard
    while(waitpid(-1,NULL,WNOHANG)>0)
    {
      //  std::cout << "A child process ended" << std::endl;
    }
}

int main(int argc, const char * argv[]) {
    //fireman code taken from Rincon Blackboard
    signal(SIGCHLD, fireman);
    
    if (argc < 2) {
        fprintf(stderr,"ERROR, no port provided\n");
        exit(1);
    }
    
    int mysock, newsock, server = atoi(argv[1]), clilen, mysize = 0;
    int portNum = atoi(argv[1]);
    //char buffer[bufsize];
    int n = 0;
    
    struct grandChild *gc ;
    struct sockaddr_in serv_addr, cli_addr;
   
    //pthread_t th[mysize];
    //struct thz * whole = new thz[mysize];
    
    
    struct sockaddr_in server_addr;
   // socklen_t size;
    
    mysock = socket(AF_INET, SOCK_STREAM, 0);
    
    if (mysock < 0)
    {
        std::cout << "Error opening socket. " << std::endl;
        exit(1);
    }
    
    bzero((char*) &serv_addr, sizeof(serv_addr));
    
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(portNum);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portNum);
    
    if( bind(mysock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        std::cout << "error binding socket " << std::endl;
        exit(1);
    }
    
    listen(mysock, 10); //how many requests can i listen to?
    clilen = sizeof(cli_addr);
    int pid;
    
    while(true)
    {
        if(listen(mysock, 10) < 0)
        {   std::cout << "error listening server\n"; }
        
        newsock = accept(mysock, (struct sockaddr*)&cli_addr, (socklen_t *)&clilen);
        if(newsock < 0)
        {
            std::cout << "error on accepting .." << std::endl;
            exit(1);
        }
        if ( newsock != -1 &&(pid = fork()) == 0)
        {
            break;
        }
    }
    // this is where i need to change code
    struct myanswer passed;
    //int digitpassed;
    n = read(newsock, &passed, sizeof(struct myanswer));
    if(n < 0)
    {std::cout << "ERROR reading from socket from server"<< std::endl; }
    char buffer[30];// passed.answer1 passed into switch, char copyed to buffer
    //switch?
       
    switch(passed.answer1)
    {
        case 0 : strcpy(buffer, "0 = 1 1 1 1 1 1 0\n");
        break;
        case 1 : strcpy(buffer,"1 = 0 1 1 0 0 0 0\n");
        break;
        case 2 : strcpy(buffer, "2 = 1 1 0 1 1 0 1\n");
        break;
        case 3 : strcpy(buffer, "3 = 1 1 1 1 0 0 1\n");
        break;
        case 4 : strcpy(buffer, "4 = 0 1 1 0 0 1 1\n");
        break;
        case 5 : strcpy(buffer, "5 = 1 0 1 1 0 1 1\n");
        break;
        case 6 : strcpy(buffer, "6 = 1 0 1 1 1 1 1\n");
        break;
        case 7 : strcpy(buffer,"7 = 1 1 1 0 0 0 0\n");
        break;
        case 8 : strcpy(buffer, "8 = 1 1 1 1 1 1 1\n");
        break;
        case 9 : strcpy(buffer, "9 = 1 1 1 1 0 1 1\n");
        break;

        default : strcpy(buffer," no numbers here \n");
        break;

    }; // was just (&gc)
    
    struct myanswer passedback;
   // strcpy(passed.answer2, buffer);
    n = write(newsock, &buffer, sizeof(buffer));
    if(n < 0)
    {std::cout << "ERROR writing to socket from server \n"<< std::endl;}
        
    close(newsock);
    
    close(mysock);

    return 0;
}

