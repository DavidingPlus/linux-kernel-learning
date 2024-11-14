# globalfifo

A Simple globalfifo Module.

Fork from [globalmem](https://github.com/DavidingPlus/linux-kernel-learning/tree/globalmem), with more features.

我们给 globalmem 增加这样的约束：把 globalmem 中的全局内存变成一个 FIFO，只有当 FIFO 中有数据的时候（即有进程把数据写到这个 FIFO 而且没有被读进程读空），读进程才能把数据读出，而且读取后的数据会从 globalmem 的全局内存中被拿掉。只有当 FIFO 不是满的时（即还有一些空间未被写，或写满后被读进程从这个 FIFO 中读出了数据），写进程才能往这个 FIFO 中写入数据。

因此，将 globalmem 重命名为 globalfifo。在 globalfifo 中，读 FIFO 将唤醒写 FIFO 的进程（如果之前 FIFO 正好是满的），而写 FIFO 也将唤醒读 FIFO 的进程（如果之前 FIFO 正好是空的）。

