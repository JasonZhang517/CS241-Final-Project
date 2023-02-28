#ifndef PREDICTION_H
#define PREDICTION_H
#include <functional>
#include <algorithm>
#include <QVector2D>
#include <PieChart.h>
struct pair{
    int gridid;
    int key;
};

class Prediction:public QWidget{
    Q_OBJECT
public:
    explicit Prediction(QWidget* =nullptr);
    ~Prediction();
    DataSet savedData;
private:
    void updateData();
private:
    void initLayout();
public:
    void loadData(const DataSet&,int,int);
    void loadData(const DataSet&);
private slots:
    void showInformationMsg();
private:
    QPushButton* informationBtn;
private slots:
    void loadData();
private:
    QVector<pair> targetData;
    QVector<pair> sortedData;
    QSpinBox* start = nullptr;
    QSpinBox* end = nullptr;
    QLabel* Origin;
    QLineEdit* OriginInput;
    QLabel* Destination;
    QLineEdit* DestinationInput;
    QLabel* Probable;
    QLabel* DestDisplay;
    QLabel* Average;
    QLabel* TimeDisplay;
    QLabel* FeeDisplay;
    QPushButton* Calculate;
    int time;
    int qualifiedOrders;
    double totalfee;
};

#endif // PREDICTION_H
