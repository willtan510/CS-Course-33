
/*
* CS:APP Data Lab
*
* <William Tan 104770108>
*
* bits.c - Source file with your solutions to the Lab.
*          This is the file you will hand in to your instructor.
*
* WARNING: Do not include the <stdio.h> header; it confuses the dlc
* compiler. You can still use printf for debugging without including
* <stdio.h>, although you might get a compiler warning. In general,
* it's not good practice to ignore compiler warnings, but in this
* case it's OK.
*/

#if 0
/*
* Instructions to Students:
*
* STEP 1: Read the following instructions carefully.
*/

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES :

Replace the "return" statement in each function with one
or more lines of C code that implements the function.Your code
must conform to the following style :

int Funct(arg1, arg2, ...) {
	/* brief description of how your implementation works */
	int var1 = Expr1;
	...
		int varM = ExprM;

	varJ = ExprJ;
	...
		varN = ExprN;
	return ExprR;
}

Each "Expr" is an expression using ONLY the following :
1. Integer constants 0 through 255 (0xFF), inclusive.You are
not allowed to use big constants such as 0xffffffff.
2. Function arguments and local variables(no global variables).
3. Unary integer operations !~
4. Binary integer operations & ^ | +<< >>

Some of the problems restrict the set of allowed operators even further.
Each "Expr" may consist of multiple operators.You are not restricted to
one operator per line.

You are expressly forbidden to :
1. Use any control constructs such as if, do, while, for, switch, etc.
2. Define or use any macros.
3. Define any additional functions in this file.
4. Call any functions.
5. Use any other operations, such as &&, || , -, or ? :
	6. Use any form of casting.
	7. Use any data type other than int.This implies that you
	cannot use arrays, structs, or unions.


	You may assume that your machine :
1. Uses 2s complement, 32 - bit representations of integers.
2. Performs right shifts arithmetically.
3. Has unpredictable behavior when shifting an integer by more
than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE :
/*
* pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
*/
int pow2plus1(int x) {
	/* exploit ability of shifts to compute powers of 2 */
	return (1 << x) + 1;
}

/*
* pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
*/
int pow2plus4(int x) {
	/* exploit ability of shifts to compute powers of 2 */
	int result = (1 << x);
	result += 4;
	return result;
}

FLOATING POINT CODING RULES

For the problems that require you to implent floating - point operations,
the coding rules are less strict.You are allowed to use looping and
conditional control.You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to :
1. Define or use any macros.
2. Define any additional functions in this file.
3. Call any functions.
4. Use any form of casting.
5. Use any data type other than int or unsigned.This means that you
cannot use arrays, structs, or unions.
6. Use any floating point data types, operations, or constants.


NOTES:
1. Use the dlc(data lab checker) compiler(described in the handout) to
check the legality of your solutions.
2. Each function has a maximum number of operators(!~& ^ | +<< >> )
that you are allowed to use for your implementation of the function.
The max operator count is checked by dlc.Note that '=' is not
counted; you may use as many of these as you want without penalty.
3. Use the btest test harness to check your functions for correctness.
4. Use the BDD checker to formally verify your functions
5. The maximum number of ops for each function is given in the
header comment for each function.If there are any inconsistencies
between the maximum ops in the writeup and in this file, consider
this file the authoritative source.

/*
* STEP 2: Modify the following functions according the coding rules.
*
*   IMPORTANT. TO AVOID GRADING SURPRISES:
*   1. Use the dlc compiler to check that your solutions conform
*      to the coding rules.
*   2. Use the BDD checker to formally verify that your solutions produce
*      the correct answers.
*/


#endif
/*
* bang - Compute !x without using !
*   Examples: bang(3) = 0, bang(0) = 1
*   Legal ops: ~ & ^ | + << >>
*   Max ops: 12
*   Rating: 4
*/
int bang(int x) {

	/*
	First checks if most significant is 1 for negatives
	Then checks if MSB is 1 if int_max is added to it, otherwise the value is 0
	*/
	int negCheck = x;
	int max = ~(1 << 31);
	int posCheck = x + max;

	negCheck = negCheck >> 31;
	negCheck = negCheck & 1;
	negCheck = negCheck ^ 1;


	posCheck = posCheck >> 31;
	posCheck = posCheck ^ 1;
	return negCheck&posCheck;
}
/*
* bitCount - returns count of number of 1's in word
*   Examples: bitCount(5) = 2, bitCount(7) = 3
*   Legal ops: ! ~ & ^ | + << >>
*   Max ops: 40
*   Rating: 4
*/
int bitCount(int x) {
	/*
	Create masks of 0101,0011,00001111,0000000011111111 etc
	For each mask, & it to current bit string, shift over accordingly, & again
	This adds up totals up one bits
	*/
	int halfmask01 = (0x55 << 8) + 0x55;
	int mask01 = halfmask01 + (halfmask01 << 16);
	int halfmask0011 = (0x33 << 8) + 0x33;
	int mask0011 = halfmask0011 + (halfmask0011 << 16);
	int halfmask00001111 = (0x0F << 8) + 0x0F;
	int mask00001111 = halfmask00001111 + (halfmask00001111 << 16);
	int mask0x81x8 = (0xFF << 16) + 0xFF;
	int mask0x161x16 = (0xFF << 8) + 0xFF;
	int total = (x&mask01) + ((x >> 1) & mask01);

	total = (total&mask0011) + ((total >> 2)&mask0011);
	total = (total&mask00001111) + ((total >> 4)&mask00001111);
	total = (total&mask0x81x8) + ((total >> 8)&mask0x81x8);
	total = (total&mask0x161x16) + ((total >> 16)&mask0x161x16);
	return total;
}
/*
* bitOr - x|y using only ~ and &
*   Example: bitOr(6, 5) = 7
*   Legal ops: ~ &
*   Max ops: 8
*   Rating: 1
*/
int bitOr(int x, int y) {
	/*
	Complement both values, and them, then complement again
	*/
	int compX = ~x;
	int compY = ~y;
	int ampXY = compX&compY;
	return ~ampXY;
}
/*
* bitRepeat - repeat x's low-order n bits until word is full.
*   Can assume that 1 <= n <= 32.
*   Examples: bitRepeat(1, 1) = -1
*             bitRepeat(7, 4) = 0x77777777
*             bitRepeat(0x13f, 8) = 0x3f3f3f3f
*             bitRepeat(0xfffe02, 9) = 0x10080402
*             bitRepeat(-559038737, 31) = -559038737
*             bitRepeat(-559038737, 32) = -559038737
*   Legal ops: int and unsigned ! ~ & ^ | + - * / % << >>
*             (This is more general than the usual integer coding rules.)
*   Max ops: 40
*   Rating: 4
*/
int bitRepeat(int x, int n) {
	/*
	First get the initial lower n-bit pattern
	Have a value to check if value is greater than or equal to 32
	Set pattern equal to current pattern shifted right by n, plus the current pattern
	Multiply patternsize(initially n) by 2
	Do the past two steps 4 more times each, to account for if n=1
	To not shift left by more than 31, have another value that checks if patternsize is 32 or more, and if so sets this value to 31
	This value will then be shifted upon the pattern twice to set new template for the "+ pattern", which should now hold the correct pattern
	*/
	int neg1 = ~0;
	int pattern = ~((neg1 << (n - 1) << 1));
	int patternsize = 2 * n;//11111111100000
	int adjust = !(31 / patternsize) * 31;

	pattern = x&pattern;

	pattern = (pattern << (n - 1) << 1) + pattern;


	pattern = ((pattern << (patternsize & 31)) << adjust << adjust) + pattern;

	patternsize = 2 * patternsize;

	adjust = !(31 / patternsize) * 31;
	pattern = ((pattern << (patternsize & 31)) << adjust << adjust) + pattern;

	patternsize = 2 * patternsize;
	adjust = !(31 / patternsize) * 31;
	pattern = ((pattern << (patternsize & 31)) << adjust << adjust) + pattern;

	patternsize = 2 * patternsize;
	adjust = !(31 / patternsize) * 31;
	pattern = ((pattern << (patternsize & 31)) << adjust << adjust) + pattern;

	return pattern;

}
/*
* fitsBits - return 1 if x can be represented as an
*  n-bit, two's complement integer.
*   1 <= n <= 32
*   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
*   Legal ops: ! ~ & ^ | + << >>
*   Max ops: 15
*   Rating: 2
*/

int fitsBits(int x, int n)
{
	/*
	Create two masks, one that affects positive integers and one that affects negative integers
	Combine them by summing (only one will hold some value)
	Shift this combnation by n-1 so that any digit not covered by n will be sticking out
	*/
	int mask = x >> 31;
	int mask1 = (~x)&mask;
	int mask2 = x&(~mask);
	int ret = mask1 + mask2;

	ret = ret >> (n + ((~1) + 1));
	return !ret;
}
/*
* getByte - Extract byte n from word x
*   Bytes numbered from 0 (LSB) to 3 (MSB)
*   Examples: getByte(0x12345678,1) = 0x56
*   Legal ops: ! ~ & ^ | + << >>
*   Max ops: 6
*   Rating: 2
*/
int getByte(int x, int n) {
	/*
	Multiply n by 8 to convert bytes to bits
	Shift x over by n to the right
	Create a mask to get the first byte from this changed x
	*/
	int nMask = 0;

	n = n << 3;
	x = x >> n;
	nMask = ~nMask;
	nMask = ~(nMask << 8);
	return x&nMask;
}
/*
* isLessOrEqual - if x <= y  then return 1, else return 0
*   Example: isLessOrEqual(4,5) = 1.
*   Legal ops: ! ~ & ^ | + << >>
*   Max ops: 24
*   Rating: 3
*/

int isLessOrEqual(int x, int y) {
	/*
	Find the difference of x -y
	Check if the sign bit, the MSB, is 1 (negative), if so it can potentially be less than
	Check if equal by adding int_max to difference and looking at MSB
	Positive overflow if sign bit is negative, x is positive, and y is negative
	Negative overflow if sign bit is positive, x is negative, and y is positive
	Relate these values to determine less than or equal
	*/
	int difference = x + (~y + 1);
	int min = 1 << 31;

	int signBit = difference &min;

	int signX = x&min;
	int signY = y &min;

	int max = ~min;

	int PosOverflow = signBit & (signX^min)& signY;
	int NegOverflow = (~signBit) & signX & (signY^min);

	difference += max;
	difference = difference ^min;


	return ((difference | signBit | NegOverflow) >> 31) & (!PosOverflow);

}
/*
* isPositive - return 1 if x > 0, return 0 otherwise
*   Example: isPositive(-1) = 0.
*   Legal ops: ! ~ & ^ | + << >>
*   Max ops: 8
*   Rating: 3
*/
int isPositive(int x) {
	/*
	Check if the value is equal to 0, then check if the MSB is 1
	Relate values to see if is positive
	*/
	int min = (1 << 31);
	int max = ~min;

	int negCheck = x + max;	// 1 at MSB if positive or INT_MIN
	int signCheck = x >> 31;	// 1 at MSB if negative
	int check = ((negCheck&min) >> 31)&(!signCheck);
	return check;
}
/*
* logicalShift - shift x to the right by n, using a logical shift
*   Can assume that 0 <= n <= 31
*   Examples: logicalShift(0x87654321,4) = 0x08765432
*   Legal ops: ! ~ & ^ | + << >>
*   Max ops: 20
*   Rating: 3
*/
int logicalShift(int x, int n) {
	/*
	Shift x to the right by n
	Account for the 1s if it's negative by:
	Create a mask of n 0s followed by 1s
	& x and this mask to get a logical shift
	*
	

	
	.
		int y = x >> n;
	int mask = 1;
	int signBit = 1 & (y >> 31);
	mask = mask << 31;		//10000000
	mask = mask >> (n);		//10000000
	mask = ~mask;			//01111111


	mask = (mask << signBit) | 1;


	return y&mask;
}
/*
* tmin - return minimum two's complement integer
*   Legal ops: ! ~ & ^ | + << >>
*   Max ops: 4
*   Rating: 1
*/
int tmin(void) {
	/*
	Create 1, shift it 31 over
	*/
	int min = 1;
	return min << 31;
}

int main()
{
	int test=getByte(0x80000000, 3); 







}