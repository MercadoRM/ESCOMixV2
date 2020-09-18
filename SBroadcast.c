 #include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
/* #include <netinet/in.h> */
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#define MAX_BUF 1024

int
main(int argc, char * argv[])
{
  if(argc != 3 )
  {
    fprintf(stderr,"Uso: %s <Direccion receptora> <Puerto comunicacion>\n", argv[0]);
    return -1;
  }

  int sockfd, status, buflen, sinlen, permiso;
  char buffer[MAX_BUF];
  struct sockaddr_in addr_broadcast;
  sinlen = sizeof(struct sockaddr_in);
  memset(&addr_broadcast, 0, sinlen);

  /* Crear socket para enviar o recibir datagramas */
  sockfd = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if(sockfd == -1)
  {
    perror("Error al crear el socket");
    return -1;
  }

  /* Construccion de la estructura de direccion local */
                                                                                     
  addr_broadcast.sin_family = PF_INET; /* Berkley socket */                          
  addr_broadcast.sin_port = htons(atoi(argv[2])); /* Puerto */                       
  addr_broadcast.sin_addr.s_addr = inet_addr(argv[1]); /* Direccion de clase broadcast*/
                                                                                        
  /*                                                                                    
  status = bind(sockfd, (struct sockaddr *)&addr_broadcast, sinlen);                    
  if(status == -1)                                                                      
  {                                                                                     
    perror("Error al hacer bind \n");                                                   
    return -1;                                                                          
  }                                                                                     
  */                                                                                    
                                                                                        
  /* Establecer socket para permitir broadcast */                                       
  permiso = 1;                                                                          
  status = setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, (void *)&permiso, sizeof(int) );
  if(status  == -1)                                                                     
  {                                                                                     
    perror("Error al establecer el socket \n");                                         
    return -1;                                                                          
  }                                                                                     
                                                                                        
  printf("Introduce la cadena a enviar:");                                              
  fgets(buffer,MAX_BUF,stdin);                                                          
  buflen = strlen(buffer);  /* Tamanio de la cadena a enviar */                         
  status = sendto(sockfd, buffer, buflen, 0, (struct sockaddr *) &addr_broadcast, sizeof(addr_broadcast));
  if(buflen != status)                                                                                    
  {                                                                                                       
     perror("Hubo un error al enviar los datos...\n");                                                    
     return -1;                                                                                           
  }                                                                                                       
  close(sockfd);                                                                                          
  return 0;                                                                                               
}                     


