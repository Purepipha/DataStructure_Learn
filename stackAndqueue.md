# 4. 栈与队列
栈与队列的数据操作范围仅限于逻辑上的特定某端。
信息处理领域，PostScript或者Java，实时运行的环境都是基于栈的虚拟机。
队列适用于需要公平且经济的对资源做管理或分配的场合。
## 4.1 栈
### 4.1.1 ADT接口
- 入栈与出栈
  栈禁止擦欧洲哦的一端成为盲端。

|操作接口|功能|
|---:|:---|
|size()|报告栈的规模|
|empty()|判断栈是否为空|
|top()|**引用**栈顶对象|
|pop()|删除栈顶对象|
|push(e)|将e插至栈顶|

- 后进先出LIFO
### 4.1.2 Stack模板类
- [基于Vector实现的Stack类](code/Stack/Stack_vector.h)
- [基于List实现的Stack类](code/Stack/Stack_List.h)

