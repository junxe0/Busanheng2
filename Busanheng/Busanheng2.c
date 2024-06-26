#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 도중 파일 이름을 Busanheng에서 Busanheng2로 변경하여
// 파일 커밋에는 커밋이 몇개 없습니다.

// 기차길이
#define LEN_MIN				15
#define LEN_MAX				50
// 확률
#define PROB_MIN			10
#define PROB_MAX			90
// 어그로 범위
#define AGGRO_MIN			0
#define AGGRO_MAX			5
// 좀비의 공격 대상
#define ATK_NONE			0
#define ATK_CITIZEN			1
#define ATK_DONGSEOK		2
// 마동석 이동 방향
#define MOVE_LEFT			1
#define MOVE_STAY			0
// 마동석 체력
#define STM_MIN				0
#define STM_MAX				5
// 마동석 행동
#define ACTION_REST			0
#define ACTION_PROVOKE		1
#define ACTION_PULL			2

void intro(void);
int trainlength_input(void);
int percent_input(void);
int stm_inpput(void);
void start_msg(void);
void count_line(int);
void train_box(int, int, int, int);
int c_move(int, int, int, int*, int*, int*, int*);
int c_aggroMinMax(int);
int z_move(int, int, int, int, int, int, int, int*, int*, int*);
int z_movewhere(int, int, int, int, int, int*);
void c_moveresult(int, int, int, int, int);
void z_moveresult(int, int, int);
int m_move_inpput(int, int);
int m_movef(int, int, int, int*, int*, int*, int*);
int m_aggroMinMax(int);
void m_moveresult(int, int, int, int, int);
void c_action(int);
int z_who_atk(int, int, int, int*, int*);
int z_who_atk2(int, int, int, int, int*, int*);
int z_action(int, int, int, int, int, int, int*, int*, int*);
void ATK_f(int, int, int, int, int, int);
int m_action_inpput(int, int);
int m_actionf(int, int, int, int, int, int, int*, int*, int*);
int m_pull(int, int, int, int*);
int m_stmMinMax(int);
int m_actionmsg(int, int, int, int, int, int);

int main(void) {
	intro(); // 콘솔창 이름 변경

	int train_length, p, stm, bstm = 0, count = 0, zombie = 0;
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

	int c_bpos = 0, z_bpos = 0, m_bpos = 0; // 이동 전 좌표

	int c_aggro = 1, m_aggro = 1; // 어그로

	int m_move = 0, m_action = 0, m_action_f = 0; // 마동석 관련

	int c_result = 0, z_result = 0, ATK = 0; // 이동 결과

	while (1) { // 반복
		count++; // 턴 추가
		zombie++; // 붙잡기

		int _c_aggro, _c_pos, c_baggro, c_bpos;
		c_result = c_move(p, c_aggro, c_pos, &_c_aggro, &_c_pos, &c_baggro, &c_bpos); // 시민 이동
		c_pos = _c_pos;
		c_aggro = c_aggroMinMax(_c_aggro); // 시민 어그로 최댓값, 최솟값 확인

		int _zombie, _z_pos, z_bpos;
		z_result = z_move(count, zombie, m_aggro, c_aggro, c_pos, z_pos, m_pos, &_zombie, &_z_pos, &z_bpos); // 좀비 이동
		zombie = _zombie;
		z_pos = _z_pos;

		count_line(count); // ~번째
		train_box(train_length, c_pos, z_pos, m_pos); // 기차 상자

		c_moveresult(c_result, c_bpos, c_pos, c_baggro, c_aggro); // 시민 이동 출력
		z_moveresult(z_result, z_bpos, z_pos); // 좀비 이동 출력

		m_move = m_move_inpput(m_pos, z_pos); // 마동석 이동 선택

		int _m_aggro, _m_pos, m_baggro;
		m_movef(m_move, m_aggro, m_pos, &_m_aggro, &_m_pos, &m_baggro, &m_bpos); // 마동석 이동
		m_aggro = m_aggroMinMax(_m_aggro); // 마동석 어그로 최댓값, 최솟값 확인
		m_pos = _m_pos;

		train_box(train_length, c_pos, z_pos, m_pos); // 기차 상자

		m_moveresult(m_move, m_bpos, m_pos, m_baggro, m_aggro); // 마동석 이동 출력

		c_action(c_pos); // 시민 행동 출력
		int z_action_r, _stm;
		z_action_r = z_action(z_pos, c_pos, m_pos, m_aggro, c_aggro, stm, &bstm, &_stm, &ATK); // 좀비 행동 출력
		stm = _stm;

		ATK_f(z_action_r, m_aggro, c_aggro, bstm, stm, ATK); // 공격 확인

		m_baggro = m_aggro; /* 어그로 */
		bstm = stm; /* 체력 */
		m_action = m_action_inpput(m_pos, z_pos); // 마동석 행동 선택
		m_action_f = m_actionf(count, zombie, m_action, m_aggro, p, stm, &_zombie, &_m_aggro, &_stm); // 마동석 행동
		zombie = _zombie;
		m_aggro = m_aggroMinMax(_m_aggro); // 마동석 어그로 최댓값, 최솟값 확인
		stm = m_stmMinMax(_stm); // 마동석 체력 최댓값, 최솟값 확인
		m_actionmsg(m_action_f, m_pos, m_baggro, m_aggro, bstm, stm); // 마동석 행동 출력
	}
	return 0;
}

void intro() { // 콘솔 창 이름 변경
	system("title 20242397 류준서 부산헹 2");
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
	printf("\n\n");
}

int c_move(int p, int c_aggro, int c_pos, int* _c_aggro, int* _c_pos, int* c_baggro, int* c_bpos) { // 시민 이동
	int c_per = rand() % 100 + 1;
	*c_baggro = c_aggro; // 어그로
	if (c_per <= p) {
		*_c_pos = c_pos; // 위치
		*_c_aggro = --c_aggro; // 어그로
		return 0; // 결과 출력
	}
	else if (c_per > p) {
		*c_bpos = c_pos; // 위치
		*_c_pos = c_pos - 1;
		*_c_aggro = ++c_aggro;
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

int z_move(int count, int zombie, int m_aggro, int c_aggro, int c_pos, int z_pos, int m_pos, int* _zombie, int* _z_pos, int* z_bpos) { // 좀비 이동
	int _z_pos_, result;
	*z_bpos = z_pos; // 좀비 이동 전 위치 반환
	*_zombie = zombie;
	if (count % 2 != 0) {
		if (count < zombie) {
			*_zombie = --zombie;
			*_z_pos = z_pos; // 위치
			result = 2; // 결과 출력
		}
		else {
			result = z_movewhere(m_aggro, c_aggro, c_pos, z_pos, m_pos, &_z_pos_); // 좀비 이동 방향
			*_z_pos = _z_pos_; // 좀비 현재 위치 반환
		}
	}
	else {
		*_z_pos = z_pos; // 좀비 위치 반환
		result = 1; // 결과 출력
	}
	return result;
}

int z_movewhere(int m_aggro, int c_aggro, int c_pos, int z_pos, int m_pos, int* _z_pos_) { // 좀비 이동 방향
	*_z_pos_ = z_pos;
	if (m_aggro <= c_aggro) {
		if (c_pos == z_pos - 1) {
			return 3;
		}
		else {
			*_z_pos_ = z_pos - 1;
			return 0;
		}
	}
	else {
		if (m_pos == z_pos + 1) {
			return 3;
		}
		else {
			*_z_pos_ = z_pos + 1;
			return 0;
		}
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
	else if (z_result == 3) {
		printf("좀비 : 제자리 %d\n\n", z_pos - 1);
	}
}

int m_move_inpput(int m_pos, int z_pos) { // 마동석 이동 선택
	int m_move;
	if (m_pos == z_pos + 1) {
		printf("마동석의 이동 여부를 선택해주세요. ( %d:stay )\n", MOVE_STAY);
		scanf_s("%d", &m_move);
		while ((m_move != MOVE_STAY)) {
			printf("마동석의 이동 여부를 선택해주세요. ( %d:stay )\n", MOVE_STAY);
			scanf_s("%d", &m_move);
		}
	}
	else {
		printf("마동석의 이동 여부를 입력해주세요. ( %d:stay, %d:left )\n", MOVE_STAY, MOVE_LEFT);
		scanf_s("%d", &m_move);
		while ((m_move != MOVE_STAY) && (m_move != MOVE_LEFT)) {
			printf("마동석의 이동 여부를 입력해주세요. ( %d:stay, %d:이동 )\n", MOVE_STAY, MOVE_LEFT);
			scanf_s("%d", &m_move);
		}
	}
	return m_move;
}

int m_movef(int m_move, int m_aggro, int m_pos, int* _m_aggro, int* _m_pos, int* m_baggro, int* m_bpos) {
	*m_baggro = m_aggro; // 어그로
	if (m_move == MOVE_STAY) {
		*_m_pos = m_pos; // 위치
		*_m_aggro = --m_aggro;
		return 0; // 결과 출력
	}
	else if (m_move == MOVE_LEFT) {
		*m_bpos = m_pos; // 위치
		*_m_pos = m_pos - 1;
		*_m_aggro = ++m_aggro;
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

void m_moveresult(int m_result, int m_bpos, int m_pos, int m_baggro, int m_aggro) { // 마동석 이동 출력
	if (m_result == MOVE_STAY) {
		printf("마동석 : 제자리 %d ( 어그로 : %d -> %d )\n\n", m_pos - 1, m_baggro, m_aggro);
	}
	else if (m_result == MOVE_LEFT) {
		printf("마동석 : %d -> %d ( 어그로 : %d -> %d )\n\n", m_bpos - 1, m_pos - 1, m_baggro, m_aggro);
	}
}

void c_action(int c_pos) { // 시민 행동 출력
	if (c_pos == 2) {
		printf("You Win!!!\n시민이 탈출에 성공하였습니다.\n");
		exit(0);
	}
	else {
		printf("시민은 아무것도 하지 않았습니다.\n");
	}
}

int z_action(int z_pos, int c_pos, int m_pos, int m_aggro, int c_aggro, int stm, int* bstm, int* _stm, int* ATK) { // 좀비 행동 출력
	*bstm = stm; // 변경 전 체력
	*_stm = stm; // 체력 변경이 없다면 체력 다시 반환
	if ((c_pos == (z_pos - 1)) && (m_pos == (z_pos + 1))) {
		int result, _stm_, _ATK;
		result = z_who_atk(m_aggro, c_aggro, stm, &_stm_, &_ATK);
		*_stm = _stm_; // 체력 변경
		*ATK = _ATK; // 둘다 인접 여부
		return result;
	}
	else if ((c_pos == (z_pos - 1)) || (m_pos == (z_pos + 1))) {
		int result, _stm_, _ATK;
		result = z_who_atk2(c_pos, z_pos, m_pos, stm, &_stm_, &_ATK);
		*_stm = _stm_; // 체력 변경
		*ATK = _ATK; // 둘다 인접 여부
		return result;
	}
	else {
		return ATK_NONE;
	}
}

int z_who_atk(int m_aggro, int c_aggro, int stm, int* _stm_, int* _ATK) {
	if (m_aggro >= c_aggro) {
		*_stm_ = --stm;
		*_ATK = 1;
		return ATK_DONGSEOK;
	}
	else {
		return ATK_CITIZEN;
	}
}

int z_who_atk2(int c_pos, int z_pos, int m_pos, int stm, int* _stm_, int* _ATK) {
	if (m_pos == (z_pos + 1)) {
		*_stm_ = --stm;
		*_ATK = 0;
		return ATK_DONGSEOK;
	}
	else if (c_pos == (z_pos - 1)) {
		return ATK_CITIZEN;
	}
}

void ATK_f(int z_action_r, int m_aggro, int c_aggro, int bstm, int stm, int ATK) { // 마동석 사망 확인
	if (z_action_r == ATK_DONGSEOK) {
		if (ATK == 1) {
			printf("좀비가 마동석을 공격하였습니다. ( %d(C) vs. %d(M), 마동석 체력 : %d -> %d )\n", c_aggro, m_aggro, bstm, stm);
		}
		else {
			printf("좀비가 마동석을 공격하였습니다. ( 마동석 체력 : %d -> %d )\n", bstm, stm);
		}
		if (stm <= 0) {
			printf("GAME OVER...\n마동석이 사망하였습니다...");
			exit(0);
		}
	}
	else if (z_action_r == ATK_CITIZEN) {
		printf("GAME OVER...\n시민을 지키는데 실패하였습니다...\n");
		exit(0);
	}
	else if (z_action_r == ATK_NONE) {
		printf("좀비는 아무도 공격하지 못했습니다.\n");
	}
}

int m_action_inpput(int m_pos, int z_pos) { // 마동석 행동 선택
	int m_action;
	if (m_pos == z_pos + 1) {
		printf("마동석의 행동을 선택해주세요. ( 0:휴식, 1:도발, 2:붙들기 )\n");
		printf("붙들기는 누적이 되지 않습니다.\n");
		scanf_s("%d", &m_action);
		while ((m_action != ACTION_REST) && (m_action != ACTION_PROVOKE) && (m_action != ACTION_PULL)) {
			printf("마동석의 행동을 선택해주세요. ( 0:stay, 1:도발, 2:붙들기 )\n");
			printf("붙들기는 누적이 되지 않습니다.\n");
			scanf_s("%d", &m_action);
		}
	}
	else {
		printf("마동석의 행동을 선택해주세요. ( 0:휴식, 1:도발 )\n");
		scanf_s("%d", &m_action);
		while ((m_action != ACTION_REST) && (m_action != ACTION_PROVOKE)) {
			printf("마동석의 행동을 선택해주세요. ( 0:휴식, 1:도발 )\n");
			scanf_s("%d", &m_action);
		}
	}
	printf("\n");
	return m_action;
}

int m_actionf(int count, int zombie, int m_action, int m_aggro, int p, int stm, int* _zombie, int* _m_aggro, int* _stm) { // 마동석 행동
	int result = 0, _zombie_;
	*_zombie = zombie;
	if (m_action == ACTION_REST) {
		m_aggro--; /* 어그로 */
		stm++; /* 체력 */
		result = 0; /* 결과 출력 */
	}
	else if (m_action == ACTION_PROVOKE) {
		m_aggro = AGGRO_MAX; /* 어그로 */
		result = 1; /* 결과 출력 */
	}
	else if (m_action == ACTION_PULL) {
		m_aggro += 2; /* 어그로 */
		stm--; /* 체력 */
		result = m_pull(p, count, zombie, &_zombie_);
		*_zombie = _zombie_;
	}
	*_m_aggro = m_aggro; /* 어그로 */
	*_stm = stm; /* 체력 */
	return result;
}

int m_pull(int count, int zombie, int p, int* _zombie_) {
	int m_per = rand() % 100 + 1;
	if (m_per <= p) { // 붙들기 실패
		*_zombie_ = zombie; /* 붙들기 반환 */
		return 2; // 결과 출력
	}
	else if (m_per > p) { // 붙들기 성공
		*_zombie_ = ++zombie; /* 붙들기 반환 */
		if ((zombie - count) >= 2) { // 2 이상 차이가 날 경우
			*_zombie_ = count + 1; /* 붙들기 반환 */
		}
		return 3; // 결과 출력
	}
}

int m_stmMinMax(int _stm) { // 마동석 체력 최솟값 최댓값 판단
	if (_stm >= STM_MAX) {
		return STM_MAX; // 최댓값
	}
	else if (_stm <= STM_MIN) {
		return STM_MIN; // 최솟값
	}
	else {
		return _stm; // 원래 값
	}
}

int m_actionmsg(int m_action_f, int m_pos, int m_baggro, int m_aggro, int bstm, int stm) { // 마동석 행동 출력
	if (m_action_f == 0) {
		printf("마동석이 휴식을 취했습니다.\n");
		printf("마동석 : %d ( 어그로 : %d -> %d, 체력 : %d -> %d )\n", m_pos - 1, m_baggro, m_aggro, bstm, stm);
	}
	else if (m_action_f == 1) {
		printf("마동석이 좀비를 도발했습니다...\n");
		printf("마동석 : %d ( 어그로 : %d -> %d, 체력 : %d )\n", m_pos - 1, m_baggro, m_aggro, stm);
	}
	else if (m_action_f == 2) {
		printf("마동석이 좀비 붙들기에 실패했습니다...\n");
		printf("마동석 : %d ( 어그로 : %d -> %d, 체력 : %d -> %d )\n", m_pos - 1, m_baggro, m_aggro, bstm, stm);
	}
	else if (m_action_f == 3) {
		printf("마동석이 좀비 붙들기에 성공했습니다. 좀비는 다음턴에 움직일 수 없습니다.\n");
		printf("마동석 : %d ( 어그로 : %d -> %d, 체력 : %d -> %d )\n", m_pos - 1, m_baggro, m_aggro, bstm, stm);
	}
}