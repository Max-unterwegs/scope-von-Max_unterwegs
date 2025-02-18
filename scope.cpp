#include "scope.h"
#include "fft_transform.h"
#include "ui_scope.h"
#include <complex>

// 数据缓冲区
QVector<float> buffer1; // 缓冲区1
QVector<float> buffer2; // 缓冲区2
int dataPointsInRange = 1000000; // 在 x 轴范围内的数据点数
int showcount = 0;
const int showcountmax = 50;
QVector<QDateTime> timestamps; // 时间戳缓冲区
QVector<float> filteredData1;
QVector<float> filteredData2;

// 滤波后的结果变量
float filteredValue1 = 0.0;
float filteredValue2 = 0.0;
// 采样间隔
float sampling_interval = 0.0;

float minY1 , maxY1 , minY2 , maxY2;


scope::scope(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::scope)
{
    ui->setupUi(this);
    this->setWindowTitle(QString("M-U的示波器"));  //设置标题
    myserial = new QSerialPort();
    serial_flag = true;
    start_flag = true;
    ui->fft_plot->addGraph();//添加一条曲线
    ui->fft_plot->addGraph();//添加一条曲线
    setWindowIcon(QIcon(":/icons/favicon.ico"));
    setupPlot();//图形界面初始化函数
}

scope::~scope()
{
    delete ui;
}

// 滑动平均滤波函数
QVector<float> scope::movingAverageFilter(const QVector<float>& data, int windowSize) {
    QVector<float> filteredData;
    for (int i = 0; i < data.size(); ++i) {
        float sum = 0.0;
        int count = 0;
        for (int j = -windowSize / 2; j <= windowSize / 2; ++j) {
            int index = i + j;
            if (index >= 0 && index < data.size()) {
                sum += data[index];
                ++count;
            }
        }
        filteredData.append(sum / count);
        if (filteredData.size() > data.size()) {
            filteredData.removeFirst();
        }
    }
    return filteredData;
}

void scope::performFFT(const QVector<float>& data, int graphIndex) {
    int nfft = data.size();
    QVector<std::complex<float>> fftOutput;
    fft_transform(data, fftOutput, nfft);

    QVector<double> frequencies(nfft);
    QVector<double> magnitudes(nfft);

    double sampleRate = 1.0 / sampling_interval; // 采样率
    for (int i = 0; i < nfft; ++i) {
        frequencies[i] = i * sampleRate / nfft;
        magnitudes[i] = std::abs(fftOutput[i]);
    }


    QPen pen;
    pen.setWidth(1); // 设置画笔线条宽度
    pen.setColor(graphIndex == 0 ? Qt::red : Qt::blue); // 设置画笔颜色
    ui->fft_plot->graph(graphIndex)->setPen(pen); // 设置画笔颜色
    ui->fft_plot->graph(graphIndex)->setData(frequencies, magnitudes);
    ui->fft_plot->graph(graphIndex)->setName("CH" + QString::number(graphIndex + 1));

    // 动态设置 x 轴和 y 轴范围及步长值
    double maxFrequency = sampleRate / 2;
    double maxMagnitude = *std::max_element(magnitudes.begin(), magnitudes.end());

    ui->fft_plot->xAxis->setLabel("频率 (Hz)");
    ui->fft_plot->yAxis->setLabel("幅度");
    ui->fft_plot->xAxis->setRange(0, static_cast<int>(maxFrequency)); // 只显示正频率部分
    ui->fft_plot->yAxis->setRange(0, static_cast<int>(maxMagnitude));

    QCPAxisTickerFixed *xTicker = new QCPAxisTickerFixed();
    xTicker->setTickStep(static_cast<int>(maxFrequency / 10)); // 设置 x 轴刻度步长为整数
    ui->fft_plot->xAxis->setTicker(QSharedPointer<QCPAxisTickerFixed>(xTicker));

    QCPAxisTickerFixed *yTicker = new QCPAxisTickerFixed();
    yTicker->setTickStep(static_cast<int>(maxMagnitude / 10)); // 设置 y 轴刻度步长为整数
    ui->fft_plot->yAxis->setTicker(QSharedPointer<QCPAxisTickerFixed>(yTicker));

    ui->fft_plot->axisRect()->setupFullAxesBox(true); // 设置缩放，拖拽，设置图表的分类图标显示位置
    ui->fft_plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes);
    ui->fft_plot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop | Qt::AlignRight); // 图例显示位置右上
    ui->fft_plot->legend->setVisible(true); // 显示图例
    ui->fft_plot->replot();
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
        //清空图像数据
        ui->scope_plot->graph(0)->data()->clear();
        ui->scope_plot->graph(1)->data()->clear();
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
    showcount = (showcount+1)%showcountmax;
    QByteArray mytemp = myserial->readAll();//定义mytemp为串口读取的所有数据
    qDebug()<<"mytemp:"<<mytemp;
    QString StrI1=tr(mytemp.mid(mytemp.indexOf("CH1:")+4,mytemp.indexOf("V,")-mytemp.indexOf("CH1:")-4));//自定义了简单协议，通过前面字母读取需要的数据
    QString StrI2=tr(mytemp.mid(mytemp.indexOf("CH2:")+4,mytemp.indexOf("V.")-mytemp.indexOf("CH2:")-5));
    float dataI1=StrI1.toFloat();//将字符串转换成float类型进行数据处理
    float dataI2=StrI2.toFloat();//将字符串转换成float类型进行数据处理
    // 将数据添加到缓冲区
    buffer1.append(dataI1);
    buffer2.append(dataI2);

    // 限制缓冲区大小，避免无限增长
    if (buffer1.size() > dataPointsInRange) {
        buffer1.removeFirst();
    }
    if (buffer2.size() > dataPointsInRange) {
        buffer2.removeFirst();
    }

    // 滤波处理
    if (buffer1.size() >= 5) { // 确保有足够的数据进行滤波
        filteredData1 = movingAverageFilter(buffer1, 5); // 使用所有数据进行滤波);
        filteredValue1 = filteredData1.last(); // 获取最新的滤波结果
    }

    if (buffer2.size() >= 5) {
        filteredData2 = movingAverageFilter(buffer2, 5);
        filteredValue2 = filteredData2.last(); // 获取最新的滤波结果
    }

    StrI1=QString::number(filteredValue1);//将float类型数据转换成字符串
    StrI2=QString::number(filteredValue2);//将float类型数据转换成字符串
    ui->lineCH1->setText(StrI1);//显示读取CH1值
    ui->lineCH2->setText(StrI2);//显示读取CH2值

    // 调整 filteredData 的大小以适应 x 轴的范围
    double xRangeLower = ui->scope_plot->xAxis->range().lower;
    double xRangeUpper = ui->scope_plot->xAxis->range().upper;
    dataPointsInRange = static_cast<int>((xRangeUpper - xRangeLower) / sampling_interval);

    if (filteredData1.size() > dataPointsInRange) {
        filteredData1 = filteredData1.mid(filteredData1.size() - dataPointsInRange);
    }
    if (filteredData2.size() > dataPointsInRange) {
        filteredData2 = filteredData2.mid(filteredData2.size() - dataPointsInRange);
    }



    mycurrenttime = QDateTime::currentDateTime();//获取系统时间
    timestamps.append(mycurrenttime); // 将时间戳添加到缓冲区

    // 计算采样间隔
    if (timestamps.size() >= 2) {
        qint64 time_diff = timestamps.last().msecsTo(timestamps[timestamps.size() - 2]);//计算两次采样时间间隔,单位ms
        sampling_interval = qAbs(time_diff) / 1000.0; // 转换为秒
    }
    qDebug()<<"采样频率:"<<1.0 / sampling_interval;
    qDebug()<<"showcount:"<<showcount;
    if(filteredData1.size() > 5 && showcount == 0)
    {
        ui->lineVmaxCH1->setText(QString::number(maxY1 = getMaxVoltage(filteredData1)));//显示CH1最大值;
        ui->lineVminCH1->setText(QString::number(minY1 = getMinVoltage(filteredData1)));//显示CH1最小值;
        ui->lineVppCH1->setText(QString::number(getPeakToPeakVoltage(filteredData1)));//显示CH1峰峰值;
        ui->lineVavgCH1->setText(QString::number(getAverageVoltage(filteredData1)));//显示CH1平均值;
        ui->lineVrmsCH1->setText(QString::number(getRMSVoltage(filteredData1)));//显示CH1有效值;
        ui->lineDutyCycleCH1->setText(QString::number(getDutyCycle(filteredData1)));//显示CH1占空比;
        ui->linePulseWidthCH1->setText(QString::number(getPulseWidth(filteredData1, sampling_interval)));//显示CH1脉冲宽度;
        ui->linePeriodCH1->setText(QString::number(getPeriod(filteredData1, sampling_interval)));//显示CH1周期;
        ui->lineFrequencyCH1->setText(QString::number(getFrequency(filteredData1, sampling_interval)));//显示CH1频率;
    }
    if(filteredData2.size() > 5 && showcount == 0)
    {
        ui->lineVmaxCH2->setText(QString::number(maxY2 = getMaxVoltage(filteredData2)));//显示CH2最大值;
        ui->lineVminCH2->setText(QString::number(minY2 = getMinVoltage(filteredData2)));//显示CH2最小值;
        ui->lineVppCH2->setText(QString::number(getPeakToPeakVoltage(filteredData2)));//显示CH2峰峰值;
        ui->lineVavgCH2->setText(QString::number(getAverageVoltage(filteredData2)));//显示CH2平均值;
        ui->lineVrmsCH2->setText(QString::number(getRMSVoltage(filteredData2)));//显示CH2有效值;
        ui->lineDutyCycleCH2->setText(QString::number(getDutyCycle(filteredData2)));//显示CH2占空比;
        ui->linePulseWidthCH2->setText(QString::number(getPulseWidth(filteredData2, sampling_interval)));//显示CH2脉冲宽度;
        ui->linePeriodCH2->setText(QString::number(getPeriod(filteredData2, sampling_interval)));//显示CH2周期;
        ui->lineFrequencyCH2->setText(QString::number(getFrequency(filteredData2, sampling_interval)));//显示CH2频率;

    }

    double xzb = mystarttime.msecsTo(mycurrenttime)/1000.0;//获取横坐标，相对时间就是从0开始
    ui->scope_plot->graph(0)->addData(xzb,filteredValue1);//添加数据1到曲线1
    ui->scope_plot->graph(1)->addData(xzb,filteredValue2);//添加数据1到曲线1
    if(xzb>30)
    {
        ui->scope_plot->xAxis->setRange((double)qRound(xzb-30),xzb);//设定x轴的范围
    }
    else ui->scope_plot->xAxis->setRange(0,30);//设定x轴的范围
    ui->scope_plot->replot();//每次画完曲线一定要更新显示
    if(filteredData1.size() > 5 && showcount == 0)
    {
        performFFT(filteredData1, 0);
    }
    if(filteredData2.size() > 5 && showcount == 0)
    {
        performFFT(filteredData2, 1);
    }

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
    ui->scope_plot->yAxis->setRange(qMin(minY1, minY2), qMax(maxY1, maxY2));//设定y轴范围

    ui->scope_plot->axisRect()->setupFullAxesBox(true);//设置缩放，拖拽，设置图表的分类图标显示位置
    ui->scope_plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom| QCP::iSelectAxes);
    ui->scope_plot->axisRect()->insetLayout()->setInsetAlignment(0,Qt::AlignTop | Qt::AlignRight);//图例显示位置右上
    ui->scope_plot->legend->setVisible(true);//显示图例

    ui->scope_plot->replot();
}
