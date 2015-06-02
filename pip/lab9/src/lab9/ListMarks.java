package lab9;

import javax.faces.bean.ManagedBean;
import javax.faces.bean.SessionScoped;
import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;

/**
 * Created by ASUS on 26.05.2015.
 */
@ManagedBean(name = "listMarks", eager = true)
@SessionScoped
public class ListMarks implements Serializable {
    private List<Mark> marks;

    public ListMarks(){
        marks = new ArrayList<Mark>();
    }

    public void addMark(Mark mark) {
        marks.add(mark);
    }

    public List<Mark> getMarks() {
        return  marks;
    }
}
