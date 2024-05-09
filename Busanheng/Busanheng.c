#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LEN_MIN		15
#define LEN_MAX		50
#define PROB_MIN	10
#define PROB_MAX	90

int mainBusnaheng(void) {
	// 인트로
	system("title 20242397 류준서 부산헹");

	int train_length, p, count;
	count = 0;

	// 열차 길이 입력
	printf("기차의 길이를 입력해주세요. ( %d ~ %d )\n", LEN_MIN, LEN_MAX);
	scanf_s("%d", &train_length);
	if ((train_length < LEN_MIN) || (train_length > LEN_MAX)) {

		system("color cf");
		printf("\n\n");
		printf("'########:'########::'########:::'#######::'########::'####:\n");
		printf(" ##.....:: ##.... ##: ##.... ##:'##.... ##: ##.... ##: ####:\n");
		printf(" ##::::::: ##:::: ##: ##:::: ##: ##:::: ##: ##:::: ##: ####:\n");
		printf(" ######::: ########:: ########:: ##:::: ##: ########::: ##::\n");
		printf(" ##...:::: ##.. ##::: ##.. ##::: ##:::: ##: ##.. ##::::..:::\n");
		printf(" ##::::::: ##::. ##:: ##::. ##:: ##:::: ##: ##::. ##::'####:\n");
		printf(" ########: ##:::. ##: ##:::. ##:. #######:: ##:::. ##: ####:\n");
		printf("........::..:::::..::..:::::..:::.......:::..:::::..::....::\n");
		printf("\n\n");

		printf("입력된 기차 길이 값이 잘못되었습니다.\n");
		exit(0);
	}

	// 움직임 확률 입력
	printf("시민이 움직이지 못 할 확률을 입력해주세요. ( %d ~ %d )\n", PROB_MIN, PROB_MAX);
	scanf_s("%d", &p);
	if ((p < PROB_MIN) || (p > PROB_MAX)) {

		system("color cf");
		printf("\n\n");
		printf("'########:'########::'########:::'#######::'########::'####:\n");
		printf(" ##.....:: ##.... ##: ##.... ##:'##.... ##: ##.... ##: ####:\n");
		printf(" ##::::::: ##:::: ##: ##:::: ##: ##:::: ##: ##:::: ##: ####:\n");
		printf(" ######::: ########:: ########:: ##:::: ##: ########::: ##::\n");
		printf(" ##...:::: ##.. ##::: ##.. ##::: ##:::: ##: ##.. ##::::..:::\n");
		printf(" ##::::::: ##::. ##:: ##::. ##:: ##:::: ##: ##::. ##::'####:\n");
		printf(" ########: ##:::. ##: ##:::. ##:. #######:: ##:::. ##: ####:\n");
		printf("........::..:::::..::..:::::..:::.......:::..:::::..::....::\n");
		printf("\n\n");

		printf("입력된 확률 값이 잘못되었습니다.\n");
		exit(0);
	}

	printf("\n\n");
	printf(":'######::::::'###::::'##::::'##:'########:::::'######::'########::::'###::::'########::'########:'####:\n");
	printf("'##... ##::::'## ##::: ###::'###: ##.....:::::'##... ##:... ##..::::'## ##::: ##.... ##:... ##..:: ####:\n");
	printf(" ##:::..::::'##:. ##:: ####'####: ##:::::::::: ##:::..::::: ##:::::'##:. ##:: ##:::: ##:::: ##:::: ####:\n");
	printf(" ##::'####:'##:::. ##: ## ### ##: ######::::::. ######::::: ##::::'##:::. ##: ########::::: ##::::: ##::\n");
	printf(" ##::: ##:: #########: ##. #: ##: ##...::::::::..... ##:::: ##:::: #########: ##.. ##:::::: ##:::::..:::\n");
	printf(" ##::: ##:: ##.... ##: ##:.:: ##: ##::::::::::'##::: ##:::: ##:::: ##.... ##: ##::. ##::::: ##::::'####:\n");
	printf(". ######::: ##:::: ##: ##:::: ##: ########::::. ######::::: ##:::: ##:::: ##: ##:::. ##:::: ##:::: ####:\n");
	printf(":......::::..:::::..::..:::::..::........::::::......::::::..:::::..:::::..::..:::::..:::::..:::::....::\n");
	printf("\n\n");
	srand((unsigned int)time(NULL));

	// 위치 지정
	int c_pos, z_pos, m_pos;
	c_pos = train_length - 5; // 시민 위치
	z_pos = train_length - 2; // 좀비 위치
	m_pos = train_length - 1; // 마동석 위치

	// 열차 초기 상태 출력
	printf("--------------- 초 기 상 태 ---------------\n");
	//열차 상태 박스
	for (int i = 1; i <= train_length; i++) {
		printf("#");
	}
	printf("\n");
	for (int i = 1; i <= train_length; i++) {
		if (i == c_pos) {
			printf("C");
		}
		else if (i == z_pos) {
			printf("Z");
		}
		else if (i == m_pos) {
			printf("M");
		}
		else if ((i == train_length) || (i == 1)) {
			printf("#");
		}
		else {
			printf(" ");
		}
	}
	printf("\n");
	for (int i = 1; i <= train_length; i++) {
		printf("#");
	}
	printf("\n\n");
	// 4초 대기
	Sleep(4000);

	//시민 이동 변수
	int c_bpos;
	c_bpos = 0;

	// 좀비 이동 변수
	int z_bpos;
	z_bpos = 0;

	// 4초마다 이동
	while (1) {
		// 이동 성공 여부 변수
		int c_result, z_result;
		c_result = 0, z_result = 0;

		// 이동 결과 출력
		count += 1;
		printf("-------------- %d 번 째 결 과 --------------\n", count);

		// 이동 확률
		int c_per, z_per;
		c_per = rand() % 100 + 1;
		z_per = rand() % 100 + 1;


		// 시민 이동
		if (c_per <= p) {
			c_result = 0;
		}
		else if (c_per > p) {
			c_pos = c_pos - 1;
			c_bpos = c_pos + 1;
			c_result = 1;
		}

		// 좀비 이동
		if (count % 2 != 0) {
			if (z_per > p) {
				z_result = 0;
			}
			else if (z_per <= p) {
				z_pos = z_pos - 1;
				z_bpos = z_pos + 1;
				z_result = 1;
			}
		}
		else {
			z_result = 2;
		}

		//열차 상태 박스
		for (int i = 1; i <= train_length; i++) {
			printf("#");
		}
		printf("\n");
		for (int i = 1; i <= train_length; i++) {
			if (i == c_pos) {
				printf("C");
			}
			else if (i == z_pos) {
				printf("Z");
			}
			else if (i == m_pos) {
				printf("M");
			}
			else if ((i == train_length) || (i == 1)) {
				printf("#");
			}
			else {
				printf(" ");
			}
		}
		printf("\n");
		for (int i = 1; i <= train_length; i++) {
			printf("#");
		}
		printf("\n\n");

		// 시민 이동 성공 여부
		if (c_result == 0) {
			printf("시민 : 제자리 %d\n", c_pos - 1);
		}
		else if (c_result == 1) {
			printf("시민 : %d -> %d\n", c_bpos - 1, c_pos - 1);
		}

		// 좀비 이동 성공 여부
		if (z_result == 0) {
			printf("좀비 : 제자리 %d\n\n", z_pos - 1);
		}
		else if (z_result == 1) {
			printf("좀비 : %d -> %d\n\n", z_bpos - 1, z_pos - 1);
		}
		else if (z_result == 2) {
			printf("좀비 : 제자리 %d ( 움직일 수 없습니다. )\n\n", z_pos - 1);
		}

		// 성공 실패 여부 출력
		if (c_pos == 2) {
			printf("시민을 지키는데 성공하였습니다.\n");
			system("color 9f");
			break;
		}
		else if (z_pos == c_pos + 1) {
			printf("시민을 지키는데 실패하였습니다.\n");
			system("color 4f");
			break;
		}
		// 4초 대기
		Sleep(4000);
	}

	return 0;
}