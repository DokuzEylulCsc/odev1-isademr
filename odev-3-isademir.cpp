#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdlib.h>

using namespace std;

int main(){
ifstream dosyaOku("input.txt");
string satir;
int i=0,j=0,k=0;
int sorusayisi;
string cvp_anahtari;
string ogrcvp[100];
float puan[100];
int kisi_sayisi;

char okul_no[100][9];

if(dosyaOku.is_open()){
	
	getline(dosyaOku,satir);      //getline dosyadaki satýrlarý okuyup satýr degiskenine atar. her satýr için ayrý ayrý. burda ilk satýrý aldýk
	istringstream sayi(satir);   //istringstream dosyadaki deðerleri int olarak almak için kullanýlýr  
	sayi >> sorusayisi;    //soru adetini int olarak atadýk
	getline(dosyaOku,cvp_anahtari);
	
	char okul_no[100][9], cvplar[100][sorusayisi];	
	
	//cvp anahtarini virgullerden kurtarilmis hali
	while (cvp_anahtari[i] != NULL) {
    if (cvp_anahtari[i] != ',') {
      cvp_anahtari[j] = cvp_anahtari[i];
      i += 2;
     j++;
    } 
   
  }
  
	i=0;
	
	do{
	
	getline(dosyaOku,ogrcvp[i]);
	
	
	j=0;
	//ogr nosunu alýyoruz
	while (ogrcvp[i][j] != ',') {
      okul_no[i][j] = ogrcvp[i][j];
    
      j++;
    }
    j++;
    k=0;
    //ogr cvplarýný alýyoruz
    while (ogrcvp[i][j] != NULL) {
      if (ogrcvp[i][j] != ',') {
        cvplar[i][k] = ogrcvp[i][j];
        j += 2;
        k++;
      } else if (ogrcvp[i][j] == ',') {
        cvplar[i][k] = 'x'; // bos cvplar icin x koyduk
        j++;
        k++;
      }
    }
    
    if (ogrcvp[i][j - 1] == ',') {
      cvplar[i][k] = 'x'; 
    }
		puan[i]=0;
    for (int t=0;t<sorusayisi;t++){
    	if (cvplar[i][t]=='x'){
		puan[i];}
    	else if (cvplar[i][t]==cvp_anahtari[t]){
		puan[i]=puan[i]+4;}
    	else if (cvplar[i][t]!=cvp_anahtari[t]){
		puan[i]=puan[i]-1;}
    		
   	}
	
	//her ogrencinin aldýðý puan ve 0-100 araligina cekilmiþ hali
	int deger=4*sorusayisi; //max alýnabilecek puan
	if (puan[i] < 0) {
      puan[i] = 0;}
      else if (puan[i]>0){
	     puan[i]=100*puan[i]/deger;
    }
   
//cout<< puan[i]<<i<<endl;
	i++;
	kisi_sayisi=i;
     	
}while(!dosyaOku.eof());

	dosyaOku.close();
}


	float temp=0;
	char temp_no;
	for(int j=0;j<kisi_sayisi;j++){
	
	for (int k=0;k<kisi_sayisi;k++){
		
		if(puan[k]<puan[k+1]){
		
		 temp=puan[k+1];
		 puan[k+1]=puan[k];
		 puan[k]=temp;
		   for (int t = 0; t < 9; t++) {
              temp_no = okul_no[k+1][t];
              okul_no[k+1][t] = okul_no[k][t];
              okul_no[k][t] = temp_no;
	}
		 
	}
		
		
		}
		
	}
	
float max_puan=puan[0];
float min_puan=puan[kisi_sayisi-1];
float range=max_puan-min_puan;
float toplam=0;
float ortalama;
float medyan;

if(kisi_sayisi%2==0){
	medyan=(puan[(kisi_sayisi/2)-1]+puan[(kisi_sayisi/2)])/2;
	
}
else if (kisi_sayisi%2!=0){
	int deger=kisi_sayisi%2;
	medyan=puan[deger+1];
}
	
for(int k=0;k<kisi_sayisi;k++){
	toplam+=puan[k];
	//cout<<puan[k]<<endl;
}
ortalama=toplam/kisi_sayisi;



 ofstream file("output.txt");
    for(int i=0;i<kisi_sayisi;i++){
    	for(int j=0;j<9;j++){
    		file << okul_no[i][j];
		}
	 file <<","<<puan[i]<<endl;;
          
        }
        
        file <<min_puan <<"," << max_puan<< ","<<ortalama<<","<<medyan<<","<<range;
        
        cout << "dosya olusturuldu";
		        
      
    
return 0;
}
