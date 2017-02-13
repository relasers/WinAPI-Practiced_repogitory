

int Question_Module_1(void); //첫번째 문제
int Question_Module_2(void); //두번째 문제
int Question_Module_3(void); //세번째 문제
int Question_Module_4(void); //네번째 문제
int Question_Module_5(void); //다섯번째 문제
int Question_Module_6(void); //여섯번째 문제
int Question_Module_7(void); //일곱번째 문제
int Question_Module_8(void); //여덟번째 문제

int Running_Module(int Select_Module); // 모듈선택 함수

int multiply_number_array(int number1,int number2,int *surplus); //첫번째 문제 배열 표시 및 더하기
int Generate_numbers(int number,int arr[]);
int Command_A(int arr[]); // 오름차순 정렬
int Command_D(int arr[]); // 내림차순 정렬
int Command_R(int arr[]); // 랜덤 재정렬
int Command_M(int arr[]); // 최대값 산출
int Command_I(int arr[]); // 최소값 산출

int Command_check(char* select);

int Command_1(int a, int b, int board[][4]); // 4번문제 1번 명령어
int Command_2(int a, int b, int board[][4]); // 4번문제 2번 명령어
int Command_3(int a, int b, int board[][4]); // 4번문제 3번 명령어
int Command_4(int a, int b, int board[][4]); // 4번문제 4번 명령어

