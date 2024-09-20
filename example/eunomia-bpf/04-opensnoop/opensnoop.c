/*
 * @Author: 0xSchnappi 952768182@qq.com
 * @Date: 2024-09-20 10:18:58
 * @LastEditors: 0xSchnappi 952768182@qq.com
 * @LastEditTime: 2024-09-20 11:19:11
 * @FilePath: /mini-falco/example/eunomia-bpf/04-opensnoop/opensnoop.c
 * @Description: 监控进程打开文件的系统调用
 *
 * Copyright (c) 2024 by github.com/0xSchnappi, All Rights Reserved.
 */
#include "vmlinux.h"
#include <bpf/bpf_helpers.h>

/**
 * const 一旦初始化就不能修改
 * volatile 该变量的值可能在执行国过程中被其他因素修改，比如异步事件(如硬件中断)
 * 或多线程环境中的其他线程。强制每次访问时都从内存中读取值，而不是使用寄存器中的缓存
 *
 * 结合使用是防止多线程、系统中断、硬件组件等的修改
 */

/**
 * 作用：全局变量在 eBPF 程序中充当一种数据共享机制，它们允许用户态程序与 eBPF
 * 程序之间进行数据交互。 这在过滤特定条件或修改 eBPF 程序行为时非常有用。
 *
 * 使用全局变量的原理是，全局变量在 eBPF 程序的数据段（data
 * section）中定义并存储。 当 eBPF
 * 程序加载到内核并执行时，这些全局变量会保持在内核中，可以通过 BPF
 * 系统调用进行访问。 用户态程序可以使用 BPF 系统调用中的某些特性，如
 * bpf_obj_get_info_by_fd 和 bpf_obj_get_info， 获取 eBPF
 * 对象的信息，包括全局变量的位置和值。
 */
/// #description "Process ID to trace"
const volatile int pid_target = 0;

SEC("tracepoint/syscalls/sys_enter_openat")
int tracepoint__syscalls__sys_enter_openat(
    struct trace_event_raw_sys_enter *ctx) {
  u64 id = bpf_get_current_pid_tgid();
  pid_t pid = id >> 32;

  if (pid_target && pid_target != pid) {
    return false;
  }
  // Use bpf_printk to print the process information
  bpf_printk("Process ID: %d enter sys openat\n", pid);
  return 0;
}

/// "Trace open family syscalls."
char LICENSE[] SEC("license") = "GPL";