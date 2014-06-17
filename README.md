Spark Core TTS Sample using Emic2 Text-to-Speech Module
-------------------------------------------------------

Here is a project using [Emic2 Text-to-Speech Module][1] and Spark Core. Emic2 is simple to use TTS module. It has all the features of a common TTS engine. We change the volume, pitch, language, etc... Also we can have 8 different voice. We can program the Emic2 using Serial. We just want to send some text to the board using Serial and the board will say it. I have used [Dan Malec][2]'s Emic2TtsModule library from [SocialChatter][3] application and ported to Spark Core (this was a very simple port).

This sample has two different applications, the Spark Core app and the Web App to access the Emic2 TTS Module. The Spark Core application exposes different method to speak, change properties, etc... The Web App calls these methods to access the Emic2. 

**Wiring**

 1. Emic2 5V to 5V 
 2. Emic2 GND to GND 
 3. Emic2 SIN to Tx 
 4. Emic2 SOUT to Rx

**Screenshots**
![enter image description here][4]

![enter image description here][5]


  [1]: http://www.parallax.com/product/30016
  [2]: https://github.com/dmalec
  [3]: https://github.com/dmalec/SocialChatter
  [4]: https://raw.githubusercontent.com/krvarma/TTS_SparkCore/master/project.jpg
  [5]: https://raw.githubusercontent.com/krvarma/TTS_SparkCore/master/web.jpg