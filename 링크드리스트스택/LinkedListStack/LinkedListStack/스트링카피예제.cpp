#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// ��� ���⼭�� �� �躹 ������ �߻��Ѵ�. 
// ���Կ����� �ϰ� �Ǹ� ���� ���簡 �Ǿ ������ �߻��Ѵ�. 
// �Լ��� �̿��ϰ� �Ǹ� �̷��� ������ ���� �� �� �ִ�. 

//int main(){
//
//	char* str1 = "abcd efg";
//	char* str2 = new char[strlen(str1) + 1];
//	char* str4 = "cdefg abc";
//	//char* str2 = nullptr;
//	printf("str1 �ּ�: %d\n", str1);
//	printf("str2 �ּ�: %d\n", str2);
//
//	str2 = str1;
//	printf("%s\n", str2);
//	printf("str1 �ּ�: %d\n", str1);
//	printf("str2 �ּ�: %d\n", str2);
//
//	str2 = str4;
//	printf("%s\n", str2);
//
//	
//
//	char* str3 = new char[strlen(str1)+1];
//	//char* str3 = nullptr;
//	//strncpy(str3, str1,9);
//	strcpy(str3, str1);
//	if (!strcmp(str2, str3))
//		printf("equal\n");
//	else
//		printf("not equal\n");
//
//	/*for (int i = 0; i < (strlen(str1) + 1); i++)
//		printf("%c\n", str2[i]);*/
//	
//	return 0;
//}
//
//
//int main() {
//
//	char str1[9] = "abcd efg";
//	char* str2 = new char[strlen(str1) + 1];
//
//	char str3[9] = "abcd efg";
//	char* str4 = new char[strlen(str3) + 1];
//
//	printf("%d\n", str1);
//	printf("%d\n", str2);
//	str2 = str1;
//	strcpy_s(str4, strlen(str3) + 1, str3);
//
//	str1[4] = '4';
//	str3[4] = '4';
//
//	printf("%s\n", str2);
//	printf("%s\n", str4);
//
//	system("pause");
//	return 0;
//}


// true false ���� 

int iIsPrior(int num1, int num2){
	return (num1 > num2);
}

bool bIsPrior(int num1, int num2){
	return (num1 > num2);
}

int main(){

	int num1 = 10;
	int num2 = 5;

	int nResult = 0;
	bool bResult = false;

	nResult = iIsPrior(num1, num2);
	bResult = bIsPrior(num1, num2);

	printf("nResult = %d\n", nResult);
	printf("bResult = %d\n", bResult);


	return 0;
}

