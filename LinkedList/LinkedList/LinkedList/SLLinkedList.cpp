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
SLLApendNode 함수의 매개변수중 _Head를 더블포인터로 하는 이유는 
싱글 포인터로 하게 될 경우 함수가 종료되면 _Head는 스택메모리에서 자동으로 해제가 되므로, _Head는 자동으로 삭제가 된다. 
이때 발생하는 문제점은  매개변수를 받을 때 _Head = List는 참이지만, List = _Head는 거짓이므로, List = _Head가 참이 되는 것
예를 들어 _Head를 리턴 해주거나, 레퍼런스를 이용하여 값을 전달 해주거나. 아니면 List 자체를 전역변수로 선언 해주거나, 멤버 변수로 직접 접근 하게 
만들지 않을 경우에는 무조건 더블 포인터를 사용해야만 한다. 

Node **_Head = &List;
Node *_Head = List; 
의 차이점은 위의 경우에는 스택에 할당된 List의 포인터 변수의 주소 자체를 넘겨주게 되어서 _Head 포인터 변수가 삭제가 되어도 문제가 없지만
*Head = &List
아래의 경우에는 List의 포인터 변수가 가지고 있는 값 자체를 전달하게 되는 경우여서 List가 nullptr로 초기화 되어 있는 경우가 아니라면 문제가 없지만, 
nullptr로 초기화 되어 있는 경우는 _Head = List = nullptr 이 구문이 실행되는 것과 마찬가지 이므로 함수가 종료될때 _Head가 종료 되면서 문제가 발생한다.


*/

// 노드 추가 , 마지막 노드 뒤에 새로운 노드를 추가하는 것
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

// 노드 탐색, 임의의 위치에 있는 노드 탐색
Node *SLLGetNodeAt(Node *_Head, int Location){
	Node *CurrentNode = _Head;
	while (CurrentNode != nullptr && (--Location)>=0)// == CurrentNode != nullptr && (Location--)>0 이렇게 할수도 있지만, 속도를 위해서 전위 식 사용
		CurrentNode = CurrentNode->next;

	return CurrentNode;
}

// 노드 삭제 , 물리적으로 노드를 삭제 해줘서 메모리 누수를 막을 수 있다. 
void SLLDestroyNode(Node *DestroyNode){
	delete DestroyNode;
	//free(DestroyNode);

}

// 노드제거, 논리적으로 리스트에서 노드를 제거 
// 리스트에서 제거 할 노드의 이전 노드를 찾아서 이전 노드의 다음노드를 제거할 노드의 뒷 노드로 연결시킨다. 
// 논리적으로 삭제를 했으면, 물리적으로 삭제를 진행 해줘야 메모리 누수가 안생긴다. 
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

// 노드출력
void PrintList(Node *Head){
	Node *Current = Head;
	while (Current != nullptr){
		printf("%d\t", Current->data);
		Current = Current->next;
	}
	printf("\n\n");
}
// 노드 삽입, 
// 1. 맨 앞에 삽입
// 2. 중간에 삽입
void SLLInsertNode(Node **_Head,Node **Current, Node *NewNode){
	// 헤드 위치에 삽입 할때
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

