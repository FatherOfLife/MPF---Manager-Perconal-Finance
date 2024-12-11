#include <iostream>

class Wallet { // ����� ��� �������� ����� � �� �������� ����� ���������� ����� ����� �������, �����, �����
private:
	//������������ ������ ���� ��������� � ���������
public:
	//������ ����� ����� �������, �����, �����

};

class Card {
protected:
	const char* number; //����� �����
	int amountOfMoney; // ����� ����� �� �����
public:



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


class Debt : protected Card {
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
	Debt(const char* number_p, int amountOfMoney_p) {
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



	const char* getNum() { // �������� ����� ��������
		return number;
	}

	int getMoney() { // �������� ���������� ����� �� ��������
		return amountOfMoney;
	}


	void setNum(const char* number_p) { // ��������� ����� ��������
		number = number_p;
	}

	void setMoney(int amountOfMoney_p) { // ��������� ���������� ����� �� ��������
		amountOfMoney = amountOfMoney_p;
	}

};

class Credit : protected Card {
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


	void doPurchase(Purchase purch) { //�������� �������(��������� ������ � ��������)
		amountOfMoney = amountOfMoney - purch.getSum();
		if (amountOfMoney < 0) {
			debt = -amountOfMoney;
		}
		if (lim()) {
			std::cout << "�� ��������� ����� ������� �� " << (debt - creditLim) << " ������ ( ����� �������: " << creditLim << ", ��� ����: " << debt << " )" << std::endl;
		}

	}



	const char* getNum() { // �������� ����� ��������
		return number;
	}

	int getMoney() { // �������� ���������� ����� �� ��������
		return amountOfMoney;
	}

	int getCreditLim() { // �������� ����� ������ �������
		return amountOfMoney;
	}

	int getDebt() { // �������� ����� �����
		return amountOfMoney;
	}

	
	void setNum(const char* number_p) { // ��������� ����� ��������
		number = number_p;
	}

	void setMoney(int amountOfMoney_p) { // ��������� ���������� ����� �� ��������
		amountOfMoney = amountOfMoney_p;
	}
	void setCreditLim(int creditLim_p) { // ��������� ����� ������ �������
		creditLim = creditLim_p;
	}
	void setDebt(int debt_p) { // ��������� ����� �����
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