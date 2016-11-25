#include "ArrayStack.h"	

ArrayStack::ArrayStack(){
	m_Capacity = 0;
	m_Top = 0;
	Nodes = nullptr;
}
void ArrayStack::ASCreateStack(ArrayStack** Stack, int Capacity){
	*Stack = new ArrayStack;
	(*Stack)->Nodes = new Node[Capacity];

	// �뷮 �ʱ�ȭ �� top�� 0���� �ʱ�ȭ 
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
	// Top�ٷ� �Ʒ��� ��ġ�� �����͸� �̾Ƴ���, Top�� -1�Ѵ�. 
	int Position = Stack->GetTop();
	Stack->SetTop(--Position);

	return Stack->Nodes[Position].GetData();
}
int ArrayStack::ASTop(ArrayStack* Stack){

}
int ArrayStack::ASGetSize(ArrayStack* Stack){}
int ArrayStack::ASIsEmpty(ArrayStack* Stack){}