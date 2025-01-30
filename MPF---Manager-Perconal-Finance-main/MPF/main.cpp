#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <cstring>

const int sizeN{ 19 };





class Card {
protected:
	char* number; //����� �����
	int amountOfMoney; // ����� ����� �� �����
public:

	char* getNum() { // �������� ����� ��������
		return number;
	}

	int getMoney() { // �������� ���������� ����� �� ��������
		return amountOfMoney;
	}


	void setNum(char* number_p) { // ��������� ����� ��������
		number = number_p;
	}

	void setMoney(int amountOfMoney_p) { // ��������� ���������� ����� �� ��������
		amountOfMoney = amountOfMoney_p;
	}

};


class Purchase { // ����� ������� ���� � ���� ����� ������� � � ���������
private:
	int sum;
	const char* category; //�������� ���������

public:
	Purchase(int sum_p, const char* category_p) : sum{ sum_p }, category{category_p} {
	}

	int getSum() { //������� ����� �������
		return sum;
	}
	
	const char* getCategory() { //������� ��������� �������
		return category; 
	}

	void setSum(int sum_p) { // ��������� ����� �������
		sum = sum_p;
	}

	void setCategory(const char* category_p) { // ��������� ��������� �������
		category = category_p;
	}
};


class Debt : public Card {
private:
	
	bool limD(Purchase purch) { // �������� �� ������ �� �� � �����
		if ( purch.getSum() > amountOfMoney) {
			return true;
		}
		else {
			return false;

		}

	}
public:
	Debt() { //����������� ��������� ����� ��� ���������� ��� Wallet
		
		char numCard[sizeN]{"1234"}; // ��������� ���������� ��� ��������� ������ ��������� ����� 
		std::cout << "������� ����� ����� ��������� �����: ";
		std::cin >> numCard;
		//strcpy(number, numCard);
		number = numCard;

		std::cout << "������� ���������� ����� �� ����� ����� ��������� �����: ";
		std::cin >> amountOfMoney;

	}
	Debt(char* number_p, int amountOfMoney_p) {
		number = number_p;
		amountOfMoney = amountOfMoney_p;
	}


	void doPurchase(Purchase purch) { //�������� �������(��������� ������ � ��������)
		if (limD(purch)) {
			std::cerr << "������: ������� �� ����� ���� ���������� � ����� �������� ������� �� �����" << std::endl;
		}
		else {

			amountOfMoney = amountOfMoney - purch.getSum();
		}
		
	}



	

};

class Credit : public Card {
private:
	int creditLim; //����� �������
	int debt; //����

	bool lim() { //��������� ��������� �� ������������ ����� ���� �� �� true
		if (debt > creditLim) {
			return true;
		}
		else {
			return false;

		}
	}
	void limFall() { // ��� ���������� ������ ������� ������� ���������
		if (lim()) {
			std::cout << "�� ��������� ����� ������� �� " << (debt - creditLim) << "������ ( ����� �������: " << creditLim << ", �� ���������: " << debt << std::endl;
		}
	}
	

public:

	Credit() { //����������� ���������� ����� ��� ���������� ��� Wallet
		char numCard[sizeN]{}; // ��������� ���������� ��� ��������� ������ ��������� ����� 
		std::cout << "������� ����� ����� ��������� �����: ";
		std::cin >> numCard;
		//strcpy(number, numCard);
		number = numCard;

		std::cout << "������� ���������� ����� �� ����� ����� ��������� �����: ";
		std::cin >> amountOfMoney;

		std::cout << "������� ����� ������� ����� ��������� �����: ";
		std::cin >> creditLim;

		std::cout << "������� ����� ����� ����� ��������� �����: ";
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


	void doPurchase(Purchase purch) { //�������� �������(��������� ������ � ��������)
		amountOfMoney = amountOfMoney - purch.getSum();
		if (amountOfMoney < 0) {
			debt = -amountOfMoney;
		}
		if (lim()) {
			std::cout << "�� ��������� ����� ������� �� " << (debt - creditLim) << " ������ ( ����� �������: " << creditLim << ", ��� ����: " << debt << " )" << std::endl;
		}

	}



	

	int getCreditLim() { // �������� ����� ������ �������
		return amountOfMoney;
	}

	int getDebt() { // �������� ����� �����
		return amountOfMoney;
	}

	
	
	void setCreditLim(int creditLim_p) { // ��������� ����� ������ �������
		creditLim = creditLim_p;
	}
	void setDebt(int debt_p) { // ��������� ����� �����
		debt = debt_p;
	}
};


class Wallet { // ����� ��� �������� ����� � �� �������� ����� ���������� ����� ����� �������, �����, �����
private: //������������ ������ ���� ��������� � ���������
	
	std::vector<Debt> dCards; 
	int dSize; //���������� ��������� ����

	std::vector<Credit> cCards;
	int cSize; //���������� ��������� ����

	char* walletName;;
	
	
public://������ ����� ����� �������, �����, �����
	//������ ���� �������� ����� ���������� ����� �����(��������� � ���������) � ������������ ������, ���� ��� � �������, ����� ����� �������� ����� � ��

	Wallet(int dSize_p, int cSize_p) : dSize{ dSize_p }, cSize{ cSize_p } { // ��������� ���������� ���������, ���������� ���������
		
		char numCard[sizeN]{}; // ��������� ���������� ��� ��������� ������ ��������� ����� 
		std::cout << "������� ��� ������ ��������: ";
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
	std::cout << "1) �����" << std::endl;
	std::cout << "2) �������� �������" << std::endl;
	std::cout << "3) ������ " << std::endl;
	std::cout << "4) ���������� ����������" << std::endl;
	std::cout << "5) �����" << std::endl;
	std::cout << "��� �����: ";
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
	1) �����
	1.1) ���������
	1.2) ���������
	2) �������� �������
	3) �������� �����
	4) ������
	5) ���������� ����������
	*/


}

int main(){
	setlocale(LC_ALL, "Russian");
	

	Interface();

	Wallet wal{ 1, 1 };

	 // ���������� �������� � �����(������������)
	char numCard1[sizeN]{"123543"};//����� ����� ��� ������������� ����
	char numCard2[sizeN]{ "1488" };//����� ����� ��� ������������� ����

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