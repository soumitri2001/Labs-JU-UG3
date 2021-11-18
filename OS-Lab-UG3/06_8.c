/**
 * Group No.: 6 (Batch-A2)
 * Group Members : 1) Sk Asif      -- Roll No. 64
 *                 2) Sagnik Haldar -- Roll No. 74
 *                 3) Soumitri Chattopadhyay -- Roll No. 83
 * ------------------------------------------------------------------------------------------------------------------
 * Assignment No. : 8
 * ------------------------------------------------------------------------------------------------------------------
 * Assignment Details: The objective of this assignment is observing the OS through the /proc file system.
 * ------------------------------------------------------------------------------------------------------------------
 * Input Description: The program maybe run in two ways -- either in a default setup, or in a dynamic setup with CLI 
 *                    arguments. Running it without any parameter should print out information required for the first 
 *                    version (default version). Running it with two parameters "./a.out <read_rate> <printout_rate>" 
 *                    should print out information required for the second version [as stated in the question].
 * ------------------------------------------------------------------------------------------------------------------
 * Output Description: The first output block corresponds to the default version where no arguments have been passed. 
 *                     The information has been printed as specified in the question. 
 * 
 *                     The second block of output corresponds to the dynamic version of the program, the two argument 
 *                     representing the read and print rates (in seconds) respectively. The output contains all the 
 *                     information as asked in the question. Since this output is supposed to be non-terminating and
 *                     continuous, we have shown the first few output blocks only, to keep the comment block concise.
 * ------------------------------------------------------------------------------------------------------------------
 * Compilation sequence: gcc 06_8.c -lm -Werror
 * ==================================================================================================================
 * Execution sequence [FOR DEFAULT VERSION]: ./a.out
 * ------------------------------------------------------------------------------------------------------------------
 * Output: [FOR DEFAULT VERSION] 
 * 
 *          soumitri@LAPTOP-48UB98QH:~/OS-Lab-UG3$ ./a.out
 *          Number of cores: 4
 *          The processor is of type Quad Core
 *          Linux version 5.4.72-microsoft-standard-WSL2 (oe-user@oe-host) (gcc version 8.2.0 (GCC)) #1 SMP Wed Oct 28 23:40:43 UTC 2020
 *          Total memory: 6405072 KB
 *          Time since boot: 19344 seconds
 * ==================================================================================================================
 * Execution sequence [FOR CONTINUOUS/DYNAMIC VERSION]: ./a.out 2 10
 * ------------------------------------------------------------------------------------------------------------------
 * Output: [FOR CONTINUOUS/DYNAMIC VERSION]
 * 
 *          soumitri@LAPTOP-48UB98QH:~/OS-Lab-UG3$ ./a.out 2 10
 *          Processor times (percentage)            : %USER: 0.199956 | %SYSTEM: 0.089131 | %IDLE: 99.688253
 *          Free memory                             : 5671684 KB | %FREE  : 88.549899
 *          Available memory                        : 5760857 KB | %AVAIL : 89.942121
 *          Disk read rate  (per second)            : 3055.5556
 *          Disk write rate (per second)            : 1794008.1249
 *          Rate of context switching (per second)  : 234.2759
 *          Rate of process creation  (per second)  : 1.4955
 *          
 *          Processor times (percentage)            : %USER: 0.199887 | %SYSTEM: 0.089128 | %IDLE: 99.688326
 *          Free memory                             : 5671401 KB | %FREE  : 88.545478
 *          Available memory                        : 5760592 KB | %AVAIL : 89.937987
 *          Disk read rate  (per second)            : 3055.5556
 *          Disk write rate (per second)            : 1794008.1249
 *          Rate of context switching (per second)  : 234.2576
 *          Rate of process creation  (per second)  : 1.4973
 *          
 *          Processor times (percentage)            : %USER: 0.199809 | %SYSTEM: 0.089112 | %IDLE: 99.688424
 *          Free memory                             : 5670795 KB | %FREE  : 88.536010
 *          Available memory                        : 5760004 KB | %AVAIL : 89.928806
 *          Disk read rate  (per second)            : 3055.5556
 *          Disk write rate (per second)            : 1794008.1249
 *          Rate of context switching (per second)  : 234.2341
 *          Rate of process creation  (per second)  : 1.4988
 *          
 *          Processor times (percentage)            : %USER: 0.199738 | %SYSTEM: 0.089088 | %IDLE: 99.688523
 *          Free memory                             : 5670812 KB | %FREE  : 88.536273
 *          Available memory                        : 5760036 KB | %AVAIL : 89.929306
 *          Disk read rate  (per second)            : 3055.5556
 *          Disk write rate (per second)            : 1794008.1249
 *          Rate of context switching (per second)  : 234.2094
 *          Rate of process creation  (per second)  : 1.5004
 *          
 *          Processor times (percentage)            : %USER: 0.199676 | %SYSTEM: 0.089078 | %IDLE: 99.688593
 *          Free memory                             : 5670133 KB | %FREE  : 88.525681
 *          Available memory                        : 5759374 KB | %AVAIL : 89.918964
 *          Disk read rate  (per second)            : 3055.5556
 *          Disk write rate (per second)            : 1794008.1249
 *          Rate of context switching (per second)  : 234.1844
 *          Rate of process creation  (per second)  : 1.5019
 * 
 *          [...]
 * ------------------------------------------------------------------------------------------------------------------  
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <math.h>
#include <errno.h>

#define STRLEN 256 // constant for strings to be parsed in proc files

// defining a data structure for proc file information
typedef struct proc_data
{
    int cnt_vals;        // nos of parameters extracted from proc file
    double proc_vals[5]; // parameters extracted [max. possible length chosen is 5]
} proc_data;

/* the following functions are for the default version of the program [as stated in question] */

/* utility function for /proc/uptime */
int upTime()
{
    // variables to store data while parsing proc file
    char line[STRLEN];
    int timesinceboot;                          // to store the uptime value from the proc file
    FILE *uptime = fopen("/proc/uptime", "rb"); // to read the proc file

    // to validate file read
    if (uptime == NULL)
    {
        perror("The file could not be opened.\n");
        exit(1);
    }
    fscanf(uptime, "%s", line); // scans the line and takes input into string
    timesinceboot = atoi(line); // convert string to integer -- time since last booting
    fclose(uptime);             // closing the opened file
    return timesinceboot;
}

/* utility function for /proc/cpuinfo */
void proc_type()
{
    char line[STRLEN];                                            // variable used for file parsing
    int nos_cores;                                                // to store number of cpu cores from the proc file
    FILE *cpuinfo = popen("grep 'cpu cores' /proc/cpuinfo", "r"); // 'grep' command ensures extraction of the line containing the mentioned string

    // to validate the proper reading of file
    if (cpuinfo == NULL)
    {
        perror("The file could not be opened.\n");
        exit(1);
    }

    fscanf(cpuinfo, "%s %s %s %d", line, line, line, &nos_cores); // extracting the information from the line
    const char *cores[4];                                         // map to store conventional names for number of cores
    cores[0] = "Single Core";
    cores[1] = "Dual Core";
    cores[2] = "Quad Core";
    cores[3] = "Octa Core";
    printf("Number of cores: %d\n", nos_cores);                           // printing the number of cores
    printf("The processor is of type %s\n", cores[(int)log2(nos_cores)]); // printing type of processor based on conventional name
    fclose(cpuinfo);                                                      // closing the opened file
}

/* utility function for /proc/version */
void version()
{
    char line[STRLEN]; // variable used for text parsing in proc file
    FILE *version = fopen("/proc/version", "rb");

    // to validate the proper reading of file
    if (version == NULL)
    {
        perror("The file could not be opened.\n");
        exit(1);
    }
    // parsing the file till its end
    while ((fgets(line, STRLEN, version)) != NULL)
    {
        printf("%s", line); // printing the kernel information
    }
    fclose(version); // closing the file
}

/* utility function for /proc/meminfo in default version of code */
void meminfo_v1()
{
    char line[STRLEN];                           // variable used for text parsing
    FILE *memory = fopen("/proc/meminfo", "rb"); // opening the proc file in read mode

    // validating file opening
    if (memory == NULL)
    {
        perror("The file could not be opened.\n");
        exit(1);
    }
    long int mem_total;                          // to store total memory from proc file parsing
    fscanf(memory, "%s %ld", line, &mem_total);  // parsing the first line
    printf("Total memory: %ld KB\n", mem_total); //printing the total memory

    fclose(memory); // closing the opened file
}

/* utility function to obtain time since last boot (in seconds) */
void time_since_boot()
{
    int timesinceboot = upTime();                           // getting the time since boot from /proc/uptime
    printf("Time since boot: %d seconds\n", timesinceboot); // displaying the uptime information
}

/* function to sequentially implement the proc files as stated in question */
void default_info()
{
    proc_type();       // Processor type
    version();         // Kernel version
    meminfo_v1();      // The amount of memory configured into this computer
    time_since_boot(); // Amount of time since the system was last booted
}

/* the following functions are for the parameterized version of the program [as stated in question] */

/* utility function to get stats for dynamic version of program */
proc_data stat_v1()
{
    char lines[STRLEN];          // variable for text parsing in proc file
    long int cpu_mode_times[8];  // to store the different CPU mode times (e.g. user, idle, system etc.)
    long int total_cpu_time = 0; // to store the total cpu time
    double user, system, idle;
    FILE *time_spent = fopen("/proc/stat", "r"); // opening the /proc/stat file in read mode for parsing

    // validating file read
    if (time_spent == NULL)
    {
        perror("File could not be opened.");
        exit(1);
    }

    // parsing the file
    fgets(lines, STRLEN, time_spent);
    char *mode_times = strtok(lines, " "); // splitting the line into delimiter separated tokens
    int counter = 0;                       // counter variable to be used to extract the different cpu mode times
    mode_times = strtok(NULL, " ");        // starting from first token

    // iterating through the line to get every cpu mode time
    while (mode_times != NULL)
    {
        cpu_mode_times[counter] = atol(mode_times); // convert the string to long
        mode_times = strtok(NULL, " ");             // moving on to the next token
        total_cpu_time += cpu_mode_times[counter];  // summing up the individual times
        counter++;
    }

    // computing the percentage of times in user, system and idle modes
    user = (1.0 * cpu_mode_times[0] / total_cpu_time) * 100;
    system = (1.0 * cpu_mode_times[2] / total_cpu_time) * 100;
    idle = (1.0 * cpu_mode_times[3] / total_cpu_time) * 100;

    fclose(time_spent); // closing the opened file

    // wrapping the information into a struct to be returned
    proc_data data;
    data.proc_vals[0] = user;
    data.proc_vals[1] = system;
    data.proc_vals[2] = idle;
    data.cnt_vals = 3;

    return data; // returning the data structure after wrapping
}

/* utility function for /proc/meminfo in dynamic version of program */
proc_data meminfo_v2()
{
    char line[STRLEN];                                       // variable to be used for text parsing in proc file
    long int mem_total = 0, mem_free = 0, mem_available = 0; // initilising the memory detail variables
    FILE *memory = fopen("/proc/meminfo", "rb");             // opening the proc file in read mode

    // validate proper file reading
    if (memory == NULL)
    {
        perror("The file could not be opened.");
        exit(1);
    }

    // parsing through the file line-by-line to get the memory details
    fscanf(memory, "%s %ld %s", line, &mem_total, line);
    fscanf(memory, "%s %ld %s", line, &mem_free, line);
    fscanf(memory, "%s %ld %s", line, &mem_available, line);

    // compute the percentages of free and available memory
    double mem_available_percent, mem_free_percent;
    mem_available_percent = (1.0 * mem_available / mem_total) * 100;
    mem_free_percent = (1.0 * mem_free / mem_total) * 100;

    fclose(memory); // closing the opened file

    // wrapping the information into a struct to be returned
    proc_data data;
    data.proc_vals[0] = mem_free;
    data.proc_vals[1] = mem_available;
    data.proc_vals[2] = mem_free_percent;
    data.proc_vals[3] = mem_available_percent;
    data.cnt_vals = 4;

    return data; // returning the data structure after wrapping
}

/* utility function for "diskstats" proc file implementation */
proc_data diskstats()
{
    FILE *read_write = popen("grep '0 sda' /proc/diskstats", "r"); // 'grep' command ensures extraction of the line containing the mentioned string
    // to validate the proper reading of file
    if (read_write == NULL)
    {
        perror("The file could not be opened.\n");
        exit(1);
    }

    char read[20]; // for parsing the proc file
    int i = 0, counter = 0;
    long int diskstats_data[4]; // to store the disk statistics values required to be displayed
    while (fscanf(read_write, "%s", read) != EOF)
    {
        // file parsing and extraction of details
        if (i == 5 || i == 6 || i == 9 || i == 10)
            diskstats_data[counter++] = atol(read);
        i++;
    }

    // computing the read and write sector rates (per second)
    double read_sector_rate = (1000.0 * diskstats_data[0]) / diskstats_data[1];
    double write_sector_rate = (1000.0 * diskstats_data[2]) / diskstats_data[3];

    fclose(read_write); // closing the opened file

    // wrapping the information into a struct to be returned
    proc_data data;
    data.proc_vals[0] = read_sector_rate;
    data.proc_vals[1] = write_sector_rate;
    data.cnt_vals = 2;

    return data; // returning the data structure after wrapping
}

/* utility function to find rate of context switches using proc files */
proc_data context_switch()
{
    FILE *ctxt_switch = popen("grep 'ctxt' /proc/stat", "r"); // opening the file in read mode using 'grep' command to select a particular line containing 'ctxt' keyword
    // to validate the proper reading of file
    if (ctxt_switch == NULL)
    {
        perror("The file could not be opened.\n");
        exit(1);
    }
    char ctxt[5];                                            // for parsing the proc file
    long int nos_ctxt_switches;                              // to store the number of context switches
    fscanf(ctxt_switch, "%s %ld", ctxt, &nos_ctxt_switches); // reading the line present in the file
    int timesinceboot = upTime();                            // to get the time since last boot

    // computing the rate of context switching in the kernel (per second)
    double rate_ctxt_switch = 1.0 * nos_ctxt_switches / timesinceboot;

    fclose(ctxt_switch); // closing the opened file

    // wrapping the information into a struct to be returned
    proc_data data;
    data.proc_vals[0] = rate_ctxt_switch;
    data.cnt_vals = 1;

    return data; // returning the data structure after wrapping
}

/* utility function to get rate of process creation from /proc/stat */
proc_data stat_v2()
{
    char line[STRLEN];                                      // variable to parse text in proc file
    FILE *stat = popen("grep 'processes' /proc/stat", "r"); // opening the file for reading and selecting the line starting with 'processes'
    // to validate the proper reading of file
    if (stat == NULL)
    {
        perror("The file could not be opened.\n");
        exit(1);
    }

    int timesinceboot = upTime();                // to get the time since boot
    int num_processes;                           // variable to store the number of processes
    fscanf(stat, "%s %d", line, &num_processes); // reading the line and obtaining the number of processes from it

    // computing the rate of process creation (per second)
    double rate_proc_create = 1.0 * num_processes / timesinceboot;

    fclose(stat); // closing the opened file

    // wrapping the information into a struct to be returned
    proc_data data;
    data.proc_vals[0] = rate_proc_create;
    data.cnt_vals = 1;

    return data; // returning the data structure after wrapping
}

/* utility function to print the average values on the terminal */
void print_terminal(proc_data *data)
{
    // [1] The percentage of time the processor(s) spend in user mode, system mode, and idle mode
    printf("Processor times (percentage) \t\t: %%USER: %lf | %%SYSTEM: %lf | %%IDLE: %lf\n",
           data[0].proc_vals[0], data[0].proc_vals[1], data[0].proc_vals[2]);

    // [2] The amount and percentage of available (or free) memory
    printf("Free memory                  \t\t: %ld KB | %%FREE  : %lf\n", (long int)data[1].proc_vals[0], data[1].proc_vals[2]);
    printf("Available memory             \t\t: %ld KB | %%AVAIL : %lf\n", (long int)data[1].proc_vals[1], data[1].proc_vals[3]);

    // [3] The rate (number of sectors per second) of disk read/write in the system
    printf("Disk read rate  (per second) \t\t: %.4lf\n", data[2].proc_vals[0]);
    printf("Disk write rate (per second) \t\t: %.4lf\n", data[2].proc_vals[1]);

    // [4] The rate (number per second) of context switches in the kernel
    printf("Rate of context switching (per second) \t: %.4lf\n", data[3].proc_vals[0]);

    // [5] The rate (number per second) of process creations in the system
    printf("Rate of process creation  (per second) \t: %.4lf\n", data[4].proc_vals[0]);

    printf("\n"); // newline for enhanced display
}

/* utility function to execute sequential functions for the dynamic version of the program */
void dynamic_info(int read_rate, int print_rate)
{
    int proc_iterations = print_rate / read_rate; // to get the number of iterations in each cycle of display

    proc_data data[5]; // global array to store the accumulated values from each proc file
    for (int i = 0; i < 5; i++)
        memset(data[i].proc_vals, 0, sizeof(data[i].proc_vals)); // setting initial values to zero for accumulation

    proc_data temp; // for temporarily storing the date returned from each proc file
    for (int i = 0; i < proc_iterations; i++)
    {
        /* [1] The percentage of time the processor(s) spend in user mode, system mode, and idle mode */
        temp = stat_v1();
        assert(temp.cnt_vals == 3); // sanity check for value(s) returned
        data[0].cnt_vals = temp.cnt_vals;
        // to accumulate the values across iterations
        for (int j = 0; j < temp.cnt_vals; j++)
            data[0].proc_vals[j] += temp.proc_vals[j];

        /* [2] The amount and percentage of available (or free) memory */
        temp = meminfo_v2();
        assert(temp.cnt_vals == 4); // sanity check for value(s) returned
        data[1].cnt_vals = temp.cnt_vals;
        // to accumulate the values across iterations
        for (int j = 0; j < data[1].cnt_vals; j++)
            data[1].proc_vals[j] += temp.proc_vals[j];

        /* [3] The rate (number of sectors per second) of disk read/write in the system */
        temp = diskstats();
        assert(temp.cnt_vals == 2); // sanity check for value(s) returned
        data[2].cnt_vals = temp.cnt_vals;
        // to accumulate the values across iterations
        for (int j = 0; j < data[2].cnt_vals; j++)
            data[2].proc_vals[j] += temp.proc_vals[j];

        /* [4] The rate (number per second) of context switches in the kernel */
        temp = context_switch();
        assert(temp.cnt_vals == 1); // sanity check for value(s) returned
        data[3].cnt_vals = temp.cnt_vals;
        // to accumulate the values across iterations
        for (int j = 0; j < data[3].cnt_vals; j++)
            data[3].proc_vals[j] += temp.proc_vals[j];

        /* [5] The rate (number per second) of process creations in the system */
        temp = stat_v2();
        assert(temp.cnt_vals == 1); // sanity check for value(s) returned
        data[4].cnt_vals = temp.cnt_vals;
        // to accumulate the values across iterations
        for (int j = 0; j < data[4].cnt_vals; j++)
            data[4].proc_vals[j] += temp.proc_vals[j];

        sleep(read_rate); // delay the process by the read interval entered by the user
    }

    // computing the average values which are to be displayed
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < data[i].cnt_vals; j++)
            data[i].proc_vals[j] /= proc_iterations;
    }

    // finally, to display information on the terminal
    print_terminal(data);
}

/* main method */
int main(int argc, char **argv)
{
    // to validate arguments entered; if invalid we show appropriate prompt
    if (!(argc == 1 || argc == 3))
    {
        errno = 22; // error code for invalid argument
        perror("Incorrect number of arguments entered -- Arguments (OPTIONAL) should be [read_rate] [printout_rate]");
        exit(1);
    }

    if (argc == 1) // default version i.e. without any argument
    {
        // to print default system information (as specified)
        default_info();
    }
    else // dynamic version i.e. with read and print rates entered as arguments
    {
        int read_rate = atoi(argv[1]), print_rate = atoi(argv[2]); // extract the passed arguments

        // to validate each argument > 0 and read_rate <= print_rate; otherwise, the arguments are illegal
        if (read_rate > print_rate || print_rate <= 0 || read_rate <= 0)
        {
            errno = 22; // error code for invalid argument
            perror("Illegal arguments entered -- both arguments MUST be positive and [read_rate] <= [print_rate] MUST be satisfied for the program to work !");
            exit(1);
        }

        while (1)
        {
            // to print information continuously according to read and write rates
            dynamic_info(read_rate, print_rate);
        }
    }
    return 0;
}