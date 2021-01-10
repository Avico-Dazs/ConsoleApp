#include "pch.h"
#include "CommandArgs.h"

#define MAXARGSCOUNT 100

CCommandArgs::CCommandArgs(const TCHAR* strCommandLine)
{
	Init();

	CString str(strCommandLine);
	TRACE(_T("Command Line:%s"), str);
	str = str.Trim();
	const int nLenOrg = str.GetLength();
	if (nLenOrg <= 0) ASSERT(FALSE);

	// インデックス０のファイルチェック
	m_strExePath = GetNextArg(str);
	CFileFind find;
	if (!find.FindFile(m_strExePath))
	{
		m_error = EError::EError_NotFileExist;
		return;
	}

	// 引数を取得する。
	while (m_nArgsCount <= MAXARGSCOUNT)
	{
		const CString arg = GetNextArg(str);
		if (arg.GetLength() <= 0) break;
		m_commandArgs.push_back(arg);
		m_nArgsCount++;
	}
}

CString CCommandArgs::GetExePath() const
{
	return m_strExePath;
}

CString CCommandArgs::GetArgs(UINT nIndex) const
{
	if (m_commandArgs.size() <= nIndex)
	{
		ASSERT(FALSE);
		return _T("");
	}
	return m_commandArgs[nIndex];
}

SIZE_T CCommandArgs::GetArgsSize() const
{
	return (UINT)m_nArgsCount;
}

CCommandArgs::CCommandArgs()
{
	Init();
}

CString CCommandArgs::GetNextArg(CString& str)
{
	const int nLen = str.GetLength();
	if (nLen <= 0) return _T("");
	CString strRet = _T("");
	str.Trim();
	TCHAR wcFirst = str.GetAt(0);
	BOOL isCout = (wcFirst == '\"');
	if (isCout)
	{
		// " がある場合は " が二つあったらBreak
		int nCoutCount = 0;
		for (int i = 0; i < nLen; i++)
		{
			TCHAR wc = str.GetAt(i);
			strRet += wc;
			if (wc == '\"')
			{
				nCoutCount++;
				if (nCoutCount >= 2) break;
			}
		}
	}
	else
	{
		// 空白が出たらBreak
		for (int i = 0; i < nLen; i++)
		{
			TCHAR wc = str.GetAt(i);
			if (wc == ' ') break;
			strRet += wc;
		}
	}
	str = str.Right(nLen - strRet.GetLength());
	str.Trim();
	// 最後に両端の " を削除しておく
	if(isCout)strRet.Trim('\"');
	return strRet;
}

void CCommandArgs::Init()
{
	m_strExePath = _T("");
	m_error = EError::NoError;
	m_nArgsCount = 0;
}
