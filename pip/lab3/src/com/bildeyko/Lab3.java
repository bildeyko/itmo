package com.bildeyko;

import java.util.Vector;

public class Lab3 {

    public static void main(String[] args) {
        if(args.length != 0) {
            double r = 8;
            try {
                r = Double.parseDouble(args[0]);
            } catch (NumberFormatException e) {
                System.out.print("You entered is not a number.\n");
                System.out.print("By default, the number R is 8.\n");
            }

            Figure newFigure = new Figure(r);

            Vector<Mark> marks = new Vector<Mark>();
            marks.add(new Mark(4, -3));
            marks.add(new Mark(-2, 1));
            marks.add(new Mark(-4, -4));
            marks.add(new Mark(-5, 4));
            marks.add(new Mark(2, 1));
            marks.add(new Mark(0, 0));
            marks.add(new Mark(5, 4));
            marks.add(new Mark(2, -1));

            int i = 0;
            System.out.print("List of marks which located inside of region:\n");
            do {
                Mark current = marks.get(i);
                if (newFigure.checkMark(current))
                    System.out.printf("Mark (%.2f,%.2f)\n", current.x, current.y);
                i++;
            } while (i < marks.size());
        } else {
            System.out.print("You haven't entered a number R.\n");
        }
    }
}
