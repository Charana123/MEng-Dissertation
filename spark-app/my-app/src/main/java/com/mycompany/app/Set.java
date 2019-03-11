package com.mycompany.app;

import java.util.List;
import java.io.Serializable;


public class Set implements Serializable{

    public List<Integer> elements;
    public int i;

    public Set(List<Integer> elements, int i){
        this.elements = elements;
        this.i = i;
    }
}
