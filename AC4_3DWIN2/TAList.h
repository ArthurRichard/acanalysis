#pragma once
#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif
#define eachlist(list,num) for(int num=0;num<list.Count;num++)
void memcmp_ta(void * dst,const void * src , unsigned int size);
template<class ListItem>
class CTAList
{
	public:
	ListItem *ListData1;
public:
	CTAList(void)
	: ItemSize(0)
	, Count(0)
	, MaxCount(0)
	, ListData1(0)
	{
		ItemSize=sizeof(ListItem);
	}
	~CTAList(void)
	{
		Clear();
	}
	int ItemSize;
	int Count;
	int MaxCount;
	void Clear(void)
	{
		Count=0;
		MaxCount=0;
		if(ListData1) delete [] ListData1; ListData1=0;
	}
	void push_back(ListItem & Item)
	{
		Count=Count+1;
		if(Count>MaxCount) ChangeMaxCount(Count);
		ListData1[Count-1]=Item;
	}
	void push_back(ListItem & Item,int ChangeMax)
	{
		Count=Count+1;
		if(Count>MaxCount) ChangeMaxCount(Count+ChangeMax);
		ListData1[Count-1]=Item;
	}
	
	void ChangeMaxCount(int NewMaxCount)
	{
		if(NewMaxCount<=MaxCount) return;
		ListItem *ListDataSwap;

		ListDataSwap=new ListItem[NewMaxCount];
		if(ListData1)
		{
			memcmp_ta(ListDataSwap,ListData1,ItemSize*MaxCount);
			//memcpy_s(
			//	ListDataSwap,
			//	ItemSize*NewMaxCount,
			//	ListData1,
			//	ItemSize*MaxCount
			//	);
			delete [] ListData1;
		}
		ListData1=ListDataSwap;

		MaxCount=NewMaxCount;
	}
	ListItem & operator[](int Pos)
	{
		return ListData1[Pos];
	}
	void operator=(CTAList & DataIn)
	{
		Clear();
		ItemSize=DataIn.ItemSize;
		Count=DataIn.Count;
		MaxCount=DataIn.MaxCount;
		ListData1=new ListItem[MaxCount];
		memcpy_s(
				ListData1,
				ItemSize*MaxCount,
				DataIn.ListData1,
				ItemSize*MaxCount
				);
	}
	ListItem & Back()
	{
		return ListData1[Count-1];
	}
	void DelBack()
	{
		Count=max(0,Count-1);
	}
};