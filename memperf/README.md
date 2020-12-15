# Memory Performance Testing

## 1. 介绍

这是一个运行在 RT-Thread 上的内存性能测试软件包，用于对 ARM CPU 的 内存性能评估，可适用于如下场景：

- 评估不同类型内存的读写性能
- 对于带有 cache 的 CPU，可用于评估 cache 性能

非常欢迎小伙伴们在运行完测试程序后，将相关测试结果 PR 到 [测试示例](#测试示例) 中以供他人参考。

### 1.1 目录结构

| 名称 | 说明 |
| ---- | ---- |
| inc  | 头文件目录 |
| src  | 源代码目录 |

### 1.2 许可证

`MemoryPerf` 软件包遵循 MIT 许可，详见 `LICENSE` 文件。

### 1.3 依赖

具有良好的移植性，无操作系统依赖。

## 2. 下载方式

使用 `MemoryPerf package` 需要在 RT-Thread 的包管理器中选择它，具体路径如下：

```
RT-Thread online packages
    tools packages --->
        [*] MemoryPerf: Memory Performance Testing for ARM CPU.
```

然后让 RT-Thread 的包管理器自动更新，或者使用 `pkgs --update` 命令更新包到 BSP 中。

## 3. 使用方法

- 在 `msh` 中运行  `<memory_perf 0x10100000 0x100000>` 命令

## 4. 注意事项

- 检查内存测试地址与长度是否设置正确
- 测试内存性能时推荐对比打开 cache 与 关闭 cache 的测试结果

## 5. 联系方式

* 维护：我夏了夏天 （SummerGift）
* 主页：https://github.com/SummerLife

## 测试示例

### 6.1 示例一

测试环境 `zynq7045 Cortex-A9 800M SDRAM uncached GCC -O3` ：

```shell
msh />memory_perf 0x10100000 0x100000
Memory performance testing start...
address: 0x10100000, length: 0x100000
Data length : 209 MB.
--------------------------------------
8-bit write speed test begin.
Spend time : 7.480000 s.
8-bit write speed: 28.036793 M/s.
8-bit read speed test begin.
Spend time : 5.380000 s.
8-bit Read speed: 38.980518 M/s.
--------------------------------------
16-bit write speed test begin.
Spend time : 3.740000 s.
16-bit write speed: 56.073586 M/s.
16-bit read speed test begin.
Spend time : 2.690000 s.
16-bit Read speed: 77.961037 M/s.
--------------------------------------
32-bit write speed test begin.
Spend time : 1.870000 s.
32-bit Write speed: 112.147171 M/s.
32-bit read speed test begin.
Spend time : 1.350000 s.
32-bit Read speed: 155.344589 M/s.
Memory performance completed.
```

### 6.2 示例二

测试环境  `zynq7045 Cortex-A9 800M SDRAM cached GCC -O3` ：

```shell
msh />memory_perf 0x10100000 0x100000 # Testing with cache
Memory performance testing start...
address: 0x10100000, length: 0x100000
Data length : 209 MB.
--------------------------------------
8-bit write speed test begin.
Spend time : 0.290000 s.
8-bit write speed: 723.155884 M/s.    # Achieve the best write performance
8-bit read speed test begin.
Spend time : 0.490000 s.
8-bit Read speed: 427.990204 M/s.
--------------------------------------
16-bit write speed test begin.
Spend time : 0.290000 s.
16-bit write speed: 723.155884 M/s.   # Achieve the best write performance
16-bit read speed test begin.
Spend time : 0.410000 s.
16-bit Read speed: 511.500488 M/s.
--------------------------------------
32-bit write speed test begin.
Spend time : 0.290000 s.
32-bit Write speed: 723.155884 M/s.   # Achieve the best write performance
32-bit read speed test begin.
Spend time : 0.370000 s.
32-bit Read speed: 566.797852 M/s.
Memory performance completed.
```

### 6.3 示例三

测试环境  `stm32f407-atk-explorer Cortex-M4 168M SRAM uncached GCC -O3` ：

```shell
msh >memory_perf 0x20010000 0x10000
Memory performance testing start...
address: 0x20010000, length: 0x10000, iterations: 200
Data length : 13 MB.
--------------------------------------
8-bit write speed test begin.
Spend time : 0.139000 s.
8-bit write speed: 94.296402 M/s.
8-bit read speed test begin.
Spend time : 0.361000 s.
8-bit Read speed: 36.308033 M/s.
--------------------------------------
16-bit write speed test begin.
Spend time : 0.070000 s.
16-bit write speed: 187.245712 M/s.
16-bit read speed test begin.
Spend time : 0.180000 s.
16-bit Read speed: 72.817780 M/s.
--------------------------------------
32-bit write speed test begin.
Spend time : 0.035000 s.
32-bit Write speed: 374.491425 M/s.
32-bit read speed test begin.
Spend time : 0.090000 s.
32-bit Read speed: 145.635559 M/s.
Memory performance completed.
```

### 6.4 示例四

测试环境  `stm32f407-atk-explorer Cortex-M4 168M SRAM uncached ARM(AC6) -O3` ：

```shell
msh >memory_perf 0x20010000 0x10000
Memory performance testing start...
address: 20010000, length: 0x10000, iterations: 200
Data length : 13 MB.
--------------------------------------
8-bit write speed test begin.
Spend time : 0.094000 s.
8-bit write speed: 139.438309 M/s.
8-bit read speed test begin.
Spend time : 0.268000 s.
8-bit Read speed: 48.907459 M/s.
--------------------------------------
16-bit write speed test begin.
Spend time : 0.047000 s.
16-bit write speed: 278.876617 M/s.
16-bit read speed test begin.
Spend time : 0.134000 s.
16-bit Read speed: 97.814919 M/s.
--------------------------------------
32-bit write speed test begin.
Spend time : 0.023000 s.
32-bit Write speed: 569.878296 M/s.
32-bit read speed test begin.
Spend time : 0.068000 s.
32-bit Read speed: 192.752930 M/s.
Memory performance completed.
```

### 6.5 示例五

测试环境  `stm32l475-atk-Pandora Cortex-M4 80M SRAM uncached GCC -O3` ：

```shell
msh >memory_perf 0x20008000 0xa000
Memory performance testing start...
address: 0x20008000, length: 0xa000, iterations: 200
Data length : 8 MB.
--------------------------------------
8-bit write speed test begin.
Spend time : 0.180000 s.
8-bit write speed: 45.511108 M/s.
8-bit read speed test begin.
Spend time : 0.449000 s.
8-bit Read speed: 18.244987 M/s.
--------------------------------------
16-bit write speed test begin.
Spend time : 0.090000 s.
16-bit write speed: 91.022217 M/s.
16-bit read speed test begin.
Spend time : 0.225000 s.
16-bit Read speed: 36.408890 M/s.
--------------------------------------
32-bit write speed test begin.
Spend time : 0.045000 s.
32-bit Write speed: 182.044434 M/s.
32-bit read speed test begin.
Spend time : 0.113000 s.
32-bit Read speed: 72.495575 M/s.
Memory performance completed.
```

