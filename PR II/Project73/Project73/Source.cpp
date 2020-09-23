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


class Uposlenik {
	static int _brojacSifra;
	const int _sifra; //Automatski uvecavati za 1 za svakog novog uposlenika.
	char _ime[30];
	char _prezime[30];
	char* _radnoMjesto;
public:
	const char* GetIme() const { return _ime; }
	int GetSifra() const { return _sifra; }
	const char* GetPrezime() const { return _prezime; }
	char* GetRadnoMjesto() const { return _radnoMjesto; }
	static int GetBrojac() { return _brojacSifra; }

	//Implementirati potrebne konstruktor i destruktor funkcije
	
	Uposlenik(const Uposlenik& u):_sifra(u.GetSifra())
	{
		strncpy_s(_ime, u.GetIme(), _TRUNCATE);
		strncpy_s(_prezime, u.GetPrezime(), _TRUNCATE);
		_radnoMjesto = AlocirajNizKaraktera(u._radnoMjesto);
	
	}
	
	Uposlenik(const char* ime, const char* prezime, const char* radnoMjesto) : _sifra(++_brojacSifra)
	{
		strncpy_s(_ime, ime, _TRUNCATE);
		strncpy_s(_prezime, prezime, _TRUNCATE);
		_radnoMjesto = AlocirajNizKaraktera(radnoMjesto);
	}

	~Uposlenik()
	{
		delete[] _radnoMjesto;
		_radnoMjesto = NULL;
	}

	//Ostale funkcije dodati po potrebi

	void Info()
	{
		cout << "Sifra: " << _sifra << endl;
		cout << "Ime i prezime: " << _ime << " " << _prezime << endl;
		cout << "Radno mjesto: " << _radnoMjesto << endl;
	}

};

int Uposlenik::_brojacSifra = 0;


class Aktivnost {
	char* _naziv;
	bool _zavrsena;
	int* _trajanje; //Izrazeno u danima
	Uposlenik* _uposlenici[5];
public:

    Uposlenik** GetUposlenici () { return _uposlenici; }
	const char* GetNaziv() const { return _naziv; }
	bool SetZavrsi() { _zavrsena = true; return _zavrsena; }

	//Implementirati potrebne konstruktor i destruktor funkcije
	void Kopiraj(const Aktivnost& akt) {
		_naziv = AlocirajNizKaraktera(akt._naziv);
		_zavrsena = akt._zavrsena;
		_trajanje = new int(*akt._trajanje);
		for (int i = 0; i < 5; i++)
		{
			if(akt._uposlenici[i] != nullptr)
			DodajUposlenika(*akt._uposlenici[i]);
		}
	}

	Aktivnost() :_zavrsena(false) {
		_trajanje = nullptr;
		_naziv = nullptr;
		for (int i = 0; i < 5; i++)
		{
			_uposlenici[i] = nullptr;
		}
	}

	Aktivnost(const char* naziv, int trajanje) :_zavrsena(false) {
		_naziv = AlocirajNizKaraktera(naziv);
		_trajanje = new int(trajanje);
		for (int i = 0; i < 5; i++)
		{
			_uposlenici[i] = nullptr;
		}
	}

	~Aktivnost() {
		delete[] _naziv; _naziv = nullptr;
		delete _trajanje; _trajanje = nullptr;
		for (int i = 0; i < 5; i++)
		{
			if (_uposlenici[i] != nullptr) {
			delete _uposlenici[i];
			_uposlenici[i] = nullptr;
			}
		}
	}

	void Info() {
		cout << "Naziv -> " << _naziv << endl;
		if (_zavrsena)
			cout << "Aktivnost je zavrsena.";
		else
			cout << "Aktivnost je aktivna.";
		cout << "Trajanje aktivnosti -> " << *_trajanje << endl;
		cout << "Uposlenici : " << endl;
		for (int i = 0; i < 5; i++)
		{
			if(_uposlenici[i] != nullptr)
			cout << _uposlenici[i]->GetIme() << endl;
		}
	}
	bool DaLiPostojiUposlenik(const Uposlenik& u) {
		for (int i = 0; i < 5; i++)
		{
			if (_uposlenici[i] != nullptr && _uposlenici[i]->GetSifra() == u.GetSifra())
				return true;
		}
		return false;
	}

	bool DaLiJeIstiUposlenik(const Uposlenik& u) {
		for (int i = 0; i < 5; i++)
		{
			if (_uposlenici[i] != nullptr && _uposlenici[i]->GetSifra() == u.GetSifra())
				return true;
		}
		return false;
	}


	//Funkciju koja omogucava angazovanje uposlenika na projektnoj aktivnosti. Funkcija treba da vrati vrijednost tipa
	//bool za uspjesno, odnosno neuspjesno dodavanje uposlenika. Nije moguce dodati istog uposlenika vise puta. Nije moguce
	//angazovati uposlenike na vec zavrsenoj aktivnosti.



	bool DodajUposlenika(const Uposlenik& u) {
		int indeks = -1;
		if (DaLiJeIstiUposlenik(u))
			return false;
		if (_zavrsena)
			return false;
		for (int i = 0; i < 5; i++)
		{
			if (_uposlenici[i] == nullptr)
			{
				indeks = i;
				break;
			}
		}
		if (indeks == -1)
			return false;
		_uposlenici[indeks] = new Uposlenik(u);
		return true;
	}
	
	//Funkciju koja uklanja uposlenika na aktivnosti sa sifrom proslijedjenom kao parametar.
	bool UkloniUposlenika(const Uposlenik& u) {
		int temp = 5;
		if (DaLiPostojiUposlenik(u) == false)
			return false;
		int indeks = -1;
		for (int i = 0; i < 5; i++)
		{
			if (_uposlenici[i] != nullptr) 
			{
				if (_uposlenici[i]->GetSifra() == u.GetSifra())
				{
					indeks = i;
				}
			}
		}
		if (indeks == -1)
		{
			return false;
		}
		delete _uposlenici[indeks];
		_uposlenici[indeks] = nullptr; 
		for (int i = indeks ; i < temp-1; i++)
		{
			if (_uposlenici[i+1] != nullptr)
			{
				_uposlenici[i] = _uposlenici[i+1];
			    _uposlenici[i + 1] = nullptr;
			}
		}
		temp--;
	}
	
};

class Projekat {
	char* _naziv;
	char* _oblast;
	int _trajanje; //Izrazeno u mjesecima
	Aktivnost* _aktivnosti;
	int _brojAktivnosti;
public:


	//Implementirati potrebne konstruktor i destruktor funkcije.
	Projekat(const char* naziv, const char* oblast, int trajanje) :_trajanje(_trajanje), _brojAktivnosti(0) {
		_naziv = AlocirajNizKaraktera(naziv);
		_oblast = AlocirajNizKaraktera(oblast);
		_aktivnosti = nullptr;
	}

	bool DaLiJeIstaAktivnost(const Aktivnost& akt) {
		for (int i = 0; i < _brojAktivnosti; i++)
		{
			if (strcmp(_aktivnosti[i].GetNaziv(), akt.GetNaziv()) == 0)
				return true;
		}
		return false;
	}
	bool DaLiPostojiAktivnost(const Aktivnost& akt) {
		for (int i = 0; i < _brojAktivnosti; i++)
		{
			if (strcmp(_aktivnosti[i].GetNaziv(), akt.GetNaziv()) == 0)
				return true;
		}
		return false;
	}

	//Funkciju za dodavanje projektnih aktivnosti. Sprijeciti dodavanje vise aktivnosti sa istim nazivom.
	//Za potrebe poredjenja aktivnosti kreirati funkciju unutar klase Aktivnosti.
	bool DodajAktivnost(const Aktivnost& akt) {
		if (DaLiJeIstaAktivnost(akt))
			return false;
		Aktivnost* temp = new Aktivnost[_brojAktivnosti + 1];
		for (int i = 0; i < _brojAktivnosti; i++)
		{
			temp[i].Kopiraj(_aktivnosti[i]);
		}
		temp[_brojAktivnosti].Kopiraj(akt);
		delete[] _aktivnosti;
		_aktivnosti = nullptr;
		_aktivnosti = temp;
		_brojAktivnosti++;
		return true;
	}
	//Funkciju koja oznacava aktivnost kao zavrsenu. Funkcija kao parametar prima naziv aktivnosti.
	bool ZavrsiAktivnost(const Aktivnost& akt) {
		if (DaLiPostojiAktivnost(akt) != true)
			return false;
		for (int i = 0; i < _brojAktivnosti; i++)
		{
			if (strcmp(_aktivnosti[i].GetNaziv(), akt.GetNaziv()) == 0)
				_aktivnosti[i].SetZavrsi();
		}
	}
	//Funkciju koja treba da aktivnosti sa proslijedjenim nazivom dodijeli novog uposlenika.
	bool DodajUposlenikaNaAktivnost(const Aktivnost& akt, const Uposlenik& u) {
		if (DaLiPostojiAktivnost(akt) != true)
			return false;
		int indeks = -1;
		for (int i = 0; i < _brojAktivnosti; i++)
		{
			if(strcmp(_aktivnosti[i].GetNaziv(), akt.GetNaziv()) == 0)
			indeks = i;
		}
		_aktivnosti[indeks].DodajUposlenika(u);
	}
    //Funkciju koja treba da vrati sve uposlenike angazovane na odredjenoj aktivnosti. Ulazni parametar je naziv aktivnosti.

	Uposlenik** SviUposlenici(const Aktivnost& akt) {
		if (DaLiPostojiAktivnost(akt) != true)
			return false;
		int brojac = 0, indeks = 0;
		for (int i = 0; i < _brojAktivnosti; i++)
		{
			if (strcmp(_aktivnosti[i].GetNaziv(),akt.GetNaziv())==0)
			{
				return _aktivnosti[i].GetUposlenici();
			}
		}
	}
	//Funkciju koja uklanja odredjenog uposlenika na aktivnosti. Ulazni parametri funkcije su naziv aktivnosti i sifra uposlenika.
	//projekat.UkloniUposlenikaSaAktivnosti(aktivnost1.GetNaziv(), u1.GetSifra()))
	bool UkloniUposlenikaSaAktivnosti(const char* nazivAkt, int sifra) {
		for (int i = 0; i < _brojAktivnosti; i++)
		{
			if (strcmp(_aktivnosti[i].GetNaziv(), nazivAkt) == 0) {
				for (int j = 0; j < 5; j++)
				{
					if (_aktivnosti[i].GetUposlenici()[j] != nullptr && _aktivnosti[i].GetUposlenici()[j]->GetSifra() == sifra) {
						_aktivnosti[i].UkloniUposlenika(*_aktivnosti[i].GetUposlenici()[j]);
						return true;
					}
				}
			}
		}
		return false;
	}

	//Funkciju koja pronalazi uposlenika sa najvecim brojem angazmana na aktivnostima.
	int BrojacAktivnosti(const Uposlenik& u) 
	{
		int brojac = 0;
		for (int i = 0; i < _brojAktivnosti; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				if ( _aktivnosti[i].GetUposlenici()[j]!=nullptr && _aktivnosti[i].GetUposlenici()[j]->GetSifra() == u.GetSifra()  )
					brojac++;
			}
		}
		return brojac;
	}


	Uposlenik* UposlenikSaMaxAngazmana() {
		int temp = 0, indeksAktivnosti, indeksUposlenika, min = 0;
		for (int i = 0; i < _brojAktivnosti; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				if (_aktivnosti[i].GetUposlenici()[j] != nullptr) {
				temp = BrojacAktivnosti(*_aktivnosti[i].GetUposlenici()[j]);
				if (temp > min) {
					min = temp;
					indeksAktivnosti = i;
					indeksUposlenika = j;
				}
				}
			}
		}
		return _aktivnosti[indeksAktivnosti].GetUposlenici()[indeksUposlenika];
	}


	//Funkciju koja pronalazi 3 uposlenika koja su angazovana na najvecem broju nezavrsenih aktivnosti.


	//Funkciju koja ispisuje sve zavrsene aktivnosti na projektu.

};


/*Kreirati globalnu funkciju koja pronalazi najuspjesnijeg uposlenika na projektima (vise projekata) proslijedjenim kao parametar.
Uposlenik se smatra najuspjesnijim ako je angazovan na najvecem broju zavrsenih aktivnosti. Ako vise uposlenika
ima isti broj zavrsenih aktivnosti, uspjesnijim se smatra onaj cije su aktivnosti trajale duze.
*/


int main()
{
	//Testirati sve dostupne funkcionalnosti
	Uposlenik u1("Denis", "Music", "Uposlenik");
	Uposlenik u2("Jasmin", "Azemovic", "Uposlenik");
	Uposlenik u3("Zanin", "Vejzovic", "Uposlenik");
	Uposlenik u4("Adel", "Handzic", "Uposlenik");
	Uposlenik u5("Larisa", "Sparvalo", "Uposlenik");
	u1.Info();
	u2.Info();
	u3.Info();
	cout << endl << endl;
	Aktivnost aktivnost1("Aktivnost 1", 15);
	Aktivnost aktivnost2("Aktivnost 2", 10);
	Aktivnost aktivnost3("Aktivnost 3", 7);
	aktivnost1.Info();
	cout <<"DDDD" << u1.GetBrojac() << endl;

	cout << endl;
	if (aktivnost1.DodajUposlenika(u1))
		cout << endl << endl << "Uposlenik uspjesno dodan." << endl << endl;
	else
		cout << endl << endl << "Uposlenik nije uspjesno dodan." << endl << endl;
	if (aktivnost1.DodajUposlenika(u5))
		cout << endl << endl << "Uposlenik uspjesno dodan." << endl << endl;
	else
		cout << endl << endl << "Uposlenik nije uspjesno dodan." << endl << endl;
	if (aktivnost1.DodajUposlenika(u3))
		cout << endl << endl << "Uposlenik uspjesno dodan." << endl << endl;
	else
		cout << endl << endl << "Uposlenik nije uspjesno dodan." << endl << endl;
	if (aktivnost3.DodajUposlenika(u2))
		cout << endl << endl << "Uposlenik uspjesno dodan." << endl << endl;
	else
		cout << endl << endl << "Uposlenik nije uspjesno dodan." << endl << endl;	
	if (aktivnost2.DodajUposlenika(u1))
		cout << endl << endl << "Uposlenik uspjesno dodan." << endl << endl;
	else
		cout << endl << endl << "Uposlenik nije uspjesno dodan." << endl << endl;

	if (aktivnost1.UkloniUposlenika(u3))
		cout << endl << endl << "Uposlenik uspjesno uklonjen." << endl << endl;
	else
		cout << endl << endl << "Uposlenik nije uspjesno uklonjen." << endl << endl;

	//aktivnost1.Info();

	Projekat projekat("Projekat 1", "Informatika", 18);

	if (projekat.DodajAktivnost(aktivnost1))
		cout << endl << "Aktivnost je uspjesno dodana." << endl;
	else
		cout << endl << "Aktivnost nije uspjesno dodana." << endl;

	if (projekat.DodajAktivnost(aktivnost2))
		cout << endl << "Aktivnost je uspjesno dodana." << endl;
	else
		cout << endl << "Aktivnost nije uspjesno dodana." << endl;

	if (projekat.ZavrsiAktivnost(aktivnost1))
		cout << endl << "Aktivnost je uspjesno zavrsena." << endl;
	else
		cout << endl << "Aktivnost nije zavrsena." << endl;

	if (projekat.DodajUposlenikaNaAktivnost(aktivnost3, u3))
		cout << endl << "Uposlenik uspjesno dodan na aktivnost." << endl;
	else
		cout << endl << "Uposlenik nije uspjesno dodan na aktivnost." << endl;
	system("CLS");
	Uposlenik** uposlenici = projekat.SviUposlenici(aktivnost1);
	cout << "Svi uposlenici sa aktivnosti: " << aktivnost1.GetNaziv() << endl;
	for (int i = 0; i < 5; i++)
		if (uposlenici[i] != nullptr)
			uposlenici[i]->Info();

	if(projekat.UkloniUposlenikaSaAktivnosti(aktivnost1.GetNaziv(), u4.GetSifra()))
		cout<<endl<<endl<<"Uposlenik sa sifrom "<<u1.GetSifra()<<" je uspjesno uklonjen."<<endl<<endl;
	else
		cout << endl << endl << "Uposlenik sa sifrom " << u1.GetSifra() << " nije uspjesno uklonjen." << endl << endl;


	Uposlenik *uposlenikMax = projekat.UposlenikSaMaxAngazmana();
	if (uposlenikMax != nullptr) {
		cout << endl << endl << "Uposlenik sa max angazmana: " << endl << endl;
		uposlenikMax->Info();
	}






	system("pause");
	return 0;
}


