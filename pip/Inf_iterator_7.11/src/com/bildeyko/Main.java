package com.bildeyko;

/**
 * Created by ASUS on 07.11.2014.
 */
public class Main {

    public static void main(String[] args) {
        InfClass<Integer> temp = new InfClass<Integer>();
        for(Integer o: temp) {
             System.out.print("Hello world!\n");
        }
    }
}
