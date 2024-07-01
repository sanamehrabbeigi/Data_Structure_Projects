#include <iostream>
//#include <conio.h>
#include <map>
#include <string>

using namespace std;

typedef struct node {
	int data;
	struct node* next;
}node;

node * root = NULL;
node * last = NULL;

int main()
{
	map <int, int> mp;
	long long n, t, a, m;
	string s;
	cin >> m;
	for (int k = 0; k < m; k++)
	{
		cout << "Scenario #" << k + 1 << endl;
		cin >> n;
		for (int i = 0; i < n; i++)
		{
			cin >> t;
			for (int j = 0; j < t; j++)
			{
				cin >> a;
				mp[a] = i;
			}
		}

		cin >> s;
		while (s != "STOP")
		{
			if (s == "DEQUEUE")
			{
				cout << root->data << endl;
				root = root->next;
			}
			else if (s == "ENQUEUE")
			{
				cin >> a;
				node * newnode = (node *)malloc(sizeof(node));
				newnode->data = a;
				newnode->next = NULL;

				if (root == NULL)
				{
					root = newnode;
					last = newnode;
				}
				else
				{
					node * temp;
					bool b = 0;
					for (temp = root; temp->next != NULL; temp = temp->next)
					{
					//	cout << temp->data <<"  "<<mp[temp->data] << "  " << mp[a] << endl;
						if ( mp[temp->data] == mp[a])
						{
							while (temp ->next != NULL && mp[temp->next->data] == mp[a])
								temp = temp->next;
						//	cout << "temp data" << temp->data << endl;
							newnode->next = temp->next;
							temp->next = newnode;
							b = 1;
							break;
						}
					}
					if (b == 0)
					{
						//cout << "temp data NULL" << temp->data << endl;
						last->next = newnode;
						last = newnode;
					}
				}
			}
			cin >> s;
		}
	}
	//getch();
	return 0;
}
