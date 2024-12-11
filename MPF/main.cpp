#include <iostream>

class Wallet { // место где хранятся карты и из которого можно посмотреть общую сумму кредита, долга, денег
private:
	//динамический массив карт кредитных и дебетовых
public:
	//геттер общей суммы кредита, долга, денег

};

class Card {
protected:
	const char* number; //номер карты
	int amountOfMoney; // Сумма денег на карте
public:



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


class Debt : protected Card {
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
	Debt(const char* number_p, int amountOfMoney_p) {
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



	const char* getNum() { // получить номер карточки
		return number;
	}

	int getMoney() { // получить количество денег на карточке
		return amountOfMoney;
	}


	void setNum(const char* number_p) { // назначить номер карточки
		number = number_p;
	}

	void setMoney(int amountOfMoney_p) { // назначить количество денег на карточке
		amountOfMoney = amountOfMoney_p;
	}

};

class Credit : protected Card {
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
	Credit(const char* number_p, int amountOfMoney_p, int creditLim_p, int debt_p) {
		number = number_p;
		amountOfMoney = amountOfMoney_p;
		creditLim = creditLim_p;
		debt = debt_p;
	}

	Credit(const char* number_p, int amountOfMoney_p, int creditLim_p) : Credit(number_p, amountOfMoney_p, creditLim_p, 0) {
		
	}

	Credit(const char* number_p, int amountOfMoney_p) : Credit(number_p, amountOfMoney_p, 0, 0) {
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



	const char* getNum() { // получить номер карточки
		return number;
	}

	int getMoney() { // получить количество денег на карточке
		return amountOfMoney;
	}

	int getCreditLim() { // получить сумму лимита кредита
		return amountOfMoney;
	}

	int getDebt() { // получить сумму долга
		return amountOfMoney;
	}

	
	void setNum(const char* number_p) { // назначить номер карточки
		number = number_p;
	}

	void setMoney(int amountOfMoney_p) { // назначить количество денег на карточке
		amountOfMoney = amountOfMoney_p;
	}
	void setCreditLim(int creditLim_p) { // назначить сумму лимита кредита
		creditLim = creditLim_p;
	}
	void setDebt(int debt_p) { // назначить сумму долга
		debt = debt_p;
	}
};


int main(){
	setlocale(LC_ALL, "Russian");


	Debt cardD1{ "123543", 12 };
	
	Credit cardC1{ "1488", 1231231, 100 };

	Purchase purch{ 500, "Pivo" };

	int temp{};

	std::cin >> temp;
	cardC1.setMoney(temp);
	std::cout << cardC1.getMoney() << std::endl;
	cardC1.doPurchase(purch);
	std::cout << cardC1.getMoney() << std::endl;


	return 0;
}