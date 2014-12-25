package com.bildeyko;

/**
 * Created by ASUS on 04.11.2014.
 */
public class Mark {
    public Float x;
    public Float y;
    private Integer rad;
    public Integer currentSize;
    private Integer startSize = 10;
    private Integer endSize = 20;
    private Integer dir = 1;
    private Integer count = 1;

    public Mark(Float x, Float y) {
        this.x = x;
        this.y = y;
    }

    public void setRadius(Integer radius) {
        rad = radius;
        currentSize = radius/startSize;
    }

    public void updateSize() {
        if(dir == 1) {
            currentSize = rad/(startSize+count);
            count ++;
            if(count==10) {
                count = 1;
                dir = 0;
            }
        }
        if(dir == 0) {
            currentSize = rad/(endSize-count);
            count ++;
            if(count==10) {
                count = 1;
                dir = 1;
            }
        }

    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        Mark mark = (Mark) o;

        if (x != null ? !x.equals(mark.x) : mark.x != null) return false;
        if (y != null ? !y.equals(mark.y) : mark.y != null) return false;

        return true;
    }

    @Override
    public int hashCode() {
        int result = x != null ? x.hashCode() : 0;
        result = 31 * result + (y != null ? y.hashCode() : 0);
        return result;
    }
}
