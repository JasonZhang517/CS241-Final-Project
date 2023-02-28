
#include <QFile>
#include <QTextStream>
#include <input_controlling_layout.h>
#include <QDateTime>

Data inputControlling::importCSV(const QString& fileName){
    QFile file("D:/CS241FinalProject/updated Dataset/Dataset-CS241-2020/Dataset-CS241-2020/order_20161101_part0.csv");
    Data data;
    if (file.open(QIODevice::ReadOnly|QIODevice::Text)){
        QTextStream in(&file);
        QString line;
        auto attr= in.readLine().splitRef(",");
        while(in.readLineInto(&line)){
            auto num=line.splitRef(",");
            auto newsingle=OrderInformation(num[1].toInt(),
                    num[2].toInt(),num[3].toDouble(),num[4].toDouble(),num[5].toDouble(),
                    num[6].toDouble(), num[7].toDouble());
            data.push_back(newsingle);
        }
    }
    Dataset.push_back(data);
    emit passing(&Dataset);
    return data;
}
