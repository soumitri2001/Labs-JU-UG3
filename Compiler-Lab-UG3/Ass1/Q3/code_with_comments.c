/**
 * NAME: SOUMITRI CHATTOPADHYAY
 * ROLL: 001911001083
 * SUBJECT: SOFTWARE ENGG. LAB
 * ASSIGNMENT: MATRIX MULTIPLICATION USING A PARALLEL ALGORITHM
 */

/*-----------------------------------------------------------------------------------------------*/

/** 
 * COMPILE :  gcc 83_Soumitri_Chattopadhyay.c -o 83_Soumitri_Chattopadhyay -lpthread
 * EXECUTION :  ./83_Soumitri_Chattopadhyay <nos_threads> <dimension> <out_flag>
 *    
 * EXECUTION COMMAND :  ./83_Soumitri_Chattopadhyay 4 4 1
 *  
 * OUTPUT : 
 *    Matrix 1:
 *    0 0 0 1
 *    1 0 1 0
 *    1 0 0 1
 *    0 1 1 1
 *    Matrix 2:
 *    0 1 0 1
 *    0 0 1 1
 *    0 0 1 0
 *    1 0 0 1
 *    Matrix Product:
 *    1 0 0 1
 *    0 1 1 1
 *    1 1 0 2
 *    1 0 2 2
 *    Time taken for the matrix multiplication using 4 threads = 0.001721 seconds   
 */

/*---------------------------------------------------------------------------------------------------*/

/**
 * Diagnostics using mpstat:
 * 
 * EXECUTION COMMAND :  ./83_Soumitri_Chattopadhyay 8 1000 0
 * 
 * OUTPUT (obtained on running the execution command): 
 * Time taken for the matrix multiplication using 8 threads = 2000000.230758 seconds
 * 
 * COMMAND TO DIAGNOSE CPU USAGE (run simultaneously with the execution command) : mpstat -P ALL 1 1000
 * 
 * OUTPUT (obtained simultaneously from the 'mpstat' command) :
 * 
 * [CPU usage before the program was executed]
 *  21:47:56     CPU    %usr   %nice    %sys %iowait    %irq   %soft  %steal  %guest  %gnice   %idle
 *` 21:47:57     all    2.68    0.00    4.01    0.00    2.07    0.00    0.00    0.00    0.00   91.24
 *  21:47:57       0    0.00    0.00   12.84    0.00    8.26    0.00    0.00    0.00    0.00   78.90
 *  21:47:57       1    0.97    0.00    1.94    0.00    0.00    0.00    0.00    0.00    0.00   97.09
 *  21:47:57       2    0.00    0.00    9.43    0.00    6.60    0.00    0.00    0.00    0.00   83.96
 *  21:47:57       3    0.99    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00   99.01
 *  21:47:57       4    0.00    0.00    3.00    0.00    0.00    0.00    0.00    0.00    0.00   97.00
 *  21:47:57       5    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00
 *  21:47:57       6    0.00    0.00    3.92    0.00    0.98    0.00    0.00    0.00    0.00   95.10
 *  21:47:57       7   20.20    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00   79.80
 *
 * [CPU usage during execution of program]
 *  21:47:57     CPU    %usr   %nice    %sys %iowait    %irq   %soft  %steal  %guest  %gnice   %idle
 *  21:47:58     all   23.82    0.00    3.94    0.00    1.44    0.00    0.00    0.00    0.00   70.80
 *  21:47:58       0   16.67    0.00   12.12    0.00    9.85    0.00    0.00    0.00    0.00   61.36
 *  21:47:58       1   20.49    0.00    2.46    0.00    0.00    0.00    0.00    0.00    0.00   77.05
 *  21:47:58       2   21.43    0.00    3.17    0.00    0.00    0.00    0.00    0.00    0.00   75.40
 *  21:47:58       3   21.26    0.00    0.79    0.00    0.00    0.00    0.00    0.00    0.00   77.95
 *  21:47:58       4   25.78    0.00    1.56    0.00    0.00    0.00    0.00    0.00    0.00   72.66
 *  21:47:58       5   25.19    0.00    0.76    0.00    0.00    0.00    0.00    0.00    0.00   74.05
 *  21:47:58       6   27.61    0.00    1.49    0.00    0.00    0.00    0.00    0.00    0.00   70.90
 *  21:47:58       7   31.21    0.00    8.51    0.00    1.42    0.00    0.00    0.00    0.00   58.87
 *
 *  21:47:58     CPU    %usr   %nice    %sys %iowait    %irq   %soft  %steal  %guest  %gnice   %idle
 *  21:48:00     all   96.02    0.00    2.87    0.00    1.11    0.00    0.00    0.00    0.00    0.00
 *  21:48:00       0   93.47    0.00    6.53    0.00    0.00    0.00    0.00    0.00    0.00    0.00
 *  21:48:00       1   96.92    0.00    3.08    0.00    0.00    0.00    0.00    0.00    0.00    0.00
 *  21:48:00       2   83.73    0.00    8.13    0.00    8.13    0.00    0.00    0.00    0.00    0.00
 *  21:48:00       3  100.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00
 *  21:48:00       4   95.77    0.00    4.23    0.00    0.00    0.00    0.00    0.00    0.00    0.00
 *  21:48:00       5  100.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00
 *  21:48:00       6  100.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00
 *  21:48:00       7  100.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00
 *
 * [CPU usage after execution is completed]
 *  21:48:00     CPU    %usr   %nice    %sys %iowait    %irq   %soft  %steal  %guest  %gnice   %idle
 *  21:48:01     all    5.99    0.00    2.43    0.00    0.14    0.00    0.00    0.00    0.00   91.44
 *  21:48:01       0    2.30    0.00    4.60    0.00    0.00    0.00    0.00    0.00    0.00   93.10
 *  21:48:01       1    3.41    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00   96.59
 *  21:48:01       2    4.49    0.00    1.12    0.00    1.12    0.00    0.00    0.00    0.00   93.26
 *  21:48:01       3    3.45    0.00    2.30    0.00    0.00    0.00    0.00    0.00    0.00   94.25
 *  21:48:01       4    3.41    0.00    3.41    0.00    0.00    0.00    0.00    0.00    0.00   93.18
 *  21:48:01       5    3.45    0.00    3.45    0.00    0.00    0.00    0.00    0.00    0.00   93.10
 *  21:48:01       6    3.41    0.00    2.27    0.00    0.00    0.00    0.00    0.00    0.00   94.32
 *  21:48:01       7   24.14    0.00    2.30    0.00    0.00    0.00    0.00    0.00    0.00   73.56
 * 
 */

/*---------------------------------------------------------------------------------------------------*/

// header files
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

int thread; // stores current working thread that is incremented for every step

/* structure to hold the two matrices, their dimension, their product and nos of cpus */
struct matrices
{
    unsigned int **mat1; // first matrix
    unsigned int **mat2; // second matrix
    unsigned int **prod; // product matrix
    int dim;             // dimension of square matrix
    int num_cpus;        // nos of cpus i.e. threads to be used by user
};

typedef struct matrices matrices;

/* utility function to initialize matrices mat1,mat2,prod */
void initializeMatrices(matrices *mat_struct)
{
    int dim = mat_struct->dim;

    // dynamic memory allocation for the matrices
    mat_struct->mat1 = (unsigned int **)malloc(dim * sizeof(unsigned int *));
    mat_struct->mat2 = (unsigned int **)malloc(dim * sizeof(unsigned int *));
    mat_struct->prod = (unsigned int **)malloc(dim * sizeof(unsigned int *));

    for (int i = 0; i < dim; i++)
    {
        // dynamic memory allocation for each row of matrices
        (mat_struct->mat1)[i] = (unsigned int *)malloc(dim * sizeof(unsigned int));
        (mat_struct->mat2)[i] = (unsigned int *)malloc(dim * sizeof(unsigned int));
        (mat_struct->prod)[i] = (unsigned int *)malloc(dim * sizeof(unsigned int));
    }

    srand(time(0)); // setting seed for random number generation, the numbers will be different for every run of the program

    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            // any integer modulo 2 results in either 0 or 1
            (mat_struct->mat1)[i][j] = rand() % 2;
            (mat_struct->mat2)[i][j] = rand() % 2;

            // product matrix to be initialized with 0s
            (mat_struct->prod)[i][j] = 0;
        }
    }
}

/* utility function to perform matrix multiplication on a given thread */
void *matrixMult_thread(void *arg)
{
    matrices *mat_args = (matrices *)arg;
    int dim = mat_args->dim;
    int num_cpus = mat_args->num_cpus;
    int cur_thr = thread;
    int num_rows = dim / num_cpus;

    // perfom matrix multiplication on the rows specific to that thread only
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

    thread++; // going to next thread

    pthread_exit(0); // exit thread
}

/* utility function to print matrix */
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

/* main() method */
int main(int argc, char **argv)
{

    if (argc != 4)
    {
        // parameter mismatch
        printf("Arguments of %s should be: <nos_threads> <dimension> <out_flag>", argv[0]);
        exit(1);
    }

    // extracting command line input arguments
    int num_cpus = atoi(argv[1]);
    int dim = atoi(argv[2]);
    int flag = atoi(argv[3]);

    // if the matrix cannot be split equally among the CPUs, print appropriate error message and exit
    if (dim % num_cpus != 0)
    {
        printf("Dimension of square matrices should be divisible by no. of CPUs for even distribution across threads.");
        exit(1);
    }

    // create structure and store relevant values
    matrices *mat_struct = (matrices *)malloc(sizeof(matrices));
    mat_struct->dim = dim;
    mat_struct->num_cpus = num_cpus;
    thread = 0;

    initializeMatrices(mat_struct); // initialising the 2 random matrices and the product matrix

    /* threading related code starts here */

    pthread_t thread_ids[num_cpus]; // creating array of thread IDs

    // initialising variables for evaluating execution time
    struct timeval start, end;
    double time_taken;

    // start timer
    gettimeofday(&start, NULL);

    // loop over all threads for parallel processing
    for (int i = 0; i < num_cpus; i++)
    {
        pthread_attr_t attr; // create attribute for thread
        pthread_attr_init(&attr);
        pthread_create(&thread_ids[i], &attr, matrixMult_thread, (void *)mat_struct); // creating thread
    }

    // waiting for the threads to complete working
    for (int i = 0; i < num_cpus; i++)
    {
        pthread_join(thread_ids[i], NULL);
    }

    // end timer
    gettimeofday(&end, NULL);

    // evaluate execution time
    time_taken = (end.tv_sec - start.tv_sec) * 1e6;
    time_taken += (end.tv_usec - start.tv_usec) * 1e-6;

    // if output flag equals 1, print all matrices
    if (flag == 1)
    {
        printf("Matrix 1:\n");
        printMatrix(mat_struct->mat1, mat_struct->dim);

        printf("Matrix 2:\n");
        printMatrix(mat_struct->mat2, mat_struct->dim);

        printf("Matrix Product:\n");
        printMatrix(mat_struct->prod, mat_struct->dim);
    }

    // print execution time of code
    printf("Time taken for the matrix multiplication using %d threads = %6f seconds\n", num_cpus, time_taken);
}