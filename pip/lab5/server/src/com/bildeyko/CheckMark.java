package com.bildeyko;

import java.io.IOException;
import java.io.ObjectOutputStream;

/**
 * Created by ASUS on 18.12.2014.
 */
public class CheckMark extends Thread {
    private MarkClient mark;
    private Figure figure;
    public Integer status;
    private double r;
    public ObjectOutputStream out = null;

    public CheckMark(MarkClient mark, ObjectOutputStream out)
    {
        this.mark = mark;
        this.r = mark.r;
        figure = new Figure(r);
        status = null;
        this.out = out;
    }

    public void run() {
        Mark tmpMark = new Mark(mark.x.floatValue(),mark.y.floatValue());
        status = figure.checkMark(tmpMark);
        AnswerClass answer = new AnswerClass();
        answer.status = status;
        answer.hash = mark.hash;

        synchronized (out) {
            try {
                out.reset();
                out.writeObject(answer);
            } catch (IOException e){

            }
        }
    }
}
