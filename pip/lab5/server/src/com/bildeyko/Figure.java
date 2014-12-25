package com.bildeyko;

/**
 * Created by ASUS on 05.11.2014.
 */
public class Figure {
    public double r;

    public Figure(double r) {
        this.r = r;
    }

    public Integer checkMark(Mark mark) {
        int y = 0;
        if(mark.x <= 0) {
            if(mark.y >= 0) {
                y = (int) Math.sqrt(Math.pow(r, 2) - Math.pow(mark.x, 2));
                if(mark.y <= y)
                    return 1;
            }
            if(mark.y < 0) {
                y = (int) -(2 * mark.x + r) / 2;
                if(mark.y >= y)
                    return 1;
            }

        }
        if(mark.x >= 0 && mark.x <= r) {
            if(mark.y < 0) {
                y = (int)(-(r/2));
                if(mark.y >= y)
                    return 1;
            }
        }
        return 0;
    }
}
