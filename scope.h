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
    void on_pb_searchport_clicked();

    void on_pb_openport_clicked();

    QVector<float> movingAverageFilter(const QVector<float>& data, int windowSize);//滑动平均滤波

    void performFFT(const QVector<float>& data, int graphIndex);
    
    void AnalyzeData();//数据读取

    void setupPlot();//初始化

    void on_pb_save_clicked();

    void on_pb_mode_clicked();

    void on_pb_CH1_clicked();

    void on_pb_CH2_clicked();

private:
    Ui::scope *ui;
    QSerialPort *myserial;//声明串口类，myserial是QSerialPort的实例
    bool serial_flag,start_flag;//定义两个标志位
    QByteArray alldata;//接收串口数据
    //绘图函数
    std::chrono::high_resolution_clock::time_point mystarttime;
    std::chrono::high_resolution_clock::time_point mycurrenttime;
    std::chrono::high_resolution_clock::time_point mylasttime;

};
#endif // SCOPE_H
