#include <iostream>
#include <math.h>
using namespace std;

const int chessBoardSize=8;

//保存在棋盘中的坐标位置
class Position{
public:
	Position(int i,int j):x(i),y(j){}
	Position(){}
	int x;
	int y;
};
//既保存了单链表的结构，也保存了向上层的树形结构
class ListTreeNode{
public:
	ListTreeNode(int x,int y):parent(NULL),next(NULL){
		this->position.x=x;
		this->position.y=y;
	}
	ListTreeNode *parent;
	ListTreeNode *next;
	Position position;
};
//单向链表
class List{
public:
	List():head(NULL),tail(NULL),_size(0){
	}
	ListTreeNode *head;
	ListTreeNode *tail;
	void appendNode(ListTreeNode *node){
		++_size;
		if(head==NULL){
			head=node;
			tail=node;
			node->next=NULL;
		}else{
			tail->next=node;
			tail=node;
		}
	}
	int size(){
		return this->_size;
	}
private:
	int _size;
};
//给定两个皇后位置，判断是否有冲突
bool checkPositionConfict(const Position& p1,const Position& p2){
	if(p1.x==p2.x||p1.y==p2.y||abs(p1.x-p2.x)==abs(p1.y-p2.y)){
		return true;
	}
	return false;
}
//从给定节点向树结构的上层查找，其中每一各节点的坐标位置是否和给定坐标冲突
bool validatePosition(Position position, ListTreeNode *node){
	ListTreeNode* currNode=node;
	while(true){
		if(currNode==NULL){
			return true;
		}
		if(checkPositionConfict(position,currNode->position)){
			return false;
		}
		currNode=currNode->parent;
	}
	return false;
}
//根据给定数组在命令行上画棋盘
void drawChessBoard(int board[][chessBoardSize]){
	for (int i=0;i<chessBoardSize;++i)
	{
		for (int j=0;j<chessBoardSize;++j)
		{
			cout<<board[i][j];
		}
		cout<<'\n';
	}
	cout<<'\n'<<endl;
}
//给定最下层的满足条件的所有节点，这些节点与向数结构上层查找的节点组成所有结果，并在命令行中显示
void drawResult(List& superLevelList){
	int board[chessBoardSize][chessBoardSize];
	ListTreeNode *currNode=superLevelList.head;
	while(currNode!=NULL){
		for (int i=0;i<chessBoardSize;++i)
		{
			for (int j=0;j<chessBoardSize;++j)
			{
				board[i][j]=0;
			}
		}
		ListTreeNode *currTreeNode=currNode;
		while(currTreeNode->parent!=NULL){
			board[currTreeNode->position.x][currTreeNode->position.y]=1;
			currTreeNode=currTreeNode->parent;
		}
		drawChessBoard(board);
		currNode=currNode->next;
	}
}
int main(){
	//上一层的可行方案节点列表
	List superLevelAvalableList;
	//添加一个不会和棋盘中任何皇后位置冲突的位置，这个节点是为了方便下面第一个while循环的NULL判断
	superLevelAvalableList.appendNode(new ListTreeNode(-10,1000));
	ListTreeNode *currNodeInSuperList;//每次遍历链表时，处在哪个节点
	for (int i=0;i<chessBoardSize;++i)
	{
		List tmpLevelAvailableList;
		for (int j=0;j<chessBoardSize;++j)
		{
			Position currPosition(i,j);
			currNodeInSuperList=superLevelAvalableList.head;
			//对上一层处理后遗留的所有可行方案
			while(currNodeInSuperList!=NULL){
				//判断当前位置是否能和遗留的可行方案结合在一起并且还是可行方案
				if(validatePosition(currPosition,currNodeInSuperList)){
					//如果是可行方案，则作为一个节点添加到临时可行方案链表，并把遗留可行方案的上一层节点作为父节点
					ListTreeNode *currNode=new ListTreeNode(currPosition.x,currPosition.y);
					currNode->parent=currNodeInSuperList;
					tmpLevelAvailableList.appendNode(currNode);
				}
				currNodeInSuperList=currNodeInSuperList->next;
			}
		}
		//一层结束后，把当前层可行方案赋值到上层可行方案，继续迭代
		superLevelAvalableList=tmpLevelAvailableList;
	}
	cout<<superLevelAvalableList.size()<<'\t'<<"solutions for chess board size of "<<chessBoardSize<<endl;;
	drawResult(superLevelAvalableList);
	return 0;

}