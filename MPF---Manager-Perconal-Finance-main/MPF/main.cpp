#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <cstring>

const int sizeN{ 19 };





class Card {
protected:
	char* number; //номер карты
	int amountOfMoney; // Сумма денег на карте
public:

	char* getNum() { // получить номер карточки
		return number;
	}

	int getMoney() { // получить количество денег на карточке
		return amountOfMoney;
	}


	void setNum(char* number_p) { // назначить номер карточки
		number = number_p;
	}

	void setMoney(int amountOfMoney_p) { // назначить количество денег на карточке
		amountOfMoney = amountOfMoney_p;
	}

};


class Purchase { // класс который несёт в себе сумму покупки и её категорию
private:
	int sum;
	const char* category; //название категории

public:
	Purchase(int sum_p, const char* category_p) : sum{ sum_p }, category{category_p} {
	}

	int getSum() { //Вернуть сумму покупки
		return sum;
	}
	
	const char* getCategory() { //Вернуть категорию покупки
		return category; 
	}

	void setSum(int sum_p) { // назначить сумму покупки
		sum = sum_p;
	}

	void setCategory(const char* category_p) { // назначить категорию покупки
		category = category_p;
	}
};


class Debt : public Card {
private:
	
	bool limD(Purchase purch) { // проверка не уходим ли мы в минус
		if ( purch.getSum() > amountOfMoney) {
			return true;
		}
		else {
			return false;

		}

	}
public:
	Debt() { //конструктор дебетовой карты без параметров для Wallet
		
		char numCard[sizeN]{"1234"}; // локальная переменная для задавания номера дебетовой карты 
		std::cout << "Введите номер новой дебетовой карты: ";
		std::cin >> numCard;
		//strcpy(number, numCard);
		number = numCard;

		std::cout << "Введите количество денег на счету новой дебетовой карты: ";
		std::cin >> amountOfMoney;

	}
	Debt(char* number_p, int amountOfMoney_p) {
		number = number_p;
		amountOfMoney = amountOfMoney_p;
	}


	void doPurchase(Purchase purch) { //добавить покупку(потратить деньги с карточки)
		if (limD(purch)) {
			std::cerr << "Ошибка: покупка не может быть совершенна в связи нехватки средств на карте" << std::endl;
		}
		else {

			amountOfMoney = amountOfMoney - purch.getSum();
		}
		
	}



	

};

class Credit : public Card {
private:
	int creditLim; //лимит кредита
	int debt; //долг

	bool lim() { //проверяет превзошел ли пользователь лимит если да то true
		if (debt > creditLim) {
			return true;
		}
		else {
			return false;

		}
	}
	void limFall() { // при превышение лимита кредита выводит сообщение
		if (lim()) {
			std::cout << "Вы превысили лимит кредита на " << (debt - creditLim) << "рублей ( Лимит кредита: " << creditLim << ", Вы потратили: " << debt << std::endl;
		}
	}
	

public:

	Credit() { //конструктор кредитнойй карты без параметров для Wallet
		char numCard[sizeN]{}; // локальная переменная для задавания номера кредитной карты 
		std::cout << "Введите номер новой кредитной карты: ";
		std::cin >> numCard;
		//strcpy(number, numCard);
		number = numCard;

		std::cout << "Введите количество денег на счету новой кредитной карты: ";
		std::cin >> amountOfMoney;

		std::cout << "Введите лимит кредита новой кредитной карты: ";
		std::cin >> creditLim;

		std::cout << "Введите сумму долга новой кредитной карты: ";
		std::cin >> debt;
		
		
	}

	Credit(char* number_p, int amountOfMoney_p, int creditLim_p, int debt_p) {
		number = number_p;
		amountOfMoney = amountOfMoney_p;
		creditLim = creditLim_p;
		debt = debt_p;
	}

	Credit(char* number_p, int amountOfMoney_p, int creditLim_p) : Credit(number_p, amountOfMoney_p, creditLim_p, 0) {
		
	}

	Credit(char* number_p, int amountOfMoney_p) : Credit(number_p, amountOfMoney_p, 0, 0) {
	}


	void doPurchase(Purchase purch) { //добавить покупку(потратить деньги с карточки)
		amountOfMoney = amountOfMoney - purch.getSum();
		if (amountOfMoney < 0) {
			debt = -amountOfMoney;
		}
		if (lim()) {
			std::cout << "Вы превысили лимит кредита на " << (debt - creditLim) << " рублей ( Лимит кредита: " << creditLim << ", ваш долг: " << debt << " )" << std::endl;
		}

	}



	

	int getCreditLim() { // получить сумму лимита кредита
		return amountOfMoney;
	}

	int getDebt() { // получить сумму долга
		return amountOfMoney;
	}

	
	
	void setCreditLim(int creditLim_p) { // назначить сумму лимита кредита
		creditLim = creditLim_p;
	}
	void setDebt(int debt_p) { // назначить сумму долга
		debt = debt_p;
	}
};


class Wallet { // место где хранятся карты и из которого можно посмотреть общую сумму кредита, долга, денег
private: //динамический массив карт кредитных и дебетовых
	
	std::vector<Debt> dCards; 
	int dSize; //количество дебетовых карт

	std::vector<Credit> cCards;
	int cSize; //количество кредитных карт

	char* walletName;;
	
	
public://геттер общей суммы кредита, долга, денег
	//КАРОЧЕ НАДО НАПИСАТЬ МЕТОД ДОБАВЛЕНИЕ НОВОЙ КАРТЫ(ДЕБЕТОВОЙ И КРЕДИТНОЙ) В ДИНАМИЧЕСКИЙ МАССИВ, ТИПО КАК В ВЕКТОРЕ, ТАКЖЕ МЕТОД УДАЛЕНИЕ КАРТЫ И ТД

	Wallet(int dSize_p, int cSize_p) : dSize{ dSize_p }, cSize{ cSize_p } { // принимает количество дебетовых, количество кредитных
		
		char numCard[sizeN]{}; // локальная переменная для задавания номера кредитной карты 
		std::cout << "Введите имя нового кошелька: ";
		std::cin >> numCard;
		
		walletName = numCard;
		
		for(int i{}; i < dSize; i++){
			dCards.push_back(Debt());
		}
		
		for (int i{}; i < cSize; i++) {
			cCards.push_back(Credit());
		}
		//dCards = new Debt[dSize];
		//cCards = new Credit[cSize];
		

	}


};


void Interface() {
	int menuI;
	std::cout << "\tMPF - Manager Personal Finance" << std::endl;
	std::cout << "1) Карты" << std::endl;
	std::cout << "2) Записать покупку" << std::endl;
	std::cout << "3) Сводка " << std::endl;
	std::cout << "4) Управление кошельками" << std::endl;
	std::cout << "5) Выход" << std::endl;
	std::cout << "Ваш выбор: ";
	std::cin >> menuI;
	switch (menuI) {
	case(1):
		int menuI2;
		if (menuI2 == )

		break;
	case(2):

		break;
	case(3):

		break;
	case(4):

		break;
	case(5):
		break;
	}
	/* 
	1) Карты
	1.1) Кредитные
	1.2) Дебетовые
	2) Записать покупку
	3) Добавить карты
	4) Сводка
	5) Управление Кошельками
	*/


}

int main(){
	setlocale(LC_ALL, "Russian");
	

	Interface();

	Wallet wal{ 1, 1 };

	 // количество символов в карте(максимальное)
	char numCard1[sizeN]{"123543"};//номер карты для инициализации карт
	char numCard2[sizeN]{ "1488" };//номер карты для инициализации карт

	Debt cardD1{ numCard1, 12 };
	
	Credit cardC1{ numCard2, 1231231, 100 };

	Purchase purch{ 500, "Pivo" };

	int moneyMain{};

	std::cin >> moneyMain;
	cardC1.setMoney(moneyMain);
	std::cout << cardC1.getMoney() << std::endl;
	cardC1.doPurchase(purch);
	std::cout << cardC1.getMoney() << std::endl;


	return 0;
}