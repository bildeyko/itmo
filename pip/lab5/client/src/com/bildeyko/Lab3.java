package com.bildeyko;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.Iterator;
import java.util.Vector;

import javax.swing.*;

import com.bildeyko.views.MainView;

public class Lab3 {

    public static void main(String[] args) {
        /*SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                new MainView();
            }
        });*/

        int a = 2;
        int y = (a == 2) ? (a-- - 1) : (--a + 1);
        System.out.println(args[y]);

        /*Socket fromserver = null;
        PrintWriter out = null;
        BufferedReader in = null;
        try {
            fromserver = new Socket("127.0.0.1", 5555);
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

        out.println("Hello!");
        out.println("Hello2!");*/
       /* try {
           // out.close();
           // in.close();
           // inu.close();
           // fromserver.close();
        } catch (IOException e) {
            System.out.println("Can't close streams");
            System.exit(-1);
        }*/
    }
}
