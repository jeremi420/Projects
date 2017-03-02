//POP 2016-12-12 projekt 1 Wielewski Jeremi EIT 8 161317 Vsiual Studio Enterprise 2015

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <iostream>


using namespace std;


const int ROWS = 50;
const int COLUMNS = 80;
const double MAXPROMILE = 2.0;


enum plec { //enum ktory zawiera stala k jako liczba calkowita ktora potem zostanie podzielona na 10
	m = 7,
	k = 6
};

struct osoba {
	double mgAlkoholu;
	double promile;
	int waga;
	plec plec;
};

enum procenty { //enum ktory zawiera procentowa zawartosc alkoholu dla roznych typow alkoholi
	wodka = 40,
	wino = 16,
	piwo = 6
};

struct czas
{
	int godzina;
	int minuty;
};

struct alkohol {
	procenty typ;
	int ilosc;
	czas czas_spozycia;
};


void UstawGodzine(char* godzina, alkohol* alkohol);//wszystkie funkcje z "Ustaw" w nazwie zapisuja informacje o odpowiednio spozytym alkoholu badz osobie
void UstawIlosc(char* ilosc, alkohol* alkohol); //zmienne przekazywane sa jako wskazniki tak aby mogly byc zmieniane w funkcjach
void UstawTyp(char* typ, alkohol* alkohol);
void UstawMase(char* masa, osoba* osoba);
void UstawPlec(char* plec, osoba* osoba);
void Input(char inputArray[], osoba* osoba, alkohol* array, int arraySize);
void ZnajdzTyp(char** typ, alkohol* alkohol);
int ZnajdzDlugosc(int liczba);
void ObliczCzasWytrzezwienia(alkohol* array, osoba* osoba, czas* czas_wytrzezwienia);
void RysujTabele(alkohol* array, int size, czas czas_wytrzezwienia);
bool CzyRowne(double a, double b);
void RysujWykres(alkohol* array, osoba* osoba, czas czas_wytrzezwienia);


int main() {
	osoba osoba = {0.0,0.0}; //tworzy nowa osobe ktora na poczatku ma zero promili oraz zero mg alkoholu
	int size = 0;
	char inputArray[256];
	cin.getline(inputArray, 256); //wczytywanie calej lini do tablicy charow
	for (int i = 0; i < strlen(inputArray); i++) {
		if (inputArray[i] == ',') { // na podstawie ilosci przecinkow na wejsciu jestesmy w stanie stwierdzic ile razy osoba pila alkohol
			size++;
		}
	}
	system("CLS");
	alkohol* array = new alkohol[size]; // tworzymy tablice ktora bedzie zawierala informacje o kazdym zpozytym alkoholu
	czas czas_wytrzezwienia;
	Input(inputArray, &osoba, array, size);
	ObliczCzasWytrzezwienia(array, &osoba, &czas_wytrzezwienia);
	RysujTabele(array,size,czas_wytrzezwienia);
	RysujWykres(array, &osoba, czas_wytrzezwienia);
	system("PAUSE");
	return 0;
}

void UstawGodzine(char* godzina, alkohol* alkohol) {
	char* godziny = new char[2];
	char* minuty = new char[2];
	strncpy(godziny, godzina, 2); //pierwsze dwa znaki z napisu zostaja zapisane jako godzina
	strncpy(minuty, godzina + 2, 2); // a dwa kolejne jako minuty
	alkohol->czas_spozycia.godzina = atoi(godziny);
	alkohol->czas_spozycia.minuty = atoi(minuty);
}

void UstawIlosc(char* ilosc, alkohol* alkohol) { //ustawia ilosc danego wypitego alkoholu
	alkohol->ilosc = atoi(ilosc);
}

void UstawTyp(char* typ, alkohol* alkohol) {
	if ((string)typ == "wodka") {
		alkohol->typ = wodka;
	}
	else if ((string)typ == "piwo") {
		alkohol->typ = piwo;
	}
	else if ((string)typ == "wino") {
		alkohol->typ = wino;
	}
}

void UstawMase(char* masa, osoba* osoba) {
	osoba->waga = atoi(masa);
}

void UstawPlec(char* plec, osoba* osoba) {//funkcja ustawia plec danej osoby na podstawie tkestu
	if ((string)plec == "Mezczyzna") {
		osoba->plec = m;
	}
	else if ((string)plec == "Kobieta") {
		osoba->plec = k;
	}
}

void Input(char inputArray[], osoba* osoba, alkohol* array, int arraySize) { //funkcja ustawa tablice informacji o wypitym alkoholu oraz informacje o osobie na podstawie lini wejscia
	char* wartosci = strtok(inputArray, ":, "); // wejsciowa tablica jest dzielona znakami ":" "," oraz spacja
	char** tablica = new char*[arraySize*4 + 3]; // tablica bêdzie przechowywa³a wszystkie oddzielone informacje
	int index = 0;
	while (wartosci) {
		tablica[index] = wartosci;
		index++;
		wartosci = strtok(NULL, ":, ");
	}                             //funkcje ustawiaja podstawowe informacje o osobie ktore sa przechowywane w tablicy
	UstawPlec(tablica[0], osoba); //pierwszy element tablicy przechowuje informacje o plci a drugi slowo "waga" dlatego nie jest zapisywany
	UstawMase(tablica[2], osoba); //trzeci element zawiera informacje o wadze osoby
	index = 0;
	for (int i = 3; i < arraySize*4 + 3; i += 4) { //od czwartego elementu tablicy zaczynaja sie informacje o wypitym alkoholu
		UstawTyp(tablica[i], &array[index]);       //informacje o kazdym wypitym alkoholu zajmuja 4 elemety tablicy
		UstawIlosc(tablica[i + 1], &array[index]); //pierwszy zawiera typ, drugi ilosc, trzeci pojedyncza literke "g" (dlatego nie jest zapisywana)
		UstawGodzine(tablica[i + 3], &array[index]); //czwarty zaiwera informacje o godzinie spozycia
		index++;
	}
}
void ZnajdzTyp(char** typ, alkohol* alkohol) {
	if (alkohol->typ == procenty::wodka) {
		*typ = "wodka";
	}
	else if (alkohol->typ == procenty::wino) {
		*typ = "wino";
	}
	else if (alkohol->typ == procenty::piwo) {
		*typ = "piwo";
	}
}
int ZnajdzDlugosc(int liczba) { //funckja znajduje ilosc znakow danej liczby
	int dlugosc = 0;
	do {
		dlugosc++;
		liczba /= 10;
	} while (liczba);
	return dlugosc;
}

void ObliczCzasWytrzezwienia(alkohol* array, osoba* osoba, czas* czas_wytrzezwienia) {
	int i = 0;
	czas aktualny_czas{ array[0].czas_spozycia.godzina,  array[0].czas_spozycia.minuty - 15 }; //na poczatku czas zostaje ustawiony na czas spozycia pierwszego alkoholu zmniejszony o 15 minut
	do {
		aktualny_czas.minuty += 15; //krokiem czasowym funkcji jest 15, po wykonaniu instrukcji za pierwszym razem aktualny czas bedzie rowny czasu spozycia pierwszego alkoholu
		if (aktualny_czas.minuty == 60) {
			aktualny_czas.godzina++; //dwie instrukcje warunkowe sprawiaja ze minuty nie przekrocza 60 a godziny 24
			if (aktualny_czas.godzina == 24) {
				aktualny_czas.godzina = 0;
			}
			aktualny_czas.minuty = 0;
		}
		if (aktualny_czas.godzina == array[i].czas_spozycia.godzina && aktualny_czas.minuty == array[i].czas_spozycia.minuty) {
			osoba->mgAlkoholu += array[0].ilosc*array[0].typ/100*0.79; //jezeli aktualna godzina jest godzina spozycia alkholu to musimy zaktualowac ilosc promili
			osoba->promile = osoba->mgAlkoholu / (osoba->waga*osoba->plec/10.0);
			i++;
		}
		osoba->mgAlkoholu -= 2.0; //osoba usuwa 8g alkoholu na godzine czyli 2 na 15 minut
		if (osoba->mgAlkoholu < 0.0) {
			osoba->mgAlkoholu = 0.0; //jezeli wartosc promili spadnie lekko ponizej 0 to znaczy ze osoba wytrzezwiala
			*czas_wytrzezwienia = aktualny_czas; //funkcja zwraca czas wytrzezwienia
		}
		osoba->promile = osoba->mgAlkoholu / (osoba->waga*osoba->plec/10.0);
	} while (osoba->promile>0.0);
}

void RysujTabele(alkohol* array, int size, czas czas_wytrzezwienia) {
	cout << "+-------------------+--------------+" << endl;//trzy pierwsze instrukcje cout rysuja naglowek tabeli
	cout << "|  rodzaj alkoholu  |  ilosc (ml)  |" << endl;
	cout << "+-------------------+--------------+" << endl;
	for (int i = 0; i < size; i++) { 
		char* typ = new char[20];
		ZnajdzTyp(&typ, &array[i]); //funkcja znajduje typ jako tekst na podstawie liczbowej wartosci enum "typ"
		cout << "|  " << typ; //wypisanie lewej krawedzi oraz typu alkoholu
		for (int j = 0; j < 17 - strlen(typ); j++) { //funkcja dostosowuje ilosc spacji do dlugosci napisu
			cout << " ";
		}
		cout << "|  " << array[i].ilosc; //wypisanie srodkowej krawedzi oraz ilosci podanego alkoholu
		for (int j = 0; j < 12 - ZnajdzDlugosc(array[i].ilosc); j++) { //funkcja dostosowuje ilosc spacji do dlugosci liczby
			cout << " ";
		}
		cout << "|" << endl; //wypisanie prawej krawedzi
		cout << "+-------------------+--------------+" << endl; //wypisanie poziomej linii tabeli
	}
	cout << "+-------------------+--------------+" << endl; //podwojna pozioma linia oddziela czas wwytrzezwienia od tabeli z alkoholami
	cout << "+czas wytrzezwienia |  ";
	if (czas_wytrzezwienia.godzina < 10) {
		cout << "0";
	}
	cout << czas_wytrzezwienia.godzina << ":"; //godziny sa odzielane od minut przecinkiem
	if (czas_wytrzezwienia.minuty < 10) {
		cout << "0";
	}
	cout << czas_wytrzezwienia.minuty << "       |" << endl;
	cout << "+-------------------+--------------+" << endl;
}

bool CzyRowne(double a, double b) { // funkcja sprawdza czy dwie zmienne typu double sa rowne gdyz operator == moze generowac bledy
	double odleglosc;
	if (a - b > 0.0) {     //instrukcja sprawdza ktora liczba jest wieksza
		odleglosc = a - b; //a potem odejmuje liczbê mniejsza od wiekszej aby znalezc odleglosc miedzy nimi
	}
	else {
		odleglosc = b - a;
	}
	if (odleglosc < 0.001) { //jezeli odleglosc jest bardzo mala to mozemy zalozyc ze liczby sa rowne
		return true;
	}
	else {
		return false;
	}
}

void RysujWykres(alkohol* array, osoba* osoba, czas czas_wytrzezwienia) {
	int i = 0, index = 0;
	double krok = MAXPROMILE / ROWS;
	double promile[COLUMNS];
	double odleglosc, minimalna = MAXPROMILE;
	czas aktualny_czas{ array[0].czas_spozycia.godzina,  array[0].czas_spozycia.minuty - 15 };
	do {
		aktualny_czas.minuty += 15;
		if (aktualny_czas.minuty == 60) {
			aktualny_czas.godzina++;
			if (aktualny_czas.godzina == 24) {
				aktualny_czas.godzina = 0;
			}
			aktualny_czas.minuty = 0;
		}
		if (aktualny_czas.godzina == array[i].czas_spozycia.godzina && aktualny_czas.minuty == array[i].czas_spozycia.minuty) {
			osoba->mgAlkoholu += array[0].ilosc*array[0].typ / 100 * 0.79;
			osoba->promile = osoba->mgAlkoholu / (osoba->waga*osoba->plec / 10.0);
			i++;
		}
		osoba->mgAlkoholu -= 2.0;
		if (osoba->mgAlkoholu < 0.0) {
			osoba->mgAlkoholu = 0.0;
		}
		osoba->promile = osoba->mgAlkoholu / (osoba->waga*osoba->plec / 10.0);
		minimalna = MAXPROMILE;
		for (double j = 0.0; j <= MAXPROMILE; j += krok) {
			if (osoba->promile - j >0) {
				odleglosc = osoba->promile - j;
			}
			else {
				odleglosc = j - osoba->promile;
			}
			if (odleglosc < minimalna) {
				minimalna = odleglosc;
				promile[index] = j;
			}
		}
		index++;
	} while (osoba->promile>0.0);
	for (int i = ROWS; i >= 0; i--) {
		cout << "|";
		for (int j = 0; j <index; j++) {
			if (CzyRowne((krok*i), promile[j])) {
				cout << "*";
			}
			else {
				cout << " ";
			}
		}
		cout << endl;
	}
	cout << "+";
	for (int i = 0; i < COLUMNS; i++) {
		cout << "-";
	}
	cout << endl;
}