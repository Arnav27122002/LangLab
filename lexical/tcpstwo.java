import java.io.*;
import java.net.*;
public class tcpstwo {
    public static void main(String args[])
    throws IOException{
        ServerSocket ss= new ServerSocket(6000);
        Socket s= ss.accept();
        DataOutputStream ds= new DataOutputStream(s.getOutputStream());
        System.out.println("enter:/t");
        BufferedReader br= new BufferedReader(new InputStreamReader(System.in));
        BufferedReader br1= new BufferedReader(new InputStreamReader(s.getInputStream()));
        String str;
        while((str=br.readLine()))
        
    }
}
