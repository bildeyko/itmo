package test;

import com.bildeyko.Figure;
import com.bildeyko.Mark;

import static org.junit.Assert.*;

public class FigureTest {

    Figure testFigure;
    @org.junit.Before
    public void setUp() throws Exception {
        testFigure = new Figure(8);
    }

    @org.junit.Test
    public void testCheckMark_1quad(){
        boolean res;
        Mark mark = new Mark(0,0);
        res = testFigure.checkMark(mark);
        assertTrue("Mark must be inside of region.",res);

        mark = new Mark(1,1);
        res = testFigure.checkMark(mark);
        assertTrue("Mark must be inside of region.",res);

        mark = new Mark(3,1);
        res = testFigure.checkMark(mark);
        assertTrue("Mark must lie on the boundary.",res);

        mark = new Mark(5,5);
        res = testFigure.checkMark(mark);
        assertFalse("Mark must be outside of region.",res);
    }

    @org.junit.Test
    public void testCheckMark_2quad(){
        boolean res;
        Mark mark = new Mark(-1,1);
        res = testFigure.checkMark(mark);
        assertFalse("Mark must be outside of region.",res);
    }

    @org.junit.Test
    public void testCheckMark_3quad(){
        boolean res;
        Mark mark = new Mark(-2,-2);
        res = testFigure.checkMark(mark);
        assertTrue("Mark must be inside of region.",res);

        mark = new Mark(-2,-3.4641f);
        res = testFigure.checkMark(mark);
        assertTrue("Mark must lie on the boundary.",res);

        mark = new Mark(-10,-10);
        res = testFigure.checkMark(mark);
        assertFalse("Mark must be outside of region.",res);
    }

    @org.junit.Test
    public void testCheckMark_4quad(){
        boolean res;
        Mark mark = new Mark(2,2);
        res = testFigure.checkMark(mark);
        assertTrue("Mark must be inside of region.",res);

        mark = new Mark(8,-4);
        res = testFigure.checkMark(mark);
        assertTrue("Mark must lie on the boundary.",res);

        mark = new Mark(10,-5);
        res = testFigure.checkMark(mark);
        assertFalse("Mark must be outside of region.",res);
    }
}