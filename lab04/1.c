// make_a_float ... read in bit strings to build a float value
// COMP1521 Lab03 exercises
// Written by John Shepherd, August 2017
// Completed by ...

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <math.h>

typedef uint32_t Word;

struct _float {
   // define bit_fields for sign, exp and frac
   // obviously they need to be larger than 1-bit each
   // and may need to be defined in a different order
   unsigned int frac:23, exp:8,sign:1;
};
typedef struct _float Float32;

union _bits32 {
   float   fval;  // interpret the bits as a float
   Word    xval;  // interpret as a single 32-bit word
   Float32 bits;  // manipulate individual bits
};
typedef union _bits32 Union32;

void    checkArgs(int, char **);
Union32 getBits(char *, char *, char *);
char   *showBits(Word, char *);

int main(int argc, char **argv)
{
   union _bits32 u;
   char out[50];

   // here's a hint ...
   u.bits.sign = u.bits.exp = u.bits.frac = 0;

   // check command-line args (all strings of 0/1
   // kills program if args are bad
   checkArgs(argc, argv);

   // convert command-line args into components of
   // a Float32 inside a Union32, and return the union
   u = getBits(argv[1], argv[2], argv[3]);

   printf("bits : %s\n", showBits(u.xval,out));
   printf("float: %0.10f\n", u.fval);

   return 0;
}

// convert three bit-strings (already checked)
// into the components of a struct _float
//TODO
Union32 getBits(char *sign, char *exp, char *frac)
{
   Union32 new;

   // this line is just to keep gcc happy
   // delete it when you have implemented the function

   new.bits.sign = new.bits.exp = new.bits.frac = 0;

   // convert char *sign into a single bit in new.bits
   int i = 0;

   if(sign[0]=='1')
   {
      new.bits.sign=1;
   }
   else if(sign[0]=='0')
   {
      new.bits.sign=0;
   }
   else
   {
      fprintf(stderr,"WARNING:UNRECOGNIZED CHARACTER READ!");
   }
   // convert char *exp into an 8-bit value in new.bits
	
   for(i=0;i<8;i++)
   {
      if(exp[i]=='1')
      {
         new.bits.exp+=pow(2,(7-i));
      }
      else if(exp[i]=='0')
      {
         continue;
      }
      else
      {
         fprintf(stderr,"WARNING:UNRECOGNIZED CHARACTER READ!");
      }
   }
	fprintf(stderr,"exp is %d\n",new.bits.exp);
   // convert char *frac into a 23-bit value in new.bits
   for(i=0;i<23;i++)
   {
      if(frac[i]=='1')
      {
         new.bits.frac+=pow(2,(22-i));
      }
      else if(frac[i]=='0')
      {
         continue;
      }
      else
      {
         fprintf(stderr,"WARNING:UNRECOGNIZED CHARACTER READ!");
      }
   }fprintf(stderr,"frac is %d\n",new.bits.frac);
	
   return new;
}

// convert a 32-bit bit-stringin val into a sequence
// of '0' and '1' characters in an array buf
// assume that buf has size > 32
// return a pointer to buf
char *showBits(Word val, char *buf)
{
   // this line is just to keep gcc happy
   // delete it when you have implemented the function
   buf[0] = '\0';
   union _bits32 u;
   u.xval = val;
   buf[1] = ' ';
   buf[10] = ' ';
   int i = 0;
   buf[0] = '0';
   Word mask1 = pow(2,7);
   for(i = 2;i < 10;i++)
   {
      if((mask1 & u.bits.exp) != 0)
      {
         buf[i] = '1';
      }
      else
      {
         buf[i] = '0';
      }
      mask1 = mask1>>1;
   }
   Word mask2 = pow(2,22);
   for(i = 11;i < 34;i++)
   {
      if((mask2 & u.bits.frac) != 0)
      {
         buf[i] = '1';
      }
      else
      {
         buf[i] = '0';
      }
      mask2 = mask2>>1;
   }
   buf[34] = '\0';
   return buf;
}

// checks command-line args
// need at least 3, and all must be strings of 0/1
// never returns if it finds a problem
void checkArgs(int argc, char **argv)
{
   int justBits(char *, int);

   if (argc < 3) {
      printf("Usage: %s Sign Exp Frac\n", argv[0]);
      exit(1);
   }
   if (!justBits(argv[1],1)) {
      printf("%s: invalid Sign\n", argv[0]);
      exit(1);
   }
   if (!justBits(argv[2],8)) {
      printf("%s: invalid Exp: %s\n", argv[0], argv[2]);
      exit(1);
   }
   if (!justBits(argv[3],23)) {
      printf("%s: invalid Frac: %s\n", argv[0], argv[3]);
      exit(1);
   }
   return;
}

// check whether a string is all 0/1 and of a given length
int justBits(char *str, int len)
{
   if (strlen(str) != len) return 0;

   while (*str != '\0') {
      if (*str != '0' && *str != '1') return 0;
      str++;
   }
   return 1;
}
