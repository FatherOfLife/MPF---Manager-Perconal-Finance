//addMoney ��������� �������

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <cstring>

const int sizeN{ 19 };//��� ������������� �������� ������ �����
const int sizeP{ 50 };//��� ������������� ���������� ���� � ��������/���������




class Card {
protected:
	char number[sizeN]; //����� �����
	int amountOfMoney; // ����� ����� �� �����
public:

	char* getNum() { // �������� ����� ��������
		return number;
	}

	int getMoney() { // �������� ���������� ����� �� ��������
		return amountOfMoney;
	}


	void setNum(char* number_p) { // ��������� ����� ��������
		strcpy(number, number_p);
		
	}

	void setMoney(int amountOfMoney_p) { // ��������� ���������� ����� �� ��������
		amountOfMoney = amountOfMoney_p;
	}

};


class Purchase { // ����� ������� ���� � ���� ����� ������� � � ���������
private:
	int sum;
	char name[sizeP]; //������������ ������
	char category[sizeP]; //�������� ���������

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

	int getSum() { //������� ����� �������
		return sum;
	}
	
	char* getCategory() { //������� ������������ �������
		return category; 
	}

	char* getName() { //������� ������������ �������
		return name;
	}

	void setSum(int sum_p) { // ��������� ����� �������
		sum = sum_p;
	}

	void setCategory(const char* category_p) { // ��������� ��������� �������
		strcpy(category, category_p);
	}

	void setName(const char* name_p) { // ��������� ������������ �������
		strcpy(category, name_p);
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
		
		char numCard[sizeN]{""}; // ��������� ���������� ��� ��������� ������ ��������� ����� 
		std::cout << "������� ����� ����� ��������� �����: ";
		std::cin >> numCard;
		strcpy(number, numCard);
		

		std::cout << "������� ���������� ����� �� ����� ����� ��������� �����: ";
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
		strcpy(number, numCard);
		

		std::cout << "������� ���������� ����� �� ����� ����� ��������� �����: ";
		std::cin >> amountOfMoney;

		std::cout << "������� ����� ������� ����� ��������� �����: ";
		std::cin >> creditLim;

		std::cout << "������� ����� ����� ����� ��������� �����: ";
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
		return creditLim;
	}

	int getDebt() { // �������� ����� �����
		return debt;
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
	}

	void addCCard() {
		cCards.push_back(Credit());
		++cSize;
	}
	void addDCard() {
		dCards.push_back(Debt());
		++dSize;
	}
	//������ � ���������� �������

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
			std::cout <<(i + 1) << ") " << cCards[i].getNum() << "\t\t������: " << cCards[i].getMoney()<< "\t�����: " << cCards[i].getCreditLim() << "\t����: " << cCards[i].getDebt() << std::endl;
		}
		std::cout << std::endl;
	}


	//������ � ����������
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
			std::cout << (i + 1) << ") " << dCards[i].getNum() << "\t������: " << dCards[i].getMoney() << std::endl;
		}
		std::cout << std::endl;
	}
};


void Interface(Wallet wallet) {
	int mainI{};
	while (mainI == 0) {
		int menuI;
		std::cout << "\tMPF - Manager Personal Finance" << std::endl;
		std::cout << "1) �����" << std::endl;
		std::cout << "2) �������� �������" << std::endl;
		std::cout << "3) ������ " << std::endl;
		std::cout << "4) ���������� ����������" << std::endl;
		std::cout << "5) �����" << std::endl;
		std::cout << "��� �����: ";
		std::cin >> menuI;
		std::cout << std::endl;

		switch (menuI) {
		case(1):
			int menuI2;
			std::cout << "\tMPF - Manager Personal Finance" << std::endl;
			std::cout << "1) ��������� �����" << std::endl;
			std::cout << "2) ��������� �����" << std::endl;
			std::cout << "��� �����: ";
			std::cin >> menuI2;
			std::cout << std::endl;

			if (menuI2 == 1) {
				std::cout << "\tMPF - Manager Personal Finance" << std::endl;
				std::cout << "1) �����" << std::endl;
				std::cout << "2) ������ ��������� ����" << std::endl;
				std::cout << "3) �������� ����� ��������� �����" << std::endl;
				std::cout << "4) ��������� �����" << std::endl;
				std::cout << "��� �����: ";
				std::cin >> menuI2;
				std::cout << std::endl;
				if (menuI2 == 1) {
					std::cout << "\tMPF - Manager Personal Finance" << std::endl;
					std::cout << "����� ����� �������: " << wallet.getAllCreditMoney() << std::endl;
					std::cout << "����� ����� ������: " << wallet.getAllCreditLim() << std::endl;
					std::cout << "����� ����� �����: " << wallet.getAllCreditDebt() << std::endl;
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
					std::cout << "������� �����(�� ����� � ������) ����� �����: ";
					std::cin >> i;

					std::cout << "������� ����� ����������: ";
					std::cin >> sum;
					(wallet.getCreditCard(i-1)).addMoney(sum);
					std::cout << std::endl;

				}
				else {
					std::cerr << "������� ������������ ��������!!!" << std::endl;
				}

			}
			else if (menuI2 == 2) {

				std::cout << "\tMPF - Manager Personal Finance" << std::endl;
				std::cout << "1) �����" << std::endl;
				std::cout << "2) ������ ��������� ����" << std::endl;
				std::cout << "3) �������� ����� ��������� �����" << std::endl;
				std::cout << "4) ��������� �����" << std::endl;
				std::cout << "��� �����: ";
				std::cin >> menuI2;
				std::cout << std::endl;
				if (menuI2 == 1) {
					std::cout << "\tMPF - Manager Personal Finance" << std::endl;
					std::cout << "����� ����� �������: " << wallet.getAllDebtMoney() << std::endl;
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
					std::cout << "������� �����(�� ����� � ������) ����� �����: ";
					std::cin >> i;

					std::cout << "������� ����� ����������: ";
					std::cin >> sum;
					(wallet.getDebtCard(i-1)).addMoney(sum);
					std::cout << std::endl;

				}
				else {
					std::cerr << "������� ������������ ��������!!!" << std::endl;
				}

			}
			else {
				std::cerr << "������� ������������ ��������!!!" << std::endl;
			}
			break;
		case(2):
		{//<-- ����� ��� ������� �������� � �������������� newPurch
			char pName[sizeP];
			char pCategory[sizeP];
			int pSum;

			std::cout << "\tMPF - Manager Personal Finance" << std::endl;
			std::cout << "������� ������������ �������: " << std::endl;
			std::cin >> pName;
			std::cout << "������� ��������� �������: " << std::endl;
			std::cin >> pCategory;
			std::cout << "������� ����� �������: " << std::endl;
			std::cin >> pSum;
			Purchase newPurch{ pSum, pName, pCategory };
			std::cout << std::endl;

			int menuI3;
			std::cout << "\tMPF - Manager Personal Finance" << std::endl;
			std::cout << "�������� ������ ������ ���� �� �������� �����: " << std::endl;
			std::cout << "1) ��������� ������" << std::endl;
			std::cout << "2) ��������� ������" << std::endl;
			std::cout << "��� �����: ";
			std::cin >> menuI3;
			std::cout << std::endl;
			if (menuI3 == 1) {
				int i{};
				std::cout << "\tMPF - Manager Personal Finance" << std::endl;

				wallet.printCredit();
				std::cout << "������� �����(�� ����� � ������) ����� �����: ";
				std::cin >> i;
				(wallet.getCreditCard(i - 1)).doPurchase(newPurch);
				std::cout << std::endl;
			}
			else if (menuI3 == 2) {
				int i{};
				std::cout << "\tMPF - Manager Personal Finance" << std::endl;

				wallet.printDebtCards();
				std::cout << "������� �����(�� ����� � ������) ����� �����: ";
				std::cin >> i;
				(wallet.getDebtCard(i - 1)).doPurchase(newPurch);
				std::cout << std::endl;

			}
			else {
				std::cerr << "������� ������������ ��������!!!" << std::endl;
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
		1) �����
		1.1) ���������
		1.2) ���������
		2) �������� �������
		3) ������
		4) ���������� ����������
		*/

	}

	

}

int main(){
	setlocale(LC_ALL, "Russian");
	
	Wallet wal{ 0, 1};

	Interface(wal);

	

	 
	//char numCard1[sizeN]{"123543"};//����� ����� ��� ������������� ����
	//char numCard2[sizeN]{ "1488" };//����� ����� ��� ������������� ����

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