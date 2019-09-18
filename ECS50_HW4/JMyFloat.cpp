#include "MyFloat.h"

MyFloat::MyFloat(){
  sign = 0;
  exponent = 0;
  mantissa = 0;
}

MyFloat::MyFloat(float f){
  unpackFloat(f);
}

MyFloat::MyFloat(const MyFloat & rhs){
	sign = rhs.sign;
	exponent = rhs.exponent;
	mantissa = rhs.mantissa;
}

ostream& operator<<(std::ostream &strm, const MyFloat &f){
	strm << f.packFloat();
	return strm;

}

MyFloat MyFloat::operator+(const MyFloat& rhs) const{
    MyFloat result;
    MyFloat operand_left;
    MyFloat operand_right;
    int exponent_difference;
    
    //Get numbers from the source and store them into operands
    operand_left.exponent = exponent;
    operand_right.exponent = rhs.exponent;
    operand_left.mantissa = mantissa | (1<<23); //need to restore the 1 in front of mantissa
    operand_right.mantissa = rhs.mantissa | (1<<23);
    
    //different cases for the signs of the operands
    if (sign == 1 && rhs.sign == 1){ //example: -1 + -2 ==> -(1 + 2)
        operand_left.sign = 0; //make them positive and pass them to the function
        operand_right.sign = 0;
        result = operand_left.operator+(operand_right); // result = (1 + 2)
        result.sign = 1; //result = -(1 + 2)
        return result;
    } else if (sign == 1 && rhs.sign == 0){ //example: -1 + 2 ==> 2 - 1
        operand_left.sign = 0; //make the left side positive, and pass them to "-" case
        result = operand_right.operator-(operand_left); //result = (2 - 1)
        return result;
    } else if (sign == 0 && rhs.sign == 1){ //example: 1 + -2 ==> 1 - 2
        operand_right.sign = 0; //make the right side positive and pass to "-" case
        result = operand_left.operator-(operand_right); //result = (1 - 2)
        return result;
    }
    
    
    //make the exponent the same by shifting the smaller number to the right
    if (exponent >= rhs.exponent){ //left hand side >= right hand side ==> shift right operand
        exponent_difference = exponent - rhs.exponent;
        operand_right.mantissa = operand_right.mantissa >> exponent_difference;
        operand_right.exponent = operand_right.exponent + exponent_difference;
        result.exponent = exponent; //result should have the same exponent as the bigger number
    } else{ //right hand side > left hand side ==> shifr left operand
        exponent_difference = rhs.exponent - exponent;
        operand_left.mantissa = operand_left.mantissa >> exponent_difference;
        operand_left.exponent = operand_left.exponent + exponent_difference;
        result.exponent = rhs.exponent;
    }
    
    //add the mantissa
    result.mantissa = operand_left.mantissa + operand_right.mantissa;
    
    //the mantissa should be 23 bits including the leading 1, so anything greater
    //equal than 2^24 should shift to the right
    while (result.mantissa >= 16777216){
        result.mantissa = result.mantissa >> 1;
        result.exponent ++;// mantissa shift right by 1, exponent inclement by 1
    }
    
    //this is the case where positive + positive, result is positive. example: 1 + 2
    result.sign = 0;
    result.mantissa &= ~(1<<23);//get rid of the leading 1
 
    return result;
}

MyFloat MyFloat::operator-(const MyFloat& rhs) const{
    MyFloat result;
    MyFloat operand_left;
    MyFloat operand_right;
    int exponent_difference;
    
    //different cases for signs of the operands
    if (sign == 1 && rhs.sign == 1){//example: -1 - -2 ==> -1 + 2
        operand_left.exponent = exponent;//get the information for operands, pass them to "+" case
        operand_right.exponent = rhs.exponent;  //actually in this case, when it goes to "+" case
        operand_left.mantissa = mantissa;       //it will push it back to the "-" case with 2 - 1
        operand_right.mantissa = rhs.mantissa;
        operand_left.sign = 1; //left sign remains unchanged
        operand_right.sign = 0; //right side becomes positive
        result = operand_left.operator+(operand_right); //result = (-1 + 2)
        return result;
    } else if (sign == 0 && rhs.sign == 1){ //example 1 - -2 ==> 1 + 2
        operand_left.exponent = exponent;//get operands and pass them to "+" case
        operand_right.exponent = rhs.exponent;
        operand_left.mantissa = mantissa;
        operand_right.mantissa = rhs.mantissa;
        operand_left.sign = 0; // make their sign be positive
        operand_right.sign = 0;
        result = operand_left.operator+(operand_right); //result = (1 + 2)
        return result;
    } else if (sign == 1 && rhs.sign == 0){ //example -1 - 2 ==> -(1 + 2)
        operand_left.exponent = exponent;//get the opeerands and pass them to "+" case
        operand_right.exponent = rhs.exponent;
        operand_left.mantissa = mantissa;
        operand_right.mantissa = rhs.mantissa;
        operand_left.sign = 0;//make their sign be positive
        operand_right.sign = 0;
        result = operand_left.operator+(operand_right);//result = (1 + 2)
        result.sign = 1; //result = -(1 + 2)
        return result;
    }
    
    //Because we always want to subtract the smaller number from the greater one
    //we save the greater number on the left hand side and the smaller one on the right
    if (exponent > rhs.exponent){
        operand_left.exponent = exponent;
        operand_right.exponent = rhs.exponent;
        operand_left.mantissa = mantissa | (1<<23); //have to restore the 1 in front of mantissa
        operand_right.mantissa = rhs.mantissa | (1<<23);
        result.sign = 0; //bigger number - smaller number, result is positive
    } else if (exponent < rhs.exponent){
        operand_left.exponent = rhs.exponent;
        operand_right.exponent = exponent;
        operand_left.mantissa = rhs.mantissa | (1<<23);
        operand_right.mantissa = mantissa | (1<<23);
        result.sign = 1; //smaller number - bigger number, result is negative
    } else{
        if (mantissa >= rhs.mantissa){
            operand_left.exponent = exponent;
            operand_right.exponent = rhs.exponent;
            operand_left.mantissa = mantissa | (1<<23);
            operand_right.mantissa = rhs.mantissa | (1<<23);
            result.sign = 0;  //bigger number - smaller number, result is positive
        } else{
            operand_left.exponent = rhs.exponent;
            operand_right.exponent = exponent;
            operand_left.mantissa = rhs.mantissa | (1<<23);
            operand_right.mantissa = mantissa | (1<<23);
            result.sign = 1;   //smaller number - bigger number, result is negative
        }
    }
    
    
    //make the exponent the same by shifting the smaller number to the right
    //right hand side is always smaller in this case
    exponent_difference = operand_left.exponent - operand_right.exponent;
    operand_right.mantissa = operand_right.mantissa >> exponent_difference;
    operand_right.exponent = operand_right.exponent + exponent_difference;
    result.exponent = operand_left.exponent;
    
    //3. subtract the mantissa
    result.mantissa = operand_left.mantissa - operand_right.mantissa;
    
    //most sig you shift out is 1, subtract additional 1 at the result
    if (operand_right.mantissa & (1<<exponent_difference)){
        result.mantissa --;
    }
    
    //we need the leading 1 in bit 23 of the mantissa, do right shift or left shift to make the
    //adjustment to make it a normal form
    while (result.mantissa >= 16777216){ //16777216 = 2^24 ==> has to be smaller than this
        result.mantissa = result.mantissa >> 1;
        result.exponent ++;
    }
    while (result.mantissa < 8388608){ //16777216 = 2^23 ==> has to be greater than this
        result.mantissa = result.mantissa << 1;
        result.exponent --;
    }
 
    result.mantissa &= ~(1<<23);//get rid of the leading 1
    
    return result;
}



void MyFloat::unpackFloat(float f) {
    
//    unsigned int number = *((unsigned int*)&f);
//    
//    sign = number >> 31;
//    exponent = (number & 0x7f800000) >> 23;
//    mantissa = number & 0x7fffff;

    __asm__(
    "movl %%eax, %%ebx;"
    "shrl $31, %%ebx;"
    //"movl %%edi, %%ebx;"
        //exponent
    "movl %%eax, %%ecx;"
    "andl 0x7f800000, %%ecx;"
    "shrl $23, %%ecx;"
    //"movl %%edi, %%ecx;"
        //mantissa
    "movl %%eax, %%edx;"
    "andl 0x7f800000, %%edx":
            
    //outputs:
    "+b" (sign), "+c"(exponent), "+d"(mantissa):
            
    //input:
    "a" (f):
    "cc"
    
    );
    
    
    
}//unpackFloat

float MyFloat::packFloat() const{
  //returns the floating point number represented by this
  float f = 0;
    
    unsigned int number = 0;
    number |= (sign << 31) | (exponent << 23) | (mantissa);
    f = *((float*)&number);
    
  return f;
}//packFloat
//



