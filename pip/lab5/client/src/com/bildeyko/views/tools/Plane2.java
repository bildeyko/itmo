package com.bildeyko.views.tools;

import com.bildeyko.Mark;
import com.bildeyko.ServerConnection;

import javax.swing.*;
import java.awt.*;
import java.util.ArrayList;
import java.util.Iterator;

/**
 * Created by ASUS on 04.12.2014.
 */
public class Plane2 extends JPanel {

    public ArrayList<Mark> marks;
    public ArrayList<Thread> threads;
    public float scaleY;
    public float scaleX;
    public int segmentLengthW, segmentLengthH;
    private Integer radius;
    public int offset = 20;

    public Plane2()
    {
        Dimension size = new Dimension(300,300);
        setPreferredSize(size);
        marks = new ArrayList<Mark>();
        threads = new ArrayList<Thread>();
        segmentLengthW = (size.width-2* offset)/4;
        segmentLengthH = (size.height-2* offset)/4;
    }

    public void addMark(Mark point)
    {
        point.setRadius(radius);
        if(!marks.contains(point)) {
            marks.add(point);
        } else {
            marks.remove(point);
        }
        this.repaint();
    }

    public void setRadius(Integer rad, ServerConnection server) {
        radius = rad;
        scaleX = (float)(2*segmentLengthW)/radius;
        scaleY = (float)(2*segmentLengthH)/radius;

        Iterator<Thread> j = threads.iterator();
        while (j.hasNext()) {
            Thread current = j.next();
            current.interrupt();
        }
        if(threads.size() != 0)
            threads.clear();

        Iterator<Mark> i = marks.iterator();
        while (i.hasNext()) {
            Mark current = i.next();
            current.status = server.send(current, rad).status;
            current.setRadius(rad);
            if(current.status == 1) {
                Runnable r = new MarkRunnable(current,this);
                Thread t = new Thread(r);
                threads.add(t);
                t.start();
            }
        }
        this.repaint();
    }

    public void paintComponent(Graphics g)
    {
        super.paintComponent(g);
        Dimension size = getSize();
        g.setColor(Color.white);
        g.fillRect(0,0, size.width, size.height);
        drawFigure(g, Color.black);
        drawPlant(g);

        Iterator<Mark> i = marks.iterator();
        while (i.hasNext()) {
            Mark current = i.next();
            if(current.status == 2)
                g.setColor(Color.gray);
            if(current.status == 1)
                g.setColor(Color.green);
            if(current.status == 0)
                g.setColor(Color.red);
            int ovalX = (int)(current.x*scaleX) + size.width/2;
            int ovalY = -(int)(current.y*scaleY) + size.height/2;
            g.drawOval(ovalX-current.currentSize/2 - 1,ovalY-current.currentSize/2,current.currentSize,current.currentSize);

            g.drawString("x: "+String.format("%.2f", current.x),ovalX+8, ovalY-10);
            g.drawString("y: "+String.format("%.2f", current.y),ovalX+8, ovalY);
        }
    }

    public  void drawPlant(Graphics g) {
        Dimension size = getSize();
        g.setColor(Color.blue);
        g.drawLine(size.width/2, 0, size.width/2,size.height);
        g.drawLine(size.width/2, 0, size.width/2 - 3, 8);
        g.drawLine(size.width/2, 0, size.width/2 + 3, 8);
        g.drawLine(size.width,size.height/2, 0, size.height/2);
        g.drawLine(size.width,size.height/2, size.width - 8, size.height/2 - 3);
        g.drawLine(size.width,size.height/2, size.width - 8, size.height/2 + 3);
        int lineSize = 2;
        g.drawLine(size.width/2 + segmentLengthW,size.height/2 - lineSize, size.width/2 + segmentLengthW, size.height/2 + lineSize);
        g.drawLine(size.width/2 + 2*segmentLengthW,size.height/2 - lineSize, size.width/2 + 2*segmentLengthW, size.height/2 + lineSize);
        g.drawLine(size.width/2 - segmentLengthW,size.height/2 - lineSize, size.width/2 - segmentLengthW, size.height/2 + lineSize);
        g.drawLine(size.width/2 - 2*segmentLengthW,size.height/2 - lineSize, size.width/2 - 2*segmentLengthW, size.height/2 + lineSize);

        g.drawLine(size.width/2 - lineSize,size.height/2 - segmentLengthH, size.width/2 + lineSize,size.height/2 - segmentLengthH);
        g.drawLine(size.width/2 - lineSize,size.height/2 - 2*segmentLengthH, size.width/2 + lineSize,size.height/2 - 2*segmentLengthH);
        g.drawLine(size.width/2 - lineSize,size.height/2 + segmentLengthH, size.width/2 + lineSize,size.height/2 + segmentLengthH);
        g.drawLine(size.width/2 - lineSize,size.height/2 + 2*segmentLengthH, size.width/2 + lineSize,size.height/2 + 2*segmentLengthH);
    }

    public  void drawFigure(Graphics g, Color color) {
        g.setColor(color);
        Dimension size = getSize();
        int x,y;
        //Круг
        for(x=-1;x>-radius*scaleX;x--) {
            y = (int)Math.sqrt(Math.pow(radius*scaleX,2)-Math.pow(x,2));
            g.drawLine(size.width/2+x,size.height/2-0,size.width/2+x,size.height/2-y);
        }

        // Прямая 4 ч
        for(x=1;x<radius*scaleX;x++) {
            y = (int)(-(radius/2)*scaleX);
            g.drawLine(size.width/2+x,size.height/2-0,size.width/2+x,size.height/2-y);
        }

        // Прямая 3 ч
        for(x=-1;x>-(radius/2)*scaleX;x--) {
            y = (int)-(2*x+radius*scaleX)/2;
            g.drawLine(size.width/2+x,size.height/2-0,size.width/2+x,size.height/2-y);
        }
    }
}
