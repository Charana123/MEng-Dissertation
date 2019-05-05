package com.mycompany.app;

import org.apache.spark.api.java.JavaSparkContext;
import org.apache.spark.api.java.JavaRDD;
import org.apache.spark.SparkConf;
import org.apache.spark.rdd.RDD;
import java.lang.String;
import java.util.List;
import java.util.stream.Collectors;
import java.util.Arrays;
import java.util.Map;
import java.util.HashSet;
import java.util.ArrayList;
import java.lang.Integer;

public class LargestSetRDD {
  public static void main(String[] args) {
    SparkConf conf = new SparkConf().setAppName("LargestSetRDD");
    JavaSparkContext sc = new JavaSparkContext(conf);
    JavaRDD<String> lines = sc.textFile("/home/charana/Desktop/test/FIMI/webdocs.dat");
    JavaRDD<Set> sets = lines.map((String line) -> {
        List<String> tokens = Arrays.asList(line.trim().split(" "));
        List<Integer> elements = tokens.stream().map(Integer::parseInt).collect(Collectors.toList());
        Integer i = elements.stream().reduce(0, (Integer i1, Integer i2) -> i1 + i2);
        Set s = new Set(elements, i);
        return s;
    });
    LargestSetImpl largest_set = sets.aggregate(new LargestSetImpl(),
        (LargestSetImpl ls, Set s) -> {
            int eff = s.elements.size();
            for(int v : s.elements){
                if(!ls.eff.containsKey(v) || eff > ls.eff.get(v)) {
                    ls.eff.put(v, eff);
                    ls.eid.put(v, s.i);
                }
            }
            return ls;
        },
        (LargestSetImpl ls1, LargestSetImpl ls2) -> {
            for(Map.Entry<Integer, Integer> entry : ls1.eff.entrySet()){
                int v = entry.getKey();
                int v_eff = entry.getValue();
                if(!ls2.eff.containsKey(v) || v_eff > ls2.eff.get(v)) {
                    ls2.eff.put(v, v_eff);
                    ls2.eid.put(v, ls1.eid.get(v));
                }
            }
            return ls2;
        }
    );
    HashSet<Integer> values = new HashSet<>(largest_set.eid.values());
    System.out.println("solution size: " + values.size());
  }
}

















