#pragma once
#include <iostream>
using namespace std;


class Tstack
{
private:
	int r = 50;
	int k; //кол-во эл-тов лежащих в стеке
	int a[50];
public:
	Tstack() {
		k = -1;
		a[0] = 0;
	}
	char view() {
		if (k <= (-1))
			cout << "Ошибка, попытка просмора из пустого стека";
		else
			return a[k];

	}
	Tstack put(char c) {
		if (r <= k++) {
			cout << "Ошибка, переполнение стека";
		}
		a[k] = c;
		return *this;
	}
	char get() {
		k = k - 1;
		return a[k + 1];
	}
	Tstack operator=(Tstack st) {
		k = st.k;
		for (int i = 0; i <= k; i++) {
			a[i] = st.a[i];
		}
		return *this;
	}
	Tstack copy(Tstack st) {
		*this = st;
	}
	int isEmpty() {
		if (k == -1)
			return 1;
		else
			return 0;
	}
};

