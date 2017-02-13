/* <�޷¸����>
2016�� 3�� 1���� ȭ�����϶� , 2016���� �޷��� �⺻������ ����ϰ�, ����ڰ� �Է��ϴ� ��¥�� ������ ����ϰ�
�� �� ������ ���� ����ϰ� �ش� ���ϵ� �Բ� ����Ѵ�.(�Է³�¥�� 2010����� 2020������� ����,switch case ���)
2016/03/01 : Tuesday
2010/12/31 : Friday
2013/06/21 : Friday
2015/03/01 : Sunday
����(2�� 29�ϱ�������) : 4�⸶�� ������ ���ƿ���, 100�� ����� �ش� ������ �ƴϴ�, �Ǵ� 400���� �������� �ش� �����̴�
*/

int Question_Module_8(void) {

	int end_day[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
	int year = 2016;
	int month = 2;
	int day = 0;
	int year_day = 0;
	int end_week = 5; // ���� ������ �� (�ʱⰪ)
	int calander_end = 0;
	int i,j;

	if (month == 2 && ((year % 4 == 0) && ((year % 100 != 0) || (year % 400 == 0)))) //2���϶�, 100���� �������� �ʰų� 400���� ��������, 4�� �������� ����
		end_day[1] = 29; //���� ������ ����
	else
		end_day[1] = 28; //�Ҹ����� 28 
	/////////////////////////////////2016 �޷� ����ϱ� ���ؼ��� �����ϴ� �ڵ�/////////////////////////////////////////////////////////////////////////////////////
	month = 0;
	//2016 1�� 1�� = �ݿ���
	printf("2016�� �޷�\n");
	for (j = 0; j < 12; ++j) {
		calander_end = 0;
		printf("%d�� �޷�\n", month + 1);
		printf(" �� �� ȭ �� �� �� ��\n");

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
		if (end_week < 0) // ���ְ� ������ �Ǹ� �ʱⰪ���� �ǵ����ش�
			end_week = 6;
		++month;

		if (j == 6)
			getch(); // �Ͻ�����
		printf("\n");
	}
	
	printf("\n");
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	while (1) {

		printf("�⵵�� �ް� ��¥�� �Է��϶� : ");
		scanf("%d %d %d", &year,&month,&day);
		getchar();

		if (month == 2 && ((year % 4 == 0) && ((year % 100 != 0) || (year % 400 == 0)))) //2���϶�, 100���� �������� �ʰų� 400���� ��������, 4�� �������� ����
			end_day[1] = 29; //���� ������ ����
		else
			end_day[1] = 28; //�Ҹ����� 28

		if ( (year<2010||2020<year)||(end_day[month-1]<day)||(month<0||12<month) ) {
			printf("���� �߸��Ǿ��� �ٽ� �Է��϶�\n"); 
			continue;
		}

		printf("%d/%d/%d : ",year,month,day);

		year_day = year + ( year / 4 ) - ( year / 100 ) + ( year / 400 ) + (13 * month + 8) / 5 + day; //Zeller ������ ���ͳݿ��� �ܾ�Դ� �����մϴ� �����!
	

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