Kanisha Shah
504-958-165

After-Action Report:


To implement multithreading, I first included pthread library and made changes
to the makefile to link it with the lpthread library. I saw that nested loop
inside the main function is used to print the pixels. I decided to put the nested loops
inside the thread function which pthread_create calls. The only argument to this
function was the thread number which can be used for printing pixels. All the variables 
that were used by by the nested for loop remained same during for each iteration.
So, I set all the varaibles global and they were assigned values inside the main.
Due to this I had to change const data types to data types.

Then, I made a for loop for pthread_create function. The for loop calls as many thread
functions as the argument passed for number of threads (nthreads). To keep the track
of all thread_id's, I made an array of pthread_t having nthreads elements  After calling
all the thread functions, we use a for loop calling all the pthread_join functions
to wait for them to complete their execution.

The logic used to print each pixel through pthread_function is as follows:
Every thread_function has a thread number passed to it. We start printing each
vertical column from that number and keep adding number of threads to it, to go
and print that vertical column as long as the width does not exceed the width limit.
For example: if the number of threads for the program is 6 and the thread number
is 4, the columns 4, 10, 16, 22, and so on would be printed.

After doing this, when I ran it, it did not print all the pixel correctly.
So, I started storing the print result into a 3-dimensional array:
scaled_color_all [131][131][3]. I printed all the results at the end using nested loops.

Other than this, there were some syntax errors while type_casting, calling functions
pthread_create, pthread_join and passing arguments to it.


Comparing the original version with the threaded version:

* Original Version:
time ./srt 1-test.ppm >1-test.ppm.tmp
real	1m10.485s
user	0m25.208s
sys	0m0.122s


* Threaded Version:
time ./srt 1-test.ppm >1-test.ppm.tmp
real	0m46.331s
user	0m46.325s
sys	0m0.002s

time ./srt 2-test.ppm >2-test.ppm.tmp
real	0m23.634s
user	0m46.748s
sys	0m0.002s

time ./srt 4-test.ppm >4-test.ppm.tmp
real	0m11.816s
user	0m46.662s
sys	0m0.003s

time ./srt 8-test.ppm >8-test.ppm.tmp

real	0m5.988s
user	0m46.399s
sys	0m0.003s


As we can see, the threaded version works faster than the original
and increasing the number of threads decreses real time execution.
Parallelism increases the performance of the program significantly.
Printing pixels with 8 threads only takes 5.998 seconds whereas the
original program took 1 minute and 10.485 seconds.
