const int ldrPin = A0;
const int valIsik = 140;
const int kisa = 80;
const int uzun = 250;
int timer2 = 100;
char harf[6];
bool ok = false;
const String morseMap[48][2] = {
  { "A", ".-" },
  { "B", "-..." },
  { "C", "-.-." },
  { "D", "-.." },
  { "E", "." },
  { "F", "..-." },
  { "G", "--." },
  { "H", "...." },
  { "I", ".." },
  { "J", ".---" },
  { "K", "-.-" },
  { "L", ".-.." },
  { "M", "--" },
  { "N", "-." },
  { "O", "---" },
  { "P", ".--." },
  { "Q", "--.-" },
  { "R", ".-." },
  { "S", "..." },
  { "T", "-" },
  { "U", "..-" },
  { "V", "...-" },
  { "W", ".--" },
  { "X", "-..-" },
  { "Y", "-.--" },
  { "Z", "--.." },
  { " ", "     " },

  { "1", ".----" },
  { "2", "..---" },
  { "3", "...--" },
  { "4", "....-" },
  { "5", "....." },
  { "6", "-...." },
  { "7", "--..." },
  { "8", "---.." },
  { "9", "----." },
  { "0", "-----" },

  { ".", ".-.-.-" },
  { ",", "--..--" },
  { "?", "..--.." },
  { "!", "-.-.--" },
  { ":", "---..." },
  { ";", "-.-.-." },
  { "(", "-.--." },
  { ")", "-.--.-" },
  { "\"", ".-..-." },
  { "@", ".--.-." },
  { "&", ".-..." },
};



void setup() {
  Serial.begin(9600);
  add('\0');
  clearH();
  pinMode(ldrPin, INPUT);
}

//Gelen karakteri harf dizisine atarmak için fonksiyon
void add(char h) { 
  for (int i = 0; i < 6; i++) {
    if (harf[i] == '\0') { //Dizideki ilk boş yere gelen karakteri ekleyecek
      harf[i] = h;
      break;

    }
  }
}

//harf dizisini temizlemek için
void clearH() { 
  for (int i = 0; i < 6; i++) {
    harf[i] = '\0';
  }
}

//harf dizindeki morse kodunu karaktere dönüştürmek için
void decodeM() { 
  String hrf = String(harf);
  for (int i = 0; i < 48; i++) { //morseMap teki mors kodlarıyla harfin içindeki kodları karşılaştırıp aynı olanı ekrana yazar.
    if (morseMap[i][1] == hrf) {
      Serial.print('(' + morseMap[i][0] + ')');
    }
  }
}

void loop() {
  int timer = 0;
  timer2++;
  while (analogRead(ldrPin) > valIsik) {
    ok = false;
    timer = timer + 1;
    timer2 = 0;
    delay(1);
  }
  if (timer > uzun) { //eğer ısık uzun yanarsa '-' karakterini ekleyecek
    add('-');
    //Serial.print("-");
  }
  else if (timer > kisa) { //eğer ısık kısa yanarsa '-' karakterini ekleyecek
    add('.');
  }

  if (timer == 0) {
    if ( timer2 < 200) { //iki harf arası süre
      if (timer2 > 100) {
        if (ok == false) {
          Serial.print(harf);
          decodeM();
          clearH();
          Serial.print("/");
          ok = true;
        }
      }
    }
    else if (timer2 < 450) { //iki kelime arası süre
      if (timer2 > 448) {
        Serial.println(" ");
      }
    }

  }
  delay(1);
}
