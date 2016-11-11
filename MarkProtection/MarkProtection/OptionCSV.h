#pragma once
class OptionCSV
{
public:
	OptionCSV();
	~OptionCSV();
public:
	CString Protection;
	CString Special;
	CString Trades;
	CString Name;
	CString BQty;
	CString SQty;
	CString Price;
	CString Time;
	CString OrderNo;
	CString Status;
	CString ExtOrderNo;
	CString Source;
public:
	void Set(CString strRow);
};

