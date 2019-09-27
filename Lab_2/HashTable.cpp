#include "HashTable.h"

size_t HashTable::getIndex(const Key& k) const
{
	return std::hash<Key>()(k) % table->size();
}

HashTable::HashTable()
{
	table = new HTVector(TABLE_SIZE);
	numb_elem = 0;
}

void HashTable::copyHTVector(HashTable::HTVector* first, const HashTable& second)
{
	HTList::iterator j;
	HTVector* secondVector = second.table;

	for (int i = 0; i < secondVector->size(); ++i){
		if (!(*secondVector)[i]){
			continue;
		}
		try{
			(*first)[i] = new HTList;
		}
		catch (std::bad_alloc&){
			memClear(first);
			throw;
		}
		
		for (j = (*secondVector)[i]->begin(); j != (*secondVector)[i]->end(); ++j){
			(*first)[i]->push_back(*j);
		}
	}
}

HashTable::HashTable(const HashTable& second)
{
	table = new HTVector(second.tsize());
	HashTable::copyHTVector(table, second);
	numb_elem = second.numb_elem;
}

HashTable::HashTable(HashTable&& second)
	:TABLE_SIZE(second.TABLE_SIZE), numb_elem(second.numb_elem), table(second.table)
{
	second.TABLE_SIZE = 0;
	second.numb_elem = 0;
	second.table = nullptr;
}


HashTable::~HashTable()
{
	memClear(table);
}

bool HashTable::empty() const
{
	return !numb_elem;
}

size_t HashTable::tsize() const
{
	return table->size();
}


void HashTable::load_factor()
{
	double currLoad = (table->size()) / numb_elem;

	if (currLoad >= maxLoad){
		resize();
	}

}

size_t nextPrime(size_t n)
{
	for (auto i = 2; i < sqrt(n); ++i){
		if (n % i == 0){
			return nextPrime(n + 1);
		}
	}

	return  n;
}

void HashTable::memClear(HashTable::HTVector* tmpTable)
{
	if (tmpTable->empty()){
		return;
	}

	for (int i = 0; i < tmpTable->size(); ++i){
		delete (*tmpTable)[i];
	}
	
	delete tmpTable;
}

void HashTable::resize()
{
	size_t OLDSIZE = table->size();
	size_t CURRSIZE = 2 * OLDSIZE;
	HTVector* oldTable = table;
	HTVector* newTable = 0;

	size_t i;
	size_t newIndex;

	HTList::iterator j;

	//find next prime that at least x2 from previous
	TABLE_SIZE = nextPrime(CURRSIZE);

	//create new table
	try{
		newTable = new HTVector(TABLE_SIZE);
	}
	catch (std::bad_alloc&){
		TABLE_SIZE = OLDSIZE;
		throw;
	}

	//move non-empty cells from old table to new
	for (i = 0; i < OLDSIZE; ++i){
		if (!((*oldTable)[i])){
			continue;
		}

		for (j = (*oldTable)[i]->begin(); j != (*oldTable)[i]->end(); ++j){
			newIndex = getIndex(j->first);

			try {
				(*newTable)[newIndex] = new HTList;
				(*newTable)[newIndex]->push_back(*j);
			}
			catch (std::bad_alloc&){
				memClear(newTable);
				TABLE_SIZE = OLDSIZE;
				throw;
			}	
		}
	}
	
	memClear(oldTable);

	table = newTable;
}

HashTable& HashTable::operator=(const HashTable& newTable)
{
	if (this == &newTable)
		return *this;

	HTVector* ourTable;

	ourTable = new HTVector(newTable.TABLE_SIZE);
	HashTable::copyHTVector(ourTable, newTable);

	memClear(table);

	this->numb_elem = newTable.numb_elem;
	this->TABLE_SIZE = newTable.TABLE_SIZE;
	this->table = ourTable;

	return *this;
}

Value & HashTable::operator[](const Key & k)
{
	Value v = { 0, 0 };
	HTList::iterator i;
	size_t index = getIndex(k);

	if (!(*table)[index]){
		
		(*table)[index] = new HTList;
		(*table)[index]->push_back(std::make_pair(k, v));
		++numb_elem;
	}

	i = search(index, table, k);

	if(i != (*table)[index]->end()){
		return i->second;
	}
	else{
		(*table)[index]->push_back(std::make_pair(k, v));
		++numb_elem;
	}
	return (*table)[index]->back().second;
}


void HashTable::swap(HashTable& second)
{
	std::swap(table, second.table);
	std::swap(numb_elem, second.numb_elem);
	std::swap(TABLE_SIZE, second.TABLE_SIZE);
}


bool HashTable::insert(const Key& k, const Value& v)
{
	if (numb_elem / table->size() >= maxLoad){
		resize();
	}

	size_t index = getIndex(k);

	if (!(*table)[index]){
		try{
			(*table)[index] = new HTList;
		}
		catch (std::bad_alloc&){
			throw;
		}
		HTPair element = std::make_pair(k, v);
		(*table)[index]->push_back(element);
		++numb_elem;

		return true;
	}

	//execute collisions
	if (!contains(k)){
		HTPair element = std::make_pair(k, v);
		(*table)[index]->push_back(element);
		++numb_elem;

		return true;
	}
	
	return false;
		
}

bool HashTable::erase(const Key& k)
{
	HTList::iterator i;
	size_t index = getIndex(k);

	if (!(*table)[index]){
		return false;
	}

	i = search(index, table, k);
	if (i != (*table)[index]->end()){
		i = (*table)[index]->erase(i);
		--numb_elem;
		return true;
	}
	
	return false;

}


bool HashTable::contains(const Key& k)
{
	size_t index = getIndex(k);
	
	if (!(*table)[index]){
		return false;
	}

	return (search(index, table, k) != (*table)[index]->end());
}


HashTable::HTList::iterator HashTable::search(size_t index, HTVector* table, const Key& k) const
{
	HTList::iterator i;
	HTList::iterator notFound = (*table)[index]->end();

	for (i = (*table)[index]->begin(); i != (*table)[index]->end(); ++i){
		if (i->first == k){
			return i;
		}
	}

	return notFound;
}

Value& HashTable::at(const Key& k)
{
	return at_implementation(k);
}

const Value& HashTable::at(const Key& k) const
{
	return at_implementation(k);
}

Value& HashTable::at_implementation(const Key& k) const
{
	HTList::iterator i;

	size_t index = getIndex(k);

	if (!(*table)[index]){
		throw(std::out_of_range(k));
	}

	i = search(index, table, k);

	if (i != (*table)[index]->end()){
		return i->second;
	}

	throw(std::out_of_range(k));
}

bool operator==(const HashTable & a, const HashTable & b)
{
	if (&a == &b){
		return true;
	}

	if (a.table->size() != b.table->size()){
		return false;
	}

	if (a.numb_elem != b.numb_elem){
		return false;
	}

	HashTable::HTList::iterator i1, i2;
	HashTable::HTVector* table1 = a.table;
	HashTable::HTVector* table2 = b.table;

	//проходим по всему вектору
	for (size_t j1 = 0, j2 = 0; j1 < table1->size() && j2 < table2->size(); ++j1, ++j2){
		//both are nullptr - go ahead
		if ( ((*table1)[j1] == nullptr) && ((*table2)[j2] == nullptr))
			continue;

		//lists have different size
		if (((*table1)[j1])->size() != ((*table2)[j2])->size())
			return false;

		i1 = (*table1)[j1]->begin();
		i2 = (*table2)[j2]->begin();
		for (i1 , i2; i1 != (*table1)[j1]->end() && i2 != (*table2)[j2]->end(); ++i1, ++i2){
			if (i1->first != i2->first){
				return false;
			}

			if (i1->second.age != i2->second.age|| i1->second.weight != i2->second.weight){
				return false;
			}
		}

	}
	return true;
}


bool operator!=(const HashTable &a, const HashTable &b)
{
	return !(a == b);
}


void HashTable::clear()
{
	for (size_t i = 0; i < table->size(); ++i){
		if ((*table)[i]){
			delete ((*table)[i]);
		}
	}
	(*table).clear();
	//Set tabble size to default value
	table->resize(7);
	numb_elem = 0;
}
