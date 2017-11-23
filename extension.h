
int sign_extension(int number)
{
    int result = number;
    number >>= 15;
    if(number == 1)
    {
  
        result += 0xFFFF0000;
        return result;
    }
   
    return result;
    	
}