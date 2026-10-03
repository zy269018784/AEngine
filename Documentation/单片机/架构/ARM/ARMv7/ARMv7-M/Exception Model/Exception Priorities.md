优先级是一个数字, 数字越低优先级越高.
Reset, NMI, HardFault优先级是固定的, 这3个异常的优先级比其他异常高.
软件可以设置其他异常的优先级.
软件可以设置的优先级从0开始.
异常的优先级数字相同, 那么异常数字小的优先级大.


Exception Priority Number 	Exception
-3 							Reset
-2							NMI
-1							HardFault

Priority Grouping:
    把优先级分为两部分: 组优先级 和 子优先级.
    Reset, NMI and HardFault 的组优先级固定为 -3, -2, -1, 不受优先级分组影响.
    
    
    



