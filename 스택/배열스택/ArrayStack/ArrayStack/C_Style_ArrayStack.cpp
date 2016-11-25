#include <stdio.h>
#include <stdlib.h>

struct Node{
	int data;
};

struct ArrayStack{
	int Capacity;
	int Top;
	Node* Nodes;
};

void ASCreateStack(ArrayStack** Stack, int capacity){
	/*(*Stack) = new ArrayStack;
	(*Stack)->Nodes = new Node[capacity];*/

	(*Stack) = (ArrayStack*)malloc(sizeof(ArrayStack));
	(*Stack)->Nodes = (Node*)malloc(sizeof(Node)* capacity);

	(*Stack)->Capacity = capacity;
	(*Stack)->Top = 0;
}

void ASDestroy(ArrayStack* Stack){
	/*delete[] Stack->Nodes;
	delete Stack;*/

	free(Stack->Nodes);
	free(Stack);
}

void ASPush(ArrayStack *Stack, int data){
	int position = (Stack->Top);
	Stack->Nodes[position].data = data;
	Stack->Top++;
}

// 스택의 최상위 노드의 인덱스(top)의 값을 1만큼 낮추고, 최상위 노드의 데이터를 반환 하는 연산
// 실제적으로 top을 -1 하는 연산이 필요
int ASPop(ArrayStack* Stack){
	int position = --(Stack->Top);
	return Stack->Nodes[position].data;
}

// 스택 최상위 노드의 인덱스(Top)의 값을 출력하는 연산
int ASTop(ArrayStack* Stack){
	int position = Stack->Top -1;
	return Stack->Nodes[position].data;
}

// 스택의 갯수를 출력
int ASGetSize(ArrayStack* Stack){
	return Stack->Top;
}

int ASIsEmpty(ArrayStack* Stack){
	return (Stack->Top == 0);
}
int main(){
	ArrayStack* Stack = nullptr;
	ASCreateStack(&Stack, 10);
	ASPush(Stack, 3);
	ASPush(Stack, 37);
	ASPush(Stack, 11);
	ASPush(Stack, 12);

	/*ASPush(Stack, 90);
	ASPush(Stack, 91);
	ASPush(Stack, 92);
	ASPush(Stack, 93);
	ASPush(Stack, 94);
	ASPush(Stack, 95);
	ASPush(Stack, 96);*/

	printf("Capacity = %d, Size = %d, Top = %d\n\n", Stack->Capacity, ASGetSize(Stack), ASTop(Stack));

	for (int i = 0; i < 4; i++){
		if (ASIsEmpty(Stack))
			break;
		printf("Popped: %d, ", ASPop(Stack));
		if (!ASIsEmpty(Stack))
			printf("Current Top: %d\n", ASTop(Stack));
		else
			printf("Stack is Empty\n");
	}

	ASDestroy(Stack);

	return 0;
}