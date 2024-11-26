# second

A character device named second that logs jiffies every second and returns elapsed seconds while reading.

编写一个字符设备 second（即“秒”）的驱动。它被打开的时候初始化一个定时器，并添加到内核定时器链表中，每秒在内核日志中输出一次当前的 jiffies，读取该字符设备的时候返回当前定时器的秒数。

注意，second 的需求和设计与之前的 globalmem 完全不同，globalmem 开辟了一块数组用于存储数据，在这块数组中顺序读和写。TODO

