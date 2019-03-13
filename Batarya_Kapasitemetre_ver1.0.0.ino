/* Ver.1.0.0
    Batarya Kapasitemetre
    Ornek olarak 12 volt kursun asit aku icin degerler hesaplandi
*/
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

byte dolu[8] = {B11111, B11111, B11111, B11111, B11111, B11111, B11111, B11111};
byte bos[8] = {B00000, B00000, B00000, B00000, B00000, B00000, B00000, B00000};
byte sifir[8] = {B10000, B10000, B10000, B10000, B10000, B10000, B10000, B10000};
byte kutupust[8] = {B11000, B11000, B11000, B11000, B11000, B11110, B11110, B11110};
byte kutupalt[8] = {B11110, B11110, B11110, B11000, B11000, B11000, B11000, B11000};

float vPow = 4.7;
float r1 = 91000;
float r2 = 8000;



void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.createChar(0, bos);
  lcd.createChar(1, dolu);
  lcd.createChar(2, sifir);
  lcd.createChar(3, kutupust);
  lcd.createChar(4, kutupalt);


}

void loop() {
  // bir saniye araliklarla sekiz farklı voltaj olcumu yapılıyor
  float v1 = (analogRead(0) * vPow) / 1024.0;
  delay(1000);
  float v2 = (analogRead(0) * vPow) / 1024.0;
  delay(1000);
  float v3 = (analogRead(0) * vPow) / 1024.0;
  delay(1000);
  float v4 = (analogRead(0) * vPow) / 1024.0;
  delay(1000);
  float v5 = (analogRead(0) * vPow) / 1024.0;
  delay(1000);
  float v6 = (analogRead(0) * vPow) / 1024.0;
  delay(1000);
  float v7 = (analogRead(0) * vPow) / 1024.0;
  delay(1000);
  float v8 = (analogRead(0) * vPow) / 1024.0;
  float kap1 = v1 / (r2 / (r1 + r2));
  float kap2 = v2 / (r2 / (r1 + r2));
  float kap3 = v3 / (r2 / (r1 + r2));
  float kap4 = v4 / (r2 / (r1 + r2));
  float kap5 = v5 / (r2 / (r1 + r2));
  float kap6 = v6 / (r2 / (r1 + r2));
  float kap7 = v7 / (r2 / (r1 + r2));
  float kap8 = v8 / (r2 / (r1 + r2));
  // ve bu olcumlerin en yuksek degeri gosterilir. bu demek oluyorki ekranda sekiz saniyede bir deger gosterimi yapılıyor. boylelikle daha stabil sonuc gosterimi olusturulur.
  float kapasite1 = max(kap1, kap2);
  float kapasite2 = max(kap3, kap4);
  float kapasite3 = max(kap5, kap6);
  float kapasite4 = max(kap7, kap8);
  float kapasite_a = max(kapasite1, kapasite2);
  float kapasite_b = max(kapasite3, kapasite4);
  float kapasite = max(kapasite_a, kapasite_b);

  // serial monitorde takibi yapılır
  Serial.print("Olcum 1: ");
  Serial.println(kap1);
  Serial.print("Olcum 2: ");
  Serial.println(kap2);
  Serial.print("Olcum 3: ");
  Serial.println(kap3);
  Serial.print("Olcum 4: ");
  Serial.println(kap4);
  Serial.print("Olcum 5: ");
  Serial.println(kapasite1);
  Serial.print("Olcum 6: ");
  Serial.println(kapasite2);
  Serial.print("Olcum 7: ");
  Serial.println(kapasite3);
  Serial.print("Olcum 8: ");
  Serial.println(kapasite4);
  Serial.print("Olcum 9: ");
  Serial.println(kapasite_a);
  Serial.print("Olcum 10: ");
  Serial.println(kapasite_b);
  Serial.print("Max: ");
  Serial.println(kapasite);

  // LCD ekranda grafik gosterimi yapilir
  // Bataryaya bagladiginiz yuk ve uygulamaya gore %0 bos gosterge voltajini belirlemeniz gerekir. 
  // burada olctugunuz voltaj degeri ile dijital multimetrenizde yaptıginiz olcum arasinda ufak fark olacaktir
  if (kapasite < 11.02) {                             // %0 bos
    lcd.clear();
    lcd.setCursor(12, 0);
    lcd.print("%0");
    lcd.setCursor(12, 1);
    lcd.print("BOS");

    lcd.setCursor(0, 0);
    lcd.write(byte(2));
    lcd.setCursor(0, 1);
    lcd.write(byte(2));

    lcd.setCursor(10, 0);
    lcd.write(byte(3));
    lcd.setCursor(10, 1);
    lcd.write(byte(4));
  }

  else if (kapasite > 11.02 && kapasite < 11.22) {    // %10 dolu
    lcd.clear();
    lcd.setCursor(12, 0);
    lcd.print("%10");
    lcd.setCursor(12, 1);
    lcd.print("DOLU");
    lcd.setCursor(0, 0);
    lcd.write(byte(1));
    lcd.setCursor(0, 1);
    lcd.write(byte(1));
    lcd.setCursor(10, 0);
    lcd.write(byte(3));
    lcd.setCursor(10, 1);
    lcd.write(byte(4));
  }

  else if (kapasite > 11.22 && kapasite < 11.42) {    // %20 dolu
    lcd.clear();
    lcd.setCursor(12, 0);
    lcd.print("%20");
    lcd.setCursor(12, 1);
    lcd.print("DOLU");
    lcd.setCursor(0, 0);
    lcd.write(byte(1));
    lcd.setCursor(0, 1);
    lcd.write(byte(1));
    lcd.setCursor(1, 0);
    lcd.write(byte(1));
    lcd.setCursor(1, 1);
    lcd.write(byte(1));
    lcd.setCursor(10, 0);
    lcd.write(byte(3));
    lcd.setCursor(10, 1);
    lcd.write(byte(4));
  }

  else if (kapasite > 11.42 && kapasite < 11.63) {    // %30 dolu
    lcd.clear();
    lcd.setCursor(12, 0);
    lcd.print("%30");
    lcd.setCursor(12, 1);
    lcd.print("DOLU");
    lcd.setCursor(0, 0);
    lcd.write(byte(1));
    lcd.setCursor(0, 1);
    lcd.write(byte(1));
    lcd.setCursor(1, 0);
    lcd.write(byte(1));
    lcd.setCursor(1, 1);
    lcd.write(byte(1));
    lcd.setCursor(2, 0);
    lcd.write(byte(1));
    lcd.setCursor(2, 1);
    lcd.write(byte(1));
    lcd.setCursor(10, 0);
    lcd.write(byte(3));
    lcd.setCursor(10, 1);
    lcd.write(byte(4));
  }

  else if (kapasite > 11.63 && kapasite < 11.83) {    // %40 dolu
    lcd.clear();
    lcd.setCursor(12, 0);
    lcd.print("%40");
    lcd.setCursor(12, 1);
    lcd.print("DOLU");
    lcd.setCursor(0, 0);
    lcd.write(byte(1));
    lcd.setCursor(0, 1);
    lcd.write(byte(1));
    lcd.setCursor(1, 0);
    lcd.write(byte(1));
    lcd.setCursor(1, 1);
    lcd.write(byte(1));
    lcd.setCursor(2, 0);
    lcd.write(byte(1));
    lcd.setCursor(2, 1);
    lcd.write(byte(1));
    lcd.setCursor(3, 0);
    lcd.write(byte(1));
    lcd.setCursor(3, 1);
    lcd.write(byte(1));
    lcd.setCursor(10, 0);
    lcd.write(byte(3));
    lcd.setCursor(10, 1);
    lcd.write(byte(4));
  }

  else if (kapasite > 11.83 && kapasite < 12.03) {    // %50 dolu
    lcd.clear();
    lcd.setCursor(12, 0);
    lcd.print("%50");
    lcd.setCursor(12, 1);
    lcd.print("DOLU");
    lcd.setCursor(0, 0);
    lcd.write(byte(1));
    lcd.setCursor(0, 1);
    lcd.write(byte(1));
    lcd.setCursor(1, 0);
    lcd.write(byte(1));
    lcd.setCursor(1, 1);
    lcd.write(byte(1));
    lcd.setCursor(2, 0);
    lcd.write(byte(1));
    lcd.setCursor(2, 1);
    lcd.write(byte(1));
    lcd.setCursor(3, 0);
    lcd.write(byte(1));
    lcd.setCursor(3, 1);
    lcd.write(byte(1));
    lcd.setCursor(4, 0);
    lcd.write(byte(1));
    lcd.setCursor(4, 1);
    lcd.write(byte(1));
    lcd.setCursor(10, 0);
    lcd.write(byte(3));
    lcd.setCursor(10, 1);
    lcd.write(byte(4));
  }

  else if (kapasite > 12.03 && kapasite < 12.23) {    // %60 dolu
    lcd.clear();
    lcd.setCursor(12, 0);
    lcd.print("%60");
    lcd.setCursor(12, 1);
    lcd.print("DOLU");
    lcd.setCursor(0, 0);
    lcd.write(byte(1));
    lcd.setCursor(0, 1);
    lcd.write(byte(1));
    lcd.setCursor(1, 0);
    lcd.write(byte(1));
    lcd.setCursor(1, 1);
    lcd.write(byte(1));
    lcd.setCursor(2, 0);
    lcd.write(byte(1));
    lcd.setCursor(2, 1);
    lcd.write(byte(1));
    lcd.setCursor(3, 0);
    lcd.write(byte(1));
    lcd.setCursor(3, 1);
    lcd.write(byte(1));
    lcd.setCursor(4, 0);
    lcd.write(byte(1));
    lcd.setCursor(4, 1);
    lcd.write(byte(1));
    lcd.setCursor(5, 0);
    lcd.write(byte(1));
    lcd.setCursor(5, 1);
    lcd.write(byte(1));
    lcd.setCursor(10, 0);
    lcd.write(byte(3));
    lcd.setCursor(10, 1);
    lcd.write(byte(4));
  }

  else if (kapasite > 12.23 && kapasite < 12.43) {    // %70 dolu
    lcd.clear();
    lcd.setCursor(12, 0);
    lcd.print("%70");
    lcd.setCursor(12, 1);
    lcd.print("DOLU");
    lcd.setCursor(0, 0);
    lcd.write(byte(1));
    lcd.setCursor(0, 1);
    lcd.write(byte(1));
    lcd.setCursor(1, 0);
    lcd.write(byte(1));
    lcd.setCursor(1, 1);
    lcd.write(byte(1));
    lcd.setCursor(2, 0);
    lcd.write(byte(1));
    lcd.setCursor(2, 1);
    lcd.write(byte(1));
    lcd.setCursor(3, 0);
    lcd.write(byte(1));
    lcd.setCursor(3, 1);
    lcd.write(byte(1));
    lcd.setCursor(4, 0);
    lcd.write(byte(1));
    lcd.setCursor(4, 1);
    lcd.write(byte(1));
    lcd.setCursor(5, 0);
    lcd.write(byte(1));
    lcd.setCursor(5, 1);
    lcd.write(byte(1));
    lcd.setCursor(6, 0);
    lcd.write(byte(1));
    lcd.setCursor(6, 1);
    lcd.write(byte(1));
    lcd.setCursor(10, 0);
    lcd.write(byte(3));
    lcd.setCursor(10, 1);
    lcd.write(byte(4));
  }

  else if (kapasite > 12.43 && kapasite < 12.64) {    // %80 dolu
    lcd.clear();
    lcd.setCursor(12, 0);
    lcd.print("%80");
    lcd.setCursor(12, 1);
    lcd.print("DOLU");
    lcd.setCursor(0, 0);
    lcd.write(byte(1));
    lcd.setCursor(0, 1);
    lcd.write(byte(1));
    lcd.setCursor(1, 0);
    lcd.write(byte(1));
    lcd.setCursor(1, 1);
    lcd.write(byte(1));
    lcd.setCursor(2, 0);
    lcd.write(byte(1));
    lcd.setCursor(2, 1);
    lcd.write(byte(1));
    lcd.setCursor(3, 0);
    lcd.write(byte(1));
    lcd.setCursor(3, 1);
    lcd.write(byte(1));
    lcd.setCursor(4, 0);
    lcd.write(byte(1));
    lcd.setCursor(4, 1);
    lcd.write(byte(1));
    lcd.setCursor(5, 0);
    lcd.write(byte(1));
    lcd.setCursor(5, 1);
    lcd.write(byte(1));
    lcd.setCursor(6, 0);
    lcd.write(byte(1));
    lcd.setCursor(6, 1);
    lcd.write(byte(1));
    lcd.setCursor(7, 0);
    lcd.write(byte(1));
    lcd.setCursor(7, 1);
    lcd.write(byte(1));
    lcd.setCursor(10, 0);
    lcd.write(byte(3));
    lcd.setCursor(10, 1);
    lcd.write(byte(4));
  }

  else if (kapasite > 12.64 && kapasite < 12.84) {    // %90 dolu
    lcd.clear();
    lcd.setCursor(12, 0);
    lcd.print("%90");
    lcd.setCursor(12, 1);
    lcd.print("DOLU");
    lcd.setCursor(0, 0);
    lcd.write(byte(1));
    lcd.setCursor(0, 1);
    lcd.write(byte(1));
    lcd.setCursor(1, 0);
    lcd.write(byte(1));
    lcd.setCursor(1, 1);
    lcd.write(byte(1));
    lcd.setCursor(2, 0);
    lcd.write(byte(1));
    lcd.setCursor(2, 1);
    lcd.write(byte(1));
    lcd.setCursor(3, 0);
    lcd.write(byte(1));
    lcd.setCursor(3, 1);
    lcd.write(byte(1));
    lcd.setCursor(4, 0);
    lcd.write(byte(1));
    lcd.setCursor(4, 1);
    lcd.write(byte(1));
    lcd.setCursor(5, 0);
    lcd.write(byte(1));
    lcd.setCursor(5, 1);
    lcd.write(byte(1));
    lcd.setCursor(6, 0);
    lcd.write(byte(1));
    lcd.setCursor(6, 1);
    lcd.write(byte(1));
    lcd.setCursor(7, 0);
    lcd.write(byte(1));
    lcd.setCursor(7, 1);
    lcd.write(byte(1));
    lcd.setCursor(8, 0);
    lcd.write(byte(1));
    lcd.setCursor(8, 1);
    lcd.write(byte(1));
    lcd.setCursor(10, 0);
    lcd.write(byte(3));
    lcd.setCursor(10, 1);
    lcd.write(byte(4));
  }

  else if (kapasite > 12.84) {                        // %100 dolu
    lcd.clear();
    lcd.setCursor(12, 0);
    lcd.print("%100");
    lcd.setCursor(12, 1);
    lcd.print("FULL");
    lcd.setCursor(0, 0);
    lcd.write(byte(1));
    lcd.setCursor(0, 1);
    lcd.write(byte(1));
    lcd.setCursor(1, 0);
    lcd.write(byte(1));
    lcd.setCursor(1, 1);
    lcd.write(byte(1));
    lcd.setCursor(2, 0);
    lcd.write(byte(1));
    lcd.setCursor(2, 1);
    lcd.write(byte(1));
    lcd.setCursor(3, 0);
    lcd.write(byte(1));
    lcd.setCursor(3, 1);
    lcd.write(byte(1));
    lcd.setCursor(4, 0);
    lcd.write(byte(1));
    lcd.setCursor(4, 1);
    lcd.write(byte(1));
    lcd.setCursor(5, 0);
    lcd.write(byte(1));
    lcd.setCursor(5, 1);
    lcd.write(byte(1));
    lcd.setCursor(6, 0);
    lcd.write(byte(1));
    lcd.setCursor(6, 1);
    lcd.write(byte(1));
    lcd.setCursor(7, 0);
    lcd.write(byte(1));
    lcd.setCursor(7, 1);
    lcd.write(byte(1));
    lcd.setCursor(8, 0);
    lcd.write(byte(1));
    lcd.setCursor(8, 1);
    lcd.write(byte(1));
    lcd.setCursor(9, 0);
    lcd.write(byte(1));
    lcd.setCursor(9, 1);
    lcd.write(byte(1));
    lcd.setCursor(10, 0);
    lcd.write(byte(3));
    lcd.setCursor(10, 1);
    lcd.write(byte(4));
  }

}
