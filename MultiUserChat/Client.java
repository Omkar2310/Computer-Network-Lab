import java.io.*;
import java.util.*;
import java.net.*;
public class CLient implements Runnable{
	
	Socket s=null;
	DataInputStream din=null;
	DataOutputStream dout=null;
	String msg=null;
	Scanner cin=null;
	public CLient(String s1) {
		// TODO Auto-generated constructor stub
		cin=new Scanner(System.in);
		int p=Integer.parseInt(s1);
		try {
		s=new Socket("localhost",p);
		System.out.println("Connected\n");
		din=new DataInputStream(s.getInputStream());
		dout=new DataOutputStream(s.getOutputStream());
		
		}catch (Exception e) {
			// TODO: handle exception
		System.out.println("Error in constru");
		}
	}
	
	//function to send msg
	void writemsg()
	{
		try {
			while(true)
			{
				msg=cin.nextLine();
				dout.writeUTF(msg);
				System.out.println("Message sent");
			}
		}catch (Exception e) {
			// TODO: handle exception
		}
	}
	
	public static void main(String[] args) {
		String a;
		System.out.println("ENter port number");
		Scanner sc=new Scanner(System.in);
		a=sc.next();
		CLient c=new CLient(a); 
		Thread t1=new Thread(c);
		t1.start();	//first server msg comes
		c.writemsg(); //write msg to group
	}

	@Override
	public void run() {
		// TODO Auto-generated method stub
		try
		{
			while(true)
			{
				System.out.println("From server " + din.readUTF());
				System.out.println("ENter msg : ");
			}
		}catch (Exception e) {
			// TODO: handle exception
			e.printStackTrace();
		}
	}
	
	
}
