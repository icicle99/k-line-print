
// KLinePrintDoc.h : CKLinePrintDoc 类的接口
//
#include <string>
#include "KLineCollection.h"
#include "TickReader.h"
#include "KLineReader.h"
#include "PlaybackConfig.h"
#include "CalendarGenerator.h"

using namespace std;

#pragma once

class CKLinePrintDoc : public CDocument
{
protected: // 仅从序列化创建
	CKLinePrintDoc();
	DECLARE_DYNCREATE(CKLinePrintDoc)

private:

	int	m_nCurrentTickIdx;		//	当前tick的索引
	int m_nCurrentTickTime;		//	当前时间

	TickCollection	m_TickData;
	KLineCollection m_15SecData;
	KLineCollection m_1MinData;
	KLineCollection m_DayData;

	KLineReader		m_KLineReader;
	TickReader		m_TickReader;

	Calendar		m_FilteredCalendar;		// 根据回放选项过滤出来的符合条件的日期

// 操作
public:

// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// 实现
public:
	virtual ~CKLinePrintDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	string m_CurCsvFile;
	string m_CurDayFile;

	void LoadPlaybackCalendar(PlaybackConfig pbConfig);
	BOOL ValidatePlaybackConfig(int nDate, PlaybackConfig pbConfig);

	BOOL HasPlaybackCalendar() { return (m_FilteredCalendar.size()!=0); }

	void ViewNeighborDate(BOOL bPrev);
	void ReloadByDate(int nDate);
	void LoadKLineGroup(string targetCsvFile);
	void ReloadDetailData(int second);

	KLine GenerateDayLineFromQuoteData(string path, int nDate);

	//  加载下一日数据准备播放
	BOOL LoadNextDay();

	/* 显示至某个时点 */

	/* nTillTime		:	-1是播放所有，0是播放首tick，其他是播放至目标时间 */
	/* nTillDate(日线)	:	-1是播放所有日期，其他是播放至目标日期 */

	void DisplayTill(int nTillMilliTime = -1, int nTillDate = -1);

	/* 播放至某个时点 */
	void PlayTillTime(int nTillMilliTime);

	//	获取当前价格(0为当前tick)
	Tick GetTick(int nOffset = 0);

	//  获取当前时间
	int GetCurTickTime()
	{
		return m_nCurrentTickTime;
	}

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	afx_msg void OnGenDayline();
};


