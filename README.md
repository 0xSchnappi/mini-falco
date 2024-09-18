# mini-falco

## 依赖

```shell
sudo apt install -y clang llvm libbpf-dev
```

## 项目本地运行

```shell
cd example/hello_world
make run        # 编译并运行程序
make clean      # 删除生成文件
```

## eunomia-bpf

使用[eunomia-bpf](https://github.com/eunomia-bpf/eunomia-bpf)框架开发的路径在example/eunomia-bpf文件夹下

- ecc: 编译bpf程序

- ecli: 运行bpf程序

## BCC

使用[BCC](https://github.com/iovisor/bcc/tree/master)框架开发的路径在example/bcc

## Rust ebpf

[aya](https://www.ebpf.top/post/ebpf_rust_aya/)
[开发模板](https://github.com/eunomia-bpf/libbpf-rs-starter-template)

## 参考文献

[BPF开发:从HelloWorld开始](https://matrixorigin.cn/posts/bpf-development-from-scratch)
[eBPF文档](https://ebpf-docs.dylanreimerink.nl/)
[BPF学习教程](https://github.com/eunomia-bpf/bpf-developer-tutorial/tree/main)

