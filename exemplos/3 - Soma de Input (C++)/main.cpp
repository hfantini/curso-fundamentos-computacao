#include <iostream>

void main(char* args)
{
	int num1 = 0;
	int num2 = 0;
	int resultado = 0;

	std::cout << "Digite o primeiro numero: ";
	//std::cout.write("Digite o primeiro numero: ", 27);
	std::cin >> num1;

	std::cout << "Digite o segundo numero: ";
	std::cin >> num2;

	resultado = num1 + num2;

	std::cout << "O resultado da sua soma: " << resultado;
	std::cin.get();
}