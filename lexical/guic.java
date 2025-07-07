import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class guic {

    public static void main(String args[]) {
        new guic().createGUI(); // Start the GUI creation
    }

    public static void createGUI() {
        // Create the main frame
        JFrame frame = new JFrame("Client");
        frame.setSize(400, 500);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); // Exit the application when the frame closes

        // Main panel with vertical layout
        JPanel mainPanel = new JPanel();
        mainPanel.setLayout(new BoxLayout(mainPanel, BoxLayout.Y_AXIS)); // Arranges components vertically

        // List model and view for displaying messages
        DefaultListModel<String> lstModel = new DefaultListModel<>();
        JList<String> lstView = new JList<>(lstModel); // List for displaying messages
        JScrollPane sclView = new JScrollPane(lstView); // Adds scrolling functionality for the list
        lstModel.addElement("hello"); // Add a sample message to the list
        mainPanel.add(sclView); // Add the scrollable list to the main panel

        // Panel for input and button
        JPanel inputPanel = new JPanel();
        inputPanel.setLayout(new FlowLayout()); // Horizontal layout for text field and button

        // Text field for user input
        JTextField txtInput = new JTextField(20); // Creates a text field with 20 columns
        inputPanel.add(txtInput); // Add the text field to the input panel

        // Button for sending messages
        JButton btnSend = new JButton("Send"); // Create a button labeled "Send"
        inputPanel.add(btnSend); // Add the button to the input panel

        // Add input panel to the main panel
        mainPanel.add(inputPanel);

        // Add main panel to the frame
        frame.add(mainPanel);

        // Add action listener for the "Send" button
        btnSend.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String message = txtInput.getText(); // Get the text entered by the user
                if (!message.isEmpty()) { // Check if the text field is not empty
                    lstModel.addElement("You: " + message); // Add the message to the list
                    txtInput.setText(""); // Clear the text field after sending
                    // Here, you can send the message to the server logic (not implemented yet)
                }
            }
        });

        // Make the frame visible
        frame.setVisible(true);
    }
}
