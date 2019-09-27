#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <list>

struct Value {
	unsigned age;
	unsigned weight;
};



class HashTable
{
	using Key = std::string;

	using HTPair = std::pair< Key, Value >;
	using HTList = std::list< HTPair >;
	using HTVector = std::vector< HTList *>;

public:

	HashTable();

	HashTable(const HashTable& second);//copy

	HashTable(HashTable&& second);//move

	~HashTable();

	HashTable& operator=(const HashTable& b);

	void clear();

	bool erase(const Key& k);

	bool insert(const Key& k, const Value& v);

	bool contains(const Key& k);

	Value& at(const Key& k);
	
	const Value& at(const Key& k) const;
	
	//Возвращает значение по ключу, в случаем отсутвия
	//вставляет с умолчательным значением
	//Возвращается ссылка на вставленный элемент
	Value& operator[](const Key& k);

	bool empty() const;

	void swap(HashTable& second);

	friend bool operator ==(const HashTable & a, const HashTable & b);
	friend bool operator !=(const HashTable & a, const HashTable & b);

private:

	//Возвращает размер таблицы
	size_t tsize() const;

	//увеличение размера таблицы
	void resize();

	//функция получение индекса по ключу
	size_t getIndex(const Key& k) const;

	//степень загруженности таблицы
	void load_factor();

	//очистка памяти из-под занятых листов и вектора
	void memClear(HTVector* tmpTable);


	//Функция, проходящая по списку
	//Возвращается:
	//		итератор на очередной элемент списка
	HTList::iterator search(size_t index, HTVector* table, const Key& k) const;

	void copyHTVector(HTVector* first, const HashTable& second);

	Value& at_implementation(const Key& k) const;

	size_t TABLE_SIZE = 7;
	float maxLoad = 0.75;
	size_t numb_elem = 0;
	HTVector* table;

};