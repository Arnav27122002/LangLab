import java.io.*;
import java.net.*;
import java.util.*;
public class tcpc{
	public static void main(String args[]) throws IOException{
		Socket s= new Socket("localhost", 8000);
		System.out.println("client ready");
		Scanner sc= new Scanner(System.in);
		Scanner in= new Scanner(s.getInputStream()); 
		PrintWriter out= new PrintWriter(s.getOutputStream());
		while(true)
		{
			String to= sc.nextLine();
			if(to.equals("exit"))
			{
				break;
			}
			out.println(to);
			out.flush();
			String dodo= in.nextLine();
			if(dodo.equals("exit"))
			{
				break;
			}
			System.out.println(dodo);
		}

	}
}