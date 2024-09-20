# fentry(Function Entry)和fexit(Function Exit)探针

- fexit和kretprobe程序最大的区别在于，fexit程序可以访问函数的输入参数和返回值，而kretprobe只能访问返回值。