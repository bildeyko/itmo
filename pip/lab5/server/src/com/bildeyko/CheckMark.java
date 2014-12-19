package com.bildeyko;

/**
 * Created by ASUS on 18.12.2014.
 */
public class CheckMark extends Thread {
    private Mark mark;
    private Figure figure;
    public Boolean status;
    private double r;

    public CheckMark(Mark mark, double r)
    {
        this.mark = new Mark(mark.x,mark.y);
        this.r = r;
        figure = new Figure(r);
        status = null;
    }

    public void run() {
        status = figure.checkMark(mark);
    }
}
