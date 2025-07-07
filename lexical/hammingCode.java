import java.util.Scanner;

public class hammingCode {
    
    // Function to calculate the value of a parity bit at a given position
    public static int calculateParity(int[] data, int position) {
        int parity = 0;
        for (int i = position - 1; i < data.length; i += 2 * position) {
            for (int j = i; j < i + position && j < data.length; j++) {
                parity ^= data[j];  // XORing all the bits covered by the parity
            }
        }
        return parity;
    }

    // Function to generate the Hamming code (with parity bits)
    public static int[] generateHammingCode(int[] dataBits) {
        int m = dataBits.length;
        int r = 0;

        // Calculate the number of parity bits required
        while (Math.pow(2, r) < (m + r + 1)) {
            r++;
        }

        // Length of the Hamming code (data + parity)
        int[] hammingCode = new int[m + r];

        // Insert data bits and leave spaces for parity bits
        for (int i = 0, j = 0, k = 0; i < hammingCode.length; i++) {
            if ((i + 1) == Math.pow(2, j)) {  // Parity bit positions are powers of 2
                hammingCode[i] = 0;  // Placeholder for parity bit
                j++;
            } else {
                hammingCode[i] = dataBits[k];
                k++;
            }
        }

        // Calculate the parity bits
        for (int i = 0; i < r; i++) {
            int parityPosition = (int) Math.pow(2, i);
            int parity = calculateParity(hammingCode, parityPosition);
            hammingCode[parityPosition - 1] = parity;
        }

        return hammingCode;
    }

    // Function to detect and correct errors in the received Hamming code
    public static void detectAndCorrectError(int[] receivedData) {
        int r = 0;

        // Calculate the number of parity bits in the received data
        while (Math.pow(2, r) < receivedData.length) {
            r++;
        }

        int errorPosition = 0;

        // Recalculate parity bits to detect if there's an error
        for (int i = 0; i < r; i++) {
            int parityPosition = (int) Math.pow(2, i);
            int recalculatedParity = calculateParity(receivedData, parityPosition);

            // If parity doesn't match, there's an error in this bit group
            if (recalculatedParity != 0) {
                errorPosition += parityPosition;
            }
        }

        if (errorPosition == 0) {
            System.out.println("There is no error in the received data.");
        } else {
            System.out.println("Error detected at bit position: " + errorPosition);
            // Correct the error by flipping the bit at the error position
            receivedData[errorPosition - 1] = (receivedData[errorPosition - 1] == 0) ? 1 : 0;
            System.out.println("Corrected data: ");
            printArray(receivedData);
        }
    }

    // Function to print the array (Hamming code)
    public static void printArray(int[] arr) {
        for (int i = 0; i < arr.length; i++) {
            System.out.print(arr[i]);
        }
        System.out.println();
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        // Get the number of data bits
        System.out.print("Enter the number of data bits: ");
        int m = sc.nextInt();

        // Input the data bits
        int[] dataBits = new int[m];
        System.out.println("Enter the data bits:");
        for (int i = 0; i < m; i++) {
            dataBits[i] = sc.nextInt();
        }

        // Generate the Hamming code
        int[] hammingCode = generateHammingCode(dataBits);

        System.out.println("The Hamming code generated for your data is: ");
        printArray(hammingCode);

        // Simulate data being sent (with or without an error)
        System.out.println("Enter the received data bits (with possible error): ");
        int[] receivedData = new int[hammingCode.length];
        for (int i = 0; i < receivedData.length; i++) {
            receivedData[i] = sc.nextInt();
        }

        // Check for errors and correct if necessary
        detectAndCorrectError(receivedData);

        sc.close();
    }
}