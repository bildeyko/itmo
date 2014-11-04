package com.bildeyko;

import java.util.Vector;

public class Lab3 {

    public static void main(String[] args) {
        Vector<Mark> marks = new Vector<Mark>();
        marks.add(new Mark(4,-3));
        marks.add(new Mark(-2,1));
        marks.add(new Mark(-4,-4));
        marks.add(new Mark(-5,4));
        marks.add(new Mark(2,1));
        marks.add(new Mark(0,0));
        marks.add(new Mark(5,4));
        marks.add(new Mark(2,-1));

        Figure newFigure = new Figure(12);
        int i=0;
        System.out.print("List of marks which located inside of region:\n");
        do {
            Mark current = marks.get(i);
            if(newFigure.checkMark(current))
                System.out.printf("Mark (%.2f,%.2f) - %n", current.x, current.y);
            i++;
        } while (i < marks.size());
        System.out.print("Hello!");
    }
}
