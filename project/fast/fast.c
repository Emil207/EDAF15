#include <stdbool.h>
#include "rationals.h"

bool fm(size_t rows, size_t cols, signed char a[rows][cols], signed char c[rows]){
 	struct rational a2[rows][cols];
	struct rational c2[rows];
	size_t tmp = 0, tmp2;
	size_t n1 = 0, n2 = 0, n3 = 0;

	//sort according to m value (positive)
	for(size_t i = 0; i < rows; i++){
		if(a[i][cols-1] > 0){
			tmp2 = a[i][cols-1];
			for(size_t j = 0; j < cols; j++){
				a2[tmp][j].a = a[i][j];
				a2[tmp][j].b = tmp2;
				a2[tmp][j] = reduce(a2[tmp][j]);
				c2[tmp].a = c[i];
				c2[tmp].b = tmp2;
			}
			n1 = tmp;
			tmp++;
		}
	}

	//sort according to m value (negative)
	for(size_t i = 0; i < rows; i++){
		if(a[i][cols-1] < 0){
			tmp2 = a[i][cols-1];
			for(size_t j = 0; j < cols; j++){
				a2[tmp][j].a = a[i][j];
				a2[tmp][j].b = tmp2;
				a2[tmp][j] = reduce(a2[tmp][j]);
				c2[tmp].a = c[i];
				c2[tmp].b = tmp2;
			}
			n2 = tmp;
			tmp++;
		}
	}

	//sort according to m value (zero)
	for(size_t i = 0; i < rows; i++){
		if(a[i][cols-1] == 0){
			tmp2 = a[i][cols-1];
			for(size_t j = 0; j < cols; j++){
				a2[tmp][j].a = a[i][j];
				a2[tmp][j].b = tmp2;
				a2[tmp][j] = reduce(a2[tmp][j]);
				c2[tmp].a = c[i];
				c2[tmp].b = tmp2;
			}
			n3 = tmp;
			tmp++;
		}
	}


	return 1;
}

bool algorithm(size_t rows, size_t cols, struct rational a[rows][cols], struct rational c[rows], size_t n1, size_t n2, size_t n3){
    if(cols == 1){
      size_t br = -;
      for(size_t i = 0; i < n1; i++){

      }
    }

  	struct rational cNew[(n1+1)*(n2-n1)+(n3-n2)];
  	struct rational aNew[(n1+1)*(n2-n1)+(n3-n2)][cols-1];

    // extracting variables from positives and negatives
  	for(size_t i = 0; i <= n1; i++){
  		for(size_t j = n1+1; i <= n2; i++){
        printf("test \n", '-');
  			for (size_t k = 0; k < cols-1; k++){
  				aNew[i*(n2-n1)+j][k] = subq(a2[i][k], a2[j][k]);
  			}
  			cNew[i*(n2-n1)+j] = subq(c2[i], c2[j]);
  		}
  	}

    // extracting variables from zero values
  	for(size_t i = n2+1; i < (n3-n2); i++){
  		for (size_t k = 0; k < cols-1; k++){
  			aNew[(n1+1)*(n2-n1)-(n2+1)+i][k] = a2[i][k];
  		}
  		cNew[(n1+1)*(n2-n1)-(n2+1)+i] = c2[i];
  	}

    // printing matrix
  	for(size_t i = 0; i < rows; i++){
  		for(size_t j= 0; j < cols; j++){
  			printf("\[%d/%d\]", a2[i][j].a, a2[i][j].b);
  		}
  		printf("\n", '-');
  	}
  	printf("\n", '-');
}
