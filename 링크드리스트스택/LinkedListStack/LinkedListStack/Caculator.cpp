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

// 계산기를 만들꺼야 
/*
1. 입력되는 문자열 ( EX:  1+3.334/(4.28*(110- 7729)) 를 입력한다고 하자.)
2. 컴퓨터가 읽어 들일수 있도록 중위 표기식으로 되어있는것을 후위 표기식으로 우선 바꾸는 함수를 제작.
2-1 후위표기식으로 바꿀때 괄호도 신경 써줘서 만들어야 한다. 
2-2 사직연산 기호와 숫자로 된 문자열을 구분해주는 것이 필요. 
2-3 여기서 token 은 문자열을 나타내는데 이 token 은 숫자일수도있고, 사칙연산 기호 일 수도 있다. 
2-4 이 token을 후위 표기식으로 된 문자열에 이어 붙이고 " " 공백을 삽입한다. 
2-5 


*/



// 여기서 OPERAND는 숫자를 의미한다. 
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
/* 숫자를 판별해주는 함수
 숫자면 true 리턴, 연산기호면 false 리턴*/
bool IsNumber(char value){
	int ArrayLength = sizeof(NUMBER);
	for (int i = 0; i < ArrayLength; i++){
		if (value == NUMBER[i])
			return true;
	}
	return false;
}

/*
- 이 함수는 숫자, 연산기호의 위치를 찾기 위한 함수이다. 연속된 숫자이면 Expression의 Index를 증가 시켜서 증가한 Index를 반환 해주면 된다. 

1. 여기서 Token은 숫자, 연산기호 모두를 말하는 포괄적인 변수, 문자열로 표현하는 이유는 연속된 숫자, 예를 들어 23, 2.0984등 을 표현하기 위해 문자열 사용
1-1. Token의 끝에는 문자열의 끝을 알리는 '\0'를 넣어 줘야 한다. 

2. Type은 Token이 숫자인지, 연산기호인지 구별해주는 구분자 역할, 숫자면 OPERAND, 연산기호면 각 기호들을 넣어준다. 
3. 연속된 숫자면, 다음 연산기호가 나올 때까지 Expression의 index를 증가시켜 준다. 

*/
unsigned int GetNextToken(char* Expression, char* Token, int* Type){
	unsigned int i = 0;
	int ExpressionLength = strlen(Expression);
	for (i = 0; Expression[i] != '\0'; i++){
		Token[i] = Expression[i];

		// 숫자일 때
		if (IsNumber(Expression[i])){
			*Type = OPERAND;
			// 다음 문자가 숫자가 아니라면 반복문 종료. 
			if (!IsNumber(Expression[i + 1]))
				break;
		}
		// 연산기호 일때 
		else{
			*Type = Expression[i];
			break;
		}
	}
	// 토큰의 끝에 문자열의 끝을 알리는 널 문자를 삽입.
	Token[++i] = '\0';
	return i;
}


// 우선순위값 ( 숫자가 높아질 수록 우선순위 값이 높아진다. 
// 왼쪽 괄호 0, 더하기 빼기 1, 곱하기 2
int GetPriority(char Operator, bool InStack){
	int Priority = -1;

	switch (Operator){
	case LEFT_PARENTHESIS:
		if (InStack){
			Priority = 0;		// 가중치 값을 0을 준 이유는 왼쪽괄호 '('는 우선순위가 가장 낮기 떄문이다.
		}						
		else					// 가중치 값을 0이 아닌 3을 준 이유는 왼쪽괄호'('는 우선순위가 낮지만, 예외 적으로 항상 스택에 삽입하기 위해 3을 사용 
			Priority = 3;		// 왼쪽 괄호 가중치가 0이 되면 , 스택에 저장된 연산자 > 토큰이 되어서 토큰을 출력해야 하는데 왼쪽 '('는 출력하지 않는 
		break;					// 규칙을 지키기 위해서 이렇게 했다. 
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
1. Infix의 데이터를 하나씩 읽어서 문자가 숫자인지, 연산기호인지 구분해서 Postfix에 저장
1-1. ()는 저장할 필요 없이 중위 표기식을 후위 표기식으로 변환 하는 함수.

2. Infix에서 Token을 구별하는 부분이 필요하고, 다음 Token의 위치를 구분 할수 있는 position또한 필요 하다. 
3. 애드거 다익스트라가 고안한 중위 표기법을 후위 표기법으로 변환 하는 알고리즘을 구현 하기 위해서는 스택 이 필요하다. 
3-1 입력받은 중위 표기식에서 토큰을 읽는다. 
3-2. 토큰이 피 연산자이면 결과에 출력한다. 
3-3. 토큰이 연산자(괄호 포함)일때, 이 토큰이 스택의 최상위 노드에 저장되어있는 연산자보다 우선순위가 높으면 스택에 삽입하고, 
	 우선순위가 낮으면 결과에 출력한다. ->  스택에 저장된 연산자 <토큰 => 스택 삽입, 토큰<스택에 저장된 연산자 => 출력
3-4. 토큰이 오른쪽괄호 ')'이면 최상위 노드에 왼쪽괄호'('가 올때까지 스택에 제거 연산을 수행하고, 제거한 노드에 담긴 연산자를 출력한다. 왼쪽 괄호를 만나면
     제거만 하고 출력하지 않는다. 
3-5. 중위 표기식에 더 읽을것이 없다면 빠져나가고, 더 읽을 것이 있다면 1부터 다시 반복한다. 
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
		// 정수 입력
		if (Type == OPERAND){
			strcat(Postfix, Token);
			strcat(Postfix, " ");
		}
		// 오른쪽 괄호')'를 만나게 될 경우 
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
		// 왼쪽 괄호 및 연산자 기호 저장.
		else{
			while (!LLSIsEmpty(Stack) && !IsPrior(LLSTop(Stack)->data[0], Token[0])){   // 이 while문이 참이 될 때는 stack이 비어 있거나 
				// 연산자 삽입 부분, 왼쪽 괄호 '('는 제외한다.						 // 스택에 저장되어 있는 연산자의 우선순위가 token 보다 높을때
				Node* Popped = LLSPop(Stack);
				if (Popped->data[0] != LEFT_PARENTHESIS){
					strcat(Postfix, Popped->data);
				}
				LLSDestroyNode(Popped);
			}
			LLSPush(Stack, LLSCreateNode(Token));
		}
	}

	// 중위 표기식을 다 읽고 스택에 저장된 기호들 Fostfix에 저장
	while (!LLSIsEmpty(Stack)){
		Node* Popped = LLSPop(Stack);
		if (Popped->data[0] != LEFT_PARENTHESIS)
			strcat(Postfix, Popped->data);
		LLSDestroyNode(Popped);
	}
	// 스택 삭제 
	LLSDestroyStack(Stack);
}

/*
1. Postfix의 피연산자를 하나씩 읽어와서 스택에 저장한다. 
2. 연산자가 나타난 경우에는 스택에서 피 연산자 두개를 꺼내 연산을 하고, 그 연산 결과를 스택에 삽입한다. 
2-1 node = pop(stack); value2 = atof(node->data), node = pop(stack), value1 = atof(node->data)
2-2 result = value1 연산 value2
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

	// Postfix 읽어 들여야 한다. 
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