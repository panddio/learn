<map version="0.9.0">
<!-- To view this file, download free mind mapping software FreeMind from http://freemind.sourceforge.net -->
<node CREATED="1521774756718" ID="ID_1077959053" MODIFIED="1521774880071">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      UART&#39537;&#21160;&#26694;&#26550;&#20998;&#26512;
    </p>
  </body>
</html>
</richcontent>
<font NAME="SansSerif" SIZE="20"/>
<node CREATED="1521774842550" ID="ID_1518020516" MODIFIED="1521774903990" POSITION="right" TEXT="&#x6570;&#x636e;&#x7ed3;&#x6784;">
<node CREATED="1521774908570" FOLDED="true" ID="ID_119780450" MODIFIED="1521776231678">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      struct uart_driver: &#20195;&#34920;&#19968;&#20010;uart&#39537;&#21160;&#31243;&#24207;
    </p>
  </body>
</html>
</richcontent>
<node CREATED="1521775833158" ID="ID_1455784472" MODIFIED="1521775847869">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      struct module *owner;/* &#25317;&#26377;&#35813;uart_driver&#30340;&#27169;&#22359;,&#19968;&#33324;&#20026;THIS_MODULE */
    </p>
    <p>
      constchar*driver_name;/* &#20018;&#21475;&#39537;&#21160;&#21517;&#65292;&#20018;&#21475;&#35774;&#22791;&#25991;&#20214;&#21517;&#20197;&#39537;&#21160;&#21517;&#20026;&#22522;&#30784; */
    </p>
    <p>
      constchar*dev_name;/* &#20018;&#21475;&#35774;&#22791;&#21517; */
    </p>
    <p>
      int major;/* &#20027;&#35774;&#22791;&#21495; */
    </p>
    <p>
      int minor;/* &#27425;&#35774;&#22791;&#21495; */
    </p>
    <p>
      int nr;/* &#35813;uart_driver&#25903;&#25345;&#30340;&#20018;&#21475;&#20010;&#25968;(&#26368;&#22823;) */
    </p>
    <p>
      struct console *cons;/* &#20854;&#23545;&#24212;&#30340;console.&#33509;&#35813;uart_driver&#25903;&#25345;serial console,&#21542;&#21017;&#20026;NULL */
    </p>
    <p>
      
    </p>
    <p>
      /*
    </p>
    <p>
      * these are private; the low level driver should not
    </p>
    <p>
      * touch these; they should be initialised to NULL
    </p>
    <p>
      */
    </p>
    <p>
      struct uart_state *state;
    </p>
    <p>
      struct tty_driver *tty_driver;&#160;&#160;&#160;
    </p>
  </body>
</html>
</richcontent>
</node>
</node>
<node CREATED="1521775828859" ID="ID_787037340" MODIFIED="1521775959579" TEXT="struct uart_state"/>
<node CREATED="1521774909138" ID="ID_1315267797" MODIFIED="1521775978973" TEXT="struct uart_port"/>
<node CREATED="1521774909698" ID="ID_1779830960" MODIFIED="1521775993394" TEXT="struct tty_driver"/>
</node>
<node CREATED="1521774845506" ID="ID_1029008316" MODIFIED="1521774845506" POSITION="right" TEXT=""/>
<node CREATED="1521774846154" ID="ID_806888346" MODIFIED="1521774846154" POSITION="right" TEXT=""/>
<node CREATED="1521774846771" ID="ID_1473181649" MODIFIED="1521774846771" POSITION="right" TEXT=""/>
<node CREATED="1521774847738" ID="ID_227618291" MODIFIED="1521774847738" POSITION="right" TEXT=""/>
</node>
</map>
