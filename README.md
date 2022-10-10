# stm32F334_HAL_Control

# 规范

## 命名注释
- 变量采用[匈牙利命名法](https://zh.m.wikipedia.org/zh-hans/%E5%8C%88%E7%89%99%E5%88%A9%E5%91%BD%E5%90%8D%E6%B3%95)
- 注释与官方格式保持一致

## 文件树
- Hardware 硬件驱动
- Midware 硬件与软件中间层

## Git规范
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


# 外设
## spi
8位传输  全双工
> Tip  初始化配置在spi.h 每次更新Cube MX 记得搬运（删除
## LCD
- SCL和SDA（DIN）分别为SPI的时钟信号线和数据线
- RES为LCD的复位信号，STM32控制其复位
- DC为数据/命令选择端，低电平写命令，高电平写数据
- CS为液晶屏片选信号，低电平使能
- BL为背光信号，低电平关闭背光
