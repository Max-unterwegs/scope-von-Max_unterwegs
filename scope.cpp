#include "scope.h"
#include "ui_scope.h"

scope::scope(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::scope)
{
    ui->setupUi(this);
    this->setWindowTitle(QString("M-U的示波器"));  //设置标题
    myserial = new QSerialPort();
    serial_flag = true;
    start_flag = true;
    setWindowIcon(QIcon(":/icons/favicon.ico"));
    setupPlot();//图形界面初始化函数

}

scope::~scope()
{
    delete ui;
}


void scope::on_pb_openport_clicked()
{
    if(serial_flag)
    {
        ui->comboBox->setDisabled(true); //禁止修改串口
        myserial->setPortName(ui->comboBox->currentText()); //设置串口号
        myserial->setBaudRate(QSerialPort::Baud115200); //设置波特
        myserial->setDataBits(QSerialPort::Data8); //设置数据位数
        myserial->setParity(QSerialPort::NoParity);//设置奇偶校验
        myserial->setStopBits(QSerialPort::OneStop);//设置停止位
        myserial->setFlowControl(QSerialPort::NoFlowControl);//非流控制
        if(myserial->open(QIODevice::ReadWrite))
        {
            connect(myserial,&QSerialPort::readyRead,this,&scope::AnalyzeData);
            mystarttime = QDateTime::currentDateTime();//图像横坐标初始值参考点，读取初始时间
            qDebug()<<"串口打开成功";
        }
        else
        {
            qDebug()<<"串口打开失败";
            //QMessageBox::warning(this,tr("waring"),tr("串口打开失败"),QMessageBox::Close);
        }
        ui->pb_openport->setText("关闭串口");
        serial_flag = false;//串口标志位置失效
    }
    else
    {
        ui->comboBox->setEnabled(true);//串口号下拉按钮使能工作
        myserial->close();
        ui->pb_openport->setText("打开串口");//按钮显示“打开串口”
        serial_flag = true;//串口标志位置工作
    }
}


void scope::on_pb_searchport_clicked()
{

    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())//读取串口信息
    {
        myserial->setPort(info);//这里相当于自动识别串口号之后添加到了cmb，如果要手动选择可以用下面列表的方式添加进去
        if(myserial->open(QIODevice::ReadWrite))
        {
            ui->comboBox->addItem(myserial->portName());//将串口号添加到cmb
            myserial->close();//关闭串口等待人为(打开串口按钮)打开
        }
    }

}

void scope::AnalyzeData()
{
    QByteArray mytemp = myserial->readAll();//定义mytemp为串口读取的所有数据
    qDebug()<<"mytemp:"<<mytemp;
    QString StrI1=tr(mytemp.mid(mytemp.indexOf("CH1:")+4,mytemp.indexOf("V,")-mytemp.indexOf("CH1:")-4));//自定义了简单协议，通过前面字母读取需要的数据
    QString StrI2=tr(mytemp.mid(mytemp.indexOf("CH2:")+4,mytemp.indexOf("V.\r\n")-mytemp.indexOf("CH2:")-5));
    ui->lineCH1->setText(StrI1);//显示读取CH1值
    ui->lineCH2->setText(StrI2);//显示读取CH2值
    float dataI1=StrI1.toFloat();//将字符串转换成float类型进行数据处理
    float dataI2=StrI2.toFloat();//将字符串转换成float类型进行数据处理
    mycurrenttime = QDateTime::currentDateTime();//获取系统时间
    double xzb = mystarttime.msecsTo(mycurrenttime)/1000.0;//获取横坐标，相对时间就是从0开始
    ui->scope_plot->graph(0)->addData(xzb,dataI1);//添加数据1到曲线1
    ui->scope_plot->graph(1)->addData(xzb,dataI2);//添加数据1到曲线1
    if(xzb>30)
    {
        ui->scope_plot->xAxis->setRange((double)qRound(xzb-30),xzb);//设定x轴的范围
    }
    else ui->scope_plot->xAxis->setRange(0,30);//设定x轴的范围
    ui->scope_plot->replot();//每次画完曲线一定要更新显示



}

void scope::setupPlot()
{
    //设置曲线一
    ui->scope_plot->addGraph();//添加一条曲线
    QPen pen;
    pen.setWidth(1);//设置画笔线条宽度
    pen.setColor(Qt::blue);
    ui->scope_plot->graph(0)->setPen(pen);//设置画笔颜色
    ui->scope_plot->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20))); //设置曲线画刷背景
    ui->scope_plot->graph(0)->setName("CH1");
    ui->scope_plot->graph(0)->setAntialiasedFill(false);
    ui->scope_plot->graph(0)->setLineStyle((QCPGraph::LineStyle)1);//曲线画笔
    ui->scope_plot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssNone,5));//曲线形状


    ui->scope_plot->addGraph();//添加一条曲线
    pen.setColor(Qt::red);
    ui->scope_plot->graph(1)->setPen(pen);//设置画笔颜色
    ui->scope_plot->graph(1)->setBrush(QBrush(QColor(0, 0, 255, 20))); //设置曲线画刷背景
    ui->scope_plot->graph(1)->setName("CH2");
    ui->scope_plot->graph(1)->setAntialiasedFill(false);
    ui->scope_plot->graph(1)->setLineStyle((QCPGraph::LineStyle)1);//曲线画笔
    ui->scope_plot->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssNone,5));//曲线形状

    QCPAxisTickerFixed *xticker = new QCPAxisTickerFixed();
    xticker->setTickStep(2);  // 设置刻度步长为2
    QCPAxisTickerFixed *yticker = new QCPAxisTickerFixed();
    yticker->setTickStep(1);  // 设置刻度步长为10


    //设置图表
    ui->scope_plot->xAxis->setLabel(QStringLiteral("时间/s"));//设置x坐标轴名称
    ui->scope_plot->xAxis->setLabelColor(QColor(20,20,20));//设置x坐标轴名称颜色
    ui->scope_plot->xAxis->setTicker(QSharedPointer<QCPAxisTicker>(xticker));
    ui->scope_plot->xAxis->setRange(0,30);//设定x轴的范围

    ui->scope_plot->yAxis->setLabel(QStringLiteral("电压/V"));//设置y坐标轴名称
    ui->scope_plot->yAxis->setLabelColor(QColor(20,20,20));//设置y坐标轴名称颜色
    ui->scope_plot->yAxis->setTicker(QSharedPointer<QCPAxisTicker>(yticker));
    ui->scope_plot->yAxis->setRange(0,17);//设定y轴范围

    ui->scope_plot->axisRect()->setupFullAxesBox(true);//设置缩放，拖拽，设置图表的分类图标显示位置
    ui->scope_plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom| QCP::iSelectAxes);
    ui->scope_plot->axisRect()->insetLayout()->setInsetAlignment(0,Qt::AlignTop | Qt::AlignRight);//图例显示位置右上
    ui->scope_plot->legend->setVisible(true);//显示图例

    ui->scope_plot->replot();
}

