void PID()
{
float kp,duoji;
    kp=0.8;
     duoji=kp*dit;
      
       if(duoji>-20&&duoji<0)
       {
       ftm_pwm_duty(S3010_FTM, S3010_CH,60+duoji);
       }
       else if(duoji>0&&duoji<20)
       {
         
      //  kp=1.2;
    // duoji=kp*dit;
         ftm_pwm_duty(S3010_FTM, S3010_CH,duoji+60);
       //  DELAY_MS(400);
         
       }
         else if(duoji<-20)
         { ftm_pwm_duty(S3010_FTM, S3010_CH,75);}
       else if(duoji>20)
         { ftm_pwm_duty(S3010_FTM, S3010_CH,50);}
       
           
     printf("dit: %5.1f\n",dit);
      printf("duoji: %5.1f\n",duoji);
      printf("\n");
      ftm_pwm_duty(FTM0,FTM_CH1,30);
}