//============================================================================
// Name        : TCPServer.cpp
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
		servadd.sin_addr.s_addr=INADDR_ANY;
		socklen_t cli=sizeof(clienadd);
		int bindstat=bind(sock, (sockaddr*)&servadd,sizeof(servadd));
		if(bindstat==-1){cout<<"Error in binding\n";}

		cout<<"Waiting for client...";

		listen(sock, 7);
		int aacep=accept(sock, (sockaddr*)&clienadd, &cli);

		int msg_len;
		char buffer[1000];
		bzero((char*)&buffer,sizeof(buffer));
		recv(aacep, buffer, 1000, 0);
		cout<<"msg from client : "<<buffer<<endl;

		bzero((char*)&buffer,sizeof(buffer));
		cout<<"Msg for client : >";
		cin.getline(buffer, 999);

		send(aacep, buffer, sizeof(buffer),0);

		{
			char filename[100];
			bzero((char*)&filename,sizeof(filename));

			recv(aacep, filename, 100,0);
			cout<<filename<<endl;

			int filesize;
			recv(aacep,(void *)&filesize,sizeof(filesize) ,0);
			cout<<filesize<<endl;

			char filemsg[80000*8];
			bzero((char*)&filemsg,sizeof(filemsg));

			recv(aacep, filemsg, filesize, 0);
			cout<<filemsg<<endl;
			ofstream fout;
			fout.open(filename, ios::out |ios::binary);
			if(!fout)
			{
				cout<<"Error in transfer\n";
			}
			else
			{
				fout.write(filemsg, filesize);
				cout<<"Successful\n";
			}
			fout.close();

		}

		return 0;
}
