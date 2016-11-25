#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node{
	char* data;
	Node* NextNode;
};

struct LLStack{
	Node* Head;
	Node* Top;
};

int LLSIsEmpty(LLStack* Stack){
	return (Stack->Head == nullptr);
}

// 스택생성
void LLSCreateStack(LLStack** Stack){
	*Stack = new LLStack;
	(*Stack)->Head = nullptr;
	(*Stack)->Top = nullptr;
		
}

// 스택리스트가 빌때까지, 노드를 pop한다음 노드 제거,
// 스택이 비게 되면 스텍리스트를 메모리해제 

Node* LLSPop(LLStack* Stack){
	Node* TopNode = Stack->Top;

	if (Stack->Head == Stack->Top){
		Stack->Head = nullptr;
		Stack->Top = nullptr;
	}
	else{
		Node* CurrentTop = Stack->Head;
		while (CurrentTop != nullptr && CurrentTop->NextNode != Stack->Top){
			CurrentTop = CurrentTop->NextNode;
		}

		Stack->Top = CurrentTop;
		CurrentTop->NextNode = nullptr;
	}
	return TopNode;
}
void LLSDestroyNode(Node* _Node){
	delete _Node->data;
	delete _Node;
}
void LLSDestroyStack(LLStack* Stack){
	while (!LLSIsEmpty(Stack)){
		Node* PopNode = LLSPop(Stack);
		LLSDestroyNode(PopNode);
	}
	delete Stack;
}

Node* LLSCreateNode(char* NewData){
	Node* NewNode = new Node;
	NewNode->data = new char[strlen(NewData) + 1];

	strcpy(NewNode->data, NewData);
	NewNode->NextNode = nullptr;
	return NewNode;
}



void LLSPush(LLStack* Stack, Node* NewNode){
	if (Stack->Head == nullptr)
		Stack->Head = NewNode;
	else{
		Node* OldTop = Stack->Head;
		while (OldTop->NextNode != nullptr){
			OldTop = OldTop->NextNode;
		}
		OldTop->NextNode = NewNode;
	}
	Stack->Top = NewNode;
}



Node* LLSTop(LLStack* Stack){
	return Stack->Top;
}

int LLSGetSize(LLStack* Stack){
	int count = 0;

	Node* Current = Stack->Head;

	while (Current != nullptr){
		Current = Current->NextNode;
		count++;
	}
	return count;
}



int main(){

	int i = 0;
	int count = 0;
	Node* Poped;
	LLStack* Stack;
	LLSCreateStack(&Stack);

	LLSPush(Stack, LLSCreateNode("abc"));
	LLSPush(Stack, LLSCreateNode("def"));
	LLSPush(Stack, LLSCreateNode("efg"));
	LLSPush(Stack, LLSCreateNode("hij"));

	count = LLSGetSize(Stack);
	printf("Size: %d, Top: %s\n\n", count, LLSTop(Stack)->data);

	for (int i = 0; i < count; i++){
		if (LLSIsEmpty(Stack))
			break;
		Poped = LLSPop(Stack);
		printf("Popped: %s, ", Poped->data);
		LLSDestroyNode(Poped);

		if (!LLSIsEmpty(Stack))
			printf("Current Top: %s\n", LLSTop(Stack)->data);
		else
			printf("Stack Is Empty\n");
	}
	LLSDestroyStack(Stack);
	return 0;

}