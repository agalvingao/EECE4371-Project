#include "zhelpers.h"

#define BUFFER_SIZE 256

void printData(char *buffer){
    // print data in buffer
}

void parseData(char *buffer){

    printData(buffer);
}

int main(int argc, char **argv) {
    //  Socket to talk to clients
    void *context = zmq_ctx_new ();
    void *responder = zmq_socket (context, ZMQ_REP);	/* Create socket */
    int rc = zmq_bind (responder, "tcp://*:5555");		/* FIXME Bind socket on all interfaces to port 5555 */
    assert (rc == 0);

    while (1) {											/* Loop forever */
        char buffer [BUFFER_SIZE];
        zmq_recv (responder, buffer, BUFFER_SIZE, 0);			/* Receive 10 byte message */
        // do something with the data
        parseData(buffer);
        printf ("Received\n");
        sleep (1);          //  Do some 'work'

        // make buffer message
        zmq_send (responder, buffer, BUFFER_SIZE, 0);			/* Send 5 byte response */
    }
    return 0;
}
