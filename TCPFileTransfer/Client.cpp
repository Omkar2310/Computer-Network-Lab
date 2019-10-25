//============================================================================
// Name        : TCPClient.cpp
// Author      : OM
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include<sys/socket.h>
#include<fstream>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>
#define PORT 27100
#define SERVER_ADDRESS "127.0.0.1"
using namespace std;

int main() {
	sockaddr_in servadd,clienadd;
			int sock=socket(AF_INET, SOCK_STREAM, 0);
			if(sock==-1)
			{
				cout<<"Socket error";
			}

			servadd.sin_family=AF_INET;
			servadd.sin_port=htons(PORT);
			servadd.sin_addr.s_addr=inet_addr(SERVER_ADDRESS);
			socklen_t cli=sizeof(servadd);
			int cstat=connect(sock, (struct sockaddr*)&servadd,cli);
			if(cstat==-1){cout<<"Connection failed\n";}
			cout<<"Connected\n";

			int msg_len;
			char buffer[1000];
			bzero((char *)&buffer,sizeof(buffer));
			cout<<"Enter msg to server";
			cin.getline(buffer, 999);

			send(sock, buffer, sizeof(buffer),0);

			bzero((char*)&buffer,sizeof(buffer));
			recv(sock, buffer, 1000, 0);
			cout<<"Msg form Server is : "<<buffer<<endl;

			{
				char filename[100];
				bzero((char*)&filename,sizeof(filename));
				cout<<"ENter filename\n";
				cin.getline(filename, 99);

				fstream fout;
				fout.open(filename, ios::in |ios ::out |ios ::binary);
				fout.seekg(0, ios::end);
				int filesize=fout.tellg();

				char filemsg[80000*9];
				bzero((char*)&filemsg,sizeof(filemsg));
				fout.seekg(0, ios::beg);
				fout.read(filemsg, filesize);

				cout<<filename<<endl;
				cout<<filesize<<endl;
				cout<<filemsg<<endl;
				//send filename
				send(sock, filename, strlen(filename), 0);

				send(sock,(void *)&filesize, sizeof(filesize),0);

				send(sock, filemsg, filesize, 0);




			}


	return 0;
}
