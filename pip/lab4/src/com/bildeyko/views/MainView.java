package com.bildeyko.views;

import com.bildeyko.Figure;
import com.bildeyko.Mark;
import com.bildeyko.views.tools.Plane2;

import javax.swing.*;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;

/**
 * Created by ASUS on 18.11.2014.
 */
public class MainView {
    final Plane2 plane;
    Figure newFigure;
    public MainView() {
        JFrame frm = new JFrame("Область");
        frm.setLayout(new GridLayout(0,2));

        frm.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frm.setResizable(false);

        JPanel controlPanel = new JPanel();
        controlPanel.setLayout(new BoxLayout(controlPanel, BoxLayout.Y_AXIS));
        controlPanel.setBorder(BorderFactory.createLineBorder(Color.lightGray, 1));
        frm.add(controlPanel);

        JPanel listXCont = new JPanel();
        listXCont.setAlignmentX(Component.LEFT_ALIGNMENT);
        listXCont.setLayout(new BoxLayout(listXCont, BoxLayout.X_AXIS));
        JLabel labelX = new JLabel("X");
        listXCont.add(labelX);
        listXCont.add(Box.createRigidArea(new Dimension(30,0)));
        String[] itemsXCoor = {"10","-20","40"};
        final JList listX = new JList(itemsXCoor);
        listX.setVisibleRowCount(-1);
        listX.setSelectedIndex(0);
        listXCont.add(listX);
        controlPanel.add(listXCont);
        frm.add(controlPanel, BorderLayout.NORTH);

        JPanel yButPanel = new JPanel();
        yButPanel.setAlignmentX(Component.LEFT_ALIGNMENT);
        yButPanel.setLayout(new BoxLayout(yButPanel, BoxLayout.X_AXIS));
        yButPanel.add(new JLabel("Y"));
        yButPanel.add(Box.createRigidArea(new Dimension(30,0)));
        final ButtonGroup yGroup = new ButtonGroup();
        JRadioButton yCoor15 = new JRadioButton("15", true);
        yCoor15.setActionCommand("15");
        JRadioButton yCoor_2 = new JRadioButton("-2");
        yCoor_2.setActionCommand("-2");
        JRadioButton yCoor_40 = new JRadioButton("40");
        yCoor_40.setActionCommand("40");
        yGroup.add(yCoor15);
        yGroup.add(yCoor_2);
        yGroup.add(yCoor_40);
        yButPanel.add(yCoor15);
        yButPanel.add(yCoor_2);
        yButPanel.add(yCoor_40);
        controlPanel.add(yButPanel);

        JPanel addMarkButPanel = new JPanel();
        addMarkButPanel.setAlignmentX(Component.LEFT_ALIGNMENT);
        addMarkButPanel.setLayout(new BoxLayout(addMarkButPanel, BoxLayout.X_AXIS));
        addMarkButPanel.add(new JLabel("Добавить/убрать"));
        addMarkButPanel.add(Box.createRigidArea(new Dimension(30,0)));
        JButton addMarkBut = new JButton("Ok");
        addMarkButPanel.add(addMarkBut);
        controlPanel.add(addMarkButPanel);

        JPanel rPanelout = new JPanel();
        rPanelout.setAlignmentX(Component.LEFT_ALIGNMENT);
        rPanelout.setLayout(new FlowLayout());
        JPanel rPanel = new JPanel();
        rPanel.setAlignmentX(Component.LEFT_ALIGNMENT);
        rPanel.setLayout(new BoxLayout(rPanel, BoxLayout.X_AXIS));
        rPanel.add(new JLabel("R"));
        rPanel.add(Box.createRigidArea(new Dimension(30,0)));
        JPanel rPanelsp = new JPanel();
        rPanelsp.setLayout(new FlowLayout());
        JSpinner spinner = new JSpinner(new SpinnerNumberModel(50,35,70,5));
        rPanelsp.add(spinner);
        rPanel.add(rPanelsp);
        rPanelout.add(rPanel);
        controlPanel.add(rPanelout);
        ChangeListener listener = new ChangeListener() {
            public void stateChanged(ChangeEvent e) {
                JSpinner spinnerTemp = (JSpinner)e.getSource();
                SpinnerModel spinnerModel = spinnerTemp.getModel();
                newFigure = new Figure((Integer)spinnerModel.getValue());
                plane.updateFigure(newFigure);
                plane.setRadius((Integer)spinnerModel.getValue());
            }
        };
        spinner.addChangeListener(listener);

        JPanel lastPointPanel = new JPanel();
        lastPointPanel.setAlignmentX(Component.LEFT_ALIGNMENT);
        lastPointPanel.setLayout(new BoxLayout(lastPointPanel, BoxLayout.X_AXIS));
        lastPointPanel.add(new JLabel("Последняя точка:"));
        lastPointPanel.add(Box.createRigidArea(new Dimension(30,0)));
        final JLabel lastPoint = new JLabel("-");
        lastPointPanel.add(lastPoint);
        controlPanel.add(lastPointPanel);

        JPanel planeCont = new JPanel();
        planeCont.setLayout(new BoxLayout(planeCont,BoxLayout.Y_AXIS));
        plane = new Plane2();
        plane.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                Dimension size = plane.getSize();
                Float x = (e.getX() - size.width/2)/(plane.scaleX);
                Float y = (size.height/2 - e.getY())/(plane.scaleY);
                plane.addMark(new Mark(x, y));
                lastPoint.setText("x: "+String.format("%.2f", x)+", y: "+String.format("%.2f", y));
            }
        });
        addMarkBut.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                Float x = Float.parseFloat(listX.getSelectedValue().toString());
                Float y = Float.parseFloat(yGroup.getSelection().getActionCommand());
                plane.addMark(new Mark(x, y));
                lastPoint.setText("x: " + String.format("%.2f", x) + ", y: " + String.format("%.2f", y));
            }
        });
        planeCont.add(plane);
        frm.add(planeCont);
        frm.pack();
        frm.setVisible(true);

        plane.setRadius((Integer)spinner.getValue());
        newFigure = new Figure((Integer)spinner.getValue());
        plane.updateFigure(newFigure);


    }
}
