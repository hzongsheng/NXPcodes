#include "self_include.h"


void  main(void)
{
  
     init_img();
     ftm_pwm_init(S3010_FTM, S3010_CH,S3010_HZ,60);      //��ʼ�� ��� PWM 
     ftm_pwm_init(FTM0, FTM_CH3,10*1000,20); //��ʼ�����
     gpio_init(PTD5,GPO,0);
         
    while(1)
    {   
      
        ftm_pwm_duty(FTM0,FTM_CH3,20); //�������
        camera_get_img();                                   //����ͷ��ȡͼ��  
        img_extract(img, imgbuff,CAMERA_SIZE);                  //��ѹͼ��
        Road();  
        imgdeal();
        vcan_sendimg(img, CAMERA_W * CAMERA_H);                  //���͵���λ��
        PID();

    }
}

