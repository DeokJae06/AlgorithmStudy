#pragma once

#include <iostream>
using namespace std;

class Node{
public:
	Node(){};
	~Node(){};

public:
	int m_data;
public:
	void SetData(int data){ m_data = data; }
	int GetData(){ return m_data; }
};

class ArrayStack :public Node{
public:
	ArrayStack();
	~ArrayStack();
public:
	void ASCreateStack(ArrayStack** Stack, int Capacity);
	void ASDestroyStack(ArrayStack* Stack);
	void ASPush(ArrayStack* Stack, int data);
	int ASPop(ArrayStack* Stack);
	int ASTop(ArrayStack* Stack);
	int ASGetSize(ArrayStack* Stack);
	int ASIsEmpty(ArrayStack* Stack);
	void SetCapacity(int capacity){ m_Capacity = capacity; }
	void SetTop(int Top){ m_Top = Top; }
	int GetTop(){ return m_Top; }
	//void SetData(int data){ Nodes->m_data = data; }
	//int GetData(){ return Nodes->m_data; }

protected:
	int m_Capacity;
	int m_Top;
	Node* Nodes;
};