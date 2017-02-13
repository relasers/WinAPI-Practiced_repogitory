/*
2. 정렬하고 검색하기 (동적 메모리 할당 사용하기)
사용자가 입력하는 숫자보다 작은 임의의 수를 20개 만들고 (중복불가) 다음의 명령어를 수행한다 (함수사용)
A : 오름차순으로 정렬
D : 내림차순으로 정렬
R : 랜덤하게 재정렬
M : 최대값 출력
I : 최소값 출력
결과 ) Input number : 50
Generated numbers : 5 3 9 11 --- 7 13 19 43
Command A  3 5 7 9 --- 13 19 43
Command D  43 19 13 --- 9 7 5 3
Command R  3 5 11 43 --- 19 13 9
Command M  43
Command I  3
*/

int Question_Module_2(void) {

	int* arr = (int*)malloc(sizeof(int)*20);
	int i;
	int number = 0;
	char select[1] = {0}; // 커맨드 문자를 받는다
	int final_select = 0; // 반환된 선택한 메뉴
	while (1) {
		printf("input_number : ");
		scanf("%d", &number);
		getchar();
		if (number < 20) {
			printf("Please input number again\n");
			continue;
		}
			break;		
	}


	printf("\n");

	Generate_numbers(number,arr);
	printf("Generated numbers : ");

	for (i = 0; i < 20; ++i) {
		printf("%4d", arr[i]);
	}
	
	printf("\n");
	printf("Command A : 오름차순 정렬 \n");
	printf("Command D : 내림차순 정렬 \n");
	printf("Command R : 랜덤으로 재정렬 \n");
	printf("Command M : 최소값 출력 \n");
	printf("Command I : 최소값 출력 \n");
	printf("Command E : 나가기\n\n");
	printf("\n");

	while (1) {
		printf("Please Insert Command : ");

		select[0] = getch();
		printf("%c",select[0]);
		final_select = Command_check(select[0]);

		printf("\n");

		switch (final_select) {
		case 0: 
			Command_A(arr); // 배열 오름차순 정렬
			continue;
		case 1: 
			Command_D(arr); // 배열 내림차순 정렬
			continue;
		case 2:
			Command_R(arr); // 랜덤 재정렬
			continue;
		case 3:
			Command_M(arr); // 최대값 출력
			continue;
		case 4:
			Command_I(arr); // 최소값 출력
			continue;
		case 5:
			break;
		default:
			printf("다시골라\n");
			continue;
		}
		break;

	}

	free(arr); //배열 메모리를 반환한다
	return 0;
}
//숫자 생성
int Generate_numbers(int number,int arr[]) {
	int temp_str[20] = { 0 };
	int i,j;
	int repeat_number = 0; // 중복되는거 찾는 변수
	int temp;
	for (i = 0; i < 20; ++i) {
		
		repeat_number = 0; // 중복체크 변수를 다시 0으로 초기화 한다.

		temp = ( rand()%number ); // 입력한 숫자로 나눈 나머지를 뽑는다.
		temp_str[i] = temp; // 일단 이 뽑인 숫자를 임시배열에 저장한다.

		for (j = 0 ; j < 20 ; ++j) {
			if (temp == temp_str[j])
				++repeat_number; // 배열 내 중복되는 숫자가 있을 시 카운트를 1 올린다
		} 
		if (1 < repeat_number) { --i; } // 만약 카운트가 2 이상을 기록하면 i값을 하나 내린다.
										// 즉 그 칸의 숫자를 다시 뽑는다
	}
	for (i = 0; i < 20; ++i) {
		arr[i] = temp_str[i]; // 원본 배열에 임시 배열을 대입한다.
	}

}

//오름차순 정렬
int Command_A(int arr[]) {
	int i,j;
	int temp = 0;
	int *str = (int *)malloc(sizeof(int) * 20);

	for (i = 0; i < 20; ++i) {
		str[i] = arr[i];
	}

	for (j = 19 ; j > 0 ; --j) {
		for (i = 0; i < j ; ++i) {
			if (str[i] > str[i+1]) {
				temp = str[i];
				str[i] = str[i+1];
				str[i+1] = temp;
			}
		}
		

	}
	for (i = 0; i < 20; ++i) {
		arr[i] = str[i];
	}
	free(str);

	printf("COMMAND A  ");
	for (i = 0; i < 20; ++i) {
		printf("%4d", arr[i]);
	}
	printf("\n");
}

//내림차순 정렬
int Command_D(int arr[]) {
	int i, j;
	int temp = 0;
	int *str = (int *)malloc(sizeof(int) * 20);

	for (i = 0; i < 20; ++i) {
		str[i] = arr[i];
	}

	for (j = 19; j > 0; --j) {
		for (i = 0; i < j; ++i) {
			if (str[i] < str[i + 1]) {
				temp = str[i];
				str[i] = str[i + 1];
				str[i + 1] = temp;
			}
		}


	}
	for (i = 0; i < 20; ++i) {
		arr[i] = str[i];
	}
	free(str);

	printf("COMMAND D  ");
	for (i = 0; i < 20; ++i) {
		printf("%4d", arr[i]);
	}
	printf("\n");
}

//랜덤하게 재정렬
int Command_R(int arr[]) {
	int i =0, j = 0;
	int temp1 = 0;
	int temp2 = 0;
	int *temp_str = (int*)malloc(sizeof(int));

	temp_str[0] =0;


	i = 0;
	while (1)
	{
		temp1 = ( rand() % 20 ); // 재배치할 열을 고른다
		temp2 = (rand() % 20 ); // 재배치할 매개체열을 고른다
		if (!(temp1 == temp2)) {
			temp_str[0] = arr[temp1];
			arr[temp1] = arr[temp2];
			arr[temp2] = temp_str[0];
			++i;
		}
		if ( i > 30) break; //30번만 재배열한다
	}


	free(temp_str);

	printf("COMMAND R  ");
	for (i = 0; i < 20; ++i) {
		printf("%4d", arr[i]);
	}
	printf("\n");

}

//최대값 출력
int Command_M(int arr[]) {
	int i;
	int temp=arr[1];

	for (i = 0; i < 20; ++i) {
		if (temp < arr[i])
			temp = arr[i];
	}
	printf("COMMAND M  %d",temp);
	printf("\n");
	
}
//최소값 출력
int Command_I(int arr[]) {
	int i;
	int temp = arr[1];

	for (i = 0; i < 20; ++i) {
		if (temp > arr[i])
			temp = arr[i];
	}
	printf("COMMAND I  %d", temp);
	printf("\n");
	
}


int Command_check(char* select) {
	int a=0; // 메뉴 반환용
	if (select == 'A' || select == 'a')
		a = 0;
	else if (select == 'D'||select == 'd')
		a = 1;
	else if (select == 'R' || select == 'r')
		a = 2;
	else if (select == 'M' || select == 'm')
		a = 3;
	else if (select == 'I' || select == 'i')
		a = 4;
	else if (select == 'E' || select == 'e')
		a = 5;
	else
		a = 6;
	return a; // a값을 반환한다
}