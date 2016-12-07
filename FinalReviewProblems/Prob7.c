#include <stdio.h>

int isValidForSite(char* domainName, char* certificateDomainName)
{
for (int i = 0; i < 32; i++){
    if (*(domainName+i)==*(certificateDomainName+i)){
      continue;
    }
    if (*(certificateDomainName+i)=='\0')
      {
	if (*(domainName+i) != '\0'){
	  return 1;
	}
	else {
	  continue;
      }
    }
}
 return 0;
}

int main (){
  char * p1 = "12345678901234567890123456789012";
  char * p2 = "12345678901234567890123456789012";
  char * p3 = "12345678901234567890123\0456789012";
  char * p4 = "12345678901234567890123\0456789012";
  if (isValidForSite(p1, p2) == 0){
    printf("Same strings verified!\n");
  }
  if (isValidForSite(p2, p3) ==1){
    printf("Malignant string detected!\n");
  }
  if (isValidForSite(p3, p4) == 0){
    printf("Same strings verified! (both with null characters)\n");
  }
}
