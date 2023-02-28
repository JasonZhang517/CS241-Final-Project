#ifndef INPUT_CONTROLLING_LAYOUT_H
#define INPUT_CONTROLLING_LAYOUT_H

#include <QWidget>
#include <QtCharts/QChart>
#include <QtWidgets>
#include <Traveltime.h>
#include <QLineEdit>
#include <QGridLayout>
#include <QString>
#include <progressThread.h>

class inputControlling: public QWidget {

    Q_OBJECT
public:
    explicit inputControlling(QWidget* =nullptr);
    ~inputControlling();
    DataSet Dataset;
public:
    QString loadedFile;
    QPushButton *fileBtn;
    QLabel *lineEdit;
    QGridLayout *mainLayout;
    QSpinBox *timeStart;
    QSpinBox *timeEnd;
    QSpinBox *dayStart;
    QSpinBox *dayEnd;
    QLabel *monthDisplay;
    QLabel *yearDisplay;
    QLineEdit *fieldStart;
    QLineEdit *fieldEnd;
    // DataSet* passData(DataSet& dataset);
    // Data importCSV(const QString& fileName);
    QProgressDialog *progressDialog;
signals:
    void passing(const DataSet*);
    void complete();
//    void passBar(int a);
private slots:
    void loadCSV();
//    void startProgress();
//    void slotStart();
//    void slotStop();
    void finished();
    void receive(Data* re);
public:
//    ProgressThread *theImportThread;
    int count;
    importThread* readThread[16];
public slots:
//    Data importCSV();
private:
    void initializeBar();
};

#endif // INPUT_CONTROLLING_LAYOUT_H

