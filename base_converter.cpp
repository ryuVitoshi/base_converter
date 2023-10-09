#include <iostream>
#include <vector>
#include <algorithm>
#include <windows.h>
#include <sstream>
#include <ctime>
using namespace std;

string vs (string, int, int);
vector<int> reverse (vector<int>);
char vector_compare (vector<int>, vector<int>);
vector<int> AuB (vector<int>, vector<int>);
vector<int> AuB (vector<int>, int);
vector<int> ApB (vector<int>, vector<int>);
vector<int> AmB (vector<int>, vector<int>);
pair<vector<int>, vector<int> > ArB (vector<int>, vector<int>, int);
pair<vector<int>, vector<int> > ArB (vector<int>, vector<int>);
void vector_print (vector<int>, char);
void vector_print (vector<int>);
string vector_to_string (vector<int>, char);
string vector_to_string (vector<int>);
vector<int> string_to_vector (string);
vector<int> int_to_vector (int);

bool debug = false;
int main1 () {
	srand(time(0));
	string str;
	bool can = true;
	while (can) {
		str = "";
		int length = rand()%500+1;
		int a = rand()%35+2;
		for (int p = 0; p < length; p++) {
			int t;
			if (p == 0) t = rand()%(a-1)+1;
			else t = rand()%a;
			if (t < 10) str += t+'0';
			else str += t-10+'A';
		}
		int b = rand()%35+2;
		cout << str << endl << a << endl << b << endl;
		string ans = vs(str, a, b);
		cout << "ans: " << ans << endl << endl;
		if (str != vs(ans, b, a)) break;
		//Sleep(500);
	}
	return 0;
}
int main () {
	while (true) {
		string str;
		unsigned short int a, b;
		//getline(cin, str);
		cout << "String: ";
		cin >> str;
		cout << "01: ";
		cin >> a;
		cout << "o2: ";
		cin >> b;
		str = vs(str, a, b);
		cout << "\nAnswer: " << str << "\n\n";
	}
	return 0;
}
int main2 () {
	string cc = "4000000000";
	vector<int> c(string_to_vector(cc));
	vector<int> pi(c);
	for (int i = 2; true; i++) {
		if (i % 2 == 1) pi = ApB(pi, ArB(c, int_to_vector(2*i-1)).first);
		else pi = AmB(pi, ArB(c, int_to_vector(2*i-1)).first);
		if (i % 10 == 0) cout << endl << vector_to_string(pi);
	}
	return 0;
}
string vs (string str, int _o1, int _o2) {
	if ((_o1 < 2 || _o1 > 36) || (_o2 < 2 || _o2 > 36)) return ".1";
	else {
		char n;
		vector<int> num(2);
		vector<int> o1(2);
		o1[0] = _o1%10;
		o1[1] = _o1/10;
		vector<int> o2;
		if (_o2 >= 10) {
			o2.push_back(_o2/10);
			o2.push_back(_o2%10);
		}else o2.push_back(_o2);
		vector<int> pow(1);
		pow[0] = 1;
		vector<int> ans;
		for (int p = 0; p < str.length(); p++) {
			n = str.at(str.length()-1-p);
			if (n >= '0' && n <= '9') num[0] = n - '0';
			else if (n >= 'A' && n <= 'Z') num[0] = n - 'A' + 10;
			else if (n >= 'a' && n <= 'z') num[0] = n - 'a' + 10;
			else if (n == ' ') num[0] = 0;
			else return ".3";
			if (debug) cout << endl << p << ". " << n << " --> " << num[0]; // debug
			if (num[0] >= _o1) return ".2";
			num[1] = num[0]/10;
			num[0] %= 10;
			if (p > 0) {
				pow = reverse(AuB(reverse(o1), reverse(pow)));
			}
			vector<int> _ans(reverse(AuB(reverse(pow), reverse(num))));
			//ans.push_back(_ans);
			//ans.insert(ans.begin() + p, _ans);
			for (int i = 0; i < _ans.size(); i++)
				if (i >= ans.size()) ans.insert(ans.begin() + i, _ans.at(i));
				else ans.at(i) += _ans.at(i);
		    if (debug) vector_print(ans, '.'); // debug
		    _ans.clear();
		}
		for (int i = 0; i < ans.size(); i++) {
			int t = ans.at(i);
			for (int g = 0; t > 0; g++) {
				if (i + g >= ans.size()) ans.insert(ans.begin() + i + g, t%10);
				else if (g == 0) ans.at(i + g) = t%10;
				else ans.at(i + g) += t%10;
				t /= 10;
				if (debug) vector_print(ans, '-'); // debug
			}
		}
		ans = reverse(ans);
		vector<int> klk;
		pair<vector<int>, vector<int> > pair;
				//cout << "\n10: " << vector_to_string(ans);
		while (ans.at(0) != 0) {
			pair = ArB(ans, o2);
			ans = pair.first;
			vector<int> t(pair.second);
					//cout << "\n ans: " << vector_to_string(ans);
					//cout << "\n t: " << vector_to_string(t);
			if (t.size() == 1) klk.push_back(t.at(0));
			else if (t.size() == 2) klk.push_back(t.at(0)*10+t.at(1));
			else cout << "\nAAAAAAAAAAAAAAAAAAAAAA";
		}
		//cout << "\n--------------------------------";
		str = "";
		for (int i = 0; i < klk.size(); i++) {
			if (klk.at(klk.size()-1-i) < 10) str += (klk.at(klk.size()-1-i) + '0');
			else str += (klk.at(klk.size()-1-i) -10 + 'A');
					//cout << "\n    " << klk.at(klk.size()-1-i);
		}
		return str;
	}
}
vector<int> AuB (vector<int> a, vector<int> b) {
	a = reverse(a);
	b = reverse(b);
	int size = a.size() + b.size() + 1;
	vector<int> c(size, 0);
	
	for (int ix = 0; ix < a.size(); ix++)
	    for (int jx = 0; jx < b.size(); jx++)
	        c[ix + jx] += a[ix] * b[jx];
	
	for (int ix = 0; ix < size; ix++) {
	    c[ix + 1] +=  c[ix] / 10;
	    c[ix] %= 10;
	}
	 
	while (c[size-1] == 0 && size > 1) {
	    size--;
	    c.erase(c.begin() + size);
	}
	return reverse(c);
}
vector<int> AuB (vector<int> a, int b) {
	a = reverse(a);
	int t = b, size_b = 0;
	while (t > 0) {
		t /= 10;
		size_b++;
	}
	int size = a.size() + size_b + 1;
	vector<int> c(size, 0);
	
	for (int ix = 0; ix < a.size(); ix++)
	    c[ix] += a[ix] * b;
	
	for (int ix = 0; ix < size; ix++) {
	    c[ix + 1] +=  c[ix] / 10;
	    c[ix] %= 10;
	}
	 
	while (c[size-1] == 0 && size > 1) {
	    size--;
	    c.erase(c.begin() + size);
	}
	return reverse(c);
}
pair<vector<int>, vector<int> > ArB (vector<int> a, vector<int> b) {
	vector<int> d;
	for (int g = 0; g < a.size();) {
		d.push_back(a.at(g));
		g++;
		if (vector_compare(d, b) != '<') {
			pair<vector<int>, vector<int> > pair = ArB(a, b, g);
			vector<int> pf(pair.first);
			vector<int> ps(pair.second);
			if (pf.empty()) pf.push_back(0);
			if (ps.empty()) ps.push_back(0);
			return make_pair(pf, ps);
		}
	}
	vector<int> p(1, 0);
	return make_pair(p, a);
}
pair<vector<int>, vector<int> > ArB (vector<int> a, vector<int> b, int c) {
	vector<int> ans;
	vector<int> d;  // delitel'
	int g = 0;
	for (; g < c;) {
		d.push_back(a.at(g));
		g++;
		if (vector_compare(d, b) != '<') {
			break;
		}
	}
			//cout << "\ndelitel': " << vector_to_string(d);
	for (int i = 0; i <= 10; i++) {
		vector<int> t(AuB(b, i));
				//cout << "\n " << i << ". " << vector_to_string(t) << " " << vector_compare(t, d) << " " << vector_to_string(d);
		if (vector_compare(t, d) != '<') {
			vector<int> r;
			if (vector_compare(t, d) == '>') {
				r = AmB(  b, AmB(t, d)  );  // remainder
			}else {
				r.clear();
				i++;
			}
			int size_r = r.size();
					//cout << "\n  ostatok: " << vector_to_string(r);
			if (a.begin()+d.size() >= a.end()) {
				ans.insert(ans.begin(), i-1);
				return make_pair(ans, r);
			}else r.insert(r.end(), a.begin()+d.size(), a.end());
					//vector_print(r);
			pair<vector<int>, vector<int> > _ans= ArB(r, b, size_r+1);
			ans.insert(ans.end(), _ans.first.begin(), _ans.first.end());
			ans.insert(ans.begin(), i-1);
			return make_pair(ans, _ans.second);
		}
	}
}
vector<int> ApB (vector<int> a, vector<int> b) {
			//cout<<vector_compare(a, b);
	if (vector_compare(a, b) == '<') {
		vector<int> t(a);
		a = b;
		b = t;
	}
	a = reverse(a);
	b = reverse(b);
	int size = a.size() + 1;
	a.push_back(0);
	for (int ix = 0; ix < size; ix++) {
				//vector_print(a, ' ');
	    if (ix < b.size()) a[ix] += b[ix];
	    a[ix + 1] += (a[ix] / 10);
	    a[ix] %= 10;
	}
			//vector_print(reverse(a));
	if (a[size - 1] == 0 && size > 1) {
	    size--;
	    a.erase(a.begin() + size);
	}
	return reverse(a);
}
vector<int> AmB (vector<int> a, vector<int> b) {
	a = reverse(a);
	b = reverse(b);
	int size = a.size();
	
	for (int ix = 0; ix < size; ix++) {
		if (ix < b.size())
			a[ix] -= b[ix];
		if (a[ix] < 0) {
	    	a[ix] += 10;
			a[ix + 1] -= 1;
		}
	}
	 
	while (a[size-1] == 0 && size > 1) {
	    size--;
	    a.erase(a.begin() + size);
	}
	return reverse(a);
}
vector<int> reverse (vector<int> a) {
	for (int i = a.size()-1; i >= (a.size()+1)/2; i--) {
		int t = a[i];
		a[i] = a[a.size()-1-i];
		a[a.size()-1-i] = t;
	}
	return a;
}
char vector_compare (vector<int> a, vector<int> b) {
	if (a.size() == b.size())
		if (a == b) return '=';
		else
			for (int i = 0; i < a.size(); i++) {
				if (a.at(i) < b.at(i)) return '<';
				else if (a.at(i) > b.at(i)) return '>';
			}
	else return (a.size() > b.size())?'>':'<';
}
void vector_print (vector<int> a, char b) {
	cout << endl;
	for (int i = 0; i < a.size(); i++) {
		cout << a[i];
		if (a.size()-1 > i) cout << b;
	}
}
void vector_print (vector<int> a) {
	cout << endl;
	for (int i = 0; i < a.size(); i++) cout << a[i];
}
string vector_to_string (vector<int> a, char b) {
	string str;
	stringstream s;
	for (int i = 0; i < a.size(); i++) {
		s << a[i];
		if (a.size()-1 > i) s << b;
	}
	s >> str;
	return str;
}
string vector_to_string (vector<int> a) {
	string str;
	stringstream s;
	for (int i = 0; i < a.size(); i++) s << a[i];
	s >> str;
	return str;
}
vector<int> string_to_vector (string a) {
	vector<int> c;
	for (int i = 0; i < a.length(); i++) {
		c.push_back(a.at(i)-'0');
	}
	return c;
}
vector<int> int_to_vector (int a) {
	vector<int> b;
	while (a > 0) {
		b.push_back(a%10);
		a /= 10;
	}
	b = reverse(b);
	return b;
}
