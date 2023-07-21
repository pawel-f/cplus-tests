#include <iostream>
#include <map>
#include <string>
#include <openssl/sha.h>



class ShaAlgorithm 
{


private:  
  static std::map<std::string, ShaAlgorithm> shaMap;
 
  
  unsigned char *(*func)(const unsigned char *d, size_t n, unsigned char *md);
  int digestLength;
  std::string prefix;    
  
public:  
  typedef unsigned char *(*ShaFunPtr)(const unsigned char *d, size_t n, unsigned char *md);

  ShaAlgorithm()
  {

  }
  ShaAlgorithm(unsigned char * (*func)(const unsigned char *d, size_t n, unsigned char *md), int digestLength, std::string prefix):
    func(func), digestLength(digestLength), prefix(prefix)
  {

  }
  ~ShaAlgorithm()
  {
  
  }

  std::string getPrefix()
  {
    return prefix;
  }

  int getDigestLength()
  {
    return digestLength;
  }

  ShaFunPtr getShaFun()
  {
    return func;
  }


  static int createMap(std::map<std::string, ShaAlgorithm> &m) 
  {
    ShaAlgorithm sha1(&SHA1, SHA_DIGEST_LENGTH, "SHA1");   
    m["{SHA}"] = sha1;
    ShaAlgorithm sha256(&SHA256, SHA256_DIGEST_LENGTH, "SHA256");   
    m["{SHA256}"] = sha256;
    return true;
  }

  static  std::map<std::string, ShaAlgorithm> & getShaMap() 
  {
    return shaMap;
  }

  friend std::ostream& operator<<(std::ostream& out, const ShaAlgorithm& f)
  {
    return out << f.prefix;
  }

};

std::map<std::string, ShaAlgorithm> ShaAlgorithm::shaMap;
static bool _dummySha = ShaAlgorithm::createMap (ShaAlgorithm::getShaMap());




 
void printShaMap(std::string comment, const std::map<std::string, ShaAlgorithm> & m)
{
    std::cout << comment;
 
 // C++98 alternative
    for (std::map<std::string, ShaAlgorithm>::const_iterator it = m.begin(); it != m.end(); it++)
       std::cout << it->first << " = " << it->second << "; ";
 
    std::cout << '\n';
}
 
int main()
{
  
    printShaMap("ShaAlgorithm::get_map", ShaAlgorithm::getShaMap());

    ShaAlgorithm::ShaFunPtr ptr = ShaAlgorithm::getShaMap()["{SHA}"].getShaFun();

    unsigned char* sha_result;
	  std::string dataTmp("mypassword");
	  unsigned char m[ShaAlgorithm::getShaMap()["{SHA}"].getDigestLength()];
	  sha_result=(*ptr)((unsigned char*)(const char*)dataTmp.c_str(), (unsigned long)dataTmp.length(), m);

    std::cout << "result:" << sha_result;
  
}
