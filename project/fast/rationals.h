#ifndef rationals_for_algimp_h

#define rationals_for_algimp_h

#include <stdio.h>

typedef struct rational{
	signed char a;
	signed char b;
} rational;

void printRational(struct rational c){
	printf("%d/%d\n", c.a, c.b);
}

signed char gcd(signed char a, signed char b){
	signed char tmp;
	while(b!=0){
		tmp = b;
		b = a%b;
		a = tmp;
	}
	return a;
}

struct rational reduce(struct rational c){
	signed char d = gcd(c.a, c.b);
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

#endif
