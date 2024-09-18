/*
 * @Author: 0xSchnappi 952768182@qq.com
 * @Date: 2024-09-18 09:49:35
 * @LastEditors: 0xSchnappi 952768182@qq.com
 * @LastEditTime: 2024-09-18 16:12:50
 * @FilePath: /mini-falco/example/hello_world/bpf_program.c
 * @Description: 第一个bpf程序
 *
 * Copyright (c) 2024 by github.com/0xSchnappi, All Rights Reserved.
 */
#include <linux/bpf.h>
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_tracing.h>


/**
 * __attribute__ 定义函数的属性
 * section("tracepoint/syscalls/sys_enter_execve")：
 * 指定函数位于特定节中，将函数bpf_prog放在sys_enter_execve
 * https://gcc.gnu.org/onlinedocs/gcc-14.2.0/gcc/Common-Function-Attributes.html
 */
#define SEC(NAME) __attribute__((section(NAME), used))

SEC("tracepoint/syscalls/sys_enter_execve")
int bpf_prog(void *ctx) {
  char msg[] = "Hello, BPF World!";

  bpf_trace_printk(msg, sizeof(msg));
  return 0;
}

char _listense[] SEC("license") = "GPL";
