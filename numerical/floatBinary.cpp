#include <iostream>
#include <string>
#include <algorithm>


std::string intToBinaryString(int num)
{
    std::string result="";

    while(num!=0)
    {
        result += num%2 + '0';
        num = num /2;
    }

    while(result.size()<8)
        result += "0";
    std::reverse(result.begin(), result.end());
    return result;
}


void floatNumToBinaryString(float num, std::string& result)
{
    int numIntPart;
    std::string strIntPart="";
    float numFloatPart;
    std::string strDecimalPart="";

    //if negative
    if(num<0)
    {
        strIntPart = "-";
        num = -num;
    }

    //split data
    numIntPart = (int)num;
    numFloatPart = num - numIntPart;


    //int to binary
    while(numIntPart!=0)
    {
        strIntPart += numIntPart%2 + '0';
        numIntPart = numIntPart /2;
    }
    if(strIntPart.size()>0) {
        if(strIntPart[0]!='-')
            std::reverse(strIntPart.begin(), strIntPart.end());
        else
            std::reverse(strIntPart.begin()+1, strIntPart.end());
    }
    else
        strIntPart="0";


    //float to binary
    while(int(numFloatPart)!=numFloatPart)
    {
        numFloatPart *= 2;
        strDecimalPart += (int)numFloatPart>0?'1':'0';
        numFloatPart -= (int)numFloatPart;
    }


    result = strIntPart + '.' + strDecimalPart;
}



void binaryStringToFloat(std::string num, float& result)
{
    int pointIndex=0;
    int numIntPart=0;
    int sign = 0;
    float numFloatPart=0.0f;

    sign = (num.size()>0 and num[0]=='-')?1:0;

    //find point
    for(auto& c: num) {
        if (c == '.')
            break;
        else
            pointIndex++;
    }

    //convert integer part
    int32_t mul_op_int=1;
    for(int i=pointIndex-1;i>=sign;i--)
    {
        numIntPart+=(num[i]-'0')*mul_op_int;
        mul_op_int*=2;
    }

    //convert float part
    float mul_op_float=0.5f;
    for(int i=pointIndex+1;i<num.size();i++)
    {

        numFloatPart+=(num[i]-'0')*mul_op_float;
        mul_op_float/=2.0f;
    }

    result = sign==0?((float)numIntPart + numFloatPart):-((float)numIntPart + numFloatPart);
}


void standardString(std::string org, std::string& result)
{
    std::string signBit = org[0]=='-'?"1":"0";
    std::string midE = "2^";
    std::string E = "";
    std::string M = "";

    //convert E
    int bitBias = -1;
    int pointBias = -1;
    for(int i=1;i<org.size();i++)
    {
       if(org[i]=='1' && bitBias<0)
           bitBias=i - (signBit[0]-'0');
        if(org[i]=='.' && pointBias<0)
            pointBias=i - (signBit[0]-'0');
        if(bitBias>=0 && pointBias>=0)
            break;
    }

    if(bitBias<pointBias)
    {
        auto bias = (pointBias-bitBias);
        midE = midE + std::to_string(bias);
        E = intToBinaryString(127+bias);
    }


    //convert M
    for(int i=bitBias;i<org.size();i++)
        if(org[i]!='.' && org[i]!='-')
            M += org[i];

    std::cout<<"mid result: "<< "("+signBit+") * 1."<< M<<" * "<< midE<<std::endl;

    result = signBit + E + M;
}



int main() {
    // forward http://binaryconvert.com/ for the ans
    float num=3.14159f;
    float convert = 0.0f;
    std::string strResult="";
    std::string floatBitResult="";

    std::cout.precision(7);

    floatNumToBinaryString(num,strResult);
    binaryStringToFloat(strResult,convert);
    standardString(strResult,floatBitResult);

    std::cout<<num<<" "<<strResult<<" "<<convert<<" "<<floatBitResult<<std::endl;

    return 0;
}
