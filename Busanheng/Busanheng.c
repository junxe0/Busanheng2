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

int main(void) {
	// ��Ʈ��
	system("title 20242397 ���ؼ� �λ���");

	int train_length, p, stm, bstm = 0, count = 0;
	train_length = trainlength_input(); // ���� ���� �Է�
	p = percent_input(); // �ۼ�Ʈ �Է�
	stm = stm_inpput(); // ü�� �Է�

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

	// ��ġ ����
	int c_pos, z_pos, m_pos;
	c_pos = train_length - 5; // �ù� ��ġ
	z_pos = train_length - 2; // ���� ��ġ
	m_pos = train_length - 1; // ������ ��ġ

	// ���� �ʱ� ���� ���
	printf("--------------- �� �� �� �� ---------------\n");
	//���� ���� �ڽ�
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
	// 4�� ���
	Sleep(4000);

	//�ù� �̵� ����
	int c_bpos;
	c_bpos = 0;

	// ���� �̵� ����
	int z_bpos;
	z_bpos = 0;

	// 4�ʸ��� �̵�
	while (1) {
		// �̵� ���� ���� ����
		int c_result, z_result;
		c_result = 0, z_result = 0;

		// �̵� ��� ���
		count += 1;
		printf("-------------- %d �� ° �� �� --------------\n", count);

		// �̵� Ȯ��
		int c_per, z_per;
		c_per = rand() % 100 + 1;
		z_per = rand() % 100 + 1;


		// �ù� �̵�
		if (c_per <= p) {
			c_result = 0;
		}
		else if (c_per > p) {
			c_pos = c_pos - 1;
			c_bpos = c_pos + 1;
			c_result = 1;
		}

		// ���� �̵�
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

		//���� ���� �ڽ�
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

		// �ù� �̵� ���� ����
		if (c_result == 0) {
			printf("�ù� : ���ڸ� %d\n", c_pos - 1);
		}
		else if (c_result == 1) {
			printf("�ù� : %d -> %d\n", c_bpos - 1, c_pos - 1);
		}

		// ���� �̵� ���� ����
		if (z_result == 0) {
			printf("���� : ���ڸ� %d\n\n", z_pos - 1);
		}
		else if (z_result == 1) {
			printf("���� : %d -> %d\n\n", z_bpos - 1, z_pos - 1);
		}
		else if (z_result == 2) {
			printf("���� : ���ڸ� %d ( ������ �� �����ϴ�. )\n\n", z_pos - 1);
		}

		// ���� ���� ���� ���
		if (c_pos == 2) {
			printf("�ù��� ��Ű�µ� �����Ͽ����ϴ�.\n");
			system("color 9f");
			break;
		}
		else if (z_pos == c_pos + 1) {
			printf("�ù��� ��Ű�µ� �����Ͽ����ϴ�.\n");
			system("color 4f");
			break;
		}
		// 4�� ���
		Sleep(4000);
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