import java.io.*;
import java.net.*;
import java.util.Scanner;

public class udpc{
    public static void main(String args[]) throws IOException{
        DatagramSocket s= new DatagramSocket();
        InetAddress address = InetAddress.getByName("localhost");
        Scanner sc = new Scanner(System.in);
        byte[] sendData = new byte[1024];
        System.out.println("enter message to send:");
        String msg= sc.nextLine();
        sendData = msg.getBytes();
        DatagramPacket sendPacket= new DatagramPacket(sendData, sendData.length, address, 6000);
        s.send(sendPacket);

        byte[] receiveData= new byte[1024];
        System.out.println("client waiting");
        DatagramPacket receivePacket= new DatagramPacket(receiveData, receiveData.length);
        s.receive(receivePacket);
        String received= new String(receivePacket.getData(), 0, receivePacket.getLength());
        System.out.println("from server:"+received);
    }
}