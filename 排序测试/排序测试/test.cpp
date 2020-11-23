#include<iostream>

using namespace std;

//����
void Swap(int* arr, int left, int right) {
    int tmp = arr[left];
    arr[left] = arr[right];
    arr[right] = tmp;
}

//ð������
void bubbleSort(int* arr, int n) {
    while (n > 0) {
        //��һ�����
        // flag : 0 --> һ��ð��������û�з�������
        int flag = 0;
        //end : ���������䳤��
        // [0, end] Ϊ����������
        int end = n;
        //����δ��������, һ��ð������
        for (int i = 0; i < end - 1; i++) {
            // �Ƚ�����Ԫ��, �������ƶ�
            if (arr[i] > arr[i + 1]) {
                Swap(arr, i, i + 1);
                flag = 1;
            }
        }
        //flag = 0��ʾһ��ð����û�з�������, �������Ѿ�����, ������ǰ����
        if (flag == 0)
            break;
        //���������䳤�ȼ�һ
        n--;
    }
}


void insertSort(int* arr, int n) {
    for (int i = 1; i < n; i++) {
        //end ��ʾ��ǰ��Ҫ�����λ��
        //[0, end)������������
        int end = i;
        //��Ҫ�����Ԫ��
        int key = arr[end];
        //����end > 0, ���� =0 ��Ϊ����ȡend - 1��ʱ���Խ����� 
        while (end > 0 && arr[end - 1] > key) {
            //���λ�ò�����, endλ��Ԫ�غ���һλ
            arr[end] = arr[end - 1];
            //������ǰ����
            end--;
        }
        arr[end] = key;
    }
}

//ϣ������
//����һ��Ԥ����, �����в�������, �൱���Ƕ��ֵĲ�������
void shellSort(int* arr, int n) {
    //����
    int gap = n;
    //���ֲ�������
    while (gap > 1) {
        gap = gap / 2;
        //һ�β�������
        for (int i = 0; i < n - gap; i++) {
            //ͨ������gap�����߼�����
            //ͬ���Ԫ�ؽ��в�������
            //��ͬ���Ԫ�ؽ�������
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


//����ȡ��
//�ǿ���������Ż�����, ���԰��м�ֵ������׼ֵ, ʹ�����������뻯
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
 hora�� :
 1. ȡ�����������һ��Ԫ��Ϊ��׼ֵ
 2. �Ӵ���������ĩβ��ǰ�ҵ�һ��С�ڻ�׼ֵ��λ��
 3. �Ӵ��������俪ͷ����ҵ�һ�����ڻ�׼ֵ��λ��
 4. ����2,3�ҵ�λ�õ�����, �ظ�ִ��234
 5.�鵽��������λ��, ��������λ�úͻ�׼ֵ����, ���һ�ֻ���
*/
int partion(int* array, int begin, int end) {
    //����ȡ��
    int mid = Getmid(array, begin, end);
    //���� mid -- begin
    Swap(array, mid, begin);
    //ѡȡ��׼ֵ
    int key = array[begin];
    //��¼��ʼλ��, ����󽻻�ʱʹ��
    int start = begin;

    while (begin < end) {
        //�����ȴӺ���ǰ��, ������ܵ��´��ڻ�׼ֵ�����ݽ�������׼ֵ�����, ʹ�������
        //�Ӻ���ǰ�ҵ�һ��С��key��ֵ
        while (begin < end && array[end] >= key)
            end--;
        //��ǰ����ҵ�һ������key��ֵ
        while (begin < end && array[begin] <= key)
            begin++;
        Swap(array, begin, end);
    }
    //������׼ֵ������λ������
    Swap(array, start, begin);
    return begin;
}

/*
 �ڿӷ� :
 1. ѡȡ��׼ֵ
 2. �Ӻ���ǰ�ҵ�һ��С�ڻ�׼ֵ��λ��, ����һ�εĿ�
 3. ��ǰ����ҵ�һ�����ڻ�׼ֵ��λ��, ����һ�εĿ�, ���ظ�ִ��2,3
 4. ����λ�õĿ����׼ֵ
*/
int partion2(int* array, int begin, int end) {
    //����ȡ��
    int mid = Getmid(array, begin, end);
    //���� mid -- begin
    Swap(array, mid, begin);

    //ѡȡ��׼ֵ
    int key = array[begin];

    while (begin < end) {
        //�Ӻ���ǰ�ҵ�һ��С��key��λ��
        while (begin < end && array[end] >= key)
            end--;
        //���
        array[begin] = array[end];
        //��ǰ����ҵ�һ������key��λ��
        while (begin < end && array[begin] <= key)
            begin++;
        //���
        array[end] = array[begin];
    }
    //����λ�������׼ֵ
    array[begin] = key;
    return begin;
}

/*
 ǰ��ָ�뷨 :
 ��ǰ���ָ��ͺ����ָ��֮���Ƿ��д��ڻ�׼ֵ������
 ǰ��ָ������ --> �м�û�д��ڻ�׼ֵ������
 ������ --> �м��д��ڻ�׼ֵ������
 �����ݺ��·��ֵ�С���ݽ��н���, ����ʵ�ֻ�׼ֵ��߶���С�ڻ�׼ֵ������, �ұ߶��Ǵ��ڻ�׼ֵ������
*/
int partion3(int* array, int begin, int end) {
    //����ȡ��
    int mid = Getmid(array, begin, end);
    //���� mid -- begin
    Swap(array, mid, begin);

    //prev : ���һ��С�ڻ�׼ֵ��λ��
    int prev = begin;
    //cur : ��һ��С�ڻ�׼ֵ��λ��
    int cur = prev + 1;
    //ȡ��׼ֵ
    int key = array[begin];
    while (cur <= end) {
        if (array[cur] < key && ++prev != cur)
            Swap(array, cur, prev);
        ++cur;
    }
    //�����Ǽ򻯰汾
    //�����Ǿ��������һ��
   /*
    while (cur <= end) {
     if (array[cur] < key) {
    //�� curλ��С��key ����ǰ��ָ�벻���� :
    //��Ҫprev++ָ���һ�����ڻ�׼ֵ������, Ȼ����cur���н���
    //��������ǰ��ָ����������, ֻҪcur�ҵ��µ�С�ڻ�׼ֵ������, prev����Ҫ++
    //���������ֱ����++, ���ж�ָ���Ƿ�����

      //ֻҪcur�ҵ��µ�С��key������, prev++, ָ����һ��λ��
      prev++;
      //�������, û���κβ���
      //���������, ��prev != cur, ����
      if (prev != cur)
       Swap(array, prev, cur);
     }
     //cur��������
     cur++;
    }
   */
   //�����л�׼ֵ��prevλ�õĽ���
    Swap(array, prev, begin);
    return prev;
}

/*
ʱ�临�Ӷȣ����O(nlogn)  ƽ��O(nlogn)  �O(n^2) -> [����ʱ�, ֻ������ֵ, Ҫ���Ż�, �����ܳ���]
�ռ临�Ӷȣ�O(logn) ��������ջ     � O(n) -> �������
�ȶ��ԣ����ȶ�
�������У�����
���Ż������, ���������н��п��� --> �˻���ð��, ����Ҫ����n�εݹ�, �����׵���ջ���
*/
//��������
void quickSort(int* array, int begin, int end) {
    if (begin >= end)
        return;
    //���ֵ�ǰ����
    int keyPos = partion(array, begin, end);
    //int keyPos = partion2(array, begin, end);
    //int keyPos = partion3(array, begin, end);
    //����������
    quickSort(array, begin, keyPos - 1);
    quickSort(array, keyPos + 1, end);
}


/*
ʱ�临�Ӷ� : �O(n^2)  ƽ��O(n^2)  ���O(n^2)
�ռ临�Ӷ� : O(1)
�ȶ��� : �ȶ�
���������� :  ������
*/
//ѡ������
//�������ұ���δ��������, �ҵ���ֵ, Ȼ�������߻����ұ�
void selectSort(int* arr, int n) {
    for (int i = 0; i < n; i++) {
        //start : ��һ��������Ԫ��
        int start = i;
        //min : ��Сֵ��λ��
        int min = i;
        for (int j = start; j < n; j++) {
            //��start��ʼ������, �ҵ���С��ֵ
            if (arr[j] < arr[min])
                min = j;
        }
        Swap(arr, start, min);
    }
}
//�ڶ���д��(������)
//һ��ͬʱȡ���ֵ����Сֵ, ʱ�����ܴ������һ��
void selectSort2(int* arr, int n) {
    //begin����Сֵ, end�����ֵ
    int begin = 0;
    int end = n - 1;

    while (begin < end) {
        //ÿһ��ѡ�����ֵ����Сֵ��λ��
        //����Ҫд��ѭ������, �����ѭ������Ļ�, �����min,maxԽ������
        int min = begin;
        int max = begin;
        for (int i = begin; i <= end; i++) {
            //�ҵ����ֵ����Сֵ
            if (arr[i] < arr[min])
                min = i;
            if (arr[i] > arr[max])
                max = i;
        }
        //�ҵ������Сֵ��, �ֱ��end begin����
        Swap(arr, begin, min);
        //��Ϊ�Ƚ�������begin����Сֵ, ����Ҫ����max��beginλ���ǲ���һ��
        //���һ��, �������Ҫ����max��λ��: max = min (��Ϊ�������ֵ����������Сֵ��λ����)
        if (max == begin)
            max = min;
        Swap(arr, end, max);
        begin++;
        end--;
    }
}


//��ѵĵ���
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
//������
void heapSort(int* arr, int n) {
    //����
    for (int i = (n - 2) / 2; i >= 0; --i) {
        shiftDown(arr, n, i);
    }
    //ѭ��ɾ��
    while (n) {
        Swap(arr, 0, n - 1);
        --n;
        shiftDown(arr, n, 0);
    }
}


//��������
void countSort(int* array, int n) {
    //ͳ�Ʒ�Χ
    int min = array[0];
    int max = array[0];
    for (int i = 0; i < n; i++) {
        if (array[i] > max)
            max = array[i];
        if (array[i] < min)
            min = array[i];
    }
    int range = max - min + 1;
    //�������ռ�, ���м���, ��ʼ��Ϊ0
    int* countArr = (int*)malloc(sizeof(int) * range);
    memset(countArr, 0, sizeof(int) * range);
    //ͳ�ƴ���, ����array
    for (int i = 0; i < n; i++) {
        countArr[array[i] - min]++;
    }
    //�ָ�����, ������������
    int idx = 0;
    for (int i = 0; i < range; i++) {
        while (countArr[i]-- != 0) {
            array[idx++] = i + min;
        }
    }
    free(countArr);
}


//�ϲ� : ��Ҫ֪���������������е�����(3������ȷ��) [begin, mid], [mid + 1, end]
void merge(int* array, int begin, int mid, int end, int* tmp) {
    //��ȷ����������
    int begin1 = begin;
    int end1 = mid;
    int begin2 = mid + 1;
    int end2 = end;
    //��һ�������ռ�tmp������
    int idx = begin;
    //�ϲ�
    while (begin1 <= end1 && begin2 <= end2) {
        if (array[begin1] <= array[begin2])
            tmp[idx++] = array[begin1++];
        else
            tmp[idx++] = array[begin2++];
    }
    //�������ʣ��Ԫ��
    if (begin1 <= end1)
        memcpy(tmp + idx, array + begin1, sizeof(int) * (end1 - begin1 + 1));
    if (begin2 <= end2)
        memcpy(tmp + idx, array + begin2, sizeof(int) * (end2 - begin2 + 1));
    //�Ѹ����ռ��Ԫ�ؿ�����ԭ����������
    memcpy(array + begin, tmp + begin, sizeof(int) * (end - begin + 1));
}
void mergeSortR(int* array, int begin, int end, int* tmp) {
    if (begin >= end)
        return;

    int mid = begin + (end - begin) / 2;
    //���ȱ�֤����������, ���������������
    mergeSortR(array, begin, mid, tmp);
    mergeSortR(array, mid + 1, end, tmp);
    //�ϲ�����������
    merge(array, begin, mid, end, tmp);
}
/*
ʱ�临�Ӷȣ�O(nlogn)
�ռ临�Ӷȣ�O(n)
�ȶ��ԣ��ȶ�
�������У�������
*/
//�鲢����
void mergeSort(int* array, int n) {
    int* tmp = (int*)malloc(sizeof(int) * n);
    mergeSortR(array, 0, n - 1, tmp);
    free(tmp);
}
void mergeSortNoR(int* array, int n) {
    int* tmp = (int*)malloc(sizeof(int) * n);
    //���ϲ������Ԫ�ظ���
    int k = 1;
    //���ֵĹ鲢
    while (k < n) {
        //һ�ֹ鲢
        for (int i = 0; i < n; i += 2 * k) {
            //[begin, mid]  [mid + 1, end]
            int begin = i;
            int mid = i + k - 1;
            //�ж�mid�Ƿ�Խ��
            if (mid >= n - 1)
                continue;
            int end = i + 2 * k - 1;
            //�ж�end�Ƿ�Խ��
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

//��������
void radixSort(int array[], int n) {
    //������ʱ����
    int* tmp = new int[n];
    //λ������������������
    int digit = getMaxDate(array, n);
    //��������
    int count[10];
    //����
    int r, i, d;
    for (r = 1; r <= digit; r++) {
        //���ü�������
        memset(count, 0, 10 * sizeof(int));
        //�����ݴ洢����ʱ����
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
        //���ݻط�
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