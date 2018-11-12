/** BeagleBone Blue code **/
#include <stdbool.h>
#include <stdio.h>
#include <inttypes.h>
#include <time.h>

#include "zhelpers.h"
#include "assert.h"

/** outputs **/
/** FIXME **/
#define GPIO_0 45
#define GPIO_1 45
#define GPIO_2 45
#define GPIO_3 45

#define BUFFER_SIZE 256

/** analog data struct for ECG data **/
struct ADASSignal {
	struct timespec timeStamp;
	char buffer[200];       // FIXME
};

/** read in analog data into data struct **/
void readData(ADASSignal data){
    char buffer [BUFFER_SIZE];
    /** FIXME **/


    data.buffer = buffer;
	clock_gettime(CLOCK_REALTIME, &data.timeStamp);
    return;
}

/** send data contained in data struct **/
void sendData(void* publisher, ADASSignal data){
    char buffer [BUFFER_SIZE];
    sprintf (buffer, "%" PRIu64 ":%" PRIu64 "=%s", data.timeStamp->tv_sec, data.timeStamp->tv_nsec, data.buffer);
    s_send (publisher, buffer);
}

int main(void){
    void *context = zmq_ctx_new ();
    void *publisher = zmq_socket (context, ZMQ_PUB);
    int rc = zmq_bind (publisher, "tcp://*:5556");          // port num, FIXME
    assert (rc == 0);
    ADASSignal buffer;
//    char buffer [BUFFER_SIZE];

    while(1){
        readData(buffer);
        sendData(publisher, buffer);
    }

    zmq_close (publisher);
    zmq_ctx_destroy (context);
    return 0;
}