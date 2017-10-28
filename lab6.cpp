#include "stdafx.h"
#include <iostream>
#include <memory>
#include <utility>
#include <vector>

std::vector<double> nodes;
template <class T>
void swap_ptr(std::unique_ptr<T>&, std::shared_ptr<T>&);

template <class T>
class Linked_list
{
private:
	struct Node
	{
		T data; // данные, которые записываются в узел 
		std::shared_ptr<Node> next; // Указатель на следующий узел (На самом деле предыдущий)
	};
	std::shared_ptr<Node> head; // Указатель на предыдущий узел в списке
	unsigned int index; // Номер узла
public:
	Linked_list();
	void push_back(T);
	void push_front(T);
	bool pop_back();
	bool pop_front();
	unsigned int size() { return index; }
	void print();
};


int main()
{
	system("chcp 65001");
	using std::cout;
	using std::cin;
	using std::endl;

	unsigned int choice = { 0 };
	Linked_list<double> list;
	cout << endl << "***Лабораторная работа №6: Реализация класса linked_list с помощью уникальных указателей***" << endl
	<< "1. Вставить элемент в конец списка;" << endl << "2. Вставить элемент в начало списка;" << endl
	<< "3. Удалить элемент из конца списка;" << endl << "4. Удалить элемент из начала списка;" << endl
	<< "5. Вывести длину списка;" << endl << "6. Показать список." << endl << "q - для выхода." << endl;
	while (cin >> choice)
	{
		if (choice == 1)
		{
			cout << "Введите элемент для вставки: ";
			double temp;
			if (cin >> temp)
				list.push_back(temp);
			else
			{	
				cout << "[-] Ошибка ввода!" << endl;
				cin.clear();
			}
				
		}
		else if (choice == 2)
		{
			cout << "Введите элемент для вставки: ";
			double temp;
			if (cin >> temp)
				list.push_front(temp);
			else
			{
				cout << "[-] Ошибка ввода!" << endl;
				cin.clear();
			}
		}
		else if (choice == 3)
		{
			if (!list.pop_back())
			{
				cout << "[-] Список уже пуст!" << endl;
			}
		}
		else if (choice == 4)
		{
			if (!list.pop_front())
			{
				cout << "[-] Список уже пуст!" << endl;
			}
		}
		else if (choice == 5)
			cout << "Количество элементов в списке: " << list.size() << endl;
		else if (choice == 6)
			list.print();
	}
	cout << endl << "Реализация обмена значений двух указателей" << endl;
	std::unique_ptr<double> u_ptr(new double(1.1));
	std::shared_ptr<double> s_ptr(new double(2.2));
	cout << "До применения функции swap():" << endl << "*u_ptr = " << *u_ptr << endl << "*s_ptr = " << *s_ptr << endl;
	swap_ptr(u_ptr,s_ptr);
	cout << "После применения функции swap():" << endl << "*u_ptr = " << *u_ptr << endl << "*s_ptr = " << *s_ptr << endl;

	cout << endl;
	system("pause");
    return 0;
}

template <class T>
Linked_list<T>::Linked_list()
{
	index = { 0 };
	head = nullptr;
}

template <class T>
void Linked_list<T>::push_back(T _data)
{
	index++;
	std::shared_ptr<Node> _next(new Node());
	_next->data = _data;         // Задаем значение для нового узла
	_next->next = head;         // Указатель next = Указатель на предыдущий узел (head)
	head = _next;              // Указатель head = Указатель на текущий узел
	nodes.push_back(_next->data);
}

template <class T>
void Linked_list<T>::push_front(T _data)
{
	std::shared_ptr<Node> temp_head(new Node()); // Указатель для поиска первого узла
	std::shared_ptr<Node> _next(new Node());
	if (head != nullptr)
	{
		temp_head = head;
		index++;
	}
	else
	{
		std::cout << "[-] Необходимо добавить хотя бы один элемент в конец списка." << std::endl;
		return;
	}
	while (temp_head->next != nullptr) // Пока не дойдем до первого узла
		temp_head = temp_head->next;
	temp_head->next = _next; // Вставляем узел
	_next->data = _data;
	_next->next = nullptr;
	nodes.insert(nodes.begin(), _next->data);
}

template <class T>
bool Linked_list<T>::pop_back()
{
	if (index > 0)
	{
		index--;
		head = head->next;
		nodes.pop_back();
		return true;
	}
	else
		return false;
}

template <class T>
bool Linked_list<T>::pop_front()
{
	if (index > 0)
	{
		index--;
		std::shared_ptr<Node> temp_head(new Node()); // Указатель для поиска первого узла
		std::shared_ptr<Node> _next(new Node());
		temp_head = head;
		while (temp_head->next != nullptr)
			temp_head = temp_head->next;
		temp_head = nullptr; // Убираем узел
		nodes.erase(nodes.begin());
		return true;
	}
	else
		return false;
}

template <class T>
void Linked_list<T>::print()
{
	std::cout << "Элементы списка:" << std::endl;
	for (auto it : nodes) 
		std::cout << it << "  ";
	std::cout << std::endl;
}

template <class T>
void swap_ptr(std::unique_ptr<T>& u_ptr, std::shared_ptr<T>& s_ptr)
{
	*u_ptr = *u_ptr + *s_ptr;
	*s_ptr = *u_ptr - *s_ptr;
	*u_ptr = *u_ptr - *s_ptr;
}