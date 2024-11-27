# second

A character device named second that logs jiffies every second and returns elapsed seconds while reading.

编写一个字符设备 second（即“秒”）的驱动。它被打开的时候初始化一个定时器，并添加到内核定时器链表中，每秒在内核日志中输出一次当前的 jiffies，读取该字符设备的时候返回当前定时器的秒数。

注意，second 的需求和设计与之前的 globalmem 完全不同。globalmem 开辟了一块数组用于存储数据，在这块数组的内存中进行顺序读和写。而 second 的读仅仅只返回自身维护的一个原子变量的值，压根没有读然后修改偏移量的机制。cat 命令的本质是循环读取文件，直到读到 EOF，在 read() 的语境下就是返回 0，而这 second 显然是做不到的。因此用 cat 做测试是行不通的，使用 cat 只会导致死循环，只能自己写用户层的测试代码。特此说明。

