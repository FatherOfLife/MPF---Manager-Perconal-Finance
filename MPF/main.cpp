//addMoney вкредитах доделай

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <cstring>

const int sizeN{ 19 };//для максимального значения номера карты
const int sizeP{ 50 };//Для максимального количества букв в названии/категории




class Card {
protected:
	char number[sizeN]; //номер карты
	int amountOfMoney; // Сумма денег на карте
public:

	char* getNum() { // получить номер карточки
		return number;
	}

	int getMoney() { // получить количество денег на карточке
		return amountOfMoney;
	}


	void setNum(char* number_p) { // назначить номер карточки
		strcpy(number, number_p);
		
	}

	void setMoney(int amountOfMoney_p) { // назначить количество денег на карточке
		amountOfMoney = amountOfMoney_p;
	}

};


class Purchase { // класс который несёт в себе сумму покупки и её категорию
private:
	int sum;
	char name[sizeP]; //наименование товара
	char category[sizeP]; //название категории

public:
	Purchase(int sum_p, char* name_p, char* category_p) {
		sum = sum_p;
		strcpy(name, name_p);
		strcpy(category, category_p);
	}
	Purchase() {
		sum = 0;
		strcpy(name, "");
		strcpy(category, "");
	}

	int getSum() { //Вернуть сумму покупки
		return sum;
	}
	
	char* getCategory() { //Вернуть наименование покупки
		return category; 
	}

	char* getName() { //Вернуть наименование покупки
		return name;
	}

	void setSum(int sum_p) { // назначить сумму покупки
		sum = sum_p;
	}

	void setCategory(const char* category_p) { // назначить категорию покупки
		strcpy(category, category_p);
	}

	void setName(const char* name_p) { // назначить наименование покупки
		strcpy(category, name_p);
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
		
		char numCard[sizeN]{""}; // локальная переменная для задавания номера дебетовой карты 
		std::cout << "Введите номер новой дебетовой карты: ";
		std::cin >> numCard;
		strcpy(number, numCard);
		

		std::cout << "Введите количество денег на счету новой дебетовой карты: ";
		std::cin >> amountOfMoney;
		std::cout << std::endl;
	}
	Debt(char* number_p, int amountOfMoney_p) {
		strcpy(number, number_p);
		amountOfMoney = amountOfMoney_p;
	}

	void addMoney(int count) {
		amountOfMoney += count;
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
		strcpy(number, numCard);
		

		std::cout << "Введите количество денег на счету новой кредитной карты: ";
		std::cin >> amountOfMoney;

		std::cout << "Введите лимит кредита новой кредитной карты: ";
		std::cin >> creditLim;

		std::cout << "Введите сумму долга новой кредитной карты: ";
		std::cin >> debt;
		std::cout << std::endl;
		
	}

	Credit(char* number_p, int amountOfMoney_p, int creditLim_p, int debt_p) {
		strcpy(number, number_p);
		amountOfMoney = amountOfMoney_p;
		creditLim = creditLim_p;
		debt = debt_p;
	}

	Credit(char* number_p, int amountOfMoney_p, int creditLim_p) : Credit(number_p, amountOfMoney_p, creditLim_p, 0) {
		
	}

	Credit(char* number_p, int amountOfMoney_p) : Credit(number_p, amountOfMoney_p, 0, 0) {
	}

	void addMoney(int count) {
		/*if (lim()) {
			if (count == (debt - creditLim)) {
				debt = creditLim;
				amountOfMoney = creditLim;
			}
			else if (count > (debt - creditLim)) {
				amountOfMoney += count - (debt - creditLim);
				if (amountOfMoney >= 0) {
					debt = 0;
				}
				else {
					debt = amountOfMoney;
				}
			}
		}
		else {
			amountOfMoney += count;
			debt = 0;
		}*/
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
		return creditLim;
	}

	int getDebt() { // получить сумму долга
		return debt;
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
	}

	void addCCard() {
		cCards.push_back(Credit());
		++cSize;
	}
	void addDCard() {
		dCards.push_back(Debt());
		++dSize;
	}
	//методы с кредитными картами

	Credit& getCreditCard(int index) {
		return cCards[index];
	}

	int getAllCreditLim() {
		int AllLim{};
		for(int i{}; i < cSize; i++){
			AllLim += cCards[i].getCreditLim();
		}
		return AllLim;
	}

	int getAllCreditDebt() {
		int AllDebt{};
		for (int i{}; i < cSize; i++) {
			AllDebt += cCards[i].getDebt();
		}
		return AllDebt;
	}

	int getAllCreditMoney() {
		int AllMoney{};
		for (int i{}; i < cSize; i++) {
			AllMoney += cCards[i].getMoney();
		}
		return AllMoney;
	}

	void printCredit() {
		for (int i{}; i < cSize; i++) {
			std::cout <<(i + 1) << ") " << cCards[i].getNum() << "\t\tбаланс: " << cCards[i].getMoney()<< "\tлимит: " << cCards[i].getCreditLim() << "\tдолг: " << cCards[i].getDebt() << std::endl;
		}
		std::cout << std::endl;
	}


	//методы с дебетовыми
	Debt& getDebtCard(int index) {
		return dCards[index];
	}

	int getAllDebtMoney() {
		int AllMoney{};
		for (int i{}; i < dSize; i++) {
			AllMoney += dCards[i].getMoney();
		}
		return AllMoney;
	}

	void printDebtCards() {
		for (int i{}; i < dSize; i++) {
			std::cout << (i + 1) << ") " << dCards[i].getNum() << "\tбаланс: " << dCards[i].getMoney() << std::endl;
		}
		std::cout << std::endl;
	}
};


void Interface(Wallet wallet) {
	int mainI{};
	while (mainI == 0) {
		int menuI;
		std::cout << "\tMPF - Manager Personal Finance" << std::endl;
		std::cout << "1) Карты" << std::endl;
		std::cout << "2) Записать покупку" << std::endl;
		std::cout << "3) Сводка " << std::endl;
		std::cout << "4) Управление кошельками" << std::endl;
		std::cout << "5) Выход" << std::endl;
		std::cout << "Ваш выбор: ";
		std::cin >> menuI;
		std::cout << std::endl;

		switch (menuI) {
		case(1):
			int menuI2;
			std::cout << "\tMPF - Manager Personal Finance" << std::endl;
			std::cout << "1) Кредитные карты" << std::endl;
			std::cout << "2) Дебетовые карты" << std::endl;
			std::cout << "Ваш выбор: ";
			std::cin >> menuI2;
			std::cout << std::endl;

			if (menuI2 == 1) {
				std::cout << "\tMPF - Manager Personal Finance" << std::endl;
				std::cout << "1) Общее" << std::endl;
				std::cout << "2) Список кредитных карт" << std::endl;
				std::cout << "3) Добавить новую кредитную карту" << std::endl;
				std::cout << "4) Пополнить карту" << std::endl;
				std::cout << "Ваш выбор: ";
				std::cin >> menuI2;
				std::cout << std::endl;
				if (menuI2 == 1) {
					std::cout << "\tMPF - Manager Personal Finance" << std::endl;
					std::cout << "Общая сумма средств: " << wallet.getAllCreditMoney() << std::endl;
					std::cout << "Общая сумма лимита: " << wallet.getAllCreditLim() << std::endl;
					std::cout << "Общая сумма долга: " << wallet.getAllCreditDebt() << std::endl;
					std::cout << std::endl;
				}
				else if (menuI2 == 2) {
					std::cout << "\tMPF - Manager Personal Finance" << std::endl;
					wallet.printCredit();
					std::cout << std::endl;
				}
				else if (menuI2 == 3) {
					wallet.addCCard();

				}
				else if (menuI2 == 4) {
					int i{};
					int sum{};
					std::cout << "\tMPF - Manager Personal Finance" << std::endl;

					wallet.printCredit();
					std::cout << "Введите номер(по счету в списке) вашей карты: ";
					std::cin >> i;

					std::cout << "Введите сумму пополнения: ";
					std::cin >> sum;
					(wallet.getCreditCard(i-1)).addMoney(sum);
					std::cout << std::endl;

				}
				else {
					std::cerr << "Введено некорректное значение!!!" << std::endl;
				}

			}
			else if (menuI2 == 2) {

				std::cout << "\tMPF - Manager Personal Finance" << std::endl;
				std::cout << "1) Общее" << std::endl;
				std::cout << "2) Список дебетовых карт" << std::endl;
				std::cout << "3) Добавить новую дебетовую карту" << std::endl;
				std::cout << "4) Пополнить карту" << std::endl;
				std::cout << "Ваш выбор: ";
				std::cin >> menuI2;
				std::cout << std::endl;
				if (menuI2 == 1) {
					std::cout << "\tMPF - Manager Personal Finance" << std::endl;
					std::cout << "Общая сумма средств: " << wallet.getAllDebtMoney() << std::endl;
					std::cout << std::endl;
				}
				else if (menuI2 == 2) {
					std::cout << "\tMPF - Manager Personal Finance" << std::endl;
					wallet.printDebtCards();
					std::cout << std::endl;

				}
				else if (menuI2 == 3) {
					wallet.addDCard();

				}
				else if (menuI2 == 4) {
					int i{};
					int sum{};
					std::cout << "\tMPF - Manager Personal Finance" << std::endl;

					wallet.printDebtCards();
					std::cout << "Введите номер(по счету в списке) вашей карты: ";
					std::cin >> i;

					std::cout << "Введите сумму пополнения: ";
					std::cin >> sum;
					(wallet.getDebtCard(i-1)).addMoney(sum);
					std::cout << std::endl;

				}
				else {
					std::cerr << "Введено некорректное значение!!!" << std::endl;
				}

			}
			else {
				std::cerr << "Введено некорректное значение!!!" << std::endl;
			}
			break;
		case(2):
		{//<-- нужны для решения проблемы с инициализацией newPurch
			char pName[sizeP];
			char pCategory[sizeP];
			int pSum;

			std::cout << "\tMPF - Manager Personal Finance" << std::endl;
			std::cout << "Введите наименование покупки: " << std::endl;
			std::cin >> pName;
			std::cout << "Введите категорию покупки: " << std::endl;
			std::cin >> pCategory;
			std::cout << "Введите сумму покупки: " << std::endl;
			std::cin >> pSum;
			Purchase newPurch{ pSum, pName, pCategory };
			std::cout << std::endl;

			int menuI3;
			std::cout << "\tMPF - Manager Personal Finance" << std::endl;
			std::cout << "Выберите картой какого типа вы оплатили товар: " << std::endl;
			std::cout << "1) Кредитной картой" << std::endl;
			std::cout << "2) Дебетовой картой" << std::endl;
			std::cout << "Ваш выбор: ";
			std::cin >> menuI3;
			std::cout << std::endl;
			if (menuI3 == 1) {
				int i{};
				std::cout << "\tMPF - Manager Personal Finance" << std::endl;

				wallet.printCredit();
				std::cout << "Введите номер(по счету в списке) вашей карты: ";
				std::cin >> i;
				(wallet.getCreditCard(i - 1)).doPurchase(newPurch);
				std::cout << std::endl;
			}
			else if (menuI3 == 2) {
				int i{};
				std::cout << "\tMPF - Manager Personal Finance" << std::endl;

				wallet.printDebtCards();
				std::cout << "Введите номер(по счету в списке) вашей карты: ";
				std::cin >> i;
				(wallet.getDebtCard(i - 1)).doPurchase(newPurch);
				std::cout << std::endl;

			}
			else {
				std::cerr << "Введено некорректное значение!!!" << std::endl;
			}
		}
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
		3) Сводка
		4) Управление Кошельками
		*/

	}

	

}

int main(){
	setlocale(LC_ALL, "Russian");
	
	Wallet wal{ 0, 1};

	Interface(wal);

	

	 
	//char numCard1[sizeN]{"123543"};//номер карты для инициализации карт
	//char numCard2[sizeN]{ "1488" };//номер карты для инициализации карт

	//Debt d(numCard1, 100);
	//std::cout << d.getNum();

	//Debt cardD1{ numCard1, 12 };
	//
	//Credit cardC1{ numCard2, 1231231, 100 };

	//Purchase purch{ 500, "Pivo" };

	//int moneyMain{};

	//std::cin >> moneyMain;
	//cardC1.setMoney(moneyMain);
	//std::cout << cardC1.getMoney() << std::endl;
	//cardC1.doPurchase(purch);
	//std::cout << cardC1.getMoney() << std::endl;


	return 0;
}