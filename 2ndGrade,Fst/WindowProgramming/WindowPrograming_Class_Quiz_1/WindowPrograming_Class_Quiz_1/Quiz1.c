/*1~1000 �����߿��� 3����ų� 7��� �հ� (�ߺ����ڴ� �ѹ��� ���Ѵ�.)���ϴ� ���α׷��� �Լ� ����Ͽ� ����(��� ��� ���) */

int Question_Module_1(void){
	int surplus = 0;
	multiply_number_array(3,3,&surplus);
	multiply_number_array(7,7,&surplus);
	multiply_number_array(3,7,&surplus);
	printf("3�� ����̰ų� 7�� ����� ���� �հ� : %d \n",surplus);
	return 0;
}



int multiply_number_array(int number1, int number2, int *surplus) {
	int i;
	int multiply[2000] = { 0 }; //!!!  {0} �� �ʱ�ȭ �ʼ� !!!!
	int temp = 0;
	int the_surplus = 0;

	for (i = 1; i <= 1000; ++i) {
		if (number1 == number2) {
			if (i % number1 == 0) {
				multiply[temp] = i; //�迭�� ������� �����Ѵ�
				the_surplus += multiply[temp]; // ����� ���� ���Ѵ�
				++temp;
			}
		}
		else {
			if (i % number1 == 0 && i % number2 == 0) {
				multiply[temp] = i; //�迭�� ������� �����Ѵ�
				the_surplus += multiply[temp]; // ����� ���� ���Ѵ�
				++temp;
				}
			}
		}

		if (number1 == number2) {
			*surplus += the_surplus;
			printf("%d�ǹ�� ��� : ", number1);
			for (i = 0; multiply[i] != '\0'; ++i) {
				printf("%4d ", multiply[i]);
			}			
		}
		else 
			*surplus -= the_surplus; //������ �̿�

	printf("\n");

}