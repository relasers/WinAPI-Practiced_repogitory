/*
�ؽ�Ʈ ��� ���� �����
����ڰ� �Է��ϴ� ������ �����ڸ� 2���� ���������� ����ϴ� ���α׷��� �����Ѵ�
���) Input numbers 3*4*5*2
result 3*4*5*2 = 70
*/

int Question_Module_5(void) {
	char str[200] = { 0 };
	char temp1[30] = { 0 }; // ���� �ӽ� ���� �迭
	int temp2[10] = { 0 }; // ���� ���� ����
	int temp3[10] = { 0 }; // �����ȣ ����
	int number=0; // ���ڸ� ����Ѵ�
	int i, j, k, m;
	int temp_num1 = 0; //�ڸ��� �Ǵ�
	int temp_num2 = 0;
	printf("Input Numbers ");

	gets(str);

	i = 0;
	k = 0;
	m = 0;
	while(1) {
		if ('0' <= str[i] && str[i] <= '9') {
			temp1[temp_num1] = str[i];
			++temp_num1;
		}
		else { //���ڸ������ۿ� �ν��� ���ϰ� �־� n�̤�
			temp3[k] = str[i];
			m = temp_num1-1;
			for (j = 0; j < temp_num1; ++j) {
				if (temp1[j] != '0'&&m!=j)
					temp2[k] += (temp1[j] - 48) * 10 * (m - j);
				else if (temp1[j] != '0'&&m == j)
					temp2[k] += (temp1[j] - 48);
				else
					temp2[k] += 10 * (m - j);
			}
			++k;
			for (m = 0; m < 30; ++m) {
				temp1[m] = '\0';
			}	
			temp_num1 = 0;
		}
		
		if (str[i] == '\0')
			break;
		++i;
		
	}




	printf("\n");
	printf("result %s\n",str);

	for (i = 0; i < 10; ++i)
		printf("%3d",temp2[i]);
	printf("\n");
	for (i = 0; i < 10; ++i)
		printf("%3c", temp3[i]);
	printf("\n");

	number = temp2[0];

	for (i = 0; i < k; ++i) {
		switch (temp3[i]) {
		case '+':
			number += temp2[i + 1];
			continue;
		case '-':
			number -= temp2[i + 1];
			continue;
		case '*':
			number *= temp2[i + 1];
			continue;
		case '/':
			number /= temp2[i + 1];
			continue;
		default:
			break;
		}
	}
	printf("result %s = %d", str, number);

	printf("\n");
	return 0;
}