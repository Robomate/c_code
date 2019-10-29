/*
 * Descrioption: Simple Win TCP/IP Client
 * Windows: gcc -o test4 test4.c -lws2_32 -lwsock32 -L $MinGW\lib; ./test4
 * Windows: gcc -o sock sock.c -lws2_32; ./sock
 * http://www.c-worker.ch/tuts/wstut_op.php
 */
#include <windows.h>
#include <winsock2.h>
#include <stdio.h>

//Prototypen
int startWinsock(void);

int main()
{
  long rc;
  SOCKET s;
  SOCKADDR_IN addr;
  char buf[256];


  // Winsock starten
  rc=startWinsock();
  if(rc!=0)
  {
    printf("Fehler: startWinsock, fehler code: %d\n",rc);
    return 1;
  }
  else
  {
    printf("Winsock gestartet!\n");
  }

  // Socket erstellen
  s=socket(AF_INET,SOCK_STREAM,0);
  if(s==INVALID_SOCKET)
  {
    printf("Fehler: Der Socket konnte nicht erstellt werden, fehler code: %d\n",WSAGetLastError());
    return 1;
  }
  else
  {
    printf("Socket erstellt!\n");
  }

  // Verbinden
  memset(&addr,0,sizeof(SOCKADDR_IN)); // zuerst alles auf 0 setzten
  addr.sin_family=AF_INET;
  addr.sin_port=htons(12345); // wir verwenden mal port 12345
  addr.sin_addr.s_addr=inet_addr("127.0.0.1"); // zielrechner ist unser eigener

  rc=connect(s,(SOCKADDR*)&addr,sizeof(SOCKADDR));
  if(rc==SOCKET_ERROR)
  {
    printf("Fehler: connect gescheitert, fehler code: %d\n",WSAGetLastError());
    return 1;
  }
  else
  {
    printf("Verbunden mit 127.0.0.1..\n");
  }


  // Daten austauschen
  while(rc!=SOCKET_ERROR)
  {
    printf("\nZeichenfolge eingeben [max 256]: ");
    gets(buf);
    send(s,buf,strlen(buf),0);
    rc=recv(s,buf,256,0);
    if(rc==0)
    {
      printf("Server hat die Verbindung getrennt..\n");
      break;
    }
    if(rc==SOCKET_ERROR)
    {
      printf("Fehler: recv, fehler code: %d\n",WSAGetLastError());
      break;
    }
    buf[rc]='\0';
    printf("\nServer antwortet: %s\n",buf);
  }
  closesocket(s);
  WSACleanup();
  return 0;
}

int startWinsock(void)
{
  WSADATA wsa;
  return WSAStartup(MAKEWORD(2,0),&wsa);
}