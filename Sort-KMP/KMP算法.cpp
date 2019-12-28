#include<iostream>
#include<string>

using namespace std; 

int BF_Find(string& s,string& t){
	int i=0,j=0,count=0;
	int k = 0;
	while(i<s.size()){
		
		if(s.at(i)==t.at(j)){
			i++; j++;
			count++;}
	   else{
		   i = i - j + 1;
		   j=0;
		   count=0;
		}
		if(count==t.size()){
			cout<<"模式匹配成功,起始位置是:"<<i-count+1<<endl;
			return (i-count+1);
		}	   
	}
    cout<<"字符串匹配失败!"<<endl;
	return 0;
}

void GetFailure(string needle, int f[])
//求匹配串pat的失效函数值
{
    f[0]=-1;                             // 初始f[0]的值为-1
    int j = 0, k = -1;      
    while (j < needle.size() - 1)
        if (k == -1 || needle[k] == needle[j])    
            f[++j]=++k;//  f[1]=0,如果相同就等于原子串长度+1
        else                             // pat[k]与pat[j]不匹配
            k = f[k];                    // 寻求新的匹配字符
    for(int i = 0; i < needle.size(); i ++)
    	cout<<f[i]<<" ";
}

void preprocessing(string haystack, string needle, int Next[]){
    int m = needle.size();
    if(m == 0) return;
    for(int i = 0, j = Next[0] = -1; i < m - 1;){
        for(; j > -1 && needle[i] != needle[j];)
            j = Next[j];
        i ++; j ++;
        if(needle[i] == needle[j])
            Next[i] = Next[j];
        else Next[i] = j;
    }
    for(int i = 0; i < m; i ++)
    	cout<<Next[i]<<" ";
}
int strStr(string haystack, string needle) {
    int m = needle.size(), n = haystack.size();
    if(m == 0) return 0;
    if(n == 0 && m != 0) return -1;
    int i, j, Next[n];
    preprocessing(haystack, needle, Next);
    for(i = j = 0; j < n;){
        for(; i > -1 && needle[i] != haystack[j];)
            i = Next[i];
        i ++; j ++;
        if(i >= m)
            return j - i;
    }
    return -1;
}

int main(){
	string haystack, needle;
	//cin>>haystack;
	cin>>needle;
	int f[needle.size()];
	cout<<"不带优化的Next数组为：";
	GetFailure(needle, f);
	cout<<endl;
	int Next[needle.size()];
	cout<<"Next数组为：";
	preprocessing(haystack, needle, Next);
	cout<<endl;
	cout<<"子串的起始位置为："<<strStr(haystack, needle); 
	return 0;
}
//ps:不带优化的部分已经有详解 ， 带优化的 就是先求出不带优化的部分，
//然后进行比较 ，如果p[i]=p[j],把Next[i]赋值Next[j]就好了 
