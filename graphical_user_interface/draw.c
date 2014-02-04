#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <math.h>

int fp;
struct fb_var_screeninfo vinfo;
struct fb_fix_screeninfo finfo;
long screensize;
char *fbp;
int x, y;
long location;

void ScreenInit()
{
	fp = open("/dev/fb0",O_RDWR);
	if (fp < 0)
	{
		printf("Error:Can not open framebuffer device\n");
		exit(1);
	}
	if (ioctl(fp,FBIOGET_FCREENINFO,&finfo))
	{
		printf("Error reading fixed information\n");
		exit(2);
	}
	if (ioctl(fp,FBIOGET_VSCREENINFO,&vinfo))
	{
		printf("Error reading variable information\n");
		exit(3);
	}

	screensize = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel / 8;
	fbp = (char *)mmap(0,screensize,PROT_READ | PROT_WRITE,WAP_SHARED,fp,0);
	
	if ((int) fbp == -1)
	{
		printf("Error:failed to map framebuffer device to memory.\n");
		exit(4);
	}	
}

void ScreenClear()
{
	memset(fbp,screensize);
	close(fp);
}

void ScreenProperty()
{
	printf("The mem is : %d\n", finfo.smem_len);
	printf("The line_length is : %d\n", finfo.line_length);
	printf("The xres is : %d\n", vinfo.xres);
	printf("The yres is : %d\n", vinfo.yres);
	printf("bits_per_pixel is : %d\n"), vinfo.bits_per_pixel);
}

void DrawPoints(int x, int y)
{
	int i, j;
	i = x;
	j = y;
	location = (i + j * vinfo.res) * vinfo.bits_per_pixel / 8;
	*(fbp + location) = 0;
	*(fbp + location + 1) = 0;
	*(fbp + location + 2) = 255;
	*(fbp + location + 3) = 0;
}

void DrawLines(int x1, int y1, int x2, int y2)
{
	int i, j;
	float k, b;
	if (x1 == x2)
	{
		if (y1 >= y2)
		{
			for (i = y2; i <= y1; i++)
				DrawPoints(x1,i);
		}
		else
		{
			for(i = y1; i <= y2; i++)
				DrawPoints(x1,i);
		}
	}
	else
	{
		k = (y2 - y1) / (x2 - x1);
		b = y1 - k * x1;
		if (x1 > x2)
		{
			for (i = x2; i <= x1; i++)
			{
				j = (int)(k * i + b);
				DrawPoints(i,j);
			}
		}
		else
		{
			for (i = x1; i <= x2; i++)
			{
				j = (int)(k * i + b);
				DrawPoints(i,j);
			}
		}
	}
}

void DrawCircles(int x, int y, int r)
{
	int m, n, i, j, theta;
	for (theta = 0; theta < 360; theta++)
	{
		m = r * sin(theta * 2 * 3.14 / 360);
		i = x + m;
		n = r * cos(theta * 2 * 3.14 / 360);
		j = y + n;
		DrawPoints(i,j);
	}
}

void DrawSins(int w, int theta)
{
	int x = 0;
	int y = 200;
	int i,j;
	for (i = x; i <= 700; i++)
	{
		j = (int)(y + 30 * (sin(w * i * 2 * 3.14 / 360 + theta)));
		DrawPoints(i,j);
	}
}
