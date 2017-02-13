/* �迭 ����ϱ�
 4X5 �迭�� 2���� ���� ������ �� (0 �Ǵ� 1) �� �����ϰ� ����ڰ� �Է��ϴ� ��� ���� �ش��ϴ� ���ڸ� 
 ����ڰ� �Է��ϴ� 4���� ��ɾ ���� �ٲپ� ����Ͻÿ� (�ּҿ� ���� ȣ������ ����ϴ� �Լ��� ����Ͽ� ����� �����Լ����� �Ѵ�)
 ex>> ��İ� : 1 0 0 1 1
               1 1 1 0 0
			   0 1 1 1 0
			   0 1 0 1 1
[�Է�] ��ɾ� �� ��
��ɾ� 1 : �� - 1 2 3 : 2�� 3���� ���ڿ� 5�� ���Ͽ� ��� (������� 5)
��ɾ� 2 : �� - 2 2 4 : 2�� 4���� ���ڿ� 4�� 2���� ���ڸ� ���Ѵ�. (��Ĺ��̸� ���� �޽��� ��� ) (������� 1)
��ɾ� 3 : �� - 3 1 1 : 1�� 1���� ���ڿ� �������� ��� (������� -1)
��ɾ� 4 : �� - 4 4 5 : 2�� 4���� ���ڿ� ����� �ִ밪�� ã�Ƽ� ��� ����Ѵ� (������� 5)
	��� : (�� 4���� ����� ���)
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
		scanf("%d %d %d", &select_menu, &a, &b ); //a�� b�� (4X5)
		getchar();

		if (select_menu == 5)
			break;
		if (4<a || 5<b || a<0 || b<0) {
			printf("�߸��Է��ص� \n");
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
				printf("�߸��Է��ص� \n");
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
			printf("�ٽ� �Է��϶�\n");
			a = 0;
			b = 0;
			continue;
		}
			
			


	
	}
		break;
	}
	return 0;
}
//a �� b���� 5 ���ϱ�
int Command_1(int a, int b, int board[][4]) {
	board[b][a] *= 5;
}
//a �� b���� b�� a���� ���Ѵ�
int Command_2(int a, int b, int board[][4]) {
	board[b][a] += board[a][b];
}
//a �� b���� �������� ����Ѵ�
int Command_3(int a, int b, int board[][4]) {
	board[b][a] *= -1;
}
//a �� b���� ��� �ִ밪�� ��� ����Ѵ�
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