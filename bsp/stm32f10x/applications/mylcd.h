#ifndef __H_MY_LCD
#define __H_MY_LCD

//----------head file is here----------
#include <board.h>
#include "delay.h"

//----------struct define is here------
typedef struct
{
	u16 LCD_REG;
	u16 LCD_RAM;
}LCD_TypeDef;

#define LCD_BASE	((u32)(0x6c000000 | 0x000007FE))
#define LCD	((LCD_TypeDef*)LCD_BASE)
//--------how to read/write lcd
//for write:
//	LCD->LCD_REG = CMD;	LCD->LCD_RAM = DATA;
//for read:
//	CMD = LCD->LCD_REG; DATA = LCD->LCD_RAM;


typedef struct 
{
	u16 width;		//lcd width
	u16 height;		//LCD height
	u16 id;				//lcd id
	u8	dir;			//0:vertical,1:horizable
	u16	wramcmd;	//write gram ins
	u16	setxcmd;	//set x pos ins
	u16	setycmd;	//set y pos ins
}_lcd_dev;

extern _lcd_dev lcd_dev;
extern u16 POINT_COLOR;
extern u16 BACK_COLOR;

//////////////////////////////////////////////////////////////////////
//ɨ�跽����
#define L2R_U2D  0 //������,���ϵ���
#define L2R_D2U  1 //������,���µ���
#define R2L_U2D  2 //���ҵ���,���ϵ���
#define R2L_D2U  3 //���ҵ���,���µ���

#define U2D_L2R  4 //���ϵ���,������
#define U2D_R2L  5 //���ϵ���,���ҵ���
#define D2U_L2R  6 //���µ���,������
#define D2U_R2L  7 //���µ���,���ҵ���

#define DFT_SCAN_DIR  L2R_U2D  //Ĭ�ϵ�ɨ�跽��

//ɨ�跽����
#define L2R_U2D  0 //������,���ϵ���
#define L2R_D2U  1 //������,���µ���
#define R2L_U2D  2 //���ҵ���,���ϵ���
#define R2L_D2U  3 //���ҵ���,���µ���

#define U2D_L2R  4 //���ϵ���,������
#define U2D_R2L  5 //���ϵ���,���ҵ���
#define D2U_L2R  6 //���µ���,������
#define D2U_R2L  7 //���µ���,���ҵ���

#define DFT_SCAN_DIR  L2R_U2D  //Ĭ�ϵ�ɨ�跽��

__STATIC_INLINE	void my_lcd_wr_reg(u16 reg_val)
{
	LCD->LCD_REG = reg_val;
}

__STATIC_INLINE	void my_lcd_wr_data(u16 data)
{
	LCD->LCD_RAM = data;
}

__STATIC_INLINE	u16 my_lcd_rd_data()
{
	return LCD->LCD_RAM;
}

__STATIC_INLINE	void my_lcd_write_reg(u16 lcd_reg,u16 reg_value)
{
	LCD->LCD_REG = lcd_reg;
	LCD->LCD_RAM = reg_value;
}

__STATIC_INLINE	u16 my_lcd_read_reg(u16 lcd_reg)
{
	my_lcd_wr_reg(lcd_reg);
	delay_us(5);
	return my_lcd_rd_data();
}

__STATIC_INLINE	void my_lcd_write_ram_prepare()
{
	LCD->LCD_REG = lcd_dev.wramcmd;
}

//LCD�ֱ�������
#define SSD_HOR_RESOLUTION		800		//LCDˮƽ�ֱ���
#define SSD_VER_RESOLUTION		480		//LCD��ֱ�ֱ���
//LCD������������
#define SSD_HOR_PULSE_WIDTH		1		//ˮƽ����
#define SSD_HOR_BACK_PORCH		46		//ˮƽǰ��
#define SSD_HOR_FRONT_PORCH		210		//ˮƽ����

#define SSD_VER_PULSE_WIDTH		1		//��ֱ����
#define SSD_VER_BACK_PORCH		23		//��ֱǰ��
#define SSD_VER_FRONT_PORCH		22		//��ֱǰ��
//���¼����������Զ�����
#define SSD_HT	(SSD_HOR_RESOLUTION+SSD_HOR_BACK_PORCH+SSD_HOR_FRONT_PORCH)
#define SSD_HPS	(SSD_HOR_BACK_PORCH)
#define SSD_VT 	(SSD_VER_RESOLUTION+SSD_VER_BACK_PORCH+SSD_VER_FRONT_PORCH)
#define SSD_VPS (SSD_VER_BACK_PORCH)

//������ɫ
#define WHITE         	 0xFFFF
#define BLACK         	 0x0000
#define BLUE         	 0x001F
#define BRED             0XF81F
#define GRED 			 0XFFE0
#define GBLUE			 0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			 0XBC40 //��ɫ
#define BRRED 			 0XFC07 //�غ�ɫ
#define GRAY  			 0X8430 //��ɫ
//GUI��ɫ

#define DARKBLUE      	 0X01CF	//����ɫ
#define LIGHTBLUE      	 0X7D7C	//ǳ��ɫ
#define GRAYBLUE       	 0X5458 //����ɫ
//������ɫΪPANEL����ɫ

#define LIGHTGREEN     	 0X841F //ǳ��ɫ
#define LGRAY 			 0XC618 //ǳ��ɫ(PANNEL),���屳��ɫ

#define LGRAYBLUE        0XA651 //ǳ����ɫ(�м����ɫ)
#define LBBLUE           0X2B12 //ǳ����ɫ(ѡ����Ŀ�ķ�ɫ)

extern void my_lcd_set_cursor(u16 xpos,u16 ypos);
extern void my_lcd_draw_point(u16 x,u16 y);
extern void my_lcd_fast_draw_point(u16 x,u16 y,u16 color);
extern void my_lcd_ssd_backlight_set(u8 pwm);
extern void my_lcd_display_dir(u8 dir);
extern void my_lcd_set_window(u16 sx,u16 sy,u16 width,u16 height);
extern u16 my_lcd_read_point(u16 x,u16 y);
extern void my_lcd_show_char(u16 x,u16 y,u8 num,u8 size,u8 mode);
extern void my_lcd_display_on(void);
extern void my_lcd_scan_dir(u8 dir);
extern void my_lcd_clear(u16 color);
extern void my_lcd_fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 color);
extern void my_lcd_color_fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 *color);
extern void my_lcd_draw_line(u16 x1, u16 y1, u16 x2, u16 y2);
extern void my_lcd_draw_rect(u16 x1, u16 y1, u16 x2, u16 y2);
extern void my_lcd_draw_cycle(u16 x0,u16 y0,u8 r);
extern void my_lcd_show_num(u16 x,u16 y,u32 num,u8 len,u8 size);
extern void my_lcd_show_x_num(u16 x,u16 y,u32 num,u8 len,u8 size,u8 mode);
extern void my_lcd_show_string(u16 x,u16 y,u16 width,u16 height,u8 size,u8 *p);
extern void LCD_Init(void);
#endif
