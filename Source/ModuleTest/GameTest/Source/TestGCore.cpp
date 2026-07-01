#include "GCore/GList.h"
#include "GCore/GQueue.h"
#include "GCore/GStack.h"
#include "GCore/GVector.h"
#include "GCore/GMultiHash.h"
#include "GCore/GMultiMap.h"
#include "GCore/GSet.h"

#include <iostream>

int TestGMultiHash(int argc, char **argv);
int TestGMultiMap(int Argc, char** Argv);

int TestGSet(int Argc, char** Argv);



int TestGCore(int argc, char **argv)
{
    return TestGSet(argc, argv);
}


int TestGMultiHash(int argc, char **argv)
{
  // ========== 创建 ==========
    GMultiHash<std::string, int> Hash;

    // ========== 插入（一个键对应多个值） ==========
    Hash.Insert("Apple", 10);
    Hash.Insert("Apple", 20);
    Hash.Insert("Apple", 30);
    Hash.Insert("Banana", 5);
    Hash.Insert("Banana", 15);
    Hash.Insert("Cherry", 25);

    std::cout << "Size: " << Hash.GetSize() << std::endl;

    // ========== 查询 ==========
    std::cout << "\nValues for 'Apple': ";
    auto Values = Hash.Values("Apple");
    for (const auto& V : Values) {
        std::cout << V << " ";
    }
    std::cout << std::endl;

    std::cout << "Count of 'Apple': " << Hash.Count("Apple") << std::endl;
    std::cout << "Contains 'Apple'? " << (Hash.Contains("Apple") ? "Yes" : "No") << std::endl;
    std::cout << "Contains 'Apple'->20? " << (Hash.Contains("Apple", 20) ? "Yes" : "No") << std::endl;
    std::cout << "Contains 'Apple'->99? " << (Hash.Contains("Apple", 99) ? "Yes" : "No") << std::endl;
    std::cout << "Contains 'Grape'? " << (Hash.Contains("Grape") ? "Yes" : "No") << std::endl;

    // ========== 遍历 ==========
    std::cout << "\nAll entries: ";
    for (const auto& Item : Hash) {
        std::cout << "(" << Item.first << "->" << Item.second << ") ";
    }
    std::cout << std::endl;

    // ========== 删除 ==========
    Hash.Remove("Apple", 20);  // 删除指定的键值对
    std::cout << "\nAfter removing Apple->20, size: " << Hash.GetSize() << std::endl;

    Hash.Remove("Banana");  // 删除所有 Banana
    std::cout << "After removing all Banana, size: " << Hash.GetSize() << std::endl;

    // ========== 使用初始化列表 ==========
    GMultiHash<std::string, std::string> Names = {
        {"Alice", "Engineer"},
        {"Alice", "Manager"},
        {"Bob", "Developer"},
        {"Charlie", "Designer"},
        {"Charlie", "Artist"}
    };

    std::cout << "\nNames hash:\n";
    for (const auto& Item : Names) {
        std::cout << "  " << Item.first << " -> " << Item.second << std::endl;
    }

    std::cout << "\nValues for 'Alice': ";
    for (const auto& Role : Names.Values("Alice")) {
        std::cout << Role << " ";
    }
    std::cout << std::endl;

    // ========== 拷贝和移动 ==========
    GMultiHash<int, std::string> H1 = {
        {1, "One"},
        {1, "Uno"},
        {2, "Two"},
        {3, "Three"}
    };

    GMultiHash<int, std::string> H2 = H1;  // 拷贝
    GMultiHash<int, std::string> H3 = std::move(H1);  // 移动

    std::cout << "\nH2: ";
    for (const auto& Item : H2) {
        std::cout << "(" << Item.first << "->" << Item.second << ") ";
    }
    std::cout << std::endl;

    std::cout << "H3: ";
    for (const auto& Item : H3) {
        std::cout << "(" << Item.first << "->" << Item.second << ") ";
    }
    std::cout << std::endl;

    std::cout << "H1 size after move: " << H1.GetSize() << std::endl;

    // ========== 清空 ==========
    H2.Clear();
    std::cout << "\nH2 after clear, size: " << H2.GetSize() << std::endl;
    std::cout << "H2 is empty? " << (H2.IsEmpty() ? "Yes" : "No") << std::endl;

    return 0;
}


int TestGMultiMap(int Argc, char** Argv) {
    // ========== 创建 ==========
    GMultiMap<std::string, int> Map;

    // ========== 插入（一个键对应多个值） ==========
    Map.Insert("Apple", 10);
    Map.Insert("Apple", 20);
    Map.Insert("Apple", 30);
    Map.Insert("Banana", 5);
    Map.Insert("Banana", 15);
    Map.Insert("Cherry", 25);

    std::cout << "Size: " << Map.GetSize() << std::endl;

    // ========== 查询 ==========
    std::cout << "\nValues for 'Apple': ";
    auto Values = Map.Values("Apple");
    for (const auto& V : Values) {
        std::cout << V << " ";
    }
    std::cout << std::endl;

    std::cout << "Count of 'Apple': " << Map.Count("Apple") << std::endl;
    std::cout << "Contains 'Apple'? " << (Map.Contains("Apple") ? "Yes" : "No") << std::endl;
    std::cout << "Contains 'Apple'->20? " << (Map.Contains("Apple", 20) ? "Yes" : "No") << std::endl;
    std::cout << "Contains 'Apple'->99? " << (Map.Contains("Apple", 99) ? "Yes" : "No") << std::endl;
    std::cout << "Contains 'Grape'? " << (Map.Contains("Grape") ? "Yes" : "No") << std::endl;

    // ========== 遍历（按键升序） ==========
    std::cout << "\nAll entries (sorted by key): ";
    for (const auto& Item : Map) {
        std::cout << "(" << Item.first << "->" << Item.second << ") ";
    }
    std::cout << std::endl;

    // ========== 删除 ==========
    Map.Remove("Apple", 20);  // 删除指定的键值对
    std::cout << "\nAfter removing Apple->20, size: " << Map.GetSize() << std::endl;

    Map.Remove("Banana");  // 删除所有 Banana
    std::cout << "After removing all Banana, size: " << Map.GetSize() << std::endl;

    // ========== 使用初始化列表 ==========
    GMultiMap<std::string, std::string> Names = {
        {"Alice", "Engineer"},
        {"Alice", "Manager"},
        {"Bob", "Developer"},
        {"Charlie", "Designer"},
        {"Charlie", "Artist"}
    };

    std::cout << "\nNames map:\n";
    for (const auto& Item : Names) {
        std::cout << "  " << Item.first << " -> " << Item.second << std::endl;
    }

    std::cout << "\nValues for 'Alice': ";
    for (const auto& Role : Names.Values("Alice")) {
        std::cout << Role << " ";
    }
    std::cout << std::endl;

    // ========== 拷贝和移动 ==========
    GMultiMap<int, std::string> M1 = {
        {1, "One"},
        {1, "Uno"},
        {2, "Two"},
        {3, "Three"}
    };

    GMultiMap<int, std::string> M2 = M1;  // 拷贝
    GMultiMap<int, std::string> M3 = std::move(M1);  // 移动

    std::cout << "\nM2: ";
    for (const auto& Item : M2) {
        std::cout << "(" << Item.first << "->" << Item.second << ") ";
    }
    std::cout << std::endl;

    std::cout << "M3: ";
    for (const auto& Item : M3) {
        std::cout << "(" << Item.first << "->" << Item.second << ") ";
    }
    std::cout << std::endl;

    std::cout << "M1 size after move: " << M1.GetSize() << std::endl;

    // ========== 清空 ==========
    M2.Clear();
    std::cout << "\nM2 after clear, size: " << M2.GetSize() << std::endl;
    std::cout << "M2 is empty? " << (M2.IsEmpty() ? "Yes" : "No") << std::endl;

    return 0;
}


int TestGSet(int Argc, char** Argv) {
    std::cout << "========== Testing GSet ==========\n";

    // ========== 基本操作 ==========
    std::cout << "\n--- Basic Operations ---\n";

    GSet<int> Set;

    // 插入
    Set.Insert(10);
    Set.Insert(20);
    Set.Insert(30);
    Set.Insert(20);  // 重复，不会插入
    Set.Insert(40);

    std::cout << "Size: " << Set.GetSize() << std::endl;
    std::cout << "Is empty: " << (Set.IsEmpty() ? "Yes" : "No") << std::endl;

    // 查找
    std::cout << "Contains 20? " << (Set.Contains(20) ? "Yes" : "No") << std::endl;
    std::cout << "Contains 99? " << (Set.Contains(99) ? "Yes" : "No") << std::endl;

    // 遍历
    std::cout << "Elements: ";
    for (const auto& Item : Set) {
        std::cout << Item << " ";
    }
    std::cout << std::endl;

    // ========== 初始化 ==========
    std::cout << "\n--- Initialization ---\n";

    GSet<int> Set2 = {1, 2, 3, 4, 5, 3, 5};  // 重复的会被自动去重

    std::cout << "Set2 elements: ";
    for (const auto& Item : Set2) {
        std::cout << Item << " ";
    }
    std::cout << std::endl;
    std::cout << "Size: " << Set2.GetSize() << std::endl;

    // ========== 集合运算 ==========
    std::cout << "\n--- Set Operations ---\n";

    GSet<int> A = {1, 2, 3, 4, 5};
    GSet<int> B = {4, 5, 6, 7, 8};

    std::cout << "A: ";
    for (const auto& V : A) std::cout << V << " ";
    std::cout << std::endl;

    std::cout << "B: ";
    for (const auto& V : B) std::cout << V << " ";
    std::cout << std::endl;

    // 并集
    GSet<int> Union = A.Union(B);
    std::cout << "Union: ";
    for (const auto& V : Union) std::cout << V << " ";
    std::cout << std::endl;

    // 交集
    GSet<int> Intersection = A.Intersection(B);
    std::cout << "Intersection: ";
    for (const auto& V : Intersection) std::cout << V << " ";
    std::cout << std::endl;

    // 差集
    GSet<int> Difference = A.Difference(B);
    std::cout << "Difference (A - B): ";
    for (const auto& V : Difference) std::cout << V << " ";
    std::cout << std::endl;

    // 对称差集
    GSet<int> SymDiff = A.SymmetricDifference(B);
    std::cout << "Symmetric Difference: ";
    for (const auto& V : SymDiff) std::cout << V << " ";
    std::cout << std::endl;

    // 子集判断
    GSet<int> C = {1, 2, 3};
    std::cout << "C is subset of A: " << (C.IsSubsetOf(A) ? "Yes" : "No") << std::endl;
    std::cout << "A is subset of C: " << (A.IsSubsetOf(C) ? "Yes" : "No") << std::endl;
    std::cout << "C is proper subset of A: " << (C.IsProperSubsetOf(A) ? "Yes" : "No") << std::endl;

    // ========== 删除和清空 ==========
    std::cout << "\n--- Remove and Clear ---\n";

    GSet<int> Set3 = {1, 2, 3, 4, 5};

    std::cout << "Before: ";
    for (const auto& V : Set3) std::cout << V << " ";
    std::cout << std::endl;

    Set3.Remove(3);
    Set3.Remove(7);  // 不存在，不会报错

    std::cout << "After remove 3: ";
    for (const auto& V : Set3) std::cout << V << " ";
    std::cout << std::endl;

    Set3.Clear();
    std::cout << "After clear, size: " << Set3.GetSize() << std::endl;
    std::cout << "Is empty? " << (Set3.IsEmpty() ? "Yes" : "No") << std::endl;

    return 0;
}