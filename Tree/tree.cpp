#include<iostream>
#include<stack>
#include<queue> 

using namespace std;

struct TreeNode{
	int val;
	TreeNode*left, *right;
}; 
//前序建立树 
void Create(TreeNode*&root){
	int num; cin >> num;
	TreeNode*p = new TreeNode;
	p->val = num; 
	if(num == 0){
		p = NULL; return;
	}
	root = p; root->left = NULL; root->right = NULL;
	Create(root->left);
	Create(root->right);
}
//前序递归 
void pre(TreeNode*root){
	if(root == NULL) return;
	else{
		cout << root->val << " ";
		pre(root->left);
		pre(root->right);
	} 
}
//前序非递归
void pre_2(TreeNode*root){
	stack<TreeNode*>s;
	if(root == NULL) return;
	s.push(root);
	while(!s.empty()){
		TreeNode*p = s.top(); s.pop();
		cout << p->val << " ";
		if(p->right) s.push(p->right);
		if(p->left) s.push(p->left);
	}
} 
//中序递归
void mid(TreeNode*root){
	if(root == NULL) return;
	else{
		mid(root->left);
		cout << root->val << " ";
		mid(root->right);
	} 
} 
//中序非递归
void mid_2(TreeNode*root){
	stack<TreeNode*>s;
	if(root == NULL) return;
	TreeNode*p = root;
	while(p || !s.empty()){
		while(p){
			s.push(p); p = p->left;
		} 
		if(!s.empty()){
			p = s.top(); s.pop();
			cout << p->val << " ";
			p = p->right;
		}
	}
} 
//后序递归
void post(TreeNode*root){
	if(root == NULL) return;
	else{
		post(root->left);
		post(root->right);
		cout << root->val << " ";
	}
} 
//后序非递归
void post_2(TreeNode*root){
	if (root == NULL) return;
	TreeNode *pre = NULL, *p = root;
	stack<TreeNode *>s;
	while (p != NULL || !s.empty()){
		while (p != NULL){
			s.push(p); p = p->left;
		}
		p = s.top();
		//右子树为空或者已访问，输出当前节点
		if (p->right == NULL || p->right == pre){
			cout << p->val << " ";
			pre = p;//将当前结点地址赋值pre作为下一次判断标志，防止重复访问
			s.pop();
			p = NULL;//p赋值空以便访问右子树
		}
		else p = p->right;//访问子树的右子树
	}
}
//结点个数 
int nodes(TreeNode*root){
	if(root == NULL) return 0;
	else{
		return nodes(root->left) + nodes(root->right) + 1;
	}
}
//高度
int height(TreeNode*root){
	if(root == NULL) return -1;
	else{
		return max(height(root->left), height(root->right)) + 1;
	}
} 
//层次遍历
void level(TreeNode*root){
	queue<TreeNode*>q;
	if(root == NULL) return;
	q.push(root);
	while(!q.empty()){
		TreeNode*p = q.front();
		cout << p->val << " "; q.pop();
		if(p->left) q.push(p->left);
		if(p->right) q.push(p->right);
	}
}  
int main(){
	TreeNode*root;
	cout << "前序建立树:";
	Create(root);
	cout << endl;
	cout << "结点个数:";
	cout << nodes(root) << endl;
	cout << "高度：";
	cout << height(root) << endl;
	cout << "前序递归:  ";
	pre(root);
	cout << endl;
	cout << "前序非递归:";
	pre_2(root);
	cout << endl;
	cout << "中序递归:  ";
	mid(root);
	cout << endl;
	cout << "中序非递归:";
	mid_2(root);
	cout << endl;
	cout << "后序递归:  ";
	post(root);
	cout << endl;
	cout << "后序非递归:";
	post_2(root);
	cout << endl;
	cout << "层次遍历:  ";
	level(root);
	return 0;
}
