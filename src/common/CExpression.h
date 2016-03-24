/**
* @file CExpression.h
*/

#pragma once
#ifndef _INC_CEXPRSSION_H
#define _INC_CEXPRSSION_H

#include <cinttypes>
#include "common.h"
#include "graycom.h"
#include "CVarDefMap.h"
#include "ListDefContMap.h"

#define _ISCSYMF(ch) ( IsAlpha(ch) || (ch)=='_')	// __iscsym or __iscsymf
#define _ISCSYM(ch) ( isalnum(ch) || (ch)=='_')		// __iscsym or __iscsymf

#ifndef M_PI 
	#define M_PI 3.14159265358979323846
#endif

#define EXPRESSION_MAX_KEY_LEN SCRIPT_MAX_SECTION_LEN


enum DEFMSG_TYPE
{
	#define MSG(a,b) DEFMSG_##a,
	#include "../tables/defmessages.tbl"
	DEFMSG_QTY
};

enum INTRINSIC_TYPE
{
	INTRINSIC_ABS = 0,
	INTRINSIC_COS,
	INTRINSIC_ID,
	INTRINSIC_ISNUMBER,
	INTRINSIC_ISOBSCENE,
	INTRINSIC_LOGARITHM,
	INTRINSIC_NAPIERPOW,
	INTRINSIC_QVAL,
	INTRINSIC_RAND,
	INTRINSIC_RANDBELL,
	INTRINSIC_SIN,
	INTRINSIC_SQRT,
	INTRINSIC_STRASCII,
	INTRINSIC_STRCMP,
	INTRINSIC_STRCMPI,
	INTRINSIC_StrIndexOf,
	INTRINSIC_STRLEN,
	INTRINSIC_STRMATCH,
	INTRINSIC_STRREGEX,
	INTRINSIC_TAN,
	INTRINSIC_QTY
};

static LPCTSTR const sm_IntrinsicFunctions[INTRINSIC_QTY+1] =
{
	"ABS",		// absolute
	"COS",		// cosinus
	"ID",		// ID(x) = truncate the type portion of an Id
	"ISNUMBER",		// ISNUMBER(var)
	"ISOBSCENE",	// test for non-allowed strings
	"LOGARITHM",	// log()/log10()
	"NAPIERPOW",	// exp()
	"QVAL",		// QVAL(test1,test2,ret1,ret2,ret3) - test1 ? test2 (< ret1, = ret2, > ret3)
	"RAND",		// RAND(x) = flat random
	"RANDBELL",	// RANDBELL(center,variance25)
	"SIN",
	"SQRT",		// sqrt()
	"StrAscii",
	"STRCMP",	// STRCMP(str1,str2)
	"STRCMPI",	// STRCMPI(str1,str2)
	"StrIndexOf", // StrIndexOf(string,searchVal,[index]) = find the index of this, -1 = not here.
	"STRLEN",	// STRLEN(str)
	"STRMATCH",	// STRMATCH(str,*?pattern)
	"STRREGEX",
	"TAN",		// tan()
	NULL
};

extern class CExpression
{
public:
	static const char *m_sClassName;
	CVarDefMap		m_VarDefs;		// Defined variables in sorted order.
	CVarDefMap		m_VarGlobals;	// Global variables
	CListDefMap		m_ListGlobals; // Global lists
	CListDefMap		m_ListInternals; // Internal lists
	CGString		m_sTmp;

								//	defined default messages
	static TCHAR sm_szMessages[DEFMSG_QTY][128];			// like: "You put %s to %s"
	static LPCTSTR const sm_szMsgNames[DEFMSG_QTY];		// like: "put_it"

public:
	// Strict G++ Prototyping produces an error when not casting char*& to const char*&
	// So this is a rather lazy workaround
	inline int64_t GetSingle( LPTSTR &pArgs )
	{
		return GetSingle(const_cast<LPCTSTR &>(pArgs));
	}

	inline int GetRange( LPTSTR &pArgs )
	{
		return static_cast<int>(GetRange(const_cast<LPCTSTR &>(pArgs)));
	}

	inline int GetRangeVals( LPTSTR &pExpr, int64_t * piVals, int iMaxQty )
	{
		return GetRangeVals(const_cast<LPCTSTR &>(pExpr), piVals, iMaxQty );
	}

	inline int64_t GetVal( LPTSTR &pArgs )
	{
		return GetVal(const_cast<LPCTSTR &>(pArgs));
	}

	// Evaluate using the stuff we know.
	int64_t GetSingle( LPCTSTR & pArgs );
	int64_t GetVal( LPCTSTR & pArgs );
	int64_t GetValMath( int64_t lVal, LPCTSTR & pExpr );
	int GetRangeVals(LPCTSTR & pExpr, int64_t * piVals, int iMaxQty);
	int64_t GetRange(LPCTSTR & pArgs);

public:
	CExpression();
	~CExpression();

private:
	CExpression(const CExpression& copy);
	CExpression& operator=(const CExpression& other);
} g_Exp;

bool IsValidDef( LPCTSTR pszTest );
bool IsValidGameObjDef( LPCTSTR pszTest );

bool IsSimpleNumberString( LPCTSTR pszTest );
bool IsStrNumericDec( LPCTSTR pszTest );
bool IsStrNumeric( LPCTSTR pszTest );
bool IsStrEmpty( LPCTSTR pszTest );
inline extern bool IsCharNumeric( char & Test );

// Numeric formulas
int64_t Calc_GetRandLLVal( int64_t iqty );
int64_t Calc_GetRandLLVal2( int64_t iMin, INT64 iMax );
int Calc_GetRandVal( int iqty );
int Calc_GetRandVal2( int iMin, int iMax );
int Calc_GetLog2( UINT iVal );
int Calc_GetSCurve( int iValDiff, int iVariance );
int Calc_GetBellCurve( int iValDiff, int iVariance );

dword ahextoi( LPCTSTR pArgs ); // Convert hex string to integer
int64_t ahextoi64( LPCTSTR pArgs ); // Convert hex string to INT64

#define Exp_GetSingle( pa ) static_cast<int>(g_Exp.GetSingle( pa ))
#define Exp_GetLLSingle( pa ) g_Exp.GetSingle( pa )
#define Exp_GetVal( pa )	static_cast<int>(g_Exp.GetVal( pa ))
#define Exp_GetLLVal( pa )	g_Exp.GetVal( pa )
#define Exp_GetRange( pa )	g_Exp.GetRange( pa )

#endif	// _INC_CEXPRSSION_H
