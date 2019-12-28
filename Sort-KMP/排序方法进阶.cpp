#include<iostream>
#include<vector>
#include<stack>

#define N 20

using namespace std;

void swap(int& a, int& b) {
	int temp = a;
	a = b; b = temp;
}
//双向冒泡排序
void Bubble_sort(vector<int>& a) {
	int n = a.size();
	int low = 0, high = n - 1;
	bool exchange;
	while (low < high) {
		exchange = false;
		for (int i = low; i < high; i++) {
			if (a[i] > a[i + 1]) swap(a[i], a[i + 1]);
			exchange = true;
		}
		high--;
		for (int i = high; i > low; i--) {
			if (a[i] < a[i - 1]) swap(a[i], a[i - 1]);
			exchange = true;
		}
		if (exchange == false) return;
		low++;
	}
}
int partition(vector<int>&a, int l, int r) {
	int i = l - 1, j = r;
	//选取控制值,这里选择当前序列的最后一个记录作为控制值
	int t = a[r];
	for (;;) {
		//从序列的最左向右扫描数据，直到找到一个比控制值大的项a_i
		while (a[++i] < t);
		//从序列的最右向左扫描，直到找到一个比控制值小的项a_j
		while (t < a[--j]) if (j == l) break;
		//此时,a_j<t<a_i,交换ai和aj,?继续上述的扫描和交换过程，直到i>=j
		if (i >= j) break;
		//这时，i‐1以左小于等于控制值t，i位置以右大于等于t
		//交换a_i和a_r，并退出函数
		swap(a[i], a[j]);
	}
	swap(a[i], a[r]);
	return i;
}
//递归快速排序
void QuickSort(vector<int>& a, int l, int r) {
	int i;
	if (r <= l) return;//边界判定,递归退出条件
	//选取控制值,并将该值放置在队列的合适的位置上,该位
	// 置存放在i中.
	//同时将小于等于该值的记录放在该位置的左边;?大于等
	// 于的放在该位置右边
	i = partition(a, l, r);
	//递归对i左边的序列做快速排序
	QuickSort(a, l, i - 1);
	//递归对i右边的序列做快速排序
	QuickSort(a, i + 1, r);
}
//非递归快速排序
void push_interval(stack<int>&s, int a, int b) {
	s.push(b); s.push(a);
}

void QuickSort_S(vector<int>&a, int l, int r) {
	stack<int>s; int i;
	push_interval(s, l, r);
	while (!s.empty()) {
		l = s.top(); s.pop();
		r = s.top(); s.pop();
		if (r <= l) continue;
		i = partition(a, l, r);
		//比较两个序列的长度,将长的区间范围先压入栈中后,?再
		//将短序列的区间压进栈
		//以保证栈的深度比较小
		if (i - l > r - i) {
			push_interval(s, l, i - 1); push_interval(s, i + 1, r);
		}
		else {
			push_interval(s, i + 1, r); push_interval(s, l, i - 1);
		}
	}
}
//简单归并,将一个数组拆开再归并,注意可以拆成两个有序数组
void merge(vector<int>&a, int l, int m, int r) {
	vector<int> a1, b;
	for(int i = l; i <= r; i ++){
		if(i <= m) a1.push_back(a[i]);
		if(i > m) b.push_back(a[i]);
	}
	for(int i = 0, j = 0, k = l; k <= r; k ++){
		if(i == m + 1){a[k] = b[j ++]; continue;}
		if(j == r-m){a[k] = a1[i ++]; continue;}
		a[k] = (a1[i] < b[j]) ? a1[i ++]:b[j ++];
	}
}

//归并排序
void merge1(vector<int>&a, int l, int m, int r) {
	//2路归并过程
	int i, j;
	//重新形成一个序列，左半部分升序，右半部分降序
	static int aux[N];
	for (i = m + 1; i > l; i--) aux[i - 1] = a[i - 1];
	for (j = m; j < r; j++) aux[r + m - j] = a[j + 1];
	//将aux数组中的两个序列归并到a数组
	for (int k = l; k <= r; k++)
		if (aux[j] < aux[i]) a[k] = aux[j--];
		else a[k] = aux[i++];
}

void MergeSort(vector<int>&a, int l, int r) {
	//递归退出条件:如果区间内已只有一个记录,?直接返回
	//同时,也是一个参数合理与否的判断条件
	if (r <= l) return;
	//将待排序序列按中心位置划分为两个待排序序列
	int m = (r + l) / 2;
	//对序列的前半段进行递归的归并排序
	MergeSort(a, l, m);
	//对序列的后半段进行递归的归并排序
	MergeSort(a, m + 1, r);
	//对两个已排好序的序列进行归并
	for(int i = 0; i <= r; i ++)
		cout<<a[i] << " ";
	cout << endl;
	merge1(a, l, m, r);
}
//希尔排序
void ShellSort(vector<int>&a){
    int currentSize = a.size();
    int gap = a.size()/2;
    int temp, j;
    while(gap != 0){//循环，直到gap为零
        for(int i = gap; i < currentSize; i ++){
            temp = a[i];
            for(j = i; j >= gap; j-= gap)
                if(temp < a[j - gap])
                    a[j] = a[j - gap];
                else break;
            a[j] = temp;
        }
        gap = gap/2;
    }
}
int main() {
	vector<int> a;
	int num;
	cout << "input numbers(end with letter)：";
	while (cin >> num) a.push_back(num);
	//MergeSort(a, 0, a.size() - 1);
	ShellSort(a);
	for (int i = 0; i < a.size(); i++)
		cout << a[i] << " ";
	return 0;
}
