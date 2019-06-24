#include <iostream>

#include <Windows.h>
#include <WinInet.h>
#pragma comment(lib, "wininet")

int main()
{
	char szData[2500];
	int iSum = 0;
	DWORD dwBytesRead;

	//WinInet initialisation
	HINTERNET hInternet = ::InternetOpen(
		TEXT("Mozilla/4.0 (compatible; MSIE 6.0b; Windows NT 5.0; .NET CLR 1.0.2914)"),
		INTERNET_OPEN_TYPE_PRECONFIG,
		NULL, NULL, 0);

	//Http session opening
	if (hInternet != NULL)
	{
		HINTERNET hConnect = ::InternetConnect(
			hInternet,
			TEXT("www.adventofcode.com"),
			INTERNET_DEFAULT_HTTP_PORT,
			NULL, NULL,
			INTERNET_SERVICE_HTTP,
			0, 1u);

		//Http request opening
		if (hConnect != NULL)
		{
			HINTERNET hRequest = ::HttpOpenRequest(
				hConnect,
				TEXT("GET"),
				TEXT("2017/day/1/input"),
				NULL, NULL, 0,
				INTERNET_FLAG_NO_COOKIES,
				1);

			//Cookie preparation
			LPCSTR lHead = "Cookie: _ga=GA1.2.1073035234.1524760106; "
				"_gid=GA1.2.1157811840.1531937202; "
				"_gat=1; "
				"session=53616c7465645f5f10f5fe7bd77e38c9c67ad30535d1336cfa050562192ed2f332af5ef5055796b3e03fa18995e7f31d";
			BOOL bRequest = ::HttpAddRequestHeaders(hRequest, lHead, strlen(lHead), NULL);

			//Http request forwarding
			if (hRequest != NULL)
			{
				BOOL bSend = ::HttpSendRequest(hRequest, NULL, 0, NULL, 0);
				if (bSend) {
					
					//Data reading
					BOOL bRead = ::InternetReadFile(
						hRequest,
						szData, sizeof(szData) - 1,
						&dwBytesRead);

					//Data processing
					for (unsigned int i = 0; i < dwBytesRead - 3; ++i)
					{
						if (szData[i] == szData[i + 1])	iSum += szData[i] - 48;
					}
					if (szData[dwBytesRead - 2] == szData[0]) iSum += szData[dwBytesRead - 2] - 48;				
				}
			}
			::InternetCloseHandle(hRequest);
		}
		::InternetCloseHandle(hConnect);
	}
	::InternetCloseHandle(hInternet);

	std::cout << "Capcha sum: " << iSum << std::endl;

	system("pause");
	return 0;
}