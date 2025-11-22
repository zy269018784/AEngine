/*
	1. 
		http://mingw-w64.org/
		https://www.msys2.org/
		https://www.cygwin.com/

	2. STL
		2.1 容器 (Containers)
			序列式容器 (Sequence Containers)
				vector
				deque
				list
				forward_list
				array
				string
			关联式容器 (Associative Containers)
				set							有序唯一元素集合	
				multiset					有序可重复元素集合
				map							键值对映射，键唯一
				multimap					键值对映射，键可重复
			无序关联容器 (Unordered Associative Containers)
				unordered_set
				unordered_multiset
				unordered_map
				unordered_multimap
			容器适配器 (Container Adapters)
				stack
				queue
				priority_queue
		2.2 算法 (Algorithms)
			非修改序列算法
				all_of, any_of, none_of (C++11)
				for_each
				count, count_if
				find, find_if
				search
				equal
				mismatch
			修改序列算法
				copy, copy_if
				move (C++11)
				transform
				replace, replace_if
				fill
				generate
				remove, remove_if
				unique
			排序和相关操作
				sort
				stable_sort
				partial_sort
				nth_element
				binary_search
				lower_bound, upper_bound
				merge
				inplace_merge
				includes
				set_union, set_intersection
			数值算法
				accumulate
				inner_product
				adjacent_difference
				partial_sum
				iota (C++11)
			堆操作
				make_heap
				push_heap
				pop_heap
				sort_heap
			最小/最大操作
				min, max
				minmax (C++11)
				min_element, max_element
				clamp (C++17)
		2.3 迭代器 (Iterators)
			输入迭代器 (Input Iterator)
			输出迭代器 (Output Iterator)
			前向迭代器 (Forward Iterator)
			双向迭代器 (Bidirectional Iterator)
			随机访问迭代器 (Random Access Iterator)
			反向迭代器 (reverse_iterator)
			插入迭代器 (insert_iterator)
			流迭代器 (istream_iterator, ostream_iterator)
			移动迭代器 (move_iterator)
		2.4 函数对象 (Functors)
			算术运算
				plus<T>
				minus<T>
				multiplies<T>
				divides<T>
				modulus<T>
				negate<T>
			比较运算
				equal_to<T>
				not_equal_to<T>
				greater<T>
				less<T>
				greater_equal<T>
				less_equal<T>
			逻辑运算
				logical_and<T>
				logical_or<T>
				logical_not<T>
			其他函数对象
				identity (C++20)
				bit_and, bit_or, bit_xor		
		2.5 适配器 (Adapters)
		2.6 分配器 (Allocators)
	3. 面向对象三大特性
		封装
		多态
		继承
	4. 类
		4.1 构造函数(Constructor function)
			Default Constructor
			Parameterized Constructor
			Copy Constructor
			Move Constructor
			Delegating Constructor
			Converting Constructor
				https://web.stanford.edu/class/archive/cs/cs106b/cs106b.1084/cs106l/handouts/180_Conversion_Constructors.pdf
			Inheriting Constructor
			constexpr Constructor
			Explicitly Defaulted Constructor
			Explicitly Deleted Constructor
		4.2 构造函数例子
			Class MyClass
			{
			public:	
				// Default Constructor
				MyClass();

				// Parameterized Constructor
				MyClass(int v);

				// Copy Constructor
				MyClass(const MyClass& other);

				// Move Constructor
				MyClass(MyClass&& other) noexcept;

				// Delegating Constructor
				MyClass() : MyClass(0) {}
			};
		4.3 构造函数和析构函数调用顺序
			4.3.1 先构造父类的, 多个父类就按定义顺序构造, 在构造子类. 先析构子类, 在析构父类, 多个父类按定义逆序析构.
				class Child : public A, public B, public C 
				{
				
				}
				构造顺序:
					A constructor
					B constructor
					C constructor
					Child constructor
				析构顺序:
					Child deconstructor
					C deconstructor
					B deconstructor
					A deconstructor
			4.3.2 虚继承
				4.3.2.1 
					class VirtualBase
					class A : virtual public VirtualBase
					class B : virtual public VirtualBase
					class Child : public A, public B
					构造顺序:
						VirtualBase constructor  // 虚基类最先
						A constructor
						B constructor
						Child constructor
					析构顺序:
						Child destructor
						B destructor
						A destructor
						VirtualBase destructor   // 虚基类最后
				4.3.2.2 混合继承
					class Base1
					class Base2
					class Base3
				

		4.4 析构函数(Deconstructor function)
			virual析构函数
		4.5 析构函数例子
		4.7
			Copy Assignment Operator
			Move Assignment Operator
		4.8 final specifier
			类不能被继承
			虚函数不能被子类override
		4.9 虚函数和纯虚函数(virtual function && pure virtual function)
			虚函数
				virtual void fun();
			纯虚函数
				virtual void fun() =0;
		4.10 虚继承(Virtual Inheritance)
			菱形继承问题（diamond problem）
*/