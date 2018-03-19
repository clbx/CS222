#include <stdio.h>
#include <math.h>


struct point{
	double x;
	double y;
};




double distance(struct point* a, struct point* b){
	double deltaX = a->x - b->x;
	double deltaY = a->y - a->x;

	return sqrt(deltaX*deltaX + deltaY*deltaY);
}


int main(){

	struct point point1;
	struct point point2;

	point1.x = 7;
	point1.x = 12;

	point2.x = 12;
	point2.x = 7;

	printf("The distance is: %f", distance(&point1,&point2));


}