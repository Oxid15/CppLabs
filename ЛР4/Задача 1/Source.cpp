#include <iostream>

using namespace std;

struct student
{
	char* first_name;
	char* last_name;
	char* patronymic_name;
	short group_num;
	short grade[5];
	float avg;
	bool otl;
};
struct linlist
{
	student curr_student;
	linlist* nextptr;
};

short short_enter(short* buf)
 {
	 cin >> *buf;
	 while (*buf < 0 || *buf > 32676)
	 {
		 cout << "Invalid input, try again:" << "\n";
		 cin >> *buf;
		 if (cin.fail())
		 {
			 cin.clear();
			 while (cin.get() != '\n');
		 }
	 }
	 return *buf;
	 delete buf;
 }
void add(linlist* &head)
{
	 for (int i = 0; i < 10; i++)
	 {
		 linlist* new_el = new linlist;
		 student* student_el = new student;
		 cout << "Enter last name" << "\n";
		 char* buf1 = new char[255];
		 cin >> buf1;
		 student_el->last_name = new char[strlen(buf1) + 1];
		 delete buf1;

		 cout << "Enter first name" << "\n";
		 char* buf2 = new char[255]; 
		 cin >> buf2;
		 student_el->first_name = new char[strlen(buf2) + 1];
		 delete buf2;

		 cout << "Enter patronymic name" << "\n";
		 char* buf3 = new char[255];
		 cin >> buf3;
		 student_el->patronymic_name = new char[strlen(buf3) + 1];
		 delete buf3;

		 cout << "Enter number of group" << "\n";
		 short* b = new short;
		 student_el->group_num = short_enter(b);
		 delete b;
		 float sum = 0;
		 cout << "Enter 5 grades" << "\n";
		 for (int j = 0; j < 5; j++)
		 {
			 short* c = new short;
			 student_el->grade[j] = short_enter(c);
			 if (*student_el->grade < 4)
			 {
				 student_el->otl = false;
			 }
			 delete c;
			 sum = sum + student_el->grade[j];
		 }
		 student_el->avg = sum / 5;
		 //...//
		 new_el->curr_student = *student_el;
		 if (head == nullptr)
		 {
			 head = new_el;
			 new_el->nextptr = nullptr;
		 }
		 else
		 {
			 new_el->nextptr = head;
			 head = new_el;
		 }
		 //...//
		 short* k = new short;
		 cout << "Enter 0 if you want to stop writing, or any positive number if you don't" << "\n";
		 cin >> *k;
		 if (!(*k))
			 break;
		 else
			 cout << "Continue..." << "\n";
		 delete k;
	 }
}

void print(linlist* &head)
 {
	 linlist* ptr = new linlist;
	 ptr = head;
	 while (ptr)
	 {
		 cout << " Last name:" << ptr->curr_student.last_name << "\n";
		 cout << " First name:" << ptr->curr_student.first_name << "\n";
		 cout << "Patr. name:" << ptr->curr_student.patronymic_name << "\n";
		 cout << "Group number:" << ptr->curr_student.group_num << "\n";
		 cout << "grades:" << "\n";
		 for (int j = 0; j < 5; j++)
		 {
			 cout << ptr->curr_student.grade[j] << "\n";
		 }
		ptr = ptr->nextptr;
	 }
	 linlist* ptr3 = new linlist;
	 ptr3 = head;
	 while (ptr3)
	 {
		 if (ptr3->curr_student.otl)
		 {
			 cout << "Students with only 4 and 5 grades:" << "\n";
			 cout << ptr3->curr_student.last_name << "\n";
			 cout << ptr3->curr_student.first_name << "\n";
			 cout << ptr3->curr_student.group_num << "\n";
		 }
		 ptr3 = ptr3->nextptr;
	 }
 }

void listsort(linlist* &head) //Doesn't work correctly...
 {
	 linlist* ptr1 = new linlist, *ptr2 = new linlist;
	 ptr1 = head;
	 ptr2 = head;
	 while (ptr1)
	 {
		 while (ptr2)
		 {
			 if (ptr2->curr_student.avg < ptr2->nextptr->curr_student.avg)
			 {
				 swap(ptr2->nextptr,ptr2->nextptr->nextptr);
			 }
		 }
	 }
 }

void arr()
{
	student a[10];
	int count = 0;
	for (int i = 0; i < 10; i++)
	{
		cout << "Enter first name" << "\n";
		cin >> a[i].first_name;
		cout << "Enter last name" << "\n";
		cin >> a[i].last_name;
		cout << "Enter patronymic name" << "\n";
		cin >> a[i].patronymic_name;
		cout << "Enter number of group" << "\n";
		short* b = new short;
		a[i].group_num = short_enter(b);
		delete b;
		float sum = 0;
		for (int j = 0; j < 5; j++)
		{
			cout << "Enter grade" << "\n";
			short* c = new short;
			a[i].grade[j] = short_enter(c);
			if (*a[i].grade < 4)
			{
				a[i].otl = false;
			}
			delete c;
			sum = sum + a[i].grade[j];
			cout << "sum=" << sum << "\n";
		}
		a[i].avg = sum / 5;
		cout << "avg=" << a[i].avg << "\n";
		count = ++count;
		short* k = new short;
		cout << "Enter 0 if you want to stop writing, or any positive number if you don't" << "\n";
		cin >> *k;
		if (!(*k))
			break;
		else
			cout << "Continue..." << "\n";
		delete k;
	}

	for (int i = 0; i < count; i++)
	{
		for (int j = 0; j < count; j++)
		{
			if (a[j].avg < a[j + 1].avg)
				swap(a[j], a[j + 1]);
		}
	}
	for (int i = 0; i < count; i++)
	{
		cout << a[i].first_name << "\n";
		cout << a[i].last_name << "\n";
		cout << a[i].patronymic_name << "\n";
		cout << a[i].group_num << "\n";
		cout << a[i].avg << "\n";
	}
	short* counter = new short;
	*counter = 0;
	for (int i = 0; i < count; i++)
	{
		if (a[i].otl)
		{
			cout << "Students with only 4 and 5 grades:" << "\n";
			cout << a[i].first_name << "\n";
			cout << a[i].last_name << "\n";
			cout << a[i].group_num << "\n";
			*counter++;
		}
	}
	if (*counter == 0)
		cout << "Student with only 4 and 5 grades does not exist" << "\n";
	delete counter;
	system ("pause");
}

void list()
{
	linlist* head = nullptr;
		add(head);
		listsort(head);
		print(head);
		system("pause");
		return;
};

int main()
{
	cout << "                   This program works with data structures" << "\n" << "\n" << "\n";
	short prog = 1;
	while (prog)
	{
		short* choose = new short;
		cout << "Choose what to keep:" << "\n" << "\n"
			<< "1 - Use array as data structure" << "\n"
			<< "2 - Use linked list as data structure" << "\n"
			<< "9 - Exit if you want" << "\n";
		*choose = short_enter(choose);
		switch (*choose)
		{
		case 1:
		{
			system("cls");
			arr();
		}
		case 2:
		{
			system("cls");
			list();
		}
		case 9: 
		{
			system("cls");
			prog = 0;
			break;
		}
		system("cls");
		default: cout << "Please, write 1, 2 or 9, there's no choice" << "\n";
			break;
		}
		delete choose;
	}
}