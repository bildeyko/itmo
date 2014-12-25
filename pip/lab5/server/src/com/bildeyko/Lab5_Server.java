package com.bildeyko;

import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;

public class Lab5_Server {

    public static void main(String[] args) {
        ServerSocket servers = null;
        Socket fromclient = null;
        ObjectInputStream in = null;
        ObjectOutputStream out = null;

        while (true) {
            try {
                servers = new ServerSocket(5556);
            } catch (IOException e) {
                System.out.println("Couldn't listen to port 5556");
                System.exit(-1);
            }

            try {
                System.out.println("Waiting for a client...");
                fromclient = servers.accept();
                System.out.println("Client connected");
            } catch (IOException e) {
                System.out.println("Can't accept");
                System.exit(-1);
            }

            try {
                in = new ObjectInputStream(fromclient.getInputStream());
            } catch (IOException e) {
                System.out.println("Can't get input stream");
                System.exit(-1);
            }
            try {
                out = new ObjectOutputStream(fromclient.getOutputStream());
            } catch (IOException e) {
                System.out.println("Can't get output stream");
                System.exit(-1);
            }
            System.out.println("Wait for messages");
            try {
                while (true) {
                    MarkClient tmpMark = null;
                    try {
                        tmpMark = (MarkClient) in.readObject();
                    } catch (ClassNotFoundException e) {
                        System.out.println("Class not found");
                    }

                        CheckMark t = new CheckMark(tmpMark,out);
                        t.run();
                    System.out.println(tmpMark.toString());
                }
            } catch (IOException e) {
                System.out.println("Client disconnected");
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
