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
void z_movewhere(int, int, int, int*, int*);
void c_moveresult(int, int, int, int, int);
void z_moveresult(int, int, int);
int m_move_inpput(int, int);
int m_movef(int, int, int, int*, int*, int*, int*);
int m_aggroMinMax(int);

int main(void) {
	system("title 20242397 류준서 부산헹 2"); // 콘솔창 이름 변경

	int train_length, p, stm, bstm = 0, count = 0;
	train_length = trainlength_input(); // 기차 길이 입력
	p = percent_input(); // 퍼센트 입력
	stm = stm_inpput(); // 체력 입력

	start_msg(); // 시작 메세지 출력

	srand((unsigned int)time(NULL)); // 난수 초기화

	int c_pos, z_pos, m_pos;
	c_pos = train_length - 5; // 시민 초기 위치
	z_pos = train_length - 2; // 좀비 초기 위치
	m_pos = train_length - 1; // 마동석 초기 위치

	count_line(count); // ~번째
	train_box(train_length, c_pos, z_pos, m_pos); // 기차 상자
	printf("\n\n");

	int c_bpos = 0, z_bpos = 0, m_bpos = 0; // 이동 전 좌표

	int c_aggro = 1, m_aggro = 1; // 어그로

	int m_move = 0, m_action = 0, m_action_f = 0; // 마동석 관련

	int c_result = 0, z_result = 0, m_result = 0; // 이동 결과

	while (1) { // 반복
		count += 1; // 턴 추가

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

		m_move = m_move_inpput(m_pos, z_pos); // 마동석 이동 선택

		int _m_aggro, _m_pos, m_baggro;
		m_movef(m_move, m_aggro, m_pos, &_m_aggro, &_m_pos, &m_baggro, &m_bpos); // 마동석 이동
		m_aggro = m_aggroMinMax(_m_aggro); // 마동석 어그로 최댓값, 최솟값 확인
		m_pos = _m_pos;

		train_box(train_length, c_pos, z_pos, m_pos); // 기차 상자
		printf("\n\n");
	}

	return 0;
}

int trainlength_input(void) { // 기차 길이 입력
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

void start_msg(void) { // 게임 시작
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

void count_line(int count) { // ~번째 턴
	if (count <= 0) {
		printf("--------------- 초 기 상 태 ---------------\n");
	}
	else {
		printf("-------------- %d 번 째 결 과 --------------\n", count);
	}
}

void train_box(int train_length, int c_pos, int z_pos, int m_pos) { // 기차 상자
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

int c_move(int p, int c_aggro, int c_pos, int* _c_aggro, int* _c_pos, int* c_baggro, int* c_bpos) { // 시민 이동
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

int z_move(int m_action_f, int count, int m_aggro, int c_aggro, int z_pos, int* _z_pos, int* z_bpos) { // 좀비 이동
	if (m_action_f == 3) {
		*_z_pos = z_pos; // 위치
		return 2; // 결과 출력
	}
	else if (count % 2 != 0) {
		int _z_pos_, _z_bpos;
		z_movewhere(m_aggro, c_aggro, z_pos, &_z_pos_, &_z_bpos); // 이동 방향 결정
		*_z_pos = _z_pos_; // 좀비 현재 위치 반환
		*z_bpos = _z_bpos; // 좀비 이동 전 위치 반환
		return 0; // 결과 출력
	}
	else {
		*_z_pos = z_pos; // 좀비 위치 반환
		return 1; // 결과 출력
	}
}

void z_movewhere(int m_aggro, int c_aggro, int z_pos, int* _z_pos_, int* _z_bpos) { // 좀비 이동 방향 결정
	if (m_aggro <= c_aggro) {
		*_z_bpos = z_pos; // 위치
		*_z_pos_ = z_pos - 1;
	}
	else {
		*_z_bpos = z_pos; // 위치
		*_z_pos_ = z_pos + 1;
	}
}

void c_moveresult(int c_result, int c_bpos, int c_pos, int c_baggro, int c_aggro) { // 시민 이동 결과 출력
	if (c_result == 0) {
		printf("시민 : 제자리 %d ( 어그로 : %d -> %d )\n", c_pos - 1, c_baggro, c_aggro);
	}
	else if (c_result == 1) {
		printf("시민 : %d -> %d ( 어그로 : %d -> %d )\n", c_bpos - 1, c_pos - 1, c_baggro, c_aggro);
	}
}

void z_moveresult(int z_result, int z_bpos, int z_pos) { // 좀비 이동 결과 출력
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

int m_move_inpput(int m_pos, int z_pos) { // 마동석 이동 선택
	int m_move;
	if (m_pos == z_pos + 1) {
		printf("마동석의 이동 여부를 선택해주세요. ( %d:stay )\n", MOVE_STAY);
		scanf_s("%d", &m_move);
		while ((m_move >= 1)) {
			printf("마동석의 이동 여부를 선택해주세요. ( %d:stay )\n", MOVE_STAY);
			scanf_s("%d", &m_move);
		}
	}
	else {
		printf("마동석의 이동 여부를 입력해주세요. ( %d:stay, %d:left )\n", MOVE_STAY, MOVE_LEFT);
		scanf_s("%d", &m_move);
		while ((m_move > 1) || (m_move < 0)) {
			printf("마동석의 이동 여부를 입력해주세요. ( %d:stay, %d:이동 )\n", MOVE_STAY, MOVE_LEFT);
			scanf_s("%d", &m_move);
		}
	}
	return m_move;
}

int m_movef(int m_move, int m_aggro, int m_pos, int* _m_aggro, int* _m_pos, int* m_baggro, int* m_bpos) {
	if (m_move == MOVE_STAY) {
		*_m_pos = m_pos; // 위치
		*m_baggro = m_aggro; // 어그로
		m_aggro--;
		*_m_aggro = m_aggro;
		return 0; // 결과 출력
	}
	else if (m_move == MOVE_LEFT) {
		*m_bpos = m_pos; // 위치
		*_m_pos = m_pos - 1;
		*m_baggro = m_aggro; // 어그로
		m_aggro++;
		*_m_aggro = m_aggro;
		return 1; // 결과 출력
	}
}

int m_aggroMinMax(int _m_aggro) { // 마동석 어그로 최솟값 최댓값 판단
	if (_m_aggro >= AGGRO_MAX) { // 최댓값
		return AGGRO_MAX;
	}
	else if (_m_aggro <= AGGRO_MIN) { // 최솟값
		return AGGRO_MIN;
	}
	else {
		return _m_aggro; // 원래 값
	}
}