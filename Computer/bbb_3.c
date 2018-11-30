#include "zhelpers.h"

static FILE *f;

int main(int argc, char **argv)
{
    if (argc != 2) {
        fputs("USAGE: bbb_2 tcp://ipv4:port\n", stderr);
        return 1;
    }

    char *ip_spec = argv[1];

    void *context = zmq_ctx_new ();
    void *subscriber = zmq_socket (context, ZMQ_SUB);
    int rc = zmq_connect (subscriber, ip_spec);
    assert (rc == 0);

    char *filter = (argc > 1)? argv [1]: "";
    rc = zmq_setsockopt (subscriber, ZMQ_SUBSCRIBE, filter, strlen (filter));
    assert (rc == 0);

    f = fopen("data_final", "w");
    printf("Start receiving");

    while (1) {
        char *string = s_recv (subscriber);
        printf("%s",string);
        fprintf(f, "%s", string);
        free (string);
    }

    zmq_close (subscriber);
    zmq_ctx_destroy (context);
    return 0;
}
