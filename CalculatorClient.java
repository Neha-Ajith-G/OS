import java.io.*;
import java.net.*;

public class CalculatorClient {
    public static void main(String[] args) {
        String serverAddress = "127.0.0.1";  // Server address (localhost)
        int port = 8080;  // Server port
        try (Socket socket = new Socket(serverAddress, port)) {
            System.out.println("Connected to the server.");

            // Create input and output streams for communication
            BufferedReader userInput = new BufferedReader(new InputStreamReader(System.in));
            BufferedReader serverInput = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            PrintWriter serverOutput = new PrintWriter(socket.getOutputStream(), true);

            String expression;
            while (true) {
                System.out.print("Enter expression (e.g., 5 + 3) or 'exit' to quit: ");
                expression = userInput.readLine();

                if (expression.equalsIgnoreCase("exit")) {
                    serverOutput.println("exit");
                    break;
                }

                // Send the expression to the server
                serverOutput.println(expression);

                // Receive the result from the server
                String result = serverInput.readLine();
                System.out.println(result);  // Print the result
            }

        } catch (IOException e) {
            System.out.println("Client exception: " + e.getMessage());
            e.printStackTrace();
        }
    }
}
