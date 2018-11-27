/** BeagleBone Blue code **/
#include <stdbool.h>
#include <stdio.h>
#include <inttypes.h>
#include <time.h>
#include <pthread.h>

#include "zhelpers.h"

/** outputs **/
/** FIXME **/
#define GPIO_0 45
#define GPIO_1 45
#define GPIO_2 45
#define GPIO_3 45

#define BUFFER_SIZE 256

static void getRandomFloat(float a){
    float x = (float)rand()/(float)(RAND_MAX/a);
    return x;
}

static void getString(){
    char* new_line;
    char* message_type = "@";
    uint_32t sampling_number;
    float volt_a = getRandomFloat(100.0);
    float volt_b = getRandomFloat(100.0);
    float volt_c = getRandomFloat(100.0);

    FILE *f = fopen("somefile.txt", "w");

    for(sampling_number = 0; sampling_number < 2000; ++sampling_number){
        sprintf(new_line, "%s%s:%08.4f,%08.4f,%08.4f\n", message_type, sampling_number, volt_a, volt_b, volt_c);
        fprintf(f, "%s", text);
        fflush();
        new_line = "";
    }

    fclose(f);
    return 0;
}

static char buffer[BUFFER_SIZE];
static uint_32 bufferCount = 0;

int main(void)
{
    //  Prepare our context and publisher
    void *context = zmq_ctx_new ();
    void *publisher = zmq_socket (context, ZMQ_PUB);
    int rc = zmq_bind (publisher, "tcp://*:5556");
    assert (rc == 0);

    while (1) {
        //  Send message to all subscribers
        char* update[BUFFER_SIZE];
        update = getString();
        s_send (publisher, update);
    }
    zmq_close (publisher);
    zmq_ctx_destroy (context);
    return 0;
}
