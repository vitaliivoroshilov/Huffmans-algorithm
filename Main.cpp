#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <list>
using namespace std;

class Node
{
public:
	int count;
	char symbol;
	Node* left, * right;
	
	Node() {}
	Node(char _symbol, int _count)
	{
		symbol = _symbol;
		count = _count;
	}
	Node(Node* l, Node* r)
	{
		symbol = 0;
		left = l;
		right = r;
		count = l->count + r->count;
	}
	static void BuildTable(Node* root, vector<bool>& code, map<char, vector<bool>>& table)
	{
		if (root->left)
		{
			code.push_back(0);
			BuildTable(root->left, code, table);
		}
		if (root->right)
		{
			code.push_back(1);
			BuildTable(root->right, code, table);
		}
		if (root->symbol)
			table[root->symbol] = code;
		if (code.size())
			code.pop_back();
	}
	bool SotrNode(const Node* a, const Node* b)
	{
		return a->count < b->count;
	}
	static string Decode(string& str, map<vector<bool>, char>& table)
	{
		string out = "";
		vector<bool> code;
		for (int i = 0; i < str.length(); i++)
		{
			code.push_back(str[i] == '0' ? false : true);
			if (table[code])
			{
				out += table[code];
				code.clear();
			}
		}
		return out;
	}
	static void print(Node* root, int depth = 0)
	{
		if (!root) return;
		if (root->symbol)
		{
			for (int i = 0; i < depth; i++)
				cout << ".";
			cout << root->symbol << endl;
		}
		else depth++;

		print(root->left, depth);
		print(root->right, depth);
	}
};

int main()
{
	int a = 0, c;
	cout << "Enter the text: " << endl;
	string row;
	getline(cin, row);
	map<char, int> symbols;
	for (int i = 0; i < row.length(); i++)
		symbols[row[i]]++;
	list<Node*> trees;
	map<char, int>::iterator itr;
	for (itr = symbols.begin(); itr != symbols.end(); itr++)
	{
		Node* p = new Node(itr->first, itr->second);
		trees.push_back(p);
	}
	if (trees.size() == 0)
	{
		cout << "String is empty" << endl;
		system("Pause");
		return 0;
	}
	else
	{
		if (trees.size() == 1)
		{
			Node* root = trees.front();
			root->print(root);
			cout << " - " << endl;
			system("Pause");
		}
		else
		{
			while (trees.size() != 1)
			{
				Node* l = trees.front();
				trees.pop_front();
				Node* r = trees.front();
				trees.pop_front();
				Node* parent = new Node(l, r);
				trees.push_back(parent);
			}
		}
	}
	Node* root = trees.front();
	root->print(root);
	vector<bool> code;
	map<char, vector<bool>> table;
	Node::BuildTable(root, code, table);
	for (itr = symbols.begin(); itr != symbols.end(); itr++)
	{
		cout << itr->first << " - ";
		for (int j = 0; j < table[itr->first].size(); j++)
			cout << table[itr->first][j] << endl;
	}
	string out = "";
	for (int i = 0; i < row.length(); i++)
	{
		for (int j = 0; j < table[row[i]].size(); j++)
		{
			out += table[row[i]][j] + '0';
			cout << table[row[i]][j];
		}
		cout << endl;
		cout << out.c_str() << endl;
		map<vector<bool>, char> ftable;
		for (auto i = table.begin(); i != table.end(); i++)
			ftable[i->second] = i->first;
		cout << Node::Decode(out, ftable).c_str() << endl;
		system("Pause");
	}
}