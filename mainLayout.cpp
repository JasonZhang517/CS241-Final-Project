#include <mainLayout.h>
#include <QHBoxLayout>
stackWidget::~stackWidget()
{

}
mainLayout::~mainLayout()
{

}
stackWidget::stackWidget(QWidget* parent): QWidget(parent)
{
    list=new QListWidget(this);
    list->insertItem(0,tr("Orders&time"));
    list->insertItem(1,tr("Orders&grid"));
    list->insertItem(2,tr("Orders&Proportion"));
    list->insertItem(3,tr("Prediction"));
    list->insertItem(4,tr("details"));
    stack =new QStackedWidget(this);
    time=new ChartWidget();
    grid=new GridChart();
    pie=new PieChart();
    predict=new Prediction();
    travel=new Traveltime();
    stack->addWidget(time);
    stack->addWidget(grid);
    stack->addWidget(pie);
    stack->addWidget(predict);
    stack->addWidget(travel);
    auto mainLayout=new QHBoxLayout(this);
    list->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
    stack->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
    mainLayout->addWidget(list);
    mainLayout->addWidget(stack);
    mainLayout->setMargin(5);
    mainLayout->setSpacing(5);
    connect(list,SIGNAL(currentRowChanged(int)),stack,SLOT(setCurrentIndex(int)));
}
mainLayout::mainLayout(QWidget* parent): QWidget(parent)
{
    splitterMain=new QSplitter(Qt::Horizontal,0);
    inputControlling *input=new inputControlling(splitterMain);
    input->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    splitterMain->addWidget(input);
    stackWidget *right=new stackWidget(splitterMain);
    splitterMain->addWidget(right);
    splitterMain->setStretchFactor(1,1);
    auto mainLayout=new QHBoxLayout(this);
    mainLayout->addWidget(splitterMain);
    connect(input, SIGNAL(passing(const DataSet*)),right,SLOT(loadCSV(const DataSet*)));
}
void stackWidget::loadCSV(const DataSet* a)
{
     time->getData(*a);
    grid->getData(*a);
    pie->getData(*a);
    predict->loadData(*a);
    travel->loadData(*a);
}
