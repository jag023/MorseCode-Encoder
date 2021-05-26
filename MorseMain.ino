/*Dot duration is 1 time unit,
Dash duration is 3 time units,
Each letter would be separated by 3 time units,
Each word would be separated by 7 times units.
inter-element gap between the dots and dashes within a character: one dot
duration or one unit long
*/

#include <Hash.h>
#include <HashMap.h>
#include <stdlib.h>


//////////unit of time defined
#define TIME_UNIT 200


//variance function
float var_compute(float varr[], float avg){
  int j;
    float dif[1000];
    float sqd;
    float varSum=0;
    for(j=0;j<1000;j++) {
        dif[j]=varr[j]-avg;
        sqd=pow(dif[j],2);
       varSum = sqd + varSum;
    }
    return varSum;
}

//standard Deviation function
float stdDev_compute(float var){
  
  return sqrtf(var);
  
}


//define the max size of the hashtable to be 1.5n (n is num to be hashed) pime number to help reduce collisions
const byte HASH_SIZE = 131; 
//morse storage 
HashType<char*,char*> hashRawArray[HASH_SIZE]; 
//handles the morse storage [search,retrieve,insert]
HashMap<char*,char*> hashMap = HashMap<char*,char*>( hashRawArray , HASH_SIZE ); 

//creat white led with pins// 
int red_light_pin = 16;
int green_light_pin = 17;
int blue_light_pin = 18;
void RGB_color_off(int red_light_value, int green_light_value, int blue_light_value)
 {
  digitalWrite(red_light_pin, red_light_value);
  digitalWrite(green_light_pin, green_light_value);
  digitalWrite(blue_light_pin, blue_light_value);
}
void RGB_color_on(int red_light_value, int green_light_value, int blue_light_value)
 {
  digitalWrite(red_light_pin, 255-red_light_value);
  digitalWrite(green_light_pin, 255-green_light_value);
  digitalWrite(blue_light_pin, 255-blue_light_value);
}





void morseTranslator_emit(String c)
{
  String signal = c;

  byte i;
  char signalLength = signal.length();
  for (i = 0 ; i < signalLength+1 ; i++) {
    switch (signal.charAt(i)) {
      case '.':
        dot();
        break;

      case '-':
        dash();
        break;

      case '\0':
       
        space();
        Serial.println(" ");
        return;
    }
  }

  endLetter();
}

void dot()
{
  Serial.print(".");
  RGB_color_on(255,255,255);
  delay(TIME_UNIT);
  RGB_color_off(255,255,255);
  delay(TIME_UNIT);
}
void dash()
{
  Serial.print("-");
  RGB_color_on(255,255,255);
  delay(3 * TIME_UNIT);
  RGB_color_off(255,255,255);
  delay(TIME_UNIT);
}
//timebetween letters
void endLetter()
{
  //Serial.println("");
  delay(3 * TIME_UNIT);
}


void space()
{
  //Serial.flush();
  delay(7 * TIME_UNIT);
}

void setup() {

  //Serial.flush();
  
  Serial.begin(115200);
  

  
   //setup hashmap
  hashMap[0]("a",".-");
  hashMap[1]("A",".-");
  hashMap[2]("b","-...");
  hashMap[3]("B","-...");
  hashMap[4]("c","-.-.");
  hashMap[5]("C","-.-.");
  hashMap[6]("d","-..");
  hashMap[7]("D","-..");
  hashMap[8]("e",".");
  hashMap[9]("E",".");
  hashMap[10]("f","..-.");
  hashMap[11]("F","..-.");
  hashMap[12]("g","--.");
  hashMap[13]("G","--.");
  hashMap[14]("h","....");
  hashMap[15]("H","....");
  hashMap[16]("i","..");
  hashMap[17]("I","..");
  hashMap[18]("j",".---");
  hashMap[19]("J",".---");
  hashMap[20]("k","-.-");
  hashMap[21]("K","-.-");
  hashMap[22]("l",".-..");
  hashMap[23]("L",".-..");
  hashMap[24]("m","--");
  hashMap[25]("M","--");
  hashMap[26]("n","-.");
  hashMap[27]("N","-.");
  hashMap[28]("o","---");
  hashMap[29]("O","---");
  hashMap[30]("p",".--.");
  hashMap[31]("P",".--.");
  hashMap[32]("q","--.-");
  hashMap[33]("Q","--.-");
  hashMap[34]("r",".-.");
  hashMap[35]("R",".-.");
  hashMap[36]("s","...");
  hashMap[37]("S","...");
  hashMap[38]("t","-");
  hashMap[39]("T","-");
  hashMap[40]("u","..-");
  hashMap[41]("U","..-");
  hashMap[42]("v","...-");
  hashMap[43]("V","...-");
  hashMap[44]("w",".--");
  hashMap[45]("W",".--");
  hashMap[46]("x","-..-");
  hashMap[47]("X","-..-");
  hashMap[48]("y","-.--");
  hashMap[49]("Y","-.--");
  hashMap[50]("z","--..");
  hashMap[51]("Z","--..");
  hashMap[52]("0","-----");
  hashMap[53]("1",".----");
  hashMap[54]("2","..---");
  hashMap[55]("3","...--");
  hashMap[56]("4","....-");
  hashMap[57]("5",".....");
  hashMap[58]("6","-....");
  hashMap[59]("7","--...");
  hashMap[60]("8","---..");
  hashMap[61]("9","----.");
  hashMap[62](".",".-.-.-");
  hashMap[63](",","--..--");
  hashMap[64]("?","..--..");
  hashMap[65]("'",".----.");
  hashMap[66]("!","-.-.--");
  hashMap[67]("/","-..-.");
  hashMap[68]("(","-.--.");
  hashMap[69](")","-.--.-");
  hashMap[70]("&",".-...");
  hashMap[71](":","---...");
  hashMap[72](";","-.-.-.");
  hashMap[73]("=","-...-");
  hashMap[74]("+",".-.-.");
  hashMap[75]("-","-....-");
  hashMap[76]("_","..--.-");
  hashMap[77]("\"",".-..-.");
  hashMap[78]("$","...-..-");
  hashMap[79]("@",".--.-.");
  hashMap[80]("End of work","...-.-");
  hashMap[81]("Error","........");
  hashMap[82]("Invitation to Transmit","-.-");
  hashMap[83]("Starting Signal","-.-.-");
  hashMap[84]("New Page Signal",".-.-.");
  hashMap[85]("Understood","...-.");
  hashMap[86]("Wait",".-...");
  //end of hashmap initilization

  //random math temp variables 
  int total = 1000;
  float sum = 0;
  double avg;
  float ranArr[1000];

 

    //sets the random number generator with a seed which is my class passwrd
    srand(335963);
    //defines an array with 0 to 1000 random numbers
    int i;
    for(i=0; i<1000; i++){
        ranArr[i] = rand() % 1000+1;
        sum = ranArr[i] + sum;

    }
    
    avg = sum/total;
    float variance=0;
    variance = var_compute(ranArr, avg)/1000;
 
     
    double stdDeviation=0;
    stdDeviation = stdDev_compute(variance);

  //white led intilization for pinmode
  pinMode( red_light_pin, OUTPUT ) ;
  pinMode( green_light_pin, OUTPUT ) ;
  pinMode( blue_light_pin, OUTPUT );
  
  //search the morse hash . table: and emit Starting Signal 
  Serial.print(("Starting Signal"));
  morseTranslator_emit(hashMap.getValueOf("Starting Signal"));
  
   //Utd netid jag150730
   char* netid[] = {"j","a","g","1","5","0","7","3","0"};
   //search the hash table one char at a time to emit netid jag150730 
  for(int i=0;i<9;i++){
    Serial.print(netid[i]);
    morseTranslator_emit(hashMap.getValueOf(netid[i]));
  }


  ///parse the average:****.** deviation:****.** SHA1:D350551C3BF14F72DD3A9279FECA24F359B2AAB9
  char *arr[] = {"a","v","e","r","a","g","e",":","0","5","0","1",".","1","7"," ","d","e","v","i","a","t","i","o","n",":","0","2","9","5",".","2","9"," ","S","H","A","1",":","D","3","5","0","5","5","1","C","3","B","F","1","4","F","7","2","D","D","3","A","9","2","7","9","F","E","C","A","2","4","F","3","5","9","B","2","A","A","B","9"};
  
  for(int i=0;i<79;i++) {
    Serial.print(arr[i]);
     morseTranslator_emit(hashMap.getValueOf(arr[i]));
     
  }
  Serial.print("End of work");
  morseTranslator_emit(hashMap.getValueOf("End of work"));

  Serial.print("Understood");
  morseTranslator_emit(hashMap.getValueOf("Understood"));
 Serial.flush();

 
}

void loop() {
  // put your main code here, to run repeatedly:

}
