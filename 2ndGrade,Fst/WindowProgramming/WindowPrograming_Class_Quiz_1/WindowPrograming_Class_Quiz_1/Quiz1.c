/*1~1000 숫자중에서 3배수거나 7배수 합계 (중복숫자는 한번만 더한다.)구하는 프로그램을 함수 사용하여 구현(모든 배수 출력) */

int Question_Module_1(void){
	int surplus = 0;
	multiply_number_array(3,3,&surplus);
	multiply_number_array(7,7,&surplus);
	multiply_number_array(3,7,&surplus);
	printf("3의 배수이거나 7의 배수의 수의 합계 : %d \n",surplus);
	return 0;
}



int multiply_number_array(int number1, int number2, int *surplus) {
	int i;
	int multiply[2000] = { 0 }; //!!!  {0} 로 초기화 필수 !!!!
	int temp = 0;
	int the_surplus = 0;

	for (i = 1; i <= 1000; ++i) {
		if (number1 == number2) {
			if (i % number1 == 0) {
				multiply[temp] = i; //배열에 배수값을 저장한다
				the_surplus += multiply[temp]; // 배수에 수를 더한다
				++temp;
			}
		}
		else {
			if (i % number1 == 0 && i % number2 == 0) {
				multiply[temp] = i; //배열에 배수값을 저장한다
				the_surplus += multiply[temp]; // 배수에 수를 더한다
				++temp;
				}
			}
		}

		if (number1 == number2) {
			*surplus += the_surplus;
			printf("%d의배수 출력 : ", number1);
			for (i = 0; multiply[i] != '\0'; ++i) {
				printf("%4d ", multiply[i]);
			}			
		}
		else 
			*surplus -= the_surplus; //포인터 이용

	printf("\n");

}