#include <stdbool.h>
#include <stdlib.h>



typedef struct rational{
	int a;
	int b;
} rational;

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
  bool negative = false;
  //printf("%s \n", "here reduce");
  if(c.a < 0){
    negative = !negative;
    c.a = abs(c.a);
  }
  if(c.b < 0){
    negative = !negative;
    c.b = abs(c.b);
  }
  //printf("%s b %d \n", "here reduce", c.b);
	int d = gcd(c.a, c.b);
  //printf("%s gcd %d \n", "here reduce", d);
	c.a = c.a/d;
	c.b = c.b/d;
  if(negative)
    c.a = -c.a;
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
  //printf("%s a.b %d, b.b %d \n", "here subq", a.b, b.b);
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

bool gt(struct rational a, struct rational b){
  //printf("%s  %d/%d, %d/%d \n", "here gt", a.a, a.b, b.a, b.b);
	struct rational tmp = subq(b, a);
	if(tmp.a < 0)
		return true;

	return false;
}





#define INT_MAX  32767;
#define INT_MIN  -32768;


bool FMalgorithm(size_t rows, size_t cols, struct rational a[rows][cols], struct rational c[rows], size_t n1, size_t n2, size_t n3){
    printf("%d %d \n", n3, cols);
    if(cols == 1){
      struct rational B1;
      B1.a = INT_MAX;
      B1.b = 1;
      for(size_t i = 0; i < n1; i++){
        printf("%d/%d \n", c[i].a, c[i].b);
        if(gt(B1, c[i]))
          B1 = c[i];
      }

      struct rational b1;
      b1.a = INT_MIN;
      b1.b = 1;
      for(size_t i = n1+1; i < n2; i++){
        printf("%d/%d \n", c[i].a, c[i].b);
        if(gt(c[i], b1))
          b1 = c[i];
      }

      printf("%d/%d, %d/%d \n", b1.a, b1.b, B1.a, B1.b);
      if(gt(b1, B1)){
        printf("%s \n", "false1");
        return false;
      }

      //for(size_t i = 0; i < n3; i++)
        //printf("%d/%d \n", c[i].a, c[i].b);

      for(size_t i = n2+1; i < n3; i++){
        struct rational tmp;
        tmp.a = 0;
        tmp.b = 1;
        if(gt(tmp, c[i])){
          printf("%s \n", "false2");
          return false;
        }
      }

      printf("%s \n", "true");
      return true;
    }

    size_t newRows = (n1+1)*(n2-n1)+(n3-n2);
  	struct rational cNew[newRows];
  	struct rational aNew[newRows][cols-1];

    // extracting variables from positives and negatives
  	for(size_t i = 0; i < n1; i++){
  		for(size_t j = n1+1; i < n2; i++){
  			for (size_t k = 0; k < cols-1; k++){
  				aNew[i*(n2-n1)+j][k] = subq(a[i][k], a[j][k]);
  			}
  			cNew[i*(n2-n1)+j] = subq(c[i], c[j]);
  		}
  	}

    // extracting variables from zero values
  	for(size_t i = n2+1; i < (n3-n2); i++){
  		for (size_t k = 0; k < cols-1; k++){
  			aNew[(n1+1)*(n2-n1)-(n2+1)+i][k] = a[i][k];
  		}
  		cNew[(n1+1)*(n2-n1)-(n2+1)+i] = c[i];
  	}

    // resort
    struct rational a2[newRows][cols-1];
    struct rational c2[newRows];
    size_t tmp = 0;
    struct rational tmp0 = {0, 1};
    struct rational tmp2;

    //sort according to m value (positive)
    for(size_t i = 0; i < newRows; i++){
      if(gt(aNew[i][cols-2], tmp0)){
        tmp2 = a[i][cols-2];
        for(size_t j = 0; j < cols-1; j++){
          a2[tmp][j] = divq(aNew[i][j], tmp2);
          c2[tmp] = divq(cNew[i], tmp2);
        }
        n1 = tmp;
        tmp++;
      }
    }

    //sort according to m value (negative)
    for(size_t i = 0; i < newRows; i++){
      if(gt(tmp0, aNew[i][cols-2])){
        tmp2 = a[i][cols-2];
        for(size_t j = 0; j < cols-1; j++){
          a2[tmp][j] = divq(aNew[i][j], tmp2);
          c2[tmp] = divq(cNew[i], tmp2);
        }
        n2 = tmp;
        tmp++;
      }
    }

    //sort according to m value (zero)
    for(size_t i = 0; i < newRows; i++){
      if(a[i][cols-2].a == 0){
        for(size_t j = 0; j < cols-1; j++){
          a2[tmp][j] = aNew[i][j];
          c2[tmp] = cNew[i];
        }
        n3 = tmp;
        tmp++;
      }
    }

    return FMalgorithm(newRows, cols-1, a2, c2, n1, n2, n3);
    // // printing matrix
  	// for(size_t i = 0; i < rows; i++){
  	// 	for(size_t j= 0; j < cols; j++){
  	// 		printf("\[%d/%d\]", a2[i][j].a, a2[i][j].b);
  	// 	}
  	// 	printf("\n", '-');
  	// }
  	// printf("\n", '-');
}








bool fm(size_t rows, size_t cols, signed char a[rows][cols], signed char c[rows]){
 	struct rational a2[rows][cols];
	struct rational c2[rows];
	size_t tmp = 0;
  signed char tmp2;
	size_t n1, n2, n3;

	//sort according to m value (positive)
  n1 = tmp;
	for(size_t i = 0; i < rows; i++){
		if(a[i][cols-1] > 0){
			tmp2 = a[i][cols-1];
			for(size_t j = 0; j < cols; j++){
				a2[tmp][j].a = a[i][j];
				a2[tmp][j].b = tmp2;
				a2[tmp][j] = reduce(a2[tmp][j]);
				c2[tmp].a = c[i];
				c2[tmp].b = tmp2;
        c2[tmp] = reduce(c2[tmp]);
			}
			tmp++;
			n1 = tmp;
		}
	}

	//sort according to m value (negative)
  n2 = tmp;
	for(size_t i = 0; i < rows; i++){
		if(a[i][cols-1] < 0){
			tmp2 = a[i][cols-1];
			for(size_t j = 0; j < cols; j++){
				a2[tmp][j].a = a[i][j];
				a2[tmp][j].b = tmp2;
				a2[tmp][j] = reduce(a2[tmp][j]);
				c2[tmp].a = c[i];
				c2[tmp].b = tmp2;
        c2[tmp] = reduce(c2[tmp]);
			}
			tmp++;
			n2 = tmp;
		}
	}

	//sort according to m value (zero)
  n3 = tmp;
	for(size_t i = 0; i < rows; i++){
		if(a[i][cols-1] == 0){
			for(size_t j = 0; j < cols; j++){
				a2[tmp][j].a = a[i][j];
				a2[tmp][j].b = 1;
				a2[tmp][j] = reduce(a2[tmp][j]);
				c2[tmp].a = c[i];
				c2[tmp].b = 1;
        c2[tmp] = reduce(c2[tmp]);
			}
			tmp++;
			n3 = tmp;
		}
	}
  //printRational(a2[0][1]);
  printf("%s \n", "new test starting");
	return FMalgorithm(rows, cols, a2, c2, n1, n2, n3);
}
