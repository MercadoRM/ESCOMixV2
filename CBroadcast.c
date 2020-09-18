  #include <stdio.h>      /* printf() y fprintf() */
#include <sys/socket.h> /* socket(), connect(), sendto(), y recvfrom() */
#include <arpa/inet.h>  /* sockaddr_in y inet_addr() */
#include <stdlib.h>     /* atoi() y exit() */
#include <string.h>     /* memset() */
#include <unistd.h>     /* close() */

#define MAX_RECV 1024 /* Cadena maxima a recibir */

int
main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr,"Uso: %s <Puerto de escucha>\n", argv[0]);
        exit(1);
    }

    int socket_fd;
    struct sockaddr_in dir_brd; /* Aqui se almacenara la direccio del servidor*/
    unsigned short puerto_brd;     /* Puerto */
    char cad_recv[MAX_RECV+1];
    puerto_brd = atoi(argv[1]);

    /* Creacion datagrama sockets udp */
    if ((socket_fd = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
    {
       perror("Error al crear socket\n");
       return -1;
    }
                                                                                  
    /* Asociar puerto a la direccion */                                         
    memset(&dir_brd, 0, sizeof(dir_brd));   /* Llenar de ceros estructura */    
    dir_brd.sin_family = AF_INET;                                               
    dir_brd.sin_addr.s_addr = htonl(INADDR_ANY);  /* Recibir en cualquier interface */
    dir_brd.sin_port = htons(puerto_brd);      /* Puerto broadcast */                 
                                                                                      
    /* Bind al puerto broadcast */                                                    
    if( bind(socket_fd, (struct sockaddr *) &dir_brd, sizeof(dir_brd)) < 0)           
    {                                                                                 
       perror("Error al hacer bind\n");                                               
       return -1;                                                                     
    }                                                                                 
                                                                                      
    int permiso = 1;                                                                  
    int status = setsockopt(socket_fd, SOL_SOCKET, SO_BROADCAST, (void *)&permiso, sizeof(int));
    if(status  == -1)                                                                           
    {                                                                                           
      perror("Error al establecer permisos \n");                                                
      return -1;                                                                                
    }                                                                                           
                                                                                                
    /* Recibir datagramas del servidor */                                                       
    struct sockaddr_in dir_serv;                                                                
    socklen_t tam_serv = sizeof(dir_serv);                                                      
    int tam_recv = recvfrom(socket_fd, cad_recv, MAX_RECV, 0, (struct sockaddr *)&dir_serv, &tam_serv );
    cad_recv[tam_recv] = '\0';                                                                          
    printf("El servidor envio: %s\n", cad_recv);                                                        
    close(socket_fd);                                                                                   
    return 0;                                                                                           
}          


