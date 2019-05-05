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
import java.util.Collections;

public class LargestSetRDD1 {
  public static void main(String[] args) {
    SparkConf conf = new SparkConf().setAppName("LargestSetRDD");
    JavaSparkContext sc = new JavaSparkContext(conf);
    JavaRDD<String> lines = sc.textFile("/mnt/storage/home/an15739/FIMI/webdocs.dat");
    JavaRDD<Set> sets = lines.map((String line) -> {
        List<String> tokens = Arrays.asList(line.trim().split(" "));
        List<Integer> elements = tokens.stream().map(Integer::parseInt).collect(Collectors.toList());
        Integer i = elements.stream().reduce(0, (Integer i1, Integer i2) -> i1 + i2);
        Set s = new Set(elements, i);
        return s;
    });
    sets.cache();
    Integer max_element = sets.aggregate(0,
        (Integer max, Set s) -> {
            int max_of_set = Collections.max(s.elements);
            return max > max_of_set ? max : max_of_set;
        },
        (Integer max1, Integer max2) -> { return max1 > max2 ? max1 : max2; }
    );
    System.out.println("max_element: " + max_element);
    LargestSetImpl1 largest_set = sets.aggregate(new LargestSetImpl1(max_element + 1),
        (LargestSetImpl1 ls, Set s) -> {
            int eff = s.elements.size();
            for(int v : s.elements){
                if(ls.eid[v] == -1 || eff > ls.eff[v]) {
                    ls.eff[v] = eff;
                    ls.eid[v] = s.i;
                }
            }
            return ls;
        },
        (LargestSetImpl1 ls1, LargestSetImpl1 ls2) -> {
            for(int v = 0; v < max_element; v++){
				if(ls1.eid[v] == -1) continue;
				else {
					int v_eff = ls1.eff[v];
					if(ls2.eid[v] == -1 || v_eff > ls2.eff[v]) {
						ls2.eff[v] = v_eff;
						ls2.eid[v] = ls1.eid[v];
					}
				}
            }
            return ls2;
        }
    );
    HashSet<Integer> sol = new HashSet<>(Arrays.asList(largest_set.eid));
    System.out.println("solution size: " + sol.size());
  }
}










