#include "self_include.h"


void  main(void)
{
  
     init_img();
     ftm_pwm_init(S3010_FTM, S3010_CH,S3010_HZ,60);      //初始化 舵机 PWM 
     ftm_pwm_init(FTM0, FTM_CH3,10*1000,20); //初始化电机
     gpio_init(PTD5,GPO,0);
         
    while(1)
    {   
      
        ftm_pwm_duty(FTM0,FTM_CH3,20); //驱动电机
        camera_get_img();                                   //摄像头获取图像  
        img_extract(img, imgbuff,CAMERA_SIZE);                  //解压图像
        Road();  
        imgdeal();
        vcan_sendimg(img, CAMERA_W * CAMERA_H);                  //发送到上位机
        PID();

    }
}

