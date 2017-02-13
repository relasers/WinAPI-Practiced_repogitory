/*
사용자가 입력하는 문자열을 출력하고, 대문자는 소문자로, 소문자는 대문자로 바꾸고 순서를
거꾸로 저장하여 출력한다.
*/

int Question_Module_3(void) {
	char *array = (char*)malloc(sizeof(char)); // 얼마나 입력할 지 모르니 동적배열로 할당한다
	int i,j,max;
	int temp;

	printf("Input Stance : ");
	gets(array); //문자열을 받는다

	printf("You Entered  ");
	for (i = 0; array[i]!='\0'; ++i) {
		printf("%c", array[i]);
	} // 문자열 출력
	printf("\n");

	for (i = 0; array[i] != '\0'; ++i) {
		if (97 <= array[i] && array[i] <= 122)
			array[i] -= 32; // a~z 사이일시 32를 빼서 A~Z 로 만든다 (ASCII CODE)
		else if (65 <= array[i] && array[i] <= 90)
			array[i] += 32; // A~Z 사이일시 32를 더해 a~z 로 만든다 (ASCII CODE)
	}

	max = i; // 배열 크기(중간점을 계산하기위해)
	j = i-1; // 마지막 칸의 숫자를 첫번째 숫자와 맞바꾸기 위해 선언한다

	for (i = 0 ; i <= (max/2) ;++i) { // 맨 앞과 맨 뒤를 바꾸고 이후 2번째, 마지막 앞에거 바꾸고 ,,,,,
		temp = array[i];
		array[i] = array[j];
		array[j] = temp;
		--j;
	}


	for (i = 0; array[i] != '\0'; ++i) {
		printf("%c", array[i]);
	} // 문자열 출력
	printf("\n");

	printf("\n");

	// free(array); 왜 오류가 날까
	return 0;

}