#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/types.h>
#include<stdbool.h>
#include<sys/shm.h>
#include<limits.h>
#include <pthread.h>
pthread_mutex_t lock;
int main()
{
    int shmID;
    int *shmptr, *temp;
    //int request, n1, n2, result;
    key_t K = 1998;
    shmID = shmget(K, 100, 0666);
    if (shmID < 0)
    {
        printf("Error in Accessing Shared Memory : \n");
        exit(0);
    }
    shmptr = shmat(shmID, NULL, 0);
    if (*shmptr == -1)
    {
        printf("Error in Attaching Shared Memory to Client : \n");
        exit(0);
    }
    temp = shmptr;
    int userID,request,num1,num2;
    printf("The Following Operations are : \n");
    printf("Press 1 for Addition of 2 numbers \n");
    printf("Press 2 for Subtraction of 2 numbers : \n");
    printf("Press 3 for Multiplication of 2 numbers : \n");
    printf("Press 4 for Division of 2 numbers : \n");
    printf("Press 5 for checking if the number is Prime or not : \n");
    printf("Press 6 for checking if number is even or odd: \n"); 
           
    printf("Enter the User ID  : ");
    scanf("%d", &userID);
    printf("\n");
     printf("Enter the Request : ");
    scanf("%d", &request);
    printf("\n");
    if((request>=1)&&(request<=4))
    {
    printf("Enter the first and second number  : ");
    scanf("%d %d", &num1,&num2);
    printf("\n");
    }
    else {
    printf("Enter the number  : ");
    scanf("%d", &num1);
    num2 = INT_MIN;
    printf("\n");
    }

    pthread_mutex_lock(&lock);
    temp++;
    *temp = request;
    temp++;
    *temp = num1;
    temp++;
    *temp = num2;
    temp++;
    int *res = temp;
    *res = INT_MIN;
    temp = shmptr;
    *temp = userID;
    while(*res==INT_MIN)
    {
    sleep(1);
    }
    int result = *res;
    pthread_mutex_unlock(&lock);
    if(request == 5)
    {
    if(result)
    {
    printf(" %d is Prime ",num1);
    }
    else {
    printf(" %d is not Prime ",num1);
    }
    }
    else if(request == 6)
    {
    if(result)
    {
    printf(" %d is Odd ",num1);
    }
    else {
    printf(" %d is Even ",num1);
    }
    }
    else {
    printf(" Result is %d : ",result);
    }
    printf("\n");
    
    return 0;
}

