
#include <iostream>
#include<fstream>

using namespace std;

template <class T>
T get()
{
	T* data = new T;
	cout << "Enter the data\n";
	cin >> *data;
	return *data;
}

char* getStr(int n)
{
	char* tmp = new char[n];
	cin >> tmp;
	return tmp;
}

template <class TKey, class TValue>
class Collection
{
private:
	struct CollectionElement
	{
		TKey key;
		TValue value;
	};
	CollectionElement **arr;
	int numOfElem;
	int length;

	void arrayExpansion()
	{
		int tmpLength = length * 2;
		CollectionElement **tmpArray = new CollectionElement*[tmpLength];
		for (int i = 0; i < length; i++)
		{
			tmpArray[i] = arr[i];
		}
		arr = tmpArray;
		length = tmpLength;
		for (int i = 0; i < tmpLength; i++)
		{
			delete tmpArray[i];
		}
	}

	void setKey(TKey newKey, int idx)
	{
		arr[idx]->key = newKey;
	}

	void setValue(TValue& newValue, int idx)
	{
		arr[idx]->value = newValue;
	}

public:
	Collection()
	{
		length = 8;
		numOfElem = 0;
		arr = new CollectionElement*[length];
		for (int i = 0; i < length; i++)
		{
			arr[i] = new CollectionElement;
		}
	}

	TKey getKey(int idx)
	{
		return arr[idx]->key;
	}

	TValue getValue(int idx)
	{
		return arr[idx]->value;
	}

	int getNumOfElem()
	{
		return numOfElem;
	}

	friend ostream& operator << (ostream& out, const Collection& inst)
	{
		for (int i = 0; i < inst.getNumOfElem(); i++)
		{
			out << inst.getKey(i) << ',' << inst.getValue(i) << '\n';
		}
		return out;
	}

	friend istream& operator >> (istream& in, Collection& inst)
	{
		while (in.peek() != '\n')
		{
			TKey key;
			TValue* value = new TValue;
			in >> key;
			in >> *value;
			inst.add(key, *value);																		
		}
			return in;
	}

	bool add(TKey newKey, TValue& newValue)
	{
		if (searchByKey(newKey) <= 0)
		{
			if (numOfElem >= length)
			{
				arrayExpansion();
			}

			setKey(newKey, getNumOfElem());
			setValue(newValue, getNumOfElem());
			numOfElem++;
			return true;
		}
		return false;
	}

	bool del(TKey key)
	{
		if (numOfElem > 0)
		{
			int idx = searchByKey(key);
			if (idx != -1)
			{
				for (int i = idx; i < getNumOfElem(); i++)
				{
					arr[i] = arr[i + 1];
				}
				numOfElem--;
				return true;
			}
			else
				return false;
		}
		return false;
	}

	int searchByKey(TKey key)
	{
		int i = 0;
		for (i; i < numOfElem; i++)
		{
			if (arr[i]->key == key)
				return i;
		}
		if(numOfElem == 0)
			return 0;
		return -1;
	}
};

class Bus
{
char* nameOfDriver;
int routeNum;
public:
	Bus()
	{
		routeNum = 0;
		nameOfDriver = new char[128];
	}

	Bus(char* name, int number)
	{
		routeNum = number;
		nameOfDriver = new char[128];
		nameOfDriver = name;
	}

	~Bus()
	{
		delete[] nameOfDriver;
	}

	char* toString()
	{
		char* buf = new char[512];
		char* num = new char[64];
		_itoa_s(getRouteNum(), num, 64, 10);
		buf[0] = '"';

		int i = 1;
		for (int k = 0; k < strlen(nameOfDriver); i++, k++)
		{
			buf[i] = nameOfDriver[k];
		}

		buf[i] = ',';
		i++;

		for (int j = 0; j < strlen(num); j++, i++)
		{
			buf[i] = num[j];
		}
		buf[i] = '"';
		i++;
		buf[i] = '\0';
		i++;
		return buf;
	}

	int getRouteNum()
	{
		return routeNum;
	}

	char* getNameOfDriver()
	{
		return nameOfDriver;
	}

	friend Bus &operator >> (istream& in, Bus &inst)
	{
		int num;
		char* name = new char[64];
		in >> name >> num;

		inst.nameOfDriver = name;
		inst.routeNum = num;

		return inst;
	}
};

class BusPark
{
private:

	Collection <int, Bus> onRoad;
	Collection <int, Bus> inPark;

	char* toString(Collection<int, Bus> inst, char *buf)
	{
		int j = 0;
		for (int i = 0; i < inst.getNumOfElem(); i++)
		{
			char* keyBuf = new char[32];
			_itoa_s(inst.getKey(i), keyBuf, 32, 10);
			char* busBuf = new char[256];
			busBuf = inst.getValue(i).toString();

			int k = 0;
			while (keyBuf[k] != '\0')
			{
				buf[j] = keyBuf[k];
				k++; j++;
			}

			buf[j] = ',';
			j++;
			int l = 0;
			while (busBuf[l] != '\0')
			{
				buf[j] = busBuf[l];
				l++; j++;
			}
			buf[j] = '\n';
			j++;
		}
		buf[j-1] = '\0';
		j++;
		return buf;
	}

public:

	bool busOut(int key)
	{
		int res = this->inPark.searchByKey(key);
		if (res != -1)
		{
			Bus tempVal = inPark.getValue(res);
			inPark.del(key);
			onRoad.add(key, tempVal);
			return true;
		}
		return false;
	}

	bool busIn(int key)
	{
		int res = this->onRoad.searchByKey(key);
		if (res != -1)
		{
			Bus tempVal = onRoad.getValue(res);
			onRoad.del(key);
			inPark.add(key, tempVal);
			return true;
		}
		return false;
	}

	void add()
	{
		int key = get<int>();
		char* name = getStr(64);
		int num = get<int>();
		Bus* bus = new Bus(name, num);

		inPark.add(key, *bus);
	}

	void del(int key)
	{
		inPark.del(key);
	}

	void add(int key, Bus& bus)
	{
		inPark.add(key, bus);
	}

	friend istream& operator >> (istream& in, BusPark& inst)
	{
		in >> inst.inPark;
		return in;
	}

	friend ifstream& operator >> (ifstream& in, BusPark& inst)
	{
		while (!in.eof())													  
		{
			char* buf = new char[2048];
			in.getline(buf, 2048);
			int i = 0;
			char* keyBuf = new char[32];
			char* nameBuf = new char[256];
			char* numBuf = new char[32];

				int j = 0;
				while (buf[i] != ',')
				{
					keyBuf[j] = buf[i];
					j++; i++;
				}
				keyBuf[j] = '\0'; 
				j++;
				i++;

				int k = 0;
				while (buf[i] != ',')
				{
					if (buf[i] != '"')
					{
						nameBuf[k] = buf[i];
						k++;
					}
					i++;
				}
				nameBuf[k] = '\0';
				k++;
				i++;

				int l = 0;
				while (buf[i] != '\0')
				{
					if (buf[i] != '"')
					{
						numBuf[l] = buf[i];
						l++;
					}
					i++;
				}
				numBuf[l] = '\0';
				l++;
				i++;

				Bus* bus = new Bus(nameBuf, atoi(numBuf));
				inst.add(atoi(keyBuf), *bus);
		}
			return in;
	}

	void fileOut()
	{
		ofstream file("inPark.csv");
		char* buf = new char[256 + 32];
		toString(inPark, buf);
		file << buf;
		file.close();
	}

	void fileOut(char* filename)
	{
		ofstream file(filename);
		char* buf = new char[256 + 32];
		toString(inPark, buf);
		file << buf;
		file.close();
	}

	void fileIn()
	{
		ifstream file("inPark.csv");
		file >> *this;
	}

	void fileIn(char* filename)
	{
		ifstream file(filename);
		file >> *this;
	}
};

void main()
{
	BusPark p;
	p.fileIn();
	p.fileOut();
};

//1 Bill 35 2 Bob 47 3 Carl 15