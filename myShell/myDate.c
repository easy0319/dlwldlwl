#include <stdio.h>
#include <time.h>

int main(){
	struct tm *t;
	time_t timer;
	char s[100];

	timer = time(NULL);   
	t = localtime(&timer);
   
	strftime(s, sizeof(s), "%Y. %m. %d. (%a) %T %Z", t);
	fprintf(stdout, "%s \n", s);

	return 0;
}
