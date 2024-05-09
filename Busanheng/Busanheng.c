#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 기차길이
#define LEN_MIN			15
#define LEN_MAX			50
// 확률
#define PROB_MIN		10
#define PROB_MAX		90
// 어그로 범위
#define AGGRO_MIN		0
#define AGGRO_MAX		5
// 좀비의 공격 대상
#define ATK_NONE		0
#define ATK_CITIZEN		1
#define ATK_DONGSEOK	2
// 마동석 이동 방향
#define MOVE_LEFT		1
#define MOVE_STAY		0
// 마동석 체력
#define STM_MIN			0
#define STM_MAX			5
// 마동석 행동
#define ACTION_REST		0
#define ACTION_PROVOKE  1
#define ACTION_PULL		2

int trainlength_input();
int percent_input();
int stm_inpput();
void start_msg();
void count_line(int);
void train_box(int, int, int, int);
int c_move(int, int, int, int*, int*, int*, int*);
int c_aggroMinMax(int);
int z_move(int, int, int, int, int, int*, int*);
int z_movewhere(int, int, int, int*, int*);
void c_moveresult(int, int, int, int, int);
void z_moveresult(int, int, int);

int main(void) {
	// 인트로
	system("title 20242397 류준서 부산헹");

	int train_length, p, stm, bstm = 0, count = 0;
	train_length = trainlength_input(); // 기차 길이 입력
	p = percent_input(); // 퍼센트 입력
	stm = stm_inpput(); // 체력 입력

	start_msg(); // 시작 메세지 출력

	srand((unsigned int)time(NULL)); // 난수 초기화

	// 위치 지정
	int c_pos, z_pos, m_pos;
	c_pos = train_length - 5; // 시민 위치
	z_pos = train_length - 2; // 좀비 위치
	m_pos = train_length - 1; // 마동석 위치

	count_line(count); // ~번째
	train_box(train_length, c_pos, z_pos, m_pos); // ~ 기차 상자
	printf("\n\n");

	// 전 좌표 표시
	int c_bpos = 0, z_bpos = 0, m_bpos = 0;

	// 어그로
	int c_aggro = 1, m_aggro = 1;

	// 마동석
	int m_move = 0, m_action = 0, m_action_f = 0;

	// 결과
	int c_result = 0, z_result = 0, m_result = 0;

	// 반복
	while (1) {
		count += 1;

		int _c_aggro, _c_pos, c_baggro, c_bpos;
		c_result = c_move(p, c_aggro, c_pos, &_c_aggro, &_c_pos, &c_baggro, &c_bpos); // 시민 이동
		c_pos = _c_pos;
		c_aggro = c_aggroMinMax(_c_aggro); // 시민 어그로 최댓값, 최솟값 확인

		int _z_pos, z_bpos;
		z_result = z_move(m_action_f, count, m_aggro, c_aggro, z_pos, &_z_pos, &z_bpos); // 좀비 이동
		z_pos = _z_pos;

		count_line(count); // ~번째
		train_box(train_length, c_pos, z_pos, m_pos); // 기차 상자
		printf("\n\n");

		c_moveresult(c_result, c_bpos, c_pos, c_baggro, c_aggro); // 시민 이동 출력

		z_moveresult(z_result, z_bpos, z_pos); // 좀비 이동 출력

	}

	return 0;
}

int trainlength_input(void) { // 열차 길이 입력
	int train_length;
	printf("기차의 길이를 입력해주세요. ( %d ~ %d )\n", LEN_MIN, LEN_MAX);
	scanf_s("%d", &train_length);
	while ((train_length < LEN_MIN) || (train_length > LEN_MAX)) {
		printf("기차의 길이를 입력해주세요. ( %d ~ %d )\n", LEN_MIN, LEN_MAX);
		scanf_s("%d", &train_length);
	}
	return train_length;
}

int percent_input(void) { // 움직임 확률 입력
	int p;
	printf("시민이 움직이지 못 할 확률을 입력해주세요. ( %d ~ %d )\n", PROB_MIN, PROB_MAX);
	scanf_s("%d", &p);
	while ((p < PROB_MIN) || (p > PROB_MAX)) {
		printf("시민이 움직이지 못 할 확률을 입력해주세요. ( %d ~ %d )\n", PROB_MIN, PROB_MAX);
		scanf_s("%d", &p);
	}
	return p;
}

int stm_inpput(void) { // 마동석 기초 체력 입력
	int stm;
	printf("마동석의 기초 체력 값을 입력해주세요. ( %d ~ %d )\n", STM_MIN, STM_MAX);
	scanf_s("%d", &stm);
	while ((stm < STM_MIN) || (stm > STM_MAX)) {
		printf("마동석의 기초 체력 값을 입력해주세요. ( %d ~ %d )\n", STM_MIN, STM_MAX);
		scanf_s("%d", &stm);
	}
	return stm;
}

void start_msg(void) {
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
}

void count_line(int count) {
	if (count <= 0) {
		printf("--------------- 초 기 상 태 ---------------\n");
	}
	else {
		printf("-------------- %d 번 째 결 과 --------------\n", count);
	}
}

void train_box(int train_length, int c_pos, int z_pos, int m_pos) {
	for (int i = 1; i <= 3; i++) {
		for (int i2 = 1; i2 <= train_length; i2++) {
			if ((i == 1) || (i == 3) || ((i == 2) & ((i2 == train_length)) || (i2 == 1))) {
				printf("#");
			}
			else if ((i == 2) & (i2 == c_pos)) {
				printf("C");
			}
			else if ((i == 2) & (i2 == z_pos)) {
				printf("Z");
			}
			else if ((i == 2) & (i2 == m_pos)) {
				printf("M");
			}
			else if (i == 2) {
				printf(" ");
			}
		}
		printf("\n");
	}
}

int c_move(int p, int c_aggro, int c_pos, int* _c_aggro, int* _c_pos, int* c_baggro, int* c_bpos) {
	int c_per = rand() % 100 + 1;
	if (c_per <= p) {
		*_c_pos = c_pos; // 위치
		*c_baggro = c_aggro; // 어그로
		c_aggro--;
		*_c_aggro = c_aggro;
		return 0; // 결과 출력
	}
	else if (c_per > p) {
		*c_bpos = c_pos; // 위치
		*_c_pos = c_pos - 1;
		*c_baggro = c_aggro; // 어그로
		c_aggro++;
		*_c_aggro = c_aggro;
		return 1; // 결과 출력
	}
}

int c_aggroMinMax(int _c_aggro) { // 시민 어그로 최솟값 최댓값 판단
	if (_c_aggro >= AGGRO_MAX) {
		return AGGRO_MAX; // 최 값
	}
	else if (_c_aggro <= AGGRO_MIN) {
		return AGGRO_MIN; // 최솟값
	}
	else {
		return _c_aggro; // 원래 값
	}
}

int z_move(int m_action_f, int count, int m_aggro, int c_aggro, int z_pos, int* _z_pos, int* z_bpos) {
	if (m_action_f == 3) {
		*_z_pos = z_pos; // 위치
		return 2; // 결과 출력
	}
	else if (count % 2 != 0) {
		int z_result, _z_pos_, _z_bpos;
		z_result = z_movewhere(m_aggro, c_aggro, z_pos, &_z_pos_, &_z_bpos); // 이동 방향
		*_z_pos = _z_pos_; // 위치
		*z_bpos = _z_bpos;
		return z_result; // 결과 출력
	}
	else {
		*_z_pos = z_pos;
		return 1;
	}
}

int z_movewhere(int m_aggro, int c_aggro, int z_pos, int* _z_pos_, int* _z_bpos) {
	if (m_aggro <= c_aggro) {
		*_z_bpos = z_pos; // 위치
		*_z_pos_ = z_pos - 1;
	}
	else {
		*_z_bpos = z_pos; // 위치
		*_z_pos_ = z_pos + 1;
	}
	return 0; // 결과 출력
}

void c_moveresult(int c_result, int c_bpos, int c_pos, int c_baggro, int c_aggro) {
	if (c_result == 0) {
		printf("시민 : 제자리 %d ( 어그로 : %d -> %d )\n", c_pos - 1, c_baggro, c_aggro);
	}
	else if (c_result == 1) {
		printf("시민 : %d -> %d ( 어그로 : %d -> %d )\n", c_bpos - 1, c_pos - 1, c_baggro, c_aggro);
	}
}

void z_moveresult(int z_result, int z_bpos, int z_pos) {
	if (z_result == 0) {
		printf("좀비 : %d -> %d\n\n", z_bpos - 1, z_pos - 1);
	}
	else if (z_result == 1) {
		printf("좀비 : 제자리 %d ( 움직일 수 없습니다. )\n\n", z_pos - 1);
	}
	else if (z_result == 2) {
		printf("좀비 : 제자리 %d ( 붙들기 )\n\n", z_pos - 1);
	}
}