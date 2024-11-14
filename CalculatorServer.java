import java.io.*;
import java.net.*;

public class CalculatorServer {
    public static void main(String[] args) {
        int port = 8080;  // Port number
        try (ServerSocket serverSocket = new ServerSocket(port)) {
            System.out.println("Server is listening on port " + port);

            // Server will continuously accept client connections
            while (true) {
                Socket socket = serverSocket.accept();  // Accept new client connection
                System.out.println("New client connected");

                // Create input and output streams for communication
                BufferedReader input = new BufferedReader(new InputStreamReader(socket.getInputStream()));
                PrintWriter output = new PrintWriter(socket.getOutputStream(), true);

                String request;
                while ((request = input.readLine()) != null) {
                    if (request.equalsIgnoreCase("exit")) {
                        System.out.println("Client disconnected.");
                        break;
                    }

                    // Process the received calculation request (e.g., "5 + 3")
                    String result = calculate(request);
                    output.println(result);  // Send result back to the client
                }

                socket.close();  // Close the client connection after handling the request
            }
        } catch (IOException e) {
            System.out.println("Server exception: " + e.getMessage());
            e.printStackTrace();
        }
    }

    // Method to process the mathematical operation
    public static String calculate(String expression) {
        try {
            String[] tokens = expression.split(" ");
            double num1 = Double.parseDouble(tokens[0]);
            String operator = tokens[1];
            double num2 = Double.parseDouble(tokens[2]);
            double result = 0;

            switch (operator) {
                case "+":
                    result = num1 + num2;
                    break;
                case "-":
                    result = num1 - num2;
                    break;
                case "*":
                    result = num1 * num2;
                    break;
                case "/":
                    if (num2 == 0) {
                        return "Error: Division by zero!";
                    }
                    result = num1 / num2;
                    break;
                default:
                    return "Invalid operator!";
            }

            return "Result: " + result;
        } catch (Exception e) {
            return "Invalid expression!";
        }
    }
}
