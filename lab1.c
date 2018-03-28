#include <stdio.h>

int main(int argc, char* argv[])
{
	int a;
	int	b;
	int	c;
	int d;
	FILE* fp;

	//printf("Please enter two numbers: ");
	//fflush(stdout);
	//sscanf(argv[1]," %d", &a);
	//sscanf(argv[2]," %d", &b);
	//printf("%d\n",d);
	//c = a + b;
	fp = fopen("data.txt", "w");
	sscanf(argv[1]," %d", &a);
	c += a;
	fprintf(fp,"%d ", a);
	for(int i = 2; i < argc; i++){
		sscanf(argv[i]," %d", &a);
		c += a;
		fprintf(fp, "+ %d ", a);
	}
	fprintf(fp,"= %d \n", c);
	fclose(fp);



	//printf("%d + %d = %d\n", a, b, c);

	//for(int i= 1; i < argc; i++){
	//	printf("%s\n", argv[i]);
	//}

	return 0;
}
