long loop(long x,long n)
{
  long result=0;
  long mask;
  for (mask=1;mask!= 0;mask=mask<< n&0xFF)
    {
      result |= (mask&x);
    }
return result;
}
