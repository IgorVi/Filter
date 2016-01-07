#include<algorithm>
#include <Windows.h>

#include "Menu.h"
#include "Filter.h"


Filter::Filter() :
page(new std::string),
buf(new std::string),
Number(false),
LatinCharacters(false),
CyrillicCharacters(false),
Punctuation(false),
pos(0)
{
	*pach = '\0';
	h = GetStdHandle(STD_OUTPUT_HANDLE);
}


Filter::~Filter()
{
	delete page;
	delete buf;
}

void Filter::ReplaceNumber() {
	std::replace_copy_if(buf->begin(), buf->end(), buf->begin(),
		[](char n){return n >= '0' && n <= '9'; }, ' ');
}

void Filter::ReplaceLatinCharacters() {
	std::replace_copy_if(buf->begin(), buf->end(), buf->begin(),
		[](char n){return n >= 'A' && n <= 'Z' || n >= 'a' && n <= 'z'; }, ' ');
}

void Filter::ReplaceCyrillicCharacters() {
	std::replace_copy_if(buf->begin(), buf->end(), buf->begin(),
		[](char n){return n >= 'ј' && n <= '€' || n == '®' || n == 'Є'; }, ' ');
}

void Filter::ReplacePunctuation() {
	std::replace_copy_if(buf->begin(), buf->end(), buf->begin(),
		[](char n){return n >= '!' && n <= '/' || n >= ':' && n <= '@' || n >= '[' && n <= '`'
		|| n >= '{' && n <= '~' || n == 'Д' || n == 'Е' || n >= 'С' && n <= 'Ч'
		|| n == '¶' || n == 'І' || n == '©' || n == 'ґ'; }, ' ');
}

void Filter::Show() {
	FilteringText();
	system("cls");
	std::cout << "\n\n\n-----------------------------------------------------------------------------------\n";
	std::ostream_iterator<char> out(std::cout);
	std::copy(buf->begin(), buf->end(), out);
}

void Filter::FilteringText() {

	*buf = *page;

	if (Number){
		ReplaceNumber();
	}
	if (LatinCharacters){
		ReplaceLatinCharacters();
	}
	if (CyrillicCharacters){
		ReplaceCyrillicCharacters();
	}
	if (Punctuation){
		ReplacePunctuation();
	}
}

void Filter::Menu() {
	CONSOLE_CURSOR_INFO cci = { sizeof(cci), true };
	SetConsoleCursorInfo(h, &cci);

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(h, &csbi);

	enum keys{ ESC = 27, UP = 72, DOWN = 80, ENTER = 13, LEFT = 75, RIGHT = 77 };

	const int count = 7;
	char* MenuList[count] = { "  символы кириллицы  ", "  символы латинского алфавита  ", "  цифры  ", "  символы пунктуации  ",
						 "  перва€ страница  ", "                 выход                ", "  следующа€ страница  "};
	bool* Action[count] = { &CyrillicCharacters, &LatinCharacters, &Number, &Punctuation };

	int key, n = 0;
	do{
		for (int i = 0; i < count; ++i){
			if (i == 0){
				SetConsoleCursorPosition(h, { 0, 1 });
			}
			else if (i == 4){
				SetConsoleCursorPosition(h, { 0, 40 });
				std::cout << "-----------------------------------------------------------------------------------\n";
			}

			if (i == n){
				SetConsoleTextAttribute(h, ((0xF << 4) | 0xC));
				std::cout << MenuList[i];
				SetConsoleTextAttribute(h, csbi.wAttributes);
			}
			else {
				std::cout << MenuList[i];
			}
		}

		key = _getch();
		if (key == ENTER)
		{
			if (n < 4){
			(*Action[n]) ? (*Action[n]) = false : (*Action[n]) = true;
			Show();
			}
			else if (n == 6){
				DownloadPage();
				Show();
			}
			else if (n == 4){
				pos = 0;
				DownloadPage();
				Show();
			}
			else if (n == 5) { break; }
		}
		else if (key == 224)
		{
			key = _getch();
			switch (key)
			{
			case LEFT:
				if (n == 0) { n = 3; }
				else if (n == 4) { n = count - 1; }
				else { --n; }
				break;
			case RIGHT:
				if (n == 3) { n = 0; }
				else if (n == count - 1) { n = 4; }
				else { ++n; }
				break;
			case UP:
			case DOWN:
				(n >= 0 && n <= 3) ? n = 4 : n = 0;
				break;
			}
		}
	} while (key != ESC);
}

void Filter::DownloadFile() {
	do{
		system("cls");
		std::cout << "\nЌажмите Enter дл€ загрузки User.txt или\n¬ведите им€ файла дл€ загрузки: User.txt";
		std::cout << "\nѕример Test.txt, User.txt" << std::endl;
		SetConsoleCursorPosition(h, { 32, 2 });
		std::cin.getline(pach, MAX_PATH);
		if (*pach == '\0'){
			strcpy_s(pach, "User.txt");
		}
		in.open(pach, std::ios::in);
	} while (!in);
}

void Filter::DownloadPage() {
	char buf = '\0';
	page->clear();
	in.seekg(pos, std::ios::beg);
	if (in){
		for (int i = 0; i < 34; ++i){
			for (int j = 0; in && j < 83; ++j){
				in.get(buf);
				page->push_back(buf);
				if (buf == '\n') break;
			}
		}
		if (-1L == (pos = in.tellg())){
			in.close();
			pos = 0;
			in.open(pach);
		}		
	}
}

void Filter::Start() {
	DownloadFile();
	DownloadPage();
	*buf = *page;
	std::cout << "\n\n\n-----------------------------------------------------------------------------------\n";
	Show();
	Menu();
}