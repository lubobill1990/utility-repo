#include <iostream>
#include <math.h>
using namespace std;

const int chessBoardSize=8;

//�����������е�����λ��
class Position{
public:
	Position(int i,int j):x(i),y(j){}
	Position(){}
	int x;
	int y;
};
//�ȱ����˵�����Ľṹ��Ҳ���������ϲ�����νṹ
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
//��������
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
//���������ʺ�λ�ã��ж��Ƿ��г�ͻ
bool checkPositionConfict(const Position& p1,const Position& p2){
	if(p1.x==p2.x||p1.y==p2.y||abs(p1.x-p2.x)==abs(p1.y-p2.y)){
		return true;
	}
	return false;
}
//�Ӹ����ڵ������ṹ���ϲ���ң�����ÿһ���ڵ������λ���Ƿ�͸��������ͻ
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
//���ݸ����������������ϻ�����
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
//�������²���������������нڵ㣬��Щ�ڵ��������ṹ�ϲ���ҵĽڵ�������н������������������ʾ
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
	//��һ��Ŀ��з����ڵ��б�
	List superLevelAvalableList;
	//���һ��������������κλʺ�λ�ó�ͻ��λ�ã�����ڵ���Ϊ�˷��������һ��whileѭ����NULL�ж�
	superLevelAvalableList.appendNode(new ListTreeNode(-10,1000));
	ListTreeNode *currNodeInSuperList;//ÿ�α�������ʱ�������ĸ��ڵ�
	for (int i=0;i<chessBoardSize;++i)
	{
		List tmpLevelAvailableList;
		for (int j=0;j<chessBoardSize;++j)
		{
			Position currPosition(i,j);
			currNodeInSuperList=superLevelAvalableList.head;
			//����һ�㴦������������п��з���
			while(currNodeInSuperList!=NULL){
				//�жϵ�ǰλ���Ƿ��ܺ������Ŀ��з��������һ���һ��ǿ��з���
				if(validatePosition(currPosition,currNodeInSuperList)){
					//����ǿ��з���������Ϊһ���ڵ���ӵ���ʱ���з������������������з�������һ��ڵ���Ϊ���ڵ�
					ListTreeNode *currNode=new ListTreeNode(currPosition.x,currPosition.y);
					currNode->parent=currNodeInSuperList;
					tmpLevelAvailableList.appendNode(currNode);
				}
				currNodeInSuperList=currNodeInSuperList->next;
			}
		}
		//һ������󣬰ѵ�ǰ����з�����ֵ���ϲ���з�������������
		superLevelAvalableList=tmpLevelAvailableList;
	}
	cout<<superLevelAvalableList.size()<<'\t'<<"solutions for chess board size of "<<chessBoardSize<<endl;;
	drawResult(superLevelAvalableList);
	return 0;

}