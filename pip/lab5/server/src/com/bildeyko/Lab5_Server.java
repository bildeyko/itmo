package com.bildeyko;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Iterator;
import java.util.Vector;

import javax.swing.*;

import com.bildeyko.views.MainView;

public class Lab5_Server {

    public static void main(String[] args) {
        ServerSocket servers = null;
        Socket fromclient = null;
        BufferedReader in = null;
        PrintWriter out = null;

        while (true) {
            try {
                servers = new ServerSocket(5555);
            } catch (IOException e) {
                System.out.println("Couldn't listen to port 5555");
                System.exit(-1);
            }

            try {
                System.out.print("Waiting for a client...");
                fromclient = servers.accept();
                System.out.println("Client connected");
            } catch (IOException e) {
                System.out.println("Can't accept");
                System.exit(-1);
            }

            try {
                in = new BufferedReader(new
                        InputStreamReader(fromclient.getInputStream()));
            } catch (IOException e) {
                System.out.println("Can't get input stream");
                System.exit(-1);
            }
            try {
                out = new PrintWriter(fromclient.getOutputStream(), true);
            } catch (IOException e) {
                System.out.println("Can't get output stream");
                System.exit(-1);
            }
            String input, output;

            System.out.println("Wait for messages");
            try {
                while ((input = in.readLine()) != null) {
                    if (input.equalsIgnoreCase("exit")) break;
                    out.println("S ::: " + input);
                    System.out.println(Double.parseDouble(input));
                }
            } catch (IOException e) {
                System.out.println("Error with reading from stream");
                //System.exit(-1);
            }
            try {
                out.close();
                in.close();
                fromclient.close();
                servers.close();
            } catch (IOException e) {
                System.out.println("Can't close streams");
                System.exit(-1);
            }
        }
    }
}
