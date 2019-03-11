package com.mycompany.app;

import java.util.List;
import java.io.Serializable;
import java.util.HashMap;
import java.util.ArrayList;

public class LargestSetImpl implements Serializable {

    public HashMap<Integer, Integer> eff;
    public HashMap<Integer, Integer> eid;

    public LargestSetImpl(){
        this.eff = new HashMap<>();
        this.eid = new HashMap<>();
    }
}
