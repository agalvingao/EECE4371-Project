#include "zhelpers.h"

#define LINE_LENGTH 33
#define PACKET_SAMPLES 400
#define BUFFER_SIZE (LINE_LENGTH * PACKET_SAMPLES + 1)

/*
 * message format:
 *      [type][time_stamp]:[voltA],[voltB],[voltC]\n
 * example:
 *      @200:80.5561,70.3122,90.1031\n
 */

void printData(uint_32t time_stamp, float volt_a, float volt_b, float volt_c){
    // print data in buffer
}

void parseData(char *string){
    double time_stamp;
    double volt_a, volt_b, volt_c;
    sscanf(string, "%011.4f %+05.3f %+05.3f %+05.3f\n", &time_stamp, &volt_a, &volt_b, &volt_c);
    printData(time_stamp, volt_a, volt_b, volt_c);
}

int main(int argc, char **argv) {
    //  Socket to talk to server
    void *context = zmq_ctx_new ();
    void *subscriber = zmq_socket (context, ZMQ_SUB);
    int rc = zmq_connect (subscriber, "tcp://localhost:5556");
    assert (rc == 0);

    char *filter = (argc > 1)? argv [1]: "";
    rc = zmq_setsockopt (subscriber, ZMQ_SUBSCRIBE, filter, strlen (filter));
    assert (rc == 0);

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
