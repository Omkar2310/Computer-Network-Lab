//============================================================================
// Name        : analysis.cpp
// Author      : OM
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>
#include<pcap.h>
#include <arpa/inet.h>
#include<net/ethernet.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <netinet/ip.h>
using namespace std;
int ethernet=0,udp=0,tcp=0,ip=0;

void packetHandler(u_char* userdata,const struct pcap_pkthdr* pkthdr,const u_char* packet)
{
	const struct ether_header *etherheader;
	const struct ip* ipHeader;

	etherheader=(struct ether_header*)packet;
	ethernet++;

	if(ntohs(etherheader->ether_type)==ETHERTYPE_IP)
	{
		ip++;
		ipHeader=(struct ip*)(packet + sizeof(struct ether_header));

		if(ipHeader->ip_p==IPPROTO_TCP)
		{
			tcp++;
		}

		if(ipHeader->ip_p==IPPROTO_UDP)
				{
					udp++;
				}
	}
}

int main(int argc,char* argv[]) {

	pcap_t *desc;
	char errbuff[PCAP_ERRBUF_SIZE];
	if(argc<2)
	{
		cout<<"Enter filename";
		exit(1);
	}

	desc=pcap_open_offline(argv[1],errbuff);

	if(desc==NULL)
	{
		cout<<"Error in opening file\n";
		cout<<errbuff<<endl;
		exit(1);
	}

	//start loop
	if(pcap_loop()desc,0,packetHandler,NULL)<0)
	{
		cout<<"Loop failed";
		exit(1);
	}

	cout<<"Ethernet "<< ethernet<<endl;
	cout<<"TCP "<< tcp<<endl;
	cout<<"UDP "<< udp<<endl;
	cout<<"IP "<< ip<<endl;


	return 0;
}
