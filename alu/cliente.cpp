#include "header.h"

int main(void)
{
    int socket_fd;
    int len;
    struct sockaddr_in  remote;
    struct hostent *hp;
    struct in_addr addr;
    char buf[MENSAJE_MAXIMO];
    vector<thread> threads;

    if ((socket_fd = socket(PF_INET, SOCK_STREAM, 0)) == -1) {
        perror("creando socket");
        exit(1);
    }

    /* Establecer la dirección a la cual conectarse. */
    remote.sin_family = AF_INET;
    remote.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &(remote.sin_addr));

    /* Conectarse. */
    int s = connect(socket_fd, (struct sockaddr *)&remote, sizeof(remote));
    if ( s == -1) {
        perror("conectandose");
        exit(1);
    }

    threads.push_back(thread(connection_handler, socket_fd));

    for (unsigned int i = 0; i < threads.size(); i++)
	{
		threads[i].join();
	}
    do{
        printf("> ");
        fgets(buf, MENSAJE_MAXIMO, stdin);
        int s = send(socket_fd, buf, strlen(buf), 0);
        if (s == -1) {
            perror("enviando");
            exit(1);
        }

    }while(!feof(stdin));

    /* Cerrar el socket. */
    close(socket_fd);

    return 0;
}