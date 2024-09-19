**kprobes 的特点与使用限制：**

1. kprobes 允许在同一个被探测位置注册多个 kprobe，但是目前 jprobe 却不可以；同时也不允许以其他的 jprobe 回调函数和 kprobe 的 `post_handler` 回调函数作为被探测点。
2. 一般情况下，可以探测内核中的任何函数，包括中断处理函数。不过在 kernel/kprobes.c 和 arch/*/kernel/kprobes.c 程序中用于实现 kprobes 自身的函数是不允许被探测的，另外还有`do_page_fault` 和 `notifier_call_chain`；
3. 如果以一个内联函数为探测点，则 kprobes 可能无法保证对该函数的所有实例都注册探测点。由于 gcc 可能会自动将某些函数优化为内联函数，因此可能无法达到用户预期的探测效果；
4. 一个探测点的回调函数可能会修改被探测函数的运行上下文，例如通过修改内核的数据结构或者保存与`struct pt_regs`结构体中的触发探测器之前寄存器信息。因此 kprobes 可以被用来安装 bug 修复代码或者注入故障测试代码；
5. kprobes 会避免在处理探测点函数时再次调用另一个探测点的回调函数，例如在`printk()`函数上注册了探测点，而在它的回调函数中可能会再次调用`printk`函数，此时将不再触发`printk`探测点的回调，仅仅是增加了`kprobe`结构体中`nmissed`字段的数值；
6. 在 kprobes 的注册和注销过程中不会使用 mutex 锁和动态的申请内存；
7. kprobes 回调函数的运行期间是关闭内核抢占的，同时也可能在关闭中断的情况下执行，具体要视CPU架构而定。因此不论在何种情况下，在回调函数中不要调用会放弃 CPU 的函数（如信号量、mutex 锁等）；
8. kretprobe 通过替换返回地址为预定义的 trampoline 的地址来实现，因此栈回溯和 gcc 内嵌函数`__builtin_return_address()`调用将返回 trampoline 的地址而不是真正的被探测函数的返回地址；
9. 如果一个函数的调用次数和返回次数不相等，则在类似这样的函数上注册 kretprobe 将可能不会达到预期的效果，例如`do_exit()`函数会存在问题，而`do_execve()`函数和`do_fork()`函数不会；
10. 当在进入和退出一个函数时，如果 CPU 运行在非当前任务所有的栈上，那么往该函数上注册 kretprobe 可能会导致不可预料的后果，因此，kprobes 不支持在 X86_64 的结构下为`__switch_to()`函数注册 kretprobe，将直接返回`-EINVAL`。
