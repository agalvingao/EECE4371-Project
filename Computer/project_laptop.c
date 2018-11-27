#include "zhelpers.h"

#define BUFFER_SIZE 256

/*
 * message format:
 *      [type][sampling_number]:[voltA],[voltB],[voltC]\n
 * example:
 *      @200:080.5561,070.3122,090.1031\n
 */

void printData(uint_32t sampling_number, float volt_a, float volt_b, float volt_c){
    // print data in buffer
}

void parseData(char *buffer){
    char* message_type;
    uint_32t sampling_number;
    float volt_a, volt_b, volt_c;
    sscanf(string, "%s%s:%08.4f,%08.4f,%08.4f\n", &message_type, &sampling_number, &volt_a, &volt_b, &volt_c);
    if(message_type == "@"){
        printData(sampling_number, volt_a, volt_b, volt_c);
    }
}

int main(int argc, char **argv) {
    //  Socket to talk to server
    void *context = zmq_ctx_new ();
    void *subscriber = zmq_socket (context, ZMQ_SUB);
    int rc = zmq_connect (subscriber, "tcp://localhost:5556");
    assert (rc == 0);

    //  Subscribe to zipcode, default is NYC, 10001
    char *filter = (argc > 1)? argv [1]: "";
    rc = zmq_setsockopt (subscriber, ZMQ_SUBSCRIBE, filter, strlen (filter));
    assert (rc == 0);

    //  Process 10 updates
    while (1) {
        char *string = s_recv (subscriber);
        printf ("Message recieved");
        parseData(string);
        free (string);
    }

    zmq_close (subscriber);
    zmq_ctx_destroy (context);
    return 0;
}
