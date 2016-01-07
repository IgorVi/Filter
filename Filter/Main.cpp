#include <Windows.h>

#include "Filter.h"

int main()
{
	SetConsoleTitleA("Filter");
	system("mode con cols=83 lines=44");	//	установка размеров окна консоли
	system("color F0");						//	izmenenie cveta fona i teksta   F - fon, 0 - text
	setlocale(LC_ALL, "Russian");

	Filter f;

	f.Start();

	return 0;
}