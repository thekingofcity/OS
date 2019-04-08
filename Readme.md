# IPC(InterPlantery Communication)

[TOC]

## Usage

1. ```git pull```

2. ```make```

3. open one terminal and type ```./earth```

4. open another terminal and type ```./mars```

5. start your journey

## Example

> This example runs on WSL(Windows Subsystem on Linux), which may be slightly different from common environment.

![earth](lab1.earth.png)

![mars](lab1.mars.png)

|\\|Earth|Mars|
|:---:|:---:|:---:|
|t1|send 15213 to Mars|-|
|t2|-|read 15213 from Earth|
|t3|-|send 6033 to Earth|
|t4|read 6033 from Mars|-|
|t5|read empty from Mars<br>note that this is a non-block procedure|-|
|t6|-|read empty from Earth<br>note that this is a non-block procedure|
|t7|quit|-|
|t8|-|quit|

## Reference

### sbuf

#### What is sbuf

This is a simple buffer package from CSAPP(chap 12). Source code at [this page][1].

#### What have I done on it

Since this simple package is based on thread which is slightly different from process, I have to rewritten some part to adapt it to shared memory.

* Function ```sbuf_init``` calloc another chunck of memory as buffer which is already owned by process. So I just assign that part at the ```shmget```.

* I also wrote a non-block ```sbuf_remove``` which simply use ```sem_trywait``` to return as soon as possible.

### ```shmdata.h``` ```shmread.c``` ```shmwrite.c```

Blog and source code could be found at [this page][2].

This is really a great example to use shared memory.

There is another nice example [here][6].

### Makefile

Makefile is quite easy. Follow [this guide][4] and [this guide][5], you will be able to write your own.

However I do encounter a problem which need tab not spaces before segement. [More details here][3].

## Closing words

![msgget](lab1.msgget.png)

Since ```msgget``` is not implemented in WSL, I have no choice but to use other methods to get process known of messages. Then I recalled some part in CSAPP which indeed give me some insights(codes more technically). However when I almost finished this lab I found it is an inter-thread communication solution.

To solve that, I turn to shared memory example and I soon realized that it is the same with memory in thread.

## TL;DR

I managed to merge those two above into a complete message queue which use shared memory as buffer and semaphore as lock.

[1]: http://csapp.cs.cmu.edu/public/code.html

[2]: https://www.cnblogs.com/52php/p/5861372.html

[3]: https://blog.csdn.net/limanjihe/article/details/52231243

[4]: https://www.cnblogs.com/owlman/p/5514724.html

[5]: https://blog.csdn.net/yychuyu/article/details/79950414

[6]: https://www.cnblogs.com/52php/p/5861372.html