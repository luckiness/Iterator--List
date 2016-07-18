#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <string>
#include<assert.h>
using namespace std;

template<class T>
struct _ListNode
{
	_ListNode<T>* _next;
	_ListNode<T>* _prev;
	T _data;
	_ListNode(const T& x):_next(NULL)
	                     ,_prev(NULL)
						 ,_data(x)
	{}

	_ListNode()
	{}
};
//T T& T*
template<class T, class Ref,class Ptr>
struct _Listiterator
{
	typedef _Listiterator<T,Ref,Ptr> Self;
	typedef T ValueType;
	typedef Ref Reference;
	typedef  Ptr Pointer;
	
	_ListNode<T>* _node;
	 _Listiterator(_ListNode<T>* x ):_node(x)
	 {}

	  _Listiterator()
	  {}

	  bool operator==(const Self& s)
	  {
	   return _node==s._node ;
	  }

	  bool operator!=(const Self& s)
	  {
	   return _node!=s._node ;
	  }

	  Reference operator*()
	  {
	   return _node->_data;
	  }
	  //
	  Pointer operator->()
	  {
	   return &(_node->_data);
	  }

      Self operator++(int)
	  {
	    Self tmp(_node);
		_node=_node->_next ;
		return tmp;

	  }

	  Self operator++()
	  {
		  _node=_node->_next ;
	   return _node;
	  }

	  Self operator--()
	  {
		 _node=_node->_prev;
		 return _node;
	  }

	  Self operator--(int)
	  {
	   Self tmp(_node);
	   _node=_node->_prev;
	   return tmp;
	  }

};

//设计为双向循环链表
template<class T>
class List
{
public:
	typedef _ListNode<T> ListNode;
	typedef _Listiterator<T,T&,T*>Iterator;

	List()
	{
	   _head=new ListNode;
	   _head->_next=_head;
	   _head->_prev=_head;
	}

	void PushBack(const T& x)
	{
	ListNode* tmp=new ListNode(x);
	ListNode* tail=_head->_prev;
	
	tail->_next=tmp;
	tmp->_prev=tail;

	_head->_prev=tmp;
	tmp->_next=_head;
	}
	void PopBack()
	{
	erase(--End());
	}
	void Insert(Iterator pos,const T& x)
	{
	ListNode* cur=pos._node ;
	ListNode* tmp=new ListNode(x);
	Node* prev=cur->_prev;
	prev->_next=tmp;
	tmp->_next=cur;

	cur->_prev=tmp;
	tmp->_prev=prev;
	}

	Iterator Erase(Iterator pos)
	{
	assert(pos!=End());

	ListNode* prev=pos._node->_prev;
	ListNode* next=pos._node->_next;
	prev->_next=next;
	next->_prev=prev;

	delete pos._node;
	return Iterator(next);
	}

	Iterator Begin()
	{
	return Iterator(_head->_next);
	}
	Iterator End()
	{
	return Iterator(_head);
	}

protected:
	ListNode* _head;
};

void TestList()
{
	List<int> l;
	l.PushBack (1);
	l.PushBack (2);
	l.PushBack (3);
	l.PushBack (4);

	List<int>::Iterator it=l.Begin ();
	while(it!=l.End ())
	{
		if(*it%2==0)
		{
			it=l.Erase (it);
		}
		else
		{
		cout<<*it<<" ";
			++it;
		}
	}

}
void Test1()
{
	vector<int> v1;
	v1.push_back (3);
	v1.push_back (1);
	v1.push_back (2);
	v1.push_back (6);
	v1.push_back (4);

	//迭代器遍历顺序表
	//STL的排序算法
	vector<int> ::iterator it=v1.begin ();
	sort(v1.begin (),v1.end ());
	for(;it!=v1.end ();++it)
	{
		cout<<*it<<" ";
	}
	cout<<endl;
}

void Test2()
{
	list<string> s1;
	s1.push_back ("aaa");
	s1.push_back ("bbb");
	s1.push_back ("ccc");
	s1.push_back ("ddd");

	//迭代器遍历链表
	list<string>::iterator it=s1.begin();
	for(;it!=s1.end ();++it)
	{
	
	cout<<*it<<" ";
	}
	cout<<endl;

	
}

void Test3()
{
	list<string> s1;
	s1.push_back ("aaa");
	s1.push_back ("bbb");
	s1.push_back ("ccc");
	s1.push_back ("ddd");
	//STL的替换算法
	//void replace ( ForwardIterator first, ForwardIterator last,const T& old_value, const T& new_value );
	replace (s1.begin (),s1.end (),"ddd","zzz");
	list<string>::iterator  it=s1.begin ();
	for(;it!=s1.end ();++it)
	{
	cout<<*it<<" ";
	}
	cout<<endl;
	// STL的find 算法查找迭代器区间的数据，并返回找到节点的迭代器
	it=find(s1.begin (),s1.end (),"zzz");
	if(it!=s1.end())
	{
	cout<<"success"<<*it<<endl;
	*it="vvv";
	}

	else if(it==s1.end ())
	{
	cout<<"failed"<<endl;
	}
}

//迭代器失效问题

void Pintvector(vector<int>& v)
{
  vector<int>::iterator  it=v.begin ();
  for(;it!=v.end ();++it)
  {
    cout<<*it<<" ";

  }
  cout<<endl;
}

void Test4()
{
	vector<int> v1;
	v1.push_back (1);
	v1.push_back (2);
	v1.push_back (3);
	v1.push_back (4);
	v1.push_back (5);
	v1.push_back (6);
	v1.push_back (7);
	v1.push_back (8);
	v1.push_back (9);
	v1.push_back (10);
	Pintvector(v1);
	vector<int>::iterator it=v1.begin ();
	while(it!=v1.end ())
	{
		 if(*it%2==0)
		 {
		   it=v1.erase (it);  
		 }
		 else
		 {
			it++;
		 }
	}
	Pintvector(v1);
}


