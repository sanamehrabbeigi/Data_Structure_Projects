#include <iostream>
//#include <conio.h>
#include <stack>
#include <string>

using namespace std;

int main()
{
	long long n;
	string s;
	stack<char> st;
	//cin >> n;
	//for (int i = 0; i < n; i++)
	//{
		cin >> s;
		int j = 0;
		for (j = 0; j < s.size(); j++)
		{
			//cout << j << endl;
			if ((s[j] == '(' || s[j] == '[' || s[j] == '{' || s[j] == '<') && (j != (s.size() - 1) && s[j + 1] != '*'))
				st.push(s[j]);
			else if (j != (s.size() - 1) && s[j + 1] == '*' && s[j] == '(')
			{
				st.push(s[j]);
				st.push(s[j + 1]);
				j++;
			}

			else if ((s[j] == ')') && (st.size() != 0) && (st.top() == '('))
				st.pop();
			else if ((s[j] == '}') && (st.size() != 0) && (st.top() == '{'))
				st.pop();
			else if ((s[j] == ']') && (st.size() != 0) && (st.top() == '['))
				st.pop();
			else if ((s[j] == '>') && (st.size() != 0) && (st.top() == '<'))
				st.pop();
			
			else if (j != (s.size() - 1) && (st.size() != 0) && s[j] == '*' && st.top() == '*')
			{
				st.pop();
				if (s[j+1] == ')' && (st.size() != 0) && st.top() == '(')
					st.pop();
				else
				{
					//cout << st.top() << endl;
					cout << "NO" << endl;
					j = s.size() + 1;
				}
				j++;
			}
			else
			{
				//cout << st.top() << endl;
				cout << "NO" << endl;
				j = s.size() + 1;
			}
		}
		if (st.size() == 0 && j < (s.size() + 2))
			cout << "YES" << endl;
		else if (st.size() != 0 && j < (s.size() + 2))
			cout << "NO" << endl;
	//}
	//getch();
	return 0;
}
