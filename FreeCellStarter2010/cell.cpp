#include "stdafx.h" // This must be included first
#include <afxwin.h>
#include "cell.h"
#include "WindowsCards.h"

Cell::Cell(int l, int t, int r, int b)
{
	mLeft = l;
	mTop = t;
	mRight = r;
	mBottom = b;

	mSelected = false;
}
void Cell::Draw(CPaintDC &dc)
{
	dc.Rectangle(mLeft , mTop, mRight, mBottom);
	if (mCards.size() > 0)
	{
		//given with hold cells
		DrawCard(dc, mLeft + cellToCardMargin, mTop + cellToCardMargin, mCards.back(), mSelected);
		//end cells
	}

}
bool Cell::CanRemoveCard()
{
	return false;
}
bool Cell::CanAcceptCard(int index)
{
	return false;
}
void Cell::AddCard(int index)
{
	mCards.push_back(index);
}
int Cell::RemoveCard()
{
	return -1;
}
bool Cell::IsPointWithinCell(CPoint point)
{
	return false;
}
int Cell::GetCardOnTop() // or -1 if none there.
{
	return -1;
}
void Cell::SetSelected(bool selected)
{

}


TempCell::TempCell(int l, int t, int r, int b) : Cell(l,t,r,b)
{

}


EndCell::EndCell(int l, int t, int r, int b) : Cell(l, t, r, b)
{
}
bool EndCell::CanRemoveCard()
{
	return false;
}
bool EndCell::CanAcceptCard(int index)
{
	return false;
}


StartCell::StartCell(int l, int t, int r, int b) : Cell(l, t, r, b)
{
}

void StartCell::Draw(CPaintDC & dc)
{
}

bool StartCell::CanAcceptCard(int index)
{
	return false;
}
