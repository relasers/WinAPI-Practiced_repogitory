#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<math.h>
#include"function.h"





int main() {
	srand((unsigned int)time(NULL)); // 시드 난수 생성

	int Select_Module; // 처음에 실행할 모듈 선택

	while (1) {
		Select_Module = 0;
		printf("실행할 모듈을 선택하세요 1~8 : ");
		scanf("%d",&Select_Module);
		getchar();
		Running_Module(Select_Module); //실행으로 넘어간다
		continue;
	}
	return 0;
}

int Running_Module(int Select_Module) { /*모듈실행 탐지*/
	int select = Select_Module;
	switch(select){
	case 1:
		printf("당신은 1번째 모듈을 실행했습니다\n");
		Question_Module_1();
		break;
	case 2:
		printf("당신은 2번째 모듈을 실행했습니다\n");
		Question_Module_2();
		break;
	case 3:
		printf("당신은 3번째 모듈을 실행했습니다\n");
		Question_Module_3();
		break;
	case 4:
		printf("당신은 4번째 모듈을 실행했습니다\n");
		Question_Module_4();
		break;
	case 5:
		printf("당신은 5번째 모듈을 실행했습니다\n");
		Question_Module_5();
		break;
	case 6:
		printf("당신은 6번째 모듈을 실행했습니다\n");
		Question_Module_6();
		break;
	case 7:
		printf("당신은 7번째 모듈을 실행했습니다\n");
		Question_Module_7();
		break;
	case 8:
		printf("당신은 8번째 모듈을 실행했습니다\n");
		Question_Module_8();
		break;
	default:
		printf("정의되지않은 모듈입니다\n");
		printf("다시 ");
		break;
	}
	return 0;
}
