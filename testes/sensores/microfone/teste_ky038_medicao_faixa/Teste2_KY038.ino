const int microphonePin = 25;

void setup() {
  Serial.begin(115200);

}

void loop() {
  int mn = 1024;
  int mx = 0;

  for (int i = 0; i < 10000; ++i) {

    int val = analogRead(microphonePin);
    
    mn = min(mn, val);
    mx = max(mx, val);
  }

  int val = analogRead(microphonePin);
  int delta = mx - mn;

  Serial.print("Min=");
  Serial.print(mn);
  Serial.print(" Max=");
  Serial.print(mx);
  Serial.print(" Delta=");
  Serial.print(delta);
  Serial.print(" Val=");
  Serial.println(val);



}

/**
-Sala
Min=423 Max=688 Delta=265 Val=528
Min=415 Max=676 Delta=261 Val=539
Min=339 Max=522 Delta=183 Val=457
Min=426 Max=650 Delta=224 Val=537
Min=489 Max=627 Delta=138 Val=530
Min=458 Max=673 Delta=215 Val=550
Min=400 Max=603 Delta=203 Val=499
Min=401 Max=640 Delta=239 Val=511
Min=372 Max=679 Delta=307 Val=497
Min=400 Max=609 Delta=209 Val=479
Min=431 Max=622 Delta=191 Val=507
Min=425 Max=691 Delta=266 Val=555
Min=483 Max=686 Delta=203 Val=574
Min=469 Max=612 Delta=143 Val=598
Min=464 Max=621 Delta=157 Val=547
Min=416 Max=706 Delta=290 Val=544
Min=407 Max=714 Delta=307 Val=544


-Quarto
Min=351 Max=1053 Delta=702 Val=560
Min=393 Max=1104 Delta=711 Val=582
Min=368 Max=1058 Delta=690 Val=573
Min=355 Max=987 Delta=632 Val=582
Min=394 Max=907 Delta=513 Val=589
Min=329 Max=1069 Delta=740 Val=590
Min=357 Max=752 Delta=395 Val=509
Min=314 Max=874 Delta=560 Val=502
Min=295 Max=793 Delta=498 Val=475
Min=301 Max=1105 Delta=804 Val=483
Min=368 Max=745 Delta=377 Val=562
Min=400 Max=758 Delta=358 Val=541




  if(780< mx & mx < 1080 & 100 < delta & delta < 500){//800 1100
    modo1=!modo1;
    digitalWrite(Fita1, modo1);
  }
   if(1100 < mx & mx < 1500 & 700 < delta & delta < 1200){//1200 1500
    modo2=!modo2;
    digitalWrite(Fita2, modo2);
  }
**/
