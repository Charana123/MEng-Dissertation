package com.mycompany.app;

import org.apache.spark.api.java.function.FlatMapFunction;
import org.apache.spark.sql.*;
import org.apache.spark.sql.streaming.StreamingQuery;
import java.util.Arrays;
import java.util.Iterator;
import java.util.ArrayList;

public class StructuredStreamingApp {

    public static void main(String[] args) {

        ArrayList<String> strings;
        SparkSession spark = SparkSession
			.builder()
			.appName("JavaStructuredNetworkWordCount")
			.getOrCreate();

		Dataset<String> lines = spark
			.readStream()
			.textFile("/home/charana/Desktop/spark-2.4.0-bin-without-hadoop/README");

		Dataset<String> words = lines.
            flatMap((FlatMapFunction<String, String>) line -> Arrays.asList(line.split(" ")).iterator(), Encoders.STRING());

        // Generate running word count
        Dataset<Row> wordCounts = words.groupBy("value").count();

        StreamingQuery query = wordCounts.writeStream()
            .outputMode("complete")
            .format("console")
            .start();

        try {
            query.awaitTermination();
        } catch(Exception e) {
            e.printStackTrace();
            System.exit(0);
        }
    }
}
