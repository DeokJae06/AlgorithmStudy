#include "ArrayStack.h"	

ArrayStack::ArrayStack(){
	m_Capacity = 0;
	m_Top = 0;
	Nodes = nullptr;
}
void ArrayStack::ASCreateStack(ArrayStack** Stack, int Capacity){
	*Stack = new ArrayStack;
	(*Stack)->Nodes = new Node[Capacity];

	// 용량 초기화 및 top을 0으로 초기화 
	(*Stack)->SetCapacity(Capacity);
	(*Stack)->SetTop(0);
}
void ArrayStack::ASDestroyStack(ArrayStack* Stack){
	delete[] Stack->Nodes;
	delete Stack;
}
void ArrayStack::ASPush(ArrayStack* Stack, int data){
	int Position = Stack->GetTop();

	Stack->Nodes[Position].SetData(data);
	int TopPosition = Stack->GetTop();
	Stack->SetTop(TopPosition++);
}
int ArrayStack::ASPop(ArrayStack* Stack){
	// Top바로 아래의 위치의 데이터를 뽑아내고, Top을 -1한다. 
	int Position = Stack->GetTop();
	Stack->SetTop(--Position);

	return Stack->Nodes[Position].GetData();
}
int ArrayStack::ASTop(ArrayStack* Stack){

}
int ArrayStack::ASGetSize(ArrayStack* Stack){}
int ArrayStack::ASIsEmpty(ArrayStack* Stack){}