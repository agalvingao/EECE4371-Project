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

static char buffer [BUFFER_SIZE];
static pthread_mutex_t mutex1;

/** read in analog data into data struct **/
static void *readData(void *arg){
    while(1){
        int lock1 = pthread_mutex_lock(&mutex1);
        /** FIXME read in ADAS**/

        int unlock1 = pthread_mutex_unlock(&mutex1);
    }
}

static void *writeData(void *arg){
    void *context = zmq_ctx_new ();
    void *requester = zmq_socket (context, ZMQ_REQ);	/* Create socket */
    zmq_connect (requester, "tcp://localhost:5555");	/* FIXME change IP Address */

    while (1) {
        int lock1 = pthread_mutex_lock(&mutex1);
        char recvMessage [BUFFER_SIZE];
        printf ("Sending %d…\n");
        // FIXME write to buffer

        zmq_send (requester, buffer, BUFFER_SIZE, 0);			/* Send message of 5 bytes */
        int unlock1 = pthread_mutex_unlock(&mutex1);

        zmq_recv (requester, recvMessage, BUFFER_SIZE, 0);			/* Receive message of 10 bytes */
        // check response
        printf ("Received %d\n");
    }

    zmq_close (requester);								/* Close socket */
    zmq_ctx_destroy (context);
    return 0;
}

int main(int argc, char *argv[])
{
    pthread_mutexattr_t mymutexattr;
    pthread_mutexattr_init(&mymutexattr);
    pthread_mutex_init(&mutex1, &mymutexattr); // create mutex1
    pthread_mutexattr_destroy(&mymutexattr);

    pthread_attr_t myattr;
    int err1, err2;
    struct sched_param param;

    main_id = pthread_self();

    pthread_attr_init(&myattr);
    pthread_attr_getschedparam(&myattr, &param);
    pthread_attr_setinheritsched(&myattr, PTHREAD_EXPLICIT_SCHED);
    pthread_attr_setschedpolicy(&myattr, SCHED_RR);

    // set own priority first
    pthread_attr_setschedparam(&myattr, &param);
    param.sched_priority = 99;
    pthread_t tid = pthread_self();
    pthread_setschedparam(tid, SCHED_RR, &param);

    // set priority of read data
    param.sched_priority = 10;
    pthread_attr_setschedparam(&myattr, &param);
    err2 = pthread_create(&body2_id, &myattr, readData, (void *)parameter2);

    // set priority of write data
    param.sched_priority = 10;
    pthread_attr_setschedparam(&myattr, &param);
    err3 = pthread_create(&body3_id, &myattr, writeData, (void *)parameter3);
    pthread_attr_destroy(&myattr);

    pthread_join(body1_id, NULL);
    pthread_join(body2_id, NULL);

    return 0;
}
