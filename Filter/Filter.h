#pragma once

#include<iostream>
#include<string>
#include <fstream>


class Filter
{
	char pach[MAX_PATH];
	std::string* page;						//	страница
	std::string* buf;				//	отфильтрована страница
	std::ifstream in;
	long long pos;
	bool Number;
	bool LatinCharacters;
	bool CyrillicCharacters;
	bool Punctuation;
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
public:
	Filter();
	~Filter();

	void Start();
	void Menu();
	// загрузка страницы
	void DownloadPage();
	// загрузка файла
	void DownloadFile();
	// вывод на екран
	void Show();
	//	фильтрация текста
	void FilteringText();

	// замена цифр		1 2 3 4 5 6 7 8 9 0
	void ReplaceNumber();
	// замена символов латинского алфавита	A a E e I i O o U u Y y B b C c D d F f G g H h J j K k L l M m N n P p Q q R r S s T t V v W w X x Y y Z z
	void ReplaceLatinCharacters();
	// замена символов кириллицы  А а Б б В в Г г Д д Е е Ё ё Ж ж З з И и Й й К к Л л М м Н н О о П п Р р С с Т т У у Ф ф Х х Ц ц Ч ч Ш ш Щ щ Ъ ъ Ы ы Ь ь Э э Ю ю Я я
	void ReplaceCyrillicCharacters();
	// замена символов пунктуации		! \" #  $  %  & ' ( ) * + ,  -  . / : ; <  = > ? @ [ \\ ] ^ _ ` { | } ~ „ … ‘ ’ “ ”  – — ¦ § © ¶
	void ReplacePunctuation();
};

