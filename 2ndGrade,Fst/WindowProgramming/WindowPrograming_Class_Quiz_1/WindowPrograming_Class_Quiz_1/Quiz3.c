/*
����ڰ� �Է��ϴ� ���ڿ��� ����ϰ�, �빮�ڴ� �ҹ��ڷ�, �ҹ��ڴ� �빮�ڷ� �ٲٰ� ������
�Ųٷ� �����Ͽ� ����Ѵ�.
*/

int Question_Module_3(void) {
	char *array = (char*)malloc(sizeof(char)); // �󸶳� �Է��� �� �𸣴� �����迭�� �Ҵ��Ѵ�
	int i,j,max;
	int temp;

	printf("Input Stance : ");
	gets(array); //���ڿ��� �޴´�

	printf("You Entered  ");
	for (i = 0; array[i]!='\0'; ++i) {
		printf("%c", array[i]);
	} // ���ڿ� ���
	printf("\n");

	for (i = 0; array[i] != '\0'; ++i) {
		if (97 <= array[i] && array[i] <= 122)
			array[i] -= 32; // a~z �����Ͻ� 32�� ���� A~Z �� ����� (ASCII CODE)
		else if (65 <= array[i] && array[i] <= 90)
			array[i] += 32; // A~Z �����Ͻ� 32�� ���� a~z �� ����� (ASCII CODE)
	}

	max = i; // �迭 ũ��(�߰����� ����ϱ�����)
	j = i-1; // ������ ĭ�� ���ڸ� ù��° ���ڿ� �¹ٲٱ� ���� �����Ѵ�

	for (i = 0 ; i <= (max/2) ;++i) { // �� �հ� �� �ڸ� �ٲٰ� ���� 2��°, ������ �տ��� �ٲٰ� ,,,,,
		temp = array[i];
		array[i] = array[j];
		array[j] = temp;
		--j;
	}


	for (i = 0; array[i] != '\0'; ++i) {
		printf("%c", array[i]);
	} // ���ڿ� ���
	printf("\n");

	printf("\n");

	// free(array); �� ������ ����
	return 0;

}