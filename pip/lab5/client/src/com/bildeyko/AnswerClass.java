package com.bildeyko;

import java.io.Serializable;

/**
 * Created by ASUS on 24.12.2014.
 */
public class AnswerClass implements Serializable {
    public Integer status;
    public Integer hash;

    @Override
    public String toString() {
        return "AnswerClass{" +
                "status=" + status +
                ", hash=" + hash +
                '}';
    }
}
