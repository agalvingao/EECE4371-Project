/** BeagleBone Blue code **/
#include <fcntl.h>
#include <sys/types>
#include <sys/stats>
#include "zhelpers.h"

#define LINE_LENGTH 34
#define PACKET_SAMPLES 1
#define BUFFER_SIZE (LINE_LENGTH * PACKET_SAMPLES + 1)

int main(void)
{
    int fd;
    char *myfifo = "/tmp/myfifo";
    char buffer[BUFFER_SIZE];
    fd = open(myfifo, O_RDONLY);

    void *context = zmq_ctx_new ();
    void *publisher = zmq_socket (context, ZMQ_PUB);
    int rc = zmq_bind (publisher, "tcp://*:5556");
    assert (rc == 0);

    while (1) {
        read(fd, buffer, LINE_LENGTH);
        s_send (publisher, buffer);
    }

    close(fd);
    zmq_close (publisher);
    zmq_ctx_destroy (context);
    return 0;
}
