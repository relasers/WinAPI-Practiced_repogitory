/* <달력만들기>
2016년 3월 1일이 화요일일때 , 2016년의 달력을 기본적으로 출력하고, 사용자가 입력하는 날짜의 요일을 계산하고
그 달 포맷을 맟줘 출력하고 해당 요일도 함께 출력한다.(입력날짜는 2010년부터 2020년까지로 제한,switch case 사용)
2016/03/01 : Tuesday
2010/12/31 : Friday
2013/06/21 : Friday
2015/03/01 : Sunday
윤년(2월 29일까지인해) : 4년마다 윤년이 돌아오고, 100의 배수의 해는 윤년이 아니다, 또는 400으로 나눠지느 해는 윤년이다
*/

int Question_Module_8(void) {

	int end_day[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
	int year = 2016;
	int month = 2;
	int day = 0;
	int year_day = 0;
	int end_week = 5; // 달의 마지막 주 (초기값)
	int calander_end = 0;
	int i,j;

	if (month == 2 && ((year % 4 == 0) && ((year % 100 != 0) || (year % 400 == 0)))) //2월일때, 100으로 나눠지지 않거나 400으로 나눠지며, 4로 나눠지면 윤년
		end_day[1] = 29; //조건 만족시 윤년
	else
		end_day[1] = 28; //불만족시 28 
	/////////////////////////////////2016 달력 출력하기 위해서만 존재하는 코드/////////////////////////////////////////////////////////////////////////////////////
	month = 0;
	//2016 1월 1일 = 금요일
	printf("2016년 달력\n");
	for (j = 0; j < 12; ++j) {
		calander_end = 0;
		printf("%d월 달력\n", month + 1);
		printf(" 일 월 화 수 목 금 토\n");

		for (i = -end_week; i <= end_day[month]; ++i) {
			if (i <= 0)
				printf("   ");
			else
				printf("%3d", i);

			if (calander_end%7 == 0)
				printf("\n");
			++calander_end;
		}

		end_week = (calander_end % 7)-1 ;
		if (end_week < 0) // 끝주가 음수가 되면 초기값으로 되돌려준다
			end_week = 6;
		++month;

		if (j == 6)
			getch(); // 일시정지
		printf("\n");
	}
	
	printf("\n");
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	while (1) {

		printf("년도와 달과 날짜를 입력하라 : ");
		scanf("%d %d %d", &year,&month,&day);
		getchar();

		if (month == 2 && ((year % 4 == 0) && ((year % 100 != 0) || (year % 400 == 0)))) //2월일때, 100으로 나눠지지 않거나 400으로 나눠지며, 4로 나눠지면 윤년
			end_day[1] = 29; //조건 만족시 윤년
		else
			end_day[1] = 28; //불만족시 28

		if ( (year<2010||2020<year)||(end_day[month-1]<day)||(month<0||12<month) ) {
			printf("뭔가 잘못되었다 다시 입력하라\n"); 
			continue;
		}

		printf("%d/%d/%d : ",year,month,day);

		year_day = year + ( year / 4 ) - ( year / 100 ) + ( year / 400 ) + (13 * month + 8) / 5 + day; //Zeller 공식을 인터넷에서 긁어왔다 감사합니다 제라님!
	

		switch (year_day% 7) {
		case 0:
			printf("Sunday\n");
			continue;
		case 1:
			printf("Monday\n");
			continue;
		case 2:
			printf("Tuesday\n");
			continue;
		case 3:
			printf("Wednesday\n");
			continue;
		case 4:
			printf("Thursday\n");
			continue;
		case 5:
			printf("Friday\n");
			continue;
		case 6:
			printf("Saturday\n");
			continue;
		}
			
	}
	
	

	return 0;
}