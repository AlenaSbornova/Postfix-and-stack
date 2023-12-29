#pragma once
#include "Tstack.h"
#include <string>
class Tpostfix
{
private:
	string s; //исходна€€ стррока которую мы преобразовываем
	string res;// строка в постфиксном виде
	Tstack st; //стек дл€ хранени€ операций
	char lex[100][2]; //массив дл€ хранени€ лексем, где во втором столбце хранитс€ 1) цифра 3) "+" или "-" 2) "*" или "\" 4) "(" 5) ")"
	int r; //кол-во символов в исходной строке
	int n; //состо€ние класса -1) отсутствует сторока дл€ обработки 0) начало рабoты передана строка дл€ обработки 1) строка преобразованна в набор лексем 2)завершена проверка на соответсвие скобок 3) завершена полна€ проверка строки 4)строка преобразована в постфиксную запись  6)ошибка неверный пор€док скобок 7)ошибка неверный пор€док лексем 8)ошибка отсутствует строка или встречен неверный символ
public:
	Tpostfix(string str) {
		lex[0][0] = 0;
		n = 0;
		s = str;
		r = str.size();
		if (r == 0)
			n = -1;
		res = "";
	}
	void toLex() {
		if (n == 0) {
			n = 1;
			for (int i = 0; i < r; i++) {
				if ((s[i] >= '0') && (s[i] <= '9')) {
					lex[i][1] = 1;
				}
				if ((s[i] == '+') || (s[i] == '-')) {
					lex[i][1] = 3;
				}
				if ((s[i] == '*') || (s[i] == '/')) {
					lex[i][1] = 2;
				}
				if (s[i] == '(') {
					lex[i][1] = 4;
				}
				if (s[i] == ')') {
					lex[i][1] = 5;
				}
				if (lex[i][1] < 1)
					n = 5;
				lex[i][0] = s[i];
			}
		}
		else
			n = 8;
	}
	void checkBra() {
		if (n == 0) {
			(*this).toLex();
		}
		if (n == 1) {
			n = 2;
			int k1 = 0, k2 = 0;
			for (int i = 0; i < r; i++) {
				if (lex[i][1] == 4)
					k1++;
				if (lex[i][1] == 5) {
					if (k1 > k2)
						k2++;
					else
						n = 6;
				}
			}
			if (k1 > k2)
				n = 6;
		}
		else
			n = 8;
	}
	void checkLex() {
		if (n < 2) {
			(*this).checkBra();
		}
		if (n == 2) {
			n = 3;
			if ((lex[0][1] == 1) || (lex[0][1] == 4)) {
				for (int i = 1; (i < r - 1) && (n == 3); i++) {
					switch (lex[i][1]) {
					case 1: {
						if ((lex[i - 1][1] != 2) && (lex[i - 1][1] != 3) && (lex[i - 1][1] != 4)) {
							n = 7;
						}
						break;
					}
					case 2: {
						if ((lex[i - 1][1] != 1) && (lex[i - 1][1] != 5)) {
							n = 7;
						}
						break;
					}
					case 3: {
						if ((lex[i - 1][1] != 1) && (lex[i - 1][1] != 5)) {
							n = 7;
						}
						break;
					}
					case 4: {
						if ((lex[i - 1][1] != 2) && (lex[i - 1][1] != 3) && (lex[i - 1][1] != 4)) {
							n = 7;
						}
						break;
					}
					case 5: {
						if ((lex[i - 1][1] != 1) && (lex[i - 1][1] != 5)) {
							n = 7;
						}
						break;
					}
					}
				}
				if ((lex[r - 1][1] != 1) && (lex[r - 1][1] != 5)) {
					n = 7;
				}
			}
			else
				n = 7;
		}
	}
	string toPostfix() {
		if (n < 3) {
			(*this).checkLex();
		}
		if (n == 3) {
			n = 4;
			for (int i = 0; i < r; i++) {
				if (lex[i][1] == 1) {
					res += lex[i][0];
				}
				if (lex[i][1] == 4) {
					st.put(i);
				}
				if (lex[i][1] == 5) {
					while (lex[st.view()][1] != 4) {
						res += lex[st.get()][0];
					}
					st.get();

				}
				if ((lex[i][1] > 1) && (lex[i][1] < 4)) {
					while (st.isEmpty() == 0) {
						if (lex[st.view()][1] <= lex[i][1]) {
							res += lex[st.get()][0];
						}
						else
							break;
					}
					st.put(i);
				}
			}
			while (st.isEmpty() == 0) {
				res += lex[st.get()][0];
			}
		}
		return res;
	}
	int calculate() {
		if (n < 4) {
			(*this).toPostfix();
		}
		if (n == 4) {
			int s;
			int calc[100] = {};
			int k = -1;
			int l = res.size();
			for (int i = 0; i < l; i++) {
				if ((res[i] >= '0') && (res[i] <= '9')) {
					k++;
					calc[k] = res[i] - '0';
				}
				if (res[i] == '+') {
					s = calc[k] + calc[k - 1];
					k = k - 1;
					calc[k] = s;

				}
				if (res[i] == '-') {
					s = calc[k - 1] - calc[k];
					k = k - 1;
					calc[k] = s;
				}
				if (res[i] == '*') {
					s = calc[k] * calc[k - 1];
					k = k - 1;
					calc[k] = s;
				}
				if (res[i] == '/') {
					s = calc[k - 1] / calc[k];
					k = k - 1;
					calc[k] = s;
				}
			}
			s = calc[k];
			return s;
		}
	}
	int status() {
		return n;
	}

};

