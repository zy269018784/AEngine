| Bits | 描述 | 特权属性 | 典型用途 | Secure / Non-secure |
|------|------|----------|----------|---------------------|
| EL0 | unprivileged execution | Unprivileged | 用户态应用程序 | 可处于 Secure EL0 或 Non-secure EL0 |
| EL1 | privileged execution | Privileged | OS 内核，如 Linux、RTOS；Secure EL1 可运行 Trusted OS | 可处于 Secure EL1 或 Non-secure EL1 |
| EL2 | privileged execution | Privileged | Hypervisor，如 KVM、Xen | 通常仅 Non-secure EL2；Secure EL2 是可选扩展 |
| EL3 | privileged execution. Secure state 和 Non-secure state | Privileged | Secure Monitor / firmware，负责 Secure 与 Non-secure 切换 | 仅 Secure state，是安全状态切换的控制点 |