#pragma once

#include "ui_GuiProcess.h"
#include "Process.h"
#include "framelesswindow.h"

Q_GUI_EXPORT QPixmap qt_pixmapFromWinHICON(HICON icon);

struct Process_State_Struct
{
	QString			txtFilter;
	int				cmbArch;
	bool			cbSession;
};

class TreeWidgetItem : public QTreeWidgetItem 
{
public:
	TreeWidgetItem(int type = 0);

private:
	bool operator< (const QTreeWidgetItem & rhs) const;
};

class GuiProcess : public QWidget
{
	Q_OBJECT

public:
	GuiProcess(QWidget * parent = Q_NULLPTR, FramelessWindow * FramelessParent = Q_NULLPTR);
	~GuiProcess();

private:

	Ui::frm_proc ui;
	FramelessWindow * frameless_parent;

	Process_State_Struct	*	pss;
	Process_Struct			*	ps;
	QFileSystemModel			model;
	SORT_SENSE					sort_sense;
	bool						native;
	int							m_OwnSession;
	std::vector<Process_Struct*> m_ProcList;

	QPixmap pxm_error;
	QPixmap pxm_generic;

protected:
	bool eventFilter(QObject * obj, QEvent * event) override;

signals:
	void send_to_inj(Process_State_Struct * procStateStruct, Process_Struct * procStruct);

public slots:
	void get_from_inj(Process_State_Struct * procStateStruct, Process_Struct * procStruct);

private slots:

	void refresh_gui();
	void refresh_process();
	void filter_change(int i);
	void session_change();
	void name_change(const QString &);
	void proc_select(bool ignore = false);
	void custom_sort(int);
	void double_click_process(const QModelIndex & index);
};