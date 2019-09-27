#ifndef STRATEGY
#define STRATEGY

#include "Field.h"
#include "Model.h"
#include "Errors.h"
#include "History.h"
#include <memory>


class Strategy 
{

public:

	Strategy(Field& fieldIn, History& historyIn) : field(fieldIn), history(historyIn) {}

	//���������� ����� ������ � ������� (x,y)
	void set(int x, int y);

	//����� ������ � ������� (x,y)
	void clear(int x, int y);

	//���������� ���� �� STEP ����� ������
	void step(int step);

	//������� ��� ���� �� 1 ����� (backStep = 1)
	void back(int backStep);

	//����� ����
	void reset();

	//��������� ������ �������� ����
	void getIterNumber();

	void clearGameData();

private:
	
	Field field;

	History history;

	//������� ��������/�������� ������
	void conditions();
	
	//��������� ������ x �� ������ SIZE
	int modulus(int x, int SIZE);

	//���������� ������� � ������ ����
	void updateNeigh(int x, int y);

	//������ � ������� ����
	void writeToHistory(int iteration, int x, int y, bool state);

	//��������� ����� ���� ��� ���
	bool chekIsGameOver();

};

#endif // !STRATEGY