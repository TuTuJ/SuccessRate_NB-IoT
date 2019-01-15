#include <stdlib.h>
#include <time.h>

double genrand64_real3(void);
void init_genrand64(unsigned long long seed);
unsigned long long genrand64_int64(void);
 #define NN 3121
 #define MM 156
 #define MATRIX_A 0xB5026F5AA96619E9ULL
 #define UM 0xFFFFFFFF80000000ULL /* Most significant 33 bits */
 #define LM 0x7FFFFFFFULL /* Least significant 31 bits */
 /* The array for the state vector */
 static unsigned long long mt[NN];
 /* mti==NN+1 means mt[NN] is not initialized */
 static int mti=NN+1;
 /* initializes mt[NN] with a seed */
 
//set parameter
 float avg_prob = 0;
 int simulate_time = 0;
 float test = 0;
 float test_count = 0;
 float test_avg_count = 0;
 int try[49] = {0};  //define subcarrier
 float result[101] = {0};
 
 void init_genrand64(unsigned long long seed)
 {
 printf("Input seed: ");
 scanf("%d",&seed);	
 mt[0] = seed;
 for (mti=1; mti<NN; mti++)
 mt[mti] = (6364136223846793005ULL * (mt[mti-1] ^ (mt[mti-1]
>> 62)) + mti);
 }

 double genrand64_real3(void)
 {
 return ((genrand64_int64() >> 12) + 0.5) *
(1.0/4503599627370496.0);
 }

  unsigned long long genrand64_int64(void)
{
 int i;
 unsigned long long x;
 static unsigned long long mag01[2]={0ULL, MATRIX_A};

 if (mti >= NN) { /* generate NN words at one time */

 /* if init_genrand64() has not been called, */
/* a default initial seed is used */
if (mti == NN+1)
init_genrand64(NULL);

 for (i=0;i<NN-MM;i++) {
x = (mt[i]&UM)|(mt[i+1]&LM);
 mt[i] = mt[i+MM] ^ (x>>1) ^ mag01[(int)(x&1ULL)];
 }
 for (;i<NN-1;i++) {
 x = (mt[i]&UM)|(mt[i+1]&LM);
 mt[i] = mt[i+(MM-NN)] ^ (x>>1) ^ mag01[(int)(x&1ULL)];
 }
 x = (mt[NN-1]&UM)|(mt[0]&LM);
 mt[NN-1] = mt[MM-1] ^ (x>>1) ^ mag01[(int)(x&1ULL)];

 mti = 0;
}

x = mt[mti++];

 x ^= (x >> 29) & 0x5555555555555555ULL;
x ^= (x << 17) & 0x71D67FFFEDA60000ULL;
x ^= (x << 37) & 0xFFF7EEE000000000ULL;
x ^= (x >> 43);

 return x;
 }

int main(){
	int i ,ue_count=0, u,g; 
	srand(time(NULL));
	//printf("Input UE count:");
	//scanf("%d",&ue_count);  
	printf("Simulation time:");
	scanf("%d",&simulate_time);
for(ue_count=1;ue_count<101;ue_count++){	//test for all
avg_prob=0;
for(u=0;u<simulate_time;u++){
	double urn[49]={0};  //define subcarrier
	float success_count = 0;
	int index = 0;
		for(i=0;i<ue_count;i++){
		double rr = genrand64_real3()*48+1;   //define which subcarrier to go 
		index = (int)rr;
		urn[index] = urn[index] + 1;
		printf("%d ",index);
	}
	printf("\n");
	printf("\n\nSuccessful transmit:\n");
	for(i=1;i<=49;i++){	 
		if(urn[i] == 1){
		printf("urn[%d] ",i);
		success_count++;
		}	
	}
	printf("\nSuccessful: %.0f 個\n", success_count);
			test_count++;
			try[(int)success_count] = try[(int)success_count] + 1;
	//for urn concept test
	avg_prob += (success_count/ue_count); 
	result[ue_count] = avg_prob;
	printf("\n\nSuccess Probility:%.4f\n-------------------------------\n",(success_count/ue_count));
	}	
}
	for(i=1;i<101;i++){
	//printf("%d個為1的機率:\n %.6f\n",i,(float)try[i]/simulate_time);
	printf("%.11f\n",result[i]/simulate_time);
	}
/*	printf("Average successful probability : %.6f", avg_prob/simulate_time);
	//printf("\nTEST :%.0f\n",test_count);
	printf("\n%.0f個urn 為1的機率: %.6f\n", test,test_count/simulate_time);
	printf("Information: UE: %d ; Simulation time:%d \n---------------------------------\n",ue_count,simulate_time);
	for(i=0;i<=12;i++){
	//printf("%d個為1的機率:\n %.6f\n",i,(float)try[i]/simulate_time);
	printf("%.11f\n",(float)try[i]/simulate_time);
	}
*/
	return 0;
}


 
