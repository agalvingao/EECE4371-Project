/** BeagleBone Blue code **/
#include "stdint.h"
#include "stdlib.h"
#include "zhelpers.h"
#include "sys/types"
#include "sys/stats"
#include <time.h>

#define SAMPLE_RATE 2000
#define LINE_LENGTH 33
#define PACKET_SAMPLES 400
#define BUFFER_SIZE (LINE_LENGTH * PACKET_SAMPLES + 1)

static FILE *f;

static double getRandomFloat(double min, double max){
    srand(time(0));
    double range = (max - min);
    double div = RAND_MAX / range;
    return min + (rand() / div);
}

static char* getString(void){
    char* new_line[LINE_LENGTH];
    int static index = 0;

    float volt_a = getRandomFloat(100.0, -30.0);
    float volt_b = getRandomFloat(100.0, -30.0);
    float volt_c = getRandomFloat(100.0, -30.0);
    double time_val = (double)index / (double)SAMPLE_RATE;

    sprintf(new_line, "%011.4f %+05.3f %+05.3f %+05.3f\n", time_val, volt_a, volt_b, volt_c);
    ++index;
    return new_line;
}

int main(void)
{
    mkfifo("../ECG_data.txt", 0666);
    f = fopen("../ECG_data.txt", "w");

    while(1){
        char* line = getString();
        fprintf(f, "%s", line);
        usleep(100);
    }

    fclose(f);
    return 0;
}
