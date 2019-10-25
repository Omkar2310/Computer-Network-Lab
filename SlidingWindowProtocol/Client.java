import java.net.*;
import java.io.*;
import java.util.*;
public class Client {
	Socket s=null;
	DataInputStream din=null;
	DataOutputStream dout=null;
	
	public Client() {
		// TODO Auto-generated constructor stub
		try
		{
			s=new Socket("localhost",22100);
			
			din=new DataInputStream(s.getInputStream());
			dout=new DataOutputStream(s.getOutputStream());
			System.out.println("Connected to server\n");
		}catch(Exception e)
		{
			e.printStackTrace();
		}
	}
	
	void GBN()
	{
		int frames;
		Scanner s1=new Scanner(System.in);
		
		System.out.println("No. of frames :");
		frames=s1.nextInt();
		
		try {
			dout.writeInt(frames);
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		System.out.println("ENter window size");
		int ws=s1.nextInt();
		int i=0;
		try
		{
		while(i<frames)
		{
			int temp=0;
			
			for(int j=0;j<ws && i+j<frames;j++)
			{
				System.out.println("Sending Packet " + (i+j));
				System.out.println("ENter 1 for error else 0");
				temp=s1.nextInt();
				
				if(temp!=1)
				{
					dout.writeInt((i+j));
				}
			}
			//receive
			int cnt=0;
			for(int j=0;j<ws && i+j<frames;j++)
			{
				s.setSoTimeout(2000);
				try {
				int t=din.readInt();
				if(t==(i+j))
				{
					System.out.println("Ack received " + t);
					cnt++;
				}
				else
				{
					Thread.sleep(500);
				}
				}catch (Exception e) {
					// TODO: handle exception
					
					if(i+cnt<frames)
					{
						System.out.println("ACK not received" + cnt);
					}
					j=ws;
				}
			}
			i+=cnt;
			
		}
		}catch (Exception e) {
			// TODO: handle exception
			e.printStackTrace();
		}
	}
	
	void srep()
	{
		int frames;
		System.out.println("ENter no. of frames");
		Scanner s1=new Scanner(System.in);
		frames=s1.nextInt();
		
		System.out.println("ENter ws ");
		int ws=s1.nextInt();
		
		int i=0;
		boolean f[]=new boolean[frames];
		while(i<frames)
		{
			f[i]=false;
			i++;
		}
		i=0;
		try
		{
			dout.writeInt(frames);
			boolean inc=true;
			while(i<frames)
			{
				for(int j=0;j<ws && i+j<frames;j++)
				{
					int temp=0;
					if(!f[i+j])
					{
						System.out.println("Sending Packet" + (i+j));
						System.out.println("Press 1 if error\n");
						temp=s1.nextInt();
						if(temp!=1)
						{
							dout.writeInt((i+j));
						}
					}				
				}
				
				//recv
				for(int j=0;j<ws && i+j<frames;j++)
				{
						s.setSoTimeout(2000);
					try {
					int t=din.readInt();
					
					//if(t==(i+j))
					{
						System.out.println("Ack recevied" + t);
						f[t]=true;
					}					
					}catch (Exception e) {
						// TODO: handle exception
						int t=0;
						while(i+t<frames && f[i+t])
						{
							t++;
						}
						if(t<ws)
						{
							System.out.println("Ack not received" + (i+t));
							j=ws;
							inc=false;
						}
					}
				}
				while(i<frames && inc)
				{
					if(f[i])
					{
						i++;
					}
					else
					{
						break;
					}
				}
			}
		}catch (Exception e) {
			// TODO: handle exception
		}
	}
	
	public static void main(String[] args) {
		Client c=new Client();
		//c.GBN();
		c.srep();
	}
}
