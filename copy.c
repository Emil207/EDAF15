#include <stdio.h>

typedef struct rational{
	int a;
	int b;
} rational;

void printRational(struct rational c){
	printf("%d/%d\n", c.a, c.b);
}

int gcd(int a, int b){
	int tmp;
	while(b!=0){
		tmp = b;
		b = a%b;
		a = tmp;
	}
	return a;
}

struct rational reduce(struct rational c){
	int d = gcd(c.a, c.b);
	c.a = c.a/d;
	c.b = c.b/d;
	return c;
}

struct rational addq(struct rational a, struct rational b){
	struct rational c;
	c.b = a.b*b.b;
	c.a = a.a*b.b + b.a*a.b;
	c = reduce(c);
	return c;
}

struct rational subq(struct rational a, struct rational b){
	struct rational c;
	c.b = a.b*b.b;
	c.a = a.a*b.b - b.a*a.b;
	c = reduce(c);
	return c;
}

struct rational mulq(struct rational a, struct rational b){
	struct rational c;
	c.a = a.a*b.a;
	c.b = a.b*b.b;
	c = reduce(c);
	return c;
}

struct rational divq(struct rational a, struct rational b){
	struct rational c;
	c.a = a.a*b.b;
	c.b = a.b*b.a;
	c = reduce(c);
	return c;
}

int main(int argc, char* argv[])
{

	int a;
	int b;
	int c;
	int d;
	//printf("Please enter two numbers: ");
	//fflush(stdout);
	//sscanf(argv[1]," %d", &a);
	//sscanf(argv[2]," %d", &b);
	//printf("%d\n",d);
	//c = a + b;
	sscanf(argv[1]," %d", &a);
	sscanf(argv[2]," %d", &b);

	struct rational h;
	// reduce
	printf("reducing input rational: \n");
	struct rational e;
	e.a = a;
	e.b = b;
	e = reduce(e);
	printRational(e);

	// addq
	printf("addition of 3/5 and 7/10: \n");
	struct rational f;
	f.a = 3;
	f.b = 5;
	e.a = 7;
	e.b = 10;
	h = addq(e,f);
	printRational(h);

	printf("addition of 0/5 and -7/10: \n");
	f.a = 0;
	e.a = -7;
	h = addq(e,f);
	printRational(h);

	// subq
	printf("subtraction of 3/5 and 7/10: \n");
	f.a = 3;
	e.a = 7;
	h = subq(f,e);
	printRational(h);

	// mulq
	printf("multiplication of 3/5 and 7/10: \n");
	h = mulq(f,e);
	printRational(h);

	// divq
	printf("division of 3/5 and 7/10: \n");
	h = divq(f,e);
	printRational(h);






	//printf("%d + %d = %d\n", a, b, c);

	//for(int i= 1; i < argc; i++){
	//	printf("%s\n", argv[i]);
	//}

	return 0;
}
