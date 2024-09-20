/*
 * @Author: 0xSchnappi 952768182@qq.com
 * @Date: 2024-09-19 09:27:44
 * @LastEditors: 0xSchnappi 952768182@qq.com
 * @LastEditTime: 2024-09-20 09:11:39
 * @FilePath: /mini-falco/example/eunomia-bpf/03-fentry-unlink/fentry-link.c
 * @Description: fentry和fexit探针跟踪
 *
 * Copyright (c) 2024 by github.com/0xSchnappi, All Rights Reserved.
 */

#include "vmlinux.h"
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_tracing.h>

char LICENSE[] SEC("license") = "Dual BSD/GPL";

SEC("fentry/do_unlinkat")
int BPF_PROG(do_unlinkat, int dfd, struct filename *name) {
  pid_t pid;

  pid = bpf_get_current_pid_tgid() >> 32;
  bpf_printk("fentry: pid = %d, filename = %s\n", pid, name->name);
  return 0;
}

SEC("fexit/do_unlinkat")
int BPF_PROG(do_unlinkat_exit, int dfd, struct filename *name, long ret) {
  pid_t pid;

  pid = bpf_get_current_pid_tgid() >> 32;
  bpf_printk("fexit: pid = %d, filename = %s, ret = %ld\n", pid, name->name,
             ret);
  return 0;
}