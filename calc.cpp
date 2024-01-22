#include <iostream>
#include<stack>


const double Pi = acos(-1);

double Ctg(double val)
{
	double a = cos(val);
	double b = sin(val);
	return a / b;
}

double Sin(double val)
{
	return (round(sin(val) * 10000000 / 10000000));
}

double Cos(double x) 
{ 
	return (round(cos(x) * 10000000) / 10000000);
}



struct MyStruct
{
	char type;	//0 для чисел, "+" для операция сложения и т.д
	double value;
};

bool Answer(std::stack<MyStruct>& stack_num, std::stack<MyStruct>& stack_operat, MyStruct& item)//Функция имеет тип bool, чтобы при возникновении какой-либо ошибки возвращать "false"
{
	
	double a, b;
	a = stack_num.top().value; 
	stack_num.pop();
	item.type = '0';
	switch (stack_operat.top().type) 
	{  
	case '+': 
		b = stack_num.top().value;
		stack_num.pop();
		
		
		item.value = a + b;
		stack_num.push(item); 
		break;

	case '-':
		b = stack_num.top().value;
		stack_num.pop();
		
		
		item.value = b - a;
		stack_num.push(item);
		break;

	case '^':
		b = stack_num.top().value;
		stack_num.pop();
		
		
		item.value = pow(b, a);
		stack_num.push(item);
		break;

	case '*':
		b = stack_num.top().value;
		stack_num.pop();
		
		
		item.value = a * b;
		stack_num.push(item);
		break;

	case '/':
		b = stack_num.top().value;
		if (a == 0) 
		{
			std::cerr << "\nНа 0 делить нельзя!\n";
			return false;
		}
		else
		{
			stack_num.pop();
			
			
			item.value = (b / a);
			stack_num.push(item);
			break;
		}

	case 's':

		item.value = Sin(a);
		stack_num.push(item);
		break;

	case 'c':
		item.value = Cos(a);
		stack_num.push(item);

		break;

	case 't':
		if (Cos(a) == 0) {
			std::cerr << "\nНеверный аргумент для тангенса!\n";
			return false;
		}
		else {
			item.value = tan(a);
			stack_num.push(item);
			break;
		}

	case 'g':
		if (Sin(a) == 0) {
			std::cerr << "\nНеверный аргумент для котангенса!\n";
			return false;
		}
		else {
			item.value = Ctg(a);
			stack_num.push(item);
			break;
		}

	case 'e':
		item.value = exp(a);
		stack_num.push(item);
		break;

	default:
		std::cerr << "\nОшибка!\n";
		return false;
		break;
	}
	stack_operat.pop();
	return true;
}





int Priority(char Ch)
{
	if (Ch == '+' || Ch == '-')
	{
		return 1;
	}
	if (Ch == '*' || Ch == '/')
	{
		return 2;
	}
	if (Ch == '^')
	{
		return 3;
	}
	if (Ch == 's' || Ch == 'c' || Ch == 't' || Ch == 'g' || Ch == 'e')
	{
		return 4;
	}
	else
		return 0;
}








int main()
{
	setlocale(LC_ALL, "rus");
	std::cout << "Калькулятор\nВведите выражение: ";

	char Ch;
	bool flag = 1;	
	double value;
	std::stack<MyStruct> stack_num;
	std::stack<MyStruct> stack_operat;
	MyStruct item;


	while (true)
	{

		Ch = std::cin.peek();
		if (Ch == '\n')
			break;
		if (Ch == ' ')
		{
			std::cin.ignore();
			continue;
		}

		if (Ch == 's' || Ch == 'c' || Ch == 't' || Ch == 'e')
		{
			char func[3];
			item.value = 0;
			for (int i = 0; i < 3; i++)	
			{
				Ch = std::cin.peek();
				func[i] = Ch;
				std::cin.ignore();
			}
			if (func[0] == 's' && func[1] == 'i' && func[2] == 'n') {
				
				item.type = 's';

				stack_operat.push(item);
				
				continue;
			}
			if (func[0] == 'c' && func[1] == 'o' && func[2] == 's') {

				item.type = 'c';

				stack_operat.push(item);
				
				continue;
			}
			if (func[0] == 't' && func[1] == 'a' && func[2] == 'n') {

				item.type = 't';

				stack_operat.push(item);
				
				continue;
			}			
			if (func[0] == 'c' && func[1] == 't' && func[2] == 'g') {

				item.type = 'g';

				stack_operat.push(item);
				
				continue;
			}
			if (func[0] == 'e' && func[1] == 'x' && func[2] == 'p') {

				item.type = 'e';

				stack_operat.push(item);
				
				continue;
			}
		}

		if (Ch == 'p')	
		{
			item.type = '0';
			item.value = Pi;
			stack_num.push(item);
			flag = 0;
			std::cin.ignore();
			continue;
		}

		if (Ch >= '0' && Ch <= '9' || Ch == '-' && flag == 1)	
		{
			item.type = '0';
			std::cin >> item.value;
			stack_num.push(item);
			flag = 0;
			continue;
		}

		if (Ch == '+' || Ch == '-' && flag == 0 || Ch == '*' || Ch == '/' || Ch== '^')//если операция
		{

			if (stack_operat.size() == 0) {
				item.type = Ch;
				item.value = 0;
				stack_operat.push(item);
				std::cin.ignore();
				continue;
			}

			if (stack_operat.size() != 0 && Priority(Ch) > Priority(stack_operat.top().type))//Если стек с операциями НЕ пуст, но приоритет текущей операции выше верхней в стеке с операциями
			{
				item.type = Ch;
				item.value = 0;
				stack_operat.push(item);
				std::cin.ignore();
				continue;
			}

			if (stack_operat.size() != 0 && Priority(Ch) <= Priority(stack_operat.top().type)) // Если стек с операциями НЕ пуст, но приоритет текущей операции ниже либо равен верхней в стеке с операциями
			{
				if (Answer(stack_num, stack_operat, item) == false)
				{
					system("pause");
					return 0;
				}
				continue;
			}

		}
		if (Ch == '(')
		{
			item.type = Ch;
			item.value = 0;
			stack_operat.push(item);
			std::cin.ignore();
			
			continue;
		}
		if (Ch == ')')
		{
			while (stack_operat.top().type != '(')
			{
				Answer(stack_num, stack_operat, item);
			}
			stack_operat.pop();
			std::cin.ignore();
			continue;
		}
		else {
			std::cout << "\nNEverno virazenie!!!!\n";
			system("pause");
			return 0;
		}
	}

	while (stack_operat.size() != 0)
	{
		//if (Answer(stack_num, stack_operat, item))
		//{
		//	continue;
		//}
		//else {
		//	system("pause");
		//	return 0;
		//}
		Answer(stack_num, stack_operat, item);
	}

	std::cout << "Otvet: " << stack_num.top().value << std::endl;
	return 0;
}

