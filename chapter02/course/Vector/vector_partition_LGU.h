template <typename T>//轴点构造算法：通过调整元素构造区间[lo,hi)的轴点，并返回其秩
Rank Vector<T>::partition(Rank lo, Rank hi){//LGU版
swap(_elem[lo],_elem[lo+rand() % (hi - lo)]);//任选一个元素与首元素交换
T pivot = _elem[lo];//以首元素为候选轴点——经以上交换，等于随机选取
int mi = lo;
for (Rank k = lo + 1; k < hi; k++)//自左向右扫描
    if(_elem[k] < pivot)//若当前元素_elem[k]小于pivot，则
        swap(_elem[++mi], _elem[k]);//将_elem[k]交换至原mi之后，使L子序列向右拓展

swap(_elem[lo], _elem[mi]);//候选点归位
return mi;//返回轴点的秩
}
