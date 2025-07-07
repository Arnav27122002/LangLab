import java.io.*;
import java.net.*;
import java.util.Scanner;
public class udps{
public static void main(String args[]) throws IOException{
   DatagramSocket serversocket= new DatagramSocket(6000);
   byte[] receiveData= new byte[1024];
   Scanner sc= new Scanner(System.in);
   System.out.println("server waiting");
   DatagramPacket receivePacket= new DatagramPacket(receiveData, receiveData.length);
   serversocket.receive(receivePacket);
   String received= new String(receivePacket.getData(),0, receivePacket.getLength());
   System.out.println("client:"+received);

   byte[] sendData= new byte[1024];
   InetAddress Client= receivePacket.getAddress();
   System.out.println("enter:");
   String dodo= sc.nextLine();
   sendData= dodo.getBytes();
   DatagramPacket sendPacket= new DatagramPacket(sendData, sendData.length, Client, 6000);
   serversocket.send(sendPacket);
}
}