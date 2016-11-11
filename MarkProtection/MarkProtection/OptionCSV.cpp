#include "stdafx.h"
#include "OptionCSV.h"


OptionCSV::OptionCSV()
{
}


OptionCSV::~OptionCSV()
{
}


/*
Protection,Special,TRADES,Name,BQty,SQty,Price,Time,Order#,Status,Ext.Order#,Source
N,S,XIC4.40W6,01398.XIC 2016-11 4.400 Put,,5,0.035,28/10/2016 9:50,4617,Traded,5DF15701:000A81B1,CL
N,,CLI18.50W6,02628.CLI 2016-11 18.50 Put,,6,0.16,28/10/2016 9:53,4616,Traded,5DF15701:000A0A2F,CL
N,,ACC20.00W6,00914.ACC 2016-11 20.00 Put,,3,0.18,28/10/2016 9:57,4618,Traded,5DF15701:000AA0AC,CL
*/
void OptionCSV::Set(CString strRow)
{
	int pos = 0;
	int start = 0;
	while (true) {
		pos = strRow.Find(L",", start);
		Protection = strRow.Mid(start, pos - start);
		if (pos == -1) { break; }   start = pos + 1;
		pos = strRow.Find(L",", start);
		Special = strRow.Mid(start, pos - start);
		if (pos == -1) { break; }   start = pos + 1;
		pos = strRow.Find(L",", start);
		Trades = strRow.Mid(start, pos - start);
		if (pos == -1) { break; }   start = pos + 1;
		pos = strRow.Find(L",", start);
		Name = strRow.Mid(start, pos - start);
		if (pos == -1) { break; }   start = pos + 1;
		pos = strRow.Find(L",", start);
		BQty = strRow.Mid(start, pos - start);
		if (pos == -1) { break; }   start = pos + 1;
		pos = strRow.Find(L",", start);
		SQty = strRow.Mid(start, pos - start);
		if (pos == -1) { break; }   start = pos + 1;
		pos = strRow.Find(L",", start);
		Price = strRow.Mid(start, pos - start);
		if (pos == -1) { break; }   start = pos + 1;
		pos = strRow.Find(L",", start);
		Time = strRow.Mid(start, pos - start);
		if (pos == -1) { break; }   start = pos + 1;
		pos = strRow.Find(L",", start);
		OrderNo = strRow.Mid(start, pos - start);
		if (pos == -1) { break; }   start = pos + 1;
		pos = strRow.Find(L",", start);
		Status = strRow.Mid(start, pos - start);
		if (pos == -1) { break; }   start = pos + 1;
		pos = strRow.Find(L",", start);
		ExtOrderNo = strRow.Mid(start, pos - start);
		if (pos == -1) { break; }   start = pos + 1;

		Source = strRow.Mid(start, strRow.GetLength() - start);
		break;
	}
}
