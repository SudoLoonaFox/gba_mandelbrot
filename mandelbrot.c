#define WIDTH 240
#define HEIGHT 160

#define MODE3 0x0003
#define BG2 0x0400

volatile unsigned short* screen = (volatile unsigned short*) 0x6000000;
volatile unsigned short* display_control = (volatile unsigned short*) 0x4000000;

unsigned short make_color(unsigned char r, unsigned char g, unsigned char b) {
    unsigned short color = (b & 0x1f) << 10;
    color |= (g & 0x1f) << 5;
    color |= (r & 0x1f);
    return color;
}

void put_pixel(int row, int col, unsigned short color) {
    /* set the screen location to this color */
    screen[row * WIDTH + col] = color;
}

int size = 160;
int maxiter = 256;
int color[][3] = {{0, 7, 100}, {32, 107, 203}, {237, 255, 255}, {255, 170, 0}, {0, 2, 0}};

int main(){
	*display_control = MODE3 | BG2;

	unsigned short pixel;
	for(double y0 = -2; y0<=2; y0 +=((double)4) / (HEIGHT - 1)){
		int index = 0;
		for(double x0 = -2; x0<=2; x0 +=((double)4) / (WIDTH- 1)){
			int iter = 0;
			double x=0, y=0, xtemp=0;
			while (((x * x + y * y) <= (2 * 2)) && iter < maxiter){
				xtemp = x * x - y * y + x0;
				y = 2 * x * y + y0;
				x = xtemp;
				iter += 1;
				}
			pixel = make_color(color[iter%5][0], color[iter%5][1], color[iter%5][2]);
			put_pixel(((y0+2)/4)*HEIGHT, ((x0+2)/4)*WIDTH, pixel);
		}
	}
	while(1);
	return 0;
}
