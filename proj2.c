/*---------------------------------------------
- FILE : 	proj2.c
- DATE : 	November 2018
- AUTHOR :	xgeffe00@stud.fit.vutbr.cz
- PROJEKT :	Projekt 2 : Iteracne vypocty
---------------------------------------------*/


/* Libraries */
#include <ctype.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>



/* Functions define on top*/
int input (int argc, char* argv[]);
float conditions_of_log(double x);
float conditions_of_pow(double x,double y);
double taylor_log(double x, unsigned int n);
double cfrac_log(double x, unsigned int n);
double taylor_pow(double x, double y, unsigned int n);
double taylorcf_pow(double x, double y, unsigned int n);



/* ===========================================[ M A I N ]================================================*/

int main(int argc, char* argv[]) {

input(argc, argv);

}

/*===========================================[ M A I N ]=================================================*/





/*==========================================[ ARGUMENTS ]================================================*/


int input (int argc, char* argv[]) {

	//Variables for functions/arguments
	double x;
	double y;
	int n;
	bool output = true;
	char var_char;
	short num_of_arg;

	//Checking condition if argv [1] is equal "--log"
	if (strcmp(argv[1],"--log") == 0) {
		//Checking if in arguments [2-n] is some characters
		//Checking if polynomal (n) is intieger
		if (argc == 4) {
			for(num_of_arg = 2; num_of_arg < argc; num_of_arg++) {

				if((sscanf(argv[num_of_arg], "%lf%c", &x, &var_char)) != 1) {
						fprintf(stderr,"V argv[%d] je chybny zapis, v argumente je znak \n", num_of_arg);
						output = false;
				}
			}
				
			if((sscanf(argv[3], "%d%lf", &n, &x) != 1) && (output))  {
				fprintf(stderr,"V argv[%d] je chybny zapis, rozvoj musi byt prirodzene cislo \n", num_of_arg);
			}
		//Printing result
			else if((sscanf(argv[3], "%d%lf", &n, &x) == 1) && (output)) {
				x = atof(argv[2]);
				n = atof(argv[3]);
				printf("\n");
				printf("	 log(%.2g) = %.12g \n", x, log(x));
				printf("  taylor_log(%.2g) = %.12g \n", x, taylor_log(x,n));
				printf("   cfrac_log(%.2g) = %.12g \n", x, cfrac_log(x,n));
				printf("\n");
			}
		}
		else {
			fprintf(stderr, "Nespravny pocet argumentov k logaritmu.\n");
		}
	}
	//Checking condition if argv [1] is equal "--pow"
	else if (strcmp(argv[1],"--pow") == 0) {
		//Checking if in arguments [2-n] is some characters
		//Checking if polynomal (n) is intieger
		if (argc == 5) {
			for(num_of_arg = 2; num_of_arg < argc; num_of_arg++) {

				if((sscanf(argv[num_of_arg], "%lf%c", &x, &var_char)) != 1) {
					fprintf(stderr,"V argv[%d] je chybny zapis, v argumente je znak \n", num_of_arg);
					output = false;
				}
			}
		
			if((sscanf(argv[4], "%d%lf", &n, &x) != 1) && (output)) {
				fprintf(stderr,"V argv[%d] je chybny zapis, rozvoj musi byt prirodezene cislo \n", num_of_arg);
			}
		//Printing result
			else if((sscanf(argv[4], "%d%lf", &n, &x) == 1) && (output)) {
 				x = atof(argv[2]);
				y = atof(argv[3]);
				n = atof(argv[4]);
				printf("\n");
				printf("	 pow(%.2g,%.1g) = %.12g \n", x, y, pow(x,y));
				printf("  taylor_pow(%.2g,%.1g) = %.12g \n", x, y, taylor_pow(x,y,n));
				printf("taylorcf_pow(%.2g,%.1g) = %.12g \n", x, y, taylorcf_pow(x,y,n));
				printf("\n");
			}
		}

		else {
			fprintf(stderr, "Nespravny pocet argumentov k exponencialnej funkcii.\n");
		}
	}
		

	else {
		fprintf(stderr, "Zadal si nepodporovany prvy argument ! \n");
		output = false;
	}

	return 0;	
}

/* ===========================================[ ARGUMENTS ]===============================================*/





/* ==========================================[ CONDITIONS ]==============================================*/

/* Checking conditions for logarithm */

float conditions_of_log(double x) {

	if (x == 0) {
		return -INFINITY;
	} 
	else if (x == 1) {
	  	return 0;
	} 
	else if (x < 0) {
	   	return NAN;
	} 
	else if (isinf(x)) {
		return NAN;
	} 
	else if (isnan(x)) {
		return NAN;
	}
		
	return -1;
}



/* Checking conditions for exponential function */

float conditions_of_pow(double x, double y) {

	if (x == 1) {
		return 1;
	}
	else if (x <= 0) {
		return NAN;
	}
	else if (x == 0) {
		return 0;
	}
	else if (y == 0) {
		return 1;
	}
	else if (x == NAN) {
		return NAN;
	}
	else if (y == NAN) {
		return NAN;
	}
	else if (x == INFINITY) {
		if (y < 0) {
			return 0;
		}
		return INFINITY;
	}
	else if (y == INFINITY) {
		if (fabs(x) < 1) {
			return 0;
		}
		return INFINITY;	
	}
	else if (y == -INFINITY) {
		if (fabs(x) < 1) {
			return INFINITY;
		}
	}

	return -1;
}
/*	(x == 1)? return 1 : return -1;
	(x <= 0)? return NAN : return -1;
	(x == 0)? return 0 : return -1;
	(y == 0)? return 1 : return -1;
	(x == NAN) return NAN : return -1;
	(y == NAN) return NAN : return -1;
	((x == INFINITY) && (y < 0))? return 0 : return -1;
	((y == INFINITY) && (fabs(x) < 1))? return 0 : return -1;
	((y == -INFINITY) && (fabs(x) < ))? return INFINITY : return -1;
}*/

/* ==========================================[ CONDITIONS ]============================================= */





/* ==========================================[ LOGARITHM ]============================================== */

/* Calculating natural logarithm where
- X is number from which I calculate logarihm
- N is count of iteration */

double taylor_log (double x, unsigned int n) {
	
	//Checking conditions of log
	double check_con_log = conditions_of_log(x);
	if (check_con_log != -1) {
		return check_con_log;
	}
	
	double sum = 0.0;
	double reader = 1.0;
	unsigned int i;

	//taylor_log polynom for numbers (0,1)
	if (x < 1) {
		x = (1.0 - x);

		for(i=1; i<=n; i++) {
			reader = reader * x;
			sum = sum - reader / i;
		}
	}
	//taylor_log polynom for numbers (1,infinity)
	else {
		x = (x - 1.0) / x;
		for(i=1 ;i<=n ;i++) {
			reader = reader * x;
			sum = sum + reader / i;
		}
 	}

	return sum;
}



/* Calculating the natural logarithm where
- X is number from which I calculate logarithm
- N iis count of iteration */

double cfrac_log (double x, unsigned int n) {
	
	//Checking conditions of log
	double check_con_log = conditions_of_log(x);
	if (check_con_log != -1) {
		return check_con_log;
	}

	unsigned int coeficient = (2 * n) - 1;
	double sum = coeficient;
	double pre_sum = 0.0;

	x = (1.0 - x) / (1.0 + x);
	x = x*-1;  //Prenasobujem (*-1) pretoze sum (vysledok) mi hadze zaporne cislo

	//cfrac_log polynom
	for(unsigned int i = n; i > 1; i--) {
		n--;
		coeficient = coeficient - 2;
		pre_sum = (n*n)*(x*x)/sum;
		sum  = coeficient - pre_sum;
	}
	sum = (2.0 * x) / sum; 
	
	return sum;
}
	
/* =========================================[ LOGARTIHM ]================================================*/





/* ====================================[ EXPONENCIAL FUNCTIONS ]=========================================*/

/* Calculating exponencial function where 
- X is the number from which I calculate exponencial function
- Y is the number of exponent
- N is count of iteration */

double taylor_pow (double x, double y, unsigned int n){

	//Checking conditions of pow
	double check_con_pow = conditions_of_pow(x,y);
	if (check_con_pow != -1) {
		return check_con_pow;
	}

	double log_x = taylor_log(x,n); 	
	double sum = 0.0;
	double pre_sum = 0.0;
	double reader = 1.0;
	double denumerator = 1.0;

	//taylor_pow polynom
	for(unsigned int i = 1; i < n; i++) {
		reader = reader * y * log_x;
		denumerator = denumerator * i;
		pre_sum = pre_sum + (reader / denumerator);
	}
	sum = sum + pre_sum + 1;

	return sum;
}



/* Calculating exponencial function where
- X is the number from which I calculate exponencial function
- Y is the number of exponent
- N is count of iteration */

double taylorcf_pow (double x, double y, unsigned int n){

	//Checking conditions of pow
	double check_con_pow = conditions_of_pow(x,y);
	if (check_con_pow != -1) {
		return check_con_pow;
	}

	double log_x = cfrac_log (x,n);
	double sum = 0.0;
	double pre_sum = 0.0;
	double reader = 1.0;
	double denominator = 1.0;

	//taylorcf_pow polynom
	for(unsigned int i = 1; i < n; i++) {
		reader = reader * y * log_x;
		denominator = denominator * i;
		pre_sum = pre_sum + (reader / denominator);
	}
	sum = sum + pre_sum + 1;

	return sum;

}

/* ===================================[ EXPONENCIAL FUNCTIONS ]==========================================*/
