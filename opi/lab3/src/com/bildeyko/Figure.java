package com.bildeyko;

/**
 * Created by ASUS on 05.11.2014.
 */
public class Figure {
    public double r;

    public Figure(double r) {
        this.r = r;
    }

    public boolean checkMark(Mark mark) {

        if(mark.x >= 0) {
            if(mark.y >= 0 && mark.y <= (r/2 - mark.x)) {
                return true;
            }
            if(mark.y < 0 && mark.y >= (-r/2) && mark.x <= r) {
                return true;
            }
        } else {
            double radius = Math.sqrt(Math.pow(mark.x,2)+Math.pow(mark.y,2));
            if(mark.y <= 0 && radius <= r/2) {
                return true;
            }
        }
        return false;
    }
}
