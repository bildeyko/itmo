package com.bildeyko;

import java.io.*;
import java.net.Socket;

/**
 * Created by ASUS on 18.12.2014.
 */
public class ServerConnection {
    Socket fromserver = null;
    ObjectOutputStream out = null;
    ObjectInputStream in = null;
    String host;
    Integer port;
    public boolean connectStatus;

    public ServerConnection(String host, Integer port){
        this.host = host;
        this.port = port;
    }

    public void connect()
    {
        try {
            fromserver = new Socket(host, port);
            connectStatus = true;
        } catch (IOException e) {
            System.out.println("Can't connect to server");
            connectStatus = false;
            return;
        }
        try {
            out = new ObjectOutputStream(fromserver.getOutputStream());
        } catch (IOException e) {
            System.out.println("Can't get output stream");
            connectStatus = false;
            return;
        }
        try {
            in = new ObjectInputStream(fromserver.getInputStream());
        } catch (IOException e) {
            System.out.println("Can't get input stream");
            connectStatus = false;
            return;
        }
    }

    public void checkServer()
    {
        MarkClient testMark = new MarkClient();
        testMark.x = 99.0;
        testMark.y = 99.0;
        testMark.hash = 99;
        testMark.r = 99.0;
        if(out != null) {
            try {
                out.reset();
                out.writeObject(testMark);
                try {
                    AnswerClass answer = (AnswerClass) in.readObject();
                }catch (ClassNotFoundException e) {
                        System.out.println("Class not found");
                    }
                System.out.println("Сервер доступен");
                connectStatus = true;
            } catch (IOException e) {
                System.out.println("Сервер недоступен");
                connectStatus = false;
                connect();
            }
        } else
        {
            connect();
        }
    }

    public AnswerClass send(Mark m, double r)
    {
        MarkClient tmpMark = new MarkClient();
        tmpMark.x = (double)m.x;
        tmpMark.y = (double)m.y;
        tmpMark.hash = m.hashCode();
        tmpMark.r = r;

        AnswerClass answer = null;
        if(connectStatus) {
            try {
                out.reset();
                out.writeObject(tmpMark);
                try {
                    answer = (AnswerClass) in.readObject();
                } catch (ClassNotFoundException e) {
                    System.out.println("Class not found");
                }
                System.out.println(answer);

            } catch (IOException e) {

            }
        }
        else {
            answer = new AnswerClass();
            answer.status = 2;
        }
        return answer;
    }
}
