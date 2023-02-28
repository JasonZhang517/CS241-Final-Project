#ifndef MAINLAYOUT_H
#define MAINLAYOUT_H

#include <QSplitter>
#include <QTextEdit>
#include <QTextCodec>
#include <QWidget>
#include <QtCharts/QChart>
#include <QtWidgets>
#include <QLineEdit>
#include <QGridLayout>
#include <QString>
#include <QListWidget>
#include <QStackedWidget>
#include <input_controlling_layout.h>
class mainLayout:public QWidget{
    Q_OBJECT
public:
    explicit mainLayout(QWidget* =nullptr);
    ~mainLayout();

private:
    QSplitter *splitterMain;
    QLabel *labelLeft;
    QLabel *labelRight;

};
class stackWidget:public QWidget{
    Q_OBJECT
public:
    explicit stackWidget(QWidget* =nullptr);
    ~stackWidget();
private slots:
    void loadCSV(const DataSet* a);
private:
    QListWidget *list;
    QStackedWidget *stack;
    QLabel *Chart1;
    QLabel *Chart2;
    QLabel *Chart3;
    ChartWidget* time;
    GridChart* grid;
    PieChart* pie;
    Prediction* predict;
    Traveltime* travel;
};

#endif // MAINLAYOUT_H
