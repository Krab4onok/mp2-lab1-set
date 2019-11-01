// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.h - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество

#ifndef __SET_H__
#define __SET_H__

#include "tbitfield.h"

class TSet
{
private:
	int MaxPower;       // максимальная мощность множества
	TBitField BitField; // битовое поле для хранения характеристического вектора
public:
	TSet(int mp) :BitField(mp)
	{
		MaxPower = mp;
	};
	TSet(const TSet& s) :BitField(s.BitField), MaxPower(s.MaxPower) {};       // конструктор копирования
	TSet(const TBitField &s) :BitField(s), MaxPower(s.GetLength()) {}; // конструктор преобразования типа
	operator TBitField()
	{
		return BitField;
	};      // преобразование типа к битовому полю
	// доступ к битам
	int GetMaxPower(void) const
	{
		return MaxPower;
	};     // максимальная мощность множества
	void InsElem(const int &a)
	{
		if (a >= 0)
			BitField.SetBit(a);
		else
			throw 1;
	};       // включить элемент в множество
	void DelElem(const int &a)
	{
		if (a >= 0)
			BitField.ClrBit(a);
		else
			throw 1;
	};       // удалить элемент из множества
	int IsMember(const int &a)const
	{
		return BitField.GetBit(a);
	}; // проверить наличие элемента в множестве
	// теоретико-множественные операции
	bool operator== (const TSet &s) const
	{
		return BitField == s.BitField;
	}; // сравнение
	bool operator!= (const TSet &s) const
	{
		return BitField != s.BitField;
	}; // сравнение
	TSet& operator=(const TSet &s)
	{
		MaxPower = s.MaxPower;
		BitField = s.BitField;
		return *this;
	};  // присваивание
	TSet operator+ (const int &a)
	{
		if (a >= 0 && a <= MaxPower) {
			TSet res(*this);
			res.InsElem(a);
			return res;
		}
		else
			throw 1;
	}; // объединение с элементом
									 // элемент должен быть из того же универса
	TSet operator- (const int &a) // разность с элементом
	{
		if (a >= 0 && a<= MaxPower) {
			TSet res(*this);
			res.DelElem(a);
			return res;
		}
		else
			throw 1;
	};                        // элемент должен быть из того же универса
	TSet operator+ (const TSet& a)
	{
		TBitField temp;
		temp = BitField | a.BitField;
		TSet res(temp);
		return res;

	};  // объединение
	TSet operator* (const TSet &s)
	{
		TSet res(*this);
		res.BitField&s.BitField;
		return res;
	};  // пересечение
	TSet operator~ ()
	{
		return ~BitField;
	};           // дополнение

	friend istream &operator>>(istream &is, TSet &a)
	{
		int i;
		is >> i;
		while (i >= 0 || i < a.MaxPower)
		{
			a.InsElem(i);
			is >> i;
		}
		return is;
	};
	friend ostream &operator<<(ostream &os, const TSet &a)
	{
		for (int i = 0; i < a.MaxPower; i++)
		{
			if(a.BitField.GetBit(i))
			{
				os << i << " ";
			}
		}
		return os;
	};
};
#endif
