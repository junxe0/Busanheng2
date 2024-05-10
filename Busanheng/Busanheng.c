#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ��������
#define LEN_MIN			15
#define LEN_MAX			50
// Ȯ��
#define PROB_MIN		10
#define PROB_MAX		90
// ��׷� ����
#define AGGRO_MIN		0
#define AGGRO_MAX		5
// ������ ���� ���
#define ATK_NONE		0
#define ATK_CITIZEN		1
#define ATK_DONGSEOK	2
// ������ �̵� ����
#define MOVE_LEFT		1
#define MOVE_STAY		0
// ������ ü��
#define STM_MIN			0
#define STM_MAX			5
// ������ �ൿ
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
	system("title 20242397 ���ؼ� �λ��� 2"); // �ܼ�â �̸� ����

	int train_length, p, stm, bstm = 0, count = 0;
	train_length = trainlength_input(); // ���� ���� �Է�
	p = percent_input(); // �ۼ�Ʈ �Է�
	stm = stm_inpput(); // ü�� �Է�

	start_msg(); // ���� �޼��� ���

	srand((unsigned int)time(NULL)); // ���� �ʱ�ȭ

	int c_pos, z_pos, m_pos;
	c_pos = train_length - 5; // �ù� �ʱ� ��ġ
	z_pos = train_length - 2; // ���� �ʱ� ��ġ
	m_pos = train_length - 1; // ������ �ʱ� ��ġ

	count_line(count); // ~��°
	train_box(train_length, c_pos, z_pos, m_pos); // ���� ����
	printf("\n\n");

	int c_bpos = 0, z_bpos = 0, m_bpos = 0; // �̵� �� ��ǥ

	int c_aggro = 1, m_aggro = 1; // ��׷�

	int m_move = 0, m_action = 0, m_action_f = 0; // ������ ����

	int c_result = 0, z_result = 0, m_result = 0; // �̵� ���

	while (1) { // �ݺ�
		count += 1; // �� �߰�

		int _c_aggro, _c_pos, c_baggro, c_bpos;
		c_result = c_move(p, c_aggro, c_pos, &_c_aggro, &_c_pos, &c_baggro, &c_bpos); // �ù� �̵�
		c_pos = _c_pos;
		c_aggro = c_aggroMinMax(_c_aggro); // �ù� ��׷� �ִ�, �ּڰ� Ȯ��

		int _z_pos, z_bpos;
		z_result = z_move(m_action_f, count, m_aggro, c_aggro, z_pos, &_z_pos, &z_bpos); // ���� �̵�
		z_pos = _z_pos;

		count_line(count); // ~��°
		train_box(train_length, c_pos, z_pos, m_pos); // ���� ����
		printf("\n\n");

		c_moveresult(c_result, c_bpos, c_pos, c_baggro, c_aggro); // �ù� �̵� ���
		z_moveresult(z_result, z_bpos, z_pos); // ���� �̵� ���

		m_move = m_move_inpput(m_pos, z_pos); // ������ �̵� ����

		int _m_aggro, _m_pos, m_baggro;
		m_movef(m_move, m_aggro, m_pos, &_m_aggro, &_m_pos, &m_baggro, &m_bpos); // ������ �̵�
		m_aggro = m_aggroMinMax(_m_aggro); // ������ ��׷� �ִ�, �ּڰ� Ȯ��
		m_pos = _m_pos;

		train_box(train_length, c_pos, z_pos, m_pos); // ���� ����
		printf("\n\n");
	}

	return 0;
}

int trainlength_input(void) { // ���� ���� �Է�
	int train_length;
	printf("������ ���̸� �Է����ּ���. ( %d ~ %d )\n", LEN_MIN, LEN_MAX);
	scanf_s("%d", &train_length);
	while ((train_length < LEN_MIN) || (train_length > LEN_MAX)) {
		printf("������ ���̸� �Է����ּ���. ( %d ~ %d )\n", LEN_MIN, LEN_MAX);
		scanf_s("%d", &train_length);
	}
	return train_length;
}

int percent_input(void) { // ������ Ȯ�� �Է�
	int p;
	printf("�ù��� �������� �� �� Ȯ���� �Է����ּ���. ( %d ~ %d )\n", PROB_MIN, PROB_MAX);
	scanf_s("%d", &p);
	while ((p < PROB_MIN) || (p > PROB_MAX)) {
		printf("�ù��� �������� �� �� Ȯ���� �Է����ּ���. ( %d ~ %d )\n", PROB_MIN, PROB_MAX);
		scanf_s("%d", &p);
	}
	return p;
}

int stm_inpput(void) { // ������ ���� ü�� �Է�
	int stm;
	printf("�������� ���� ü�� ���� �Է����ּ���. ( %d ~ %d )\n", STM_MIN, STM_MAX);
	scanf_s("%d", &stm);
	while ((stm < STM_MIN) || (stm > STM_MAX)) {
		printf("�������� ���� ü�� ���� �Է����ּ���. ( %d ~ %d )\n", STM_MIN, STM_MAX);
		scanf_s("%d", &stm);
	}
	return stm;
}

void start_msg(void) { // ���� ����
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

void count_line(int count) { // ~��° ��
	if (count <= 0) {
		printf("--------------- �� �� �� �� ---------------\n");
	}
	else {
		printf("-------------- %d �� ° �� �� --------------\n", count);
	}
}

void train_box(int train_length, int c_pos, int z_pos, int m_pos) { // ���� ����
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

int c_move(int p, int c_aggro, int c_pos, int* _c_aggro, int* _c_pos, int* c_baggro, int* c_bpos) { // �ù� �̵�
	int c_per = rand() % 100 + 1;
	if (c_per <= p) {
		*_c_pos = c_pos; // ��ġ
		*c_baggro = c_aggro; // ��׷�
		c_aggro--;
		*_c_aggro = c_aggro;
		return 0; // ��� ���
	}
	else if (c_per > p) {
		*c_bpos = c_pos; // ��ġ
		*_c_pos = c_pos - 1;
		*c_baggro = c_aggro; // ��׷�
		c_aggro++;
		*_c_aggro = c_aggro;
		return 1; // ��� ���
	}
}

int c_aggroMinMax(int _c_aggro) { // �ù� ��׷� �ּڰ� �ִ� �Ǵ�
	if (_c_aggro >= AGGRO_MAX) {
		return AGGRO_MAX; // �� ��
	}
	else if (_c_aggro <= AGGRO_MIN) {
		return AGGRO_MIN; // �ּڰ�
	}
	else {
		return _c_aggro; // ���� ��
	}
}

int z_move(int m_action_f, int count, int m_aggro, int c_aggro, int z_pos, int* _z_pos, int* z_bpos) { // ���� �̵�
	if (m_action_f == 3) {
		*_z_pos = z_pos; // ��ġ
		return 2; // ��� ���
	}
	else if (count % 2 != 0) {
		int _z_pos_, _z_bpos;
		z_movewhere(m_aggro, c_aggro, z_pos, &_z_pos_, &_z_bpos); // �̵� ���� ����
		*_z_pos = _z_pos_; // ���� ���� ��ġ ��ȯ
		*z_bpos = _z_bpos; // ���� �̵� �� ��ġ ��ȯ
		return 0; // ��� ���
	}
	else {
		*_z_pos = z_pos; // ���� ��ġ ��ȯ
		return 1; // ��� ���
	}
}

void z_movewhere(int m_aggro, int c_aggro, int z_pos, int* _z_pos_, int* _z_bpos) { // ���� �̵� ���� ����
	if (m_aggro <= c_aggro) {
		*_z_bpos = z_pos; // ��ġ
		*_z_pos_ = z_pos - 1;
	}
	else {
		*_z_bpos = z_pos; // ��ġ
		*_z_pos_ = z_pos + 1;
	}
}

void c_moveresult(int c_result, int c_bpos, int c_pos, int c_baggro, int c_aggro) { // �ù� �̵� ��� ���
	if (c_result == 0) {
		printf("�ù� : ���ڸ� %d ( ��׷� : %d -> %d )\n", c_pos - 1, c_baggro, c_aggro);
	}
	else if (c_result == 1) {
		printf("�ù� : %d -> %d ( ��׷� : %d -> %d )\n", c_bpos - 1, c_pos - 1, c_baggro, c_aggro);
	}
}

void z_moveresult(int z_result, int z_bpos, int z_pos) { // ���� �̵� ��� ���
	if (z_result == 0) {
		printf("���� : %d -> %d\n\n", z_bpos - 1, z_pos - 1);
	}
	else if (z_result == 1) {
		printf("���� : ���ڸ� %d ( ������ �� �����ϴ�. )\n\n", z_pos - 1);
	}
	else if (z_result == 2) {
		printf("���� : ���ڸ� %d ( �ٵ�� )\n\n", z_pos - 1);
	}
}

int m_move_inpput(int m_pos, int z_pos) { // ������ �̵� ����
	int m_move;
	if (m_pos == z_pos + 1) {
		printf("�������� �̵� ���θ� �������ּ���. ( %d:stay )\n", MOVE_STAY);
		scanf_s("%d", &m_move);
		while ((m_move >= 1)) {
			printf("�������� �̵� ���θ� �������ּ���. ( %d:stay )\n", MOVE_STAY);
			scanf_s("%d", &m_move);
		}
	}
	else {
		printf("�������� �̵� ���θ� �Է����ּ���. ( %d:stay, %d:left )\n", MOVE_STAY, MOVE_LEFT);
		scanf_s("%d", &m_move);
		while ((m_move > 1) || (m_move < 0)) {
			printf("�������� �̵� ���θ� �Է����ּ���. ( %d:stay, %d:�̵� )\n", MOVE_STAY, MOVE_LEFT);
			scanf_s("%d", &m_move);
		}
	}
	return m_move;
}

int m_movef(int m_move, int m_aggro, int m_pos, int* _m_aggro, int* _m_pos, int* m_baggro, int* m_bpos) {
	if (m_move == MOVE_STAY) {
		*_m_pos = m_pos; // ��ġ
		*m_baggro = m_aggro; // ��׷�
		m_aggro--;
		*_m_aggro = m_aggro;
		return 0; // ��� ���
	}
	else if (m_move == MOVE_LEFT) {
		*m_bpos = m_pos; // ��ġ
		*_m_pos = m_pos - 1;
		*m_baggro = m_aggro; // ��׷�
		m_aggro++;
		*_m_aggro = m_aggro;
		return 1; // ��� ���
	}
}

int m_aggroMinMax(int _m_aggro) { // ������ ��׷� �ּڰ� �ִ� �Ǵ�
	if (_m_aggro >= AGGRO_MAX) { // �ִ�
		return AGGRO_MAX;
	}
	else if (_m_aggro <= AGGRO_MIN) { // �ּڰ�
		return AGGRO_MIN;
	}
	else {
		return _m_aggro; // ���� ��
	}
}