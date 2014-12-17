package com.bildeyko;

import java.util.Iterator;
import java.util.Vector;

import javax.swing.*;

import com.bildeyko.views.MainView;

public class Lab3 {

    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                new MainView();
            }
        });
    }
}
