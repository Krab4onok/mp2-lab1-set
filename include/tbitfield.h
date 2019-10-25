// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.h - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#ifndef __BITFIELD_H__
#define __BITFIELD_H__

#include <iostream>

using namespace std;

typedef unsigned int TELEM;

class TBitField
{
private:
	int  BitLen; // длина битового поля - макс. к-во битов
	TELEM* pMem; // память для представления битового поля
	int  MemLen; // к-во эл-тов Мем для представления бит.поля

	// методы реализации
	int   GetMemIndex(const int n) const { return n / 32; }; // индекс в pМем для бита n       (#О2)
	TELEM GetMemMask(const int n) const {
		int v;
		v = n % 32;
		TELEM tmp = 1;
		tmp = tmp << v;
		return tmp;
	}; // битовая маска для бита n       (#О3)
public:
	TBitField(int len = 15)
	{
		if(len<0)
		{
			throw 1;
		}
		else {
			BitLen = len;
			MemLen = ((len) / 8 * sizeof(TELEM)) + 1;
			pMem = new TELEM[MemLen];
			for (int i = 0; i < MemLen; i++)
			{
				pMem[i] = 0;
			}
		}

	};                //                                   (#О1)
	TBitField(const TBitField& a) {
		BitLen = a.BitLen;
		MemLen = a.MemLen;
		pMem = new TELEM[MemLen];
		for (int i = 0; i < MemLen; i++)
		{
			pMem[i] = a.pMem[i];
		}
	};    //                                   (#П1)
	~TBitField() {
		delete[] pMem;
	};                      //                                    (#С)

  // доступ к битам
	int GetLength(void) const { return BitLen; };      // получить длину (к-во битов)           (#О)
	void SetBit(const int n) 
	{
		if (n<0 || n>MemLen)
		{
			throw 1;
		}
		else {
			int i = GetMemIndex(n);
			TELEM mask = GetMemMask(n);
			pMem[i] = pMem[i] | mask;
		}
	};       // установить бит                       (#О4)
	void ClrBit(const int n) {
		if (n<0 || n>MemLen)
		{
			throw 1;
		}
		else {
			int i = GetMemIndex(n);
			TELEM mask = GetMemMask(n);
			mask = ~mask;
			pMem[i] &= mask;
		}
	};       // очистить бит                         (#П2)
	TELEM  GetBit(const int n) const
	{
		if (n<0 || n>MemLen)
		{
			throw 1;
		}
		else {
			int i = GetMemIndex(n);
			TELEM mask = GetMemMask(n);
			return pMem[i] & mask;
		}
	}; // получить значение бита               (#Л1)

  // битовые операции
	bool operator==(const TBitField& a) const {
		if (BitLen != a.BitLen)
		{
			return false;
		}
		for (int i = 0; i < MemLen - 1; i++)
		{
			if (pMem[i] != a.pMem[i])
			{
				return false;
			}
		}
		for (int i = (MemLen - 1) * 32; i < BitLen; i++)
		{
			if (GetBit(i) != a.GetBit(i))
			{
				return false;
			}
			return true;
		}
	}; // сравнение                 (#О5)
	bool operator!=(const TBitField& a) const {
		if (BitLen != a.BitLen)
		{
			return true;
		}
		for (int i = 0; i < MemLen - 1; i++)
		{
			if (pMem[i] != a.pMem[i])
			{
				return true;
			}
		}
		for (int i = (MemLen - 1) * 32; i < BitLen; i++)
		{
			if( GetBit(i) != a.GetBit(i))
			{
				return true;
			}
			return false;
		}
	}; // сравнение
	TBitField& operator=(const TBitField& a)
	{
		BitLen = a.BitLen;
		MemLen = a.MemLen;
		pMem = new TELEM[MemLen];
		for (int i = 0; i < MemLen; i++)
		{
			pMem[i] = a.pMem[i];
		}
		return *this;
	}; // присваивание              (#П3)
	TBitField  operator|(const TBitField& b) {
		int maxBitlen = b.BitLen;
		if (BitLen > b.BitLen)
		{
			maxBitlen = BitLen;
		}
		TBitField temp(maxBitlen);
		if (BitLen < b.BitLen)
		{
			for (int i = 0; i < MemLen - 1; i++)
			{
				temp.pMem[i] = pMem[i];
			}
			for (int i = (MemLen - 1) * 32; i < BitLen; i++)
			{
				if (GetBit(i))temp.SetBit(i);
			}
			for (int i = 0; i < temp.MemLen; i++)
			{
				temp.pMem[i] = temp.pMem[i] | b.pMem[i];
			}
		}
		else
		{
			for (int i = 0; i < b.MemLen - 1; i++)
			{
				temp.pMem[i] = b.pMem[i];
			}
			for (int i = (b.MemLen - 1) * 32; i < b.BitLen; i++)
			{
				if (b.GetBit(i))temp.SetBit(i);
			}
			for (int i = 0; i < temp.MemLen; i++)
			{
				temp.pMem[i] = temp.pMem[i] | b.pMem[i];
			}
		}
		return temp;
	}; // операция "или"            (#О6)
	TBitField  operator&(const TBitField& b) {
		int maxBitlen = b.BitLen;
		if (BitLen > b.BitLen)
		{
			maxBitlen = BitLen;
		}
		TBitField temp(maxBitlen);
		if (BitLen < b.BitLen)
		{
			for (int i = 0; i < MemLen - 1; i++)
			{
				temp.pMem[i] = pMem[i];
			}
			for (int i = (MemLen - 1) * 32; i < BitLen; i++)
			{
				if (GetBit(i))temp.SetBit(i);
			}
			for (int i = 0; i < temp.MemLen; i++)
			{
				temp.pMem[i] = temp.pMem[i] & b.pMem[i];
			}
		}
		else
		{
			for (int i = 0; i < b.MemLen - 1; i++)
			{
				temp.pMem[i] = b.pMem[i];
			}
			for (int i = (b.MemLen - 1) * 32; i < b.BitLen; i++)
			{
				if (b.GetBit(i))temp.SetBit(i);
			}
			for (int i = 0; i < temp.MemLen; i++)
			{
				temp.pMem[i] = temp.pMem[i] & b.pMem[i];
			}
		}
		return temp;

	}; // операция "и"              (#Л2)
	TBitField  operator~(void) {
		TBitField b(BitLen);
		for (int i = 0; i < MemLen; i++)
		{
			b.pMem[i] = ~pMem[i];
		}
		return b;
	};                // отрицание                  (#С)

	friend istream& operator>>(istream& is, TBitField& a) {
		char c;
		int i = 0;
		do {
			is >> c;
			if (c == '1')
			{
				a.SetBit(i);
				i++;
			}
			if (c == '0')
			{
				a.ClrBit(i);
				i++;
			}
		} while ((c == '0') || (c == '1'));
		return is; };      //      (#О7)
	friend ostream& operator<<(ostream& ostr, const TBitField& a) { 
		for (int i = 0; i < a.BitLen; i++)
		{
			if (a.GetBit(i) != 0)
			{
				ostr << 1;
			}
			else
			{
				ostr << 0;
			}
		}
		
		return ostr; }; //      (#П4)
};
// Структура хранения битового поля
//   бит.поле - набор битов с номерами от 0 до BitLen
//   массив pМем рассматривается как последовательность MemLen элементов
//   биты в эл-тах pМем нумеруются справа налево (от младших к старшим)
// О8 Л2 П4 С2

#endif
