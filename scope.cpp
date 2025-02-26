#include "scope.h"
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
    ui->userimage->setPixmap(QPixmap(":/icons/favicon.ico"));
    ui->likelabel->setPixmap(QPixmap(":/icons/like.png"));
    QMovie  * miaohamovie  = new  QMovie( ":/icons/miaoha.gif" );
    QMovie  * sinmovie  = new  QMovie( ":/icons/scopeimage.gif" );
    ui->miaohagiflabel-> setMovie(miaohamovie);
    ui->singiflabel-> setMovie(sinmovie);
    miaohamovie -> start();
    sinmovie -> start();

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

// 自适应滤波函数
QVector<float> scope::adaptive_filter(QVector<float> *input) {
    QVector<float> output;
    int length = input->size();

    output.resize(length);  // 初始化 output 的大小，使其与 input 相同
    output[0] = (*input)[0];
    for (int i = 1; i < length; i++) {
        float error = (*input)[i] - output[i - 1];
        output[i] = output[i - 1] + alpha * error + beta * ((*input)[i] - (*input)[i - 1]);
    }
    return output;
}


void scope::performFFT(const QVector<float>& data, int graphIndex) {
    int nfft = data.size();
    QVector<std::complex<float>> fftOutput;
    fft_transform(data, fftOutput, nfft);

    QVector<double> frequencies(nfft);
    QVector<double> magnitudes(nfft);

    for (int i = 0; i < nfft; ++i) {
        frequencies[i] = i * frecuncy / nfft;
        magnitudes[i] = std::abs(fftOutput[i]);
    }
    double maxFAtmp = frequencies[std::max_element(magnitudes.begin()+int(0.2*nfft/frecuncy), magnitudes.end())-magnitudes.begin()];
    if(graphIndex == 0)
    {
        ui->lineFrequencyCH1->setText(QString::number(maxFAtmp));//显示CH1频率;
        ui->linePeriodCH1->setText(QString::number(1/maxFAtmp));//显示CH1周期;
    }
    else
    {
        ui->lineFrequencyCH2->setText(QString::number(maxFAtmp));//显示CH2频率;
        ui->linePeriodCH2->setText(QString::number(1/maxFAtmp));//显示CH2周期;
    }
    // qDebug()<<"nfft:"<<nfft;
    // for (int i = 0; i < nfft; ++i)
    //     qDebug()<<"i"<<i<<"fftOutput:"<<fftOutput[i].real()<<"i:"<<fftOutput[i].imag()<<"magnitude:"<<magnitudes[i];
    // system("pause");

    QPen pen;
    pen.setWidth(1); // 设置画笔线条宽度
    pen.setColor(graphIndex == 0 ? Qt::blue : Qt::red); // 设置画笔颜色
    ui->fft_plot->graph(graphIndex)->setPen(pen); // 设置画笔颜色
    ui->fft_plot->graph(graphIndex)->setData(frequencies, magnitudes);
    ui->fft_plot->graph(graphIndex)->setName("CH" + QString::number(graphIndex + 1));

    // 动态设置 x 轴和 y 轴范围及步长值
    double maxFrequency = frecuncy / 2;
    maxMagnitude[graphIndex] = *std::max_element(magnitudes.begin(), magnitudes.end());
    maxMagnitude[2] = fmax(maxMagnitude[0],maxMagnitude[1]);
    ui->fft_plot->xAxis->setLabel("频率 (Hz)");
    ui->fft_plot->yAxis->setLabel("幅度");
    ui->fft_plot->xAxis->setRange(0, static_cast<int>(maxFrequency*3/2)); // 只显示正频率部分
    ui->fft_plot->yAxis->setRange(0, static_cast<int>(maxMagnitude[2]*2));

    QCPAxisTickerFixed *xTicker = new QCPAxisTickerFixed();
    xTicker->setTickStep(static_cast<int>(maxFrequency /10)); // 设置 x 轴刻度步长为整数
    ui->fft_plot->xAxis->setTicker(QSharedPointer<QCPAxisTickerFixed>(xTicker));

    QCPAxisTickerFixed *yTicker = new QCPAxisTickerFixed();
    yTicker->setTickStep(static_cast<int>(maxMagnitude[2] /10)); // 设置 y 轴刻度步长为整数
    ui->fft_plot->yAxis->setTicker(QSharedPointer<QCPAxisTickerFixed>(yTicker));

    ui->fft_plot->axisRect()->setupFullAxesBox(true); // 设置缩放，拖拽，设置图表的分类图标显示位置
    ui->fft_plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes);
    ui->fft_plot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop | Qt::AlignRight); // 图例显示位置右上
    ui->fft_plot->legend->setVisible(true); // 显示图例

    // tracer_fft_CH1 = new QCPItemTracer(ui->fft_plot); //生成游标
    // tracer_fft_CH1->setPen(QPen(Qt::red));
    // tracer_fft_CH1->setBrush(QBrush(Qt::red));
    // tracer_fft_CH1->setStyle(QCPItemTracer::tsCircle);
    // tracer_fft_CH1->setSize(5);
    // tracerLabel_fft_CH1 = new QCPItemText(ui->fft_plot);
    // tracerLabel_fft_CH1->setLayer("overlay");
    // tracerLabel_fft_CH1->setPen(QPen(Qt::blue));
    // tracerLabel_fft_CH1->setPositionAlignment(Qt::AlignLeft | Qt::AlignTop);
    // tracerLabel_fft_CH1->position->setParentAnchor(tracer_fft_CH1->position);
    // connect(ui->fft_plot, &QCustomPlot::mouseMove, this, [this](QMouseEvent* event) {
    //     mousemove(event, ui->fft_plot, 0,tracer_fft_CH1,tracerLabel_fft_CH1);
    // });

    // tracer_CH2 = new QCPItemTracer(ui->fft_plot); //生成游标
    // tracer_CH2->setPen(QPen(Qt::blue));
    // tracer_CH2->setBrush(QBrush(Qt::blue));
    // tracer_CH2->setStyle(QCPItemTracer::tsCircle);
    // tracer_CH2->setSize(5);
    // tracerLabel_CH2 = new QCPItemText(ui->fft_plot);
    // tracerLabel_CH2->setLayer("overlay");
    // tracerLabel_CH2->setPen(QPen(Qt::blue));
    // tracerLabel_CH2->setPositionAlignment(Qt::AlignLeft | Qt::AlignTop);
    // tracerLabel_CH2->position->setParentAnchor(tracer_CH2->position);
    // connect(ui->fft_plot, &QCustomPlot::mouseMove, this, [this](QMouseEvent* event) {
    //     mousemove(event, ui->fft_plot, 1,tracer_CH2,tracerLabel_CH2);
    // });

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
            //清空图像数据
            ui->scope_plot->graph(0)->data()->clear();
            ui->scope_plot->graph(1)->data()->clear();
            connect(myserial,&QSerialPort::readyRead,this,&scope::AnalyzeData);
            mystarttime = std::chrono::high_resolution_clock::now();//图像横坐标初始值参考点，读取初始时间
            mycurrenttime = mystarttime;//图像横坐标初始值参考点，读取初始时间
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
    ui->comboBox->clear();//清空cmb
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

void scope::mousemove(QMouseEvent *event, QCustomPlot *cmPlot,int graphIndex,QCPItemTracer *tracer,QCPItemText *tracerLabel)
{
    //获得鼠标位置处对应的横坐标数据x
    double x = cmPlot->xAxis->pixelToCoord(event->pos().x());

    tracer->setGraph(cmPlot->graph(graphIndex)); //将游标和该曲线图层想连接
    tracer->setGraphKey(x); //将游标横坐标（key）设置成刚获得的横坐标数据x
    tracer->setInterpolating(true); //游标的纵坐标可以通过曲线数据线性插值自动获得（这就不用手动去计算了）
    tracer->updatePosition(); //使得刚设置游标的横纵坐标位置生效
    //以下代码用于更新游标说明的内容
    double xValue = tracer->position->key();
    double yValue = tracer->position->value();
    tracerLabel->setText(QString("x = %1, y = %2").arg(xValue).arg(yValue));
    cmPlot->replot(); //不要忘了重绘
}

void scope::AnalyzeData()
{
    showcount = (showcount+1)%showcountmax;
    realcount = (realcount+1)%realcountmax;
    QByteArray mytemp = myserial->readAll();//定义mytemp为串口读取的所有数据
    qDebug()<<"mytemp:"<<mytemp;
    // QString StrI1=tr(mytemp.mid(mytemp.indexOf("CH1:")+4,mytemp.indexOf("V,")-mytemp.indexOf("CH1:")-4));//自定义了简单协议，通过前面字母读取需要的数据
    // QString StrI2=tr(mytemp.mid(mytemp.indexOf("CH2:")+4,mytemp.indexOf("V.")-mytemp.indexOf("CH2:")-5));
    // float dataI1=StrI1.toFloat();//将字符串转换成float类型进行数据处理
    // float dataI2=StrI2.toFloat();//将字符串转换成float类型进行数据处理
    readValuePack(&rx_pack,(unsigned char*)mytemp.data(), mytemp.size());
    float dataI1 = rx_pack.floats[0];
    float dataI2 = rx_pack.floats[1];
    QString StrI1=QString::number(dataI1);//将float类型数据转换成字符串
    QString StrI2=QString::number(dataI2);//将float类型数据转换成字符串
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
        // filteredData1 = movingAverageFilter(buffer1, 5); // 使用所有数据进行滤波);
        filteredData1 = adaptive_filter(&buffer1); // 使用所有数据进行滤波
        filteredValue1 = filteredData1.last(); // 获取最新的滤波结果
    }

    if (buffer2.size() >= 5) {
        //filteredData2 = movingAverageFilter(buffer2, 5);
        filteredData2 = adaptive_filter(&buffer2); // 使用所有数据进行滤波
        filteredValue2 = filteredData2.last(); // 获取最新的滤波结果
    }

    StrI1=QString::number(filteredValue1);//将float类型数据转换成字符串
    StrI2=QString::number(filteredValue2);//将float类型数据转换成字符串

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


    mylasttime = mycurrenttime;//将当前时间赋值给上一次时间
    mycurrenttime = std::chrono::high_resolution_clock::now();//获取系统时间

    // 计算采样间隔
    auto time_diff  = std::chrono::duration_cast<std::chrono::nanoseconds>(mycurrenttime - mylasttime); // 计算时间差;
    frecuncy = 1.0e9/time_diff.count(); // 转换为Hz
    sampling_interval = 1/frecuncy; // 转换为秒

    if(realcount == 0)
    {
        ui->lcdNumberCH1->display(StrI1);//显示读取CH1值
        ui->lcdNumberCH2->display(StrI2);//显示读取CH2值
        ui->lcdNumberFrecuncy->display(frecuncy);//显示读取频率
    }

    qDebug()<<"采样频率:"<<frecuncy;
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
        // ui->linePeriodCH1->setText(QString::number(getPeriod(filteredData1, sampling_interval)));//显示CH1周期;
        // ui->lineFrequencyCH1->setText(QString::number(getFrequency(filteredData1, sampling_interval)));//显示CH1频率;
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
        // ui->linePeriodCH2->setText(QString::number(getPeriod(filteredData2, sampling_interval)));//显示CH2周期;
        // ui->lineFrequencyCH2->setText(QString::number(getFrequency(filteredData2, sampling_interval)));//显示CH2频率;

    }


    // 计算采样间隔
    auto time_diff_xzb  = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - mystarttime); // 计算时间差;
    double xzb = time_diff_xzb.count()/1.0e9;//获取横坐标，相对时间就是从0开始
    if(x_y_flag)
    {
        ui->scope_plot->graph(0)->addData(filteredValue1,filteredValue2);//添加数据1到曲线1
        ui->scope_plot->graph(1)->addData(xzb,filteredValue2);//添加数据2到曲线1
    }
    else
    {
        ui->scope_plot->graph(0)->addData(xzb,filteredValue1);//添加数据1到曲线0
        ui->scope_plot->graph(1)->addData(xzb,filteredValue2);//添加数据2到曲线1
        if(xzb>30)
        {
            ui->scope_plot->xAxis->setRange((double)qRound(xzb-30),xzb);//设定x轴的范围
        }
        else ui->scope_plot->xAxis->setRange(0,30);//设定x轴的范围
    }

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

    //设置曲线二
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

    tracer_CH = new QCPItemTracer(ui->scope_plot); //生成游标
    tracer_CH->setPen(QPen(Qt::green));
    tracer_CH->setBrush(QBrush(Qt::green));
    tracer_CH->setStyle(QCPItemTracer::tsCircle);
    tracer_CH->setSize(5);
    tracerLabel_CH = new QCPItemText(ui->scope_plot);
    tracerLabel_CH->setLayer("overlay");
    tracerLabel_CH->setPen(QPen(Qt::cyan));
    tracerLabel_CH->setPositionAlignment(Qt::AlignLeft | Qt::AlignTop);
    tracerLabel_CH->position->setParentAnchor(tracer_CH->position);
    connect(ui->scope_plot, &QCustomPlot::mouseMove, this, [this](QMouseEvent* event) {
        mousemove(event, ui->scope_plot, indexflag,tracer_CH,tracerLabel_CH);
    });

    ui->scope_plot->replot();
}

void scope::on_pb_save_clicked()
{
    QCustomPlot *savecustomPlot = ui->scope_plot;
    QMessageBox msgBox;
    msgBox.setWindowTitle("选择保存数据");
    msgBox.setText("请选择要保存哪个数据^_^？");
    msgBox.setIcon(QMessageBox::Question);
    msgBox.addButton("波形图", QMessageBox::YesRole);
    msgBox.addButton("FFT图", QMessageBox::ResetRole);
    msgBox.exec(); // 执行对话框
    if(msgBox.clickedButton()->text() == "FFT图")
        savecustomPlot = ui->fft_plot;
    else
        savecustomPlot = ui->scope_plot;

    QString filename = QFileDialog::getSaveFileName(nullptr,"保存波形数据",QCoreApplication::applicationDirPath(),"Image Files(*.png *.jpg *.bmp *.pdf)");

    if( filename == "" ){
        QMessageBox::information(this,"fail","保存失败");
    }
    if( filename.endsWith(".png") ){
        QMessageBox::information(this,"success","成功保存为png文件");
        savecustomPlot->savePng( filename, savecustomPlot->width(), savecustomPlot->height() );

    }
    if( filename.endsWith(".jpg")||filename.endsWith(".jpeg") ){
        QMessageBox::information(this,"success","成功保存为jpg文件");
        savecustomPlot->saveJpg( filename, savecustomPlot->width(), savecustomPlot->height() );

    }
    if( filename.endsWith(".bmp") ){
        QMessageBox::information(this,"success","成功保存为bmp文件");
        savecustomPlot->saveBmp( filename, savecustomPlot->width(), savecustomPlot->height() );

    }
    if( filename.endsWith(".pdf") ){
        QMessageBox::information(this,"success","成功保存为pdf文件");
        savecustomPlot->savePdf( filename, savecustomPlot->width(), savecustomPlot->height() );

    }
}


void scope::on_pb_mode_clicked()
{
    if(x_y_flag)
    {
        //清空图像数据
        ui->scope_plot->graph(0)->data()->clear();
        ui->scope_plot->graph(1)->data()->clear();
        ui->pb_mode->setText("X-T模式");
        x_y_flag = false;
    }
    else
    {
        //清空图像数据
        ui->scope_plot->graph(0)->data()->clear();
        ui->scope_plot->graph(1)->data()->clear();
        ui->pb_mode->setText("X-Y模式");
        x_y_flag = true;
    }
}


void scope::on_pb_CH1_clicked()
{
    if(CH1_flag)
    {
        ui->scope_plot->graph(0)->setVisible(false);
        ui->fft_plot->graph(0)->setVisible(false);
        ui->pb_CH1->setText("CH1：关");
        CH1_flag = false;
    }
    else
    {
        ui->scope_plot->graph(0)->setVisible(true);
        ui->fft_plot->graph(0)->setVisible(true);
        ui->pb_CH1->setText("CH1：开");
        CH1_flag = true;
    }
}


void scope::on_pb_CH2_clicked()
{
    if(CH2_flag)
    {
        ui->scope_plot->graph(1)->setVisible(false);
        ui->fft_plot->graph(1)->setVisible(false);
        ui->pb_CH2->setText("CH2：关");
        CH2_flag = false;
    }
    else
    {
        ui->scope_plot->graph(1)->setVisible(true);
        ui->fft_plot->graph(1)->setVisible(true);
        ui->pb_CH2->setText("CH2：开");
        CH2_flag = true;
    }
}



void scope::on_verticalSlider_show_valueChanged(int value)
{
    showcountmax = value;
    ui->label_show->setText(QString::number(value+1));
}


void scope::on_verticalSlider_real_valueChanged(int value)
{
    realcountmax = value;
    ui->label_real->setText(QString::number(value+1));
}


void scope::on_pb_setindex_clicked()
{
    if(indexflag)
    {
        ui->pb_setindex->setText("游标通道：CH1");
        indexflag = false;
    }
    else
    {
        ui->pb_setindex->setText("游标通道：CH2");
        indexflag = true;
    }
}


void scope::on_verticalSlider_alpha_valueChanged(int value)
{
    alpha = value/100.0;
    ui->label_alpha->setText("alpha:"+QString::number(alpha));
}


void scope::on_verticalSlider_beta_valueChanged(int value)
{
    beta = value/100.0;
    ui->label_beta->setText("beta:"+QString::number(beta));
}

