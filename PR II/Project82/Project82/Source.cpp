#include <iostream>
using namespace std;


/****************************************************************************
1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR
2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA KOJI UZROKUJU RUNTIME ERROR CE BITI OZNACENO KAO "RE"
3. SPAŠAVAJTE PROJEKAT KAKO BI SE SPRIJECILO GUBLJENJE URAÐENOG ZADATKA
4. NAZIVI FUNKCIJA, TE BROJ I TIP PARAMETARA MORAJU BITI IDENTICNI ONIMA KOJI SU KORIŠTENI U TESTNOM CODE-U, OSIM U SLUCAJU DA POSTOJI ADEKVATAN RAZLOG ZA NJIHOVU MODIFIKACIJU. OSTALE, POMOCNE FUNKCIJE MOŽETE IMENOVATI I DODAVATI PO ŽELJI.
5. BEZ OBZIRA NA TO DA LI SU ISPITNI ZADACI URAÐENI, SVI STUDENTI KOJI SU PRISTUPILI ISPITU MORAJU PREDATI SVOJ RAD
6. ZA POTREBE TESTIRANJA, UNUTAR MAIN FUNKCIJE MOZETE DODAVATI NOVE TESTNE PODATKE
****************************************************************************/
//narednu liniju code-a ignorisite, osim u slucaju da vam bude predstavljala smetnje u radu
#pragma warning(disable:4996)

auto * crt = "\n----------------------------------------------------\n";
class Datum {
	int * _dan, *_mjesec, *_godina;
public:
	Datum(int d, int m, int g) {
		_dan = new int(d);
		_mjesec = new int(m);
		_godina = new int(g);
	}
	Datum(const Datum& original) {
		_dan = new int(*original._dan);
		_mjesec = new int(*original._mjesec);
		_godina = new int(*original._godina);
	}
	Datum() :_dan(nullptr), _mjesec(nullptr), _godina(nullptr) {}
	~Datum() {
		delete _dan; _dan = nullptr;
		delete _mjesec; _mjesec = nullptr;
		delete _godina; _godina = nullptr;
	}
	friend ostream & operator<<(ostream & COUT, const Datum& obj) {
		COUT << *obj._dan << " / " << *obj._mjesec << " / " << *obj._godina << endl;
		return COUT;
	}
	Datum& operator=(const Datum& original) {
		if (this != &original) {
			delete _dan;
			delete _mjesec;
			delete _godina;
			_dan = new int(*original._dan);
			_mjesec = new int(*original._mjesec);
			_godina = new int(*original._godina);
		}
		return *this;
	}
};

template<class T, int velicina>
class FITArray {
	T _niz[velicina];
	int _trenutno;
	bool _dozvoliDupliciranje;
public:
	//OSTALE FUNKCIJE CLANICE DEFINISATI VAN TEMPLATE KLASE
	FITArray(bool dozvoliDupliciranje = true) { _dozvoliDupliciranje = dozvoliDupliciranje; _trenutno = 0; }
	int GetTrenutno() { return _trenutno; }
	T * GetNiz() { return _niz; }
	bool operator+=(const T& novi);
	bool operator-=(const T& novi);
	friend ostream& operator<< <>(ostream&, const FITArray&);
	FITArray operator()(int, int);
};

template<class T, int velicina>
bool FITArray<T, velicina>::operator+=(const T& novi) {
	if (!_dozvoliDupliciranje) {
		for (int i = 0; i < _trenutno; i++) {
			if (_niz[i] == novi)
				return false;
		}
	}
	_niz[_trenutno++] = novi;
	return true;
}

template<class T, int velicina>
ostream& operator<< <>(ostream& ispis, const FITArray<T, velicina>& fit) {
	for (int i = 0; i < fit._trenutno; i++)
		ispis << fit._niz[i];
	ispis << endl;
	return ispis;
}

template<class T, int velicina>
bool FITArray<T, velicina>::operator-=(const T& obj) {
	for (int i = 0; i < _trenutno; i++) {
		if (_niz[i] == obj) {
			for (int j = i; j < _trenutno; j++) {
				_niz[j] = _niz[j + 1];
			}
			_trenutno--;
			return true;
		}
	}
	return false;

}

template<class T, int velicina>
FITArray<T, velicina> FITArray<T, velicina>::operator()(int OD, int DO) {
	FITArray<T, velicina> temp;
	if (OD<0 || OD>_trenutno || DO<0 || DO>_trenutno)
		return temp;
	temp._trenutno = DO - OD;
	int br = 0;
	for (int i = OD; i < DO; i++)
		temp._niz[br++] = _niz[i];
	return temp;
}

class PolozeniPredmet {
	char * _naziv;
	int _ocjena;
	Datum _datumPolaganja;
public:
	PolozeniPredmet(const Datum& datum, const char* naziv, int ocjena) :_datumPolaganja(datum), _ocjena(ocjena) {
		int vel = strlen(naziv) + 1;
		_naziv = new char[vel];
		strcpy_s(_naziv, vel, naziv);
	}
	PolozeniPredmet() :_naziv(nullptr), _ocjena(0) {}
	~PolozeniPredmet() { delete[] _naziv; _naziv = nullptr; }
	friend ostream & operator<<(ostream & COUT, const  PolozeniPredmet & obj) {
		COUT << obj._naziv << " (" << obj._ocjena << ") " << obj._datumPolaganja << endl;
		return COUT;
	}
	friend bool operator==(const PolozeniPredmet&, const PolozeniPredmet&);
	PolozeniPredmet& operator=(const PolozeniPredmet& original) {
		if (this != &original) {
			delete[] _naziv;
			int vel = strlen(original._naziv) + 1;
			_naziv = new char[vel];
			strcpy_s(_naziv, vel, original._naziv);
			_ocjena = original._ocjena;
			_datumPolaganja = original._datumPolaganja;
		}
		return *this;

	}
	int GetOcjena() { return _ocjena; }
};
bool operator==(const PolozeniPredmet& p1, const PolozeniPredmet& p2) {
	if (strcmp(p1._naziv, p2._naziv) == 0)
		return true;
	return false;

}

class Student {
	static int _indeksCounter; //sluzi za odredjivanje narednog broja indeksa koji ce biti dodijeljen studentu, pocevsi od 160000
	const int _indeks;
	char * _imePrezime;
	FITArray<PolozeniPredmet, 40> _polozeniPredmeti;
public:
	Student(const char* imePrezime) :_indeks(_indeksCounter++) {
		int vel = strlen(imePrezime) + 1;
		_imePrezime = new char[vel];
		strcpy_s(_imePrezime, vel, imePrezime);
	}
	~Student() {
		delete[] _imePrezime; _imePrezime = nullptr;
	}
	friend ostream & operator<<(ostream & COUT, Student & obj) {
		COUT << obj._indeks << "  " << obj._imePrezime << endl << obj._polozeniPredmeti;
		return COUT;
	}
	void DodajPredmet(const PolozeniPredmet& polozeniPredmet) {
		_polozeniPredmeti += polozeniPredmet;
	}
	float GetProsjek() {
		float suma = 0;
		for (int i = 0; i < _polozeniPredmeti.GetTrenutno(); i++)
			suma += _polozeniPredmeti.GetNiz()[i].GetOcjena();
		return suma / _polozeniPredmeti.GetTrenutno();

	}
	Student& operator=(Student& student) {
		if (this != &student) {
			delete[] _imePrezime;
			int vel = strlen(student._imePrezime) + 1;
			_imePrezime = new char[vel];
			strcpy_s(_imePrezime, vel, student._imePrezime);
			for (int i = 0; i < student._polozeniPredmeti.GetTrenutno(); i++)
				_polozeniPredmeti += student._polozeniPredmeti.GetNiz()[i];
		}
		return *this;
	}
};
int Student::_indeksCounter = 160000;

int main() {
	const int max = 20;

	Datum jucer(20, 11, 2017), danas(21, 11, 2017), sutra(22, 11, 2017);
	cout << jucer << danas << sutra << endl;
	jucer = danas;
	cout << jucer << danas << sutra << endl;

	//parametar tipa bool odredjuje da li je u nizu dozvoljeno dupliciranje elemenata
	FITArray<int, max> nizIntegera(false);

	for (size_t i = 0; i < max - 1; i++)
		nizIntegera += i;//dodaje novog clana niza

	if (!(nizIntegera += 6))//pokusavamo dodati dupli clan niza
		cout << "Element nije dodan u niz" << endl;

	cout << crt << nizIntegera << crt; //ispisuje sve clanove niza
	nizIntegera -= 9; //uklanja clan niza sa vrijednoscu 9
	nizIntegera -= 17;

	FITArray<int, max> noviNizIntegera(nizIntegera);
	cout << crt << noviNizIntegera << crt;

	/*parametri odredjuju lokacije (indekse u nizu) elemenata OD - DO koje je potrebno vratiti. u slucaju da u nizu
	ne postoji trazeni broj elemenata funkcija treba da vrati sve element od lokacije OD pa do posljednje dostupnog elementa */

	cout << "Clanovi niza od lokacije 2 do lokacije 5 su -> " << noviNizIntegera(2, 5) << crt;

	Student adel("Adel Handzic"), jasmin("Jasmin Azemovic");

	PolozeniPredmet prII(jucer, "PRII", 8), prIII(sutra, "PRIII", 7), BPI(danas, "BPI", 8), ASP(jucer, "ASP", 9);

	adel.DodajPredmet(prII);
	adel.DodajPredmet(prIII);
	adel.DodajPredmet(BPI);
	adel.DodajPredmet(ASP);
	cout << adel << endl;
	//vraca prosjecnu ocjenu studenta
	cout << "Prosjecna ocjena -> " << adel.GetProsjek() << crt;

	jasmin = adel;
	cout << jasmin << endl;
	cout << "Prosjecna ocjena -> " << jasmin.GetProsjek() << crt;
	system("pause>0");
	return 0;
}