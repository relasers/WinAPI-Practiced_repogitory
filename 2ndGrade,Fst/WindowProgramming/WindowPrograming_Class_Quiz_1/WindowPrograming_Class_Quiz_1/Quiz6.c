/*
사용자가 입력하는 값에 따라 원 또는 사각형의 면적과 중심값을 출력한느 프로그램을 구현한다.
구조체는 최소 2개를 사용한다

구조체 점(point) 구조체 멤버 =x, y
구조체 사각형 또는 원 : 구조체 멤버 = int 타입 , point 중심점, float 면적
명령어 (1:사각형, 2: 원) 가장 작은 좌표값 (x,y) 가장 큰 좌표값 (x,y) 입력받는다

결과) Input Command: 1 2 1 6 5 (사각형, 좌측하단 좌표값(2,1) 우측상단 좌표값 (6, 5)
	출력 : 사각형 : 중심좌표 (x,y)-(4,3) 면적 - 16
      Input Command: 2 2 1 6 5 (원, 좌측하단 좌표값(2,1) 우측상단 좌표값(6,5))
	출력 : 원 중심좌표 (x,y)-(4,3) 면적-12.56
	(타원인 경우엔 에러메세지 출력)
*/

typedef struct point {
	float x;
	float y;
}Point; // 6번문제 점 구조체 멤버

typedef struct shape {
	int type;
	Point point_center;
	float size;
}Shape; // 6번문제 도형 구조체 멤버

int Question_Module_6(void) {

	Point left_point = { 0,0 };
	Point right_point = { 0,0 };
	Shape shape = {0,0,0,0};

	while (1) {

		printf("입력순서 : type 좌측하단x 좌측하단y 우측상단x 우측상단y\n");
		printf("type = 1:사각형 , type = 2:원 , type 3:나감 \n");
		printf("Input Command : ");
		scanf("%d %f %f %f %f", &shape.type, &left_point.x, &left_point.y, &right_point.x, &right_point.y);
		getchar();

		if ((left_point.x > right_point.x) || (left_point.y > right_point.y)) {
			printf("좌측상단과 우측상단을 지켜라\n");
			continue;
		}
			
		if (!(shape.type == 1 || shape.type || 2)) {
			printf("잘못된 도형 타입이다\n");
			continue;
		}
		if ((shape.type == 2)&&!((right_point.x-left_point.x) == (right_point.y-left_point.y)))  {
			printf("난 타원은 계산 안한다\n");
			continue;
		}

		switch (shape.type) {
		case 1: {
			shape.point_center.x = (right_point.x - left_point.x)/2 + left_point.x;
			shape.point_center.y = (right_point.y - left_point.y)/2 + left_point.y;
			shape.size = (right_point.x - left_point.x)*(right_point.y - left_point.y);
			printf("사각형 : 중심좌표 : (x,y)-(%0.1f,%0.1f) 면적 - %0.1f\n", shape.point_center.x, shape.point_center.y, shape.size);
			continue;
		}

		case 2: {
			shape.point_center.x = (right_point.x - left_point.x) / 2 + left_point.x;
			shape.point_center.y = (right_point.y - left_point.y) / 2 + left_point.y;
			shape.size = (shape.point_center.x - left_point.x)*(shape.point_center.x - left_point.x)*3.14;
			printf("원 : 중심좌표 : (x,y)-(%0.1f,%0.1f) 면적 - %0.2f\n", shape.point_center.x, shape.point_center.y, shape.size);
			continue;
		}
		case 3: {
			printf("나간다\n");
			break;
		}
		default:
			continue;
		}
		break;
	}
	



	return 0;
}