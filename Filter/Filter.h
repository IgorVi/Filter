#pragma once

#include<iostream>
#include<string>
#include <fstream>


class Filter
{
	char pach[MAX_PATH];
	std::string* page;						//	��������
	std::string* buf;				//	������������� ��������
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
	// �������� ��������
	void DownloadPage();
	// �������� �����
	void DownloadFile();
	// ����� �� �����
	void Show();
	//	���������� ������
	void FilteringText();

	// ������ ����		1 2 3 4 5 6 7 8 9 0
	void ReplaceNumber();
	// ������ �������� ���������� ��������	A a E e I i O o U u Y y B b C c D d F f G g H h J j K k L l M m N n P p Q q R r S s T t V v W w X x Y y Z z
	void ReplaceLatinCharacters();
	// ������ �������� ���������  � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � �
	void ReplaceCyrillicCharacters();
	// ������ �������� ����������		! \" #  $  %  & ' ( ) * + ,  -  . / : ; <  = > ? @ [ \\ ] ^ _ ` { | } ~ � � � � � �  � � � � � �
	void ReplacePunctuation();
};

