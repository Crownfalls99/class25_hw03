# define _GNU_SOURCE
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/time.h>
# include <sched.h>

# define MICRO_SEC 1000000

typedef struct timeval TIMEV;

/*
int ellapsedTime(TIMEV startTime, TIMEV endTime) {
	if (endTime.tv_usec < startTime.tv_sec) {
		endTime.tv_sec--;
		endTime.tv_usec += MICRO_SEC;
	}
	return (endTime.tv_sec - startTime.tv_sec) * MICRO_SEC 
		+ (endTime.tv_usec - startTime.tv_usec);
}
*/

void cummulatedTime(TIMEV* total, TIMEV start, TIMEV end) {
	TIMEV diff;

	if (end.tv_usec < start.tv_usec) {
		end.tv_usec--;
		end.tv_usec += MICRO_SEC;
	}
	diff.tv_sec = end.tv_sec - start.tv_sec;
	diff.tv_usec = end.tv_usec - start.tv_usec;

	total->tv_sec += diff.tv_sec;
	total->tv_usec += diff.tv_usec;

	if (total->tv_usec > MICRO_SEC) {
		total->tv_usec -= MICRO_SEC;
		total->tv_sec++;
	}
}


void usage(void) {
	printf("syntax : tlb <NUM_PAGE> <ITERATION>\n");
	printf("sample : tlb 64 1000\n");
}

int main(int argc, char* argv[]) {
	if (argc != 3) {
		usage();
		exit(1);
	}
	cpu_set_t c;
	CPU_ZERO(&c);
	CPU_SET(0, &c);
	sched_setaffinity(getpid(), sizeof(cpu_set_t), &c);

	TIMEV start, end, total;
	int PAGESIZE = getpagesize();
	int NUM_PAGE = atoi(argv[1]);
	int itr = atoi(argv[2]), sum = 0;

	int jump = PAGESIZE / sizeof(int); // number of elements in each page
	int ARR_SIZE = NUM_PAGE * jump; // number of elements in array

	int* a = (int*) calloc(NUM_PAGE * jump, sizeof(int));
	total.tv_sec = 0;
	total.tv_usec = 0;

	for (int j = 0; j < itr; j++) {
		for (int i = 0; i < ARR_SIZE; i += jump) {
			gettimeofday(&start, NULL);
			a[i] += 1;
			gettimeofday(&end, NULL);
			cummulatedTime(&total, start, end);
		}
	}
	
	int loop = (itr * NUM_PAGE);
	double m = (total.tv_sec * 1000000000 / loop) + ( total.tv_usec * 1000 / loop);
	printf("%.03lf nsec\n", m);
	return 0;
}

