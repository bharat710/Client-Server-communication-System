#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/types.h>
#include<stdbool.h>
#include<sys/shm.h>
#include<limits.h>
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int n1,n2,result;

bool checkprime(int n)
{
        for(int i=2;i<n;i++)
        {
        if((n%i)==0)
        {
                return false;
        }
}
return true;
}
void *addition ( void *arg )
{
        pthread_mutex_lock(&mutex);
        result = n1+n2;
        pthread_mutex_unlock(&mutex);
}
void *subtraction(void *arg)
{
        pthread_mutex_lock(&mutex);
        result = n1-n2;
        pthread_mutex_unlock(&mutex);
}
void *multiplication(void *arg)
{
        pthread_mutex_lock(&mutex);
        result = n1*n2;
        pthread_mutex_unlock(&mutex);
}

void *division(void *arg)
{
        pthread_mutex_lock(&mutex);
        result = n1/n2;
        pthread_mutex_unlock(&mutex);
}

void *Isprime(void *arg)
{
        pthread_mutex_lock(&mutex);
        if(checkprime(n1))
        {
                result = 1;
        }
        else result = 0;
        pthread_mutex_unlock(&mutex);
}

void *isOdd(void *arg)
{
        pthread_mutex_lock(&mutex);
        if(n1%2)
        {
                result = 1;
        }
        else result = 0;
        pthread_mutex_unlock(&mutex);
}

int main()
{
int shmID ;
int *shmptr, *temp;
int request ;
key_t K = 1998;
shmID = shmget(K,100,IPC_CREAT|0666);
if(shmID<0)
{
        printf("Error in Creating Shared Memory : /n");
        exit(0);
}
shmptr = shmat(shmID,NULL,0);
if(*shmptr==-1)
{
        printf("Error in Attaching Shared Memory to Server : /n");
        exit(0);
}
*shmptr = INT_MIN;
temp = shmptr ;
while(*temp==INT_MIN)
{
        sleep(1);
}
pthread_mutex_lock(&mutex);
int arr[1000] ;
int curruser = 0;
while(1)
{
int userID = *temp;
int userunique = 1;
temp++;
for(int i=0;i<curruser;i++)
{
if(userID == arr[i])
{
printf("User not Unique : /n ");
userunique = 0;
}
}
if(userunique)
{
printf("User is unique : /n ");
arr[curruser] = userID;
curruser++;
}
request = *temp;
temp++;
 n1 = *temp;
temp++;
 n2 = *temp;
temp++;
pthread_mutex_unlock(&mutex);
switch(request)
{
case 1 : {
printf("\nWorker process initiated successfully for Addition !\n");
pthread_t id;
pthread_create(&id, NULL,&addition,NULL);
        pthread_join(id, NULL);
        printf("Thread terminated\n");
       }
       break;
case 2 : {
printf("\nWorker process initiated successfully for Subtraction !\n");
pthread_t id;
pthread_create(&id, NULL,&subtraction,NULL);
        pthread_join(id, NULL);
        printf("Thread terminated\n");
        }
        break;
case 3 : {
printf("\nWorker process initiated successfully for Multiplication! \n");
pthread_t id;
pthread_create(&id, NULL,&multiplication,NULL);
        pthread_join(id, NULL);
        printf("Thread terminated\n");
        }
        break;
case 4 : {
printf("\nWorker process initiated successfully for Division ! \n");
pthread_t id;
pthread_create(&id, NULL,&division,NULL);
        pthread_join(id, NULL);
        printf("Thread terminated\n");
        }
        break;
case 5 : {
printf("\nWorker process initiated successfully for checking if number is Prime or Not ! \n");
pthread_t id;
pthread_create(&id, NULL,&Isprime,NULL);
        pthread_join(id, NULL);
        printf("Thread terminated\n");
}
         break;
case 6 : {
printf("\nWorker process initiated successfully for Checking if number is Even or Odd ! \n");
pthread_t id;
pthread_create(&id, NULL,&isOdd,NULL);
        pthread_join(id, NULL);
        printf("Thread terminated\n");
        }
        break;
}
*temp = result;
*shmptr = INT_MIN;
temp = shmptr ;
while(*temp==INT_MIN)
{
        sleep(1);
}
}

return 0;
}




