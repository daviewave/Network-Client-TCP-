// #include "defInclude.h"
// #include "defInclude.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>

#include <netdb.h>
#include <strings.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>


#define PERIOD '.'
#define NULL_CHARACTER '\0'
#define BINARY_IP_SIZE 32
#define INTRO "cs230 HELLO "
#define NEWLINE '\n'
#define STATUS "STATUS"
#define MAX_DATA 256


typedef struct 
{
  char message[MAX_DATA];
} message;

typedef struct 
{
  int socket;
  struct sockaddr_in address;

  message send_buff;
  ssize_t send_byte;

  message rec_buff;
  ssize_t rec_byte;

}end_point_connection;



extern int errno;
end_point_connection client;

int create_socket(end_point_connection *server, int port, char *ip);


int read_message(end_point_connection *server);   //recieve message
int send_message(end_point_connection *server);   //send message




int get_clientID(int argc, char *argv[], char *name);
int set_server(end_point_connection *server);
int message_prep(char *msg_content, end_point_connection *server);
int close_connection(end_point_connection *server);
//int modify_stdin(end_point_connection *server, char *client);
//int translate_message(char* buff, size_t max_bytes);



int main(int argc, char* argv[]) 
{
  int errnum;  //error handler variable for errno
  //1. Check cmd line arguments to see if the correct amount of arguments were passed in 
  if(argc != 4)
  {
    errnum = errno;
    fprintf(stderr, "INVALID NUMBER OF ARGUMENTS: %s\n", strerror(errnum));
    exit(EXIT_FAILURE);
  }

  //2. Set variables initialized at start of main = to arguments passed in
  char client_ID[MAX_DATA];
  int server_port_ID;
  char *server_IP_address;
  
  get_clientID(argc, argv, client_ID);
  set_server(&client);
  server_port_ID = atoi(argv[2]);
  server_IP_address = argv[3];
  
  // fprintf(stdout ,"1: %s\n2: %i\n3: %s\n", server.netID, server_port_ID, server_IP_address);


  //3.creates socket for client/server with the cmd line argurments 
  int status = create_socket(&client, server_port_ID, server_IP_address);
  if(status == -1)
  {
    errnum = errno;
    fprintf(stderr, "ERROR CREATING SOCKET: %s\n", strerror(errnum));
    exit(EXIT_FAILURE);
  }

  char send_buffer[MAX_DATA];
  char rec_buffer[MAX_DATA];
  int is_intro = 0;
  int is_flag_captured = 0;

  while(1)
  {
    if(is_intro == 0)
    {
      message_prep(INTRO, &client);
      message_prep(client_ID, &client);
      message_prep("\\n", &client);
      sprintf(client.send_buff.message, "%c", '\0');
            
      printf("REAL AMT: %s\n", client.send_buff.message);
      
      send_message(&client);
      read_message(&client);
      
      is_intro = 1;
    }

    break;
    // do
    // {
    //   // read_message(&client);

    // }while(is_flag_captured == 0);


  }
  
  
  
  //starts the conversation with the client
  // converse_with_client(&client);
  

  //4. Send and recieve messages with the client
  // converse_with_client(&client, argv[1]);

  //5. Close the socket descriptor 
  // close_socket(&client);

  return 0;
}



int read_message(end_point_connection *server)
{
  int errnum;
  
  ssize_t msg_length, recv_status, recv_counter = 0;
  do
  {
    msg_length = sizeof(server->rec_buff) - server->rec_byte;
    if(msg_length > MAX_DATA)
    {
      msg_length = MAX_DATA; 
    }

    recv_status = recv(server->socket, (char *)&server->rec_buff + server->rec_byte, msg_length, 0);
    if(recv_status < 0)
    {
      errnum = errno;
      fprintf(stderr, "ERROR WITH RECV: %s\n", strerror(errnum));
      return -1;
    }
    else if(recv_status == 0)
    {
      errnum = errno;
      fprintf(stderr, "FINISHED RECIEVING DATA: %s\n", strerror(errnum));
    }
    else
    {
      server->rec_byte += recv_status;
      recv_counter += recv_status;
    }
  }while(recv_status > 0);
  return 1;
}

int send_message(end_point_connection *server)
{
  int errnum;
  
  size_t msg_length, send_counter = 0;
  ssize_t send_status; 

  do
  {
    // msg_length = (strlen(server->send_buff.message) - server->send_byte);
    if(server->send_byte > MAX_DATA)
    {
      server->send_byte = MAX_DATA; 
    }

    send_status = send(server->socket, (char*)&server->send_buff + server->send_byte, server->send_byte, 0);
    if(send_status < 0)
    {
      errnum = errno;
      fprintf(stderr, "ERROR SENDING TO SERVER: %s\n", strerror(errnum));
      return -1;
    }
    else if(send_status == 0)
    {
      errnum = errno;
      fprintf(stderr, "FINISHED SENDING DATA: %s\n", strerror(errnum));
      break;
    }
    else
    {
      server->send_byte -= send_status;
      send_counter -= send_status;
    }
  }while(send_status > 0);

  return 0;
}













int create_socket(end_point_connection *server, int port, char ip[])
{
  int errnum;

  //socket_creation
  server->socket = socket(AF_INET, SOCK_STREAM, 0);
  if(server->socket == -1)
  {
    errnum = errno;
    fprintf(stderr, "ERROR CREATING SOCKET: %s\n", strerror(errnum));
    return -1;
  }

  //address setup
  struct sockaddr_in server_address;  
  memset(&server_address, 0, sizeof(server_address));  
  server_address.sin_family = AF_INET;          //Assign protocol 
  server_address.sin_port = htons(port);        //Converts host byte order port number and stores in server_address
  server_address.sin_addr.s_addr = inet_addr(ip);

  server->address = server_address;

  //4. Connects the client to the server with the given IP address and port number
  if(connect(server->socket, (struct sockaddr *)&server_address,  sizeof(struct sockaddr)) == -1)
  {
    errnum = errno;
    fprintf(stderr, "ERROR CONNECTING SOCKET: %s\n", strerror(errnum));
    return -1; 
  }
  else
  {
    fprintf(stdout, "\nClient is connected to the server address %s:%i\n", ip, port);
  }
  
  return 0;
}

int get_clientID(int argc, char *argv[], char *name)
{
  strcpy(name, argv[1]);
  return 1;
}

int set_server(end_point_connection *server)
{
  server->send_byte = 0;
  server->rec_byte = 0;

  return 1;
}

int message_prep(char *msg_content, end_point_connection *server)
{
  server->send_byte = server->send_byte + strlen(msg_content);
  printf("\n\nBYTES IN CLIENT BUFFER: %lu\n\n", client.send_byte);//sizeof(&client.send_buff.message));

  if(msg_content[0] == '\0')
  {
    sprintf(server->send_buff.message, "%s", msg_content);
  }
  else
  {
    strcat(server->send_buff.message, msg_content);
  }

  
  
  // printf("MSG ADDED: %s\n", server->send_buff.message);
  
  return 1;
}



int close_connection(end_point_connection *server)
{
  close(server->socket);
  return 1;
}













// int translate_message(char* buff, size_t max_bytes)
// {
//   int errnum;
//   bzero(buff, max_bytes);

//   ssize_t msg_status, counter, msg_size; 
//   do
//   {
//     msg_status = read(STDIN_FILENO, buff, max_bytes) - client.send_byte;
//     if(msg_status > MAX_DATA)
//     {
//       msg_status = MAX_DATA; 
//     }

//     if(msg_status < 0)
//     {
//       errnum = errno;
//       fprintf(stderr, "ERROR TRANSLATING MESSAGE: %s\n", strerror(errnum));
//       return -1;
//     }
//     else if(msg_status > 0)
//     {
//       counter += msg_status;
//     }

//   }while(msg_status > 0);

//   msg_size = strlen(buff);
//   if(buff[msg_size - 1] == NEWLINE && msg_size > 0)
//   {
//     buff[msg_size - 1] = NULL_CHARACTER;
//   }
  
//   return 1;
// }

// int modify_stdin(end_point_connection *server, char *client)
// {
//   char rbuff[MAX_DATA];
//   if(translate_message(rbuff, MAX_DATA) != 1)
//   {
//     return -1;
//   }

//   message new_message;
//   message_prep(rbuff, &new_message);

//   //send
//   return 0;
// }
