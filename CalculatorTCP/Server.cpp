//============================================================================
// Name        : SCalcualtor.cpp
// Author      : OM
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include<sys/socket.h>
#include<string.h>
#include<arpa/inet.h>
#include<stdlib.h>
#define PORT 21124
using namespace std;

int main() {
	sockaddr_in servadd,clientadd;

	int sock=socket(AF_INET, SOCK_STREAM, 0);
	if(sock==-1){cout<<"Socket error";exit(1);}

	servadd.sin_family=AF_INET;
	servadd.sin_port=htons(PORT);
	servadd.sin_addr.s_addr=INADDR_ANY;

	socklen_t cli=sizeof(clientadd);
	int bindstat=bind(sock, (sockaddr*)&servadd, sizeof(servadd));
	cout<<"Waiting for client..\n";
	listen(sock, 4);
	int aaccept=accept(sock, (struct sockaddr*)&clientadd, &cli);
	cout<<"Connected\n";

	char op[2];
	char num1[20];
	char num2[20];
	float a,b,res;

	while(1)
	{
		int n;
		bzero((char *)&num1,sizeof(num1));
		n=recv(aaccept, num1, 20, 0);
		a=atof(num1);
		int n1;
		bzero((char *)&num2,sizeof(num2));
		n1=recv(aaccept, num2, 20, 0);
		b=atof(num2);
		cout<<"First number : "<< num1 <<endl;
		cout<<"Second Number : "<<num2<<endl;

		int pp;
		bzero((char *)&op,sizeof(op));
		pp=recv(aaccept, op, 2, 0);
		cout<<"Operator : "<<op<<endl;

		switch(op[0])
		{
		case '+':
			char ans[20];
			res=a+b;
			bzero((char *)&ans,sizeof(ans));
			sprintf(ans,"%f",res);
			cout<<res<<endl;
			send(aaccept, ans, strlen(ans), 0);

			break;

		case '-':
					char ans1[20];
					res=a-b;
					bzero((char *)&ans1,sizeof(ans1));
					sprintf(ans1,"%f",res);
					cout<<res<<endl;
					send(aaccept, ans1, strlen(ans), 0);

					break;
		case '*':
							char ans2[20];
							res=a*b;
							bzero((char *)&ans2,sizeof(ans2));
							sprintf(ans2,"%f",res);
							cout<<res<<endl;
							send(aaccept, ans2, strlen(ans), 0);

							break;
		case '/':
							char ans3[20];
							res=a/b;
							bzero((char *)&ans3,sizeof(ans3));
							sprintf(ans3,"%f",res);
							cout<<res<<endl;
							send(aaccept, ans3, strlen(ans), 0);

							break;
		case '%':
							char ans4[20];
							int x,y;
							x=(int)a;
							y=(int)b;
							res=x%y;
							bzero((char *)&ans4,sizeof(ans4));
							sprintf(ans4,"%f",res);
							cout<<res<<endl;
							send(aaccept, ans4, strlen(ans), 0);

							break;
		}
	}

	return 0;
}
