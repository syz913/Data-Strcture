#include<iostream>
#include<vector>
#include<stack>

using namespace std;

void swap(int&a, int&b){
	int temp = a; a = b; b = temp;
}
//√∞≈› 
void sort1(int a[], int n){
	for(int i = 0; i < n; i ++)
		for(int j = n - 1; j > i; j --)
			if(a[j] < a[j - 1]) swap(a[j], a[j - 1]);
	for(int i = 0; i < n; i ++) cout << a[i] << " ";
}
//À´œÚ√∞≈›(º¶Œ≤æ∆£©
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
//—°‘Ò
void sort2(int a[], int n){
	for(int i = 0; i < n; i ++){
		int min = i;
		for(int j = i + 1; j < n; j ++){
			if(a[j] < a[i]) {
				min = j;
			}
		} 
		swap(a[i], a[min]);
	}
	for(int i = 0; i < n; i ++) cout << a[i] << " ";
} 
//≤Â»Î
void sort3(int a[], int n){
	int j, t;
	for(int i = 1; i < n; i ++){
		for(j = i, t = a[i]; j > 0 && t < a[j - 1]; j --){
			a[j] = a[j - 1];
		}
		a[j] = t;
	}
	for(int i = 0; i < n; i ++) cout << a[i] << " ";
} 
//πÈ≤¢
void merge(vector<int>&a, int l, int m, int r){
	int i, j;
	static int aux[100];
	for(i = m + 1; i > l; i --) aux[i - 1] = a[i - 1];
	for(j = m; j < r; j ++) aux[r + m - j] = a[j + 1];
//	for(i = m; i >= 0; i --) aux[i] = a[i];
//	for(j = m + 1; j <= r; j ++) aux[r + m - j + 1] = a[j];
//	i ++; j --;
	for(int k = l; k <= r; k ++)
		if(aux[j] < aux[i]) a[k] = aux[j --];
		else a[k] = aux[i ++];
}
//◊‘∂•œÚœ¬πÈ≤¢ 
void mergesort(vector<int>&a, int l, int r){
	if(r <= l) return;
	int m = (l + r)/2;
	mergesort(a, l, m);
	mergesort(a, m + 1, r);
	merge(a, l, m, r);
}
//◊‘µ◊œÚ…œπÈ≤¢ 
void merger(vector<int>&a, int l, int r){
	for(int m = 1; m <= r - 1; m += m)
		for(int i = l; i <= r - m; i += m + m)
			merge(a, i, i + m - 1, min(i + m + m - 1, r));
}
//øÏ≈≈
int partition(vector<int>&a, int l, int r){
	int i = l - 1, j = r;
	int t = a[r];
	for(;;){
		while(a[++ i] < t);
		while(t < a[--j]) if(j == l) break;
		if(i >= j) break;
		swap(a[i], a[j]);
	}
	swap(a[i], a[r]);
	return i;
}
void quick(vector<int>&a, int l, int r){
	int i;
	if(r <= l) return;
	i = partition(a, l, r);
	quick(a, l, i - 1);
	quick(a, i + 1, r);
} 
void push_interval(stack<int>&s, int a, int b){
	s.push(b); s.push(a);
}
void quick_s(vector<int>&a, int l, int r){
	int i;
	stack<int>s; push_interval(s, l, r);
	while(!s.empty()){
		l = s.top(); s.pop();
		r = s.top(); s.pop();
		if(r <= l) continue;
		i = partition(a, l, r);
		if(i - l > r - i){
			push_interval(s, l, i - 1); push_interval(s, i + 1, r);
		}
		else{
			push_interval(s, i + 1, r); push_interval(s, l, i - 1);
		}
	}
}
//œ£∂˚≈≈–Ú
void shell(vector<int>&a){
	int n = a.size(), j;
	int gap = n/2;
	while(gap != 0){
		for(int i = gap; i < n; i ++){
			int t = a[i];
			for(j = i; j >= gap && a[j - gap] > t; j = j - gap)
				a[j] = a[j - gap];
			a[j] = t;
		}
		gap/=2;
	}
} 
//∂—≈≈–Ú
void sift_up(vector<int>&a, int start){
	int i = start, j = (i - 1)/2;
	int temp = a[i];
	while(j > 0){
		if(a[j] < temp) break;
		else{
			a[i] = a[j]; i = j; j = (j - 1)/2;
		}
	}
	a[i] = temp;
}
void sift_down(vector<int>&a, int start, int m){
	int i = start, j = 2*i + 1;
	int temp = a[i];
	while(j <= m){
		if(j < m && a[j] > a[j + 1]) j ++;
		if(temp <= a[j]) break;
		else{
			a[i] = a[j]; i = j; j = 2*j + 1;
		}
	}
	a[i] = temp;
}
void heap_sort(vector<int>&a){
	int t; 
	//Ω®¡¢∂— 
	for(int i = (a.size() - 2)/2; i >= 0; i --) sift_down(a, i, a.size() - 1);
	for(int i = a.size() - 1; i > 0; i --){
		swap(a[0], a[i]); sift_down(a, 0, i - 1);
	}
}

int main(){
	vector<int> a;
	int num;
	cout << "input numbers(end with letter)£∫";
	while (cin >> num) a.push_back(num);
	heap_sort(a);
	for(int i = 0; i < a.size(); i ++) cout << a[i] << " ";
	return 0;
} 
