#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

#include <cctype>



class String {
	int length;                              //rozmiar tablicy

public:
	char* wsk;                               //tablica
	String() : wsk(nullptr), length(0) {}
	String(const char* str) {
		length = std::strlen(str) + 1;
		wsk = new char[length];
		std::strcpy(wsk, str);
	}

	String(int integer) {
		int length = snprintf(nullptr, 0, "%d", integer);

		this->length = length + 1;
		wsk = new char[this->length];

		sprintf(wsk, "%d", integer);
	}
	String(char znak) {
		length = 2;
		wsk = new char[length];
		wsk[0] = znak;
		wsk[1] = '\0';
	}

	String(const String& other) {
		length = other.length;
		wsk = new char[length + 1];
		strcpy(wsk, other.wsk);
	}
	void wypisz() {
		printf("%s", wsk);
	}
	~String() {
		delete[] wsk; // Zwolnienie zaalokowanej pamiêci
	}
	int get_length() {
		return strlen(wsk);
	}
	String& operator+=(const char* str) {
		if (strlen(str) + strlen(wsk) + 1 > length) {
			char* newWsk = new char[length + strlen(str) + 10];
			std::strcpy(newWsk, wsk); // Skopiowanie danych z obecnego obiektu
			std::strcat(newWsk, str); // Do³¹czenie napisu str na koniec
			delete[]wsk;
			wsk = newWsk;
			length = length + strlen(str) + 30;
		}
		else {
			std::strcat(wsk, str);
		}
		return *this;

	}
	String& operator+=(const char str) {
		int dlugosc;
		if (strlen(wsk) + 2 > length) {
			char* newWsk = new char[length + 10];
			std::strcpy(newWsk, wsk); // Skopiowanie danych z obecnego obiektu
			newWsk[strlen(wsk)] = str;
			newWsk[strlen(wsk) + 1] = '\0';
			delete[]wsk;
			wsk = newWsk;
			length = length + 30;

		}
		else {
			dlugosc = strlen(wsk);
			wsk[dlugosc] = str;
			wsk[dlugosc + 1] = '\0';
		}
		return *this;

	}

	String& operator+=(int liczba) {
		char temp[20];
		std::sprintf(temp, "%d", liczba);
		*this += temp;
		return *this;
	}
	String& operator=(const char* str) {
		delete[] wsk;
		length = std::strlen(str) + 1;
		wsk = new char[length];
		std::strcpy(wsk, str);
		return *this;
	}
	String& operator=(const char znak) {
		delete[] wsk;
		length = 2;
		wsk = new char[2];
		wsk[0] = znak;
		wsk[1] = '\0';
		return *this;
	}
	String& operator=(const String& other) {
		if (this != &other) {
			delete[] wsk;
			length = other.length;
			wsk = new char[length];
			std::strcpy(wsk, other.wsk);
		}
		return *this;
	}
	int get_size() {
		return length;
	}
	char& operator[](int index) {
		return wsk[index];
	}
	void clear() {
		delete[] wsk;
		wsk = new char[1];
		wsk[0] = '\0';
		length = 1;
	}
	bool isNumber() const {
		if (length == 0) {
			return false;
		}

		return std::isdigit(wsk[0]) != 0;
	}
};


template<typename T>

class Node {
public:
	T value;
	Node* next;

	Node(T val) :
		value(val), next(nullptr) {}
};


template<typename T>
class Stos {
private:
	Node<T>* lastNode;
public:
	Stos() : lastNode(nullptr) {}


	bool isEmpty() const {
		return lastNode == nullptr;
	}

	void push(T val) {
		Node<T>* newNode = new Node<T>(val);
		newNode->next = lastNode;
		lastNode = newNode;
	}

	void wypiszStos() {                //tylko dla intow
		Node<T>* current = lastNode;
		while (current != nullptr) {
			printf("%d ", current->value);
			current = current->next; 
		}
		printf("\n");
	}

	T pop() {
		T val = lastNode->value;
		Node<T>* temp = lastNode;
		lastNode = lastNode->next;
		delete temp;

		return val;
	}
	T top() const {
		if (!isEmpty()) {
			return lastNode->value;
		}
		else {
			std::cerr << "Stos jest pusty!" << std::endl;
			return T(); // Zwraca domyœln¹ wartoœæ dla typu T
		}
	}

};


template<typename T>
class Kolejka {
private:
	Node<T>* lastNode;
	Node<T>* firstNode;
public:
	Kolejka() : lastNode(nullptr), firstNode(nullptr) {}
	
	~Kolejka() {
		clear();
	}

	bool isEmpty() const {
		return firstNode == nullptr;
	}

	void push(const String& str) {
		Node<T>* newNode = new Node<T>(str);
		if (isEmpty()) {
			firstNode = lastNode = newNode;
		}
		else {
			lastNode->next = newNode;
			lastNode = newNode;
		}
	}

	void dodajDoOstatniego(int liczba) {
		lastNode ->value+= liczba;
	}
	String pop() {
		if (isEmpty()) {
			std::cerr << "Kolejka jest pusta!" << std::endl;
			return -1;
		}
		Node<T>* temp = firstNode;
		firstNode = firstNode->next;

		if (firstNode == nullptr) {
			lastNode = nullptr;
		}
		T value = temp->value;
		delete temp;
		return value;
	}
	int pop_and_convert() {
		if (isEmpty()) {
			std::cerr << "Kolejka jest pusta!" << std::endl;
			return -1; // Zwraca -1, gdy kolejka jest pusta
		}

		String value = firstNode->value;
		if (value.isNumber()) { // Jeœli pierwszy element jest liczb¹
			int number = std::atoi(value.wsk); // Konwertuje ci¹g znaków na liczbê ca³kowit¹

			Node<T>* temp = firstNode;
			firstNode = firstNode->next;
			if (firstNode == nullptr) {
				lastNode = nullptr;
			}
			delete temp;
			return number; // Zwraca wartoœæ liczbow¹
		}
		else {
			std::cerr << "Pierwszy element nie jest liczb¹!" << std::endl;
			return -1; 
		}
	}
	void wypiszKolejke() {                //tylko dla Stringow
		if (firstNode == nullptr) {
			std::cout << "Queue is empty\n";
			return;
		}

		Node<T>* temp = firstNode;
		while (temp != nullptr) {
			temp->value.wypisz();
			printf(" ");
			temp = temp->next;
		}
	}
	String first() const {
		if (!isEmpty()) {
			return firstNode->value;
		}
		else {
			std::cerr << "Kolejka jest pusta!" << std::endl;
			return String(); // Zwraca domyœln¹ wartoœæ dla typu String
		}
	}
	void clear() {
		while (firstNode != nullptr) {
			Node<T>* temp = firstNode;
			firstNode = firstNode->next;
			delete temp;
		}
		lastNode = nullptr; 
	}
};



int add_to_stack(const char& znak, Stos<char>& stos, Kolejka<String>&kolejka);
int priorytet(const char& znak);
void calculate(Kolejka<String>& kolejka);
int convertToONP(Stos<char>& stos, Kolejka<String>& kolejka);



int main() {
	int n = 0;
	std::cin >> n;
	Stos<char> stos;
	Kolejka<String> ONP;
	for (int i = 0; i < n; i++) {
		convertToONP(stos, ONP);
		if (!stos.isEmpty()) {
			ONP.push(stos.pop());
		}
		while (!stos.isEmpty()) {
			ONP.push(stos.pop());
		}
		
		ONP.wypiszKolejke();
		calculate(ONP);
		if (!ONP.isEmpty()) {
			ONP.clear(); 
		}
		printf("\n");
	}
	

	return 0;
}
int convertToONP(Stos<char>& stos, Kolejka<String>& kolejka) {
	int ile_przecinkow = 0, l_arg, liczba;
	char znak = '\0';
	bool ciagla = false;

	while (znak != '.') {
		if (scanf("%c", &znak)) {
			switch (znak) {
			case ' ':
				if (ciagla) {
					kolejka.push(liczba);
					ciagla = false;
				}
				break;
			case ',':
				ile_przecinkow += 1;
				while (stos.top() != '(') {
					kolejka.push(stos.pop());
				}
				break;
			case 'X':
				stos.push('M');
				l_arg = convertToONP(stos, kolejka) + 1;
				stos.pop();

				kolejka.push("MAX");
				kolejka.dodajDoOstatniego(l_arg);
				ciagla = false;
				break;
			case 'I':
			case 'M':
			case 'A':
				ciagla = true;
				break;
			case 'N':
				if (ciagla == true) {
					stos.push('m');
					l_arg = convertToONP(stos, kolejka) + 1;
					stos.pop();
					kolejka.push("MIN");
					kolejka.dodajDoOstatniego(l_arg);
				}
				else {
					add_to_stack(znak, stos, kolejka);
				}
				ciagla = false;
				break;
			case 'F':
				stos.push('I');
				convertToONP(stos, kolejka);
				stos.pop();
				kolejka.push("IF");
				ciagla = false;
				break;
			default:
				if (znak != ' ' && znak != '.') {
					if (std::isdigit(znak)) {
						if (ciagla == false) {
							ciagla = true;
							liczba = znak - '0';

						}
						else
							liczba = liczba * 10 + (znak - '0');
					}
					else {
						if (add_to_stack(znak, stos, kolejka) == 1) {
							return ile_przecinkow;
						}
					}
				}
				break;
			}
		}
	}
	return 0;
}

int priorytet(const char& znak) {
	switch (znak) {
	case '(':
		return 0;
		break;
	case '-':
	case '+':
	case ')':
		return 1;
		break;
	case '*':
	case '/':
		return 2;
		break;
	case 'N':
		return 3;
		break;
	default:
		return -1;
		break;
	}
}

int add_to_stack(const char& znak, Stos<char>& stos, Kolejka<String>& kolejka) {
	if (stos.isEmpty()) {
		stos.push(znak);
	}
	else if (znak == '(') {
		stos.push('(');
	}
	else if (znak == ')') {
		while (stos.top() != '(') {
			kolejka.push(stos.pop());
		}
		stos.pop();
		if (stos.top() == 'N') {
			kolejka.push(stos.pop());
		}
		else if (stos.top() == 'M' || stos.top() == 'm' || stos.top() == 'I') {
			return 1;
		}
	}
	else if (znak == 'N') {
		stos.push(znak);
	}
	else {
		while (priorytet(stos.top()) >= priorytet(znak)) {
			kolejka.push(stos.pop());
		}
		stos.push(znak);
	}
	return 0;
}


void calculate(Kolejka<String>& kolejka) {
	Stos<int> stos_liczb;
	bool ciag = false, error = false;;
	int liczba, argumenty, sciagnieta1, sciagnieta2, sciagnieta3, minmax, i;
	String token;
	while (!kolejka.isEmpty() && error == false) {
		if (kolejka.first().isNumber()) {
			stos_liczb.push(kolejka.pop_and_convert());
		}
		else {
			token = kolejka.pop();
			switch (token[0]) {
			case '+':
				printf("+ ");
				stos_liczb.wypiszStos();
				sciagnieta1 = stos_liczb.pop();
				sciagnieta2 = stos_liczb.pop();
				sciagnieta1 += sciagnieta2;
				stos_liczb.push(sciagnieta1);
				break;
			case '-':
				printf("- ");
				stos_liczb.wypiszStos();
				sciagnieta1 = stos_liczb.pop();
				sciagnieta2 = stos_liczb.pop();
				sciagnieta2 -= sciagnieta1;
				stos_liczb.push(sciagnieta2);
				break;
			case '*':
				printf("* ");
				stos_liczb.wypiszStos();
				sciagnieta1 = stos_liczb.pop();
				sciagnieta2 = stos_liczb.pop();
				sciagnieta1 *= sciagnieta2;
				stos_liczb.push(sciagnieta1);
				break;
			case '/':
				printf("/ ");
				stos_liczb.wypiszStos();
				sciagnieta1 = stos_liczb.pop();
				sciagnieta2 = stos_liczb.pop();
				if (sciagnieta1 == 0) {
					error = true;
					break;
				}
				else {
					sciagnieta2 /= sciagnieta1;
					stos_liczb.push(sciagnieta2);
				}
				break;
			case 'N':
				printf("N ");
				stos_liczb.wypiszStos();
				sciagnieta1 = stos_liczb.pop();
				sciagnieta1 *= -1;
				stos_liczb.push(sciagnieta1);
				break;
			case 'I':
				printf("IF ");
				stos_liczb.wypiszStos();
				sciagnieta1 = stos_liczb.pop();
				sciagnieta2 = stos_liczb.pop();
				sciagnieta3 = stos_liczb.pop();
				if (sciagnieta3 > 0)
					stos_liczb.push(sciagnieta2);
				else
					stos_liczb.push(sciagnieta1);
				break;
			case 'M':
				argumenty = 0;
				if (token[1] == 'I') {
					printf("MIN");
					minmax = -1;
				}
				else {
					printf("MAX");
					minmax = 1;
				}
				i = 3;
				while (std::isdigit(token[i])) {
					if (ciag == false) {
						ciag = true;
						argumenty = token[i] - '0';
					}
					else
						argumenty = argumenty * 10 + (token[i] - '0');
					i++;
				}
				ciag = false;
				printf("%d ", argumenty);
				stos_liczb.wypiszStos();
				sciagnieta1 = stos_liczb.pop();
				if (minmax == 1) {
					for (int k = 0; k < argumenty - 1; k++) {
						sciagnieta2 = stos_liczb.pop();
						if (sciagnieta2 > sciagnieta1)
							sciagnieta1 = sciagnieta2;
					}
				}
				else if (minmax == -1) {
					for (int k = 0; k < argumenty - 1; k++) {
						sciagnieta2 = stos_liczb.pop();
						if (sciagnieta2 < sciagnieta1)
							sciagnieta1 = sciagnieta2;
					}
				}
				stos_liczb.push(sciagnieta1);
			}
		}
	}
	if (error == false) {
		stos_liczb.wypiszStos();
	}
	else
		printf("ERROR\n");
}

