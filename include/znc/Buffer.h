/*
 * Copyright (C) 2004-2011  See the AUTHORS file for details.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published
 * by the Free Software Foundation.
 */

#ifndef _BUFFER_H
#define _BUFFER_H

#include <znc/zncconfig.h>
#include <znc/ZNCString.h>
#include <deque>

using std::deque;

class CBufLine {
public:
	CBufLine(const CString& sFormat);
	~CBufLine();
	const CString& GetFormat() const { return m_sFormat; }
	void SetFormat(const CString& sFormat) { m_sFormat = sFormat; }
	void GetLine(CString& sRet, const MCString& msParams) const;

private:
protected:
	CString m_sFormat;
};

class CBuffer : private deque<CBufLine> {
public:
	CBuffer(unsigned int uLineCount = 100);
	~CBuffer();

	int AddLine(const CString& sFormat);
	/// Same as AddLine, but replaces a line that starts with sMatch if there is one.
	int UpdateLine(const CString& sMatch, const CString& sFormat);
	/// Same as UpdateLine, but does nothing if this exact line already exists.
	int UpdateExactLine(const CString& sFormat);
	bool GetNextLine(CString& sRet, const MCString& msParams = MCString::EmptyMap);
	bool GetLineFormat(unsigned int uIdx, CString& sRet) const;
	bool GetLine(unsigned int uIdx, CString& sRet, const MCString& msParams = MCString::EmptyMap) const;
	bool IsEmpty() const { return empty(); }
	void Clear() { clear(); }

	// Setters
	bool SetLineCount(unsigned int u, bool bForce = false);
	// !Setters

	// Getters
	unsigned int GetLineCount() const { return m_uLineCount; }
	// !Getters
private:
protected:
	unsigned int m_uLineCount;
};

#endif // !_BUFFER_H