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

bool LLSIsEmpty(LLStack* Stack){
	return (Stack->Head == nullptr);
}

// ���û���
void LLSCreateStack(LLStack** Stack){
	*Stack = new LLStack;
	(*Stack)->Head = nullptr;
	(*Stack)->Top = nullptr;

}

// ���ø���Ʈ�� ��������, ��带 pop�Ѵ��� ��� ����,
// ������ ��� �Ǹ� ���ظ���Ʈ�� �޸����� 

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

// ���⸦ ���鲨�� 
/*
1. �ԷµǴ� ���ڿ� ( EX:  1+3.334/(4.28*(110- 7729)) �� �Է��Ѵٰ� ����.)
2. ��ǻ�Ͱ� �о� ���ϼ� �ֵ��� ���� ǥ������� �Ǿ��ִ°��� ���� ǥ������� �켱 �ٲٴ� �Լ��� ����.
2-1 ����ǥ������� �ٲܶ� ��ȣ�� �Ű� ���༭ ������ �Ѵ�. 
2-2 �������� ��ȣ�� ���ڷ� �� ���ڿ��� �������ִ� ���� �ʿ�. 
2-3 ���⼭ token �� ���ڿ��� ��Ÿ���µ� �� token �� �����ϼ����ְ�, ��Ģ���� ��ȣ �� ���� �ִ�. 
2-4 �� token�� ���� ǥ������� �� ���ڿ��� �̾� ���̰� " " ������ �����Ѵ�. 
2-5 


*/



// ���⼭ OPERAND�� ���ڸ� �ǹ��Ѵ�. 
enum SYMBOL{
	LEFT_PARENTHESIS = '(',
	RIGHT_PARENTHESIS = ')',
	PLUS = '+',
	MINUS = '-',
	MULTIPLY = '*',
	DIVIDE = '/',
	SPACE = ' ',
	OPERAND
};
char NUMBER[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.' };
/* ���ڸ� �Ǻ����ִ� �Լ�
 ���ڸ� true ����, �����ȣ�� false ����*/
bool IsNumber(char value){
	int ArrayLength = sizeof(NUMBER);
	for (int i = 0; i < ArrayLength; i++){
		if (value == NUMBER[i])
			return true;
	}
	return false;
}

/*
- �� �Լ��� ����, �����ȣ�� ��ġ�� ã�� ���� �Լ��̴�. ���ӵ� �����̸� Expression�� Index�� ���� ���Ѽ� ������ Index�� ��ȯ ���ָ� �ȴ�. 

1. ���⼭ Token�� ����, �����ȣ ��θ� ���ϴ� �������� ����, ���ڿ��� ǥ���ϴ� ������ ���ӵ� ����, ���� ��� 23, 2.0984�� �� ǥ���ϱ� ���� ���ڿ� ���
1-1. Token�� ������ ���ڿ��� ���� �˸��� '\0'�� �־� ��� �Ѵ�. 

2. Type�� Token�� ��������, �����ȣ���� �������ִ� ������ ����, ���ڸ� OPERAND, �����ȣ�� �� ��ȣ���� �־��ش�. 
3. ���ӵ� ���ڸ�, ���� �����ȣ�� ���� ������ Expression�� index�� �������� �ش�. 

*/
unsigned int GetNextToken(char* Expression, char* Token, int* Type){
	unsigned int i = 0;
	int ExpressionLength = strlen(Expression);
	for (i = 0; Expression[i] != '\0'; i++){
		Token[i] = Expression[i];

		// ������ ��
		if (IsNumber(Expression[i])){
			*Type = OPERAND;
			// ���� ���ڰ� ���ڰ� �ƴ϶�� �ݺ��� ����. 
			if (!IsNumber(Expression[i + 1]))
				break;
		}
		// �����ȣ �϶� 
		else{
			*Type = Expression[i];
			break;
		}
	}
	// ��ū�� ���� ���ڿ��� ���� �˸��� �� ���ڸ� ����.
	Token[++i] = '\0';
	return i;
}


// �켱������ ( ���ڰ� ������ ���� �켱���� ���� ��������. 
// ���� ��ȣ 0, ���ϱ� ���� 1, ���ϱ� 2
int GetPriority(char Operator, bool InStack){
	int Priority = -1;

	switch (Operator){
	case LEFT_PARENTHESIS:
		if (InStack){
			Priority = 0;		// ����ġ ���� 0�� �� ������ ���ʰ�ȣ '('�� �켱������ ���� ���� �����̴�.
		}						
		else					// ����ġ ���� 0�� �ƴ� 3�� �� ������ ���ʰ�ȣ'('�� �켱������ ������, ���� ������ �׻� ���ÿ� �����ϱ� ���� 3�� ��� 
			Priority = 3;		// ���� ��ȣ ����ġ�� 0�� �Ǹ� , ���ÿ� ����� ������ > ��ū�� �Ǿ ��ū�� ����ؾ� �ϴµ� ���� '('�� ������� �ʴ� 
		break;					// ��Ģ�� ��Ű�� ���ؼ� �̷��� �ߴ�. 
	case MULTIPLY:
	case DIVIDE:
		Priority = 2;
		break;

	case PLUS:
	case MINUS:
		Priority = 1;
		break;
	}
	return Priority;
}
// 
bool IsPrior(char OperatorInStack, char OperatorInToken){
	return (GetPriority(OperatorInStack, true) < GetPriority(OperatorInToken, false));
}
/*
1. Infix�� �����͸� �ϳ��� �о ���ڰ� ��������, �����ȣ���� �����ؼ� Postfix�� ����
1-1. ()�� ������ �ʿ� ���� ���� ǥ����� ���� ǥ������� ��ȯ �ϴ� �Լ�.

2. Infix���� Token�� �����ϴ� �κ��� �ʿ��ϰ�, ���� Token�� ��ġ�� ���� �Ҽ� �ִ� position���� �ʿ� �ϴ�. 
3. �ֵ�� ���ͽ�Ʈ�� ����� ���� ǥ����� ���� ǥ������� ��ȯ �ϴ� �˰����� ���� �ϱ� ���ؼ��� ���� �� �ʿ��ϴ�. 
3-1 �Է¹��� ���� ǥ��Ŀ��� ��ū�� �д´�. 
3-2. ��ū�� �� �������̸� ����� ����Ѵ�. 
3-3. ��ū�� ������(��ȣ ����)�϶�, �� ��ū�� ������ �ֻ��� ��忡 ����Ǿ��ִ� �����ں��� �켱������ ������ ���ÿ� �����ϰ�, 
	 �켱������ ������ ����� ����Ѵ�. ->  ���ÿ� ����� ������ <��ū => ���� ����, ��ū<���ÿ� ����� ������ => ���
3-4. ��ū�� �����ʰ�ȣ ')'�̸� �ֻ��� ��忡 ���ʰ�ȣ'('�� �ö����� ���ÿ� ���� ������ �����ϰ�, ������ ��忡 ��� �����ڸ� ����Ѵ�. ���� ��ȣ�� ������
     ���Ÿ� �ϰ� ������� �ʴ´�. 
3-5. ���� ǥ��Ŀ� �� �������� ���ٸ� ����������, �� ���� ���� �ִٸ� 1���� �ٽ� �ݺ��Ѵ�. 
*/
void  GetPostfix(char* Infix, char* Postfix){
	LLStack* Stack;
	char Token[32];
	int Type = -1;
	unsigned int position = 0;
	unsigned int Length = strlen(Infix);

	LLSCreateStack(&Stack);

	while (position < Length){

		position += GetNextToken(&Infix[position], Token, &Type);
		// ���� �Է�
		if (Type == OPERAND){
			strcat(Postfix, Token);
			strcat(Postfix, " ");
		}
		// ������ ��ȣ')'�� ������ �� ��� 
		else if (Type == RIGHT_PARENTHESIS){
			while (!LLSIsEmpty(Stack)){
				Node* Popped = LLSPop(Stack);
				if (Popped->data[0] == LEFT_PARENTHESIS){
					LLSDestroyNode(Popped);
					break;
				}
				else{
					strcat(Postfix, Popped->data);
					LLSDestroyNode(Popped);
				}
			}
		}
		// ���� ��ȣ �� ������ ��ȣ ����.
		else{
			while (!LLSIsEmpty(Stack) && !IsPrior(LLSTop(Stack)->data[0], Token[0])){   // �� while���� ���� �� ���� stack�� ��� �ְų� 
				// ������ ���� �κ�, ���� ��ȣ '('�� �����Ѵ�.						 // ���ÿ� ����Ǿ� �ִ� �������� �켱������ token ���� ������
				Node* Popped = LLSPop(Stack);
				if (Popped->data[0] != LEFT_PARENTHESIS){
					strcat(Postfix, Popped->data);
				}
				LLSDestroyNode(Popped);
			}
			LLSPush(Stack, LLSCreateNode(Token));
		}
	}

	// ���� ǥ����� �� �а� ���ÿ� ����� ��ȣ�� Fostfix�� ����
	while (!LLSIsEmpty(Stack)){
		Node* Popped = LLSPop(Stack);
		if (Popped->data[0] != LEFT_PARENTHESIS)
			strcat(Postfix, Popped->data);
		LLSDestroyNode(Popped);
	}
	// ���� ���� 
	LLSDestroyStack(Stack);
}

/*
1. Postfix�� �ǿ����ڸ� �ϳ��� �о�ͼ� ���ÿ� �����Ѵ�. 
2. �����ڰ� ��Ÿ�� ��쿡�� ���ÿ��� �� ������ �ΰ��� ���� ������ �ϰ�, �� ���� ����� ���ÿ� �����Ѵ�. 
2-1 node = pop(stack); value2 = atof(node->data), node = pop(stack), value1 = atof(node->data)
2-2 result = value1 ���� value2
2-3 _gcvt(result,10,buffer);
2-4 newNode = createNode(buffer);
2-5 push(newNode)
*/
double caculate(char* Postfix){
	LLStack* Stack;
	Node* ResultNode;
	double Result;
	char Token[32];
	int Type = -1;
	unsigned int read = 0;
	unsigned int length = strlen(Postfix);

	LLSCreateStack(&Stack);

	// Postfix �о� �鿩�� �Ѵ�. 
	while (read < length){
		read += GetNextToken(&Postfix[read], Token, &Type);
		if (Type == SPACE){
			continue;
		}
		else if (Type == OPERAND){
			LLSPush(Stack, LLSCreateNode(Token));
		}
		else{
			char ResultString[32];
			double Operator1, Operator2, TempResult;
			Node* OperatorNode;

			OperatorNode = LLSPop(Stack);
			Operator2 = atof(OperatorNode->data);
			LLSDestroyNode(OperatorNode);

			OperatorNode = LLSPop(Stack);
			Operator1 = atof(OperatorNode->data);
			LLSDestroyNode(OperatorNode);

			switch (Token[0]){
			case PLUS:
				TempResult = Operator1 + Operator2;
				break;
			case MINUS:
				TempResult = Operator1 - Operator2;
				break;
			case DIVIDE:
				TempResult = Operator1 / Operator2;
				break;
			case MULTIPLY:
				TempResult = Operator1 * Operator2;
				break;
			}

			_gcvt(TempResult, 10, ResultString);
			LLSPush(Stack, LLSCreateNode(ResultString));
		}
	}
	ResultNode = LLSPop(Stack);
	Result = atof(ResultNode->data);
	LLSDestroyNode(ResultNode);
	LLSDestroyStack(Stack);

	return Result;

}
int main(){

	char InfixExpression[100];
	char PostfixExpression[100];
	double result = 0.0f;
	memset(InfixExpression, 0, sizeof(InfixExpression));
	memset(PostfixExpression, 0, sizeof(PostfixExpression));

	while (1){
		printf("Enter Infix Expression:");
		scanf("%s", InfixExpression);

		GetPostfix(InfixExpression, PostfixExpression);
		printf("Infix:%s\n Postfix:%s\n", InfixExpression, PostfixExpression);

		result = caculate(PostfixExpression);
		printf("Caculation Result: %f\n", result);
	}
	return 0;
}