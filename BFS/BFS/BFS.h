#pragma once
#include<iostream>
//1墙0路3入口4出口
using namespace std;

class Data {
public:
	int Row, Col;
	int Step;
	Data(int Row, int Col, int Step) :Row(Row), Col(Col), Step(Step) {}
	Data() {};
};

class queue {//循环队列
	friend class Data;
	int head, tail;
	bool flag;
	int size;
	int count;
	Data* q;
public:

	void Resize() {
		Data* p = new Data[size * 2];
		if (head <= tail) {
			int j = 0;
			for (int i = head; i <= tail; i++) {
				p[j++] = q[i];

			}
			head = 0; tail = head + count;
		}
		else {
			int j = 0;
			for (int i = head; i < size; i++) {
				p[j++] = q[i];
			}
			for (int i = 0; i < head; i++) {
				p[j++] = q[i];
			}

			head = 0; tail = head + count;
		}

		delete[] q;
		q = p;
		size = size * 2;

	}
	queue(int size);
	~queue();
	void input(Data x);
	Data output();
	bool IsFull() {
		return count == size - 1;//入队后将flag设定为true
	}
	bool IsNull() {
		return count == 0; //出队后将flag设定为false
	}
	int rRow() {
		return q[head].Row;
	}
	int rCol() {
		return q[head].Col;
	}

};

class Board {//迷宫
	friend class queue;
	friend class Data;
	int Row, Col;
	int** b;
	int*** Record;
	int begin[2]; int end[2];
public:
	Board(int Row, int Col);
	~Board();
	void Show();
	void Search(queue& q);
	bool IsOver(queue& q);
	void CheckAndInput(Data& tmp, queue& q);

	void Clear(int r, int c);
};

bool Board::IsOver(queue& q) {
	return b[q.rRow()][q.rCol()] != 4;
}

void Board::CheckAndInput(Data& tmp, queue& q) {//左上顺时针
	if (b[tmp.Row - 1][tmp.Col - 1] == 0 || b[tmp.Row - 1][tmp.Col - 1] == 4) {
		Data x(tmp.Row - 1, tmp.Col - 1, tmp.Step + 1);
		if (b[tmp.Row - 1][tmp.Col - 1] == 0)
			b[tmp.Row - 1][tmp.Col - 1] = 1;
		Record[tmp.Row - 1][tmp.Col - 1][0] = tmp.Row;
		Record[tmp.Row - 1][tmp.Col - 1][1] = tmp.Col;
		q.input(x);
	}
	if (b[tmp.Row - 1][tmp.Col] == 0 || b[tmp.Row - 1][tmp.Col] == 4) {
		Data x(tmp.Row - 1, tmp.Col, tmp.Step + 1);
		if (b[tmp.Row - 1][tmp.Col] == 0)
			b[tmp.Row - 1][tmp.Col] = 1;
		Record[tmp.Row - 1][tmp.Col][0] = tmp.Row;
		Record[tmp.Row - 1][tmp.Col][1] = tmp.Col;
		q.input(x);//
	}
	if (b[tmp.Row - 1][tmp.Col + 1] == 0 || b[tmp.Row - 1][tmp.Col + 1] == 4) {
		Data x(tmp.Row - 1, tmp.Col + 1, tmp.Step + 1);
		if (b[tmp.Row - 1][tmp.Col + 1] == 0)
			b[tmp.Row - 1][tmp.Col + 1] = 1;
		Record[tmp.Row - 1][tmp.Col + 1][0] = tmp.Row;
		Record[tmp.Row - 1][tmp.Col + 1][1] = tmp.Col;
		q.input(x);
	}
	if (b[tmp.Row][tmp.Col + 1] == 0 || b[tmp.Row][tmp.Col + 1] == 4) {
		Data x(tmp.Row, tmp.Col + 1, tmp.Step + 1);
		if (b[tmp.Row][tmp.Col + 1] == 0)
			b[tmp.Row][tmp.Col + 1] = 1;
		Record[tmp.Row][tmp.Col + 1][0] = tmp.Row;
		Record[tmp.Row][tmp.Col + 1][1] = tmp.Col;
		q.input(x);
	}
	if (b[tmp.Row][tmp.Col - 1] == 0 || b[tmp.Row][tmp.Col - 1] == 4) {
		Data x(tmp.Row, tmp.Col - 1, tmp.Step + 1);
		if (b[tmp.Row][tmp.Col - 1] == 0)
			b[tmp.Row][tmp.Col - 1] = 1;
		Record[tmp.Row][tmp.Col - 1][0] = tmp.Row;
		Record[tmp.Row][tmp.Col - 1][1] = tmp.Col;
		q.input(x);
	}
	if (b[tmp.Row + 1][tmp.Col + 1] == 0 || b[tmp.Row + 1][tmp.Col + 1] == 4) {
		Data x(tmp.Row + 1, tmp.Col + 1, tmp.Step + 1);
		if (b[tmp.Row + 1][tmp.Col + 1] == 0)
			b[tmp.Row + 1][tmp.Col + 1] = 1;
		Record[tmp.Row + 1][tmp.Col + 1][0] = tmp.Row;
		Record[tmp.Row + 1][tmp.Col + 1][1] = tmp.Col;
		q.input(x);
	}
	if (b[tmp.Row + 1][tmp.Col] == 0 || b[tmp.Row + 1][tmp.Col] == 4) {
		Data x(tmp.Row + 1, tmp.Col, tmp.Step + 1);
		if (b[tmp.Row + 1][tmp.Col] == 0)
			b[tmp.Row + 1][tmp.Col] = 1;
		Record[tmp.Row + 1][tmp.Col][0] = tmp.Row;
		Record[tmp.Row + 1][tmp.Col][1] = tmp.Col;
		q.input(x);
	}
	if (b[tmp.Row + 1][tmp.Col - 1] == 0 || b[tmp.Row + 1][tmp.Col - 1] == 4) {
		Data x(tmp.Row + 1, tmp.Col - 1, tmp.Step + 1);
		if (b[tmp.Row + 1][tmp.Col - 1] == 0)
			b[tmp.Row + 1][tmp.Col - 1] = 1;
		Record[tmp.Row + 1][tmp.Col - 1][0] = tmp.Row;
		Record[tmp.Row + 1][tmp.Col - 1][1] = tmp.Col;
		q.input(x);
	}
}

void Board::Clear(int r, int c) {
	if (r == -1 && c == -1) {
		return;
	}
	Clear(Record[r][c][0], Record[r][c][1]);
	cout << '(' << r << ',' << c << ')' << endl;
}
void Board::Search(queue& q) {

	Data tmp(begin[0], begin[1], 0);
	q.input(tmp);
	while (IsOver(q)) {
		tmp = q.output();
		CheckAndInput(tmp, q);
	}
	Clear(end[0], end[1]);
}




Data queue::output() {
	if (IsNull()) {
		return Data(-1, -1, -1);
	}
	else if (head == size - 1) {
		head = 0; count--;
		return q[size - 1];
	}
	else {
		head++; count--;
		return q[head - 1];
	}
}
void queue::input(Data x) {
	if (count == size - 1) {
		Resize();
	}
	if (IsFull()) {
		return;
	}
	else if (tail == size - 1) {
		q[0] = x;
		tail = 0;
		count++;
	}
	else {
		q[++tail] = x;
		count++;
	}
}
queue::queue(int size) :size(size) {
	q = new Data[size];
	head = 0; tail = size - 1;
	count = 0;
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
		for (int j = 0; j < Col; j++) {
			delete[] Record[i][j];
		}
		delete[] Record[i];
	}
	delete[] b;
	delete[] Record;
}

Board::Board(int Row, int Col) {
	this->Row = Row; this->Col = Col;
	b = new int* [Row];
	Record = new int** [Row];
	for (int i = 0; i < Row; i++) {
		int* p = new int[Col];
		int** q = new int* [Col];
		b[i] = p;
		Record[i] = q;
		for (int j = 0; j < Col; j++) {
			int* x = new int[2];
			Record[i][j] = x;
		}
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
	end[0] = 1, end[1] = 1;
	b[Row - 2][Col - 2] = 3;
	begin[0] = Row - 2, begin[1] = Col - 2;
	Record[begin[0]][begin[1]][0] = -1;
	Record[begin[0]][begin[1]][1] = -1;
}
