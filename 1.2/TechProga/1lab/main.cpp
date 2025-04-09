#include <iostream>
#include <ctime>
#include <cmath>

using namespace std;

struct element {
	int id;
	char* a;
	float* f;
};

struct lenta {
	element* elems;
	int size = 0;
	int cur_ind = 0;
};

int gen_id() {
	return rand() % 300 - 100;
}

char* gen_chars() {
	int cnt = rand() % 20 + 1;
	char* str = new char[cnt + 1];
	str[cnt] = '\0';
	for (int i = 0; i < cnt; i++) {
		str[i] = char('!' + (rand() % 94));
	}
	return str;
}

float* gen_floats() {
	float* fl = new float[3];
	for (int i = 0; i < 3; i++)
		fl[i] = float(rand() % 200) / float(rand() % 200);
	return fl;
}

void sort_Shell(element els[], int n) {
	for (int step = n / 2; step > 0; step /= 2) {
		for (int i = step; i < n; i++) {
			element cur = els[i];
			int j;
			for (j = i; j >= step && els[j - step].id > cur.id; j -= step)
				els[j] = els[j - step];
			els[j] = cur;
		}
	}
}

void merge_lents(lenta* lents, lenta& res, int sz, int n) {
	for (int i = 0; i < n; i++) {
		element mn;
		mn.id = INT_MAX;
		int ind = -1;
		for (int j = 0; j < sz; j++) {
			if (lents[j].cur_ind < lents[j].size && lents[j].elems[lents[j].cur_ind].id < mn.id)
				ind = j, mn = lents[j].elems[lents[j].cur_ind];
		}
		res.elems[res.size] = mn;
		res.size++;
		lents[ind].cur_ind++;
	}
}

lenta balanced_n_lents(element els[], int n) {
	lenta ans;
	ans.elems = new element[n];
	int sz = ceil(sqrt(n));
	lenta* lents = new lenta[sz];
	for (int i = 0; i < sz; i++) {
		lents[i].elems = new element[sz];
	}
	for (int i = 0; i < n; i++) {
		lents[i % sz].elems[lents[i % sz].size] = els[i];
		lents[i % sz].size += 1;
	}

	for (int i = 0; i < sz; i++) {
		for (int j = 0; j < lents[i].size; j++) {
			cout << lents[i].elems[j].id << " ";
		}
		cout << '\n';
	}
	cout << "_-----------------------------_\n";
	cout << "_-----------------------------_\n";
	cout << "_-----------------------------_\n";
	for (int i = 0; i < sz; i++) {
		sort_Shell(lents[i].elems, lents[i].size);
	}
	for (int i = 0; i < sz; i++) {
		for (int j = 0; j < lents[i].size; j++) {
			cout << lents[i].elems[j].id << " ";
		}
		cout << '\n';
	}
	cout << "_-----------------------------_\n";
	cout << "_-----------------------------_\n";
	cout << "_-----------------------------_\n";
	/*for (int i = 0; i < sz; i++)
		merge_lents(lents[i], ans);*/
	merge_lents(lents, ans, sz, n);
	for (int i = 0; i < n; i++) {
		cout << ans.elems[i].id << " ";
	}
	cout << '\n';
	cout << "_-----------------------------_\n";
	cout << "_-----------------------------_\n";
	cout << "_-----------------------------_\n";
	return ans;
}

int main() {
	srand(time(NULL));
	int n;
	cout << "Input integer number of elements (from 1 to 100): ";
	while (cin >> n) {
		if (n < 1 || n > 100) {
			cout << "Invalid input.\n";
			cout << "Input integer number of elements (from 1 to 100): ";
		}
		else
			break;
	}
	lenta els;
	els.elems = new element[n];
	for (int i = 0; i < n; i++) {
		els.elems[i].id = gen_id();
		els.elems[i].a = gen_chars();
		els.elems[i].f = gen_floats();
	}

	for (int i = 0; i < n; i++) {
		cout << els.elems[i].id << " ";
		cout << els.elems[i].a << " - ";
		for (int j = 0; j < 3; j++) {
			cout << els.elems[i].f[j] << " ";
		}
		cout << '\n';
	}

	cout << "_-----------------------------_\n";
	cout << "_-----------------------------_\n";
	cout << "_-----------------------------_\n";

	els = balanced_n_lents(els.elems, n);

	for (int i = 0; i < n; i++) {
		cout << els.elems[i].id << " ";
		cout << els.elems[i].a << " - ";
		for (int j = 0; j < 3; j++) {
			cout << els.elems[i].f[j] << " ";
		}
		cout << '\n';
	}
	return 0;
}
