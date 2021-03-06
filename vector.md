# 2. 向量
## 2.1 抽象数据类型
### 2.1.1 接口与实现
- 抽象数据类型 = 数据模型 + 定义在模型上的一组操作
    &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;抽象定义&emsp;外部的逻辑特性&emsp;&emsp;&emsp;&emsp;操作&语义
    &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;一种定义&emsp;不考虑时间复杂度&emsp;&emsp;&emsp;不涉及数据的存储方式
- 数据结构 = 基于某种特定语言，实现ADT的一整套算法
    &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;具体实现&emsp;内部的表示与实现&emsp;&emsp;&emsp;&emsp;完整的算法
    &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;多种实现&emsp;与复杂度密切相关&emsp;&emsp;&emsp;&emsp;要考虑数据的具体存储机制
- 在数据结构的**具体实现**与**实际应用**之间，ADT就分工与接口制定了的规范
  - 实现：**高效**兑现数据结构的ADT接口操作
  - 应用：便捷的通过操作接口使用数据结构
- 按照ADT规范
  - 高层 **算法设计**者与底层 **数据结构实现者**可高效的分工协作
  - 不同的算法与数据结构可以 **便捷组合**
  - 每种操作接口只需统一的实现一次，代码篇幅缩短，软件 **复用**度提高
### 2.1.2 从数组到向量
- 循秩访问
  - C/C++中，数组元素与编号一一对应
  - 元素由**编号**唯一指代，并可 **直接访问** //故亦称作线性数组
- 向量：向量是数组的 **抽象**与 **泛化**，由一组元素按线性次序封装而成
  - 各元素与[0,n)内的秩(rank)一一对应：using Rank = int Rank；
  - 操作、管理维护更加简化、统一与安全
  - 元素类型可灵活选取，便于定义复杂数据结构 //Vector<PFCTree*>pfcForest
- 向量ADT接口

操作|功能|适用对象
:---:|:---:|:---:
size()|报告向量当前的规模(元素总数)|向量
get(r)|获取秩为r的元素|向量
put(r,e)|用e替换秩为r的元素的数值|向量
insert(r,e)|e作为秩为r元素插入，原后继依次后移|向量
remove(r)|删除秩为r的元素，返回该元素原值|向量
disordered()|判断所有的元素是否已按非降序排列|向量
sort()|调整二元素的位置，使之按非降序排列|向量
find(e)|查找目标元素e|向量
search(e)|查找e，返回不大于e且秩最大的元素|有序向量
deduplicate(),uniquify()|删除重复元素|向量/有序向量
traverse()|遍历响亮并同意处理所有元素|向量
- [STL VECTOR样例程序](/chapter02/course/vector_example.cpp)
### 2.1.3 模板类
![模板类的基本组成](chapter02/assets/mk2022-02-02-20-24-18.png)
- [构造+析构：重载程序](/code/Vector/Vector.h)
## 2.2 可扩充向量
### 2.2.1 算法
- 静态空间管理
  - 开辟内部数组_elem[]并使用一段连续的物理空间
    - _capacity 总容量
    - _size 当前实际规模n
  - 静态空间策略，容量_capacity固定，有明显缺陷
    - 上溢/overflow：_elem[]不足以存放所有元素，尽管系统空间充足
    - 下溢/underflow:_elem[]元素廖廖无几，浪费存储空间
      **装填因子**/ load factor:$\lambda = \_size/\_capacity << 50\%$
  - 一般应用环境，难以准确 **预测**空间的需求量
- 动态空间管理
  - 在即将上溢时，**适当扩大**内部数组的容量
  - [扩容算法](code/Vector/vector_expand.h)
### 2.2.2 分摊
- 容量递增策略
  - 追加固定容量： _elem = new_T[_capacity += INCREMENT];
  - 最坏情况： 在初始容量0的**空**向量中，连续插入n = m * I && n >> 2个元素，**无删除**操作。
  - 在第1、I+1、2I+1...次插入时，都需要扩容。
  - 即使不计申请空间操作，扩容复制原向量的成本依次为：
    0, I，2I，...(m-1)I   //算数级数
    总体耗时O(n^2),每次(insert/remove)的**分摊成本**为O(n)
- 容量加倍策略
  - 容量加倍： _elem = new T[_capacity <<= 1];
  - 最坏情况：在初始容量为**1**的 **满** 向量中，连续插入 n = 2^m && n >> 2个元素，而 **无删除** 操作
  - 在第1、2、4、8、...次插入时，都需要扩容
  - 各次扩容过程中复制原向量的成本依次为
    1,2,4,...2^m-1,2^m = n  //几何级数
    总体耗时O(n),每次(insert/remove)操作的**分摊成本**为O(1)
- 对比

指标|递增策略|倍增策略
:---:|:---:|:---:
累计<br>扩容时间|O(n^2)|O(n)
分摊<br>扩容时间|O(n)|O(1)
空间利用率<br>(装填因子)|≈100%|>50%
- 平均分析vs分摊分析
  - 平均(average complexity)：根据各种操作出现的概率，将对应的成本加权平均
    - 各种可能的操作，作为 **独立事件** 分别考察
    - 割裂了操作之间的 **相关** 性和 **连贯性**
    - 往往 **不能准确** 评判数据结构和算法的真实性能
  - 分摊(amortized complexity)：**连续** 实施 **足够多** 次操作，所需 **总体** 成本摊还至 **单次** 操作
    - 从实际可行的角度，对一系列操作做整体的考量
    - 更加 **忠实** 地刻画了可能出现的操作序列
    - 更为 **精准** 地评判数据结构和算法的真实性能

## 2.3 无序向量
### 2.3.1 基本操作
- [元素访问](code/Vector/vector_bracket.h)
  - V.get(r)和V.put(r,2)不够便捷、直观。通过 **重载** 下标操作符"[]"实现
  - 重载运算符的返回值为引用，这样可以实现元素赋值操作
  - 这里采用了简易的方式处理意外和错误(入口参数约定：0 <= r < _size)
  - 实际应用中，应采用更为严格的方式
- [插入操作](code/Vector/vector_insert.h)
- [区间删除](code/Vector/vector_removeInterval.h)
- [单元素删除](code/Vector/vector_remove.h)
  - 将 **单元素** 视作 **区间** 的特例
  - 但不能反过来，通过反复调用remove(r)来实现remove(lo,hi):
    - 每次循环耗时 n-hi = O(n);
    - 循环次数 hi-lo = O(n);
    - 这样将导致时间复杂度为O(n^2);
### 2.3.2 查找
- 对于无序向量，只需要判等器
- 对于有序向量，需要比较器
- [顺序查找](code/Vector/vector_find.h)
  - 输入敏感(input-sensitive):最好O(1)，最差O(n)
### 2.3.3 去重
- [去重](code/Vector/vector_deduplicate.h)
  - 可以从不变性和单调性证明算法的正确性
    - 不变性：[0,i)内没有重复元素
    - 单调性：i增大，直至_size，问题规模不断缩小
### 2.3.4 遍历
- 对于向量中的每一元素，统一实施visit()操作 //如何指定visit()?如何将其传递到向量内部？
- 有两种方式，一种是使用函数指针，另一种是使用函数对象
  - 函数指针，只读或者局部性修改
  - 函数对象，全局性修改更便捷
  - 函数对象实例：统一地将向量的元素分别 **加一**，只需
    - 实现一个可以单个T类型元素加一的类(结构)
      template <typename T>   // 假设T可直接递增或已重载"++"
      struct Increase     // 函数对象：通过重载()实现
      { virtual void operator()(T & e) {e++;} };
    - 将其作为参数传递给遍历算法
      template <typename T>
      void increase(Vector<T> & V)
      { V.traverse(Increase<T>());} // 即可以使之作为基本操作，遍历向量
## 2.4 有序向量
### 2.4.1 唯一化
- 有序性及其甄别
  - 起泡排序原理：有序/无序序列中，任何/总有一对 **相邻元素** 顺序/逆序
  - 因此，相邻逆序对数目，可在一定程度上 **度量** 向量的 **紊乱** 程度
  - [disordered()](code/Vector/Vector.h)
  - 无序向量经 **预处理** 转换为有序向量之后，算法多可优化。
- 去重算法
  - 若采用无序向量的去重算法，会相当低效(O(n^2))。
  - [高效去重法uniquify()](code/Vector/vector_uniquify.h)
### 2.4.2 二分查找(版本A)
- 统一接口
  - 对于特殊情况的处理：
    - 目标元素不存在
    - 同时存在多个
- 有序向量中，每个元素都是 **轴点**
  - 以任一元素为界，可以将待查找区间分为三部分
- 减而治之
  将目标元素e与轴点处元素x作比较：
  - e < x:则e必存在轴点左侧子区间，故可递归左侧子区间
  - x < e:则e必在轴点右侧字却见，故递归右侧子区间
  - e = x：在此处命中，可随即返回 // 若有多个，返回何者
  将轴点mi取做中点，则至多经过两次比较，要么命中，要么将问题规模缩减一半
- 实现 [binSearch()](code/Vector/vector_search_binary_A.h)
- 查找长度
  - 如何更精确的评估查找算法的性能？考察关键码的比较次数
  - 通常，需分别针对 **成功** 与 **失败**查找，从 **最好、最坏、平均** 等角度评估
  - 上述二分法，成功、失败时的平均长度均大致为O(1.50×logn)
  - 以n=7时为例：
    ![](/chapter02/assets/mk2022-02-03-18-24-32.png)
### 2.4.3 Fibnacci查找
- 思路及原理
  - 版本A：转向左右分支的关键码 **比较次数** 不等，而 **递归深度**却相同
  - 通过对 **递归深度** 的不均衡对 **转向成本** 的不均衡做 **补偿**， 平均查找深度能进一步缩短
  - 若有 n = fib(k) - 1，则可取mi = fib(k-1) - 1
    于是，前后子向量的长度分别为 fib(k-1) - 1和fib(k-2) - 1
- 实现 [fibSearch()](code/Vector/vector_search_fibonaccian_A.h)
- 平均查找长度增长趋势为O(1.44 log_2(n))
### 2.4.4 二分查找(版本B)
- 从三分支到两分支
  即无论朝哪个方向发展，都做一次比较。
- 实现 [二分查找版本B](code/Vector/vector_search_binary_B.h)
- 性能：该算法的渐进复杂度O(logn)不受任何影响
### 2.4.5 二分查找(版本C)
- 实现 [二分查找版本C](code/Vector/vector_search_binary_C.h)
- 性能与版本A和版本B相比，没有变化
- 版本C可以对特殊情况的约定，即存在多个元素时，返回秩最大者；不存在元素时，返回失败的位置
## 2.5 排序与下界
### 2.5.1 有序性
从数据处理的角度看，有序性在很多场合都能极大的提高计算效率。以查找算法为例，可以将复杂度从O(n)优化到O(logn)
### 2.5.2 排序及其分类
解决应用问题时采取的策略是，将向量转换为有序向量，在调用有序向量的高效算法。
排序算法的分类：
- 按照处理数据的规模与存储特点分类：
  - 内部排序算法(数据规模不大，内存足以容纳)
  - 外部排序算法(数据规模很大，必须借助外部甚至分布式存储器)
- 根据输入形式不同进行分类
  - 离线算法(待处理的数据以批处理的形式整体给出)
  - 在线算法(待排序的数据需要实时生成，在排序算法启动后数据陆续到达)
- 根据依赖不同
  - 串行
  - 并行
- 是否采用随机策略
  - 确定式
  - 随机式
这里讨论的是确定式串行脱机的内部排序算法。
### 2.5.3 下界
下界解决的问题是一个问题时间复杂度最小是多少。
- 复杂度下界
  任一问题在最坏情况下的最低计算成本，即为该问题的复杂度下界。尽早的确定一个问题的复杂度下界，对于相关算法的优化有巨大的裨意。
### 2.5.4 比较树
- 基于比较的分支
  将程序的运行过程化为一个树形结构。节点(圆圈)表示算法过程中不同的状态，有方向的边表示不同状态之间的相互转换。
  - 根节点：算法入口处的起始状态
  - 内部节点：对应过程的某步计算，通常属于基本操作
  - 叶节点，对应一系列计算后某次运行的终止状态
- 比较树
  算法所有可能的执行过程，都涵盖与这一树形结构中。具体的，该树具有一下性质：
  - 每一内部节点对应于一次比对操作
  - 内部节点的左右分支，分别对应两种比对结果下的执行方向
  - 根到叶节点的路径对应于算法某次执行的完整过程及输出

  按照上述规则与算法相对应的树，称作比较树。完全取决于不同变量或常量的比对或比较结果，称作基于比较式算法(comparison-based algorithm)，简称CBA算法。
### 2.5.5 估计下界
- 最小树高
  - 对于存在CBA式算法的计算问题，问题的复杂度下届等于比较树的最小高度
  - 最小高度：高度为h的二叉树，叶节点的数目不可能多余2^h，因此输出结果不少于N种，则比较树中叶节点数目不可能少于N个，树高h不可能小于$log_2n$。
- 苹果鉴别
  h >= $log_23$ = 2
  最坏情况下，至少需要两次比较
- 排序
  以CBA排序算法为例，可能的输出有N=n!种。排序算法的比较树属于三叉树。
  $h >= [log_3(n!)] = [log_3e×ln(n!)] = \Omega(nlogn)$
  上述结果是针对比较树模型而言，存在不属于此类的比较算法，其最坏情况下的运行时间可能低于这一下界。

## 2.6排序器
### 2.6.1 统一入口
排序操作应该纳入向量基本接口的范围。
### 2.6.2 起泡排序
- [起泡排序实现](code/Vector/vector_bubblesort_A.h)
- [扫描交换实现](code/Vector/Vector.h)
- 重复元素与稳定性
  稳定性是一个更细致的要求，即要求对重复元素，排序算法不改变重复元素的相对顺序。上述起泡算法仍可改进。
### 2.6.3 归并排序
- 历史与发展
  归并排序是第一个可以在最坏情况下保持O(nlogn)运行时间的确定性排序算法。
  对海量信息的处理必须首先考虑如何在跨节点的环境中高效协同的计算。
- 有序向量的二路归并
  归并排序可以理解为通过反复调用所谓二路归并(2-way merge)的算法实现的。二路归并属于**迭代式算法**，每步迭代的过程中，只需要比较两个待归并向量的**首元素**，将最小者取出并追加到**输出向量的结尾**，该元素在原向量中的后继成为新的首元素。直至**某一向量为空**，最后将另一非空向量**整体接至**输出向量的末尾。
- 分治策略
  归并排序的主体结构属于典型的分治策略:[归并排序代码](code/Vector/vector_mergeSort.h)
- 二路归并接口的实现 [二路归并算法](code/Vector/vector_merge.h)
- 归并时间
  归并算法merge()的渐进时间成本，取决于循环迭代的总次数，即时间复杂度为O(n),且该算法在最好情况下也为O(n)，即其时间复杂度为 $\Theta(n)$ 。二路归并的算法可在严格少于 $\Omega(nlogn)$的时间内完成排序的这一事实，与此前的排序算法下界的结论并不矛盾——这里的**输入并非一组完全随机的元素**
- 推广
  二路归并只需线性时间的结论，并不限于相邻且等长的子向量。
- 排序时间为O(nlogn)
