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
  TELEM *pMem; // память для представления битового поля
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
		BitLen = len;
		MemLen = ((len) / 32) + 1;
		pMem = new TELEM[MemLen];
		for (int i = 0; i < MemLen; i++) 
		{
			pMem[i] = 0;
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
	void SetBit(const int n) {};       // установить бит                       (#О4)
	void ClrBit(const int n) {};       // очистить бит                         (#П2)
	TELEM  GetBit(const int n) const 
	{
		return pMem[n / 32];
	}; // получить значение бита               (#Л1)

  // битовые операции
	int operator==(const TBitField& bf) const {}; // сравнение                 (#О5)
	int operator!=(const TBitField& bf) const {}; // сравнение
	TBitField& operator=(const TBitField& a)
	{
		BitLen = a.BitLen;
		MemLen = a.MemLen;
		pMem = new TELEM[MemLen];
		for (int i = 0; i < MemLen; i++)
		{
			pMem[i] = a.pMem[i];
		}

	}; // присваивание              (#П3)
	TBitField  operator|(const TBitField& bf) {}; // операция "или"            (#О6)
	TBitField  operator&(const TBitField& bf) {}; // операция "и"              (#Л2)
	TBitField  operator~(void) {};                // отрицание                  (#С)

  friend istream& operator>>(istream& istr, TBitField& bf) {};       //      (#О7)
  friend ostream& operator<<(ostream& ostr, const TBitField& bf) {}; //      (#П4)
};
// Структура хранения битового поля
//   бит.поле - набор битов с номерами от 0 до BitLen
//   массив pМем рассматривается как последовательность MemLen элементов
//   биты в эл-тах pМем нумеруются справа налево (от младших к старшим)
// О8 Л2 П4 С2

#endif
