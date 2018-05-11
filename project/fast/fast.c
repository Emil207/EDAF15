#include <stdbool.h>
#include "rationals.h"

bool fm(size_t rows, size_t cols, signed char a[rows][cols], signed char c[rows]){
 	struct rational a2[rows][cols];
	struct rational c2[rows];
	size_t tmp = 0, tmp2;
	size_t n1 = 0, n2 = 0;

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
			tmp++;
		}
	}

	for(size_t i = 0; i < rows; i++){
		for(size_t j= 0; j < cols; j++){
			printf("\[%d/%d\]", a2[i][j].a, a2[i][j].b);
		}
		printf("\n", '-');
	}
	printf("\n", '-');

	return 1;
}
