/*
up-down 게임 만들기
컴퓨터가 1부터 100사이 임의수인 목표수를 정한다
컴퓨터와 사용자가 번갈아 숫자를 제시하면 목표수와 비교하여 업다운을 나타낸다
사용자가 임의 숫자 제시하면 그 수와 목표수를 비교해 업 또는 다운을 나타낸다
컴퓨터가 가지고 있는 정보(목표수와 사용자가 입력한 임의의 수) 를 이용해 임의의 숫자 제시하고
다시 목표수와 비교해 업 또는 다운을 나타낸다
위와 같은 숫자 제시를 컴퓨터와 사용자가 각각 3번씩 하도록 하고, 4번째에 사용자가 숫자를
입력하고 목표수를 맞추거나 목표수가 더 가까운 숫자를 제시한 쪽이 승리한다.
위 게임을 최소 2번 이상 연달아 하고 컴퓨터와 사용자의 승률을 계산한다
Goal Numver setting finished
Input : 49 - down
AI Input : 34 - down
Input : 19 - up
AI Input : 33 - down
Input : 35 - Player Win!
New game begin : Y/N

위 게임을 2번 이상 한 후 사용자의 컴퓨터의 승률을 출력한다 (승률(%)계산  : 이긴 게임수/전체 게임수 * 100)
*/


int Question_Module_7(void) {

	int goal = 0;
	int i;
	int ai_number = 0;
	int player_number = 0;
	int player_min = 0; // 플레이어가 입력한 최소값
	int player_max = 0; // 플레이어가 입력한 최대값
	int ai_min = 0; // 알파고의 최소값
	int ai_max = 0; // 알파고의 최대값
	int player_final_number=0; // 플레이어와 목표값 사이 수
	int ai_final_number=0; // AI와 목표값 사이 수

	char command = 'a';
	float rating = 0; // 승률 계산
	float game = 0; // 플레이한 게임 수
	float win = 0; // 승리 수
	int restart = 0; // 다시 플레이 할건지 여부

	while (1) {
		player_min = 0; // 플레이어가 입력한 최소값
		player_max = 100; // 플레이어가 입력한 최대값
		ai_min = 0; // 알파고의 최소값
		ai_max = 100; // 알파고의 최대값
		restart = 0;

		goal = (rand() % 100) + 1;
		printf("Goal number setting finished\n");
		++game;

		for (i = 0; i < 3; ++i) {

			///////////////////////플레이어의 턴/////////////////////////////
			printf("Input : ");
			scanf("%d", &player_number);
			getchar();
			if (player_number <= 0 || 100 < player_number) { // 오류 측정
				printf("Plz Insert again \n");
				continue;
			}

			if (player_number == goal) { // 승리하면 바로 나간다
				break;
			}
			else { // 아니라면 업인지 다운인지 검사를 해보자
				if (player_number < goal) {
					printf(" --- Up\n");
					if (player_min < player_number)
						player_min = player_number;
					if (ai_min < player_min) { //AI의 최소값보다 플레이어 최소값이 높으면 플레이어걸 참고한다
						ai_min = player_min;
					}
				}
				else if (player_number > goal) {
					printf(" --- down\n");
					if (player_number < player_max)
						player_max = player_number;
					if (player_max < ai_max) { //AI의 최대값보다 플레이어 최대값이 낮으면 플레이어걸 참고한다
						ai_max = player_max;
					}
				}
			}
			////////////////////////////////////////////////////////////////////////////////
			/////////////////////////////////AI 턴 ///////////////////////////////////
			do {
				ai_number = rand() % ai_max; //값을 만족할때까지 계속 수를 뽑는다
			} while (ai_min > ai_number);

			printf("AI Input : %d", ai_number);
			if (ai_number == goal) { // 승리하면 바로 나간다
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
			if (ai_number == goal) { //AI가 이겼다 특이점은 온다!
				printf("Goal Number : %d \n", goal);
				printf("AI win\n");
			}
			else if (player_number == goal) { //내가 이겼다 팝콘을 가져와라
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
				printf("Player Closer Point : %d\nAI Closer Point : %d\n",player_final_number,ai_final_number); //누가 더 가까운지 표시 낮을수록 가까운거

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

			printf("rating : %0.2f\n", rating); // 승률출력
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