#include<iostream>
#include<math.h>
#include<stack>

#define N 100
using namespace std;

struct node{
        char a, b, c;
		int n;
        node(int m, char x, char y, char z) :n(m), a(x), b(y), c(z) {}
}; //构建节点 
//汉诺塔问题递归解法 
void Hanoi(int n, char A, char B, char C){
	if(n == 1) cout<<"move "<< A <<" to "<< C <<endl;
	else{
		Hanoi(n - 1, A, C, B);
		cout<<"move "<< A <<" to "<< C <<endl;
		Hanoi(n - 1, B, A, C);
	}
}
//Hanoi的非递归解法
void Hanoi_n(int n){
	stack<node>s;
    s.push(node(n, 'a', 'b', 'c'));
    while (!s.empty()){
        node t = s.top();
        s.pop();//之所以pop掉，是因为n>1的部分已经被下一级n-1所代替，所以没必要再需要，并且若是n == 1,直接输出即好，没必要再存留
        if (t.n == 1) printf("%c -> %c\n", t.a, t.c);
        else{
            s.push(node(t.n - 1, t.b, t.a, t.c));
            s.push(node(1, t.a, t.b, t.c));
            s.push(node(t.n - 1, t.a, t.c, t.b));//由于栈的特点，所以先进行的步骤后压入栈
        }
    }
} 
//akm函数的递归写法
int akm(int m, int n){
	if(m == 0) return n + 1;
	else if(m != 0 && n == 0) return akm(m - 1, 1);
	else return akm(m - 1, akm(m, n - 1));
} 
//akm函数的非递归写法
int akm_n(int m, int n){
	stack<int> s;
	s.push(m);
	while(!s.empty()){
		m = s.top(); s.pop();
		if(m == 0) n =  n + 1;
		else if(m != 0 && n == 0){
			m = m - 1; n = 1; s.push(m);
		}
		else{
			n = n - 1;
			s.push(m - 1); s.push(m); 
		}
	}
	return n;
} 
//n皇后问题 
int n;   
int sum = 0;
int x[N];


int place(int k){
	int i;
	for (i = 1; i < k; i++)
		if (abs(k - i) == abs(x[k] - x[i]) || x[k] == x[i])
			return 0;
	return 1;
//abs(k - i) == abs(x[k] - x[i])的含义是行距和列距相等，故此时代表对角线的情形
}


int queen(int t){
	if (t > n && n > 0)   
		sum++;
	else
		for (int i = 1; i <= n; i++)
		{
			x[t] = i;   
			if (place(t)) 
				queen(t + 1);
		}//逐列寻找，若存在，则接下来安放下一行的皇后
                 //可以知道，t代表行号，x[t]代表列号
	return sum;
}

int main(){
//	int m, n;
//	char A = 'A', B = 'B', C = 'C';
//	while(n < 4){
//		cin>>m>>n;
//		cout<<"递归解法："<<endl;
//	//	Hanoi(n, A, B, C);
//		cout<<akm(m,n)<<endl;
//		cout<<"非递归解法："<<endl;
//		//Hanoi_n(n);
//		cout<<akm_n(m,n)<<endl;
	//}
	int t;
	cin >> n;
	t = queen(1);
	if (n == 0) t = 0;
	cout << t << endl;
	return 0;
}
