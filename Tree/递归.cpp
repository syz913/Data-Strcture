#include<iostream>
#include<math.h>
#include<stack>

#define N 100
using namespace std;

struct node{
        char a, b, c;
		int n;
        node(int m, char x, char y, char z) :n(m), a(x), b(y), c(z) {}
}; //�����ڵ� 
//��ŵ������ݹ�ⷨ 
void Hanoi(int n, char A, char B, char C){
	if(n == 1) cout<<"move "<< A <<" to "<< C <<endl;
	else{
		Hanoi(n - 1, A, C, B);
		cout<<"move "<< A <<" to "<< C <<endl;
		Hanoi(n - 1, B, A, C);
	}
}
//Hanoi�ķǵݹ�ⷨ
void Hanoi_n(int n){
	stack<node>s;
    s.push(node(n, 'a', 'b', 'c'));
    while (!s.empty()){
        node t = s.top();
        s.pop();//֮����pop��������Ϊn>1�Ĳ����Ѿ�����һ��n-1�����棬����û��Ҫ����Ҫ����������n == 1,ֱ��������ã�û��Ҫ�ٴ���
        if (t.n == 1) printf("%c -> %c\n", t.a, t.c);
        else{
            s.push(node(t.n - 1, t.b, t.a, t.c));
            s.push(node(1, t.a, t.b, t.c));
            s.push(node(t.n - 1, t.a, t.c, t.b));//����ջ���ص㣬�����Ƚ��еĲ����ѹ��ջ
        }
    }
} 
//akm�����ĵݹ�д��
int akm(int m, int n){
	if(m == 0) return n + 1;
	else if(m != 0 && n == 0) return akm(m - 1, 1);
	else return akm(m - 1, akm(m, n - 1));
} 
//akm�����ķǵݹ�д��
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
//n�ʺ����� 
int n;   
int sum = 0;
int x[N];


int place(int k){
	int i;
	for (i = 1; i < k; i++)
		if (abs(k - i) == abs(x[k] - x[i]) || x[k] == x[i])
			return 0;
	return 1;
//abs(k - i) == abs(x[k] - x[i])�ĺ������о���о���ȣ��ʴ�ʱ����Խ��ߵ�����
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
		}//����Ѱ�ң������ڣ��������������һ�еĻʺ�
                 //����֪����t�����кţ�x[t]�����к�
	return sum;
}

int main(){
//	int m, n;
//	char A = 'A', B = 'B', C = 'C';
//	while(n < 4){
//		cin>>m>>n;
//		cout<<"�ݹ�ⷨ��"<<endl;
//	//	Hanoi(n, A, B, C);
//		cout<<akm(m,n)<<endl;
//		cout<<"�ǵݹ�ⷨ��"<<endl;
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
