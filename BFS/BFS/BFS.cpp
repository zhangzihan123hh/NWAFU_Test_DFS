#include"BFS.h"

int main() {
	int Row, Col; cin >> Row >> Col;
	Board test(Row+2, Col+2);
	queue q(Row * Col);
	test.Search(q);


}
