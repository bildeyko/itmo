package com.bildeyko;

import java.util.Iterator;
import java.util.Vector;

public class Lab3 {

    public static void main(String[] args) {
        if(args.length != 0) {
            double r = 8;
            try {
                r = checkInputR(args[0]);
            } catch (NumberFormatException e) {
                System.out.print("You entered is not a number.\n");
                System.exit(1);
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

            Iterator<Mark> i = marks.iterator();
            System.out.print("List of marks which located inside of region:\n");
            do {
                Mark current = i.next();
                if (newFigure.checkMark(current))
                    System.out.printf("Mark (%.2f,%.2f)\n", current.x, current.y);
            } while (i.hasNext());
        } else {
            System.out.print("You haven't entered a number R.\n");
        }
    }

    public static double checkInputR(String inputStr) throws NumberFormatException {
        return Double.parseDouble(inputStr);
    }
}
