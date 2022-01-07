// // #include "defInclude.h"
// #include<stdio.h>
// #include<stdlib.h>
// #include<string.h>
// #include<sys/socket.h>
// #include<netinet/in.h>
// #include<arpa/inet.h>
// #include<unistd.h>

// #include <netdb.h>
// #include <strings.h>
// #include <errno.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <ctype.h>
// #include <sys/types.h>


// #define MAX_READ 256
// #define MAX_SEND 100
// #define PERIOD '.'
// #define NULL_CHARACTER '\0'
// #define BINARY_IP_SIZE 32
// #define INTRO "cs230 HELLO "
// #define NEWLINE "\\n"
// #define STATUS "STATUS"
// #define MAX_DATA 1024

// typedef struct 
// {
//   int socket;
//   struct sockaddr_in address;
//   char *netID;
//   char *send_buff;
//   char *rec_buff;
// } end_point_connection;




// // // extern int errno;
// // // end_point_connection connection_server;

// // // int create_connection(int server_port,  char IP_address[BINARY_IP_SIZE], end_point_connection *server);
// // // void converse_with_server();
// // // char *buffer_reset(char buffer[]);
// // // void *to_upper(char str[]);
// // // int create_socket(end_point_connection *server);



// // // int main(int argc, char* argv[]) 
// // // {
// // //   int errnum;  //error handler variable for errno
  
// // //   //1. Check cmd line arguments to see if the correct amount of arguments were passed in 
// // //   if(argc != 4)
// // //   {
// // //     errnum = errno;
// // //     fprintf(stderr, "INVALID NUMBER OF ARGUMENTS: %s\n", strerror(errnum));
// // //     exit(EXIT_FAILURE);
// // //   }
  
// // //   //2. Declare variables needed in function
// // //   char *client_ID;            //stores the netID passed in the command line
// // //   unsigned long int server_port_ID;         //will store the port number passed in
// // //   char *server_IP_address;    //will store server domain name **GIVEN IP ADDRESS FOR PROJECT**
  
// // //   //3. Set variables initialized at start of main = to arguments passed in
// // //   strcpy(connection_server.netID, argv[1]);
// // //   server_port_ID = atoi(argv[2]);
// // //   server_IP_address = argv[3];
  
// // //   // to_upper(client_ID);
// // //   // connection_server.netID = client_ID;
  
// // //   // char buff[MAX_LINE];
// // //   // strcpy(buff, INTRO);
// // //   // strcat(buff, connection_server.netID);
// // //   // strcat(buff, "\\n");

// // //   // char *p = "cs230 HELLO dsilveira@umass.edu\\n";
  
// // //   // printf("%lu\n", sizeof(buff));
// // //   // printf("%lu\n", sizeof(p));


// // //   //4. Open socket descriptor and connect client to server
// // //   if(create_connection(server_port_ID, server_IP_address, &connection_server) != 1)
// // //   {
// // //     errnum = errno;
// // //     fprintf(stderr, "ERROR IN OPEN FUNCTION: %s\n", strerror(errnum));
// // //     exit(EXIT_FAILURE);
// // //   }
  
// // //   //5. Send and recieve messages with the server
// // //   converse_with_server(&connection_server);

// // //   //6. Close the socket descriptor 
// // //   if(close(connection_server.socket) != 0)
// // //   {
// // //     errnum = errno; 
// // //     fprintf(stderr, "ERROR IN CLOSE FUNCTION: %s\n", strerror(errnum));
// // //     exit(EXIT_FAILURE);
// // //   }

// // // }

// // // int create_connection(int server_port,  char IP_address[BINARY_IP_SIZE], end_point_connection *server)
// // // {
// // //   int errnum;
// // //   char read_buff[MAX_READ];
// // //   char send_buff[MAX_WRITE];

// // //   struct sockaddr_in server_address;
// // //   struct hostent *server_info_getter;
// // //   struct in_addr ip;
// // //   in_addr_t address;

// // //   //1.Creates the socket
// // //   create_socket(&server);

// // //   inet_aton(IP_address, &ip);
// // //   // fprintf(stdout, "\n\nNET:%s\n", ip);
// // //   fprintf(stdout, "NET:%s\n\n", inet_ntoa(ip));

// // //   //2. retrieve server IP, port, and name information
// // //   server_info_getter = gethostbyaddr((const char *)&ip, sizeof(ip), AF_INET);

// // //   if(server_info_getter == NULL)
// // //   {
// // //     errnum = errno;
// // //     fprintf(stderr, "ERROR GETTING SERVER INFO: %s\n", strerror(errnum));
// // //     return -1; 
// // //   }

// // //   fprintf(stdout, "\nNAME:%s\nAlias:%s\nFAMILY:%i\nLength:%i\nADDRESS:%s\n\n\n", server_info_getter->h_name, server_info_getter->h_aliases[0], 
// // //       server_info_getter->h_addrtype, server_info_getter->h_length, inet_ntoa(ip));

// // //   bzero((char *)&server_address, sizeof(server_address));

// // //   //Assign protocol
// // //   server_address.sin_family = AF_INET;

// // //   //Converts host byte order port number and stores in server_address 
// // //   server_address.sin_port = htons(server_port);

// // //   //Copys the IP address from hostent struct into the server_address structure
// // //   bcopy((char *)&server_info_getter->h_addr_list[0], (char *)&server_address.sin_addr.s_addr, 
// // //       server_info_getter->h_length);

// // //   //3. Sets the server structure equal to its structure within the structure
// // //   server->address = server_address;

// // //   // fprintf(stdout,"Port from parameter: %i", server_port);
// // //   // fprintf(stdout, "\nFAMILY: %i\nServer_address Port: %i\nIP: %s\n\n\n", server_address.sin_family, server_address.sin_port, 
// // //   //       inet_ntoa(server_address.sin_addr));

// // //   //4. Connects the client to the server with the given IP address and port number
// // //   if(connect(server->socket, (struct sockaddr *)&server_address,  sizeof(struct sockaddr)) != 0)
// // //   {
// // //     errnum = errno;
// // //     fprintf(stderr, "ERROR CONNECTING SOCKET: %s\n", strerror(errnum));
// // //     return -1; 
// // //   }
// // //   else
// // //   {
// // //     fprintf(stdout, "CLIENT SUCCESSFULLY CONNECTED TO SERVER\n\n\n");
// // //   }
  
// // //   return 1;
// // // }

// // // void converse_with_server(end_point_connection *server)
// // // {
// // //   int errnum;
// // //   char read_buff[MAX_READ];
// // //   char send_buff[MAX_WRITE];

// // //   int is_flag_captured = 0; 
// // //   int is_intro_over = 0;

// // //   while(1)
// // //   {
// //     // //1.Send server NetID and correctly formatted output
// //     // if(is_intro_over == 0)
// //     // {
// //     //   is_intro_over = 1;
// //     //   sprintf(send_buff, INTRO);
// //     //   strcat(send_buff, server->netID);
// //     //   sprintf(send_buff, NEWLINE);
// //     // }
      
// //     // if((send(server->socket, send_buff, MAX_WRITE, 0)) < 0)
// //     // {
// //     //   errnum = errno;
// //     //   fprintf(stderr, "ERROR SENDING MESSAGE TO SERVER: %s\n", strerror(errnum));
// //     //   exit(EXIT_FAILURE);
// //     // }
// //     // else
// //     // {
// //     //   fprintf(stdout, "%s", send_buff);
// //     //   buffer_reset(send_buff);
// //     //   break;
// //     // }

// // //     if(recv(server->socket, read_buff, sizeof(read_buff), 0) < 0)
// // //     {
// // //       errnum = errno;
// // //       fprintf(stderr, "ERROR SENDING MESSAGE TO SERVER: %s\n", strerror(errnum));
// // //       exit(EXIT_FAILURE);
// // //     }
// // //     else
// // //     {
// // //       fprintf(stdout, "%s", read_buff);
// // //       buffer_reset(read_buff);
// // //     }




// // //     if(is_flag_captured == 1)
// // //     {
// // //       break;
// // //     }
// // //   }  
// // // }

// // // char *buffer_reset(char buffer[])
// // // {
// // //   bzero(buffer, sizeof(&buffer));
  
// // //   return buffer;
// // // } 

// // // void *to_upper(char str[])
// // // {
// // //   const char OFFSET = 'a' - 'A';
// // //   int i = 0;
  
  
// // //   while (*str)
// // //   {
// // //     if(str[i] == '@')
// // //     {
// // //       return str;
// // //     }
// // //     *str = (*str >= 'a' && *str <= 'z') ? *str -= OFFSET : *str;
// // //     str++;
// // //   }
// // //   return str;
// // // }

// // // int create_socket(end_point_connection *server)
// // // {
// // //   server->socket = socket(AF_INET, SOCK_STREAM, 0);
// // //   if(server->socket == -1)
// // //   {
// // //     errnum = errno;
// // //     fprintf(stderr, "ERROR CREATING SOCKET: %s\n", strerror(errnum));
// // //     return -1;
// // //   }
// // //   return 1;
// // // }