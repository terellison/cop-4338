#include<stdio.h>
#include<pthread.h>
#include <string.h>

pthread_mutex_t mutex;
int balance = 10000;

void* deposit(void* arg)
{
    for(int i = 0; i < 100;i++)
    {
        pthread_mutex_lock(&mutex);
        balance += (int)arg;
        pthread_mutex_unlock(&mutex);
    }
}
void* withdraw(void* arg)
{
    for(int i = 0; i < 100;i++)
    {
        pthread_mutex_lock(&mutex);
        balance -= (int)arg;
        pthread_mutex_unlock(&mutex);
    }
}

int main(int argc, char** argv){
    int thread_no = 1;//default # of deposit/withdraw threads
    //you can update this number by passing 
    //an integer as a command-line argument
    if(argc > 1)
        sscanf(strdup(argv[1]), "%d", &thread_no);
    fprintf(stderr,  "# of deposit threads: %d\n", thread_no); 
    fprintf(stderr,  "# of withdraw threads: %d\n", thread_no); 
    pthread_mutex_init(&mutex, NULL);
    pthread_t deposit_thread_id[thread_no];
    pthread_t withdraw_thread_id[thread_no];
    for(int i = 0;i  < thread_no;i++){
        pthread_create(&deposit_thread_id[i], NULL, deposit, (void*)100);//create a thread to deposit $100 100 times
        pthread_create(&withdraw_thread_id[i], NULL, withdraw, (void*)100);//create a thread to withdraw $100 100 times
    }
    for(int i = 0;i  < thread_no;i++){
        pthread_join(deposit_thread_id[i], NULL);
        pthread_join(withdraw_thread_id[i], NULL);
    }
    pthread_mutex_destroy(&mutex);
    printf("final balance: %d.\n", balance);
}