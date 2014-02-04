int main()
{
	int number;
	int x, y, x1, x2, y1, y2;
	int w, theta, r;
	ScreenInit();
	printf("These are some functions you can use:\n1.Show Screen Property 2.Draw Points 3.Draw Lines 4. Draw Circles 5. Draw sins\nPlease enter the number in front of the options to select:");
	scanf("%d",&number);
	switch(number)
	{
		case 1:
			ScreenClear();
			ScreenProperty();
			break;
		case 2:
			ScreenClear();
			printf("Please enter the location you want to draw:x=");
			scanf("%d",&x);
			printf("y=");
			scanf("%d",&y);
			DrawPoints(x,y);
			break;
		case 3:
			ScreenClear();
			printf("Please enter the location of two points in your line:x1=");
			scanf("%d",&x1);
			printf("y1=");
			scanf("%d",&y1);
			printf("x2=");
			scanf("%d",&x2);
			printf("y2=");
			scanf("%d",&y2);
			DrawLines(x1,y1,x2,y2);
			break;
		case 4:
			ScreenClear();
			printf("Please enter the center of the circle:x=");
			scanf("%d",&x);
			printf("y=");
			scanf("%d",&y);
			printf("Please enter the radius:r=");
			scanf("%d",&r);
			DrawCircles(x,y,r);
			break;
		case 5:
			ScreenClear();
			printf("Please enter angular frequency and phase angle:w=");
			scanf("%d",&w);
			printf("theta=");
			scanf("%d",&theta);
			DrawSins(w,theta);
			break;
	}
}
