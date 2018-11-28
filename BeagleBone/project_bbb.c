/** BeagleBone Blue code **/
#include "stdint.h"
#include "stdlib.h"
#include "zhelpers.h"

#define LINE_LENGTH 33
#define PACKET_SAMPLES 400
#define BUFFER_SIZE (LINE_LENGTH * PACKET_SAMPLES + 1)

static FILE *f;

static void getRandomFloat(float a){
    float x = (float)rand()/(float)(RAND_MAX/a);
    return x;
}

static char* getString(void){
    char* new_line[LINE_LENGTH];
    double time_stamp = 1;
    double volt_a = getRandomFloat(100.0);
    double volt_b = getRandomFloat(100.0);
    double volt_c = getRandomFloat(100.0);

    sprintf(new_line, "%011.4f %+05.3f %+05.3f %+05.3f\n", time_stamp, volt_a, volt_b, volt_c);
    return new_line;
}

static void getPacket(char* &buffer){
    char* new_line[LINE_LENGTH];

    //  null terminator
    buffer[BUFFER_SIZE] = 0;

    int i;
    for(i = 0; i < PACKET_SAMPLES; ++i){
        fgets(new_line, LINE_LENGTH, FILE *f);
        memcpy(&buffer[i*LINE_LENGTH], new_line, LINE_LENGTH);
        new_line = "";
    }
}

int main(void)
{
//    system("./start_ECG_driver.sh");
    f = fopen("../ECG_data.txt", "r");
    char* const buffer[BUFFER_SIZE];

    //  Prepare our context and publisher
    void *context = zmq_ctx_new ();
    void *publisher = zmq_socket (context, ZMQ_PUB);
    int rc = zmq_bind (publisher, "tcp://*:5556");
    assert (rc == 0);

    while (1) {
        char* line[LINE_LENGTH];
        getPacket(&buffer);
        s_send (publisher, buffer);
    }

    zmq_close (publisher);
    zmq_ctx_destroy (context);

    fclose(f);
    return 0;
}
