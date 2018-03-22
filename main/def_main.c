#define S3010_FTM   FTM1
#define S3010_CH    FTM_CH0
#define S3010_HZ    (400)
#define WHITE 255
#define BLACK 0
#define top_line 10
extern uint8 imgbuff[CAMERA_SIZE];
extern uint8 img[CAMERA_H][CAMERA_W]; 


extern int L_edge[60] = {-1}, R_edge[60] = {-1},Mid_Line[60]={-1};