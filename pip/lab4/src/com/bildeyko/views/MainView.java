package com.bildeyko.views;

import javax.swing.*;
import java.awt.*;

/**
 * Created by ASUS on 18.11.2014.
 */
public class MainView {
    public MainView() {
        JFrame frm = new JFrame("Область");
        //frm.setLayout(new BoxLayout(frm.getContentPane(), BoxLayout.Y_AXIS));

        frm.setSize(500,500);
        frm.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        JPanel controlPanel = new JPanel();
        controlPanel.setLayout(new GridLayout(10,1));
        controlPanel.setVisible(true);
        controlPanel.setSize(100,100);
        controlPanel.setBorder(BorderFactory.createLineBorder(Color.DARK_GRAY, 2));
        frm.add(controlPanel);

        JPanel xPanel = new JPanel();
        xPanel.setLayout(new BoxLayout(xPanel, BoxLayout.X_AXIS));
        xPanel.setMaximumSize(new Dimension(200, 100));
        xPanel.setBorder(BorderFactory.createLineBorder(Color.DARK_GRAY, 2));
        String[] itemsXCoor = {"2", "5", "10"};
        JComboBox xBox = new JComboBox(itemsXCoor);
        //xBox.setMaximumSize(new Dimension(200, 100));
        xPanel.add(new JLabel("X"));
        xPanel.add(Box.createRigidArea(new Dimension(5,0)));
        xPanel.add(xBox);

        JPanel yPanel = new JPanel();
        yPanel.setLayout(new BoxLayout(yPanel, BoxLayout.X_AXIS));
        JPanel yButPanel = new JPanel();
        yButPanel.setLayout(new BoxLayout(yButPanel, BoxLayout.Y_AXIS));
        JRadioButton yCoor1 = new JRadioButton("1", true);
        JRadioButton yCoor3 = new JRadioButton("3");
        JRadioButton yCoor15 = new JRadioButton("15");
        ButtonGroup yGroup = new ButtonGroup();
        yGroup.add(yCoor1);
        yGroup.add(yCoor3);
        yGroup.add(yCoor15);

        yButPanel.add(yCoor1);
        yButPanel.add(yCoor3);
        yButPanel.add(yCoor15);
        yPanel.add(new JLabel("Y"));
        yPanel.add(Box.createRigidArea(new Dimension(5,0)));
        yPanel.add(yButPanel);

        controlPanel.add(xPanel);
        controlPanel.add(yPanel);

        //JLabel lab = new JLabel("Hello!");
        //frm.add(lab);

       // frm.setContentPane(inputPanel);
        frm.setVisible(true);
    }
}
