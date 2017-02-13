/*
����ڰ� �Է��ϴ� ���� ���� �� �Ǵ� �簢���� ������ �߽ɰ��� ����Ѵ� ���α׷��� �����Ѵ�.
����ü�� �ּ� 2���� ����Ѵ�

����ü ��(point) ����ü ��� =x, y
����ü �簢�� �Ǵ� �� : ����ü ��� = int Ÿ�� , point �߽���, float ����
��ɾ� (1:�簢��, 2: ��) ���� ���� ��ǥ�� (x,y) ���� ū ��ǥ�� (x,y) �Է¹޴´�

���) Input Command: 1 2 1 6 5 (�簢��, �����ϴ� ��ǥ��(2,1) ������� ��ǥ�� (6, 5)
	��� : �簢�� : �߽���ǥ (x,y)-(4,3) ���� - 16
      Input Command: 2 2 1 6 5 (��, �����ϴ� ��ǥ��(2,1) ������� ��ǥ��(6,5))
	��� : �� �߽���ǥ (x,y)-(4,3) ����-12.56
	(Ÿ���� ��쿣 �����޼��� ���)
*/

typedef struct point {
	float x;
	float y;
}Point; // 6������ �� ����ü ���

typedef struct shape {
	int type;
	Point point_center;
	float size;
}Shape; // 6������ ���� ����ü ���

int Question_Module_6(void) {

	Point left_point = { 0,0 };
	Point right_point = { 0,0 };
	Shape shape = {0,0,0,0};

	while (1) {

		printf("�Է¼��� : type �����ϴ�x �����ϴ�y �������x �������y\n");
		printf("type = 1:�簢�� , type = 2:�� , type 3:���� \n");
		printf("Input Command : ");
		scanf("%d %f %f %f %f", &shape.type, &left_point.x, &left_point.y, &right_point.x, &right_point.y);
		getchar();

		if ((left_point.x > right_point.x) || (left_point.y > right_point.y)) {
			printf("������ܰ� ��������� ���Ѷ�\n");
			continue;
		}
			
		if (!(shape.type == 1 || shape.type || 2)) {
			printf("�߸��� ���� Ÿ���̴�\n");
			continue;
		}
		if ((shape.type == 2)&&!((right_point.x-left_point.x) == (right_point.y-left_point.y)))  {
			printf("�� Ÿ���� ��� ���Ѵ�\n");
			continue;
		}

		switch (shape.type) {
		case 1: {
			shape.point_center.x = (right_point.x - left_point.x)/2 + left_point.x;
			shape.point_center.y = (right_point.y - left_point.y)/2 + left_point.y;
			shape.size = (right_point.x - left_point.x)*(right_point.y - left_point.y);
			printf("�簢�� : �߽���ǥ : (x,y)-(%0.1f,%0.1f) ���� - %0.1f\n", shape.point_center.x, shape.point_center.y, shape.size);
			continue;
		}

		case 2: {
			shape.point_center.x = (right_point.x - left_point.x) / 2 + left_point.x;
			shape.point_center.y = (right_point.y - left_point.y) / 2 + left_point.y;
			shape.size = (shape.point_center.x - left_point.x)*(shape.point_center.x - left_point.x)*3.14;
			printf("�� : �߽���ǥ : (x,y)-(%0.1f,%0.1f) ���� - %0.2f\n", shape.point_center.x, shape.point_center.y, shape.size);
			continue;
		}
		case 3: {
			printf("������\n");
			break;
		}
		default:
			continue;
		}
		break;
	}
	



	return 0;
}