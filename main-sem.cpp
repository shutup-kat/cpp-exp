//
//  main.cpp
//  cosc3360-hw3
//
//  Created by Kat hernandez on 11/16/21.
//

#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <vector>
#include <stack>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <fcntl.h>

using namespace std;


struct grand_semmie
{
    string *who;
    int turns;
    sem_t *mySem;
    int numID;
};


struct semmie
{
    pthread_mutex_t *ksem;
    pthread_cond_t *mywait;
    pthread_mutex_t *zsem;
    sem_t *mySem;
    int numID;
    int threadnum;
    string x;
    int *turns;
};


//grandchild function that recieved digit from child, gives new data to same mem space
void* theGrandChild(void * param)
{
    //*(void pointer passed into function which has digit from child).memloc = ; help from classmate
    struct grand_semmie pth = *(struct grand_semmie *) param;
    sem_post(pth.mySem);
    
    switch(pth.numID)
    {
        case 0 : *pth.who = "0 = 1 1 1 1 1 1 0\n";
        break;
        case 1 : *pth.who = "1 = 0 1 1 0 0 0 0\n";
        break;
        case 2 : *pth.who = "2 = 1 1 0 1 1 0 1\n";
        break;
        case 3 : *pth.who = "3 = 1 1 1 1 0 0 1\n";
        break;
        case 4 : *pth.who = "4 = 0 1 1 0 0 1 1\n";
        break;
        case 5 : *pth.who = "5 = 1 0 1 1 0 1 1\n";
        break;
        case 6 : *pth.who = "6 = 1 0 1 1 1 1 1\n";
        break;
        case 7 : *pth.who = "7 = 1 1 1 0 0 0 0\n";
        break;
        case 8 : *pth.who = "8 = 1 1 1 1 1 1 1\n";
        break;
        case 9 : *pth.who = "9 = 1 1 1 1 0 1 1\n";
        break;

        default : *pth.who = " no numbers here \n";
        break;

    }
    
    return NULL;
}


//child function, gets whole number, first breaks into digits with a stack; silly is dedicated memeory space for grandchild to use for final answer
void* myChild(void * param)
{
    //lock
    struct semmie mypoint = *(struct semmie *) param;
    //continued critical section
    sem_post(mypoint.mySem);
    sem_t *mySemmie;
    string unique = "rinconlkpkrf" + to_string(mypoint.threadnum); //*HAS TO CHANGE EVERYTIME*
    mySemmie = sem_open( unique.c_str(), O_CREAT, 0666, 0);
    if(mySemmie == SEM_FAILED)
    { fprintf(stderr,"ERROR, sem_open in child function)\n"); }
    
    int size=0, me=0, count=0, var1=0; //recycled from my PA 1 and 2
    stack<int> ataka;
    var1 = mypoint.numID; //temp var as to not delete original number
    while (var1 > 0) {
        me = var1%10;
        ataka.push(me);
        var1 /= 10;
        size++;
    }
    string * silly = new string [size];
    int temp [size];
    while (!ataka.empty()) {
        temp[count] = ataka.top();
        ataka.pop();
        count++;
    }
    pthread_t *th = new pthread_t[size];
    struct grand_semmie bby;
    bby.mySem = mySemmie;
    for (int i=0; i<size; i++) {
        bby.numID = temp[i];
        bby.who = &silly[i];
        if (pthread_create(&th[i], NULL, theGrandChild, &bby) !=0 ) {
            cout << "couldn't create thread" << endl;
        }
        //start of critical section
        sem_wait(mySemmie);
    }
    
    for (int i=0; i<size; i++)
    {   pthread_join(th[i], NULL);  }
    //critical section
    pthread_mutex_lock(mypoint.ksem);
    while (*mypoint.turns != mypoint.threadnum) {
        pthread_cond_wait(mypoint.mywait, mypoint.ksem);
    }
    pthread_mutex_unlock(mypoint.ksem);
    for(int i=0; i<size; i++)
    {   cout << silly[i];   }
    
    (* mypoint.turns ) += 1;
    //critical section
    pthread_mutex_lock(mypoint.ksem);
    pthread_cond_broadcast(mypoint.mywait);
    pthread_mutex_unlock(mypoint.ksem);
    
    sem_unlink(unique.c_str());
    sem_close(mySemmie);
    delete [] th;
    
    return NULL;
}



int main(int argc, const char * argv[]) {
    
    
    semmie s;
    long val;
    int k=0, turn = 0;
    vector<int> katvec;
    pthread_mutex_t katsem = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t theirwait = PTHREAD_COND_INITIALIZER;
    pthread_mutex_t zimsem = PTHREAD_MUTEX_INITIALIZER;
    
    while(cin>>val)
    {
        katvec.push_back(val);
        k++; //size
    }
    
    
    pthread_t *th = new pthread_t [k];
   
    char semaph [] = "katelynnmkstdu"; //*CHANGE EVERY RUN*
    sem_t *mysemmie;
    mysemmie = sem_open( semaph, O_CREAT, 0666, 0); //semaphore creation
    s.ksem = &katsem;
    s.mywait = &theirwait;
    s.zsem = &zimsem;
    
    if(mysemmie == SEM_FAILED)
    { fprintf(stderr,"ERROR, sem_open in main)\n"); }
    
    s.mySem = mysemmie;
    s.turns = &turn;
    
    for(int i=0; i<k; i++)
    {
        s.numID = katvec.at(i);
        s.threadnum = i;
        
        if(pthread_create(&th[i], NULL, myChild, &s) != 0)
        {   cout << "couldn't create thread" << endl;   }
        //start of critical section
        sem_wait(mysemmie);
    }
    
    for (int i=0; i<k; i++) {
        if (pthread_join(th[i], NULL) != 0)
        { cout << "couldn't joint threads " << endl;  }
    }
    
    sem_unlink(semaph);
    sem_close(mysemmie);
    delete [] th;
    
    return 0;
}
