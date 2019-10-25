/*
Write a program  in Java/Python to demonstrate sub netting  
for a network 192.168.4.10 / 26 (form 4 subnets) and find the sub net masks.
*/
import java.util.Scanner;
import java.net.InetAddress;

import java.util.*;
import java.io.*;
public class SUB {

	public static void main(String[] args) {
	Scanner s1=new Scanner(System.in);
		String ipadd="";
		System.out.println("ENter IP Address");
		
		ipadd=s1.nextLine();
		
		String splitip[]=ipadd.split("\\.");
		
		//convert binary
		String binip="";
		for(int i=0;i<4;i++)
		{
			splitip[i]=appendZeros(Integer.toBinaryString(Integer.parseInt(splitip[i])));
			binip+=splitip[i];
		}
		
		System.out.println("Binary is : " + binip);
		
		System.out.println("ENter CIDR bits");
		int cidr=s1.nextInt();
		int bits=8-(cidr%8);
		int total_address=(int)Math.pow(2,bits);
		getsubnet(cidr);
		
		//convert binary
		int firstaddbint[]=new int[32];
		int lastaddbint[]=new int[32];
		
		for(int i=0;i<32;i++)
		{
			firstaddbint[i]=binip.charAt(i) - 48;
			lastaddbint[i]=binip.charAt(i) - 48;
		}
		
		//anding


		
		for(int i=31;i>31-bits;i--)
		{
			firstaddbint[i]=firstaddbint[i] & 0;
		}
		

		
		//move this to a string array
		String ipinBin[]= {"","","",""};
		for(int i=0;i<32;i++)
		{
			ipinBin[i/8]=new String(ipinBin[i/8]+firstaddbint[i]);
		}
		
		//convert to a decimal value
		int FirstAddGrp[]=new int[4];
		for(int i=0;i<4;i++)
		{
			FirstAddGrp[i]=Integer.parseInt(ipinBin[i],2);
			System.out.print(FirstAddGrp[i]);
			if(i!=3)
			{
				System.out.print(".");
			}
		}
		
		
		//get last
		
		for(int i=31;i>31-bits;i--)
		{
			lastaddbint[i]=lastaddbint[i] | 1;
		}
		
		//move this to a string
		
		String LastipGrp[]= {"","","",""};
		for(int i=0;i<32;i++)
		{
			LastipGrp[i/8]=new String (LastipGrp[i/8]+lastaddbint[i]);
		}
		
		//cnvrt in decimal
		int LastipGrpinDec[]=new int[4];
		for(int i=0;i<4;i++)
		{
			LastipGrpinDec[i]=Integer.parseInt(LastipGrp[i],2);
			System.out.print(LastipGrpinDec[i]);
			if(i!=3)
			{
				System.out.print(".");
			}
		}
		
		System.out.println("How many subnets you want to form");
		int scont=s1.nextInt();
		for(int j=1;j<scont;j++)
		{
			System.out.println("Group " + (j+1)+ "First Address : ");
			
			for(int i=0;i<4;i++)
			{
				if(i<3)
				{
				System.out.print(FirstAddGrp[i] + " .");
				}
				else
				{
					System.out.print(FirstAddGrp[i]=FirstAddGrp[i]+total_address);
				}
			}
			System.out.println("Group " + (j+1)+ "Last Address : ");
			
			for(int i=0;i<4;i++)
			{
				if(i<3)
				{
				System.out.print(LastipGrpinDec[i] + " .");
				}
				else
				{
					System.out.print(LastipGrpinDec[i]=LastipGrpinDec[i]+total_address);
				}
			}
		}
		
		
	}

	private static void getsubnet(int cidr) {
		// TODO Auto-generated method stub
		
		int x=cidr%8;
		int t=8-x;
		int a=1;
		int lastbit=0;
		while(a<=x)
		{
			lastbit+=Math.pow(2,t);
			t++;
			a++;
		}
		String subnemask="255.255.255.";
		
		subnemask+=String.valueOf(lastbit);
		
		System.out.println("SUbnet is : " + subnemask);
	}

	private static String appendZeros(String binaryString) {
		// TODO Auto-generated method stub
		String temp="00000000";
		return temp.substring(binaryString.length()) + binaryString;
	}	
	
}

