#include<iostream>
#include<conio.h>
#include <cstdlib> 
#include <map>
#include <string>
#include<fstream>
using namespace std;

#define MAX_TREE_HT 200
map <char, string> mp;

struct MinHeapNode {
	char data;
	unsigned freq;
	struct MinHeapNode *left, *right;
};

struct MinHeap {
	unsigned size;
	unsigned capacity;
	struct MinHeapNode** array;
};

struct MinHeapNode* newNode(char data, unsigned freq)
{
	struct MinHeapNode* temp
		= (struct MinHeapNode*)malloc
		(sizeof(struct MinHeapNode));

	temp->left = temp->right = NULL;
	temp->data = data;
	temp->freq = freq;

	return temp;
}
struct MinHeap* createMinHeap(unsigned capacity)

{

	struct MinHeap* minHeap
		= (struct MinHeap*)malloc(sizeof(struct MinHeap));

	minHeap->size = 0;

	minHeap->capacity = capacity;

	minHeap->array
		= (struct MinHeapNode**)malloc(minHeap->
			capacity * sizeof(struct MinHeapNode*));
	return minHeap;
}

void swapMinHeapNode(struct MinHeapNode** a,
	struct MinHeapNode** b)

{

	struct MinHeapNode* t = *a;
	*a = *b;
	*b = t;
}

void minHeapify(struct MinHeap* minHeap, int idx)

{

	int smallest = idx;
	int left = 2 * idx + 1;
	int right = 2 * idx + 2;

	if (left < minHeap->size && minHeap->array[left]->
		freq < minHeap->array[smallest]->freq)
		smallest = left;

	if (right < minHeap->size && minHeap->array[right]->
		freq < minHeap->array[smallest]->freq)
		smallest = right;

	if (smallest != idx) {
		swapMinHeapNode(&minHeap->array[smallest],
			&minHeap->array[idx]);
		minHeapify(minHeap, smallest);
	}
}

int isSizeOne(struct MinHeap* minHeap)
{

	return (minHeap->size == 1);
}

struct MinHeapNode* extractMin(struct MinHeap* minHeap)

{

	struct MinHeapNode* temp = minHeap->array[0];
	minHeap->array[0]
		= minHeap->array[minHeap->size - 1];

	--minHeap->size;
	minHeapify(minHeap, 0);

	return temp;
}

void insertMinHeap(struct MinHeap* minHeap,
	struct MinHeapNode* minHeapNode)

{

	++minHeap->size;
	int i = minHeap->size - 1;

	while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq) {

		minHeap->array[i] = minHeap->array[(i - 1) / 2];
		i = (i - 1) / 2;
	}

	minHeap->array[i] = minHeapNode;
}

void buildMinHeap(struct MinHeap* minHeap)

{

	int n = minHeap->size - 1;
	int i;

	for (i = (n - 1) / 2; i >= 0; --i)
		minHeapify(minHeap, i);
}

// A utility function to print an array of size n 
string saveArr(int arr[], int n)
{
	string s;
	for (int i = 0; i < n; ++i)
		s.push_back(arr[i] + '0');
	return s;
}

int isLeaf(struct MinHeapNode* root)

{

	return !(root->left) && !(root->right);
}

struct MinHeap* createAndBuildMinHeap(char data[], int freq[], int size)

{

	struct MinHeap* minHeap = createMinHeap(size);

	for (int i = 0; i < size; ++i)
		minHeap->array[i] = newNode(data[i], freq[i]);

	minHeap->size = size;
	buildMinHeap(minHeap);

	return minHeap;
}

struct MinHeapNode* buildHuffmanTree(char data[], int freq[], int size)

{
	struct MinHeapNode *left, *right, *top;

	struct MinHeap* minHeap = createAndBuildMinHeap(data, freq, size);

	while (!isSizeOne(minHeap)) {

		left = extractMin(minHeap);
		right = extractMin(minHeap);
		//cout << left->freq << "  " << right->freq << endl;

		top = newNode('$', left->freq + right->freq);

		top->left = left;
		top->right = right;

		insertMinHeap(minHeap, top);
	}

	return extractMin(minHeap);
}

void saveCodes(struct MinHeapNode* root, int arr[], int top)
{
	if (root->left)
	{
		arr[top] = 0;
		saveCodes(root->left, arr, top + 1);
	}

	if (root->right)
	{
		arr[top] = 1;
		saveCodes(root->right, arr, top + 1);
	}
	if (isLeaf(root))
		mp[root->data] = saveArr(arr, top);
}

void HuffmanCodes(char data[], int freq[], int size)
{
	struct MinHeapNode* root
		= buildHuffmanTree(data, freq, size);

	int arr[MAX_TREE_HT], top = 0;

	saveCodes(root, arr, top);
}

int main()
{
	
	string text;
	char arr[128];
	int ferq[128] = { 0 };
	int charNum = 0;
	ifstream file;
	file.open("example.txt");
	string temp;
	while (getline(file, temp))
	{
		text += temp + "\n";
	}
	
	temp = text;
	string temp2 = "";
	for (int i = 0; i<text.size(); i++)
	{

		arr[charNum] = temp[0]; 
		for (int j = 0; j<temp.size(); j++)
		{
			if (temp[j] == temp[0])
			{
				ferq[charNum]++;

			}
			else if (temp[j] != '\n')
				temp2.push_back(temp[j]);

		}
		charNum++;
		temp = temp2;
		temp2 = "";
		if (temp == "")
			break;
	}
	for (int i = 0; i<charNum; i++)
	{
		for (int j = i + 1; j<charNum; j++)
		{
			if (ferq[i]>ferq[j])
			{
				int temp;
				temp = ferq[i];
				ferq[i] = ferq[j];
				ferq[j] = temp;
				char tempch;
				tempch = arr[i];
				arr[i] = arr[j];
				arr[j] = tempch;
			}
		}
	}
	file.close();

	HuffmanCodes(arr, ferq, charNum);

	ofstream outFile("resualt.txt");

	for (int i = 0; i < text.size(); i++)
	{
		if (text[i] == '\n')
			outFile << '\n';
		else
			outFile << mp[text[i]];
	}
	outFile.close();
	getch();
	return 0;
}