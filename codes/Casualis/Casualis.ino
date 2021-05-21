#include <Servo.h>
Servo S1;
Servo S2;
Servo petit;
int bouton = 13;
int led = 2;

double d;
double m;
double L = 22;
double beta ;
double rbeta ;
double alpha ;
double x=0;
double y=0;
double x1=0;// servira d'ancien point x 
double y1=0;// servira d'ancien point y
double a;
double X1;
double X2;
double z;
double pi = 3.14159265359;
int petitServoH = 180;
int petitServoB = 85;
int c=1;


int type; //=random(1,5);
int pinR=6;//sortie son Right
int pinL=7;//sortie son Left
int pinB=12;//sortie son bib
int sr;//son right
int sl;//son left
int sb;// son bi
// definition des fréquences des notes:
float Do[]={32.70,65.41,130.81,261.63,523.25};
float Reb[]={34.65,69.30,138.59,277.18,554.37};
float Re[]={36.71,73.42,146.83,293.66,587.33};
float Mib[]={38.89,77.78,155.56,311.13,622.25};
float Mi[]={41.20,82.41,164.81,329.63,659.26};
float Fa[]={43.65,87.31,174.61,349.23,698.46};
float Solb[]={46.25,92.50,185,369.99,739.99};
float Sol[]={49,98,196,392,783.99};
float Lab[]={51.91,103.83,207.65,415.30,830.61};
float La[]={55,110,220,440,880};
float Sib[]={58.27,116.54,233.08,466.16,932.33};
float Si[]={61.74,123.47,246.94,493.88,987.77};
int wait=500; // temps d'attente apres une note (il peux definir le temps de la note)
int fin=3;
int SonB= 16; // note de base lors de l'effet de monter de note jusqu'a la note definit en fonction de la couleur
int Alea; // variable de temps des pics de note lorsqu'il demande une couleur
int aleaMelodie;// variable pour l'effet des petit pic de notes lorsqu'il demande une couleur
int noteB= 0;// note joué lorsqu'il demande une couleur
int dureNote=500;// ≠ de wait il definit le temps pendant lequel sera jouée au max
int couleur;// variable defiissant une couleur
int octave;// varie entre 0 et 4 et dépend de la coordonnée x du point
float note1= Do[0];// sert pour les effet de slide (c'est l'ancienne note joué par le robot)
float note=note1;// note est la note que joue le prg lors de ses mouvements


void setup() {
 //initialisation des servo
 S1.attach(9);
 S2.attach(10);
 petit.attach(11);

 //initialisation des communications
 Serial.begin (115200);

 //initialisation des pins
 pinMode(bouton,INPUT);
 pinMode(led,OUTPUT);


pinMode(pinR,OUTPUT);//son R
pinMode(pinL,OUTPUT);//son L
pinMode(pinB,OUTPUT);//bib
  //musique d'intro
 prelude();
 //random seed
 attendre();
 randomSeed(millis()); 
 prelude();

 }


void loop() {

  changerCrayon();
  actionnerBras();
  petit.write(petitServoB);

 while (c<=295){
   c = random (1,301);

   delay(10);

   if(c <= 270){
     actionnerBras();
     }
   else{ if(c<=295){
     changerCrayon();
     petit.write(petitServoB);
     } } 
     }

    petit.write(petitServoH);
    titre();
    c=1;
    Serial.flush();
 }



void attendre(){                      //attendre tant qu'on appuie pas sur le bouton
 while(digitalRead(bouton) == 0){
   delay(50);}
   delay(1000);
    type=random(1,5);// on definit le genre de musique qui va se faire pendant l'utilisation d'une couleur
   }


void actionnerBras(){      //choisir les coordonées d'un point et l'atteindre en actionnant S1 et S2
 x1=x; 
 y1=y;//on definit les anciennes positions pour calculer la distance des points entre eux et en faire des notes.  
 x = random (12,36); //(16,50.7)
 y = random (2,21);    //(1,25)
 //x=30;
 //y=2;
// Serial.println(String(x) + " ; " + String(y));
 d = sqrt(pow(y,2)+pow(x,2));
 z = (-pow(d,2)+2*pow(L,2))/(2*pow(L,2));
 rbeta = acos (z);
 beta = 180/pi *rbeta;
 a= y/x;
 m= atan(a) *(180)/pi;
 alpha = 180-beta;
 X1 = m + (alpha/2) + 20;
 X2 = 180 - (90 - m + (alpha/2))+20;
// Serial.println(rbeta);
 //Serial.println(z); 

 //musique
 //octave en fonction de la position x 
 octave = map(x, 12, 40.7, 0, 4);
   sr=x-x1;
   abs(sr);
   sr=map(sr, 0, 28.7, 1, 7);
   sl=y-y1;
   abs(sl);
   sl=map(sl, 0, 19, 1, 7); //écart entre la position x1 et x et entre y1 et y ------> valeur entre 1 et 7

 S1.write(X1); 
 S2.write(X2); // on demande aux servo-moteurs de prendre la position calculée


//en fonction du type(1,2,3,4,5) (gamme ou effet) on aurra des mélodies de different genre.
if (type==1){
{switch(sr){
case 1:note= Do[octave];
break;
case 2:note=Re[octave];
break;
case 3:note= Mi[octave];
break;
case 4:note=Fa[octave];
break;
case 5:note=Sol[octave];
break;
case 6:note=La[octave];
break;
case 7:note=Si[octave];
break;}}
tone(pinB, note, dureNote); // on fait sonner la note
delay(wait);


{switch(sl){
case 1:note=Do[octave];
break;
case 2:note=Re[octave];
break;
case 3:note= Mi[octave];
break;
case 4:note=Fa[octave];
break;
case 5:note=Sol[octave];
break;
case 6:note=La[octave];
break;
case 7:note=Si[octave];
break;}}
tone(pinB, note, dureNote);
delay(wait);
}

if (type==2){ // en Majeur
{switch(sr){
case 1:note=Mi[octave];
break;
case 2:note=Solb[octave];
break;
case 3:note=Lab[octave];
break;
case 4:note=La[octave];
break;
case 5:note=Si[octave];
break;
case 6:note=Reb[octave];
break;
case 7:note=Mib[octave];
break;}}
tone(pinB, note, dureNote);
delay(wait);


{switch(sl){
case 1:note=Do[octave];
break;
case 2:note=Re[octave];
break;
case 3:note=Mi[octave];
break;
case 4:note=Fa[octave];
break;
case 5:note=Sol[octave];
break;
case 6:note=La[octave];
break;
case 7:note=Si[octave];
break;}}
tone(pinB, note, dureNote);
delay(wait);

}

if (type==3){ // en mineur
{switch(sr){
case 1:note=Mib[octave];
break;
case 2:note=Fa[octave];
break;
case 3:note= Sol[octave];
break;
case 4:note=Lab[octave];
break;
case 5:note=Sib[octave];
break;
case 6:note=Do[octave];
break;
case 7:note=Re[octave];
break;}}
tone(pinB, note, dureNote);
delay(wait);

{switch(sl){
case 1:note=Do[octave];
break;
case 2:note=Re[octave];
break;
case 3:note=Mi[octave];
break;
case 4:note=Fa[octave];
break;
case 5:note=Sol[octave];
break;
case 6:note=La[octave];
break;
case 7:note=Si[octave];
break;}}
tone(pinB, note, dureNote);
delay(wait);
  }
if (type== 4 or type==5){ // effet slide
 note1=note; 
{switch(sr){
case 1:note = Mib[octave];
break;
case 2:note = Fa[octave];
break;
case 3:note = Sol[octave];
break;
case 4:note = Lab[octave];
break;
case 5:note = Sib[octave];
break;
case 6:note = Do[octave];
break;
case 7:note = Re[octave];
break;}}

if(note1 <note){
 float temps=500/(note-note1);
 for (note1; note1<note; note1++){
 tone (pinB, note1, 1000);
 delay(temps);
   }
   goto prgBras; // on saute les autres conditions (if) pour ne pas risquer d'entrer dans une boucle infinit
  }
if(note1>note){
 float temps=500/(note1-note);
 for (note1; note1>note; note1--){
 tone (pinB, note1,1000);
 delay(temps);
   }
   goto prgBras;
  }
if(note1==note){
 tone(pinB, note,1000);
 delay(wait);
 goto prgBras;
  }
 }
 prgBras:
 delay(1);
}

void changerCrayon(){       // lever crayon / allumer led /choisir et demander une couleur / attendre 
petit.write(petitServoH);
digitalWrite(led,HIGH);
Serial.print("Pourrais je avoir le ");

int couleur = random (1,18);
delay(1500);
{switch(couleur){
 case 1 : Serial.print ("bleu foncé");
  noteB= Do[1];
  tone(pinB, Do[1], dureNote);// on fais sonner une note en fonction de la couleur
  break;
 case 2 : Serial.print ("violet");
  noteB= Re[1];
  tone(pinB, Re[1], dureNote);
  break;
 case 3 : Serial.print ("rose");
  noteB= Mi[1];
  tone(pinB, Mi[1], dureNote);  
  break;
 case 4 : Serial.print ("rouge");
  noteB= Fa[1];
  tone(pinB, Fa[1], dureNote);
  break;
 case 5 : Serial.print ("orange");
  noteB= Sol[1];
  tone(pinB, Sol[1], dureNote);
  break;
 case 6 : Serial.print ("jaune");
  noteB= La[1];
  break;
 case 7 : Serial.print ("vert clair");
  noteB= Si[1];
  tone(pinB, Si[1], dureNote);
  break;
 case 8 : Serial.print ("gris");
  noteB= Lab[1];
  tone(pinB, Lab[1], dureNote); 
  break;
 case 9 : Serial.print ("cyan");
  noteB= Reb[1];
  tone(pinB, Reb[1], dureNote);
  break;
 case 10 : Serial.print ("turquoise");
  noteB= Sib[1];
  tone(pinB, Sib[1], dureNote);
  break;
 case 11 : Serial.print ("jaune orangé");
  note= Mi[1];
 tone(pinB, Mi[1], dureNote);
 delay(250);
 tone(pinR, Si[1], dureNote); 
  break;
  case 12 : Serial.print ("beige");
  note= Sol[1];
 tone(pinB, Sol[1], dureNote);
 delay(250);
 tone(pinB, Re[1], dureNote);
  break;
   case 13 : Serial.print ("brun");
   note=La[1];
  tone(pinB, La[1], dureNote);
  delay(250);
  tone(pinB, Mi[1], dureNote);
  break;
  case 14 : Serial.print ("marron");
  note=Si[1];
  tone(pinB, Si[1], dureNote);
  delay(250);
  tone(pinB, Fa[1], dureNote);
  break;
     case 15 : Serial.print ("vert foncé");
  note=Fa[1];
  tone(pinB, Fa[1], dureNote);
  delay(250);
  tone(pinB, Lab[1], dureNote);
  break;
     case 16 : Serial.print ("noir");
  note=Do[1];
  tone(pinB, Fa[1], dureNote);
  delay(250);
  tone(pinB, Do[1], dureNote);
  delay(250);
  tone(pinB, Fa[1], dureNote);
  break;
     case 17 : Serial.print ("mauve");
  note=Do[1];
  tone(pinB, Do[1], dureNote);
  delay(250);
  tone(pinB, Mi[1], dureNote);
  break; }}
delay(wait);

//effet slide: on monte de plus en plus la fréquance pour atteindre la note definit par la couleur
 for (int i=0; i <= noteB; i++){ 
 tone (pinB, SonB, 1000);
 SonB= SonB+1;
 delay(20);
}

 Serial.println(" s'il vous plaît?");
  // effet de pics de fréquences aléatoires durant une durée aléatoire
Alea=random(1,20);
for (int i=0; i <= Alea ; i++){ 
 aleaMelodie=random(1,440);
  tone (pinB, aleaMelodie, 1000);
 delay(50);
}
// on fait sonner la note definie par la couleur
 tone(pinB,noteB,1000);
  SonB=16;
  delay(1500);

  attendre();
  digitalWrite(led,LOW);
  Serial.println("Merci!");

 }



void titre(){         //écrire le titre de l'oeuvre


 int genre;
 int determinant;
 int adj1;
 int nom;
 int adj2;
 int complement;

 genre=random(1,5); // 1:plurielF 2:plurielM 3:singulierF 4:singulierM
 determinant = random(1,11); // 1:des 2:les 3:leurs 4:ces 5:ses

 if (genre==1 or genre==2) {     //pluriel

//determinant$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$determinant

    switch(determinant){
     case 1: Serial.print("des");
       break;
     case 2: Serial.print("les");
       break;
     //case 3: Serial.print("leurs");
    //   break;
     case 4: Serial.print("ces");
       break;
     case 5: Serial.print("ô");
       break;
     case 6: Serial.print("ô");
       break; }}


 if (genre==3){         //feminin sg

    switch(determinant){
     case 1: Serial.print("une");
       break;
     case 2: Serial.print("cette");
       break;
     case 3: Serial.print("ô");
       break;
     case 4: Serial.print("ô");
       break;
      }}

if (genre==4){            //masculin sg

    switch(determinant){
     case 1: Serial.print("un");
       break;
     // case 2: Serial.print("son");
     //  break;
     case 3: Serial.print("ô");
       break;
     case 4: Serial.print("ô");
       break;
      }}


    Serial.print(" ");
    delay(10);

//adj1 $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$adj1

adj1=random(1,26);

if (genre==4 or genre==2){              //masculin

   switch(adj1){
     case 1: Serial.print("adorable");
       break;
     case 2: Serial.print("admirable");
       break;
     case 3: Serial.print("irrégulier");
       break;
     case 4: Serial.print("calme");
       break;
     case 5: Serial.print("indolent");
       break;
     case 6: Serial.print("humble");
       break;
     case 7: Serial.print("hardi");
       break;
     case 8: Serial.print("rebelle");
       break;
     case 9: Serial.print("timide");
       break;
     case 10: Serial.print("ravissant");
       break;
     case 11: Serial.print("pathétique");
       break;
     case 12: Serial.print("coquet");
       break;
     case 13: Serial.print("galant");
       break;}}


if (genre==1 or genre==3){                  //feminin

   switch(adj1){
     case 1: Serial.print("adorable");
       break;
     case 2: Serial.print("admirable");
       break;
     case 3: Serial.print("irrégulière");
       break;
     case 4: Serial.print("belle");
       break;
     case 5: Serial.print("ambitieuse");
       break;
     case 6: Serial.print("calme");
       break;
     case 7: Serial.print("courageuse");
       break;
     case 8: Serial.print("rebelle");
       break;
     case 9: Serial.print("timide");
       break;
     case 10: Serial.print("ravissante");
       break;
     case 11: Serial.print("limpide");
       break;
     case 12: Serial.print("gracieuse");
       break;
     case 13: Serial.print("courtoise");
       break;}}


   //if (genre==1 or genre==2 & adj1<=13);            //pluriel               //problème de priorité and et or
    if(genre==1 and adj1<=13 or genre==2 and adj1<=13)
        {Serial.print("s");}
    delay(2);
    if (adj1<=13) {Serial.print(" ");}




//nom$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$nom

    nom=random(1,15);

 if (genre==4 or genre==2){              //masculin

   switch(nom){
     case 1: Serial.print("paysage");
     note=Do[octave]; // on donne ou pas une note en fonction du nom du titre 
       break;
     case 2: Serial.print("pic");
     note=Re[octave];
       break;
     case 3: Serial.print("coquelicot");
     note=Mi[octave];
       break;
     case 4: Serial.print("espace");
     note=10;
       break;
     case 5: Serial.print("vide");
     note=0;
       break;
     case 6: Serial.print("néant");
     note=0;
       break;
     case 7: Serial.print("chemin");
     note=Si[octave];
       break;
     case 8: Serial.print("astéroïde");
     note=Solb[octave];
       break;
     case 9: Serial.print("jardin");
     note=Lab[octave];
       break;
     case 10: Serial.print("navire");
     note=Reb[octave];
       break;
     case 11: Serial.print("homme");
     note=Mib[octave];
       break;
     case 12: Serial.print("garçon");
     note=La[octave];
       break;
     case 13: Serial.print("personnage");
     note=Fa[octave];
       break;
     case 14: Serial.print("rêve");
     note=Sol[octave];
       break;}}


if (genre==1 or genre==3){              //feminin

   switch(nom){
     case 1: Serial.print("cascade");
       break;
     case 2: Serial.print("montagne");
       break;
     case 3: Serial.print("falaise");
       break;
     case 4: Serial.print("mer");
       break;
     case 5: Serial.print("vallée");
       break;
     case 6: Serial.print("maison");
       break;
     case 7: Serial.print("rose");
       break;
     case 8: Serial.print("nuit");
       break;
     case 9: Serial.print("hortensia");
       break;
     case 10: Serial.print("galaxie");
       break;
     case 11: Serial.print("soirée");
       break;
     case 12: Serial.print("femme");
       break;
     case 13: Serial.print("demoiselle");
       break;
     case 14: Serial.print("personne");
       break;}}


   //if (genre==1 or genre==2 & nom<=14);            //pluriel
   if((genre==1 and nom<=14) or (genre==2 and nom<=14))
      {Serial.print("s");}
    if (nom<=14){Serial.print(" ");}


// adjectif 2 $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$adj2

 adj2=random(1,21);                                    
   if (genre==4 or genre==2){              //masculin

   switch(adj2){
     case 1: Serial.print("rose");
       break;
     case 2: Serial.print("pâle");
       break;
     case 3: Serial.print("fuchsia");
       break;
     case 4: Serial.print("perlé");
       break;
     case 5: Serial.print("argenté");
       break;
     case 6: Serial.print("doré");
       break;
     case 7: Serial.print("noisette");
       break;
     case 8: Serial.print("stylisé");
       break;
     case 9: Serial.print("mélancolique");
       break;
     case 10: Serial.print("épuré");
       break;
     case 11: Serial.print("utopique");
       break;
      }}


if (genre==1 or genre==3){              //feminin

   switch(adj2){
     case 1: Serial.print("rose");
       break;
     case 2: Serial.print("pâle");
       break;
     case 3: Serial.print("fuschia");
       break;
     case 4: Serial.print("perlée");
       break;
     case 5: Serial.print("dorée");
       break;
     case 6: Serial.print("argentée");
       break;
     case 7: Serial.print("noisette");
       break;
     case 8: Serial.print("stylisée");
       break;
     case 9: Serial.print("mélancolique");
       break;
     case 10: Serial.print("épurée");
       break;
     case 11: Serial.print("utopique");
       break;
      }}


   //if (genre==1 or genre==2 & adj2<=11);            //pluriel
   if(genre==1 and adj2<=11 or genre==2 and adj2<=11)
    {Serial.print("s");}
    if (adj2<=11){Serial.print(" ");}


//complement$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$complement

    complement=random(1,20);
     switch(complement){
      case 1:
       Serial.print("dormant"); break;
      case 2:
       Serial.print("voyageant"); break;
      case 3:
       Serial.print("entre ciel et mer"); break;
      case 4:
       Serial.print("mourant"); break;
      case 5:
       Serial.print("en hiver"); break;
      case 6:
       Serial.print("du futur"); break;
      case 7:
       Serial.print("saluant le passé"); break;
      case 8:
       Serial.print("contemplant l'avenir"); break;
      case 9:
       Serial.print("sous des myriades d'étoiles"); break;
      case 10:
       Serial.print("au milieu des oiseaux"); break;
      case 11:
       Serial.print("aux aguets"); break;
      case 12:
       Serial.print("gisant"); break;
       }

    Serial.println();
    // effet slide pour aller jusqu'à la note definit par le nom du titre 
delay(1000);
 float temps=500/note;
 for (note1; note1<note; note1++){
 tone (pinB, note1, 1000);
 delay(temps);
   }
   tone(pinB,note,1000); // on fait sonner la note qui dépend du nom du titre
   delay(1000);

 attendre();
 }

 void prelude () {
delay(1000);
tone(pinB, La[2], 200);
delay(250);
tone(pinB, Mi[2], 200);
delay(250);
tone(pinB, Re[2], 1000);
delay(1000);
tone(pinB, Sol[3], 200);
delay(250);
tone(pinB, Fa[2], 990);
delay(1000);
tone(pinB, Re[1], 450);
delay(500);
float temps=500/(Re[1]-note1);
 for (note1; note1<Re[1]; note1++){
 tone (pinB, note1, 1000);
 delay(temps);
   }
tone(pinB, Re[1], 1000);
delay(1000);
}
