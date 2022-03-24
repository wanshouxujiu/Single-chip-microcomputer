​
#include <REGX52.H>
 
//=========================串口==========================
 
void UART_Init() //9600bps @12:F9 F9  11.0592:FA FA
{
    PCON |= 0x80;      //波特率加倍
    SCON |= 0x50;      //8位数据，可变波特率（模式选择）
    TMOD &= 0x0F;      //定时器1
    TMOD |= 0x20;      //八位自动重装模式
    TL1 = 0xFA;        //设置定时器1初始值，可去除？
    TH1 = 0xFA;        //设置定时器1重载值
    ET1 = 0;           //禁止定时器1中断
    TR1 = 1;
    EA = 1;
    ES = 1;
}
 
 
void UART_SendByte(unsigned char Byte)
{
    SBUF = Byte;
    while(TI == 0); //类似消抖？
    TI = 0; //由手册得知每次请求中断后必须置回1
}
 
//========================信号产生========================
 
unsigned char PWM_high1 = 5;
unsigned char PWM_high2 = 23;
unsigned char PWM_high_num1 = 0;
unsigned char PWM_high_num2 = 0;
 
void PWM()
{
    if(PWM_high_num1 <= PWM_high1)
    {
        P0_0 = 1;    //将电机的PWM线接到P0_0口
    }
    else
    {
        P0_0 = 0;    //限制高电平长度
    }
    if(PWM_high_num1 == 200)    //PWM需要的信号周期为20ms
    {
        PWM_high_num1 = 0;
    }
    //====================================================//
        if(PWM_high_num2 <= PWM_high2)
    {
        P0_1 = 1;    //将电机的PWM线接到P0_1口
    }
    else
    {
        P0_1 = 0;    //限制高电平长度
    }
    if(PWM_high_num2 == 200)    //PWM需要的信号周期为20ms
    {
        PWM_high_num2 = 0;
    }
 
}
 
//========================定时器设置=======================
 
void Timer0Init()        //100微秒@12:9C FF  11.0592:A4 FF
{
    TMOD &= 0xF0;        //设置定时器模式
    TMOD |= 0x01;        //设置定时器模式
    TL0 = 0xA4;        //设置定时初始值
    TH0 = 0xFF;        //设置定时初始值
    TF0 = 0;        //清除TF0标志
    TR0 = 1;        //定时器0开始计时
    ET0 = 1;
    EA = 1;
    PT0 = 1;
}
 
unsigned char KeyNum = 0;
unsigned char lock = 1;    //上锁
 
void main()    //============主函数============
{
    Timer0Init();
    UART_Init();
    PWM_high2 = 23;
    PWM_high1 = 5;
    while(1)
    {
        if(KeyNum == 0x01 && lock % 2)
        {
            PWM_high2 = 23;
            PWM_high1 = 23;    //开灯
        }
        if(KeyNum == 0x02 && lock % 2)
        {
            PWM_high1 = 5;
            PWM_high2 = 5;     //关灯
        }
        if(KeyNum == 0x03 && lock % 2)
        {
            PWM_high2 = 23;
            PWM_high1 = 5;     //复位
        }
        if(KeyNum == 0xFF)
        {
            lock++;    //密码上锁
        }
        if(KeyNum == 0x04)
        {
            PWM_high2 = 0;    //待机模式
            PWM_high1 = 0;
        }
    }
}
 
//========================定时器0中断=========================
 
void Timer0_Rountine() interrupt 1
{
    TH0 = 0xFF;        //设置定时初始值
    TL0 = 0xA4;        //设置定时初始值
    PWM_high_num1++;
    PWM_high_num2++;
    PWM();
}
 
//========================串口中断============================
 
void UART_Routine() interrupt 4 //接收到数据跳到这执行
{
    if(RI == 1)
    {
        KeyNum = SBUF;
        UART_SendByte(SBUF);
        RI = 0;
    }
}

​//效果展示：https://www.bilibili.com/video/BV14P4y1u7on?spm_id_from=333.1007.top_right_bar_window_history.content.click