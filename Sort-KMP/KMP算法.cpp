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
			cout<<"ģʽƥ��ɹ�,��ʼλ����:"<<i-count+1<<endl;
			return (i-count+1);
		}	   
	}
    cout<<"�ַ���ƥ��ʧ��!"<<endl;
	return 0;
}

void GetFailure(string needle, int f[])
//��ƥ�䴮pat��ʧЧ����ֵ
{
    f[0]=-1;                             // ��ʼf[0]��ֵΪ-1
    int j = 0, k = -1;      
    while (j < needle.size() - 1)
        if (k == -1 || needle[k] == needle[j])    
            f[++j]=++k;//  f[1]=0,�����ͬ�͵���ԭ�Ӵ�����+1
        else                             // pat[k]��pat[j]��ƥ��
            k = f[k];                    // Ѱ���µ�ƥ���ַ�
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
	cout<<"�����Ż���Next����Ϊ��";
	GetFailure(needle, f);
	cout<<endl;
	int Next[needle.size()];
	cout<<"Next����Ϊ��";
	preprocessing(haystack, needle, Next);
	cout<<endl;
	cout<<"�Ӵ�����ʼλ��Ϊ��"<<strStr(haystack, needle); 
	return 0;
}
//ps:�����Ż��Ĳ����Ѿ������ �� ���Ż��� ��������������Ż��Ĳ��֣�
//Ȼ����бȽ� �����p[i]=p[j],��Next[i]��ֵNext[j]�ͺ��� 
