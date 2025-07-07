import java.util.HashMap;
import java.util.PriorityQueue;
import java.util.Scanner;

class HuffmanNode implements Comparable<HuffmanNode> {
    char c;
    int data;
    HuffmanNode left, right;

    // Constructor for the leaf node
    public HuffmanNode(char c, int data) {
        this.c = c;
        this.data = data;
        this.left = this.right = null;
    }

    // Constructor for the internal node
    public HuffmanNode(char c, int data, HuffmanNode left, HuffmanNode right) {
        this.c = c;
        this.data = data;
        this.left = left;
        this.right = right;
    }

    // Comparing the nodes based on their frequencies
    public int compareTo(HuffmanNode node) {
        return this.data - node.data;
    }
}

class Huffman {
    // Function to build the Huffman code mapping
    public static void buildCodeMap(HuffmanNode root, String s, HashMap<Character, String> huffmanCode) {
        if (root.left == null && root.right == null) {
            huffmanCode.put(root.c, s); // Put the character and its code in the map
            return;
        }
        buildCodeMap(root.left, s + "0", huffmanCode);
        buildCodeMap(root.right, s + "1", huffmanCode);
    }

    // Function to decode the encoded string
    public static String decodeString(HuffmanNode root, String encodedString) {
        StringBuilder decodedString = new StringBuilder();
        HuffmanNode currentNode = root;
        for (int i = 0; i < encodedString.length(); i++) {
            currentNode = (encodedString.charAt(i) == '0') ? currentNode.left : currentNode.right;

            // If it's a leaf node, we've found a character
            if (currentNode.left == null && currentNode.right == null) {
                decodedString.append(currentNode.c);
                currentNode = root; // Start again from the root for the next character
            }
        }
        return decodedString.toString();
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        // Get number of characters
        System.out.print("Enter number of characters: ");
        int n = sc.nextInt();

        // Arrays to store the characters and frequencies
        char[] charArray = new char[n];
        int[] charfreq = new int[n];

        // Input characters and their frequencies
        for (int i = 0; i < n; i++) {
            System.out.print("Enter character: ");
            charArray[i] = sc.next().charAt(0);
            System.out.print("Enter frequency of " + charArray[i] + ": ");
            charfreq[i] = sc.nextInt();
        }

        // Priority queue to hold Huffman nodes
        PriorityQueue<HuffmanNode> q = new PriorityQueue<>();

        // Create HuffmanNode for each character and add to priority queue
        for (int i = 0; i < n; i++) {
            q.add(new HuffmanNode(charArray[i], charfreq[i]));
        }

        // Create the Huffman Tree
        while (q.size() > 1) {
            HuffmanNode left = q.poll();
            HuffmanNode right = q.poll();
            int sum = left.data + right.data;
            q.add(new HuffmanNode('-', sum, left, right));
        }

        // Root of the Huffman Tree
        HuffmanNode root = q.poll();

        // Build the Huffman code map
        HashMap<Character, String> huffmanCode = new HashMap<>();
        buildCodeMap(root, "", huffmanCode);

        // Print the Huffman codes
        System.out.println("Huffman Codes:");
        for (char c : huffmanCode.keySet()) {
            System.out.println(c + ": " + huffmanCode.get(c));
        }

        // Accept a string from the user
        System.out.print("Enter a string containing the above characters: ");
        String inputString = sc.next();

        // Convert the input string to its Huffman encoded form
        StringBuilder encodedString = new StringBuilder();
        for (char c : inputString.toCharArray()) {
            encodedString.append(huffmanCode.get(c));
        }

        // Display the encoded string
        System.out.println("Encoded string: " + encodedString.toString());

        // Decode the encoded string
        String decodedString = decodeString(root, encodedString.toString());

        // Display the decoded string
        System.out.println("Decoded string: " + decodedString);

        sc.close();
    }
}
