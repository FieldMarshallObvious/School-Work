#include <iostream>
#include <string>
using namespace std;

class pizza
{
public:
	string ingrediants, address;
	pizza *next;
	pizza(string ingrediants, string address)
	{
		this->address = address;
		this->ingrediants = ingrediants;
		next = NULL;
	}
};

void enqueue(pizza **head, pizza **tail, pizza *thispizza)
{
	if (*head == NULL) *head = thispizza;
	else (*tail)->next = thispizza;
	*tail = thispizza;
	return;
}

pizza* dequeue(pizza **head, pizza **tail)
{
	pizza* pizzatodeliver = NULL;
	if (*head != NULL)
	{
		pizzatodeliver = *head;
		*head = (*head)->next;
	}
	if (*head == NULL) *tail = NULL;
	return pizzatodeliver;
}

void deliver(pizza **head, pizza** tail)
{
	pizza *thispizza = dequeue(head, tail);
	if (thispizza == NULL)
	{
		cout << "No deliveries pending" << endl; return;
	}
	cout << "Deliver a pizza with " << thispizza->ingrediants
		<< " to " << thispizza->address << endl;
}

int main()
{
	pizza *first = NULL, *last = NULL;

	enqueue(&first, &last, new pizza("pepperoni", "1234 Bobcat Trail"));
	enqueue(&first, &last, new pizza("sausage", "2345 University Drive"));
	deliver(&first, &last);
	enqueue(&first, &last, new pizza("extra cheese", "3456 Rickster Road"));
	enqueue(&first, &last, new pizza("everything", "4567 King Court"));
	enqueue(&first, &last, new pizza("coffee beans", "5678 Java Circle"));
	deliver(&first, &last);
	deliver(&first, &last);
	deliver(&first, &last);
	deliver(&first, &last);
	deliver(&first, &last);

	cin.get();  return 0;
}

