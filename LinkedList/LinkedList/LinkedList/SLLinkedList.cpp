#include <stdio.h>
#include <stdlib.h>

struct Node{
	Node*next;
	int data;
};

Node* CreateNode(int _data){
	Node* newNode = new Node;
	//Node *newNode = (Node*)malloc(sizeof(Node));
	newNode->data = _data;
	newNode->next = nullptr;
	return newNode;
}

/*
SLLApendNode �Լ��� �Ű������� _Head�� ���������ͷ� �ϴ� ������ 
�̱� �����ͷ� �ϰ� �� ��� �Լ��� ����Ǹ� _Head�� ���ø޸𸮿��� �ڵ����� ������ �ǹǷ�, _Head�� �ڵ����� ������ �ȴ�. 
�̶� �߻��ϴ� ��������  �Ű������� ���� �� _Head = List�� ��������, List = _Head�� �����̹Ƿ�, List = _Head�� ���� �Ǵ� ��
���� ��� _Head�� ���� ���ְų�, ���۷����� �̿��Ͽ� ���� ���� ���ְų�. �ƴϸ� List ��ü�� ���������� ���� ���ְų�, ��� ������ ���� ���� �ϰ� 
������ ���� ��쿡�� ������ ���� �����͸� ����ؾ߸� �Ѵ�. 

Node **_Head = &List;
Node *_Head = List; 
�� �������� ���� ��쿡�� ���ÿ� �Ҵ�� List�� ������ ������ �ּ� ��ü�� �Ѱ��ְ� �Ǿ _Head ������ ������ ������ �Ǿ ������ ������
*Head = &List
�Ʒ��� ��쿡�� List�� ������ ������ ������ �ִ� �� ��ü�� �����ϰ� �Ǵ� ��쿩�� List�� nullptr�� �ʱ�ȭ �Ǿ� �ִ� ��찡 �ƴ϶�� ������ ������, 
nullptr�� �ʱ�ȭ �Ǿ� �ִ� ���� _Head = List = nullptr �� ������ ����Ǵ� �Ͱ� �������� �̹Ƿ� �Լ��� ����ɶ� _Head�� ���� �Ǹ鼭 ������ �߻��Ѵ�.


*/

// ��� �߰� , ������ ��� �ڿ� ���ο� ��带 �߰��ϴ� ��
void SLLAppendNode(Node **_Head, Node *_NewNode){

	if ((*_Head) == nullptr)
		*_Head = _NewNode;
	else{
		Node *NextNode = *_Head;
		while (NextNode->next != nullptr)
			NextNode = NextNode->next;
		NextNode->next = _NewNode;
	}
}

// ��� Ž��, ������ ��ġ�� �ִ� ��� Ž��
Node *SLLGetNodeAt(Node *_Head, int Location){
	Node *CurrentNode = _Head;
	while (CurrentNode != nullptr && (--Location)>=0)// == CurrentNode != nullptr && (Location--)>0 �̷��� �Ҽ��� ������, �ӵ��� ���ؼ� ���� �� ���
		CurrentNode = CurrentNode->next;

	return CurrentNode;
}

// ��� ���� , ���������� ��带 ���� ���༭ �޸� ������ ���� �� �ִ�. 
void SLLDestroyNode(Node *DestroyNode){
	delete DestroyNode;
	//free(DestroyNode);

}

// �������, �������� ����Ʈ���� ��带 ���� 
// ����Ʈ���� ���� �� ����� ���� ��带 ã�Ƽ� ���� ����� ������带 ������ ����� �� ���� �����Ų��. 
// �������� ������ ������, ���������� ������ ���� ����� �޸� ������ �Ȼ����. 
Node *SLLRemoveNode(Node **_Head, Node *RemoveNode){
	if ((*_Head) == RemoveNode){
		*_Head = RemoveNode->next;
	}
	else{
		Node *Current = *_Head;
		while (Current != nullptr && Current->next != RemoveNode)
			Current = Current->next;
		if (Current != nullptr){
			Current->next = RemoveNode->next;
			//SLLDestroyNode(RemoveNode);
		}
	}
	return RemoveNode;
}

// ������
void PrintList(Node *Head){
	Node *Current = Head;
	while (Current != nullptr){
		printf("%d\t", Current->data);
		Current = Current->next;
	}
	printf("\n\n");
}
// ��� ����, 
// 1. �� �տ� ����
// 2. �߰��� ����
void SLLInsertNode(Node **_Head,Node **Current, Node *NewNode){
	// ��� ��ġ�� ���� �Ҷ�
	if (*_Head == *Current){
		NewNode->next = *_Head;
		(*_Head) = NewNode;
	}
	else{
		NewNode->next = (*Current)->next;
		(*Current)->next = NewNode;
	}
	
}

void SLLGetNodeCount(Node *_Head){
	int count = 0;
	Node *Current = _Head;

	while (Current != nullptr){
		Current = Current->next;
		count++;
	}
	
	printf("Node Count : %d EA\n", count);
}

int main(){
	Node *List = nullptr;
	Node *NewNode = nullptr;
	Node *myNode = nullptr;

	NewNode = CreateNode(117);
	SLLAppendNode(&List, NewNode);
	SLLGetNodeCount(List);
	PrintList(List);

	NewNode = CreateNode(200);
	SLLAppendNode(&List, NewNode);
	SLLGetNodeCount(List);
	PrintList(List);

	myNode = SLLGetNodeAt(List, 0);
	NewNode = CreateNode(300);
	SLLInsertNode(&List,&myNode, NewNode);
	SLLGetNodeCount(List);
	PrintList(List);

	NewNode = CreateNode(400);
	SLLAppendNode(&List, NewNode);
	SLLGetNodeCount(List);
	PrintList(List);

	NewNode = CreateNode(500);
	SLLAppendNode(&List, NewNode);
	SLLGetNodeCount(List);
	PrintList(List);

	myNode = SLLGetNodeAt(List, 0);
	SLLRemoveNode(&List, myNode);
	SLLGetNodeCount(List);
	PrintList(List);

	SLLDestroyNode(myNode);
	SLLGetNodeCount(List);
	PrintList(List);



	return 0;
}

