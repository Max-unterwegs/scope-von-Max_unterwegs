# Scope von Max_unterwegs

## 项目简介

Scope von Max_unterwegs 是一个基于硬禾学堂“寒假一起练——基于stm32的双通道示波器学习平台”的板卡硬件实现的口袋虚拟仪器🥰🥰🥰

## 演示、使用与项目报告（包含使用说明）

### 演示与使用视频：

[【项目展示】基于stm32g031的虚拟仪器实现](https://www.bilibili.com/video/BV1KuRYYEE86?vd_source=8f015028f10842cbab187c6f57ec6ec9)

### 项目报告（包含使用说明）：

[2025寒假练 - 基于stm32g031的双通道示波器学习平台板卡硬件实现的口袋虚拟仪器](https://www.eetree.cn/project/detail/3948)

🌈<u>**或见master分支中的项目报告**</u>🌈

## 安装使用

请按照以下步骤来安装和配置此项目：

1. 克隆此仓库到本地：

```bash
git clone https://github.com/Max-unterwegs/scope-von-Max_unterwegs.git
```

2. 进入项目目录：

```bash
cd scope-von-Max_unterwegs
```

3. 按开头嵌入的视频教程进行项目使用

## ⚠️分支说明（<u>找源代码必看！！！</u>）⚠️

本仓库包含多个分支，每个分支都有其特定的用途：

- `master`：主分支，包含项目的即点即用文件

- - `M_Uscope.exe`:Qt上位机程序，点击即用
  - `M_Uscope`：Qt上位机未打包程序
  - `scope.hex`：单片机hex文件，可用STM32CubeProgrammer、FlyMcu等烧录工具烧录。

    ⚠️**<u>注意：其中M_Uscope.exe可能会被windows当做病毒删除，下载使用时关闭windows实时防护即可，如实在不行可以使用文件夹里的未打包程序或用Qtproject分支里的源代码直接编译出程序。</u>** ⚠️
  
- `Qtproject`：Qt项目分支，其中包含有Qt上位机程序源代码，使用Qt 6.5.3 QMake  3.1+MinGW-W64-builds-5.0.0工具链Release编译生成程序

- `stm32project`：stm32项目分支，其中包含有stm32程序源代码，使用stm32cubemx+keil+vscode keil assistant插件 工具链基于HAL库编译生成程序

## 贡献

欢迎贡献！如果您有兴趣为本项目做出贡献，请按照以下步骤进行：

1. Fork 此仓库。
2. 创建一个新的分支：

```bash
git checkout -b feature-branch
```

3. 提交你的更改：

```bash
git commit -am 'Add some feature'
```

4. 推送到远程分支：

```bash
git push origin feature-branch
```

5. 创建一个 Pull Request。


## 许可证

此项目使用 [MIT 许可证](LICENSE) - 请查阅 `LICENSE` 文件以了解更多细节。

## 参考

本项目部分代码与移植库参考仓库与博客：

**协议发包解包：**[提高开发效率-蓝牙调试器](https://www.jianshu.com/p/1a8262492619)

**按键扫描：**[stm32单片机按键消抖、长按、多击终极解决方案_csdn stm32硬件高频消抖-CSDN博客](https://blog.csdn.net/m0_46704668/article/details/113360878)

**FFT变换：**[GitHub - mborgerding/kissfft at 131.1.0](https://github.com/mborgerding/kissfft/tree/131.1.0)  Author：Mark Borgerding

**OLED驱动与图模提取：**[波特律动LED字模生成器](https://led.baud-dance.com/)

## 作者信息

🌐**<u>有问题也可直接邮箱联系</u>**：max_unterwegs@126.com

**主页：** [Max-unterwegs的主页](https://max-unterwegs.github.io/)

**本github仓库：** https://github.com/Max-unterwegs
