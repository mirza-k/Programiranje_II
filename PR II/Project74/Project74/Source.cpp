#include<iostream>

using namespace std;

auto crt = "----------------------------------------------------\n";

char* AlocirajChar(const char *sadrzaj)
{
	int vel = strlen(sadrzaj) + 1;
	char *temp = new char[vel];
	strcpy_s(temp, vel, sadrzaj);
	return temp;
}

class Vrijeme
{
	int* _sati;
	int* _minute;
	int* _sekunde;
public:
	int GetSati() const { return *_sati; }
	int GetMinute() const { return *_minute; }
	void PomjeriVrijemePolijetanja(int sati, int minute) {
		*_sati += sati; *_minute += minute;
	}

	Vrijeme(const Vrijeme& v) {
		_sati = new int(*v._sati);
		_minute = new int(*v._minute);
		_sekunde = new int(*v._sekunde);
	}

	Vrijeme(int sati, int minute, int sekunde = 0) {
		_sati = new int(sati);
		_minute = new int(minute);
		_sekunde = new int(sekunde);
	}
	~Vrijeme()
	{
		delete _sati; _sati = nullptr;
		delete _minute; _minute = nullptr;
		delete _sekunde; _sekunde = nullptr;
	}

	Vrijeme& operator= (const Vrijeme& v) {
		_sati = new int(*v._sati);
		_minute = new int(*v._minute);
		_sekunde = new int(*v._sekunde);
		return *this;
	}

	//Preklopiti operator << za ispis objekata tipa Vrijeme
	friend ostream& operator<<(ostream& cout, const Vrijeme& v);
};
ostream& operator<<(ostream& cout, const Vrijeme& v) {
	cout << *v._sati << " : " << *v._minute << " : " << *v._sekunde << endl;
	return cout;
}

class Let
{
	static const  int _oznakaSize = 10;
	char _oznaka[_oznakaSize];
	char* _odrediste;
	int _brIzlazneKapije;
	Vrijeme _vrijemePolijetanja; //sati i minute
	int _trajanje; //izraÅ¾eno u minutama
	int _kasnjenje; //izraÅ¾eno u minutama

public:
	//Potrebne konstruktor i destruktor funkcije

	int GetBrKapije()const { return _brIzlazneKapije; }
	const char* GetOznaka() const { return _oznaka; }
	const char* GetOdrediste()const { return _odrediste; }
	int GetKasnjenje() const { return _kasnjenje; }
	Vrijeme GetVrijeme() const { return _vrijemePolijetanja; }
	int GetTrajanje() const { return _trajanje; }

	Let& operator=(const Let& let) {
		strncpy_s(_oznaka, let._oznaka, _TRUNCATE);
	    //strcpy_s(_oznaka, 22, let._oznaka);
		delete[] _odrediste;
		_odrediste = new char[strlen(let._odrediste) + 1];
		strcpy_s(_odrediste, strlen(let._odrediste) + 1, let._odrediste);
		_brIzlazneKapije = let._brIzlazneKapije;
		_vrijemePolijetanja = let._vrijemePolijetanja;
		_trajanje = let._trajanje;
		_kasnjenje = let._kasnjenje;
		return *this;
	}

	~Let() { delete[] _odrediste; _odrediste = nullptr; }

	Let(const Let& let):_vrijemePolijetanja(let._vrijemePolijetanja){
		strcpy_s(_oznaka, 22, let._oznaka);
		_odrediste = new char[strlen(let._odrediste) + 1];
		strcpy_s(_odrediste, strlen(let._odrediste) + 1, let._odrediste);
		_brIzlazneKapije = let._brIzlazneKapije;
		_vrijemePolijetanja = let._vrijemePolijetanja;
		_trajanje = let._trajanje;
		_kasnjenje = let._kasnjenje;
	}

	Let() : _odrediste(nullptr), _brIzlazneKapije(0), _trajanje(0), _kasnjenje(0),_vrijemePolijetanja(0,0,0)
	{
		strncpy_s(_oznaka, "------", _TRUNCATE);
	}


	Let(const char* oznaka, const char* grad, int brojIzlazneKapije, Vrijeme vrijemePolijetanja, int trajanje, int kasnjenje):_brIzlazneKapije(brojIzlazneKapije),
		_trajanje(trajanje),_kasnjenje(kasnjenje),_vrijemePolijetanja(vrijemePolijetanja)
	{
		int brKaraktera = strlen(oznaka);
		if (brKaraktera < 10) {
			strncpy_s(_oznaka, oznaka, 10);
		}
		else
			strcpy_s(_oznaka, 20,"------");
		int vel = strlen(grad) + 1;
		_odrediste = new char[vel];
		strcpy_s(_odrediste, vel, grad);
	}


	//Funkciju sa jednim parametrom koja postavlja informaciju o eventualnom kaÅ¡njenju na vrijednost zadanu parametrom.
	void SetKasnjenje(int broj)  { if (broj> 0) _kasnjenje = broj; }

	/*Preklopiti unarni operator "!" putem kojeg je moguÄ‡e saznati da li odgovarajuÄ‡i let kasni ili ne (vratiti logiÄku
	vrijednost "true" u sluÄaju kaÅ¡njenja, u suprotnom vratiti "false").*/
	bool operator! () {
		if (_kasnjenje > 0)
			return true;
		else
			return false;
	}
Vrijeme VrijemePolijetanjaSKasnjenjem() {
		return _vrijemePolijetanja;
	}


	/*Preklopiti operator + na naÄin da omoguÄ‡ava sabiranje objekata tipa "Let" i cijelog broja, pri
	Äemu se kao rezultat dobiva novi objekat tipa "Let", u kojem je vrijeme polijetanja pomjereno
	unaprijed za iznos odreÄ‘en drugim sabirkom (raÄunato u minutama).
	TakoÄ‘er preklopiti i operator "+=" koji osigurava da izraz oblika "X += Y uvijek ima isto znaÄenje kao i izraz
	"X = X + Y" */

	/* Funkciju kojom je moguÄ‡e saznati oÄekivano vrijeme polijetanja kada se uraÄuna iznos kaÅ¡njenja
	u odnosu na predviÄ‘eno vrijeme polijetanja (preklopiti operator + u klasi Vrijeme). */

	//Funkciju koja vraÄ‡a oÄekivano vrijeme slijetanja

	/*Preklopiti operator "++" na naÄin da pomijera vrijeme polaska za jedan sat unaprijed.
	  Potrebno je podrÅ¾ati i prefiksnu i postfiksnu verziju ovog operatora.*/

int VrijemePolijetanjaSaKasnjenjem(Vrijeme v, int kasnjenje) 
{
	return v.GetSati() * 60 + v.GetMinute() + kasnjenje;
}


bool operator< ( const Let& l1)
{
	int temp1 = VrijemePolijetanjaSaKasnjenjem(_vrijemePolijetanja, _kasnjenje);
	int temp2 = VrijemePolijetanjaSaKasnjenjem(l1._vrijemePolijetanja, l1._kasnjenje);
	if (temp1 < temp2)
	{
		return true;
	}
	else
		return false;
}
bool operator> (const Let& l1)
{
	int temp1 = VrijemePolijetanjaSaKasnjenjem(_vrijemePolijetanja, _kasnjenje);
	int temp2 = VrijemePolijetanjaSaKasnjenjem(l1._vrijemePolijetanja, l1._kasnjenje);
	if (temp1 > temp2)
	{
		return true;
	}
	else
		return false;
}
		/*Preklopiti operator "<<" koji treba da podrÅ¾i ispis objekata tipa "Let" na ekran. U sluÄaju da
		se radi o polijetanju bez kaÅ¡njenja, ispis bi trebao da izgleda kako slijedi:

			JFK 156 Atalanta    12:50   19:30   5

		Podaci predstavljaju redom: oznaku leta, naziv odrediÅ¡ta, vrijeme polijetanja, oÄekivano
		vrijeme slijetanja i broj izlazne kapije.

		U sluÄaju da se radi o letu koji kasni, ispis bi trebao izgledati kako slijedi:

			ZGK 932 Zagreb    15:50 (Planirano 15:30, Kasni 20 min)*/



friend ostream& operator<< (ostream& cout, Let let);
};
ostream& operator<< (ostream& cout, Let let) {
	int konacnoTrajanje = let.GetKasnjenje() + let._trajanje;
	int sati = (konacnoTrajanje / 60);
	sati *= 60;
	int minute = konacnoTrajanje - sati;
	int satiSlijetanja = sati + let.GetVrijeme().GetSati();
	int minuteSlijetanja = minute + let.GetVrijeme().GetMinute();
	if (minuteSlijetanja > 60) {
		int temp = minuteSlijetanja / 2;
		satiSlijetanja += temp;
		temp = temp * 60;
		temp = minuteSlijetanja - temp;
		minuteSlijetanja += temp;
	}
	if (minuteSlijetanja == 60)
		++satiSlijetanja;
	if (let.GetKasnjenje() == 0) {
		cout << let.GetOznaka() << "\t" << let.GetOdrediste() << "\t" << let.GetVrijeme() << "\t" << satiSlijetanja << ":" << minuteSlijetanja << "\t" << let.GetBrKapije() << endl;
		return cout;
	}
	else
	{
		int novi = let.GetVrijeme().GetMinute() - let.GetKasnjenje();
		cout << let.GetOznaka() << "\t" << let.GetOdrediste() << "\t" << let.GetVrijeme() << "Planirano (" << let.GetVrijeme().GetSati() << ":" << novi << "), kasni " << let.GetKasnjenje() << "minuta." << endl;
		return cout;
	}


}

class RasporedLetova
{
	int _brojRegistrovanihLetova;
	const int _maksimalanBrojLetova;
	Let** _letovi;

public:
	RasporedLetova(int maksimalanBrojLetova) : _maksimalanBrojLetova(maksimalanBrojLetova),
		_letovi(new Let*[_maksimalanBrojLetova]), _brojRegistrovanihLetova(0)
	{
	}

	~RasporedLetova() {
		for (int i = 0; i < _brojRegistrovanihLetova; i++)
		{
			delete _letovi[i];
			_letovi[i] = nullptr;
		}
		delete[] _letovi;
	}

	/*Preklopiti operator "+=" na naÄin da registruje novi let u raspored. Raspored letova u svakom momentu treba biti sortiran
	 prema vremenu polijetanja. Voditi raÄuna o maksimalnom broju letova.  Za potrebe poreÄ‘enja vremena polaska letova preklopiti odgovarajuÄ‡e operatore u klasi Vrijeme.*/
	


	int RacunanjeVremena(const Let& let) {
		int temp = let.GetVrijeme().GetSati() * 60 + let.GetVrijeme().GetMinute() + let.GetKasnjenje();
		return temp;
	}

	RasporedLetova& operator+= (const Let& let) {
		if (_maksimalanBrojLetova > 100)
		{
			return *this;
		}
		bool zamjena = false;
		Let privremena1, privremena2;
		if (_brojRegistrovanihLetova > 0) {
			for (int i = 0; i < _brojRegistrovanihLetova; i++)
			{
				int tempMain = RacunanjeVremena(let);
				int tempFja = RacunanjeVremena(*_letovi[i]);
				if (tempMain < tempFja)
				{
					zamjena = true;
					_letovi[_brojRegistrovanihLetova] = new Let;
					privremena1 = *_letovi[i];
					*_letovi[i] = let;
				//	_letovi[i] = new Let(privremena1);
					for (int j = i + 1; j < _brojRegistrovanihLetova+1; j++)
					{
						if(_letovi[j]->GetTrajanje()!=0)
						privremena2 = *_letovi[j];
						*_letovi[j] = privremena1;
						privremena1 = privremena2;
					}
					break;
				}
			}
				if (zamjena==false)
				{
					_letovi[_brojRegistrovanihLetova] = new Let(let);
				}
		}
		else {
			_letovi[_brojRegistrovanihLetova] = new Let(let);
		}
		_brojRegistrovanihLetova++;
		return *this;
	}
  /*Preklopiti operator "-=" na naÄin da uklanja registrovani let sa oznakom definisanom putem desnog operanda.
	   Pri tome saÄuvati redoslijed prethodno registrovanih letova. */

	RasporedLetova& operator-= (const char* oznaka) {
		for (int i = 0; i < _brojRegistrovanihLetova; i++)
		{
			if (strcmp(_letovi[i]->GetOznaka(), oznaka)==0)
			{
			delete _letovi[i];
			for (int j = i; j < _brojRegistrovanihLetova-1; j++)      // 0  1  3  4        2    5
			{
				_letovi[j] = _letovi[j + 1];
			}
			_letovi[_brojRegistrovanihLetova - 1] = nullptr;
			break;
			}
		}
		_brojRegistrovanihLetova--;
		return *this;
	}

	   //Preklopiti operator "[]" na naÄin da vraÄ‡a objekat tipa Let na osnovu proslijeÄ‘ene pozicije u rasporedu (pozicije kreÄ‡u od 1).

	Let& operator[] (int index) {
		return *_letovi[index];
	}

	   /*Preklopiti operator "()" na naÄin da letu sa definisanom oznakom pomjeri vrijeme polijetanja za vrijednost drugog parametra izraÅ¾enog
		u minutama. */

	//Raspored("TUA 192", 95);

	RasporedLetova& operator() (const char* oznaka, int brojminuta) {
		for (int i = 0; i < _brojRegistrovanihLetova; i++)
		{
			if (strcmp(_letovi[i]->GetOznaka(), "ddd")==0) {
				if (brojminuta > 60) {
				int sati = brojminuta/ 60;
				int minute = brojminuta - (sati * 60);
				_letovi[i]->GetVrijeme().PomjeriVrijemePolijetanja(sati, minute);
				}
				else if(brojminuta<60)
				{
					_letovi[i]->GetVrijeme().PomjeriVrijemePolijetanja(0, brojminuta);
				}
				else
					_letovi[i]->GetVrijeme().PomjeriVrijemePolijetanja(1, 0);
			}

		}
		return *this;
	}


		//Funkciju koja daje prosjeÄno trajanje svih pohranjenih letova.


		/*Preklopiti operator "<<" koji ispisuje kompletan spisak svih letova, sortiran po oÄekivanim vremenima polazaka.
		  Za potrebe poreÄ‘enja vremena polaska letova preklopiti odgovarajuÄ‡e operatore u klasi Vrijeme. */
   friend ostream& operator<< (ostream& cout, const RasporedLetova& rasp);
};
	ostream& operator<< (ostream& cout, const RasporedLetova& rasp) {
		for (int i = 0; i <rasp._brojRegistrovanihLetova ; i++)
		{
			cout << *rasp._letovi[i];
		}
		return cout;
	}

int main()
{


	Vrijeme v1(10, 15);
	Vrijeme v2(5, 54);
	Vrijeme v4(8, 12);
	Vrijeme v3(21, 23);
	cout << v1 << v2 << v3;
	system("CLS");

	Let let1("GEW 327", "Berlin", 4, v1, 130, 10);
	Let let2("TUA 192", "Moskva", 2, v3, 510, 0);
	Let let3("PEG 568", "Oslo", 9, v2, 445, 20);
	Let let4("ROE 346", "Bec", 9, v4, 345, 20);
	//Let let5("SIU 351", "Frankfurt", 9, v2, 400, 20);

	if (!let1)
		cout << "Let kasni" << endl;
	else
		cout << "Let je na vrijeme" << endl;

	cout << let1.VrijemePolijetanjaSKasnjenjem() << endl;

	//cout << let1.VrijemeSlijetanja()<<endl;

	if (let1 < let2)
		cout << "Let1 je prije leta2" << endl;
	else
		cout << "Let1 je poslije leta2" << endl;

	if (let1 > let2)
		cout << "Let1 je poslije leta2" << endl;
	else
		cout << "Let1 je prije leta2" << endl;

	RasporedLetova Raspored(100);

	Raspored += let1;
	Raspored += let2;
	Raspored += let3;
	Raspored += let4;
	//Raspored += let5;

	Raspored -= let1.GetOznaka();

	cout << Raspored[1] << endl;

	Raspored("TUA 192", 95);

	//cout << endl << "Prosjecno trajanje svih letova je -> " << Raspored.ProsjecnoTrajanjeLetova() << endl;

	cout << endl << Raspored << endl;



	system("pause");
	return 0;
}









