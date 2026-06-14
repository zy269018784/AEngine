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



| Type | Size (bits) | Min value | Max value | 说明 |
|------|-------------|-----------|-----------|------|
| **int** | 64 | -9,223,372,036,854,775,808 (-2⁶³) | 9,223,372,036,854,775,807 (2⁶³ - 1) | 有符号 64 位整数，Dart 的唯一整数类型 |
| **double** | 64 | 4.9E-324 | 1.7976931348623157E308 | 64 位双精度浮点数 (IEEE 754) |
| **num** | 64 | -2⁶³ | 2⁶³ - 1 | int 和 double 的父类型，可同时接收整数和浮点数 |
| **bool** | 1 (概念上) | false | true | 布尔值，只能是 true 或 false |
| **String** | 可变 | - | - | UTF-16 编码的字符串，不可变 |
| **Runes** | 可变 | - | - | UTF-32 码点，用于处理 Unicode 字符 |
| **List\<T\>** | 可变 | - | - | 有序可重复集合，类似数组 |
| **Set\<T\>** | 可变 | - | - | 无序不可重复集合 |
| **Map\<K,V\>** | 可变 | - | - | 键值对集合 |
| **Symbol** | 可变 | - | - | 表示运算符或标识符 |
| **Null** | - | null | null | 唯一实例就是 `null` |
