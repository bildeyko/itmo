package com.bildeyko.views;

import com.bildeyko.Figure;
import com.bildeyko.views.tools.PlaneCanvas;
import com.bildeyko.views.tools.Plane;

import javax.swing.*;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import java.awt.*;

/**
 * Created by ASUS on 18.11.2014.
 */
public class MainView {
    final Plane plane;
    Figure newFigure;
    public MainView() {
        JFrame frm = new JFrame("Область");
        frm.setLayout(new BoxLayout(frm.getContentPane(), BoxLayout.Y_AXIS));

        frm.setSize(500,500);
        frm.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        JPanel controlPanel = new JPanel();
        controlPanel.setLayout(new GridLayout(0,2));
        controlPanel.setBorder(BorderFactory.createLineBorder(Color.DARK_GRAY, 1));
        frm.add(controlPanel);

        JPanel listXCont = new JPanel();
        listXCont.setLayout(new FlowLayout());
        listXCont.setBorder(BorderFactory.createLineBorder(Color.DARK_GRAY, 1));
        //listXCont.setMaximumSize(new Dimension(200, 100));
        String[] itemsXCoor = {"2", "5", "10"};
        JList listX = new JList(itemsXCoor);
        listX.setVisibleRowCount(-1);
        listXCont.add(listX);
        controlPanel.add(new JLabel("X"));
        controlPanel.add(listXCont);
       // frm.add(controlPanel);
        frm.add(controlPanel, BorderLayout.NORTH);

        JPanel yButPanel = new JPanel();
        yButPanel.setLayout(new BoxLayout(yButPanel, BoxLayout.Y_AXIS));
        ButtonGroup yGroup = new ButtonGroup();
        JRadioButton yCoor1 = new JRadioButton("1", true);
        JRadioButton yCoor3 = new JRadioButton("3");
        JRadioButton yCoor15 = new JRadioButton("15");
        yGroup.add(yCoor1);
        yGroup.add(yCoor3);
        yGroup.add(yCoor15);
        yButPanel.add(yCoor1);
        yButPanel.add(yCoor3);
        yButPanel.add(yCoor15);
        controlPanel.add(new JLabel("Y"));
        controlPanel.add(yButPanel);

        JPanel rPanel = new JPanel();
        rPanel.setLayout(new FlowLayout());
        JSpinner spinner = new JSpinner(new SpinnerNumberModel(5,1,20,1));
        rPanel.add(spinner);
        controlPanel.add(new JLabel("R"));
        controlPanel.add(rPanel);
        ChangeListener listener = new ChangeListener() {
            public void stateChanged(ChangeEvent e) {
                JSpinner spinnerTemp = (JSpinner)e.getSource();
                SpinnerModel spinnerModel = spinnerTemp.getModel();
                System.out.println("Source: " + spinnerModel.getValue());
                plane.setRadius((Integer)spinnerModel.getValue());
                newFigure = new Figure((Integer)spinnerModel.getValue());
            }
        };

        spinner.addChangeListener(listener);

       plane = new Plane(200,200);
        plane.setPoint(10,10);
        /*JPanel planePanel = new JPanel();
        planePanel.setLayout(new FlowLayout());
        PlaneCanvas test = new PlaneCanvas();
        planePanel.add(test);
        test.setSize(200,200);*/
        frm.add(plane);

        /*JPanel controlPanel = new JPanel();
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
        controlPanel.add(yPanel);*/

        //JLabel lab = new JLabel("Hello!");
        //frm.add(lab);

       // frm.setContentPane(inputPanel);
        frm.pack();
        frm.setVisible(true);
    }
}
