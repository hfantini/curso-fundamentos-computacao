#include <iostream>
#include <string>

void main(char* args)
{
	int num1 = 0;
	int num2 = 0;
	char operacao;
	int resultado = 0;

	std::cout << "Digite o primeiro numero: ";
	std::cin >> num1;

	std::cout << "Digite o segundo numero: ";
	std::cin >> num2;

	std::cout << "Qual operacao: ";
	std::cin >> operacao;

	if ( operacao == '+' )
	{
		resultado = num1 + num2;
	}
	else if ( operacao == '-' )
	{
		resultado = num1 - num2;
	}
	else if ( operacao == '*' )
	{
		resultado = num1 * num2;
	}
	else if ( operacao == '/' )
	{
		if (num2 == 0)
		{
			std::cout << "Operação inválida - divisão por zero";
			return;
		}

		resultado = num1 / num2;
	}
	else
	{
		std::cout << "Operacao invalida! Saindo.";
		return;
	}

	std::cout << "O resultado da sua conta: " << resultado;
	std::cin.get();
}