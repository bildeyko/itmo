package com.bildeyko;

import java.io.Serializable;

/**
 * Created by ASUS on 23.12.2014.
 */
public class MarkClient implements Serializable {
    public Double x;
    public Double y;
    public Double r;
    public Integer hash;

    @Override
    public String toString() {
        return "MarkClient{" +
                "x=" + x +
                ", y=" + y +
                ", r=" + r +
                ", hash=" + hash +
                '}';
    }
}
