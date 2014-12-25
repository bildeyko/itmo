package com.bildeyko.views.tools;

import com.bildeyko.Mark;

import java.awt.*;

/**
 * Created by ASUS on 17.12.2014.
 */
public class MarkRunnable implements Runnable {
    private Mark mark;
    private Component component;
    public static int DELAY = 40;

    public MarkRunnable(Mark aMark, Component aComponent)
    {
        mark = aMark;
        component = aComponent;
    }

    public void run()
    {
        try {
            while(!Thread.interrupted()){
                mark.updateSize();
                component.repaint();
                Thread.sleep(DELAY);
            }
        }
        catch (InterruptedException e)
        {
        }
    }
}
