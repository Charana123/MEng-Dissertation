Spark allows for caching of compressed DataFrames, spark configuration allows disabling DataFrame column compression and controlling the batch-size i.e. rows of DataFrame (care must be taken to avoid "Out Of Memory" exceptions".
Each RDD/Dataset transformation is re-computed for each reduction performed. The transformation can be cached to speed computation. e.g.
JavaRDD<String> lines = sc.textFile("data.txt");.
JavaRDD<Integer> lineLengths = lines.map(s -> s.length());
lineLengths.persist(StorageLevel.MEMORY_ONLY());
int totalLength = lineLengths.reduce((a, b) -> a + b);
int maxLength = lineLengths.reduce((a, b) -> if a > b ? a : b);
Caching lineLengths speeds up the later maxLength computation.
Spark’s storage levels are meant to provide different trade-offs between memory usage and CPU efficiency. We recommend going through the following process to select one:
- If your RDDs fit comfortably with the default storage level (MEMORY_ONLY), leave them that way. This is the most CPU-efficient option, allowing operations on the RDDs to run as fast as possible.
- If not, try using MEMORY_ONLY_SER and selecting a fast serialization library to make the objects much more space-efficient, but still reasonably fast to access. (Java and Scala)
- Don’t spill to disk unless the functions that computed your datasets are expensive, or they filter a large amount of the data. Otherwise, recomputing a partition may be as fast as reading it from disk.

Spark does not define or guarantee the behavior of mutations to objects referenced from outside of closures.
Accumulators in Spark are used specifically to provide a mechanism for safely updating a variable when execution is split up across worker nodes in a cluster.
Similarly writing to standard output with the common idiom - rdd.foreach(println), fails to write to the standard output of the node of the driver program if executed in cluster mode.
We must collect the distributed dataset on the driver node - rdd.collect().foreach(println) or  rdd.take(100).foreach(println) (to avoid out of memory exceptions).
Spark does define two types of Shared Variables
Broadcast Variables - Used to cache a read-only variable on machines of the cluster. By default spark automatically distributes and caches common data in serialised form needed by transformations/actions. Therefore broadcast variables are only of benefit when they are used between different tasks or stored in a deserialized form.
Accumulators -

Each distributed dataset is divided into blocks that are allocated to partitions. By default Hadoop uses 128MB blocks and creates one partition per block.
By default the number of partitions is the number of all available cores.
In general, smaller/more numerous partitions allow work to be distributed among more workers, but larger/fewer partitions allow work to be done in larger chunks, which may result in the work getting done more quickly as long as all workers are kept busy, due to reduced overhead.
So if you have a cluster with 50 cores, you want your RDDs to at least have 50 partitions (and probably 2-3x times that). In general, we recommend 2-3 tasks per CPU core in your cluster.
The number of partitions should be atleast the number of executors.
Some operations, e.g. map, flatMap, filter, don’t preserve partitioning.


Shuffling is a re-distribution of data across partitions s.t local transformations and actions have their required data to perform the computation.
Operations that invoke a shuffle operation include -
- repartition operations - RDD.repartition, RDD.coalesce
    - increases or decreases the number of partitions across which blocks of the dataset
        are distributed therefore most probably altering the default block size.
    - Gives automony over number of workers
- 'ByKey operations - RDD.groupByKey and RDD.reduceByKey
- join operation - cogroup and join
Shuffling invoked by operation (e.g. groupByKey) creates a large number of intermediate files corresponding to the RDD, these can be persisted in cache to speed re-computation or failed
computation by calling 'persist' on the resulting RDD.

The Spark SQL Engine leveraged through SQL or the Dataset API provides a method of Structured batch/streaming processing. It performs optimization based on the structure of the data and operation being performed.







































