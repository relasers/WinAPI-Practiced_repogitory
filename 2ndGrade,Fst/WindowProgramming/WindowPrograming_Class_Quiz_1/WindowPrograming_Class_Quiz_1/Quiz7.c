/*
up-down ���� �����
��ǻ�Ͱ� 1���� 100���� ���Ǽ��� ��ǥ���� ���Ѵ�
��ǻ�Ϳ� ����ڰ� ������ ���ڸ� �����ϸ� ��ǥ���� ���Ͽ� ���ٿ��� ��Ÿ����
����ڰ� ���� ���� �����ϸ� �� ���� ��ǥ���� ���� �� �Ǵ� �ٿ��� ��Ÿ����
��ǻ�Ͱ� ������ �ִ� ����(��ǥ���� ����ڰ� �Է��� ������ ��) �� �̿��� ������ ���� �����ϰ�
�ٽ� ��ǥ���� ���� �� �Ǵ� �ٿ��� ��Ÿ����
���� ���� ���� ���ø� ��ǻ�Ϳ� ����ڰ� ���� 3���� �ϵ��� �ϰ�, 4��°�� ����ڰ� ���ڸ�
�Է��ϰ� ��ǥ���� ���߰ų� ��ǥ���� �� ����� ���ڸ� ������ ���� �¸��Ѵ�.
�� ������ �ּ� 2�� �̻� ���޾� �ϰ� ��ǻ�Ϳ� ������� �·��� ����Ѵ�
Goal Numver setting finished
Input : 49 - down
AI Input : 34 - down
Input : 19 - up
AI Input : 33 - down
Input : 35 - Player Win!
New game begin : Y/N

�� ������ 2�� �̻� �� �� ������� ��ǻ���� �·��� ����Ѵ� (�·�(%)���  : �̱� ���Ӽ�/��ü ���Ӽ� * 100)
*/


int Question_Module_7(void) {

	int goal = 0;
	int i;
	int ai_number = 0;
	int player_number = 0;
	int player_min = 0; // �÷��̾ �Է��� �ּҰ�
	int player_max = 0; // �÷��̾ �Է��� �ִ밪
	int ai_min = 0; // ���İ��� �ּҰ�
	int ai_max = 0; // ���İ��� �ִ밪
	int player_final_number=0; // �÷��̾�� ��ǥ�� ���� ��
	int ai_final_number=0; // AI�� ��ǥ�� ���� ��

	char command = 'a';
	float rating = 0; // �·� ���
	float game = 0; // �÷����� ���� ��
	float win = 0; // �¸� ��
	int restart = 0; // �ٽ� �÷��� �Ұ��� ����

	while (1) {
		player_min = 0; // �÷��̾ �Է��� �ּҰ�
		player_max = 100; // �÷��̾ �Է��� �ִ밪
		ai_min = 0; // ���İ��� �ּҰ�
		ai_max = 100; // ���İ��� �ִ밪
		restart = 0;

		goal = (rand() % 100) + 1;
		printf("Goal number setting finished\n");
		++game;

		for (i = 0; i < 3; ++i) {

			///////////////////////�÷��̾��� ��/////////////////////////////
			printf("Input : ");
			scanf("%d", &player_number);
			getchar();
			if (player_number <= 0 || 100 < player_number) { // ���� ����
				printf("Plz Insert again \n");
				continue;
			}

			if (player_number == goal) { // �¸��ϸ� �ٷ� ������
				break;
			}
			else { // �ƴ϶�� ������ �ٿ����� �˻縦 �غ���
				if (player_number < goal) {
					printf(" --- Up\n");
					if (player_min < player_number)
						player_min = player_number;
					if (ai_min < player_min) { //AI�� �ּҰ����� �÷��̾� �ּҰ��� ������ �÷��̾�� �����Ѵ�
						ai_min = player_min;
					}
				}
				else if (player_number > goal) {
					printf(" --- down\n");
					if (player_number < player_max)
						player_max = player_number;
					if (player_max < ai_max) { //AI�� �ִ밪���� �÷��̾� �ִ밪�� ������ �÷��̾�� �����Ѵ�
						ai_max = player_max;
					}
				}
			}
			////////////////////////////////////////////////////////////////////////////////
			/////////////////////////////////AI �� ///////////////////////////////////
			do {
				ai_number = rand() % ai_max; //���� �����Ҷ����� ��� ���� �̴´�
			} while (ai_min > ai_number);

			printf("AI Input : %d", ai_number);
			if (ai_number == goal) { // �¸��ϸ� �ٷ� ������
				break;
			}
				if (ai_number < goal) {
					printf(" --- Up\n");
					if (ai_min <= ai_number)
						ai_min = ai_number;
				}
				else if (ai_number > goal) {
					printf(" --- down\n");
					if (ai_number < ai_max)
						ai_max = ai_number;
				}
			}
				//////////////////////////////////////////////////////////////////////////
			if (ai_number == goal) { //AI�� �̰�� Ư������ �´�!
				printf("Goal Number : %d \n", goal);
				printf("AI win\n");
			}
			else if (player_number == goal) { //���� �̰�� ������ �����Ͷ�
				printf("Goal Number : %d \n", goal);
				printf("Player win\n");
				++win;
			}
			else {
				if (player_number < goal)
					player_final_number = goal - player_number;
				else
					player_final_number = player_number - goal;

				if (ai_number < goal)
					ai_final_number = goal - ai_number;
				else
					ai_final_number = ai_number - goal;
				printf("\n");
				printf("Goal Number : %d \n", goal);
				printf("Player Closer Point : %d\nAI Closer Point : %d\n",player_final_number,ai_final_number); //���� �� ������� ǥ�� �������� ������

				if (player_final_number < ai_final_number) {
					printf("Player win\n");
					++win;
				}
				else if (ai_final_number < player_final_number) {
					printf("AI win\n");
				}
				else
					printf("Draw!\n");



			}
			



			rating = (win / game) * 100;

			printf("rating : %0.2f\n", rating); // �·����
			while (1) {
				printf("Continue? (Y/N) : ");
				scanf("%c", &command);
				getchar();

				if (command == 'n' || command == 'N')
					break;
				else if (command == 'y' || command == 'Y') {
					++restart;
					break;
				}
				else {
					printf("Plz re insert command : ");
					continue;
				}

			}

			if (0 < restart)
				continue;
			else
				break;
		}
	return 0;
}