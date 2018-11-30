#include <fcntl.h>
#include <sys/types>
#include <sys/stats>
#include <unistd.h>
#include <stdio.h>

#define LINE_LENGTH 34
#define PACKET_SAMPLES 1
#define BUFFER_SIZE (LINE_LENGTH * PACKET_SAMPLES + 1)

int main(void){
    system("rm-f /tmp/myfifo");
    FILE *f = fopen("data_final.txt", "r");

    int fd;
    char* myfifo = "/tmp/myfifo";
    mkfifo("data_final.txt", 0666);
    system("./bbb_2 &");
    fd = open(myfifo, O_WRONLY);

    while(1){
        char next_line[LINE_LENTH];

        rdline:
        fgets(next_line, LINE_LENGTH, f);
        if(feof(f)){
            rewind(f);
            goto rdline;
        }
        write(fd, next_line, sizeof(next_line));
    }

    close(fd);
    fclose(f);
    return 0;
}
