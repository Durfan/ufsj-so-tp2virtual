#include <stdio.h>

int main(void) {

	unsigned s, page_size, tmp;
	page_size = 4096;
	/* Derivar o valor de s: */
	tmp = page_size; s = 0;
	while (tmp>1) {
		tmp = tmp>>1;
		s++;
	}

	printf("%d\n", s);

	return 0;
}