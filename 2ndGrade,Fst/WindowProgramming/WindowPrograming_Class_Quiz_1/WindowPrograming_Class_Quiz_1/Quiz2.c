/*
2. �����ϰ� �˻��ϱ� (���� �޸� �Ҵ� ����ϱ�)
����ڰ� �Է��ϴ� ���ں��� ���� ������ ���� 20�� ����� (�ߺ��Ұ�) ������ ��ɾ �����Ѵ� (�Լ����)
A : ������������ ����
D : ������������ ����
R : �����ϰ� ������
M : �ִ밪 ���
I : �ּҰ� ���
��� ) Input number : 50
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
	char select[1] = {0}; // Ŀ�ǵ� ���ڸ� �޴´�
	int final_select = 0; // ��ȯ�� ������ �޴�
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
	printf("Command A : �������� ���� \n");
	printf("Command D : �������� ���� \n");
	printf("Command R : �������� ������ \n");
	printf("Command M : �ּҰ� ��� \n");
	printf("Command I : �ּҰ� ��� \n");
	printf("Command E : ������\n\n");
	printf("\n");

	while (1) {
		printf("Please Insert Command : ");

		select[0] = getch();
		printf("%c",select[0]);
		final_select = Command_check(select[0]);

		printf("\n");

		switch (final_select) {
		case 0: 
			Command_A(arr); // �迭 �������� ����
			continue;
		case 1: 
			Command_D(arr); // �迭 �������� ����
			continue;
		case 2:
			Command_R(arr); // ���� ������
			continue;
		case 3:
			Command_M(arr); // �ִ밪 ���
			continue;
		case 4:
			Command_I(arr); // �ּҰ� ���
			continue;
		case 5:
			break;
		default:
			printf("�ٽð��\n");
			continue;
		}
		break;

	}

	free(arr); //�迭 �޸𸮸� ��ȯ�Ѵ�
	return 0;
}
//���� ����
int Generate_numbers(int number,int arr[]) {
	int temp_str[20] = { 0 };
	int i,j;
	int repeat_number = 0; // �ߺ��Ǵ°� ã�� ����
	int temp;
	for (i = 0; i < 20; ++i) {
		
		repeat_number = 0; // �ߺ�üũ ������ �ٽ� 0���� �ʱ�ȭ �Ѵ�.

		temp = ( rand()%number ); // �Է��� ���ڷ� ���� �������� �̴´�.
		temp_str[i] = temp; // �ϴ� �� ���� ���ڸ� �ӽù迭�� �����Ѵ�.

		for (j = 0 ; j < 20 ; ++j) {
			if (temp == temp_str[j])
				++repeat_number; // �迭 �� �ߺ��Ǵ� ���ڰ� ���� �� ī��Ʈ�� 1 �ø���
		} 
		if (1 < repeat_number) { --i; } // ���� ī��Ʈ�� 2 �̻��� ����ϸ� i���� �ϳ� ������.
										// �� �� ĭ�� ���ڸ� �ٽ� �̴´�
	}
	for (i = 0; i < 20; ++i) {
		arr[i] = temp_str[i]; // ���� �迭�� �ӽ� �迭�� �����Ѵ�.
	}

}

//�������� ����
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

//�������� ����
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

//�����ϰ� ������
int Command_R(int arr[]) {
	int i =0, j = 0;
	int temp1 = 0;
	int temp2 = 0;
	int *temp_str = (int*)malloc(sizeof(int));

	temp_str[0] =0;


	i = 0;
	while (1)
	{
		temp1 = ( rand() % 20 ); // ���ġ�� ���� ����
		temp2 = (rand() % 20 ); // ���ġ�� �Ű�ü���� ����
		if (!(temp1 == temp2)) {
			temp_str[0] = arr[temp1];
			arr[temp1] = arr[temp2];
			arr[temp2] = temp_str[0];
			++i;
		}
		if ( i > 30) break; //30���� ��迭�Ѵ�
	}


	free(temp_str);

	printf("COMMAND R  ");
	for (i = 0; i < 20; ++i) {
		printf("%4d", arr[i]);
	}
	printf("\n");

}

//�ִ밪 ���
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
//�ּҰ� ���
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
	int a=0; // �޴� ��ȯ��
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
	return a; // a���� ��ȯ�Ѵ�
}