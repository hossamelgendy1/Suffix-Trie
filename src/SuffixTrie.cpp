#include<iostream>
using namespace std;

class TrieNode;

class ListNode 
{
	ListNode* next;
	TrieNode* childNode;
	char character;

public:
	ListNode(char c);
	void setNext(ListNode* node);
	ListNode* getNext();
	TrieNode* getChildNode();
	char getChar();
};

class LinkedList
{
	int size;
	ListNode* head;

public:
	LinkedList();
	void insert(char c);
	ListNode* getHead();
	ListNode* search(char c);
	ListNode* get(int i);
	int getSize();
};

class TrieNode
{
	LinkedList* children;
	int index;
public:
	TrieNode();
	void addChild(char c);
	void setIndex(int i);
	int getIndex();
	ListNode* search(char c);
	LinkedList* getChildren();
};

class SuffixTrie
{
	TrieNode* root;
	int stringSize;
	void addSuffix(const char* suff, int startIndex);
	void printIndecies(TrieNode* node);
public:
	SuffixTrie(const char* str);
	void Search(const char* sub);
};


int main()
{
	// Construct a suffix trie containing all suffixes of "bananabanaba$"

   //            0123456789012
	SuffixTrie t("bananabanaba$");

	t.Search("ana"); // Prints: 1 3 7
	t.Search("naba"); // Prints: 4 8

	return 0;
}

// ----------------------------------------------------------------------------------------------------------
// class "ListNode" Implementation
// ----------------------------------------------------------------------------------------------------------

ListNode::ListNode(char c)
{
	character = c;
	next = nullptr;
	childNode = new TrieNode();
}

void ListNode::setNext(ListNode* node)
{
	next = node;
}

ListNode* ListNode::getNext()
{
	return next;
}

TrieNode* ListNode::getChildNode()
{
	return childNode;
}

char ListNode::getChar()
{
	return character;
}

// ----------------------------------------------------------------------------------------------------------
// class "LinkedList" Implementation
// ----------------------------------------------------------------------------------------------------------

LinkedList::LinkedList()
{
	head = nullptr;
	size = 0;
}

void LinkedList::insert(char c)
{
	size++;
	ListNode* node = new ListNode(c);
	if (head == nullptr)
	{
		head = node;
		return;
	}
	ListNode* tmp = head;
	while (tmp->getNext() != nullptr)
		tmp = tmp->getNext();
	tmp->setNext(node);
}

ListNode* LinkedList::getHead()
{
	return head;
}

ListNode* LinkedList::search(char c)
{
	ListNode* temp = head;
	while (temp != nullptr)
	{
		if (temp->getChar() == c)
			return temp;
		temp = temp->getNext();
	}
	return nullptr; //if the char isn't found in the list.
}

ListNode* LinkedList::get(int i)
{
	if (i == 0) {
		return head;
	}
	int cnt = 0;
	ListNode* tmp = head;
	while (tmp != nullptr) {
		if (cnt++ == i) {
			return tmp;
		}
		tmp = tmp->getNext();
	}
	return nullptr;
}

int LinkedList::getSize()
{
	return size;
}

// ----------------------------------------------------------------------------------------------------------
// class "TrieNode" Implementation
// ----------------------------------------------------------------------------------------------------------

TrieNode::TrieNode()
{
	children = new LinkedList();
	index = -1;
}

void TrieNode::addChild(char c)
{
	children->insert(c);
}

void TrieNode::setIndex(int i)
{
	index = i;
}

int TrieNode::getIndex()
{
	return index;
}

ListNode* TrieNode::search(char c)
{
	return children->search(c);
}

LinkedList* TrieNode::getChildren()
{
	return children;
}

// ----------------------------------------------------------------------------------------------------------
// class "SuffixTrie" Implementation
// ----------------------------------------------------------------------------------------------------------

void SuffixTrie::addSuffix(const char* suff, int startIndex)
{
	TrieNode* temp = root;
	int suffSize = 0;
	while (suff[suffSize] != '\0')
	{
		suffSize++;
	}
	for (int i = 0; i < suffSize; i++)
	{
		if (temp->search(suff[i]) == nullptr)
		{
			temp->addChild(suff[i]);
		}
		temp = temp->search(suff[i])->getChildNode();
	}
	temp->setIndex(startIndex);
}

void SuffixTrie::printIndecies(TrieNode* node)
{
	if (!node) // base case
		return;	
	TrieNode* tmp = node;
	if (node->getIndex() != -1)
		cout << node->getIndex() << ' ';
	for (int i = 0; i < tmp->getChildren()->getSize(); i++)
	{
		printIndecies(tmp->getChildren()->get(i)->getChildNode());
	}
}

SuffixTrie::SuffixTrie(const char* str)
{
	root = new TrieNode();
	stringSize = 0;
	while (str[stringSize] != '\0')
	{
		stringSize++;
	}
	for (int i = 0; i < stringSize; i++)
	{
		addSuffix(&str[i], i);
	}
}

void SuffixTrie::Search(const char* sub)
{
	TrieNode* temp = root;
	int subSize = 0;
	while (sub[subSize] != '\0')
	{
		subSize++;
	}
	for (int i = 0; i < subSize; i++)
	{
		if (temp->search(sub[i]) == nullptr)
		{
			cout << -1 << endl;
			return;
		}
		temp = temp->search(sub[i])->getChildNode();
	}
	printIndecies(temp);
	cout << endl;
}
