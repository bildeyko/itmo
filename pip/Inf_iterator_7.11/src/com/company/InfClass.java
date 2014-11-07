package com.company;

import java.util.Iterator;

/**
 * Created by ASUS on 07.11.2014.
 */
public class InfClass<E> implements Iterable<E> {

    public Iterator<E> iterator() {
        return new InfIterator<E>();
    }
}
