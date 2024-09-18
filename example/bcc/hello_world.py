'''
Author: 0xSchnappi 952768182@qq.com
Date: 2024-09-18 17:25:45
LastEditors: 0xSchnappi 952768182@qq.com
LastEditTime: 2024-09-18 17:26:50
FilePath: /mini-falco/example/python/hello_world.py
Description: BCC框架下的BPF程序

Copyright (c) 2024 by github.com/0xSchnappi, All Rights Reserved. 
'''
#!/usr/bin/python
# Copyright (c) PLUMgrid, Inc.
# Licensed under the Apache License, Version 2.0 (the "License")

# run in project examples directory with:
# sudo ./hello_world.py"
# see trace_fields.py for a longer example

from bcc import BPF

# This may not work for 4.17 on x64, you need replace kprobe__sys_clone with kprobe____x64_sys_clone
BPF(text='int kprobe__sys_clone(void *ctx) { bpf_trace_printk("Hello, World!\\n"); return 0; }').trace_print()