/*
텍스트 기반 계산기 만들기
사용자가 입력하는 숫자의 연산자를 2개씩 연속적으로 계산하는 프로그램을 구현한다
결과) Input numbers 3*4*5*2
result 3*4*5*2 = 70
*/

int Question_Module_5(void) {
	char str[200] = { 0 };
	char temp1[30] = { 0 }; // 숫자 임시 저장 배열
	int temp2[10] = { 0 }; // 최종 숫자 저장
	int temp3[10] = { 0 }; // 연산기호 저장
	int number=0; // 숫자를 계산한다
	int i, j, k, m;
	int temp_num1 = 0; //자릿수 판단
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
		else { //두자리까지밖에 인식을 못하고 있엉 nㅜㅜ
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