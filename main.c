#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>

#define lineLength 150
#define fnameCount 5530
#define lnameCount 90800
#define cityCount  768
#define streetCount 91670
#define diseaseCount  768
#define companyCount 1000

#define dbsize 10000000
#define Health_Phone_correlation 4000000
#define Health_Phone_uncommon  dbsize - Health_Phone_correlation

#define Health_Finance_correlation 3000000
#define Health_Finance_uncommon  dbsize - Health_Finance_correlation

int createIndex(void);
char* getData(int mode, FILE *indx, FILE *datafile);
char* createAddress(char *street,char *city);
char* createEmailAddress(char *fname,char *lname,char *company,char *email);
bool generateGender(int Percent);
static char *rand_string(char *str, size_t size);
char *GenererateRandomDate();
void profilephone();
char *profileClearanceLevel();
char *phoneClearanceLevel();
char *healthClearanceLevel();
char *financeClearanceLevel();
void healthFinance();
int main(int argc, char** argv)
{
//   int createIndex(void)

   printf("start...\n");

   //profilephone();            // generate 100% of profile 100% of phonebook with 50% correlation on email address
   printf("100%% of profile and phonebook are built.\n");
   healthFinance(); // 100% of health & Finance
   printf("100%% of health & finance are built.\n");


}
//===================================================================================================
// 100% of health & Finance
void healthFinance()
{
    char *firstname    = "db/firstname.csv";
    char *surname      = "db/surname.csv";
    char *city         = "db/city.csv";
    char *street       = "db/street.csv";
    char *disease      = "db/disease.csv";
    char *company      = "db/company.csv";
    char *firstnameIndx= "db/firstnameindx.dat";
    char *surnameIndx  = "db/surnameindx.dat";
    char *cityIndx     = "db/cityindx.dat";
    char *streetIndx   = "db/streetindx.dat";
    char *diseaseIndx  = "db/diseaseindx.dat";

    FILE *fnameFile;
    FILE *lnameFile;
    FILE *cityFile;
    FILE *streetFile;
    FILE *diseseFile;
    FILE *companyFile;
    FILE *fnameIndexFile;
    FILE *lnameIndexFile;
    FILE *cityIndexFile;
    FILE *streetIndexFile;
    FILE *diseseIndexFile;

    FILE *health = fopen("output/health.json", "w");
    if (health == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    FILE *finance = fopen("output/finance.json", "w");
    if (finance == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    FILE *socialphone = fopen("socialphone.txt", "r");
    if (socialphone == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    fnameFile = fopen(firstname,"r");
    if (fnameFile == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    fnameIndexFile = fopen(firstnameIndx,"rb");
    if (fnameIndexFile == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    lnameFile = fopen(surname,"r");
    if (lnameFile == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    lnameIndexFile = fopen(surnameIndx,"rb");
    if (lnameIndexFile == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    streetFile = fopen(street,"r");
    if (streetFile == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    streetIndexFile = fopen(streetIndx,"rb");
    if (streetIndexFile == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    diseseFile = fopen(disease,"r");
    if (diseseFile == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    diseseIndexFile = fopen(diseaseIndx,"rb");
    if (diseseIndexFile == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    companyFile = fopen(company,"r");
    if (companyFile == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    cityFile = fopen(city,"r");
    if (cityFile == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    cityIndexFile = fopen(cityIndx,"rb");
   if (cityIndexFile == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    char *address=NULL;
    char *citystr=NULL;
    char *streetstr=NULL;
    char *diseasestr=NULL;
    char *dob=NULL;
    char s[12];
    char *clearance=NULL;
    char  *commonfullname;
    char dataLine[lineLength];
    unsigned long ssn=0;
    unsigned long account=0;
    unsigned long phone=0;
    unsigned int j=0;
    unsigned int k=0;

    for(unsigned int i=1; i<dbsize+1; i++)
    {



        if((i%4)==0 || (i%5)==0)  //40% phone-health correlation on phone#
        {
            j++;
            if(fgets(dataLine, lineLength, socialphone) != NULL)
            {
                char* commonPhone = strtok(dataLine, ",");
                commonfullname = strtok(NULL, ",");
                char* commonClearance = strtok(NULL, ",");
                int newline=strlen(commonClearance)-1;
                if ((commonClearance[newline] == '\n')||(commonClearance[newline] == '\r'))
                    commonClearance[newline] = '\0';

                rand_string(s, 8);
                ssn=0;
                ssn = (rand()*(999999999-100000000)+100000000)%1000000000;
                ssn%=1000000000;
                dob=GenererateRandomDate();
                diseasestr=getData(5,diseseIndexFile,diseseFile);
                newline=strlen(diseasestr)-1;
                if ((diseasestr[newline] == '\n')||(diseasestr[newline] == '\r'))
                    diseasestr[newline] = '\0';

                citystr=getData(3,cityIndexFile,cityFile);
                newline=strlen(citystr)-1;
                if ((citystr[newline] == '\n')||(citystr[newline] == '\r'))
                    citystr[newline] = '\0';

                streetstr=getData(4,streetIndexFile,streetFile);
                newline=strlen(streetstr)-2;
                if ((streetstr[newline] == '\n')||(streetstr[newline] == '\r'))
                    streetstr[newline] = '\0';

                address=createAddress(streetstr,citystr);
                clearance=healthClearanceLevel();

                fprintf(health,"{\n");
                fprintf(health,"\"patientID\":\"%s\",\n",s);
                fprintf(health,"\"ssn\":%lu,\n",ssn);
                fprintf(health,"\"DOB\":\"%s\",\n",dob);
                fprintf(health,"\"disease\":\"%s\",\n",diseasestr);
                fprintf(health,"\"address\":\"%s\",\n",address);
                fprintf(health,"\"phone\":%s,\n",commonPhone);
                fprintf(health,"\"clearance\":\"%s\"\n",clearance);
                fprintf(health,"}\n");

            }
            if(((j%4)==0 || (j%5)==0)&& (j%10)!=0)  //30% of 40% which is 1200000 health-finance-phone correlation on phone->ssn#
            {
                k++;
                fprintf(finance,"{\n");
                fprintf(finance,"\"ssn\":%lu,\n",ssn);
                account = (rand()*(9999999999-1000000000)+1000000000)%10000000000;
                account %=10000000000;
                fprintf(finance,"\"account\":%lu,\n",account);
                fprintf(finance,"\"balance\":%4u,\n",(rand()*(99999-10000)+1000)%1000000);
                fprintf(finance,"\"name\":\"%s\",\n",commonfullname);
                fprintf(finance,"\"address\":\"%s\",\n",address);
                fprintf(finance,"\"clearance\":\"%s\"\n",clearance);
                fprintf(finance,"}\n");


            }


        }
          else{//other 60% of uncommon health information, but still need to be pick 1.8 million to correlated with Finance on ssn#

            rand_string(s, 10);
            ssn=0;
            ssn = (rand()*899999999)%1000000000;
            ssn%=1000000000;
            dob=GenererateRandomDate();
            diseasestr=getData(5,diseseIndexFile,diseseFile);
            int newline=strlen(diseasestr)-1;
            if ((diseasestr[newline] == '\n')||(diseasestr[newline] == '\r'))
                diseasestr[newline] = '\0';

            citystr=getData(3,cityIndexFile,cityFile);
            newline=strlen(citystr)-1;
            if ((citystr[newline] == '\n')||(citystr[newline] == '\r'))
                citystr[newline] = '\0';

            streetstr=getData(4,streetIndexFile,streetFile);
            newline=strlen(streetstr)-2;
            if ((streetstr[newline] == '\n')||(streetstr[newline] == '\r'))
                streetstr[newline] = '\0';

            address=createAddress(streetstr,citystr);
            phone=(rand()*(9999999999-10000000000)+10000000000)%10000000000;
            clearance=healthClearanceLevel();

            fprintf(health,"{\n");
            fprintf(health,"\"patientID\":\"%s\",\n",s);
            fprintf(health,"\"ssn\":%lu,\n",ssn);
            fprintf(health,"\"DOB\":\"%s\",\n",dob);
            fprintf(health,"\"disease\":\"%s\",\n",diseasestr);
            fprintf(health,"\"address\":\"%s\",\n",address);
            fprintf(health,"\"phone\":%lu,\n",phone);
            fprintf(health,"\"clearance\":\"%s\"\n",clearance);
            fprintf(health,"}\n");


            if((i%3==0)&& (i%14!=1) )  //for 1.809525 million correlated on ssn#
            {
                k++;
                char* fname=getData(1,fnameIndexFile,fnameFile);
                newline=strlen(fname)-1;
                if (fname[newline] == '\n')
                    fname[newline] = '\0';
                char* lname=getData(2,lnameIndexFile,lnameFile);
                newline=strlen(lname)-1;
                if (lname[newline] == '\n')
                    lname[newline] = '\0';
                clearance=financeClearanceLevel();
                fprintf(finance,"{\n");
                fprintf(finance,"\"ssn\":%lu,\n",ssn);
                account = (rand()*(9999999999-1000000000)+1000000000)%10000000000;
                account %=10000000000;
                fprintf(finance,"\"account\":%lu,\n",account);
                fprintf(finance,"\"balance\":%4u,\n",(rand()*(99999-10000)+1000)%1000000);
                fprintf(finance,"\"name\":\"%s %s\",\n",fname, lname);
                fprintf(finance,"\"address\":\"%s\",\n",address);
                fprintf(finance,"\"clearance\":\"%s\"\n",clearance);
                fprintf(finance,"}\n");
            } //end if

                fprintf(finance,"{\n");
                ssn=0;
                ssn = (rand()*(999999999-100000000)+100000000)%1000000000;
                ssn%=1000000000;
                fprintf(finance,"\"ssn\":%lu,\n",ssn);
                account = (rand()*(9999999999-1000000000)+1000000000)%10000000000;
                account %= 10000000000;
                fprintf(finance,"\"account\":%lu,\n",account);
                fprintf(finance,"\"balance\":%4u,\n",(rand()*(99999-10000)+1000)%1000000);

                char* fname=getData(1,fnameIndexFile,fnameFile);
                newline=strlen(fname)-1;
                if (fname[newline] == '\n')
                    fname[newline] = '\0';

                char* lname=getData(2,lnameIndexFile,lnameFile);
                newline=strlen(lname)-1;
                if (lname[newline] == '\n')
                    lname[newline] = '\0';
                fprintf(finance,"\"name\":\"%s %s\",\n",fname, lname);

                citystr=getData(3,cityIndexFile,cityFile);
                newline=strlen(citystr)-1;
                if ((citystr[newline] == '\n')||(citystr[newline] == '\r'))
                    citystr[newline] = '\0';

                streetstr=getData(4,streetIndexFile,streetFile);
                newline=strlen(streetstr)-2;
                if ((streetstr[newline] == '\n')||(streetstr[newline] == '\r'))
                    streetstr[newline] = '\0';
                address=createAddress(streetstr,citystr);

                fprintf(finance,"\"address\":\"%s\",\n",address);
                clearance=financeClearanceLevel();
                fprintf(finance,"\"clearance\":\"%s\"\n",clearance);
                fprintf(finance,"}\n");
                k++;

          }//end else
    } //end dbsize loop

    for(unsigned int i=1; i<(dbsize+1)-k; i++)
    {
                fprintf(finance,"{\n");
                ssn=0;
                ssn = (rand()*(999999999-100000000)+100000000)%1000000000;
                ssn%=1000000000;
                fprintf(finance,"\"ssn\":%lu,\n",ssn);
                account = (rand()*(9999999999-1000000000)+1000000000)%10000000000;
                account %= 10000000000;
                fprintf(finance,"\"account\":%lu,\n",account);
                fprintf(finance,"\"balance\":%4u,\n",(rand()*(99999-10000)+1000)%1000000);

                char* fname=getData(1,fnameIndexFile,fnameFile);
                int newline=strlen(fname)-1;
                if (fname[newline] == '\n')
                    fname[newline] = '\0';

                char* lname=getData(2,lnameIndexFile,lnameFile);
                newline=strlen(lname)-1;
                if (lname[newline] == '\n')
                    lname[newline] = '\0';
                fprintf(finance,"\"name\":\"%s %s\",\n",fname, lname);

                citystr=getData(3,cityIndexFile,cityFile);
                newline=strlen(citystr)-1;
                if ((citystr[newline] == '\n')||(citystr[newline] == '\r'))
                    citystr[newline] = '\0';

                streetstr=getData(4,streetIndexFile,streetFile);
                newline=strlen(streetstr)-2;
                if ((streetstr[newline] == '\n')||(streetstr[newline] == '\r'))
                    streetstr[newline] = '\0';
                address=createAddress(streetstr,citystr);

                fprintf(finance,"\"address\":\"%s\",\n",address);
                clearance=financeClearanceLevel();
                fprintf(finance,"\"clearance\":\"%s\"\n",clearance);
                fprintf(finance,"}\n");


    }


    printf("j is %d \n",j);
    printf("k is %d \n",k);

    fclose(health);
    fclose(finance);
    fclose(fnameFile);
    fclose(lnameFile);
    fclose(fnameIndexFile);
    fclose(lnameIndexFile);
    fclose(socialphone);
    fclose(cityFile);
    fclose(streetFile);
    fclose(diseseFile);
    fclose(companyFile);
}
//====================================================================================================
char *financeClearanceLevel()
{
char *cl[14];
cl[0]  = "private";
cl[1]  = "secret";
cl[2]  = "topSecret";
cl[3]  = "topSecret";
cl[4]  = "private";
cl[5]  = "topSecret";
cl[6]  = "topSecret";
cl[7]  = "unclassified";
cl[8]  = "topSecret";
cl[9]  = "topSecret";
cl[10] = "topSecret";
cl[11] = "topSecret";
cl[12] = "topSecret";
cl[13] = "topSecret";
return cl[rand() % 14];
}
//====================================================================================================
char *healthClearanceLevel()
{
char *cl[14];
cl[0]  = "private";
cl[1]  = "secret";
cl[2]  = "secret";
cl[3]  = "private";
cl[4]  = "topSecret";
cl[5]  = "topSecret";
cl[6]  = "private";
cl[7]  = "unclassified";
cl[8]  = "topSecret";
cl[9]  = "topSecret";
cl[10] = "topSecret";
cl[11] = "topSecret";
cl[12] = "topSecret";
cl[13] = "topSecret";
return cl[rand() % 14];
}
//====================================================================================================
char *phoneClearanceLevel()
{
char *cl[12];
cl[0]  = "private";
cl[1]  = "secret";
cl[2]  = "secret";
cl[3]  = "public";
cl[4]  = "public";
cl[5]  = "topSecret";
cl[6]  = "private";
cl[7]  = "unclassified";
cl[8]  = "public";
cl[9]  = "secret";
cl[10] = "public";
cl[11] = "public";
return cl[rand() % 12];
}
//====================================================================================================
char *profileClearanceLevel()
{
char *cl[13];
cl[0]  = "private";
cl[1]  = "secret";
cl[2]  = "public";
cl[3]  = "private";
cl[4]  = "public";
cl[5]  = "public";
cl[6]  = "public";
cl[7]  = "unclassified";
cl[8]  = "public";
cl[9]  = "topSecret";
cl[10] = "public";
cl[11] = "public";
cl[12] = "public";
return cl[rand() % 13];
}
//===================================================================================================
// 100% of profile 100% of phonebook will be generated
void profilephone()
{
    char *firstname= "db/firstname.csv";
    char *surname  = "db/surname.csv";
    char *company  = "db/company.csv";

    char *firstnameIndx= "db/firstnameindx.dat";
    char *surnameIndx  = "db/surnameindx.dat";
    char *companyIndx  = "db/companyindx.dat";

    FILE *fnameFile;
    FILE *lnameFile;
    FILE *companyFile;

    FILE *fnameIndexFile;
    FILE *lnameIndexFile;
    FILE *companyIndexFile;

    FILE *profile = fopen("output/social.json", "w");
    if (profile == NULL)
    {
     printf("Error opening file!\n");
     exit(1);
    }

    FILE *temp = fopen("socialphone.txt", "w");
    if (temp == NULL)
    {
     printf("Error opening file!\n");
     exit(1);
    }

    FILE *phonebook = fopen("output/phone.json", "w");
    if (phonebook == NULL)
    {
     printf("Error opening file!\n");
     exit(1);
    }

    fnameFile = fopen(firstname,"r");
    fnameIndexFile = fopen(firstnameIndx,"rb");

    lnameFile = fopen(surname,"r");
    lnameIndexFile = fopen(surnameIndx,"rb");

    companyFile = fopen(company,"r");
    companyIndexFile = fopen(companyIndx,"rb");

    char *fname;
    char *lname;

    char *email=malloc(120);
    if(!email){printf("out of memory.\n");exit(-1);}

    char *companystr;
    unsigned long phone=0;
    char *clearance;
    char *s = malloc(8 + 1);
    if (!s) {
    printf("out of memory.\n");
    exit(-1);
    }

for(unsigned int i=0;i<dbsize;i++){
    fprintf(profile,"{\n");
    fname=getData(1,fnameIndexFile,fnameFile);
    int newline=strlen(fname)-1;
    if (fname[newline] == '\n')
        fname[newline] = '\0';


    lname=getData(2,lnameIndexFile,lnameFile);
    newline=strlen(lname)-1;
    if (lname[newline] == '\n')
        lname[newline] = '\0';

    fprintf(profile,"\"name\":\"%s %s\",\n",fname,lname);


    companystr= getData(6,companyIndexFile,companyFile);
    newline=strlen(companystr)-1;
    if ((companystr[newline] == '\n')||(companystr[newline] == '\r'))
        companystr[newline] = '\0';

    email[0]='\0';
    email=createEmailAddress(fname,lname,companystr,email);
    fprintf(profile,"\"email\":\"%s\",\n",email);

     if(generateGender(80)==true){
        fprintf(profile,"\"gender\":\"M\",\n"); }
      else fprintf(profile,"\"gender\":\"F\",\n");

    rand_string(s, 7);
    fprintf(profile,"\"UserID\":\"%s\",\n",s);
    clearance=profileClearanceLevel();
    fprintf(profile,"\"clearance\":\"%s\"\n",clearance);

    fprintf(profile,"}\n");

    if(i % 2 == 0)
    {
        fprintf(phonebook,"{\n");
        fprintf(phonebook,"\"email\":\"%s\",\n",email);
        fprintf(phonebook,"\"name\":\"%s %s\",\n",fname,lname);
        phone=(rand()*(9999999999-10000000000)+10000000000)%10000000000;
        fprintf(phonebook,"\"phone\":%lu,\n",phone);
        fprintf(phonebook,"\"clearance\":\"%s\"\n",clearance);
        fprintf(phonebook,"}\n");
        //fprintf(temp3,"\"email\":\"%s\",\n",email);
        if((i+1)%5!=0){
                fprintf(temp,"%lu,%s %s,%s\n",phone,fname,lname,clearance);
//                fprintf(temp,"%lu\n",phone);
//                fprintf(temp2,"%s %s\n",fname,lname);
//                fprintf(tempcl,"%s\n",clearance);
                     }

   }
   else{
    fname=getData(1,fnameIndexFile,fnameFile);
    int newline=strlen(fname)-1;
    if (fname[newline] == '\n')
        fname[newline] = '\0';

    lname=getData(2,lnameIndexFile,lnameFile);
    newline=strlen(lname)-1;
    if (lname[newline] == '\n')
        lname[newline] = '\0';

    companystr= getData(6,companyIndexFile,companyFile);
    newline=strlen(companystr)-1;
    if ((companystr[newline] == '\n')||(companystr[newline] == '\r'))
        companystr[newline] = '\0';
    email[0]='\0';
    email=createEmailAddress(fname,lname,companystr,email);

        fprintf(phonebook,"{\n");
        fprintf(phonebook,"\"email\":\"%s\",\n",email);
        fprintf(phonebook,"\"name\":\"%s %s\",\n",fname,lname);
        phone=(rand()*(9999999999-10000000000)+10000000000)%10000000000;
        fprintf(phonebook,"\"phone\":%lu,\n",phone);
        fprintf(phonebook,"\"clearance\":\"%s\"\n",phoneClearanceLevel());
        fprintf(phonebook,"}\n");
   }
}
    free(s);
    s=NULL;
    free(email);
    email=NULL;
//    fclose(tempcl);
    fclose(profile);
    fclose(temp);
//    fclose(temp2);
//    fclose(temp3);
    fclose(phonebook);
    fclose(fnameFile);
    fclose(lnameFile);
    fclose(companyFile);
}


//===================================================================================================
char *GenererateRandomDate()
{
     int min=1900;
     int max=2000;
     char tmp[6];
     int year = (rand() % (max + 1 - min)) + min;
     min=1;max=12;
     int month= (rand() % (max + 1 - min)) + min;
     min=1;max=30;
     int day=  (rand() % (max + 1 - min)) + min;
     char *date=malloc(10*sizeof(char));
     snprintf(date,2,"%d",month);
     strcat(date,"-");

     snprintf(tmp,2,"%d",day);
     strcat(date,tmp);
     strcat(date,"-");
     snprintf(tmp,5,"%d",year);
     strcat(date,tmp);
     return date;

}
//====================================================================================================
static char *rand_string(char *str, size_t size)
{
    const char charset[] = "abcdefghijklmnopqrstuvwxyz0123456789";
    if (size) {
        --size;
        for (size_t n = 0; n < size; n++) {
            int key = rand() % (int) (sizeof charset - 1);
            str[n] = charset[key];
        }
        str[size] = '\0';
    }
    return str;
}
//====================================================================================================
bool generateGender(int Percent)
{
 int iTemp = rand() % 100 ;

 if(iTemp<Percent)
    return true;
 return false;
}
//====================================================================================================
char* createEmailAddress(char *fname,char *lname,char *company,char *email)
{

char ff[3];
ff[0]=fname[0];
ff[1]='.';
ff[2]='\0';

char sign[2];
sign[0]='@';
sign[1]='\0';

char extenstion[5];
extenstion[0]='.';
extenstion[1]='c';
extenstion[2]='o';
extenstion[3]='m';
extenstion[4]='\0';

unsigned int const sz1  = strlen(ff);
unsigned int const sz2  = strlen(lname);
unsigned int const sz3  = strlen(sign);
unsigned int const sz4  = strlen(company);
unsigned int const sz5  = strlen(extenstion);
char *concat            = (char*)malloc(sz1+sz2+sz3+sz4+sz5+1);

memcpy( concat         , ff  , sz1 );
memcpy( concat+sz1     , lname , sz2 );
memcpy( concat+sz1+sz2 , sign , sz3 );
memcpy( concat+sz1+sz2+sz3 , company , sz4 );
memcpy( concat+sz1+sz2+sz3+sz4 , extenstion , sz5 );


concat[sz1+sz2+sz3+sz4+sz5] = '\0';
return concat;
}
//====================================================================================================
char* createAddress(char *street,char *city)
{
    int min=0;
    int max=9999;

    char zip[6];
    char *add;
    add=malloc(120*sizeof(char));

    //srand(time(NULL));
    int r = (rand() % (max + 1 - min)) + min;
    snprintf(add, 5,"%d",r);
    strcat(add," ");
    strcat(add,street);
    strcat(add," ");
    strcat(add,city);
    strcat(add," ");
    min=11111;max=99999;

    //srand(time(NULL));
    r = (rand() % (max + 1 - min)) + min;
    snprintf(zip, 6,"%d",r);
    strcat(add,zip);
    //strcpy(add,buff);
    return add;

}
//====================================================================================================
char* getData(int mode, FILE *indx, FILE *datafile)
{
    char * line = NULL;
    size_t len = 0;
    int pos=0;
    int min=0;
    int max=0;
    unsigned int r=0;
   // srand(time(NULL));   // should only be called once
switch(mode)
    {
case 1:
      max=fnameCount-1;

    break;
case 2:
      max=lnameCount-1;

    break;
case 3:
      max=cityCount-1;

    break;
case 4:
      max=streetCount-1;

    break;
case 5:
      max=diseaseCount-1;

    break;
case 6:
      max=companyCount-1;

    break;
default:
      max=0;

    }

    r = (rand() % (max + 1 - min)) + min;
    pos=r*4;
    fseek(indx,pos,SEEK_SET);
    fread(&pos,sizeof(int),1,indx);

    fseek(datafile,pos,SEEK_SET);
    getline(&line, &len,datafile );
    return line;


}

//====================================================================================================
int createIndex(void)
{
    char *firstname= "db/firstname.csv";
    char *surname  = "db/surname.csv";
    char *city     = "db/city.csv";
    char *street   = "db/street.csv";
    char *disease  = "db/disease.csv";
    char *company  = "db/company.csv";

    char *firstnameIndx= "db/firstnameindx.dat";
    char *surnameIndx  = "db/surnameindx.dat";
    char *cityIndx     = "db/cityindx.dat";
    char *streetIndx   = "db/streetindx.dat";
    char *diseaseIndx  = "db/diseaseindx.dat";
    char *companyIndx  = "db/companyindx.dat";

    FILE *fnameFile;
    FILE *lnameFile;
    FILE *cityFile;
    FILE *streetFile;
    FILE *diseseFile;
    FILE *companyFile;

    FILE *fnameIndexFile;
    FILE *lnameIndexFile;
    FILE *cityIndexFile;
    FILE *streetIndexFile;
    FILE *diseseIndexFile;
    FILE *companyIndexFile;

    //reads from firstname
    fnameFile = fopen(firstname, "r");
    if(fnameFile == NULL)
    {
        printf("Error when  opening the file %s",firstname);
    }
    //reads from surname
    lnameFile = fopen(surname, "r");
    if(lnameFile == NULL)
    {
        printf("Error when  opening the file %s",surname);
    }
    //reads from cities
    cityFile = fopen(city, "r");
    if(cityFile == NULL)
    {
        printf("Error when  opening the file %s",city);
    }
    //reads from street
    streetFile = fopen(street, "r");
    if(streetFile == NULL)
    {
        printf("Error when  opening the file %s",street);
    }
    //reads from disease
    diseseFile = fopen(disease, "r");
    if(diseseFile == NULL)
    {
        printf("Error when  opening the file %s",disease);
    }

    companyFile = fopen(company, "r");
    if(companyFile == NULL)
    {
        printf("Error when  opening the file %s",company);
    }

    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    int pos=0;
//==================================================================================
//   W R I T E   P H A S E
//==================================================================================
//1
    fnameIndexFile = fopen(firstnameIndx,"wb");
    if(fnameIndexFile == NULL) {
        printf("error creating file");
        return -1;
    }

    while ((read = getline(&line, &len, fnameFile)) != -1) {
          fwrite((const void*) & pos,sizeof(int),1,fnameIndexFile);
           if ((pos = ftell(fnameFile)) == EOF)
              break;
                                                           }
    fclose(fnameIndexFile);
//2
//=====================================================================================
    pos=0;
    lnameIndexFile = fopen(surnameIndx,"wb");
    if(lnameIndexFile == NULL) {
        printf("error creating file");
        return -1;
    }

    while ((read = getline(&line, &len, lnameFile)) != -1) {
          fwrite((const void*) & pos,sizeof(int),1,lnameIndexFile);
           //printf("%d\n", pos);
           if ((pos = ftell(lnameFile)) == EOF)
              break;
                                                           }
    fclose(lnameIndexFile);
//3
//=====================================================================================
    pos=0;
    cityIndexFile = fopen(cityIndx,"wb");
    if(cityIndexFile == NULL) {
        printf("error creating file");
        return -1;
    }

    while ((read = getline(&line, &len,cityFile )) != -1) {
          fwrite((const void*) & pos,sizeof(int),1,cityIndexFile);
           //printf("%d\n", pos);
           if ((pos = ftell(cityFile)) == EOF)
              break;
                                                           }
    fclose(cityIndexFile);
//4
//=====================================================================================

    pos=0;
    streetIndexFile = fopen(streetIndx,"wb");
    if(streetIndexFile == NULL) {
        printf("error creating file");
        return -1;
    }

    while ((read = getline(&line, &len,streetFile )) != -1) {
          fwrite((const void*) & pos,sizeof(int),1,streetIndexFile);
           //printf("%d\n", pos);
           if ((pos = ftell(streetFile)) == EOF)
              break;
                                                           }
    fclose(streetIndexFile);
//5
//=====================================================================================
    pos=0;
    diseseIndexFile = fopen(diseaseIndx,"wb");
    if(diseseIndexFile == NULL) {
        printf("error creating file");
        return -1;
    }

    while ((read = getline(&line, &len,diseseFile )) != -1) {
          fwrite((const void*) & pos,sizeof(int),1,diseseIndexFile);
           //printf("%d\n", pos);
           if ((pos = ftell(diseseFile)) == EOF)
              break;
                                                           }
    fclose(diseseIndexFile);
//6
//=====================================================================================
    pos=0;
    companyIndexFile = fopen(companyIndx,"wb");
    if(companyIndexFile == NULL) {
        printf("error creating file");
        return -1;
    }
    while ((read = getline(&line, &len,companyFile )) != -1) {
          fwrite((const void*) & pos,sizeof(int),1,companyIndexFile);
           if ((pos = ftell(companyFile)) == EOF)
              break;
                                                           }
    fclose(companyIndexFile);
//=====================================================================================
//  R E A D   T E S T
//=====================================================================================
//1
    printf("================[First name]========================\n");
    pos=-1;
    fnameIndexFile = fopen(firstnameIndx,"rb");

     fseek(fnameIndexFile,0,SEEK_END);
     long end = ftell(fnameIndexFile); //finds length of the file
     fseek(fnameIndexFile,0,SEEK_SET);
     long counter = 0;


      while(!feof(fnameIndexFile)){
       fread(&pos,sizeof(int),1,fnameIndexFile);
       //printf("read value: %d\n",pos);
       counter+=4;
      if(counter>=end){ //Breaks when it seeks to the end
           break;
                     }
                                  }

     fclose(fnameIndexFile);
//========================================================================================
//2
    printf("================[Surname name]========================\n");
    pos=-1;
    lnameIndexFile = fopen( surnameIndx,"rb");

     fseek(lnameIndexFile,0,SEEK_END);
     end = ftell(lnameIndexFile); //finds length of the file
     fseek(lnameIndexFile,0,SEEK_SET);
     counter = 0;


      while(!feof(lnameIndexFile)){
       fread(&pos,sizeof(int),1,lnameIndexFile);
       //printf("read value: %d\n",pos);
       counter+=4;
      if(counter>=end){ //Breaks when it seeks to the end
           break;
                     }
                                  }

     fclose(lnameIndexFile);
//========================================================================================
//3

    printf("================[Cities name]========================\n");
    pos=-1;
    cityIndexFile = fopen( cityIndx,"rb");

     fseek(cityIndexFile,0,SEEK_END);
     end = ftell(cityIndexFile); //finds length of the file
     fseek(cityIndexFile,0,SEEK_SET);
     counter = 0;


      while(!feof(cityIndexFile)){
       fread(&pos,sizeof(int),1,cityIndexFile);
       printf("read value: %d\n",pos);
       counter+=4;
      if(counter>=end){ //Breaks when it seeks to the end
           break;
                     }
                                  }

     fclose(cityIndexFile);
//========================================================================================
//4
    printf("================[Street name]========================\n");
    pos=-1;
    streetIndexFile = fopen( streetIndx,"rb");

     fseek(streetIndexFile,0,SEEK_END);
     end = ftell(streetIndexFile); //finds length of the file
     fseek(streetIndexFile,0,SEEK_SET);
     counter = 0;


      while(!feof(streetIndexFile)){
       fread(&pos,sizeof(int),1,streetIndexFile);
       //printf("read value: %d\n",pos);
       counter+=4;
      if(counter>=end){ //Breaks when it seeks to the end
           break;
                     }
                                  }

     fclose(streetIndexFile);
//========================================================================================
//5
    printf("================[Disease name]========================\n");
    pos=-1;
    diseseIndexFile = fopen( diseaseIndx,"rb");

     fseek(diseseIndexFile,0,SEEK_END);
     end = ftell(diseseIndexFile); //finds length of the file
     fseek(diseseIndexFile,0,SEEK_SET);
     counter = 0;
      while(!feof(diseseIndexFile)){
       fread(&pos,sizeof(int),1,diseseIndexFile);
       //printf("read value: %d\n",pos);
       counter+=4;
      if(counter>=end){ //Breaks when it seeks to the end
           break;
                     }
                                  }

     fclose(diseseIndexFile);
//========================================================================================
//6
    printf("================[Company name]========================\n");
    pos=-1;
    companyIndexFile = fopen( companyIndx,"rb");

     fseek(companyIndexFile,0,SEEK_END);
     end = ftell(companyIndexFile); //finds length of the file
     fseek(companyIndexFile,0,SEEK_SET);
     counter = 0;
      while(!feof(companyIndexFile)){
       fread(&pos,sizeof(int),1,companyIndexFile);
       //printf("read value: %d\n",pos);
       counter+=4;
      if(counter>=end){ //Breaks when it seeks to the end
           break;
                     }
                                  }

     fclose(companyIndexFile);
//========================================================================================
    fclose(fnameFile);
    fclose(lnameFile);
    fclose(cityFile);
    fclose(streetFile);
    fclose(diseseFile);
    fclose(companyFile);
    printf("All files are ok!\n");
    return 0;
}
//========================================================================================
//                                E N D
//========================================================================================
