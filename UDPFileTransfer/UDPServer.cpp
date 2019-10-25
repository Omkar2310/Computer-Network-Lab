//============================================================================
// Name        : UDPServer.cpp
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
#define PORT 24100
using namespace std;

int main(){

	sockaddr_in servadd,clienadd;

	int sock=socket(AF_INET, SOCK_DGRAM, 0);
	if(sock==-1)
	{
		cout<<"Socket error";
	}

	servadd.sin_family=AF_INET;
	servadd.sin_port=htons(PORT);
	servadd.sin_addr.s_addr=INADDR_ANY;

	int bindstat=bind(sock, (struct sockaddr*)&servadd,sizeof(servadd));
	if(bindstat==-1){cout<<"Error in binding\n";}

	int slen=sizeof(clienadd);
	socklen_t cli=sizeof(clienadd);
	int msg_len;
	char buffer[1000];
	bzero((char*)&buffer,sizeof(buffer));
	msg_len=recvfrom(sock, buffer, 1000, 0, (struct sockaddr*)&clienadd, &cli);

	cout<<"Message from CLient is : "<<buffer<<endl;

	bzero((char*)&buffer,sizeof(buffer));
	cout<<"Reply to client > :";
	cin.getline(buffer, 999);
	msg_len=sendto(sock, buffer, sizeof(buffer),0, (struct sockaddr*)&clienadd, slen);

	if(msg_len==-1){cout<<"error in sending msg\n";}

	{
		char filename[100];
		bzero((char *)&filename,sizeof(filename));
		int filesize;

		msg_len=recvfrom(sock, filename, 99, 0, (struct sockaddr*)&clienadd, &cli);
		if(msg_len==-1){cout<<"Error in receiving filename\n";}
		cout<<filename<<endl;

		msg_len=recvfrom(sock, (void *)&filesize, sizeof(filesize),0, (struct sockaddr*)&clienadd, &cli);
		if(msg_len==-1){cout<<"Error in receiving filesize\n";}
		cout<<filesize<<endl;

		//char *filemsg=new char[9000];
		char filemsg[80000*9];
		bzero((char*)&filemsg,sizeof(filemsg));

		msg_len=recvfrom(sock, filemsg, 80000*9, 0, (struct sockaddr*)&clienadd, &cli);
		if(msg_len==-1){cout<<"Error in receiving filemsg\n";}


		ofstream fout;
		fout.open(filename,ios::out |ios::binary);
		if(!fout)
		{
			cout<<"Error in transfer";
		}
		else
		{
			fout.write(filemsg, filesize);
			cout<<"Successful";
		}
		fout.close();
	}
	return 0;
}
