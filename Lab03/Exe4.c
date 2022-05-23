#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 20

int count = 0;
int buffer[BUFFER_SIZE];
int producer_idx, consumer_idx;
pthread_t tid;
pthread_mutex_t lock;
sem_t mutex;

void insert(int item)
{
    while (count == BUFFER_SIZE)
        ;
    buffer[count] = item;
    sem_wait(&mutex);
    count++;
    sem_post(&mutex);
    sleep(1);
}

int remove_item()
{
    int item;
    while (count == 0)
        ;
    item = buffer[count];
    sem_wait(&mutex);
    count--;
    sem_post(&mutex);
    sleep(1);
    return item;
}

void *producer(void *param)
{
    int item;
    while (1)
    {
        item = rand() % BUFFER_SIZE;
        insert(item);
        printf("inserted: %d\t", item);
    }
}

void *consumer(void *param)
{
    int item;
    while (1)
    {
        item = remove_item();
        printf("removed: %d\n", item);
    }
}

int main(int argc, char *argv[])
{
    int producers = atoi(argv[1]), consumers = atoi(argv[2]), i;

    sem_init(&mutex, 0, 1);

    for (i = 0; i < producers; i++)
        pthread_create(&tid, NULL, producer, NULL);

    for (i = 0; i < consumers; i++)
        pthread_create(&tid, NULL, consumer, NULL);

    pthread_join(tid, NULL);
    sem_destroy(&mutex);
    return 0;
}
