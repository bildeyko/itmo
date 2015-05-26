package lab9;

import com.sun.org.apache.xpath.internal.operations.Bool;

import javax.faces.bean.ManagedBean;
import javax.faces.bean.RequestScoped;
import java.io.Serializable;

/**
 * Created by ASUS on 04.11.2014.
 */
@ManagedBean(name = "mark", eager = true)
public class Mark implements Serializable {
    private Float x;
    private Float y;
    private Float r;
    private Boolean status;

    public Mark(Float x, Float y, Float r) {
        this.x = x;
        this.y = y;
        this.r = r;
    }

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
}
