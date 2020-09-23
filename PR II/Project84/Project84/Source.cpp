#include <iostream>
/****************************************************************************
1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR
2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA KOJI UZROKUJU RUNTIME ERROR CE BITI OZNACENO KAO "RE"
3. SPAŠAVAJTE PROJEKAT KAKO BI SE SPRIJECILO GUBLJENJE URAÐENOG ZADATKA
4. NAZIVI FUNKCIJA, TE BROJ I TIP PARAMETARA MORAJU BITI IDENTICNI ONIMA KOJI SU KORIŠTENI U TESTNOM CODE-U, OSIM U SLUCAJU DA POSTOJI ADEKVATAN RAZLOG ZA NJIHOVU MODIFIKACIJU. OSTALE, POMOCNE FUNKCIJE MOŽETE IMENOVATI I DODAVATI PO ŽELJI.
5. BEZ OBZIRA NA TO DA LI SU ISPITNI ZADACI URAÐENI, SVI STUDENTI KOJI SU PRISTUPILI ISPITU MORAJU PREDATI SVOJ RAD
6. ZA POTREBE TESTIRANJA, UNUTAR MAIN FUNKCIJE MOZETE DODAVATI NOVE TESTNE PODATKE
****************************************************************************/
using namespace std;

const char * crt = "\n------------------------------------\n";

char * AlocirajNizKaraktera(const char * sadrzaj) {
	if (sadrzaj == nullptr)
		return nullptr;
	int vel = strlen(sadrzaj) + 1;
	char * temp = new char[vel];
	strcpy_s(temp, vel, sadrzaj);
	return temp;
}
class Datum {
	int *_dan, *_mjesec, *_godina;
public:
	Datum(int dan = 1, int mjesec = 1, int godina = 2000) {
		_dan = new int(dan);
		_mjesec = new int(mjesec);
		_godina = new int(godina);
	}
	~Datum() {
		delete _dan; _dan = nullptr;
		delete _mjesec; _mjesec = nullptr;
		delete _godina; _godina = nullptr;
	}
	friend ostream& operator<< (ostream &COUT, const Datum &obj) {
		COUT << *obj._dan << " " << *obj._mjesec << " " << *obj._godina;
		return COUT;
	}

	Datum& operator= (const Datum& d)
	{
		delete _dan; delete _mjesec; delete _godina;
		_dan = new int(*d._dan);
		_mjesec = new int(*d._mjesec);
		_godina = new int(*d._godina);
		return *this;
	}

	int GetDan() const { return *_dan; }
	int GetMjesec() const { return *_mjesec; }
	int GetGodina() const { return *_godina; }


	Datum(const Datum& d)
	{
		_dan = new int(*d._dan);
		_mjesec = new int(*d._mjesec);
		_godina = new int(*d._godina);
	}
};



template<class T>
class Kolekcija {
	T * _niz;
	int _trenutno;
public:
	Kolekcija() : _trenutno(0), _niz(nullptr) {}
	~Kolekcija() { delete[] _niz; _niz = nullptr; _trenutno = 0; }
	T * GetNiz() { return _niz; }
	int GetTrenutno() { return _trenutno; }
	//implementirati potrebne funkcije
	Kolekcija (const Kolekcija& kol)
	{
		_trenutno = kol._trenutno;
		_niz = new T[_trenutno];
		for (int i = 0; i < _trenutno; i++)
		{
			_niz[i] = kol._niz[i];
		}
	}

	Kolekcija& operator= (const Kolekcija& kol)
	{
		_trenutno = kol._trenutno;
		_niz=new T[_trenutno];
		for (int i = 0; i < _trenutno; i++)
		{
			_niz[i] = kol._niz[i];
		}
		return *this;
	}

	bool DaLiPostoji(const T& t)
	{
		for (int i = 0; i < _trenutno; i++)
		{
			if (t == _niz[i])
				return true;
		}
		return false;
	}

	void Add(const T& t)
	{
		if (DaLiPostoji(t))
		{
			cout << "Nemoguce dodati isti." << endl;
			return;
		}
		T* temp = new T[_trenutno + 1];
		for (int i = 0; i < _trenutno; i++)
		{
			temp[i] = _niz[i];
		}
	temp[_trenutno] = t;
	delete[] _niz;
	_niz = temp;
	_trenutno++;
	}

	friend ostream& operator<< <> (ostream& cout, const Kolekcija& t);

	T operator[] (int indeks)
	{
		return _niz[indeks];
	}

};
template<class T>
ostream& operator<< <> (ostream& cout, const Kolekcija<T>& t)
{
	for (int i = 0; i < t._trenutno; i++)
	{
		cout << t._niz[i] << endl;
	}
	return cout;
}


class Usluga {
	char* _naziv;
	double _cijena;//cijena usluge je izrazena po danu koristenja
public:
	Usluga() : _naziv(nullptr), _cijena(0) {}
	Usluga(const char* naziv, double cijena) : _cijena(cijena) {
		_naziv = AlocirajNizKaraktera(naziv);
	}


	//~Usluga() { delete[] _naziv; _naziv = nullptr; }
	double GetCijena() { return _cijena; }
	const char * GetNaziv() { return _naziv; }
	friend ostream& operator<< (ostream &COUT, const Usluga &obj);



	Usluga(const Usluga& u)
	{
		_naziv = AlocirajNizKaraktera(u._naziv);
		_cijena = u._cijena;
	}
	Usluga& operator= (const Usluga& u)
	{
		delete[] _naziv; _naziv = nullptr;
		_naziv = AlocirajNizKaraktera(u._naziv);
		_cijena = u._cijena;
		return *this;
	}

	friend bool operator== (const Usluga& u1, const Usluga& u2);

};

bool operator== (const Usluga& u1, const Usluga& u2)
{
	if (strcmp(u1._naziv, u2._naziv) == 0  &&  u1._cijena == u2._cijena)
	{
		return true;
	}
	return false;
}

ostream& operator<< (ostream &COUT, const Usluga &obj) {
	COUT << obj._naziv << " -> \t\t" << obj._cijena << " KM" << endl;
	return COUT;
}

class Rezervacija {
	static int _rezervacijeIDBrojac;
	const int _rezervacijaID; ///broj rezervacije krece od 160000
	Datum _rezervacijaOD;
	Datum _rezervacijaDO;
	double _cijenaPoDanu; //cijena osnovnih usluga koja ne ukljucuje dodatne usluge
	Kolekcija<Usluga> _dodatneUsluge; //dodatne usluge mogu biti: sauna, sportski tereni, kuglanje, masaza i sl. 
public:
	//implementirati potrebne funkcije
	Rezervacija(Datum OD, Datum DO, double cijena):_rezervacijaID(++_rezervacijeIDBrojac),_cijenaPoDanu(cijena),_rezervacijaDO(DO),_rezervacijaOD(OD)
	{
	}

	bool operator+= (const Usluga& u)
	{
		for (int i = 0; i < _dodatneUsluge.GetTrenutno(); i++)
		{
			if (u == _dodatneUsluge.GetNiz()[i])
			{
				return false;
			}
		}
		_dodatneUsluge.Add(u);
		return true;
	}

	//rezervacija.PrintRacun();

	/*R.ID: 160000
		OD : 25 10 2018
		DO : 30 10 2018
		DODATNE USLUGE :
	Parking -> 5 KM
		Dorucak -> 10 KM
		Rucak -> 15 KM
		Veseraj -> 10 KM
		Osnovne usluge-> 299.5 KM
		Dodatne usluge-> 200 KM
		Ukupno -> 499.5 KM*/

	int BrojDana()
	{
		int OD = _rezervacijaOD.GetGodina() * 10000 + _rezervacijaOD.GetMjesec() * 100 + _rezervacijaOD.GetDan();
		int DO = _rezervacijaDO.GetGodina() * 10000 + _rezervacijaDO.GetMjesec() * 100 + _rezervacijaDO.GetDan();
		return DO - OD;
	}

	double Dodatne()
	{
		float dodatne = 0;
		for (int i = 0; i < _dodatneUsluge.GetTrenutno(); i++)
		{
			dodatne += _dodatneUsluge.GetNiz()[i].GetCijena();
		}
		return dodatne * BrojDana();
	}

	double Osnovne()
	{
		int osnovne = 0;
		int dani = BrojDana();
		osnovne = dani * _cijenaPoDanu;
		return osnovne;
	}

	void PrintRacun()
	{
		cout << "ID:  " << _rezervacijaID << endl;
		cout << "OD  :  " << _rezervacijaOD << endl;
		cout << "DO  :  " << _rezervacijaDO << endl;
		cout << "DODATNE USLUGE :" << endl;
		for (int i = 0; i < _dodatneUsluge.GetTrenutno(); i++)
		{
			cout << _dodatneUsluge.GetNiz()[i];
		}
		cout << "Osnoven usluge-> " << Osnovne() <<" KM "<< endl;
		cout << "Dodatne usluge-> " << " KM " << Dodatne() << endl;
		cout << "Ukupno-> " << Osnovne() + Dodatne() << " KM " << endl;
	}

	Usluga* operator[] (const char* naziv)
	{
		Usluga* temp = nullptr;
		for (int i = 0; i < _dodatneUsluge.GetTrenutno(); i++)
		{
			if (strcmp(naziv, _dodatneUsluge.GetNiz()[i].GetNaziv()) == 0)
			{
				temp = new Usluga;
				*temp = _dodatneUsluge.GetNiz()[i];
				return temp;
			}
		}
		return temp;
	}

	//template<class T>
	Kolekcija<Usluga> operator() (int poc, int kraj)
	{
		Usluga* niz;
		int br = 0;
		for (int i = 0; i < _dodatneUsluge.GetTrenutno(); i++)
		{
			if (_dodatneUsluge.GetNiz()[i].GetCijena() > poc  && _dodatneUsluge.GetNiz()[i].GetCijena() < kraj)
				br++;
		}
		Kolekcija<Usluga> temp;
		for (int i = 0; i < _dodatneUsluge.GetTrenutno(); i++)
		{
			if (_dodatneUsluge.GetNiz()[i].GetCijena() > poc  && _dodatneUsluge.GetNiz()[i].GetCijena() < kraj)
			{
				temp.Add(_dodatneUsluge.GetNiz()[i]);
			}
		}
		return temp;
	}

};
int Rezervacija::_rezervacijeIDBrojac = 160000;

void main() {
	cout << crt << "TRAJANJE ISPITA -> 90 minuta " << crt;
	Kolekcija<int> brojevi;
	for (int i = 0; i < 15; i++)
		brojevi.Add(i);
	cout << brojevi << crt;

	////u okviru klase Usluga implementirati MOVE konstruktor
	Usluga Parking("Parking", 5), Dorucak("Dorucak", 10), Rucak("Rucak", 15), Veseraj("Veseraj", 10);

	////rezervacijaOD, rezervacijaDO, cijenaPoDanu
	Rezervacija rezervacija(Datum(25, 10, 2018), Datum(30, 10, 2018), 59.9);

	////dodaje novu uslugu u rezervaciju. onemoguciti ponavljanje usluga
	if (rezervacija += Parking)
		cout << "Usluga uspjesno dodana!" << endl;
	if (rezervacija += Dorucak)
		cout << "Usluga uspjesno dodana!" << endl;
	if (rezervacija += Rucak)
		cout << "Usluga uspjesno dodana!" << endl;
	if (rezervacija += Veseraj)
		cout << "Usluga uspjesno dodana!" << endl;
	if (!(rezervacija += Dorucak))
		cout << "Usluga vec postoji!" << endl;

	///*prikazuje racun formatiran na nacin prikazan na slici. prilikom izracunavanja iznosa koristiti cijene osnovnih i dodatnih usluga, kao i broj dana za koje je napravljena rezervacija (napomena: duzina trajanja rezervacije je maksimalno 30 dana)*/
	rezervacija.PrintRacun();

	////vraca pokazivac na uslugu sa proslijedjenim nazivom
	Usluga * p = rezervacija["Dorucak"];
	if (p != nullptr)
		cout << *p << crt;

	////vraca sve dodatne usluge koje imaju cijenu u opsegu vrijednosti parametara
	Kolekcija<Usluga> uslugePoCijeni = rezervacija(8, 12);
	system("CLS");
	for (size_t i = 0; i < uslugePoCijeni.GetTrenutno(); i++)
		cout << uslugePoCijeni[i] << crt;
	cin.get();
}

