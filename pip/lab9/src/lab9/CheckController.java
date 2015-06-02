package lab9;

import javax.faces.bean.ManagedBean;
import javax.faces.bean.ManagedProperty;
import javax.faces.bean.RequestScoped;
import java.io.Serializable;

/**
 * Created by ASUS on 25.05.2015.
 */
@ManagedBean(name = "checkController", eager = true)
@RequestScoped
public class CheckController implements Serializable {
    private Float x = 0.0f;
    private Float y = 0.0f;
    private Float r = 1.0f;
    private Boolean status;

    @ManagedProperty("#{listMarks}")
    private ListMarks marks;

    public void setX(Float x) {
        this.x = x;
    }
    public Float getX() {
        return this.x;
    }
    public void setY(Float y) {
        this.y = y;
    }
    public Float getY() {
        return this.y;
    }
    public void setR(Float r) {
        this.r = r;
    }
    public Float getR() {
        return this.r;
    }
    public void setStatus(Boolean status) {
        this.status = status;
    }
    public Boolean getStatus() {
        return this.status;
    }

    public void setMarks(ListMarks marks) {
        this.marks = marks;
    }

    public String check() {

        Mark mark = new Mark(this.x, this.y, this.r);
        this.status = checkMark(mark);
        mark.setStatus(this.status);
        marks.addMark(mark);
        System.out.println(this.x);
        System.out.println(this.y);
        System.out.println(this.r);
        return "check_point";
    }

    public Boolean checkCanvas() {
        Mark mark = new Mark(this.x, this.y, this.r);
        this.status = checkMark(mark);
        mark.setStatus(this.status);
        marks.addMark(mark);
        return this.status;
    }

    private boolean checkMark(Mark mark) {
        if(mark.getX() >= 0) {
            if(mark.getY() >= 0 && mark.getY() <= (mark.getR() - 2*mark.getX())) {
                return true;
            }
            if(mark.getY() <= 0 && mark.getY() >= -mark.getR() && mark.getX() <= mark.getR()/2) {
                return true;
            }
        } else {
            double radius = Math.sqrt(Math.pow(getX(),2)+Math.pow(mark.getY(),2));
            if(mark.getY() <= 0 && radius <= mark.getR()/2) {
                return true;
            }
        }
        return false;
    }

    public Boolean fixR() {
        return true;
    }
}
