/*
 * @Author: 0xSchnappi 952768182@qq.com
 * @Date: 2024-09-18 17:52:44
 * @LastEditors: 0xSchnappi 952768182@qq.com
 * @LastEditTime: 2024-09-18 18:11:50
 * @FilePath: /mini-falco/example/eunomia-bpf/02-kprobe-unlink/kprobe-link.c
 * @Description: unlikely监控
 *
 * Copyright (c) 2024 by github.com/0xSchnappi, All Rights Reserved.
 */
#include "vmlinux.h"
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_tracing.h>
#include <bpf/bpf_core_read.h>

char LICENSE[] SEC("license") = "Dual BSD/GPL";

SEC("kprobe/do_unlinkat")
int BPF_KPROBE(do_unlinkat, int dfd, struct filename *name)
{
    pid_t pid;
    const char *filename;

    pid = bpf_get_current_pid_tgid() >> 32;
    filename = BPF_CORE_READ(name, name);
    bpf_printk("KPROBE ENTRY pid = %d, filename = %s\n", pid, filename);
    return 0;
}

SEC("kretprobe/do_unlinkat")
int BPF_KRETPROBE(do_unlinkat_exit, long ret)
{
    pid_t pid;

    pid = bpf_get_current_pid_tgid() >> 32;
    bpf_printk("KPORBE EXIT: pid = %d, ret = %ld\n", pid, ret);
    return 0;
}
