#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/* this data is shared by the thread(s) */
int num_threads;
unsigned long long iterations;
double *partial_answers;

void *runner(void *param);
void thread_indexes(int thread_id, int num_iters, int num_threads, int start_end[]);
double pi_partial_terms(int term, int start_idx, int end_idx);

int main(int argc, char *argv[])
{

    if (argc != 3)
    {
        fprintf(stderr, "usage: a.out <iterations> <threads>\n");
        return -1;
    }
    if (atoi(argv[1]) < 0 || atoi(argv[2]) < 0)
    {
        fprintf(stderr, "Arguments must be non-negative\n ");
        return -1;
    }

    iterations = atoi(argv[1]);
    num_threads = atoi(argv[2]);

    partial_answers = (double *)calloc(num_threads, sizeof(double));

    /* create the thread identifiers */
    pthread_t threads[num_threads];
    int threads_vals[num_threads];

    /* create threads */
    int ids[num_threads];

    for (int i = 0; i < num_threads; i++)
    {
        ids[i] = i;
    }

    int id = 0;
    for (id = 0; id < num_threads; id++)
    {
        pthread_attr_t attributes;
        pthread_attr_init(&attributes);
        threads_vals[ids[id]] = pthread_create(&threads[id], &attributes, (void *)runner, &ids[id]);
        pthread_join(threads[id], NULL);
    }

    /* compute and print results */
    double sum_of_partials = 0;
    for (int i = 0; i < num_threads; i++)
    {
        sum_of_partials += partial_answers[i];
    }
    double pi = 4 * sum_of_partials;
    printf("Newton's Pi Approximation is ... %.15f\n", pi);
    free(partial_answers);
}

void *runner(void *param)
{
    int *threadid_ptr = ((int *)param);
    int id = *threadid_ptr;
    int idxs[2];
    thread_indexes(id, iterations, num_threads, idxs);
    partial_answers[id] = pi_partial_terms(0, idxs[0], idxs[1]);
    pthread_exit(0);
}

void thread_indexes(int thread_id, int num_iters, int num_threads, int start_end[])
{
    int terms = (int)ceil(num_iters / num_threads);
    if (terms % 2 != 0 && thread_id == 0)
    {
        start_end[0] = 0;
        start_end[1] = terms;
        return;
    }
    if (terms % 2 == 0)
    {
        start_end[0] = thread_id * terms;
        start_end[1] = (thread_id + 1) * terms - 1;
    }
    if (terms % 2 != 0)
    {
        start_end[0] = thread_id * terms + 1;
        start_end[1] = (thread_id + 1) * terms;
    }
}

double pi_partial_terms(int term, int start_idx, int end_idx)
{
    double partial = 0.0000000;
    for (int i = start_idx; i <= end_idx; i++)
    {
        double exp = pow(-1, i);
        partial += exp / ((2 * i) + 1);
    }
    return partial;
}
