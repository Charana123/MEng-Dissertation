package com.mycompany.app;

import org.apache.spark.sql.Encoders;
import org.apache.spark.sql.SparkSession;
import org.apache.spark.sql.Dataset;
import java.util.Arrays;
import java.lang.String;
import org.apache.spark.api.java.function.MapFunction;
import java.util.ArrayList;
import org.apache.spark.sql.Encoder;
import java.util.List;
import java.util.stream.Collectors;

public class LargestSet {
  // public static void main(String[] args) {
  //   SparkSession spark = SparkSession.builder().appName("Largest Set").getOrCreate();
  //   Encoder<Set> setEncoder = Encoders.bean(Set.class);
  //   Dataset<String> lines = spark.read().textFile("/home/charana/Desktop/spark-2.4.0-bin-without-hadoop/README.md");
  //   Dataset<Set> sets = lines.map((MapFunction<String, Set>) (String line) -> {
  //           List<String> tokens = Arrays.asList(line.trim().split(" "));
  //           List<Integer> elements = tokens.stream().map(Integer::parseInt).collect(Collectors.toList());
  //           Integer i = elements.stream().reduce(0, (Integer i1, Integer i2) -> i1 + i2);
  //           Set s = new Set(elements, i);
  //           return s;
  //       },
  //       setEncoder
  //   );
  // }
}





















