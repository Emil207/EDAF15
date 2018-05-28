#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>



typedef struct rational{
	long int a;
	long int b;
} rational;

long int gcd(long int a, long int b){
	long int tmp;
	while(b!=0){
		tmp = b;
		b = a%b;
		a = tmp;
	}
	return a;
}

// struct rational reduce(struct rational c){
// 	if(c.a == 0){
// 		c.b = 1;
// 		return c;
// 	}
//   bool negative = false;
//   if(c.a < 0){
//     negative = !negative;
//     c.a = abs(c.a);
//   }
//   if(c.b < 0){
//     negative = !negative;
//     c.b = abs(c.b);
//   }
// 	long int d = gcd(c.a, c.b);
// 	c.a = c.a/d;
// 	c.b = c.b/d;
//   if(negative)
//     c.a = -c.a;
// 	return c;
// }

struct rational addq(struct rational a, struct rational b){
	struct rational c;
	c.b = a.b*b.b;
	c.a = a.a*b.b + b.a*a.b;
	//c = reduce(c);
	return c;
}

struct rational subq(struct rational a, struct rational b){
	struct rational c;
	c.b = a.b*b.b;
	c.a = a.a*b.b - b.a*a.b;
	//c = reduce(c);
	return c;
}

// struct rational mulq(struct rational a, struct rational b){
// 	struct rational c;
// 	c.a = a.a*b.a;
// 	c.b = a.b*b.b;
// 	c = reduce(c);
// 	return c;
// }

struct rational divq(struct rational a, struct rational b){
	struct rational c;
	c.a = a.a*b.b;
	c.b = a.b*b.a;
	//c = reduce(c);
	return c;
}

bool gt(struct rational a, struct rational b){
	struct rational tmp = subq(b, a);
	if(tmp.a < 0)
		return true;

	return false;
}





#define INT_MAX  2147483647;
#define INT_MIN  -2147483647;


bool FMalgorithm(long int rows, long int cols, struct rational a[rows][cols], struct rational c[rows], long int n1, long int n2, long int n3){
    // printf("%d %d \n", rows, cols);
		//
		// printf("%s \n", "in Data");
		// for(long int i = 0; i < rows; i++){
		// 	printf("%d: %d/%d ", i, a[i][0].a, a[i][0].b);
		// 	if(cols > 1)
		// 		printf(" %d/%d ", a[i][1].a, a[i][1].b);
		// 	printf("\n",'-');
		// }
		//
// 		if(x){
//      printf("n1: %ld, n2: %ld, n3: %ld \n", n1, n2, n3);
//     }
// if(x)
//       for(long int i = 0; i < rows; i++){
//         for(long int j = 0; j < cols; j++){
//           printf(" %ld/%ld", a[i][j].a, a[i][j].b);
//         }
//        printf(" < %ld/%ld \n", c[i].a, c[i].b);
//       }

      // if(x)
      //   for(long int i = 0; i < rows; i++)
      //     printf("%ld/%ld \n", c[i].a, c[i].b);
    if(cols == 1 || n3 == 0){
      if(n3 == 0)
        return true;

      struct rational B1;
      B1.a = INT_MAX;
      B1.b = 1;
      for(long int i = 0; i < n1; i++){
        if(gt(B1, c[i])){
          B1 = c[i];
        //  if(x){
				  //  printf("B1 %ld/%ld \n", c[i].a, c[i].b);
         // }
				}
      }

      struct rational b1;
      b1.a = INT_MIN;
      b1.b = 1;
      for(long int i = n1; i < n2; i++){
        if(gt(c[i], b1)){
          b1 = c[i];
        //  if(x){
				  //  printf("b1: %ld/%ld \n", c[i].a, c[i].b);
        //  }
				}
      }

      //printf("%d/%d, %d/%d \n", b1.a, b1.b, B1.a, B1.b);
      if(gt(b1, B1)){
       // if(x)
         // printf("%s \n", "false1");
        return false;
      }

      //for(size_t i = 0; i < n3; i++)
        //printf("%d/%d \n", c[i].a, c[i].b);

      for(long int i = n2; i < n3; i++){
        struct rational tmp;
        tmp.a = 0;
        tmp.b = 1;
        if(gt(tmp, c[i])){
         // if(x)
           // printf("%s \n", "false2");
          return false;
        }
      }

      //if(x)
        //printf("%s \n", "true");
      return true;
    }




    //reorder according to the next variable
    long int tmp = 0;
    struct rational tmp0 = {0, 1};
    struct rational tmp2;


    long int newRows = (n1)*(n2-n1)+(n3-n2);
  	struct rational aNew[newRows][cols-1];
    struct rational cNew[newRows];

    //printf("%s \n", "here recursive part 0");
    


    // extracting variables from positives and negatives
  	for(long int i = 0; i < n1; i++){
  		for(long int j = n1; j < n2; j++){
  			for (long int k = 0; k < cols-1; k++){
  				aNew[i*(n2-n1)+(j-n1)][k] = subq(a[i][k], a[j][k]);
  			}
  			cNew[i*(n2-n1)+(j-n1)] = subq(c[i], c[j]);
  		}
  	}

    //printf("%s \n", "here recursive part 1");

    // extracting variables from zero values
  	for(long int i = n2; i < n3; i++){
  		for (long int k = 0; k < cols-1; k++){
  			aNew[(n1)*(n2-n1)-(n2)+(i-n2)][k] = a[i][k];
        //if(x){
        	//printf("%ld/%ld \n", a[i][k].a, a[i][k].b);
        //}
  		}
  		cNew[(n1)*(n2-n1)-(n2)+(i-n2)] = c[i];
  	}

    //printf("%s \n", "here recursive part 2");

    // resort
    struct rational a2[newRows][cols-1];
    struct rational c2[newRows];
    tmp = 0;


    //printf("%s \n", "here recursive part 3");

    //sort according to m value (positive)
		n1 = tmp;
    for(long int i = 0; i < newRows; i++){
      if(gt(aNew[i][cols-2], tmp0)){
        tmp2 = aNew[i][cols-2];
        for(long int j = 0; j < cols-1; j++){
          a2[tmp][j] = divq(aNew[i][j], tmp2);
          c2[tmp] = divq(cNew[i], tmp2);
        }
				tmp++;
        n1 = tmp;
      }
    }
  //  printf("%s \n", "here recursive part 4");

    //sort according to m value (negative)
		n2 = tmp;
    for(long int i = 0; i < newRows; i++){
      if(gt(tmp0, aNew[i][cols-2])){
        tmp2 = aNew[i][cols-2];
        for(long int j = 0; j < cols-1; j++){
          a2[tmp][j] = divq(aNew[i][j], tmp2);
          c2[tmp] = divq(cNew[i], tmp2);
        }
				tmp++;
        n2 = tmp;
      }
    }
    //printf("%s \n", "here recursive part 5");

    //sort according to m value (zero)
		n3 = tmp;
    for(long int i = 0; i < newRows; i++){
      if(a[i][cols-2].a == 0){
        for(long int j = 0; j < cols-1; j++){
          a2[tmp][j] = aNew[i][j];
          c2[tmp] = cNew[i];
        }
				tmp++;
        n3 = tmp;
      }
    }

  //  printf("%s \n", "here recursive part 6");

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
//	printf("%s \n", "new file");
  //bool x = false;
	// if(rows == 3 && cols == 3 && a[0][0] == 27 && a[1][0] == 67){
 //    for(size_t i = 0; i < rows; i++){
 //      for(size_t j = 0; j < cols; j++)
 //        printf("%d ", (int)a[i][j]);
 //      printf(" < %d \n", (int)c[i]);
 //    }
	// 	x = true;
 //  }
 	struct rational a2[rows][cols];
	struct rational c2[rows];
	long int tmp = 0;
  signed char tmp2;
	long int n1, n2, n3;

	//sort according to m value (positive) and divide with the rightmost coefficient
  n1 = tmp;
	for(size_t i = 0; i < rows; i++){
		if(a[i][cols-1] > 0){
			tmp2 = a[i][cols-1];
			for(size_t j = 0; j < cols; j++){
				a2[tmp][j].a = a[i][j];
				a2[tmp][j].b = tmp2;
			//	a2[tmp][j] = reduce(a2[tmp][j]);
				c2[tmp].a = c[i];
				c2[tmp].b = tmp2;
       // c2[tmp] = reduce(c2[tmp]);
			}
			tmp++;
			n1 = tmp;
		}
	}

	//sort according to m value (negative) and divide with the rightmost coefficient
  n2 = tmp;
	for(size_t i = 0; i < rows; i++){
		if(a[i][cols-1] < 0){
			tmp2 = a[i][cols-1];
			for(size_t j = 0; j < cols; j++){
				a2[tmp][j].a = a[i][j];
				a2[tmp][j].b = tmp2;
				//a2[tmp][j] = reduce(a2[tmp][j]);
				c2[tmp].a = c[i];
				c2[tmp].b = tmp2;
        //c2[tmp] = reduce(c2[tmp]);
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
			//	a2[tmp][j] = reduce(a2[tmp][j]);
				c2[tmp].a = c[i];
				c2[tmp].b = 1;
        //c2[tmp] = reduce(c2[tmp]);
			}
			tmp++;
			n3 = tmp;
		}
	}

	// for(size_t i = 0; i < rows; i++){
	// 	printf("a2: %d/%d \n", a2[i][0].a, a2[i][0].b);
	// }
  //printRational(a2[0][1]);
	return FMalgorithm((long int)rows, (long int)cols, a2, c2, n1, n2, n3);
}
