#include "zhelpers.h"

#define BUFFER_SIZE 256

void printData(char *buffer){
    // print data in buffer
}

void parseData(char *buffer){
    // parse the string

    printData(buffer);
}

int main(int argc, char **argv) {
    //  Socket to talk to clients
    void *context = zmq_ctx_new ();
    void *requester = zmq_socket (context, ZMQ_REQ);	/* Create socket */
    int rc = zmq_connect (requester, "tcp://localhost:5555");		/* FIXME Bind socket on all interfaces to port 5555 */
    assert (rc == 0);

    while (1) {											/* Loop forever */
        char buffer [BUFFER_SIZE];
        // make buffer message
        zmq_send (requester, buffer, BUFFER_SIZE, 0);			/* Send 5 byte response */

        zmq_recv (requester, buffer, BUFFER_SIZE, 0);			/* Receive 10 byte message */
        // do something with the data
        parseData(buffer);
        sleep (1);          //  Do some 'work'

    }
    return 0;
}
