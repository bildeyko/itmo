package com.bildeyko;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;

/**
 * Created by ASUS on 18.12.2014.
 */
public class ServerConnection {
    Socket fromserver = null;
    PrintWriter out = null;
    BufferedReader in = null;
    String host;
    Integer port;

    public ServerConnection(String host, Integer port){
        this.host = host;
        this.port = port;
    }

    public void connect()
    {
        try {
            fromserver = new Socket(host, port);
        } catch (IOException e) {
            System.out.println("Can't connect to server");
            System.exit(-1);
        }
        try {
            in = new BufferedReader(new
                    InputStreamReader(fromserver.getInputStream()));
        } catch (IOException e) {
            System.out.println("Can't get input stream");
            System.exit(-1);
        }
        try {
            out = new PrintWriter(fromserver.getOutputStream(),true);
        } catch (IOException e) {
            System.out.println("Can't get output stream");
            System.exit(-1);
        }
        BufferedReader inu = new
                BufferedReader(new InputStreamReader(System.in));
    }

    public void send(double num)
    {
        out.println(num);
    }
}
