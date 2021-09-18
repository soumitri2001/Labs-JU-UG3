











#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

int thread; 

struct matrices
{
    unsigned int **mat1;     unsigned int **mat2;     unsigned int **prod;     int dim;                 int num_cpus;        };

typedef struct matrices matrices;


void initializeMatrices(matrices *mat_struct)
{
    int dim = mat_struct->dim;

        mat_struct->mat1 = (unsigned int **)malloc(dim * sizeof(unsigned int *));
    mat_struct->mat2 = (unsigned int **)malloc(dim * sizeof(unsigned int *));
    mat_struct->prod = (unsigned int **)malloc(dim * sizeof(unsigned int *));

    for (int i = 0; i < dim; i++)
    {
                (mat_struct->mat1)[i] = (unsigned int *)malloc(dim * sizeof(unsigned int));
        (mat_struct->mat2)[i] = (unsigned int *)malloc(dim * sizeof(unsigned int));
        (mat_struct->prod)[i] = (unsigned int *)malloc(dim * sizeof(unsigned int));
    }

    srand(time(0)); 
    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
        {
                        (mat_struct->mat1)[i][j] = rand() % 2;
            (mat_struct->mat2)[i][j] = rand() % 2;

                        (mat_struct->prod)[i][j] = 0;
        }
    }
}


void *matrixMult_thread(void *arg)
{
    matrices *mat_args = (matrices *)arg;
    int dim = mat_args->dim;
    int num_cpus = mat_args->num_cpus;
    int cur_thr = thread;
    int num_rows = dim / num_cpus;

        for (int i = cur_thr * num_rows; i < (cur_thr + 1) * num_rows; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            for (int k = 0; k < dim; k++)
            {
                (mat_args->prod)[i][j] += (mat_args->mat1)[i][k] * (mat_args->mat2)[k][j];
            }
        }
    }

    thread++; 
    pthread_exit(0); }


void printMatrix(unsigned int **mat, int dim)
{
    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
}


int main(int argc, char **argv)
{

    if (argc != 4)
    {
                printf("Arguments of %s should be: <nos_threads> <dimension> <out_flag>", argv[0]);
        exit(1);
    }

        int num_cpus = atoi(argv[1]);
    int dim = atoi(argv[2]);
    int flag = atoi(argv[3]);

        if (dim % num_cpus != 0)
    {
        printf("Dimension of square matrices should be divisible by no. of CPUs for even distribution across threads.");
        exit(1);
    }

        matrices *mat_struct = (matrices *)malloc(sizeof(matrices));
    mat_struct->dim = dim;
    mat_struct->num_cpus = num_cpus;
    thread = 0;

    initializeMatrices(mat_struct); 
    

    pthread_t thread_ids[num_cpus]; 
        struct timeval start, end;
    double time_taken;

        gettimeofday(&start, NULL);

        for (int i = 0; i < num_cpus; i++)
    {
        pthread_attr_t attr;         pthread_attr_init(&attr);
        pthread_create(&thread_ids[i], &attr, matrixMult_thread, (void *)mat_struct);     }

        for (int i = 0; i < num_cpus; i++)
    {
        pthread_join(thread_ids[i], NULL);
    }

        gettimeofday(&end, NULL);

        time_taken = (end.tv_sec - start.tv_sec) * 1e6;
    time_taken += (end.tv_usec - start.tv_usec) * 1e-6;

        if (flag == 1)
    {
        printf("Matrix 1:\n");
        printMatrix(mat_struct->mat1, mat_struct->dim);

        printf("Matrix 2:\n");
        printMatrix(mat_struct->mat2, mat_struct->dim);

        printf("Matrix Product:\n");
        printMatrix(mat_struct->prod, mat_struct->dim);
    }

        printf("Time taken for the matrix multiplication using %d threads = %6f seconds\n", num_cpus, time_taken);
}