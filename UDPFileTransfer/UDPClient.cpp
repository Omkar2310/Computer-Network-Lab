//============================================================================
// Name        : UDPClient.cpp
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
#define SERVER_ADDRESS "127.0.0.1"
#define PORT 24100
using namespace std;

int main() {

	sockaddr_in servadd;

	int sock=socket(AF_INET, SOCK_DGRAM, 0);
	if(sock==-1)
	{
		cout<<"Socket error";
	}

	servadd.sin_family=AF_INET;
	servadd.sin_port=htons(PORT);
	servadd.sin_addr.s_addr=inet_addr(SERVER_ADDRESS);

	int msg_len;
	char buffer[1000];
	bzero((char*)&buffer,sizeof(buffer));
	cout<<"ENter msg for server\n";
	cin.getline(buffer, 999);
	socklen_t cli=sizeof(servadd);
	msg_len=sendto(sock, buffer, sizeof(buffer),0, (struct sockaddr*)&servadd,cli);

	if(msg_len==-1){cout<<"Error in sending msg";}

	bzero((char*)&buffer,sizeof(buffer));
	msg_len=recvfrom(sock, buffer, 1000, 0, (struct sockaddr*)&servadd,&cli);

	cout<<"Msg from Server : " <<buffer<<endl;

	{
		cout<<"Enter filename\n";
		char filename[100];
		cin>>filename;
		//send fname
				msg_len=sendto(sock, filename, strlen(filename), 0, (struct sockaddr*)&servadd, cli);
				if(msg_len==-1){"error in sending filename";}
				cout<<filename<<endl;
		fstream fout;
		fout.open(filename, ios::in |ios::out |ios::binary);
		fout.seekg(0,ios::end);
		int filesize=fout.tellg();
		msg_len=sendto(sock, (void *)&filesize, sizeof(filesize), 0, (struct sockaddr*)&servadd, cli);
				if(msg_len==-1){"error in sending filesize";}
				cout<<filesize<<endl;

		char *filemsg=new char[filesize];

		fout.seekg(0, ios::beg);
		fout.read(filemsg, filesize);





		msg_len=sendto(sock, filemsg, filesize, 0, (struct sockaddr*)&servadd, cli);
		if(msg_len==-1){"error in sending filemsg";}
		cout<<filemsg<<endl;
	}


	return 0;
}
