# stm32F334_HAL_Control

# 规范

## 命名注释
- 变量采用[匈牙利命名法](https://zh.m.wikipedia.org/zh-hans/%E5%8C%88%E7%89%99%E5%88%A9%E5%91%BD%E5%90%8D%E6%B3%95)
- 注释与官方格式保持一致
- 引脚号必须使用label代替

## 文件树
- Hardware： 硬件驱动
- Midware： 硬件与软件中间层
- Basic： CPU API的封装或其他与CPU底层相关代码

## 移植规范
尽可能不要在Hardware、Midware文件夹下的代码中调用CPU API 或寄存器

> Hardware、Midware可移植到其他CPU平台


## Git规范
### 不得push编译相关文件
### 功能修改/更新
先pull主分支，再merge新分支，更改都在自己开的分支中进行，主分支仅用于merge操作，确认不需要修改后及时删除开的分支。
### commit - m
格式为[%type] - %msg
type： 本次操作类别
- New 新增
- Del 删除
- Fix 修正
- Mix 多种操作
msg：附加的说明信息，务必是能让其他人看懂


## log规范

使用串口实现log输出，打印的Log的级别是能真实反映此Log对应的级别，标签、Log内容具有很好的可读性

### 各个Log等级的使用
Debug
> 用于调试的信息，编译进产品，但可以在运行时关闭

Info
> 例如一些运行时的状态信息，这些状态信息在出现问题的时候能提供帮助

Warning
> 警告系统出现了异常，即将出现错误

Error
> 系统已经出现了错误



# 外设
在 main.h 中 extern 外设，初始化配置依照Cube MX 生成的位置不动

## spi
8位传输  全双工

## LCD
- SCL和SDA（DIN）分别为SPI的时钟信号线和数据线
- RES为LCD的复位信号，STM32控制其复位
- DC为数据/命令选择端，低电平写命令，高电平写数据
- CS为液晶屏片选信号，低电平使能
- BL为背光信号，低电平关闭背光

## SSD1309 OLED
引脚功能同LCD


# 算法

## PID
- 单极PID   适合线性系统
- 串级PID   非线性
### 调参
- 单级：
  - 首先加P （P太小，不足；P太大，在平衡位置容易震荡；调好情况：不太会震荡，但过零后会回弹好几下才能停止） 
  - 其次加D （作用是能很好地抑制过零后的震荡）
  - 最后加I （在一定范围内修正）
- 串级：
  - 先内环后外环


## FFT




# 工具
[串口](https://github.com/rymcu/RYCOM)

[取模软件](http://en.radzio.dxp.pl/bitmap_converter/)

[显示屏Wiki，含部分驱动](http://www.lcdwiki.com/Main_Page)

# 本项目基于以下项目
[stm32-ssd1306](https://github.com/afiskon/stm32-ssd1306)
