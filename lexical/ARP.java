import java.io.*;
import java.util.*;
public class ARP {
    public static void main(String args[]) throws FileNotFoundException
    {
        File fp= new File("arp.txt");
        Scanner sc= new Scanner(System.in);
        System.out.println("enter ip address:");
        String inpIp= sc.nextLine().trim();
        Scanner in= new Scanner(fp);
        while(in.hasNextLine())
        {
            String line= in.nextLine();
            String[] parts= line.split(" ");
            System.out.println(Arrays.toString(parts));
            
                String ip= parts[0];
                String mac= parts[1];
                if(ip.equals(inpIp))
                {
                    System.out.println(mac);
                    break;
                }
                else if(!ip.equals(inpIp)){
                    System.out.println("error");
                }
            }
        }

    }