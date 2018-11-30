/** BeagleBone Blue code **/
#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"
#include "sys/types"
#include "sys/stats"
#include <string.h>
#include <time.h>
#include <unistd.h>

#define SAMPLE_RATE 2000
#define LINE_LENGTH 33
#define PACKET_SAMPLES 400
#define BUFFER_SIZE (LINE_LENGTH * PACKET_SAMPLES + 1)

static double getRandomFloat(double min, double max)
{
    double range = (max - min);
    double div = RAND_MAX / range;
    return min + (rand() / div);
}

static char* getString(void)
{
    char new_line[LINE_LENGTH];
    int static index = 0;

    float volt_a = getRandomFloat(-2.0, 2.0);
    float volt_b = getRandomFloat(-2.0, 2.0);
    float volt_c = getRandomFloat(-2.0, 2.0);
    double time_val = (double)index / (double)SAMPLE_RATE;

    sprintf(*new_line, "%011.4f % 05.3f % 05.3f % 05.3f\n", time_val, volt_a, volt_b, volt_c);
    ++index;
    return* new_line;
}

int main(void)
{
    system(rm-f "./ECG_data.txt");
    mkfifo("./ECG_data.txt", 0666);
    FILE *f = fopen("./ECG_data.txt", "w");

    srand(time(0));

    while(1){
        char* line = getString();
        fprintf(f, "%s", line);
        usleep(100);
    }

    fclose(f);
    return 0;
}
