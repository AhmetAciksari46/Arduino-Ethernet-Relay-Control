#include <SPI.h> 
#include <Ethernet.h>
//rolelerin sinyal pini ile arduinonun 20. dijital pini arasında bağlantı kurulduğu tanımlanır.
#define role01 20 
#define role16 36
//kullanılacak role sayısı kadar tanımlama yapılmalıdır. byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; byte ip[] = { 192, 168, 1, 178 };
byte gateway[] = { 192, 168, 1, 1 };
byte subnet[] = { 255, 255, 255, 0 }; 
EthernetServer server(80);
String readString; 

void setup() {
Serial.begin(9600); 
while (!Serial) 
{
;	
}
pinMode(role01,OUTPUT); //role01 olarak tanımlananın çıkış olduğu belirtilir. 
pinMode(role16,OUTPUT);
//kullanılan rölelerin hepsi için yukardaki komut uygulanmalıdır. 
Ethernet.begin(mac, ip, gateway, subnet);
server.begin(); 
Serial.print("server is at "); 
Serial.println(Ethernet.localIP());
}
void loop() 
{
EthernetClient client = server.available(); 
if (client) {
while (client.connected()) 
{ 
  if (client.available()) 
  {
char  c  = client.read();
if (readString.length() < 100) 
{ 
  readString += c;
}
if  (c  ==  '\n')  
{ 
  Serial.println(readString); 
  client.println("HTTP/1.1 200 OK"); 
  client.println("Content-Type: text/html"); 
  client.println();  
  client.println("<HTML>"); 
  client.println("<HEAD>");
client.println("<meta	name='apple-mobile-web-app-capable' content='yes' />");
client.println("<meta name='apple-mobile-web-app-status-bar-sty- le' content='black-translucent' />");
client.println("<link	rel='stylesheet'	type='text/css' href='http://randomnerdtutorials.com/ethernetcss.css' />");
client.println("<TITLE>Arduino Akilli Ev Uygulamasi</TITLE>"); // Türkçe karakter kullanılmamalıdır.
client.println("</HEAD>");//Temel HTMl sayfa oluşturma komutları client.println("<BODY>");
client.println("<hr />"); 
client.println("<br />");
client.println("<H2>Buton ile role kontrolu</H2>"); 
client.println("<br />");
client.println("<a href=\"/?1on\"\">Salon Isigini Ac</a>"); //a href yönlendirme komutudur.
//üzerinde "Salon Isigini Ac" yazan bir buton oluşturuldu.
//192.168.1.178 kısmının devamında/?1on url si verildi. eğer direk bu urlye gidilirse, buton için tanımlanan işlem çalıştırılır.
 
client.println("<a href=\"/?1off\"\">Salon Isigini Kapat</a><br />"); client.println("<br />");
//eklenilecek röle sayısı kadar buraya aşağıdaki komutlar eklenmelidir ve /?16on ve off kısımlar isimleri ile birlikte değiştirilmelidir. client.println("<br />");
client.println("<a href=\"/?16on\"\">Salon Prizini Ac</a>"); 
client.println("<a href=\"/?16off\"\">Salon Prizini Kapat</a><br />");
client.println("<br />");
//buraya kadar olan komutlar
client.println("</BODY>"); 
client.println("</HTML>"); 
delay(1);
client.stop();
if (readString.indexOf("?1on") >0)
{ //eğer /?1on sayfası çağrılırsa 
digitalWrite(role01, HIGH); // role01'i aktif hale getir.
}
if (readString.indexOf("?1off")  >0)
{ 
  digitalWrite(role01, LOW); //role01 pasif hale getir.
}
//buraya kullanılacak röle sayısı kadar alt kısımdaki komutlar eklenmelidir. if (readString.indexOf("?16on") >0){
digitalWrite(role16, HIGH);	
} 
if (readString.indexOf("?16off") >0)
{
digitalWrite(role16, LOW);	
}
//buraya kadar
readString="";
}
}
}
}
}

