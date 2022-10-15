#include "header.h"
#include <thread>
using namespace std;





bool revisarCantidadJugadores(vector<vector<int>> &matrix, vector<int> &socketsListos, int socketNuevo){
    socketsListos.push_back(socketNuevo);
    cout << socketNuevo << endl;
    if(socketsListos.size() == 9){
        int numero = 0;
        for (size_t i = 0; i < 3 ; i++)
        {
            for (size_t j = 0; j < 3; j++)
            {
                matrix[i].push_back(socketsListos[numero]);
                numero++;
            }
        }
        for (size_t i = 0; i < 3 ; i++)
        {
            for (size_t j = 0; j < 3; j++)
            {
                matrix[i][j];
            }
        }
        return true;
    }
    
    return false;
}


int main(void)
{
    int s, s1, s2, len;
    struct sockaddr_in local;
    struct sockaddr_in remote;
    vector <thread> threads;
    vector <int> sockets;
    vector<vector<int>> matrix(3, vector<int>(3));
    

    /* crea socket */
    if ((s = socket(PF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    /* configura dirección */
    local.sin_family = AF_INET;
    local.sin_port = htons(PORT);
    local.sin_addr.s_addr = INADDR_ANY;


    /* linkea socket con dirección */
    if (bind(s, (struct sockaddr *)&local, sizeof(local)) < 0) {
        perror("bind");
        exit(1);
    }

    /* setea socket a modo "listen"*/
    if (listen(s, 10) == -1) {
        perror("listen");
        exit(1);
    }

    int t = sizeof(remote);
    int socket;
    for(;;){
        if((socket = accept(s, (struct sockaddr*) &remote, (socklen_t*) &t)) == -1) {
            perror("aceptando la conexión entrante");
            exit(1);
        }
        threads.push_back(thread(connection_handler, socket));
        if (revisarCantidadJugadores(matrix,sockets,socket))
        {
            request req;
            strcpy(req.msg, "Bienvenidos al juego de tu vida");
            strcpy(req.type, "SALUDO");
            cout << "nashe"<< endl;
            broadcast(matrix,&req);
        }
    }

    for (unsigned int i = 0; i < threads.size(); i++)
	{
		threads[i].join();
	}
    

    close(s1);
    close(s2);
    /* Cerrar la conexión que escucha. */
    close(s);

    return 0;
}
