#include<iostream>
using namespace std;

int br = 0;

class Uposlenik {
	int _sifra; //Automatski uvecavati za 1 za svakog novog uspolenika.
	char _ime[30];
	char _prezime[30];
	char* _radnoMjesto;
	static const char* _kompanija;
	static int _brojUposlenih;
public:
	int GetBrojUposlenih() const { return _brojUposlenih; }
	const char* GetIme() const { return _ime; }


	Uposlenik& operator= (const Uposlenik& u) {
		_sifra = u._sifra;
		strncpy_s(_ime, u._ime, 30);
		strncpy_s(_prezime, u._prezime, 30);
		int vel = strlen(u._radnoMjesto) + 1;
		_radnoMjesto = new char[vel];
		strcpy_s(_radnoMjesto, vel, u._radnoMjesto);
	}

	void Info() {
		cout << "Sifra -> " << _sifra << endl;
		cout << "Ime -> " << _ime << endl;
		cout << "Kompanija -> " << _kompanija << endl;
	}

	//Implementirati potrebne konstruktor i destruktor funkcije
	Uposlenik(const char* ime, const char* prezime, const char*radnomjesto) : _sifra(++br)
	{
		strncpy_s(_ime, ime, _TRUNCATE);
		strncpy_s(_prezime, prezime, _TRUNCATE);
		int vel = strlen(radnomjesto) + 1;
		_radnoMjesto = new char[vel];
		strcpy_s(_radnoMjesto, vel, radnomjesto);
	}
	Uposlenik() : _sifra(0), _radnoMjesto(nullptr)
	{
		strncpy_s(_ime, "----", _TRUNCATE);
		strncpy_s(_prezime, "----", _TRUNCATE);
	}

	//kon kopija
	Uposlenik(const Uposlenik& u) : _sifra(u._sifra)
	{
		strncpy_s(_ime, u._ime, _TRUNCATE);
		strncpy_s(_prezime, u._prezime, _TRUNCATE);
		int vel = strlen(u._radnoMjesto) + 1;
		_radnoMjesto = new char[vel];
		strcpy_s(_radnoMjesto, vel, u._radnoMjesto);
	}

	~Uposlenik() {
		delete[]_radnoMjesto; _radnoMjesto = nullptr;
	}


	bool UporediUposlenike(const Uposlenik &u) {
		if (strcmp(u._ime, _ime) == 0)
			return false;
		return true;
	}
	friend bool operator== (const Uposlenik& u1, const Uposlenik& u2);
	friend ostream& operator<< (ostream& cout, const Uposlenik& u);


};
ostream& operator<< (ostream& cout, const Uposlenik& u) {
	cout << "Sifra -> " << u._sifra << endl;
	cout << "Ime -> " << u._ime << endl;
	cout << "Prezime -> " << u._prezime << endl;
	cout << "Oblast -> " << u._radnoMjesto << endl;
	return cout;
}

bool operator== (const Uposlenik& u1, const Uposlenik& u2) {
	if (strcmp(u1._ime, u2._ime) == 0)
		return true;
	return false;
}

const char* Uposlenik::_kompanija = "FIT";
int  Uposlenik::_brojUposlenih = 0;

class Aktivnost {
	char* _naziv;
	bool _zavrsena;
	int* _trajanje; //Izrazeno u danima
	Uposlenik* _uposlenici[5];

public:
	const char* GetNaziv() const { return _naziv; }
	Uposlenik** GetUposlenici() { return _uposlenici; }
	int GetTrajanje() const { return *_trajanje; }

	Aktivnost& operator+= (const Uposlenik& u)
	{
		for (int i = 0; i < 5; i++)
		{
			if (_uposlenici[i] != nullptr) {
				if (_uposlenici[i]->UporediUposlenike(u) == false)
				{
					cout << "Uposlenik nije dodan." << endl;
					return *this;
				}
			}
			if (_uposlenici[i] == nullptr) {
				_uposlenici[i] = new Uposlenik(u);
				cout << "Uspjesno dodan." << endl;
		        return *this;
			}
		}
	}

	Aktivnost& operator= (const Aktivnost& akt) {
		int vel = strlen(akt._naziv) + 1;
		_naziv = new char[vel];
		strcpy_s(_naziv, vel, akt._naziv);
		_zavrsena = akt._zavrsena;
		_trajanje = new int(*akt._trajanje);
		for (int i = 0; i < 5; i++)
		{
			if (akt._uposlenici[i] != nullptr)
				_uposlenici[i] = new Uposlenik;
			_uposlenici[i] = akt._uposlenici[i];
		}
		return *this;
	}

	Aktivnost() :_zavrsena(false), _trajanje(nullptr)
	{
		_naziv = nullptr;
		for (int i = 0; i < 5; i++)
		{
			_uposlenici[i] = nullptr;
		}
	}

	bool DaLiJeIstaAktivnost(const Aktivnost& akt) {
		if (strcmp(_naziv, akt._naziv) == 0 || akt._zavrsena == true)
			return false;
		return true;
	}


	void Info() {
		cout << "Naziv -> " << _naziv << endl;
		for (int i = 0; i < 5; i++)
		{
			if (_uposlenici[i] != nullptr) {
				_uposlenici[i]->Info();
			}
		}

	}
	bool DaLiPostojiUposlenik(const Uposlenik& u)
	{
		for (int i = 0; i < 5; i++)
		{
			if (_uposlenici[i] != nullptr) {
				if (strcmp(u.GetIme(), _uposlenici[i]->GetIme()) == 0)
					return true;
			}
		}
		return false;
	}
	//Implementirati potrebne konstruktor i destruktor funkcije
	//Aktivnost Programiranje("Programiranje", 3), Mreze("Mreze", 3);
	Aktivnost(const char* naziv, int trajanje) :_zavrsena(false)
	{
		int vel = strlen(naziv) + 1;
		_naziv = new char[vel];
		strcpy_s(_naziv, vel, naziv);
		_trajanje = new int(trajanje);
		for (int i = 0; i < 5; i++)
		{
			_uposlenici[i] = nullptr;
		}
	}

	~Aktivnost() {
		delete[]_naziv; _naziv = nullptr;
		delete _trajanje; _trajanje = nullptr;
	}
	bool AddUposlenik(Uposlenik *u)
	{
		if (_zavrsena)
			return false;
		for (int i = 0; i < 5; i++)
		{
			if (_uposlenici[i] != nullptr) {
				if (_uposlenici[i]->UporediUposlenike(*u) != true)
					return false;
			}
			if (_uposlenici[i] == nullptr) {
				_uposlenici[i] = new Uposlenik(*u);
				cout << "Uspjesno dodan." << endl;
				return true;
			}
		}
		return true;
	}

	Aktivnost& operator-= (const Uposlenik& u)
	{
		if (DaLiPostojiUposlenik(u) != true) {
			cout << "Takav uposlenik ne postoji. " << endl;
			return *this;
		}
		int br = 0;
		for (int i = 0; i < 5; i++)
		{
			if (_uposlenici[i] != nullptr)
			{
				br++;
			}
		}
		for (int i = 0; i < 5; i++)
		{
			if (_uposlenici[i] != nullptr) {
				if (*_uposlenici[i] == u) {
					delete _uposlenici[i];
					_uposlenici[i] = nullptr;
					--br;
					for (int j = i; j < br; j++)
					{
						if (_uposlenici[j + 1] != nullptr)
							_uposlenici[j] = _uposlenici[j + 1];
						else
						{
							_uposlenici[j] = nullptr;
							break;
						}
					}
				}
			}
		}
	}
};
class Projekat {
	char* _naziv;
	char* _oblast;
	int _trajanje; //Izrazeno u mjesecima
	Aktivnost* _aktivnosti;
	int _brojAktivnosti;
public:
	int GetBrojAktivnosti() const { return _brojAktivnosti; }
	Aktivnost* GetAktivnosti() const { return _aktivnosti; }

	//Projekat Nastava("Nastava", "Obrazovanje", 10);
	Projekat(const char* naziv, const char* oblast, int trajanje) :_trajanje(trajanje), _brojAktivnosti(0)
	{
		int vel = strlen(naziv) + 1;
		_naziv = new char[vel];
		strcpy_s(_naziv, vel, naziv);
		vel = strlen(oblast) + 1;
		_oblast = new char[vel];
		strcpy_s(_oblast, vel, oblast);
	}

	~Projekat() {
		delete[] _naziv; _naziv = nullptr;
		delete[] _oblast; _oblast = nullptr;
		delete[]_aktivnosti;
	}
	bool AddAktivnost(const Aktivnost* akt) {
		for (int i = 0; i < _brojAktivnosti; i++)
		{
			if (_aktivnosti[i].DaLiJeIstaAktivnost(*akt) == false)
				return false;
		}
		Aktivnost* temp = new Aktivnost[_brojAktivnosti + 1];
		for (int i = 0; i < _brojAktivnosti; i++)
		{
			temp[i] = _aktivnosti[i];
		}
		temp[_brojAktivnosti] = *akt;
		delete[] _aktivnosti;
		_aktivnosti = temp;
		_brojAktivnosti++;
		return true;
	}
	bool DodijeliUposlenika(const char* nazivAkt, const Uposlenik* u)
	{
		for (int i = 0; i < _brojAktivnosti; i++)
		{
			if (strcmp(_aktivnosti[i].GetNaziv(), nazivAkt) == 0)
			{
				_aktivnosti[i] += *u;
				break;
			}
		}
		return true;
	}
	void UkloniUposlenika(const char* naziv, const Uposlenik& u)
	{
		for (int i = 0; i < 5; i++)
		{
			if (strcmp(_aktivnosti[i].GetNaziv(), naziv) == 0)
			{
				_aktivnosti[i] -= u;
				break;
			}

		}
	}
	
	int* BrojacAktivnosti(const Uposlenik & u)
	{
		int duzina = 0;
		int niz[2];
		int br = 0;
		for (int i = 0; i < _brojAktivnosti; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				if (_aktivnosti[i].GetUposlenici()[j] != nullptr) {
				if (strcmp(_aktivnosti[i].GetUposlenici()[j]->GetIme(), u.GetIme()) == 0)
				{
					duzina += _aktivnosti[i].GetTrajanje();
					br++;
					break;
				}
				}
			}
		}
		niz[0] = br;
		niz[1] = duzina;
		return niz;
	}


	//Funkciju koja pronalazi uposlenika sa najvecim brojem angazmana na aktivnostima.
	//Funkciju koja pronalazi 3 uposlenika koja su angazovana na najvecem broju nezavrsenih aktivnosti.
	//Funkciju koja ispisuje sve zavrsene aktivnosti na projektu.

};


/*Kreirati globalnu funkciju koja pronalazi najuspjesnijeg usposlenika na projektima proslijedjenim kao parametar.
Uposlenik se smatra najuspjesnijim ako je angazovan na najvecem broju zavrsenih aktivnosti. Ako vise uposlenika
ima isti broj zavrsenih aktivnosti, uspjesnijim se smatra onaj cije su aktivnosti trajale duze.
*/

Uposlenik* PronadjiNajuspjesnijeg(Projekat& p) 
{
	int minAktivnost = INT_MIN,minDuzina=INT_MIN, indeksAktivnosti = 0, indeksUposlenika = 0, duzinaAktivnosti;
	Uposlenik* temp;
	for (int i = 0; i <p.GetBrojAktivnosti() ; i++)
	{
		int brojac = 0;
		for (int j = 0; j < 5; j++)
		{
			if (p.GetAktivnosti()[i].GetUposlenici()[j] != nullptr) {
			brojac = p.BrojacAktivnosti(*p.GetAktivnosti()[i].GetUposlenici()[j])[0];
			duzinaAktivnosti= p.BrojacAktivnosti(*p.GetAktivnosti()[i].GetUposlenici()[j])[1];
			if (brojac > minAktivnost)
			{
				minDuzina=duzinaAktivnosti;
				minAktivnost = brojac;
				indeksAktivnosti = i;
				indeksUposlenika = j;
			}
			else if (brojac == minAktivnost)
			{
				if (duzinaAktivnosti > minDuzina) 
				{
					indeksAktivnosti = i;
					indeksUposlenika = j;
				}
			}

			}
		}
	}
	return p.GetAktivnosti()[indeksAktivnosti].GetUposlenici()[indeksUposlenika];
}

int main()
{
	//Testirati sve dostupne funkcionalnosti
	Uposlenik 
		u1("Denis", "Music", "FIT"),
		u2("Jasmin", "Azemovic", "FIT"),
		u3("Zanin", "Vejzovic", "FIT"),
		u4("Mohamed", "El-Zayat", "FIT"),
		u5("Indira", "Hamulic", "FIT");
	Aktivnost Programiranje("Programiranje", 3), Mreze("Mreze", 3);
	Programiranje.AddUposlenik(&u1);
	Programiranje.AddUposlenik(&u2);
	Mreze.AddUposlenik(&u1);
	Mreze.AddUposlenik(&u3);
	Mreze.AddUposlenik(&u4);

	Uposlenik u6(u5);
	u6.Info();
	system("CLS");

	Projekat Nastava("Nastava", "Obrazovanje", 10);
	if (Nastava.AddAktivnost(&Programiranje))
		cout << "Uspjesno." << endl;
	else
		cout << "Neuspjesno." << endl;
	if (Nastava.AddAktivnost(&Mreze))
		cout << "Uspjesno." << endl;
	else
		cout << "Neuspjesno." << endl;
	Nastava.DodijeliUposlenika("Programiranje", &u5);
	Nastava.UkloniUposlenika("Programiranje", u4);
	cout << "\n\nNajuspjesniji uposlenik na projektu: ";
	Uposlenik *najUspjesniji = PronadjiNajuspjesnijeg(Nastava);
	cout << *najUspjesniji;
	for (int i = 0; i < 5; i++)
	{
		if(Nastava.GetAktivnosti()[0].GetUposlenici()[i]!=nullptr)
		cout<<*Nastava.GetAktivnosti()[0].GetUposlenici()[i] << endl;
	}

	system("pause");
	return 0;
}
