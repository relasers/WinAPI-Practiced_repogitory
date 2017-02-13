/* 배열 사용하기
 4X5 배열에 2보다 작은 임의의 수 (0 또는 1) 을 저장하고 사용자가 입력하는 행과 열에 해당하는 숫자를 
 사용자가 입력하는 4개의 명령어에 따라 바꾸어 출력하시오 (주소에 의한 호출방식을 사용하는 함수를 사용하여 출력은 메인함수에서 한다)
 ex>> 행렬값 : 1 0 0 1 1
               1 1 1 0 0
			   0 1 1 1 0
			   0 1 0 1 1
[입력] 명령어 행 열
명령어 1 : 예 - 1 2 3 : 2행 3열의 숫자에 5를 곱하여 출력 (결과에서 5)
명령어 2 : 예 - 2 2 4 : 2행 4열의 숫자에 4행 2열의 숫자를 더한다. (행렬밖이면 에러 메시지 출력 ) (결과에서 1)
명령어 3 : 예 - 3 1 1 : 1행 1열의 숫자에 음수값을 출력 (결과에서 -1)
명령어 4 : 예 - 4 4 5 : 2행 4열의 숫자에 행렬의 최대값을 찾아서 대신 출력한다 (결과에서 5)
	결과 : (위 4개의 명령의 결과)
	 -1 0 0 1 1
	  1 1 5 1 0
*/


int Question_Module_4(void) {
	int board[5][4] = { 0 };
	int i, j;
	int a=0, b=0;
	int select_menu = 0;
	for (i = 0; i < 4; ++i) {
		for (j = 0; j < 5; ++j) {
			board[j][i] = rand() % 2;
		}
	}

	while (1) {

		for (i = 0; i < 4; ++i) {
			for (j = 0; j < 5; ++j) {
				printf("%2d", board[j][i]);
			}
			printf("\n");
		}
		scanf("%d %d %d", &select_menu, &a, &b ); //a행 b열 (4X5)
		getchar();

		if (select_menu == 5)
			break;
		if (4<a || 5<b || a<0 || b<0) {
			printf("잘못입력해따 \n");
			a = 0;
			b = 0;
			continue;
		}

		--a;
		--b;

		switch (select_menu) {
		case 1: {
			Command_1(a, b, board);
			a = 0;
			b = 0;
			continue;
		}
		case 2: {
			if ( 4<a||4<b ) {
				printf("잘못입력해따 \n");
				a = 0;
				b = 0;
				continue;
			}
			
			Command_2(a, b, board);
			a = 0;
			b = 0;
			continue;
		}
		case 3: {
			Command_3(a, b, board);
			a = 0;
			b = 0;
			continue;
		}
		case 4: {
			Command_4(a, b, board);
			a = 0;
			b = 0;
			continue;
		}
		case 5: 
			break;
		default: {
			printf("다시 입력하라\n");
			a = 0;
			b = 0;
			continue;
		}
			
			


	
	}
		break;
	}
	return 0;
}
//a 행 b열에 5 곱하기
int Command_1(int a, int b, int board[][4]) {
	board[b][a] *= 5;
}
//a 행 b열에 b행 a열을 더한다
int Command_2(int a, int b, int board[][4]) {
	board[b][a] += board[a][b];
}
//a 행 b열에 음수값을 출력한다
int Command_3(int a, int b, int board[][4]) {
	board[b][a] *= -1;
}
//a 행 b열에 행렬 최대값을 대신 출력한다
int Command_4(int a, int b, int board[][4]) {
	int i = 0, j = 0;
	int temp = board[j][i];
	for (i = 0; i < 4; ++i) {
		for (j = 0; j < 5; ++j) {
			if (board[j][i] > temp)
				temp = board[j][i];
		}
		board[b][a] = temp;
	}
}