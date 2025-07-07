import java.io.*;
import java.net.*;
import java.util.*;
public class tcps{
    public static void main(String args[]) throws IOException{
        ServerSocket ss= new ServerSocket(8000);
        System.out.println("server listening");
        Socket s= ss.accept();
        System.out.println("client connected");
        Scanner sc= new Scanner(System.in);
        Scanner in= new Scanner(s.getInputStream());
        PrintWriter out= new PrintWriter(s.getOutputStream());
        while(true){
            String msg= in.nextLine();
        if(msg.equals("exit"))
        {
            break;
        }
        System.out.println("Client:"+msg);
        String dodo= sc.nextLine();
        if(dodo.equals("exit"))
        {
            break;
        }
        out.println(dodo);
        out.flush();
        }
    }
}