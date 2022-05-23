#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 20

int count = 0;
int buffer[BUFFER_SIZE];
int producer_idx, consumer_idx;
pthread_t tid;
pthread_mutex_t lock;

void insert(int item)
{
    while (count == BUFFER_SIZE)
        ;
    pthread_mutex_lock(&lock);
    buffer[count] = item;
    count++;
    pthread_mutex_unlock(&lock);
    sleep(1);
}

int remove_item()
{
    int item;
    while (count == 0)
        ;
    pthread_mutex_lock(&lock);
    item = buffer[count];
    count--;
    sleep(1);
    pthread_mutex_unlock(&lock);
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
    int producers = atoi(argv[1]);
    int consumers = atoi(argv[2]);
    int i;
    if (pthread_mutex_init(&lock, NULL))
    {
        printf("\nCould not init mutex");
        return 1;
    }

    for (i = 0; i < producers; i++)
        pthread_create(&tid, NULL, producer, NULL);

    for (i = 0; i < consumers; i++)
        pthread_create(&tid, NULL, consumer, NULL);

    pthread_join(tid, NULL);

    pthread_mutex_destroy(&lock);

    return 0;
}