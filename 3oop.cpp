#include <iostream>
#include <ctime>
using namespace std;

class MyBase
{
public:
	MyBase()
	{
		printf("MyBase()\n");
	}
	virtual void showName()
	{
		printf("MyBase\n");
	}
	virtual~MyBase()
	{
		printf("~MyBase()\n");
	}
};

class Class1 : public MyBase
{
private:
	int x;
	int y;
public:
	Class1()
	{
		printf("Class1()\n");
		x = 0;
		y = 0;
	}

	Class1(int x, int y)
	{
		printf("Class1(int x, int y)\n");
		this->x = x;
		this->y = y;
	}

	Class1(const Class1& obj)
	{
		printf("Class1(const Class1& obj)\n");
		x = obj.x;
		y = obj.y;
	}

	void showName()
	{
		printf("Class1\n");
	}
	~Class1()
	{
		printf("~Class1()\n");
	}
};

class Class2 : public MyBase {
private:
	int x;
	int y;
	int color;
public:
	Class2()
	{
		printf("Class2()\n");
		x = 0;
		y = 0;
		color = 0;
	}

	Class2(int x, int y, int color)
	{
		printf("Class2(int x, int y, int color)\n");
		this->x = x;
		this->y = y;
		this->color = color;
	}

	Class2(const Class2& obj)
	{
		printf("Class2(const Class2& obj)\n");
		x = obj.x;
		y = obj.y;
		color = obj.color;
	}
	~Class2()
	{
		printf("~Class2()\n");
	}

	void showName()
	{
		printf("Class2\n");
	}
};

class MyStorage
{
private:
	int size;
	MyBase** storage;
public:
	MyStorage(int size)
	{
		printf("MyStorage(int size)\n");
		this->size = size;
		storage = new MyBase * [size];
		for (int i=0; i<size; i++)
			storage[i] = nullptr;
	}
	MyStorage(MyStorage& storage_copy)
	{
		printf("MyStorage(MyStorage& storage_copy)\n");
		size = storage_copy.size;
		storage = new MyBase * [size];
		for (int i = 0; i < size; i++)
			*storage[i] = storage_copy.GetObject(i);
	}
	~MyStorage()
	{
		printf("~MyStorage()\n");
		for (int i = 0; i < size; i++)
			delete storage[i];
		delete storage;
	}
	int SizeStorage()
	{
		return size;
	}

	void GetCount()
	{
		int count = 0;
		for (int i = 0; i < size; i++)
			if (storage[i] != nullptr)
				count = count + 1;
		printf("Количество элементов: %d\nРазмер хранилища: %d\n", count, size);
	}

	void SetObject(int i, MyBase* object)
	{
		printf("SetObject(int i, MyBase* object) - i = %d\n", i);
		storage[i] = object;
	}

	void AddObject(MyBase* object)
	{
		size = size + 1;
		printf("AddObject(MyBase* object) - size = %d\n", size);
		MyBase** storage_copy = new MyBase * [size];
		for (int i = 0; i < size - 1; i++)
			storage_copy[i] = storage[i];
		storage_copy[size - 1] = object;
		for (int j = 0; j < size - 1; j++)
			storage[j] = nullptr;
		delete storage;
		storage = storage_copy;
	}

	MyBase& GetObject(int i)
	{
		return *storage[i];
	}

	void DeleteObject(int i)
	{
		printf("DeleteObject(int i) - i = %d\n", i);
		storage[i] = nullptr;
	}

	void ShowObjectMethod(int i)
	{
		printf("ShowObjectMethod(int i) - i = %d\n", i);
		if (storage[i] != nullptr)
			storage[i]->showName();
	}

	void ReplaceObject(int i, MyBase* object)
	{
		if (storage[i] == nullptr)
			storage[i] = object;
		else
		{
			delete storage[i];
			storage[i] = object;
		}
	}
	void ShowMyStorage()
	{
		for (int i = 0; i < size; i++)
			if (storage[i] != nullptr)
				storage[i]->showName();
			else printf("nullptr\n");
	}
};

int main()
{
	srand(time(NULL));
	setlocale(LC_ALL, "RUS");
	MyStorage storage(10);

	for (int i = 0; i < storage.SizeStorage(); i++)
	{
		int r = rand() % 2;
		if (r)
			storage.SetObject(i, new Class1);
		else storage.SetObject(i, new Class2);
	}
	cout << endl << endl;
	for (int i = 0; i < storage.SizeStorage(); i++)
		storage.GetObject(i).showName();
	unsigned int StartTime = clock();
	printf("\n\n");
	for (int i = 0; i < 100; i++)
	{
		printf("%d\n", i);
		int action = rand() % 4;
		int rand_index = rand() % storage.SizeStorage();
		int c = rand() % 2;
		switch (action)
		{
		case 0:
			if (c)
			{
				storage.AddObject(new Class1);
				printf("AddObject: new Class1\n");
			}
			else
			{
				storage.AddObject(new Class2);
				printf("AddObject: new Class2\n");
			}
			break;
		case 1:
			storage.DeleteObject(rand_index);
			break;
		case 2:
			storage.ShowObjectMethod(rand_index);
			break;
		case 3:
			if (c)
			{
				storage.ReplaceObject(rand_index, new Class1);
				printf("ReplaceObject: new Class1\n");
			}
			else
			{
				storage.ReplaceObject(rand_index, new Class2);
				printf("ReplaceObject: new Class2\n");
			}
			break;
		default:
			storage.GetCount();
			break;
		}
		cout << endl;
	}
	unsigned int EndTime = clock();
	printf("\nВремя работы = %d\n", EndTime - StartTime);
	storage.ShowMyStorage();
	storage.GetCount();
}

