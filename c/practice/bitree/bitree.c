/* ************************************************************************
 *       Filename:  bitree.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年09月06日 18时35分22秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _BiTNode
{
	char data; //节点数据域
	struct _BiTNode *lchild, *rchild;  /*指向左孩子和右孩子*/
}BiTNode, *pBiTNode; 


/*创建一棵二叉树*/
//不管是先序或中序或后序创建二叉树，对遍历二叉树不影响
CreatBiTree(pBiTNode *T) // T为二级指针
{
	char ch;
	
	ch = getchar();
	getchar();
	
	printf("get = %c\n",ch);
	if(ch == ' ')
	{
		*T = NULL;
	}
	else
	{
		*T = (BiTNode *)malloc(sizeof(BiTNode));/*创建一个结点*/
		bzero(*T, sizeof(BiTNode));
		
		// * 运算符的优先级比 -> 运算符低
		(*T)->data = ch; //这条语句放这里是先序创建二叉树, 
		CreatBiTree(&((*T)->lchild)); // 递归创建左子树
		//(*T)->data = ch;
		CreatBiTree(&((*T)->rchild)); // 递归创建右子树
		//(*T)->data = ch;
	}
}

/*遍历二叉树*/
//先序
PreOrderTraverse(pBiTNode T,int level)
{
	if(T) 
	{	/*递归结束条件，T为空*/
		printf("level: %d  node: %c\n",level, T->data);
		PreOrderTraverse(T->lchild, level+1);
		PreOrderTraverse(T->rchild, level+1);
	}
}
//中序
MiOrderTraverse(pBiTNode T,int level)
{
	if(T) 
	{	/*递归结束条件，T为空*/	
		MiOrderTraverse(T->lchild, level+1);
		printf("level: %d  node: %c\n",level, T->data);
		MiOrderTraverse(T->rchild, level+1);
	}
}
//后序
PostOrderTraverse(pBiTNode T,int level)
{
	if(T) 
	{	/*递归结束条件，T为空*/	
		PostOrderTraverse(T->lchild, level+1);		
		PostOrderTraverse(T->rchild, level+1);
		printf("level: %d  node: %c\n",level, T->data);
	}
}

//统计二叉树叶子节点数
int CountLeaf(pBiTNode T)
{
	static int count = 0;
	
	if(T)
	{
		count = CountLeaf(T->lchild);
		if(T->lchild == NULL && T->rchild == NULL)
		{
			count++;
		}
		count = CountLeaf(T->rchild);
	}
	return count;
}

//求二叉树的深度
int TreeDepth(pBiTNode T)
{
	static int count = 0;
	
	if(T)
	{
		count++;
		count = TreeDepth(T->lchild);
		count = TreeDepth(T->rchild);
	}
	return count;
}

int main(int argc, char *argv[])
{
	int level = 1;
	int Node_num = 0,Depth_num = 0;
	pBiTNode T = NULL;  /*最开始T指向空*/

	CreatBiTree(&T);  			//创建二叉树，先画出树形图，根据图进行输入创建
	printf("\n先序遍历：\n");
	PreOrderTraverse(T,level); 	//遍历二叉树，找到包含D字符结点位于二叉树中的层数
	printf("\n中序遍历：\n");
	MiOrderTraverse(T,level); 	//遍历二叉树，找到包含D字符结点位于二叉树中的层数
	printf("\n后序遍历：\n");
	PostOrderTraverse(T,level); 	//遍历二叉树，找到包含D字符结点位于二叉树中的层数

	Node_num = CountLeaf(T);
	Depth_num = TreeDepth(T);
	printf("\nNode_num = %d, Depth_num = %d\n",Node_num,Depth_num);
	return 0;
}


