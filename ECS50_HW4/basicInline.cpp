#include <stdio.h>
int abAdd(int a, int b);
int anyRegAdd(int a, int b);
int altAnyRegAdd(int a, int b);
int memAdd(int a, int b);
int anyWhereAdd(int a, int b);

/*
The synax for inlined assembly is
__asm__(
assembly code :
outputs :
inputs :
clobbered );

outputs, inputs, and clobbered are all optional

*/


int abcAdd(int a, int b){
	//add a and b together
	//placing the result in result
	int result;
	__asm__(
	"movl %%ebx, %%eax;" //note that registers have double % signs in front of them
	"addl %%ecx, %%eax" : //and that if you are not the last line you have to end with a ;
	"=a" (result) : //the = sign means that result will be overwritten with whatever value is 
									//in the associated register. In this case it is a
	"b" (b), "c" (a) : //b will be stored in EBX and a in ECX
	"cc" //the condition codes will be changed
	);
	return result;
}

int abAdd(int a, int b){
	//use the inline assembly to add a and b together
	//storing the result in a
	//and being explicit about which registers
	//should contain what values
	__asm__(
	"addl %%ebx, %%eax" :
	"+a" (a) : //store a in register a. the + in front of a means it is is an input and output register
	 "b" (b) : //store b in register b
	 "cc"
	);
	
	return a;
}

int anyRegAdd(int a, int b){
	//add a and b together but allow gcc or g++
	//to determine which registers to place a and b into
	__asm__(
	"addl %1, %0" :
	"+r" (a): //r means that gcc can store the varaible in any general purpose register
	"r" (b) :
	"cc"
	);
	return a;
}

int altAnyRegAdd(int a, int b){
	//again allow gcc/g++ to choose which register
	//to store our values in but this time we give nice names
	//to the values instead of having to use their positions
	__asm__(
	"addl %[b], %[sum]" :
	[sum] "+r" (a): //note that the names of the variables don't have to match the names that show
									//up in the assembly.
	[b] "r" (b) //but they can if you want them to
	);
	return a;
}

int memAdd(int a, int b){
	//this time we add a and b 
	//but we leave b in memory instead of putting it into a register
	__asm__(
	"addl %[b], %[sum]" :
	[sum] "+g" (a): //a is stored in a register or memory but for the code to work 
									//it must be placed in a reg and gcc will be forced to put it in one
	[b] "m" (b): // the m makes b be stored in memory
	 "cc"
	);
	return a;

}

int anyWhereAdd(int a, int b){
	//this time we allow gcc to store our values
	//in any register it wants or memory
	__asm__(
	"addl %[b], %[sum]" :
	[sum] "+g" (a): //the g means a general purpose register or somewhere in memory
	[b] "g" (b):
	"cc"
	);
	return a;

}

int clobberAdd(int a, int b){
  int result;
	__asm__(
	"movl $0, %0;"
	"movl %1, %0;" //note that registers have double % signs in front of them
	"addl %2, %0"
	   : //and that if you are not the last line you have to end with a ;
	"=&r" (result) : //the = sign means that result will be overwritten with whatever value is 
									//in the associated register. In this case it is a
	"r" (b), "r" (a) : //b will be stored in EBX and a in ECX
	"cc" //the condition codes will be changed
	);
	return result;

}



int main(){
	int x = 10;
	int y = 100;
	
	printf("%d\n", abcAdd(x,y));
	printf("%d\n", abAdd(x,y));
	printf("%d\n", anyRegAdd(x,y));
	printf("%d\n", altAnyRegAdd(x,y));
	printf("%d\n", memAdd(x,y));
	printf("%d\n", anyWhereAdd(x,y));
	printf("%d\n", clobberAdd(x,y));
	
return 0;
}
