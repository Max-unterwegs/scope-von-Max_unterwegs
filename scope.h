#ifndef SCOPE_H
#define SCOPE_H

#include <QWidget>

/*------------------------用户代码头文件---------------------------*/
#include <QtSerialPort/QSerialPort>//串口
#include <QtSerialPort/QSerialPortInfo>//串口
#include <QDebug>//用于在控制台输出调试信息
#include <chrono>//时间
#include <QPainter>//坐标系绘图
#include <QVector>//数据处理
#include <voltparamrech.h>//用户自定义头文件
#include "fft_transform.h"//FFT变换
#include "ui_scope.h"//UI界面
#include "valuepack.h"//数据包
#include <complex>//复数
QT_BEGIN_NAMESPACE
namespace Ui {
class scope;
}
QT_END_NAMESPACE

class scope : public QWidget
{
    Q_OBJECT

public:
    scope(QWidget *parent = nullptr);
    ~scope();

private slots:
    void mousemove(QMouseEvent *event, QCustomPlot *cmPlot,int graphIndex,QCPItemTracer *tracer,QCPItemText *tracerLabel);

    void on_pb_searchport_clicked();

    void on_pb_openport_clicked();

    QVector<float> movingAverageFilter(const QVector<float>& data, int windowSize);//滑动平均滤波

    QVector<float> adaptive_filter(QVector<float> *input);//自适应滤波

    void performFFT(const QVector<float>& data, int graphIndex);
    
    void AnalyzeData();//数据读取

    void setupPlot();//初始化

    void on_pb_save_clicked();

    void on_pb_mode_clicked();

    void on_pb_CH1_clicked();

    void on_pb_CH2_clicked();

    void on_verticalSlider_show_valueChanged(int value);

    void on_verticalSlider_real_valueChanged(int value);


    void on_pb_setindex_clicked();

    void on_verticalSlider_alpha_valueChanged(int value);

    void on_verticalSlider_beta_valueChanged(int value);

private:
    Ui::scope *ui;
    QSerialPort *myserial;//声明串口类，myserial是QSerialPort的实例
    bool serial_flag,start_flag;//定义两个标志位
    QByteArray alldata;//接收串口数据

    std::chrono::high_resolution_clock::time_point mystarttime;//开始时间
    std::chrono::high_resolution_clock::time_point mycurrenttime;//当前时间
    std::chrono::high_resolution_clock::time_point mylasttime;//上一次时间

    // 数据缓冲区
    QVector<float> buffer1; // 缓冲区1
    QVector<float> buffer2; // 缓冲区2
    int dataPointsInRange = 1000000; // 在 x 轴范围内的数据点数
    int showcount = 0 ,realcount = 0 ,showcountmax = 50, realcountmax = 1;//显示数据分频，实际数据分频
    QVector<float> filteredData1;//滤波后的数据1
    QVector<float> filteredData2;//滤波后的数据2
    double maxMagnitude[3] = {0.0, 0.0, 0.0};//最大幅值
    // 滤波后的结果变量
    float filteredValue1 = 0.0;
    float filteredValue2 = 0.0;
    // 采样间隔
    float sampling_interval = 0.0;
    double frecuncy = 0.0;//频率
    float minY1 , maxY1 , minY2 , maxY2;//最大最小值
    bool x_y_flag = false,CH1_flag = true,CH2_flag = true,indexflag = false;//标志位
    float alpha=0.05f,beta=0.05f;//滤波参数
    RxPack rx_pack;//数据包
    QCPItemTracer *tracer_CH;//游标
    QCPItemText *tracerLabel_CH;//游标标签

};
#endif // SCOPE_H
