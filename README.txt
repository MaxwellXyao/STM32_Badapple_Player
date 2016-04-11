【SOL开源】STM32_Badapple_Player

在STM32上播放badapple（烂苹果）。

早先就看到B站有人做过这个，效果还不错，于是自己也想尝试一下。程序是基于我自己的开发板设计的，其中会用到FATFS，定时器，SOLGUI_V2。代码不是很多，但完成后非常有成就感——看着画面里的人物一个个在这块不大的屏幕上舞动变换，真应了那句话：有屏幕的地方就有badapple（笑）。



目前进度：已经调试通过，无warning，可以正常播放badapple，画面大小为74*56；

/*-------------------------------

平台：STM32F103C8T6

所需硬件模块：OLED12864，SD卡

-------------------------------*/


2016-4-12
SOL.lab
MaxwellXyao
Email:maxwellxyao@foxmail.com