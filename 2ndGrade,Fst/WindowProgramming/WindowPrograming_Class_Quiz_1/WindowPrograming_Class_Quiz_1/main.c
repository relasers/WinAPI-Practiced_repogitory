#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<math.h>
#include"function.h"





int main() {
	srand((unsigned int)time(NULL)); // �õ� ���� ����

	int Select_Module; // ó���� ������ ��� ����

	while (1) {
		Select_Module = 0;
		printf("������ ����� �����ϼ��� 1~8 : ");
		scanf("%d",&Select_Module);
		getchar();
		Running_Module(Select_Module); //�������� �Ѿ��
		continue;
	}
	return 0;
}

int Running_Module(int Select_Module) { /*������ Ž��*/
	int select = Select_Module;
	switch(select){
	case 1:
		printf("����� 1��° ����� �����߽��ϴ�\n");
		Question_Module_1();
		break;
	case 2:
		printf("����� 2��° ����� �����߽��ϴ�\n");
		Question_Module_2();
		break;
	case 3:
		printf("����� 3��° ����� �����߽��ϴ�\n");
		Question_Module_3();
		break;
	case 4:
		printf("����� 4��° ����� �����߽��ϴ�\n");
		Question_Module_4();
		break;
	case 5:
		printf("����� 5��° ����� �����߽��ϴ�\n");
		Question_Module_5();
		break;
	case 6:
		printf("����� 6��° ����� �����߽��ϴ�\n");
		Question_Module_6();
		break;
	case 7:
		printf("����� 7��° ����� �����߽��ϴ�\n");
		Question_Module_7();
		break;
	case 8:
		printf("����� 8��° ����� �����߽��ϴ�\n");
		Question_Module_8();
		break;
	default:
		printf("���ǵ������� ����Դϴ�\n");
		printf("�ٽ� ");
		break;
	}
	return 0;
}
