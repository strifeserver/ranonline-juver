//	Note : �ý�Ʈ ��ƿ��Ƽ.
//
//	(2002.12.02), [Seperator] �ʱ� ����. JDH.
//
//
#include "stdafx.h"
#include "./StringUtils.h"
#include "./CharSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

namespace STRUTIL
{
	typedef std::vector<char>	VEC_STR;
	VEC_STR g_Separator;

	void RegisterSeparator ( CString strSeparator )
	{
		if ( strSeparator.IsEmpty() )	return;

		if ( strSeparator.GetLength() > 1 )
		{
			MessageBox ( NULL, "separator must one char.", strSeparator, MB_OK );
			return;
		}

		g_Separator.push_back ( strSeparator.GetAt(0) );
		std::sort ( g_Separator.begin(), g_Separator.end() );
	}

	void ClearSeparator ()
	{
		g_Separator.clear();
	}

	const int ERR_POS = -1;

	inline char* lower_bound ( char *pFirst, DWORD dwCount, char cFIND )
	{
		for (; 0 < dwCount; )
		{
			// divide and conquer, find half that contains answer
			DWORD dwCount2 = dwCount / 2;
			char *pMiddle = pFirst;
			pMiddle += dwCount2;

			if ( *pMiddle < cFIND )
				pFirst = ++pMiddle, dwCount -= dwCount2 + 1;
			else
				dwCount = dwCount2;
		}

		return (pFirst);
	}

	inline bool binary_search ( char *pFirst, DWORD dwCount, char cFIND )
	{
		const char *pFound = lower_bound ( pFirst, dwCount, cFIND );
		return (pFound!=(pFirst+dwCount) && !(cFIND < *pFound));
	}

	inline BOOL IsSeparator ( const char *_szBuffer, int _nLength, int &_nSepLength )
	{
		_nSepLength = ERR_POS;
		if ( _szBuffer==NULL || _szBuffer[0]==NULL )		return FALSE;

		bool bFOUND = binary_search ( &g_Separator[0], (DWORD)g_Separator.size(), _szBuffer[0] );
		if ( bFOUND )
		{
			_nSepLength = 1;
			return TRUE;
		}

		_nSepLength = 0;
		return FALSE;
	}

	BOOL StringSeparate ( CString &Str, CStringArray &StrArray )
	{
		StrArray.RemoveAll ();

		CString StrTemp;
		int nLength = Str.GetLength();
		LPCTSTR szBuffer = Str.GetString();

		for ( int i=0; i<nLength; )
		{
			char cAt = szBuffer[i];

			if ( CHARSET::IsLeadChar(cAt) )
			{
				StrTemp += cAt;
				i++;

				if ( i<nLength )
				{
					StrTemp += szBuffer[i];
					i++;
				}

				continue;
			}

			int nSepLength = ERR_POS;
			if ( IsSeparator ( szBuffer+i, nLength-i, nSepLength ) )
			{
				if ( nSepLength == ERR_POS )	return FALSE;

				i += nSepLength;

				//	�и��� ��Ʈ�� �߰�.
				if ( StrTemp.GetLength() > 0 )
				{
					StrArray.Add ( StrTemp );
					StrTemp = "";
				}
			}
			else
			{
				StrTemp += cAt;
				i++;
			}
		}

		//	�и��� ��Ʈ�� �߰�.
		if ( StrTemp.GetLength() > 0 )
		{
			StrArray.Add ( StrTemp );
		}

		return FALSE;
	}

	BOOL ChangeExt ( const char* _szSrc, CString &strDes, const char* szDesExt )
	{
		char szSrcTemp[MAX_PATH] = "";
		StringCchCopy( szSrcTemp, MAX_PATH, _szSrc );

		_strlwr ( szSrcTemp );
		char* strExtension = strrchr(szSrcTemp,'.');
		if ( !strExtension )					return FALSE;

		int nLength = (int)(strExtension - szSrcTemp);
		
		for ( int i=0; i<nLength; i++ )
		{
			strDes += szSrcTemp[i];
		}
		strDes += szDesExt;

		return TRUE;
	}

	BOOL ChangeExt ( const char* _szSrc, const char* szSrcExt, CString &strDes, const char* szDesExt )
	{
		char szSrcTemp[MAX_PATH] = "";
		StringCchCopy( szSrcTemp, MAX_PATH, _szSrc );

		_strlwr ( szSrcTemp );
		char* strExtension = strrchr(szSrcTemp,'.');
		if ( !strExtension )					return FALSE;
		if ( _stricmp(strExtension,szSrcExt) )	return FALSE;

		int nLength = (int)(strExtension - szSrcTemp);
		
		for ( int i=0; i<nLength; i++ )
		{
			strDes += szSrcTemp[i];
		}

		strDes += szDesExt;

		return TRUE;
	}

	VOID OutputStrCsv( std::fstream &SFile, std::string &Str )
	{
		// Csv ���� �ε��� �� Separater�� �����ڰ� ���ӵǸ� �����ϱ⶧���� ���� �־��
		if( Str.empty() )
		{
			SFile << " " << ",";
			return;
		}

		// ���ڿ��� ��ǥ ','�� ���Ե� �� �ֱ⶧���� ����1 ���� ���� '`'�� ��ü��
		for( std::string::iterator ci = Str.begin(); ci != Str.end(); ++ci )
			if( ( *ci ) == ',' )
				*ci = '`';
		SFile << Str << ",";
	}

	VOID InputStrCsv( CString &Src, std::string &Dest )
	{
		Dest.clear();

		// OutputStrCsv ������ �����̸� Ŭ�����ϰ� �ƴϸ� ���� ����
		if( CString::StringLength( Src ) == 0 )
			return;
		if( Src.GetAt( 0 ) == ' ' && CString::StringLength( Src ) < 2 )
			return;

		// ���ڿ��� '`'�� ���ԵǾ� ������ ��ǥ ','�� ��ü��
		Src.Replace( '`', ',' );
		Dest = Src;
	}

	BOOL CheckString( const CString & strChk )
	{
		if( strChk.FindOneOf("~!@#$%^&*+|:?><,.;[]{}()\n\t\v\b\r\a\\\?\'\" ") != -1 )
		{
			return TRUE;
		}

		return FALSE;
	}
	//userpanel
	bool isCharacter(const char Character)
	{
		return ( (Character >= 'a' && Character <= 'z') || (Character >= 'A' && Character <= 'Z'));
		//Checks if a Character is a Valid A-Z, a-z Character, based on the ascii value
	}
	bool isNumber(const char Character)
	{
		return ( Character >= '0' && Character <= '9');
		//Checks if a Character is a Valid 0-9 Number, based on the ascii value
	}
	bool isValidEmailAddress(const char * EmailAddress)
	{
		CString strChk;
		strChk.Format("%s",EmailAddress);
		if( strChk.FindOneOf("~!#$%^&*+|:?><,;[]{}()\n\t\v\b\r\a\\\?\'\" ") != -1 )
		{
			return FALSE;
		}
		if(!EmailAddress) // If cannot read the Email Address...
			return 0;
		if(!isCharacter(EmailAddress[0])) // If the First character is not A-Z, a-z
			return 0;
		int AtOffset = -1;
		int DotOffset = -1;
		unsigned int Length = strlen(EmailAddress); // Length = StringLength (strlen) of EmailAddress
		for(unsigned int i = 0; i < Length; i++)
		{
			if(EmailAddress[i] == '@') // If one of the characters is @, store it's position in AtOffset
				AtOffset = (int)i;
			else if(EmailAddress[i] == '.') // Same, but with the dot
				DotOffset = (int)i;
		}
		if(AtOffset == -1 || DotOffset == -1) // If cannot find a Dot or a @
			return 0;
		if(AtOffset > DotOffset) // If the @ is after the Dot
			return 0;
		return !(DotOffset >= ((int)Length-1)); //Chech there is some other letters after the Dot
	}
	//userpanel end

	BOOL CheckVietnamString( const CString & strChk )
	{
		int size = 0;
		TCHAR chBefore = '\0';
		size = strChk.GetLength();

		TCHAR strText[MAX_PATH] = {0};
		_tcscpy( strText, strChk );

		for ( int i = 0; i < size; ++i )
		{
			if ( CheckCharSunjo(strText[i])  &&  !CheckCharMoum(chBefore) )
			{
				return TRUE;
			}

			chBefore = strText[i];
		}

		return FALSE;
	}
	BOOL CheckCharSunjo( const TCHAR chText )
	{
		const int nSungjo = 5;
		static const TCHAR szSungjo[nSungjo] = { 0xcc, 0xd2, 0xde, 0xec, 0xf2 }; // ����

		for ( int i = 0; i< nSungjo; ++i )
		{
			if ( chText == szSungjo[i] )
				return TRUE;
		}
		return FALSE;
	}

	BOOL CheckCharMoum( const TCHAR chText )
	{
		const int nMoum = 24;				
		/* A, a, E, e, I, i , O, o, U, u Y, y ��Ʈ�� ������ */
		static const TCHAR szMoum[nMoum] = { 0x41, 0x61, 0xc3, 0xe3, 0xc2, 0xe2, 0x45, 0x65, 0xca, 0xea,
											 0x49, 0x69, 0x4f, 0x6f, 0xd4, 0xf4, 0xd5, 0xf5, 0x55, 0x75,
											 0xdd, 0xfd, 0x59, 0x79 };

		for ( int i = 0; i< nMoum; ++i )
		{
			if ( chText == szMoum[i] )
				return TRUE;
		}
		return FALSE;
	}

	BOOL CheckString_Special( const CString & strChk )
	{
		if( strChk.FindOneOf("_~!@#$%^&*+|:?><,.;[]{}()\n\t\v\b\r\a\\\?\'\" ") != -1 )
		{
			return TRUE;
		}

		return FALSE;
	}

	BOOL CheckString_Special2( const CString & strChk )
	{
		if( strChk.FindOneOf("~!#$%^&*+|:?><,;[]{}()\n\t\v\b\r\a\\\?\'\" ") != -1 )
		{
			return TRUE;
		}

		return FALSE;
	}

	BOOL CheckString_Letter( const CString & strChk )
	{
		if( strChk.FindOneOf("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") != -1 )
		{
			return TRUE;
		}

		return FALSE;
	}
};

void CSEPARATOR::Register ( char cSEP )
{
	m_Separator.push_back ( cSEP );
	std::sort ( m_Separator.begin(), m_Separator.end() );
}

void CSEPARATOR::Clear ()
{
	m_Separator.clear();
}

inline bool CSEPARATOR::IsSeparator ( char cVALUE )
{
	return STRUTIL::binary_search ( &m_Separator[0], (DWORD)m_Separator.size(), cVALUE );
}

bool CSEPARATOR::DoSeparate ( const std::string strSource, std::vector<std::string> &strArray )
{
	strArray.clear();
	std::string strtemp;
	strtemp.reserve ( strSource.size() );

	//CString StrTemp;
	int nLength = (int)strSource.length();
	const char* szSOURCE = strSource.c_str();

	for ( int i=0; i<nLength; )
	{
		char cVAL = szSOURCE[i];

		if ( CHARSET::IsLeadChar(cVAL) )
		{
			strtemp += cVAL;
			++i;

			if ( i<nLength )
			{
				strtemp += szSOURCE[i];
				++i;
			}

			continue;
		}

		if ( !IsSeparator(cVAL) )
		{
			strtemp += cVAL;
			++i;
			continue;
		}

		++i;

		//	�и��� ��Ʈ�� �߰�.
		if ( !strtemp.empty() )
		{
			strArray.push_back ( strtemp );
			strtemp = "";
		}
	}

	//	�и��� ��Ʈ�� �߰�.
	if ( !strtemp.empty() )
	{
		strArray.push_back ( strtemp );
	}

	return FALSE;
}