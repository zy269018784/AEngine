变量类型:
    Nullable 
    Non-nullable

Nullable变量默认初始化为null.
Non-nullable变量, 未初始化使用会报错， Error: Non-nullable variable must be assigned before it can be used.

| 变量类型 | 说明与示例 |
|---------|-----------|
| **Nullable 变量** | 可以存储 `null`。<br>`int? age;` `String? name;` |
| **Non-nullable 变量** | 不能为 `null`，必须初始化。<br>`int age = 20;` `String name = 'Alice';` |
| **late 变量** | 延迟初始化，使用时保证已赋值。<br>`late String description;` `description = 'ok';` |
| **final 变量** | 运行时常量，只赋值一次。<br>`final now = DateTime.now();` `final List<int> list = [1,2];` |
| **const 变量** | 编译时常量，深度不可变。<br>`const pi = 3.14;` `const list = [1,2,3];` |
| **Wildcard 变量** | 忽略匹配的值，不分配存储。<br>`var (_, y) = (1, 2);` `list.forEach((_) => print('item'));` |


| Type | Size (bits) | Min value | Max value | 说明 |
|------|-------------|-----------|-----------|------|
| **int** | 64 | -9,223,372,036,854,775,808 | 9,223,372,036,854,775,807 | Dart 中整数统一为 64 位，无 Byte/Short/Long 区分 |
