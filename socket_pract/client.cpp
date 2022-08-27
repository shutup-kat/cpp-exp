//
//  client.cpp
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
    int portnum, x;
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
    std::string lastnum;
};



void* createsocket(void *ptr)
{//gets digit
    struct grandChild *life = (struct grandChild *)ptr;
    //struct myanswer;
    int mysock;
    
    mysock = socket(AF_INET, SOCK_STREAM, 0);
    //if(mysock < 0){}
   
    long n=0;
    
    if(connect(mysock, (struct sockaddr *)&life->serv_addr, sizeof(life->serv_addr)) < 0)
    { std::cout << "ERROR connecting"; }
    
    life->ans.answer1 = life->digit;
    
    n = write(mysock, &life->ans, sizeof(struct myanswer)); //passes myanswer struct
    if(n < 0){  std::cout<<"ERROR writing to socket from client\n";   }
    
    
    char rev_back[30];
    n = read(mysock, &rev_back, sizeof(rev_back));
    if(n < 0)
    {
        std::cout<<"ERROR reading from socket from client\n";
        printf("this is digit: %d this is kui: %s ", life->digit,life->kui);
    }
    life->digit = life->ans.answer1;
    strcpy(life->kui, rev_back);
    close(mysock);
    
    return NULL;
}



//creates my child threads, sends them to other function to create GC and sockets, i send in whole number to be broken down

void* createthz(void *xp)
{
    
    //int x = *(int*) xp;
    struct thz *x = (struct thz*)xp;
    int size=0, me=0;
    std::stack<int> ataka;
    while(x->num>0)
    {
        me = x->num%10;
        ataka.push(me);
        x->num/=10;
        size++;
    }
    
    pthread_t th[size];
    struct grandChild * temp = new grandChild[size];
    int count=0;
    while(!ataka.empty())
    {
        temp[count].digit = ataka.top();
        temp[count].serv_addr = x->serv_addr;
        temp[count].portnum = x->portnum;
        ataka.pop();
        count++;
    }
    //in order after stack
    
    for(int i=0; i<size; i++)
    {
        
        if(pthread_create(&th[i], NULL, createsocket, &temp[i]) != 0)
        {std::cout << "couldn't create thread. "<<std::endl;}
    }
    
    //join here?
    for (int k=0; k<size; k++) {
        if (pthread_join(th[k], NULL) != 0)
        { std::cout << "couldn't joint threads " << std::endl;  }
    }
    
    //for loop to pass final answer back to child struct, x
   for(int i=0; i<size; i++)
    {
        x->lastnum += temp[i].kui;
    }
    
    
    return NULL;
}



int main(int argc, const char * argv[])
{
    
    if (argc < 2) {
        fprintf(stderr,"ERROR, no port provided\n");
        exit(1);
    }
    
    
    int portNum = atoi(argv[2]);
    struct sockaddr_in serv_addr;
    struct hostent *ho;
    long num = 0;
    int mysize = 0;
    std::vector<int> kat_main; // whole numbers in
    
    //taken from rincon code on BB
     ho = gethostbyname(argv[1]); // server address
     if(ho == NULL){  fprintf(stderr, "ERROR, no such host\n"); exit(0);  }
     
     bzero((char*)&serv_addr, sizeof(serv_addr));
     serv_addr.sin_family = AF_INET;
     bcopy((char*)ho->h_addr,(char *)&serv_addr.sin_addr.s_addr, ho->h_length);
     serv_addr.sin_port = htons(portNum);
    
    while(std::cin >> num)
    {
        kat_main.push_back(num);
        mysize++;
    }
    
    pthread_t th[mysize];
    struct thz * whole = new thz[mysize];
    
    for(int i=0; i<mysize; i++)
    {   whole[i].num = kat_main.at(i);
        whole[i].serv_addr = serv_addr;
        whole[i].portnum = portNum;
    }
    
    //call
    for(int i=0; i<mysize; i++)
    {
       if(pthread_create(&th[i], NULL, createthz, &whole[i]) != 0)
       {std::cout << "couldn't create thread. "<<std::endl;}
    }
    
    for (int k=0; k<mysize; k++) {
        if (pthread_join(th[k], NULL) != 0)
        { std::cout << "couldn't joint threads " << std::endl;  }
    }
    
    
    for(int i=0; i<mysize; i++)
    {
        std::cout << whole[i].lastnum;
        if(i+1 != mysize)
        {
            std::cout<<std::endl;
        }
    }
    
    delete [] whole;
    
    
    return 0;
}


