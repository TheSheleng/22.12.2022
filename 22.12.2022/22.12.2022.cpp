#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>

#include <sstream>
#include <codecvt>

#pragma comment(lib, "urlmon.lib")

using namespace std;

void FindPrintJSON(const wstring&, const wstring&);

int main()
{
    setlocale(LC_ALL, "Russian");

    const char* FileName = "rate.txt";

    const char* srcURL = "https://bank.gov.ua/NBUStatService/v1/statdirectory/exchange?json";
    if (S_OK == URLDownloadToFileA(NULL, srcURL, FileName, 0, NULL))
    {
        wcout << "Information updated:" << FileName;
    }

    wcout << endl << endl;

    wifstream file(FileName, ios::in);
    file.imbue(locale(std::locale::empty(), new codecvt_utf8<wchar_t>));

    if (file.is_open())
    {
        wstring buff;

        while (!file.eof())
        {
            getline(file, buff, L'\n');
             
            FindPrintJSON(buff, L"txt\":");
            FindPrintJSON(buff, L"rate\":");
        }

        file.close();
    }
}

void FindPrintJSON(const wstring& sours, const wstring& find)
{
    int pos = -1;
    while (true)
    {
        pos = sours.find(find, pos + 1);
        if (pos == wstring::npos) break;

        for (auto i = sours.begin() + pos + find.length(); i != sours.end(); ++i)
        {
            if (*i == ',') break;
            wcout << *i;
        }
        wcout << endl;
    }
}