#include<iostream>
using namespace std;

char * AlocirajNizKaraktera(const char * sadrzaj) {
	if (sadrzaj == nullptr)
		return nullptr;
	int vel = strlen(sadrzaj) + 1;
	char * temp = new char[vel];
	strcpy_s(temp, vel, sadrzaj);
	return temp;
}


template<class T, int max>
class Kolekcija
{
	T* _elementi[max];
	int _trenutnoElemenata;
public:
	//Implementirati potrebne funkcije za rad sa kolekcijom.
	int GetTrenutno() const { return _trenutnoElemenata; }
	T** GetElementi()  { return _elementi; }

	Kolekcija():_trenutnoElemenata(0)
	{
		for (int i = 0; i < max; i++)
		{
			_elementi[i] = nullptr;
		}
	}
	~Kolekcija()
	{
		for (int i = 0; i < _trenutnoElemenata; i++)
		{
			delete _elementi[i];
		}
	}
	Kolekcija(const Kolekcija& orig)
	{
		_trenutnoElemenata = orig._trenutnoElemenata;
		for (int i = 0; i < _trenutnoElemenata; i++)
		{
			_elementi[i] = new T(*orig._elementi[i]);
		}
	}
	Kolekcija& operator= (const Kolekcija& orig) 
	{
		for (int i = 0; i < _trenutnoElemenata; i++)
		{
			delete _elementi[i]; 
			_elementi[i] = new T(*orig._elementi[i]);
		}
	}

	bool DaLiJeIsti(const T& t)
	{
		for (int i = 0; i < _trenutnoElemenata; i++)
		{
			if (t == *_elementi[i])
				return true;
		}
		return false;
	}

	void AddElement(const T& t)
	{
		if (_trenutnoElemenata == max)
		{
			cout << "Popunjen." << endl;
			return;
		}
		if (DaLiJeIsti(t) == true)
		{
			cout << "Nemoguce dodati istog." << endl;
			return;
		}
		_elementi[_trenutnoElemenata] = new T(t);
		_trenutnoElemenata++;
	}
	void Info()
	{
		for (int i = 0; i < _trenutnoElemenata; i++)
		{
			cout << *_elementi[i] << endl;
		}
	}

	Kolekcija& RemoveByIndex(int indeks)
	{
		if (indeks < 0 || indeks >= _trenutnoElemenata)
		{
			cout << "Nepostojeci indeks." << endl;
			return *this;
		}
		delete _elementi[indeks];
		_elementi[indeks] = new T;
		for (int i = indeks; i < _trenutnoElemenata-1; i++)
		{
			_elementi[i] = _elementi[i + 1];
		}
		_trenutnoElemenata--;
		_elementi[_trenutnoElemenata] = nullptr;
		cout << "Uspjesno uklonjeno." << endl;
	return *this;
	}

	int DaLiPostojiElement(const T& el)
	{
		for (int i = 0; i < _trenutnoElemenata; i++)
		{
			if (el == *_elementi[i])
				return i;
		}
		return -1;
	}

	Kolekcija& RemoveElement(const T& el)
	{
		if (DaLiPostojiElement(el) == -1)
		{
			cout << "Takav element ne postoji." << endl;
			return *this;
		}
		RemoveByIndex(DaLiPostojiElement(el));
		return *this;
	}

};

class Prisustvo
{
	char* _brojIndeksa;
	int _brojSati;
public:
	int GetBrojSati() { return _brojSati; }
	const char* GetIndeks() const { return _brojIndeksa; }
	//Osnovne funkcije za rad s klasom
	Prisustvo()
	{
		_brojIndeksa = nullptr;
		_brojSati = 0;
	}

	Prisustvo(const char* brojIndeksa, int brojSati) : _brojSati(brojSati)
	{
		int size = strlen(brojIndeksa) + 1;
		_brojIndeksa = new char[size];
		strcpy_s(_brojIndeksa, size, brojIndeksa);
	}

	~Prisustvo()
	{
		delete[] _brojIndeksa;
		_brojIndeksa = nullptr;
	}

	Prisustvo(const Prisustvo& org)
	{
		_brojIndeksa = AlocirajNizKaraktera(org._brojIndeksa);
		_brojSati = org._brojSati;
	}
	Prisustvo& operator= (const Prisustvo& org)
	{
		delete[] _brojIndeksa; 
		_brojIndeksa = AlocirajNizKaraktera(org._brojIndeksa);
		_brojSati = org._brojSati;
		return *this;
	}
	
	bool operator== (const Prisustvo& p)
	{
		if (strcmp(_brojIndeksa, p._brojIndeksa) == 0)
			return true;
		return false;
	}

	friend bool operator< (const Prisustvo& p1, const Prisustvo& p2);


	/////Preklopljeni operator + i += za uvećavanje broja sati prisustva za vrijednost proslijeđenog parametra

	friend ostream& operator<< (ostream& cout, const Prisustvo& p);

};
ostream& operator<< (ostream& cout, const Prisustvo& p)
{
	cout << "Broj indeksa -> " << p._brojIndeksa << endl;
	cout << "Broj sati -> " << p._brojSati << endl;
	return cout;
}

bool operator< (const Prisustvo& p1, const Prisustvo& p2)
{
	if (strcmp(p1._brojIndeksa, p2._brojIndeksa) == -1)
		return true;
	return false;
}


class Nastava
{
	char _datum[12];
	char _tipNastave; //P ili V
	int _odrzanoSati;
	Prisustvo* _prisutni;
	int _brojStudenata;
public:
	Prisustvo* GetPrisutni() { return _prisutni; }
	char GetTip() const { return _tipNastave; }
	int GetOdrzanoSati() const { return _odrzanoSati; }
	const char* GetDatum() const { return _datum; }
	//Konstruktor sa osnovnim atributima klase
	//Nastava n1("5.12.2018", 'P', 35);
	Nastava(const char* datum, char tip, int sati) : _odrzanoSati(sati), _tipNastave(tip), _brojStudenata(0), _prisutni(nullptr)
	{
		int vel = strlen(_datum);
		if (vel > 12)
			strncpy_s(_datum, "-------", _TRUNCATE);
		else
		{
			strncpy_s(_datum, datum, _TRUNCATE);
		}
		
	}
	int GetBrojStudenata() const{ return _brojStudenata; }

	float Procenat(const char* indeks)
	{
		float p = 0;
		for (int i = 0; i < _brojStudenata; i++)
		{
			if (strcmp(indeks, _prisutni[i].GetIndeks()) == 0)
			{
				p=(_prisutni[i].GetBrojSati() / _odrzanoSati) * 100;
				return  p;
			}
		}
	}


	//Destruktor
	~Nastava()
	{
		delete[] _prisutni; _prisutni = nullptr;
	}

	Nastava(const Nastava& n)
	{
		strncpy_s(_datum, n._datum, _TRUNCATE);
		_tipNastave = n._tipNastave;
		_odrzanoSati = n._odrzanoSati;
		_brojStudenata = n._brojStudenata;
		_prisutni = new Prisustvo[_brojStudenata];
		for (int i = 0; i < _brojStudenata; i++)
		{
			_prisutni[i] = n._prisutni[i];
		}
	}

	Nastava& operator= (const Nastava& n)
	{
		strncpy_s(_datum, n._datum, _TRUNCATE);
		_tipNastave = n._tipNastave;
		_odrzanoSati = n._odrzanoSati;
		_brojStudenata = n._brojStudenata;
		delete[] _prisutni;
		_prisutni = new Prisustvo[_brojStudenata];
		for (int i = 0; i < _brojStudenata; i++)
		{
			_prisutni[i] = n._prisutni[i];
		}
	}

	//Preklopljeni operator+= za dodavanje objekata tipa Prisustvo u niz _prisutni.
	//Nije moguće dodati više puta prisustvo za istog studenta (preklopiti operator== u klasi Prisustvo).
	//Elementi u svakom momentu treba da budu sortirani po broju indeksa studenta (preklopiti operator < u klasi Prisustvo).

	Nastava& operator+= ( Prisustvo& pr)
	{
		for (int i = 0; i < _brojStudenata; i++)
		{
			if (pr == _prisutni[i])
			{
				cout << "Nemoguce dodati isto prisustvo." << endl;
				return *this;
			}
		}
		Prisustvo* temp = new Prisustvo[_brojStudenata + 1];
		for (int i = 0; i < _brojStudenata; i++)
		{
			if (pr < _prisutni[i])
			{
				temp[i] = pr;
				int br = i;
				br++;
				for (int j = i; j < _brojStudenata; j++)
				{
					temp[br] = _prisutni[j];
					br++;
				}
				_brojStudenata++;
				delete[] _prisutni;
				_prisutni = temp;
				return *this;
			}
			else
			{
				temp[i] = _prisutni[i];
			}	 
		}
		temp[_brojStudenata] = pr;
		_brojStudenata++;
		delete[] _prisutni;
		_prisutni = temp;
		return *this;
	}

	//Preklopljeni operator-= za uklanjanje prisustva za studenta sa proslijedjenim brojem indeksa. Nakon uklanjanja,
	//potrebno je sačuvati redoslijed dodavanja, odnosno podaci ostaju sortirani po broju indeksa.

	int DaLiPostojiIndeks(const char* indeks)
	{
		for (int i = 0; i < _brojStudenata; i++)
		{
			if (strcmp(indeks, _prisutni[i].GetIndeks()) == 0)
				return i;
		}
		return -1;
	}

	Nastava& operator-= (const char* indeks)
	{
		if (DaLiPostojiIndeks(indeks) == -1)
		{
			cout << "Takav indeks ne postoji." << endl;
			return *this;
		}
		int vel = DaLiPostojiIndeks(indeks);
		for (int i = vel; i < _brojStudenata-1; i++)
		{
			_prisutni[i] = _prisutni[i + 1];
		}
		_brojStudenata--;
		return *this;
	}



	//Preklopljeni operator [] koji na osnovu broja indeksa provjerava da li je 
	//određeni student prisustvovao nastavi i vraća njegove podatke o prisustvu.

	Prisustvo operator[]  (const char* indeks)
	{
		if (DaLiPostojiIndeks(indeks) == -1)
		{
			cout << "Takav student nije prisustvovao nastavi." << endl;
		}
		return _prisutni[DaLiPostojiIndeks(indeks)];
	}

	//Preklopljeni operator () koji pronalazi studenta sa proslijeđenim brojem indeksa i uvećava mu broj sati prisustva
	//za vrijednost drugog parametra. Ako je studentu već evidentiran odrzani broj sati nastave prekinuti funkciju.

	//Preklopljeni operator + koji zbraja dva objekta tipa Nastava na način da kreira novi objekat na osnovu lijevog operanda
	//i dodaje mu prisutne studente desnog operanda. Funkciju napustiti ukoliko objekti koji učestvuju u operaciji sabiranja
	//nisu istog tipa nastave. Spriječiti dodavanje prisustva za istog studenta više puta.
	//Operator implementirati kao globalnu funkciju.

	Nastava operator+ (const Nastava& n1)
	{
		Nastava temp(*this);
		if (temp._tipNastave != n1._tipNastave)
		{
			cout << "Tip nastave nije isti.";
			return temp;
		}
		for (int i = 0; i < n1._brojStudenata; i++)
		{
			temp += n1._prisutni[i];
		}
		return *this;
	}

	friend ostream& operator<< (ostream& cout, const Nastava& n);
	friend bool operator== (const Nastava& n1, const Nastava& n2);


};

bool operator== (const Nastava& n1, const Nastava& n2)
{
	if (strcmp(n1._datum, n2._datum) == 0)
		return true;
	return false;

}


ostream& operator<< (ostream& cout, const Nastava& n)
{
	for (int i = 0; i < n._brojStudenata; i++)
	{
		cout << n._prisutni[i] << endl;
	}
	return cout;
}

class Predmet
{
	char* _naziv;
	int _godinaStudija;
	Kolekcija<Nastava, 45> _odrzanaNastava;
public:
	Predmet(const char* naziv, int godinaStudija) : _godinaStudija(godinaStudija)
	{
		_naziv = AlocirajNizKaraktera(naziv);
	}

	~Predmet()
	{
		delete[] _naziv;
		_naziv = nullptr;
	}

	//Funkciju za evidenciju održane nastave na predmetu.
	
	void AddEvidencija(const Nastava& n)
	{
		_odrzanaNastava.AddElement(n);
	}


	/*Funkciju koja na osnovu datuma i tipa održane nastave dodaje prisustvo studentu sa proslijeđenim brojem indeksa i brojem sati.
	Voditi računa da broj sati prisustva ne može biti veći od broja sati održane nastave.*/
	//predmet.DodajPrisustvo("5.12.2018", 'P', "IB170044", 28);

	void DodajPrisustvo(const char* datum, char tip, const char* indeks, int brojsati)
	{
		for (int i = 0; i < _odrzanaNastava.GetTrenutno(); i++)
		{
			if (strcmp(datum, _odrzanaNastava.GetElementi()[i]->GetDatum())==0)
			{
				if (brojsati < _odrzanaNastava.GetElementi()[i]->GetOdrzanoSati())
				{
					Prisustvo temp(indeks, brojsati);
					*_odrzanaNastava.GetElementi()[i] += temp;
				}
			}
		}
	}


	/*Funkciju koja na osnovu datuma i tipa održane nastave uklanja prisustvo studentu sa proslijeđenim brojem indeksa.*/
	void UkloniPrisustvo(const char* datum, char tip, const char* indeks)
	{
		for (int i = 0; i < _odrzanaNastava.GetTrenutno(); i++)
		{
			if (strcmp(datum, _odrzanaNastava.GetElementi()[i]->GetDatum()) == 0 && tip == _odrzanaNastava.GetElementi()[i]->GetTip())
				*_odrzanaNastava.GetElementi()[i] -= indeks;
		}

	}

	Prisustvo GetPodaciStudenta(const char* indeks)
	{
		for (int i = 0; i < _odrzanaNastava.GetTrenutno(); i++)
		{
			for (int j = 0; j < _odrzanaNastava.GetElementi()[i]->GetBrojStudenata(); j++)
			{
				if (strcmp(_odrzanaNastava.GetElementi()[i]->GetPrisutni()[j].GetIndeks(), indeks) == 0)
					return _odrzanaNastava.GetElementi()[i]->GetPrisutni()[j];
			}
		}
	}

	/*Funkciju koja na osnovu broja indeksa studenta vraća sve podatke o njegovom prisustvu na nastavi*/


	/*Funkciju koja na osnovu tipa nastave (P ili V) vrši ispis prisustva za sve studente (sumarno) u datom formatu:
	IB140001 30/40 75%, gdje je prva kolona "broj indeksa", druga kolona "broj sati prisustva / ukupan broj sati održane nastave" i
	treca kolona "procenat prisustva studenta na nastavi".*/


	void Info(char tip)
	{
		for (int i = 0; i < _odrzanaNastava.GetTrenutno(); i++)
		{
			if (_odrzanaNastava.GetElementi()[i]->GetTip() == tip)
			{
				for (int j = 0; j < _odrzanaNastava.GetElementi()[i]->GetBrojStudenata(); j++)
				{
					cout << _odrzanaNastava.GetElementi()[i]->GetPrisutni()[j].GetIndeks() << "   \t   " << _odrzanaNastava.GetElementi()[i]->GetPrisutni()[j].GetBrojSati() <<   "/"   <<
						 _odrzanaNastava.GetElementi()[i]->GetOdrzanoSati() << "   \t   " <<
						_odrzanaNastava.GetElementi()[i]->Procenat(_odrzanaNastava.GetElementi()[i]->GetPrisutni()[j].GetIndeks()) << endl;
				}
			}
		}
	}

	friend ostream& operator<<(ostream&, const Predmet&);
};

ostream& operator<<(ostream& cout, const Predmet& p)
{
	cout << "Predmet: " << p._naziv << endl;
	cout << "Godina studija: " << p._godinaStudija << endl;

	return cout;

}

const char* crt = { "---------------------------" };

int main()
{
	////Testirati sve dostupne funkcionalnosti klasa Prisustvo i Nastava.
	Kolekcija<int, 10> kolekcija;
	cout << crt << "KOLEKCIJA TEST" << crt << endl;;
	for (int i = 0; i < 10; i++)
		kolekcija.AddElement(i);
	kolekcija.Info();
	kolekcija.RemoveByIndex(0);
	kolekcija.RemoveByIndex(7);
	kolekcija.RemoveByIndex(2);
	kolekcija.RemoveElement(22);
	cout << crt;
	Prisustvo p1("IB170067", 20);
	Prisustvo p2("IB170011", 27);
	Prisustvo p3("IB170065", 32);
	Prisustvo p4("IB170123", 13);
	Prisustvo p5("IB170212", 12);
	
	Nastava n1("5.12.2018", 'P', 35);
	Nastava n2("1.9.2017", 'P', 15);
	cout << crt << "NASTAVA TEST" << crt << endl;
	n1 += p1;
	n1 += p3;
	n1 += p4;
	n1 += p2;
	cout <<crt<< "ISPIS NASTAVE 1" << crt << endl;;
	//cout << n1;
	//n1 -= "IB170065";
	cout << crt << endl;
	cout << n1;
	cout << crt << endl;;
	cout << n1["IB170067"];
	n2 += p4;
	n2 += p5;
	n2 += p2;
	n2 += p1;
	cout << crt << "ISPIS NASTAVE 2" << crt;
	cout << n2;
	//cout << crt;

	cout << n1 + n2;
	system("CLS");

	cout << crt << "PREDMET TEST" << crt << endl;

	Predmet predmet("Programiranje III", 2);
	predmet.AddEvidencija(n1);
	predmet.AddEvidencija(n2);

	predmet.DodajPrisustvo("5.12.2018", 'P', "IB170044", 28);
	predmet.DodajPrisustvo("5.12.2018", 'P', "IB170350", 34);

	predmet.UkloniPrisustvo("5.12.2018", 'P', "IB170065");
	cout << predmet.GetPodaciStudenta("IB170067");
	cout << crt;
	predmet.Info('P');


	system("pause");
	return 0;
}

