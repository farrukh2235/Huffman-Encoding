#include<iostream>
#include<fstream>
#include<vector>
#include<queue>
#include<string>

using namespace std;









struct codes
{
	char c;
	vector<int> code;
	codes(vector<int> w, char ci)
	{
		code = w;
		c = ci;
	}
	codes()
	{

	}
};







struct huffnode
{
	char mychar;
	int frequency;
	huffnode * left;
	huffnode *right;
	huffnode()
	{
		mychar = '\0';
		frequency = 0;
		right = nullptr;
		left = nullptr;
	}
	huffnode(char c, int f)
	{
		mychar = c;
		frequency = f;
		right = nullptr;
		left = nullptr;
	}
	huffnode(char c, int f, huffnode * a, huffnode * b)
	{
		mychar = c;
		frequency = f;
		right = b;
		left = a;
	}


};









class minheap
{
private:
	huffnode **mypriorityqueue;
	huffnode *root;
	vector<codes> p;
	int cap;
	int size;
	string alpha;
public:
	~minheap()
	{
		for (int i = 0; i < size; i++)
		{
			mypriorityqueue[i] = nullptr;
		}
		root = nullptr;
		delete[] mypriorityqueue;
		delete[] root;
		cap = 0;
		size = 0;
	}
	minheap()
	{
		root = nullptr;
		mypriorityqueue = nullptr;
		cap = 0; size = 0;
	}
	minheap(huffnode **f)
	{
		mypriorityqueue = f;
	}
	minheap(int c)
	{
		mypriorityqueue = new huffnode*[c];
		cap = c;
		size = 0;


	}
	void makingsize(int c)
	{
		mypriorityqueue = new huffnode*[c];
		cap = c;
		size = 0;

	}
	void insert(huffnode *p)
	{
		mypriorityqueue[size] = p;
		size++;
	}
	void reinsert(huffnode *c)
	{
		huffnode **p = new huffnode*[size + 1];
		int i = 0, j = 0;;
		for (i, j; j < size; i++, j++)
		{
			if (c->frequency >= mypriorityqueue[i]->frequency)
			{
				p[i] = mypriorityqueue[j];
			}
			else
			{
				break;
			}
		}
		p[i] = c;
		i++;
		for (j; j < size; j++, i++)
		{
			p[i] = mypriorityqueue[j];
		}
		mypriorityqueue = nullptr;
		mypriorityqueue = p;
		size = i;
	}
	huffnode * pop()
	{
		huffnode *p = mypriorityqueue[0];
		for (int i = 0; i < size - 1; i++)
		{
			mypriorityqueue[i] = mypriorityqueue[i + 1];
		}
		size--;
		return p;
	}
	void display()
	{
		for (int i = 0; i < size; i++)
		{
			cout << mypriorityqueue[i]->mychar << "    " << mypriorityqueue[i]->frequency << endl;
		}
		cout << endl << endl << endl;
	}
	huffnode * creatingcode()
	{
		while (size != 1)
		{
			huffnode *left1 = pop();
			huffnode *right1 = pop();
			
			huffnode *temp = new huffnode('\0', right1->frequency + left1->frequency, left1, right1);
			reinsert(temp);

		}
		return pop();
	}
	
	void printcodes()
	{
		for (int i = 0; i < p.size(); i++)
		{
			cout << p[i].c << "      ";
			for (int j = 0; j < p[i].code.size(); j++)
			{
				cout << p[i].code[j];
			}
			cout << endl;
		}
	}
	void save_in_a_file()
	{
		ofstream fout("mycodes.txt");
		for (int i = 0; i < p.size(); i++)
		{
			fout << p[i].c << "      ";
			for (int j = 0; j < p[i].code.size(); j++)
			{
				fout << p[i].code[j];
			}
			fout << endl;
		}
		fout.close();
	}
	void savecodes( int arr[],int top,char character )
	{
		codes w;
		w.c = character;
		for (int i = 0; i < top; i++)
		{
			w.code.push_back(arr[i]);
		}
		p.push_back(w);
	}
	void encoding(huffnode* p, int arr[], int top)
	{
		if (p->left != nullptr)
		{
			arr[top] = 0;
			encoding(p->left, arr, top + 1);
		}
		if (p->right != nullptr)
		{
			arr[top] = 1;
			encoding(p->right, arr, top + 1);
		}
		if (isLeaf(p))
		{
			char c = p->mychar;
			savecodes(arr, top, c);

		}
			
	}
	bool isLeaf(huffnode *p)
	{
		if (p->left == nullptr&&p->right == nullptr)
		{
			return true;
		}
		return false;
	}
	void codeChecker()
	{
		string s;
		bool flag = false;
		cout << " Plz entre the code" << endl;
		cin >> s;
		int count = 0;
		for (int i = 0; i < p.size(); i++)
		{
			count = 0;
			for (int j = 0; j < p[i].code.size(); j++)
			{

				if (p[i].code.size() != s.size() || s[j] - 48 != p[i].code[j])
				{
					break;
				}
				else
				{
					count++;
				}
			}
			if (count == s.size())
			{
				flag = true;
				break;
			}
		}
		if (flag)
		{
			cout << " Is Present" << endl;
		}
		else
		{
			cout << "Not present" << endl;
		}

		

	}
	string  readincodesmessage()
	{
		ifstream fin("encodedInput.txt");
		char i = 0;
		string themessage="";
		string forreading = "";
		char thecharacter;
		while (fin >> i)
		{
			forreading += i;
			if (decoded_message(forreading, thecharacter))
			{
				themessage += thecharacter;
				forreading.clear();
			}
		}
		fin.close();
		return themessage;
	}
	bool checkingsize(string a)
	{
		for (int i = 0; i <p.size(); i++)
		{
			if (a.size() == p[i].code.size())
			{
				return true;
			}
		}
		return false;
	}
	bool decoded_message(string a, char &thecharacter)
	{
		int count = 0;
		

			for (int i = 0; i < p.size(); i++)
			{
				count = 0;
				for (int j = 0; j < p[i].code.size(); j++)
				{

					if (p[i].code.size() != a.size()||a[j] - 48 != p[i].code[j])
					{
						break;
					}
					else
					{
						count++;
					}
				}
				if (count == a.size())
				{
					thecharacter = p[i].c;
					return true;
				}
			}

		return false;
	}
	void checkcharacter_in_code()
	{
		char ch;
		cout << " Plz Entre a Character to find it  " << endl;
		cin >> ch;
		bool flag = false;
		for (int i = 0; i < p.size(); i++)
		{
			if (ch == p[i].c)
			{
				flag = true;
			}
		}
		if (flag)
		{
			cout << " Your Character is present" << endl;
		}
		else
		{
			cout << " Not Found" << endl;
		}
	}
	

	void genratecode(int no)
	{

		if (no == 1)
		{
			root = creatingcode();
			int arr[100];
			encoding(root, arr, 0);
			save_in_a_file();
		}
		else if (no == 2)
		{
			printcodes();
		}
		else if (no == 3)
		{
			 alpha = readincodesmessage();
		}
		else if (no == 4)
		{
			cout << alpha << endl;
		}
		else if (no == 5)
		{
			codeChecker();
		}
		else if (no == 6)
		{
			checkcharacter_in_code();

		}

	}

};






void ascending_order(vector<int> &a, vector<char> &b)
{
	for (int i = 0; i < a.size(); i++)
	{
		for (int j = 0; j < a.size()-1; j++)
		{
			if (a[j]>a[j+1])
			{
				swap(a[j], a[j+1]);
				swap(b[j], b[j+1]);
			}
		}
	}
}

bool unique(char a, vector <char> &w)
{
	for (int i = 0; i < w.size(); i++)
	{
		if (a == w[i])
		{
			return false;
		}
	}
	return true;
}

vector<char>  readfile(ifstream &fin, vector<char> & a)
{
	char c;
	vector<char> w;
	while (fin.get(c))
	{
		a.push_back(c);
		if (unique(c, w))
		{
			w.push_back(c);
		}
		cout << c;
	}
	return w;
}

template<typename t>
void display(vector<t> a)
{
	for (int i = 0; i < a.size(); i++)
	{
		cout << a[i];
	}
	cout << endl;
}

vector<int> alphabatscounts(vector<char>a, vector<char> b)
{
	vector<int> w;
	int count = 0;
	for (int i = 0; i < a.size(); i++)
	{
		count = 0;

		for (int j = 0; j<b.size(); j++)
		{
			if (a[i] == b[j])
			{
				count++;
			}
		}
		w.push_back(count);
	}
	return w;
}

void menu()
{
	int no;
	//minheap w(counter.size());
	minheap w;
	while (true)
	{
		
		cout << "Press 1 to read a single sentence or sentences from a file input.txt to generate codes and save them in a new file myCodes.txt"<<endl;
		cout << "Press 2 to display codes generated against each character" << endl;
		cout << "Press 3 to read an encoded message(in form of 0’s and 1’s)from file “encodedInput.txt”" << endl;
		cout<<"Press 4 to display the decoded message against the messageread in option 3"<<endl;
		cout<<"Press 5 for searching whether a code is present in yourgenerated codes or not " << endl;
		cout << "Press 6 for searching whether a character is present in your codes or not " << endl;
		cout << "Press 7 to EXIT" << endl;
		cout << endl << endl << endl;
		cout << "Plz Entre a number " << endl;
		cin >> no;
		if (no == 1)
		{
			ifstream fin("input.txt");
			queue<huffnode> tree;
			vector<char> a;
			vector<char> unique_alphabats = readfile(fin, a);
			vector<int> counter = alphabatscounts(unique_alphabats, a);
			ascending_order(counter, unique_alphabats);
			w.makingsize(counter.size());
			for (int i = 0; i <counter.size(); i++)
			{
				huffnode * p = new huffnode(unique_alphabats[i], counter[i]);
				w.insert(p);
			}
			w.genratecode(no);
		}
		else if (no == 2)
		{
			w.genratecode(no);
		}
		else if (no == 3)
		{
			w.genratecode(no);
		}
		else if (no == 4)
		{
			w.genratecode(no);
		}
		else if (no == 5)
		{
			w.genratecode(no);
		}
		else if (no == 6)
		{
			w.genratecode(no);
		}

		else if (no == 7)
		{
			break;
		}

		


	}
	
}







int main()
{
	menu();
	system("pause");
	return 0;

}