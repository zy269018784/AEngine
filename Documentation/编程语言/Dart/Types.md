| 类型 | 关键字 | 示例 | 说明 |
|------|--------|------|------|
| **Numbers** | `int` | `42` | 整数，支持任意精度 |
| | `double` | `3.14159` | 双精度浮点数，支持小数 |
| **Strings** | `String` | `'Hello'` 或 `"World"` | UTF-16 字符串，支持单引号或双引号 |
| **Booleans** | `bool` | `true` / `false` | 布尔值，只有两个字面量值 |
| **Records** | `(value1, value2)` | `('Alice', 30)` | 匿名聚合类型，可包含多个不同类型的值 |
| **Functions** | `Function` | `(int x) => x * 2` | Dart 是一等公民，函数可作为对象传递 |
| **Lists** | `List<T>` | `[1, 2, 3]` | 有序集合，支持随机访问 |
| **Sets** | `Set<T>` | `{1, 2, 3}` | 无序且唯一的元素集合 |
| **Maps** | `Map<K, V>` | `{'key': 'value'}` | 键值对集合，键和值可以是任意类型 |
| **Runes** | `Runes` | `Runes('👨‍👩‍👧')` | UTF-32 码点字符串，用于处理 Unicode 字符 |
| **Symbols** | `Symbol` | `#myVar` | 用于表示 Dart 代码中的标识符元数据 |
| **Null** | `Null` | `null` | 表示空值，所有类型的子类型 |