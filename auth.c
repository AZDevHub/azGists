#include "qsysinc/H/qsyphandle"
#include "qsysinc/H/qusec"
#include "qsysinc/H/string"

int main (int argc, char *argv[])
{
  if (argc < 3) {
    // Not enough arguments provided, handle error or exit
    return -1;
  }

  char *username = argv[1]; 
  char *password = argv[2]; 
  int passwordLength = strlen(password); // Calculate the password length

  char handle[12];
  Qus_EC_t errcode;

  errcode.Bytes_Provided = 0;

  QsyGetProfileHandle(handle,        
                      username,      
                      password,      
                      passwordLength,
                      0,            
                      &errcode);     

  if (errcode.Bytes_Available > errcode.Bytes_Provided) {
	 return -1;
    // handle error
  }

  return 0;
}
