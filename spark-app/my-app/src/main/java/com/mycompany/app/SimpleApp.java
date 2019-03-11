package com.mycompany.app;

import org.apache.spark.sql.SparkSession;
import org.apache.spark.sql.Dataset;
import org.apache.spark.api.java.function.FilterFunction;
import java.lang.String;

public class SimpleApp {
  public static void main(String[] args) {
    String filepath = "/home/charana/Desktop/data/kosarak.dat";
    SparkSession spark = SparkSession.builder().appName("Parse Inputs to Sets").getOrCreate();
    Dataset<String> dataset = spark.read().textFile(filepath).cache();

    long numAs = dataset.filter((FilterFunction<String>)s -> s.contains("a")).count();
    long numBs = dataset.filter((FilterFunction<String>)s -> s.contains("b")).count();

    System.out.println("Lines with a: " + numAs + ", lines with b: " + numBs);

    spark.stop();
  }
}
