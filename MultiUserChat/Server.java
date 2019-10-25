import java.io.*;
import java.util.*;
import java.net.*;
public class Server {
	ServerSocket ss=null;
	ServerSocket ss1=null,ss2=null;
	DataInputStream din=null,din1=null,din2=null;
	DataOutputStream dout=null,dout1=null,dout2=null;
	
	static Runnable r1,r2,r3=null;
	
	public Server(String a) {
		// TODO Auto-generated constructor stub
		int p=Integer.parseInt(a);
		try {
		ss=new ServerSocket(p);
		Socket s=ss.accept();
		//System.out.println("connected to client");
		//System.out.println("Connected to 1\n");
		
		ss1=new ServerSocket(p+1);
		Socket s1=ss1.accept();
		//System.out.println("connected to client");
	//	System.out.println("Connected to 2\n");
		
		ss2=new ServerSocket(p+2);
			Socket s2=ss2.accept();
		//System.out.println("connected to client");
		//System.out.println("Connected to 3\n");
		
		System.out.println("All clients connected");
		
		din=new DataInputStream(s.getInputStream());
		dout=new DataOutputStream(s.getOutputStream());
		din1=new DataInputStream(s1.getInputStream());
		dout1=new DataOutputStream(s1.getOutputStream());
		din2=new DataInputStream(s2.getInputStream());
		dout2=new DataOutputStream(s2.getOutputStream());

		
		}catch (Exception e) {
			// TODO: handle exception
			System.out.println("Error in serv construc");
		}
		
		r1=new Runnable() {
			
			@Override
			public void run() {
				// TODO Auto-generated method stub
				try {
					while(true)
					{
						String m;
						m=din.readUTF();
						dout.writeUTF("Client id 1 " + m);
						dout1.writeUTF("Client id 1 " + m);
						dout2.writeUTF("Client id 1 " + m);
					}
				}catch (Exception e) {
					// TODO: handle exception
					e.printStackTrace();
				}
			}
		};
		
		r2=new Runnable() {
			
			@Override
			public void run() {
				// TODO Auto-generated method stub
				try {
					while(true)
					{
						String m;
						m=din1.readUTF();
						dout.writeUTF("Client id 2 " + m);
						dout1.writeUTF("Client id 2 " + m);
						dout2.writeUTF("Client id 2 " + m);
					}
				}catch (Exception e) {
					// TODO: handle exception
					e.printStackTrace();
				}
			}
		};
		
		r3=new Runnable() {
			
			@Override
			public void run() {
				// TODO Auto-generated method stub
				try {
					while(true)
					{
						String m;
						m=din2.readUTF();
						dout.writeUTF("Client id 3 " + m);
						dout1.writeUTF("Client id 3 " + m);
						dout2.writeUTF("Client id 3 " + m);
					}
				}catch (Exception e) {
					// TODO: handle exception
					e.printStackTrace();
				}
			}
		};
	}
	
	
	public static void main(String[] args) {
		String a=args[0];
		Server s=new Server(a);
		Thread t1=new Thread(r1);
		Thread t2=new Thread(r2);
		Thread t3=new Thread(r3);
		t1.start();
		t2.start();
		t3.start();
	}
}
