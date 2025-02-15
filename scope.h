#ifndef SCOPE_H
#define SCOPE_H

#include <QWidget>

/*------------------------用户代码头文件---------------------------*/
#include <QtSerialPort/QSerialPort>//串口
#include <QtSerialPort/QSerialPortInfo>//串口
#include <QDebug>//用于在控制台输出调试信息
#include <QTime>//定时器
#include <QPainter>//坐标系绘图
#include <QVector>//数据处理

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

    void AnalyzeData();//数据读取

    void setupPlot();//初始化

private:
    Ui::scope *ui;
    QSerialPort *myserial;//声明串口类，myserial是QSerialPort的实例
    bool serial_flag,start_flag;//定义两个标志位
    QByteArray alldata;//接收串口数据
    //绘图函数
    QDateTime mycurrenttime;//系统当前时间
    QDateTime mystarttime;//系统开始时间

};
#endif // SCOPE_H