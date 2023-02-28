#ifndef PROGRESSDLG_H
#define PROGRESSDLG_H

#endif // PROGRESSDLG_H
#include <QtWidgets>
#include <QWidget>
#include <QGridLayout>
class ProgressDlg: public QDialog
{
    Q_OBJECT
public:
    ProgressDlg(QWidget *parent=0);
    ~ProgressDlg();
private:
    QLabel *FileNum;
    QLineEdit *FileNumLineEdit;
    QLabel *ProgressType;
    QComboBox *comboBox;
    QProgressBar *progressBar;
    QPushButton *starBtn;
    QGridLayout *mainLayout;
};
