import java.net.*;
import java.io.*;
import java.util.*;
public class Server {

	ServerSocket ss=null;
	DataInputStream din=null;
	DataOutputStream dout=null;
	
	public Server() {
		// TODO Auto-generated constructor stub
		try {
			ss=new ServerSocket(22100);
		
		Socket s=ss.accept();
		din=new DataInputStream(s.getInputStream());
		dout=new DataOutputStream(s.getOutputStream());
		System.out.println("Connected\n");
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	void datatransfer()
	{
		int frames;
		try {
			frames=din.readInt();
			int i=0;
			while(i<frames)
			{
				int t=din.readInt();
				if(t==i || true)  //use false when Go Back N
				{
					System.out.println("Received " + t);
					System.out.println("Sending ACK");
					dout.writeInt(t);
					i++;
				}
			}
		
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	public static void main(String[] args) {
		Server s=new Server();
		s.datatransfer();
	}
}
