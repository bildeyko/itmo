package test;

import com.bildeyko.Lab3;
import org.junit.Test;

import static org.junit.Assert.*;

public class Lab3Test {

    @Test
    public void testCheckInputR(){
        double r = Lab3.checkInputR("0.05");
        assertEquals(r, 0.05, 0.001);
    }

    @Test(expected = NumberFormatException.class)
    public void testCheckInputR_exeption(){
        Lab3.checkInputR("abc");
    }
}