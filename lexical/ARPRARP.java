import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class ARPRARP {

    private Map<String, String> arpTable;
    private Map<String, String> rarpTable;

 

    public ARPRARP() {
        arpTable = new HashMap<>();
        rarpTable = new HashMap<>();
        initializeMappings("mappings.txt");
    }

    private void initializeMappings(String fileName) {
        try (BufferedReader br = new BufferedReader(new FileReader(fileName))) {
            String line;
            while ((line = br.readLine()) != null) {
                String[] parts = line.split(" ");
                if (parts.length == 2) {
                    arpTable.put(parts[0], parts[1]);
                    rarpTable.put(parts[1], parts[0]);
                }
            }
        } catch (IOException e) {
            System.out.println("Error reading from file: " + e.getMessage());
        }
    }

    public String resolveIP(String ipAddress) {
       
        return arpTable.getOrDefault(ipAddress, "00:1A:2B:3C:4D:FF");
    }

    public String resolveMAC(String macAddress) {
       
        return rarpTable.getOrDefault(macAddress,"192.168.1.100");
    }

    public static void main(String[] args) {
        ARPRARP arpRarp = new ARPRARP();
        Scanner scanner = new Scanner(System.in);
        String choice;

        do {
            System.out.println("Select an option:");
            System.out.println("1. ARP");
            System.out.println("2. RARP");
            System.out.println("3. Exit");
            choice = scanner.nextLine();

            switch (choice) {
                case "1":
                    System.out.print("Enter IP Address: ");
                    String ip = scanner.nextLine();
                    String mac = arpRarp.resolveIP(ip);
                    System.out.println("MAC Address: " + mac);
                    break;
                case "2":
                    System.out.print("Enter MAC Address: ");
                    String macAddress = scanner.nextLine();
                    String ipAddress = arpRarp.resolveMAC(macAddress);
                    System.out.println("IP Address: " + ipAddress);
                    break;
                case "3":
                    System.out.println("Exiting");
                    break;
                default:
                    System.out.println("Invalid choice.");
            }
        } while (!choice.equals("3"));

        scanner.close();
    }
}
