#pragma once
#include<iostream>
//1墙0路3入口4出口
using namespace std;
class Board {//迷宫
	int Row, Col;
	int** b;
public:
	Board(int Row, int Col);
	~Board();
	void Show();
};
class Data {
	int Row, Col;
	int Step;
public:
	Data(int Row, int Col, int Step) :Row(Row), Col(Col), Step(Step) {}
	Data() {};
};
class queue {//循环队列
	int head, tail;
	bool flag;
	int size;
	Data* q;
public:
	queue(int size);
	~queue();
	void input(Data x);
	Data output();
	bool IsFull() {
		return (head + 1) / size - (tail + 1) / size == 1 && flag;//入队后将flag设定为true
	}
	bool IsNull() {
		return (head + 1) / size - (tail + 1) / size == 1 && !flag;//出队后将flag设定为false
	}
};
Data queue::output() {
	if (IsNull()) {
		return Data(-1, -1, -1);
	}
	else if (head == size - 1) {
		head = 0; flag = false;
		return q[size - 1];
	}
	else {
		head++; flag = false;
		return q[head - 1];
	}
}
void queue::input(Data x) {
	if (IsFull()) {
		return;
	}
	else if (tail == size - 1) {
		q[0] = x;
		tail = 0;
		flag = true;
	}
	else {
		q[++tail] = x;
		flag = true;
	}
}
queue::queue(int size) :size(size) {
	q = new Data[size];
	head = 0; tail = size - 1;
	flag = false;
};
queue::~queue() {
	delete[] q;
}
void Board::Show() {
	for (int i = 0; i < Row; i++) {
		for (int j = 0; j < Col; j++) {
			cout << b[i][j] << " ";
		}
		cout << endl;
	}
}
Board::~Board() {
	for (int i = 0; i < Row; i++) {
		delete[] b[i];
	}
	delete[] b;
}
Board::Board(int Row, int Col) {
	this->Row = Row; this->Col = Col;
	b = new int* [Row];
	for (int i = 0; i < Row; i++) {
		int* p = new int[Col];
		b[i] = p;
	}
	for (int i = 0; i < Col; i++) {
		b[0][i] = 1;
		b[Row - 1][i] = 1;
	}
	for (int i = 0; i < Row; i++) {
		b[i][0] = 1;
		b[i][Col - 1] = 1;
	}
	for (int i = 1; i < Row - 1; i++) {
		for (int j = 1; j < Col - 1; j++) {
			cin >> b[i][j];
		}
	}
	b[1][1] = 4;
	b[Row - 2][Col - 2] = 3;
}
