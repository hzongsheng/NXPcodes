void Road();
int Edge_Find_1(int,char,int);
int Next_Point(int,int,char);
void imgdeal();


extern uint8 img[60][80];
extern uint8 imgbuff[CAMERA_SIZE];
//int imgnew[60][80];

float dit;

int Edge_Find_1(int row, char which_edge, int start_col)
{
	/*
   ���ܣ�Ϊ�ҵ�ĳһ�е� ���� �� ���ҡ��߽��
   ��������߽��which_edgeΪ 'L'���ұ߽�Ϊ 'R' , start_locΪ���߷��ұ߽����ʼ��
   ����ֵ����Ϊ-1 �� 80 ʱΪû�ҵ��߽磬����Ϊ���ҵ��ı߽�

   */
  
  
	if (which_edge == 'R')
	{
		if (row < 60 - 1)
		{
			while (start_col < 80)
			{ ////////////////////
				if ((img[row][start_col] == BLACK && img[row][start_col - 1] == WHITE) && ((img[row + 1][start_col] == BLACK || img[row - 1][start_col] == BLACK)))
					return start_col;
				//�ڶ����ж�������Ϊ����������,���õ�Ϊ�ڵ㣬��������ͬʱΪ��ɫ�����ж���Ϊ���
				else
					start_col += 1;
			}
		}
		else
		{
			while (start_col < 80)
			{
				if (img[row][start_col] == BLACK && img[row][start_col - 1] == WHITE)
					return start_col;
				else
					start_col += 1;
			}
		}
	}

	if (which_edge == 'L')
	{
		if (row < 60 - 1)
		{
			while (start_col >= 0)
			{ //////////////
				if (img[row][start_col] == BLACK && img[row][start_col + 1] == WHITE && ((img[row + 1][start_col] == BLACK || img[row - 1][start_col] == BLACK)))
					return start_col;
				//�ڶ����ж�������Ϊ����������,���õ�Ϊ�ڵ㣬��������ͬʱΪ��ɫ�����ж���Ϊ���
				else
					start_col -= 1;
			}
		}
		else
		{
			while (start_col >= 0)
			{
				if (img[row][start_col] == BLACK && img[row][start_col + 1] == WHITE)
					return start_col;
				else
					start_col -= 1;
			}
		}
	}
	return start_col;
}

int Next_Point(int row, int col, char which_edge)
{
	/*
    ���ܣ���ĳһ�����ҵ�����һ���߽��,ѭ���ҵ��߽�
    ������row,col�ֱ�Ϊ��ǰ�������ֵ��which_edgeȡֵ 'L','R',��ʾ������ұ߽�
    ����ֵ�����ص�ֵ��ʾ�ϲ������У�Ϊ0��ʾ��������߽�
    */
	row--;
	if (which_edge == 'L')
	{
		int i = 0;
		while (row > top_line && col < 80 && col >= 0)
		{
			for (i = 0; i < 4; i++)
			{
				if (img[row][col + i] == BLACK && img[row][col + i + 1] == WHITE)
				{
					col = col + i;
					break;
				} //����
				if (img[row][col - i] == BLACK && img[row][col - i + 1] == WHITE)
				{
					col = col - i;
					break;
				} //����
			}
			//ѭ��������i=4����Ϊ�׵����Կ���Ϊ�ϲ�,�˳���
			if (i == 4)
			{
				if (img[row][col] == WHITE)
					return row; //���ضϲ�������
				else
					while (img[row][col] == BLACK && col < 80)
						col++; //����ĵ�Ϊ��ɫ�����ж�Ϊ�ɼ�����ɵĲ�����
			}
			L_edge[row] = col;
			row--;
		}
	}
	if (which_edge == 'R')
	{
		int i = 0;
		while (row > top_line && col < 80 && col >= 0)
		{
			for (i = 0; i < 4; i++)
			{
				if (img[row][col + i] == BLACK && img[row][col + i - 1] == WHITE)
				{
					col = col + i;
					break;
				}
				if (img[row][col - i] == BLACK && img[row][col - i - 1] == WHITE)
				{
					col = col - i;
					break;
				}
			}
			if (i == 4)
			{
				if (img[row][col] == WHITE)
					return row;
				else
					while (img[row][col] == BLACK && col >= 0)
						col--; //����ĵ�Ϊ��ɫ�����ж�Ϊ�ɼ�����ɵĲ�����
			}
			R_edge[row] = col;
			row--;
		}
	}
	return 0;
}
void Road()
{
	/*
    ���ܣ�Ѱ��ͼ��ı߽磬������ L_edge[60],R_edge[60],Mid_Line[60]���������У�

    */
  
	int row = 60 - 1; //top_line����ߵ���Ч��
	int temp_col;
	while (row > top_line)
	{
		temp_col = Edge_Find_1(row, 'L', 40 - 1);
		if (temp_col == -1)
		{ //���û�߽磬����߽�ֵΪ-1��row��һ��
			L_edge[row] = -1;
			row--;
			continue; //û�߽磬�������ϲ���
		}
		else
		{
			L_edge[row] = temp_col;
			int temp_row = Next_Point(row, temp_col, 'L'); //�ɹ��հײ㣬�Դ�Ϊ��㿪ʼ���ұ߽�
			if (temp_row != 0)
			{
				row = temp_row;
				continue;
			} //�����ϲ㣬�����հ���ʼ�����ٴβ���
			else
				break;
		}
	}
	//�ұ߽�ͬ
	row = 60 - 1;
	while (row > top_line)
	{
		temp_col = Edge_Find_1(row, 'R', 40 - 1);
		if (temp_col == 80)
		{ //���û�߽磬����߽�ֵΪ-1��row��һ��
			R_edge[row] = -1;
			row--;
			continue; //û�߽磬�������ϲ���
		}
		else
		{
			R_edge[row] = temp_col;
			int temp_row = Next_Point(row, temp_col, 'R'); //�ɹ��հײ㣬�Դ�Ϊ��㿪ʼ���ұ߽�
			if (temp_row != 0)
			{
				row = temp_row;
				continue;
			} //�����ϲ㣬�����հ���ʼ�����ٴβ���
			else
				break;
		}
	}
	for (int i = top_line; i < 60; i++)
		if (L_edge[i] > R_edge[i])
			L_edge[i] = R_edge[i] = -1;
}



void imgdeal()
{
  
    float dis=0;
    for(int row=top_line;row<60;row++)
    {		
		if(L_edge[row]==-1&&R_edge[row]!=-1)
			Mid_Line[row]=R_edge[row]-(row+3)/2;
		else if(L_edge[row]!=-1&&R_edge[row]==-1)
			Mid_Line[row]=L_edge[row]+(row+3)/2;
		else if(L_edge[row]!=-1&&R_edge[row]!=-1)
        {
            Mid_Line[row]=(L_edge[row]+R_edge[row])/2;
            img[row][Mid_Line[row]]=0;
        }
    }
   
    
    for(int row=59;row>=49;row--)
    if( Mid_Line[row]<40)
    {
         dis=dis+Mid_Line[row]-40;
    }
  else{ dis=dis+Mid_Line[row]-40;}
   
   
    dit=dis/10;
    
    
    }

