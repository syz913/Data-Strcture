#include<iostream>
#include<vector>
#include<stack>

#define N 20

using namespace std;

void swap(int& a, int& b) {
	int temp = a;
	a = b; b = temp;
}
//˫��ð������
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
	//ѡȡ����ֵ,����ѡ��ǰ���е����һ����¼��Ϊ����ֵ
	int t = a[r];
	for (;;) {
		//�����е���������ɨ�����ݣ�ֱ���ҵ�һ���ȿ���ֵ�����a_i
		while (a[++i] < t);
		//�����е���������ɨ�裬ֱ���ҵ�һ���ȿ���ֵС����a_j
		while (t < a[--j]) if (j == l) break;
		//��ʱ,a_j<t<a_i,����ai��aj,?����������ɨ��ͽ������̣�ֱ��i>=j
		if (i >= j) break;
		//��ʱ��i�\1����С�ڵ��ڿ���ֵt��iλ�����Ҵ��ڵ���t
		//����a_i��a_r�����˳�����
		swap(a[i], a[j]);
	}
	swap(a[i], a[r]);
	return i;
}
//�ݹ��������
void QuickSort(vector<int>& a, int l, int r) {
	int i;
	if (r <= l) return;//�߽��ж�,�ݹ��˳�����
	//ѡȡ����ֵ,������ֵ�����ڶ��еĺ��ʵ�λ����,��λ
	// �ô����i��.
	//ͬʱ��С�ڵ��ڸ�ֵ�ļ�¼���ڸ�λ�õ����;?���ڵ�
	// �ڵķ��ڸ�λ���ұ�
	i = partition(a, l, r);
	//�ݹ��i��ߵ���������������
	QuickSort(a, l, i - 1);
	//�ݹ��i�ұߵ���������������
	QuickSort(a, i + 1, r);
}
//�ǵݹ��������
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
		//�Ƚ��������еĳ���,���������䷶Χ��ѹ��ջ�к�,?��
		//�������е�����ѹ��ջ
		//�Ա�֤ջ����ȱȽ�С
		if (i - l > r - i) {
			push_interval(s, l, i - 1); push_interval(s, i + 1, r);
		}
		else {
			push_interval(s, i + 1, r); push_interval(s, l, i - 1);
		}
	}
}
//�򵥹鲢,��һ��������ٹ鲢,ע����Բ��������������
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

//�鲢����
void merge1(vector<int>&a, int l, int m, int r) {
	//2·�鲢����
	int i, j;
	//�����γ�һ�����У���벿�������Ұ벿�ֽ���
	static int aux[N];
	for (i = m + 1; i > l; i--) aux[i - 1] = a[i - 1];
	for (j = m; j < r; j++) aux[r + m - j] = a[j + 1];
	//��aux�����е��������й鲢��a����
	for (int k = l; k <= r; k++)
		if (aux[j] < aux[i]) a[k] = aux[j--];
		else a[k] = aux[i++];
}

void MergeSort(vector<int>&a, int l, int r) {
	//�ݹ��˳�����:�����������ֻ��һ����¼,?ֱ�ӷ���
	//ͬʱ,Ҳ��һ���������������ж�����
	if (r <= l) return;
	//�����������а�����λ�û���Ϊ��������������
	int m = (r + l) / 2;
	//�����е�ǰ��ν��еݹ�Ĺ鲢����
	MergeSort(a, l, m);
	//�����еĺ��ν��еݹ�Ĺ鲢����
	MergeSort(a, m + 1, r);
	//���������ź�������н��й鲢
	for(int i = 0; i <= r; i ++)
		cout<<a[i] << " ";
	cout << endl;
	merge1(a, l, m, r);
}
//ϣ������
void ShellSort(vector<int>&a){
    int currentSize = a.size();
    int gap = a.size()/2;
    int temp, j;
    while(gap != 0){//ѭ����ֱ��gapΪ��
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
	cout << "input numbers(end with letter)��";
	while (cin >> num) a.push_back(num);
	//MergeSort(a, 0, a.size() - 1);
	ShellSort(a);
	for (int i = 0; i < a.size(); i++)
		cout << a[i] << " ";
	return 0;
}
