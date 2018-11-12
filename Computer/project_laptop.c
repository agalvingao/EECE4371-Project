#include "zhelpers.h"
#include "assert.h"

int main(int argc, char **argv) {
    void *context = zmq_ctx_new ();
    void *receiver = zmq_socket (context, ZMQ_REP);
    int rc = zmq_bind(receiver, "tcp://*:5555");
    assert (rc == 0);

    void *subscriber = zmq_socket (context, ZMQ_SUB);
    zmq_connect (subscriber, "tcp://localhost:5556");   // FIXME

    char *filter = (argc > 1)? argv [1]: "";      // FIXME
    int sb = zmq_setsockopt (subscriber, ZMQ_SUBSCRIBE, filter, strlen (filter));
    assert (sb == 0);

    while (1) {
        char msg [256];

        zmq_pollitem_t items [] = {
            { receiver,   0, ZMQ_POLLIN, 0 },			/* Server (REQ/REP) */
            { subscriber, 0, ZMQ_POLLIN, 0 }			/* Subscriber (PUB/SUB) */
        };
        zmq_poll (items, 2, -1);

        // send data to file
        if (items [0].revents & ZMQ_POLLIN) {
            int size = zmq_recv (receiver, msg, 255, 0);
            if (size != -1) {
            	/** do something, print to file **/
            }
        }

        // recieve BBB data
        if (items [1].revents & ZMQ_POLLIN) {
            int size = zmq_recv (subscriber, msg, 255, 0);
            if (size != -1) {
                char *string = s_recv (subscriber);
                uint64_t time_sec, time_nsec;
                char buffer[256];

                sscanf (string, "%" PRIu64 ":%" PRIu64 "=%s", &time_sec, &time_nsec, &buffer);
                /** FIXME **/
            }
        }
    }

    zmq_close (subscriber);
    zmq_ctx_destroy (context);
    return 0;
}
