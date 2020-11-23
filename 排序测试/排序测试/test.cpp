#include<iostream>

using namespace std;

//交换
void Swap(int* arr, int left, int right) {
    int tmp = arr[left];
    arr[left] = arr[right];
    arr[right] = tmp;
}

//冒泡排序
void bubbleSort(int* arr, int n) {
    while (n > 0) {
        //给一个标记
        // flag : 0 --> 一轮冒泡排序中没有发生交换
        int flag = 0;
        //end : 待排序区间长度
        // [0, end] 为待排序区间
        int end = n;
        //遍历未排序区间, 一轮冒泡排序
        for (int i = 0; i < end - 1; i++) {
            // 比较相邻元素, 大的向后移动
            if (arr[i] > arr[i + 1]) {
                Swap(arr, i, i + 1);
                flag = 1;
            }
        }
        //flag = 0表示一轮冒泡中没有发生交换, 即数据已经有序, 可以提前结束
        if (flag == 0)
            break;
        //待排序区间长度减一
        n--;
    }
}


void insertSort(int* arr, int n) {
    for (int i = 1; i < n; i++) {
        //end 表示当前需要排序的位置
        //[0, end)是已排序区间
        int end = i;
        //需要排序的元素
        int key = arr[end];
        //这里end > 0, 不能 =0 因为下面取end - 1的时候会越界访问 
        while (end > 0 && arr[end - 1] > key) {
            //如果位置不合适, end位置元素后移一位
            arr[end] = arr[end - 1];
            //继续向前遍历
            end--;
        }
        arr[end] = key;
    }
}

//希尔排序
//先走一个预排序, 最后进行插入排序, 相当于是多轮的插入排序
void shellSort(int* arr, int n) {
    //步长
    int gap = n;
    //多轮插入排序
    while (gap > 1) {
        gap = gap / 2;
        //一次插入排序
        for (int i = 0; i < n - gap; i++) {
            //通过步长gap进行逻辑分组
            //同组的元素进行插入排序
            //不同组的元素交替排序
            int end = i;
            int key = arr[end + gap];
            while (end >= 0 && arr[end] > key) {
                arr[end + gap] = arr[end];
                end -= gap;
            }
            arr[end + gap] = key;
        }
    }
}


//三数取中
//是快速排序的优化方法, 可以吧中间值当做基准值, 使划分趋于理想化
int Getmid(int* array, int begin, int end) {
    int mid = begin + (end - begin) / 2;
    if (array[begin] > array[mid]) {
        //begin > mid
        if (array[mid] > array[end])
            return mid;
        else {
            //begin > mid, end >= mid
            if (array[begin] > array[end])
                return end;
            else
                return begin;
        }
    }
    else {
        //begin <= mid
        if (array[begin] > array[end])
            return begin;
        else {
            //begin <= mid, begin <= end
            if (array[mid] > array[end])
                return end;
            else
                return mid;
        }
    }
}

/*
 hora法 :
 1. 取待划分区间第一个元素为基准值
 2. 从待划分区间末尾向前找第一个小于基准值的位置
 3. 从待划分区间开头向后找第一个大于基准值的位置
 4. 交换2,3找到位置的数据, 重复执行234
 5.查到到相遇的位置, 交换相遇位置和基准值数据, 完成一轮划分
*/
int partion(int* array, int begin, int end) {
    //三数取中
    int mid = Getmid(array, begin, end);
    //交换 mid -- begin
    Swap(array, mid, begin);
    //选取基准值
    int key = array[begin];
    //记录起始位置, 供最后交换时使用
    int start = begin;

    while (begin < end) {
        //必须先从后向前找, 否则可能导致大于基准值的数据交换到基准值的左边, 使排序混乱
        //从后向前找第一个小于key的值
        while (begin < end && array[end] >= key)
            end--;
        //从前向后找第一个大于key的值
        while (begin < end && array[begin] <= key)
            begin++;
        Swap(array, begin, end);
    }
    //交换基准值和相遇位置数据
    Swap(array, start, begin);
    return begin;
}

/*
 挖坑法 :
 1. 选取基准值
 2. 从后向前找第一个小于基准值的位置, 填上一次的坑
 3. 从前向后找第一个大于基准值的位置, 填上一次的坑, 并重复执行2,3
 4. 相遇位置的坑填基准值
*/
int partion2(int* array, int begin, int end) {
    //三数取中
    int mid = Getmid(array, begin, end);
    //交换 mid -- begin
    Swap(array, mid, begin);

    //选取基准值
    int key = array[begin];

    while (begin < end) {
        //从后向前找第一个小于key的位置
        while (begin < end && array[end] >= key)
            end--;
        //填坑
        array[begin] = array[end];
        //从前向后找第一个大于key的位置
        while (begin < end && array[begin] <= key)
            begin++;
        //填坑
        array[end] = array[begin];
    }
    //相遇位置填入基准值
    array[begin] = key;
    return begin;
}

/*
 前后指针法 :
 看前面的指针和后面的指针之间是否有大于基准值的数据
 前后指针连续 --> 中间没有大于基准值的数据
 不连续 --> 中间有大于基准值的数据
 大数据和新发现的小数据进行交换, 最终实现基准值左边都是小于基准值的数据, 右边都是大于基准值的数据
*/
int partion3(int* array, int begin, int end) {
    //三数取中
    int mid = Getmid(array, begin, end);
    //交换 mid -- begin
    Swap(array, mid, begin);

    //prev : 最后一个小于基准值的位置
    int prev = begin;
    //cur : 下一个小于基准值的位置
    int cur = prev + 1;
    //取基准值
    int key = array[begin];
    while (cur <= end) {
        if (array[cur] < key && ++prev != cur)
            Swap(array, cur, prev);
        ++cur;
    }
    //上面是简化版本
    //下面是具体分析了一波
   /*
    while (cur <= end) {
     if (array[cur] < key) {
    //当 cur位置小于key 并且前后指针不连续 :
    //需要prev++指向第一个大于基准值的数据, 然后与cur进行交换
    //所以无论前后指针连不连续, 只要cur找到新的小于基准值的数据, prev就需要++
    //所以下面就直接先++, 再判断指针是否连续

      //只要cur找到新的小于key的数据, prev++, 指向下一个位置
      prev++;
      //如果连续, 没有任何操作
      //如果不连续, 即prev != cur, 交换
      if (prev != cur)
       Swap(array, prev, cur);
     }
     //cur继续遍历
     cur++;
    }
   */
   //最后进行基准值和prev位置的交换
    Swap(array, prev, begin);
    return prev;
}

/*
时间复杂度：最好O(nlogn)  平均O(nlogn)  最坏O(n^2) -> [有序时最坏, 只是理论值, 要做优化, 不可能出现]
空间复杂度：O(logn) 函数调用栈     最坏 O(n) -> 不会出现
稳定性：不稳定
数据敏感：敏感
不优化情况下, 对有序序列进行快排 --> 退化成冒泡, 并且要调用n次递归, 很容易导致栈溢出
*/
//快速排序
void quickSort(int* array, int begin, int end) {
    if (begin >= end)
        return;
    //划分当前区间
    int keyPos = partion(array, begin, end);
    //int keyPos = partion2(array, begin, end);
    //int keyPos = partion3(array, begin, end);
    //划分子区间
    quickSort(array, begin, keyPos - 1);
    quickSort(array, keyPos + 1, end);
}


/*
时间复杂度 : 最坏O(n^2)  平均O(n^2)  最好O(n^2)
空间复杂度 : O(1)
稳定性 : 稳定
数据敏感性 :  不敏感
*/
//选择排序
//从左向右遍历未排序序列, 找到最值, 然后放在左边或者右边
void selectSort(int* arr, int n) {
    for (int i = 0; i < n; i++) {
        //start : 第一个待排序元素
        int start = i;
        //min : 最小值的位置
        int min = i;
        for (int j = start; j < n; j++) {
            //从start开始向后遍历, 找到最小的值
            if (arr[j] < arr[min])
                min = j;
        }
        Swap(arr, start, min);
    }
}
//第二种写法(改良版)
//一次同时取最大值和最小值, 时间性能大概提升一倍
void selectSort2(int* arr, int n) {
    //begin放最小值, end放最大值
    int begin = 0;
    int end = n - 1;

    while (begin < end) {
        //每一次选择最大值和最小值的位置
        //这里要写在循环里面, 如果在循环外面的话, 会出现min,max越界的情况
        int min = begin;
        int max = begin;
        for (int i = begin; i <= end; i++) {
            //找到最大值和最小值
            if (arr[i] < arr[min])
                min = i;
            if (arr[i] > arr[max])
                max = i;
        }
        //找到最大最小值后, 分别和end begin交换
        Swap(arr, begin, min);
        //因为先交换的是begin和最小值, 所以要考虑max和begin位置是不是一样
        //如果一样, 交换完后要更新max的位置: max = min (因为这里最大值被换到了最小值的位置上)
        if (max == begin)
            max = min;
        Swap(arr, end, max);
        begin++;
        end--;
    }
}


//大堆的调整
void shiftDown(int* arr, int n, int parent) {
    int child = 2 * parent + 1;
    while (child < n) {
        if (child + 1 < n && arr[child + 1] > arr[child])
            ++child;
        if (arr[child] > arr[parent]) {
            Swap(arr, child, parent);
            parent = child;
            child = 2 * parent + 1;
        }
        else
            break;
    }
}
//堆排序
void heapSort(int* arr, int n) {
    //建堆
    for (int i = (n - 2) / 2; i >= 0; --i) {
        shiftDown(arr, n, i);
    }
    //循环删除
    while (n) {
        Swap(arr, 0, n - 1);
        --n;
        shiftDown(arr, n, 0);
    }
}


//计数排序
void countSort(int* array, int n) {
    //统计范围
    int min = array[0];
    int max = array[0];
    for (int i = 0; i < n; i++) {
        if (array[i] > max)
            max = array[i];
        if (array[i] < min)
            min = array[i];
    }
    int range = max - min + 1;
    //开辅助空间, 进行计数, 初始化为0
    int* countArr = (int*)malloc(sizeof(int) * range);
    memset(countArr, 0, sizeof(int) * range);
    //统计次数, 遍历array
    for (int i = 0; i < n; i++) {
        countArr[array[i] - min]++;
    }
    //恢复数据, 遍历计数数组
    int idx = 0;
    for (int i = 0; i < range; i++) {
        while (countArr[i]-- != 0) {
            array[idx++] = i + min;
        }
    }
    free(countArr);
}


//合并 : 需要知道两个有序子序列的区间(3个参数确定) [begin, mid], [mid + 1, end]
void merge(int* array, int begin, int mid, int end, int* tmp) {
    //先确定两个区间
    int begin1 = begin;
    int end1 = mid;
    int begin2 = mid + 1;
    int end2 = end;
    //给一个辅助空间tmp的索引
    int idx = begin;
    //合并
    while (begin1 <= end1 && begin2 <= end2) {
        if (array[begin1] <= array[begin2])
            tmp[idx++] = array[begin1++];
        else
            tmp[idx++] = array[begin2++];
    }
    //检查有无剩余元素
    if (begin1 <= end1)
        memcpy(tmp + idx, array + begin1, sizeof(int) * (end1 - begin1 + 1));
    if (begin2 <= end2)
        memcpy(tmp + idx, array + begin2, sizeof(int) * (end2 - begin2 + 1));
    //把辅助空间的元素拷贝到原来的数组中
    memcpy(array + begin, tmp + begin, sizeof(int) * (end - begin + 1));
}
void mergeSortR(int* array, int begin, int end, int* tmp) {
    if (begin >= end)
        return;

    int mid = begin + (end - begin) / 2;
    //首先保证子区间有序, 进行子区间的排序
    mergeSortR(array, begin, mid, tmp);
    mergeSortR(array, mid + 1, end, tmp);
    //合并有序子区间
    merge(array, begin, mid, end, tmp);
}
/*
时间复杂度：O(nlogn)
空间复杂度：O(n)
稳定性：稳定
数据敏感：不敏感
*/
//归并排序
void mergeSort(int* array, int n) {
    int* tmp = (int*)malloc(sizeof(int) * n);
    mergeSortR(array, 0, n - 1, tmp);
    free(tmp);
}
void mergeSortNoR(int* array, int n) {
    int* tmp = (int*)malloc(sizeof(int) * n);
    //待合并区间的元素个数
    int k = 1;
    //多轮的归并
    while (k < n) {
        //一轮归并
        for (int i = 0; i < n; i += 2 * k) {
            //[begin, mid]  [mid + 1, end]
            int begin = i;
            int mid = i + k - 1;
            //判断mid是否越界
            if (mid >= n - 1)
                continue;
            int end = i + 2 * k - 1;
            //判断end是否越界
            if (end >= n)
                end = n - 1;
            merge(array, begin, mid, end, tmp);
        }
        k *= 2;
    }
}


int getMaxDate(int array[], int n) {
    int digit, max;
    digit = 0;
    max = array[0];
    for (int i = 1; i < n; i++) {
        if (array[i] > max)
            max = array[i];
    }
    while (max) {
        digit++;
        max /= 10;
    }
    return digit;
}

//基数排序
void radixSort(int array[], int n) {
    //创建临时数组
    int* tmp = new int[n];
    //位数：决定了排序趟数
    int digit = getMaxDate(array, n);
    //计数数组
    int count[10];
    //排序
    int r, i, d;
    for (r = 1; r <= digit; r++) {
        //重置计数数组
        memset(count, 0, 10 * sizeof(int));
        //把数据存储到临时数组
        memcpy(tmp, array, n * sizeof(int));
        d = i = 1;
        while (i < r) {
            i++;
            d *= 10;
        }
        for (i = 0; i < n; i++)
            count[(array[i] / d) % 10]++;
        for (i = 1; i < 10; i++)
            count[i] += count[i - 1];
        //数据回放
        for (i = n - 1; i >= 0; i--)
            array[--count[(tmp[i] / d) % 10]] = tmp[i];
    }
}


int main() {
    int n = 0;
    cin >> n;
    int* arr = new int[n];
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    //bubbleSort(arr, n);
    //insertSort(arr, n);
    //shellSort(arr, n);
    quickSort(arr, 0, n - 1);
    //selectSort2(arr, n);
    //heapSort(arr, n);
    //countSort(arr, n);
    //mergeSort(arr, n);
    //radixSort(arr, n);


    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";

    return 0;
}