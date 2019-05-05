package com.mycompany.app;

import java.util.List;
import java.io.Serializable;
import java.util.HashMap;
import java.util.ArrayList;
import java.util.Arrays;

public class LargestSetImpl1 implements Serializable {

    public Integer[] eff;
    public Integer[] eid;

    public LargestSetImpl1(Integer max_element){
        this.eff = new Integer[max_element];
        this.eid = new Integer[max_element];
        Arrays.fill(this.eid, -1);
    }
}
