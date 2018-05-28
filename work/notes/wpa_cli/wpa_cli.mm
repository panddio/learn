<map version="0.9.0">
<!-- To view this file, download free mind mapping software FreeMind from http://freemind.sourceforge.net -->
<node CREATED="1509517075615" ID="ID_1482751523" MODIFIED="1509680290452" TEXT="wpa_cli">
<font BOLD="true" ITALIC="true" NAME="SansSerif" SIZE="28"/>
<node CREATED="1509607423285" ID="ID_540898265" MODIFIED="1509680363658" POSITION="right" TEXT="&#x91cd;&#x8981;&#x6570;&#x636e;&#x7ed3;&#x6784;&#x89e3;&#x8bfb;">
<font BOLD="true" ITALIC="true" NAME="SansSerif" SIZE="18"/>
<node CREATED="1509517145999" FOLDED="true" ID="ID_1427946013" MODIFIED="1515572798081">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      struct <font color="#1327de">eloop_data</font>&#160;{
    </p>
    <p>
      <font color="#110d0d">&#160;&#160;&#160;&#160;int max_sock; </font>
    </p>
    <p>
      <font color="#110d0d">&#160;&#160;&#160;&#160;int count; /* sum of all table counts */</font>
    </p>
    <p>
      
    </p>
    <p>
      #ifdef CONFIG_ELOOP_POLL
    </p>
    <p>
      &#160;&#160;&#160;&#160;int max_pollfd_map; /* number of pollfds_map currently allocated */
    </p>
    <p>
      &#160;&#160;&#160;&#160;int max_poll_fds; /* number of pollfds currently allocated */
    </p>
    <p>
      &#160;&#160;&#160;&#160;struct pollfd *pollfds;
    </p>
    <p>
      &#160;&#160;&#160;&#160;struct pollfd **pollfds_map;
    </p>
    <p>
      #endif /* CONFIG_ELOOP_POLL */
    </p>
    <p>
      #if defined(CONFIG_ELOOP_EPOLL) || defined(CONFIG_ELOOP_KQUEUE)
    </p>
    <p>
      &#160;&#160;&#160;&#160;int max_fd;
    </p>
    <p>
      &#160;&#160;&#160;&#160;struct eloop_sock *fd_table;
    </p>
    <p>
      #endif /* CONFIG_ELOOP_EPOLL || CONFIG_ELOOP_KQUEUE */
    </p>
    <p>
      #ifdef CONFIG_ELOOP_EPOLL
    </p>
    <p>
      &#160;&#160;&#160;&#160;int epollfd;
    </p>
    <p>
      &#160;&#160;&#160;&#160;int epoll_max_event_num;
    </p>
    <p>
      &#160;&#160;&#160;&#160;struct epoll_event *epoll_events;
    </p>
    <p>
      #endif /* CONFIG_ELOOP_EPOLL */
    </p>
    <p>
      #ifdef CONFIG_ELOOP_KQUEUE
    </p>
    <p>
      &#160;&#160;&#160;&#160;int kqueuefd;
    </p>
    <p>
      &#160;&#160;&#160;&#160;int kqueue_nevents;
    </p>
    <p>
      &#160;&#160;&#160;&#160;struct kevent *kqueue_events;
    </p>
    <p>
      #endif /* CONFIG_ELOOP_KQUEUE */
    </p>
    <p>
      
    </p>
    <p>
      <font color="#bf1313">&#160;&#160;&#160;&#160;struct eloop_sock_table readers; </font>
    </p>
    <p>
      <font color="#bf1313">&#160;&#160;&#160;&#160;struct eloop_sock_table writers; </font>
    </p>
    <p>
      <font color="#bf1313">&#160;&#160;&#160;&#160;struct eloop_sock_table exceptions; </font>
    </p>
    <p>
      
    </p>
    <p>
      <font color="#bf1313">&#160;&#160;&#160;&#160;struct dl_list timeout; </font>
    </p>
    <p>
      
    </p>
    <p>
      <font color="#132abf">&#160;&#160;&#160;&#160;int signal_count; </font>
    </p>
    <p>
      <font color="#132abf">&#160;&#160;&#160;&#160;struct eloop_signal *signals; </font>
    </p>
    <p>
      <font color="#132abf">&#160;&#160;&#160;&#160;int signaled; </font>
    </p>
    <p>
      <font color="#132abf">&#160;&#160;&#160;&#160;int pending_terminate; </font>
    </p>
    <p>
      
    </p>
    <p>
      <font color="#bf1313">&#160;&#160;&#160;&#160;int terminate;</font>
    </p>
    <p>
      }
    </p>
  </body>
</html></richcontent>
<node CREATED="1509517286159" FOLDED="true" ID="ID_1844811191" MODIFIED="1515572796953">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      struct <font color="#0f0fe4">eloop_sock_table</font>&#160;{
    </p>
    <p>
      &#160;&#160;&#160;&#160;int count;
    </p>
    <p>
      &#160;&#160;&#160;&#160;struct eloop_sock *table;
    </p>
    <p>
      &#160;&#160;&#160;&#160;eloop_event_type type;
    </p>
    <p>
      &#160;&#160;&#160;&#160;int changed;
    </p>
    <p>
      }
    </p>
  </body>
</html></richcontent>
<node CREATED="1509517393951" FOLDED="true" ID="ID_1781022412" MODIFIED="1515572796017">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      struct <font color="#1b1cdf">eloop_sock</font>&#160;{
    </p>
    <p>
      &#160;&#160;&#160;&#160;int sock;
    </p>
    <p>
      &#160;&#160;&#160;&#160;void *eloop_data;
    </p>
    <p>
      &#160;&#160;&#160;&#160;void *user_data;
    </p>
    <p>
      &#160;&#160;&#160;&#160;eloop_sock_handler handler;
    </p>
    <p>
      <font color="#d10909">&#160;&#160;&#160;&#160;/** </font>
    </p>
    <p>
      <font color="#d10909">&#160;&#160;&#160;&#160;&#160;* &#30001;&#20110;WPA_TRACE&#27809;&#26377;&#23450;&#20041;, &#20197;&#19979;&#23439;&#23637;&#24320;&#20026;&#31354; </font>
    </p>
    <p>
      <font color="#d10909">&#160;&#160;&#160;&#160;&#160;*/ </font>
    </p>
    <p>
      <font color="#d10909">&#160;&#160;&#160;&#160;WPA_TRACE_REF(eloop); </font>
    </p>
    <p>
      <font color="#d10909">&#160;&#160;&#160;&#160;WPA_TRACE_REF(user); </font>
    </p>
    <p>
      <font color="#d10909">&#160;&#160;&#160;&#160;WPA_TRACE_INFO</font>
    </p>
    <p>
      }
    </p>
  </body>
</html></richcontent>
<node CREATED="1509518053672" ID="ID_1364764252" MODIFIED="1509518056824" TEXT="WPA_TRACE_LEN 16"/>
<node CREATED="1509616526479" ID="ID_1037661243" MODIFIED="1509679937867">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      <font color="#e21919">/** </font>
    </p>
    <p>
      <font color="#e21919">&#160;&#160;* WPA_TRACE &#27809;&#26377;&#23450;&#20041; </font>
    </p>
    <p>
      <font color="#e21919">&#160;&#160;*/</font>
    </p>
    <p>
      #ifdef WPA_TRACE
    </p>
    <p>
      
    </p>
    <p>
      #define WPA_TRACE_INFO void *btrace[WPA_TRACE_LEN]; int btrace_num;
    </p>
    <p>
      struct wpa_trace_ref {
    </p>
    <p>
      &#160;&#160;&#160;&#160;struct dl_list list;
    </p>
    <p>
      &#160;&#160;&#160;&#160;const void *addr;
    </p>
    <p>
      &#160;&#160;&#160;&#160;WPA_TRACE_INFO
    </p>
    <p>
      };
    </p>
    <p>
      #define WPA_TRACE_REF(name) struct wpa_trace_ref wpa_trace_ref_##name
    </p>
    <p>
      /**
    </p>
    <p>
      &#160;&#160;* &#27492;&#22788;&#30465;&#30053;&#25481;&#22914; #define wpa_trace_dump(title, ptr) &#30340;&#23450;&#20041;
    </p>
    <p>
      &#160;&#160;*/
    </p>
    <p>
      
    </p>
    <p>
      #else /* WPA_TRACE */
    </p>
    <p>
      
    </p>
    <p>
      <font color="#ca1414">#define WPA_TRACE_INFO </font>
    </p>
    <p>
      <font color="#ca1414">#define WPA_TRACE_REF(n)</font>
    </p>
    <p>
      #define wpa_trace_dump(title, ptr) do { } while (0)
    </p>
    <p>
      #define wpa_trace_record(ptr) do { } while (0)
    </p>
    <p>
      #define wpa_trace_show(title) do { } while (0)
    </p>
    <p>
      #define wpa_trace_add_ref(ptr, name, addr) do { } while (0)
    </p>
    <p>
      #define wpa_trace_remove_ref(ptr, name, addr) do { } while (0)
    </p>
    <p>
      #define wpa_trace_check_ref(addr) do { } while (0)
    </p>
    <p>
      
    </p>
    <p>
      #endif /* WPA_TRACE */
    </p>
  </body>
</html></richcontent>
</node>
</node>
<node CREATED="1509680033194" ID="ID_1399362844" MODIFIED="1509680046427">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      /**
    </p>
    <p>
      &#160;* eloop_event_type - eloop socket event type for eloop_register_sock()
    </p>
    <p>
      &#160;* @EVENT_TYPE_READ: Socket has data available for reading
    </p>
    <p>
      &#160;* @EVENT_TYPE_WRITE: Socket has room for new data to be written
    </p>
    <p>
      &#160;* @EVENT_TYPE_EXCEPTION: An exception has been reported
    </p>
    <p>
      &#160;*/
    </p>
    <p>
      typedef enum {
    </p>
    <p>
      &#160;&#160;&#160;&#160;EVENT_TYPE_READ = 0,
    </p>
    <p>
      &#160;&#160;&#160;&#160;EVENT_TYPE_WRITE,
    </p>
    <p>
      &#160;&#160;&#160;&#160;EVENT_TYPE_EXCEPTION
    </p>
    <p>
      } eloop_event_type;
    </p>
  </body>
</html></richcontent>
</node>
</node>
<node CREATED="1509619464651" FOLDED="true" ID="ID_215881248" MODIFIED="1515572794256">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      struct <font color="#0e1fea">eloop_timeout</font>&#160;{
    </p>
    <p>
      &#160;&#160;&#160;&#160;struct dl_list list;
    </p>
    <p>
      &#160;&#160;&#160;&#160;struct os_reltime time;
    </p>
    <p>
      &#160;&#160;&#160;&#160;void *eloop_data;
    </p>
    <p>
      &#160;&#160;&#160;&#160;void *user_data;
    </p>
    <p>
      &#160;&#160;&#160;&#160;eloop_timeout_handler handler;
    </p>
    <p>
      <font color="#d70c0c">&#160;&#160;&#160;&#160;/** </font>
    </p>
    <p>
      <font color="#d70c0c">&#160;&#160;&#160;&#160;&#160;* &#30001;&#20110;WPA_TRACE&#27809;&#26377;&#23450;&#20041;, &#20197;&#19979;&#23439;&#23637;&#24320;&#20026;&#31354; </font>
    </p>
    <p>
      <font color="#d70c0c">&#160;&#160;&#160;&#160;&#160;*/ </font>
    </p>
    <p>
      <font color="#d70c0c">&#160;&#160;&#160;&#160;WPA_TRACE_REF(eloop); </font>
    </p>
    <p>
      <font color="#d70c0c">&#160;&#160;&#160;&#160;WPA_TRACE_REF(user); </font>
    </p>
    <p>
      <font color="#d70c0c">&#160;&#160;&#160;&#160;WPA_TRACE_INFO</font>
    </p>
    <p>
      };
    </p>
  </body>
</html></richcontent>
<node CREATED="1509619943763" ID="ID_104078762" MODIFIED="1509680558453">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      typedef long os_time_t;
    </p>
    <p>
      <font color="#e41717">/** </font>
    </p>
    <p>
      <font color="#e41717">&#160;* &#36825;&#20010;&#32467;&#26500;&#30456;&#24403;&#20110;struct timeval </font>
    </p>
    <p>
      <font color="#e41717">&#160;*/</font>
    </p>
    <p>
      struct os_reltime {
    </p>
    <p>
      &#160;&#160;&#160;&#160;os_time_t sec;
    </p>
    <p>
      &#160;&#160;&#160;&#160;os_time_t usec;
    </p>
    <p>
      };
    </p>
  </body>
</html></richcontent>
</node>
</node>
<node CREATED="1509518392082" ID="ID_516828847" MODIFIED="1509680534392">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      struct <font color="#0f19f1">dl_list</font>&#160;{
    </p>
    <p>
      &#160;&#160;&#160;&#160;struct dl_list *next;
    </p>
    <p>
      &#160;&#160;&#160;&#160;struct dl_list *prev;
    </p>
    <p>
      }
    </p>
  </body>
</html></richcontent>
</node>
<node CREATED="1509518439048" FOLDED="true" ID="ID_464419824" MODIFIED="1515572793640">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      struct <font color="#1c0ee5">eloop_signal</font>&#160;{
    </p>
    <p>
      &#160;&#160;&#160;&#160;int sig;
    </p>
    <p>
      &#160;&#160;&#160;&#160;void *user_data;
    </p>
    <p>
      &#160;&#160;&#160;&#160;eloop_signal_handler handler;
    </p>
    <p>
      &#160;&#160;&#160;&#160;int signaled;
    </p>
    <p>
      }
    </p>
  </body>
</html></richcontent>
<node CREATED="1509518505224" ID="ID_269669243" MODIFIED="1509518557770">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      /**
    </p>
    <p>
      &#160;* eloop_signal_handler - eloop signal event callback type
    </p>
    <p>
      &#160;* @sig: Signal number
    </p>
    <p>
      &#160;* @signal_ctx: Registered callback context data (user_data from
    </p>
    <p>
      &#160;* eloop_register_signal(), eloop_register_signal_terminate(), or
    </p>
    <p>
      &#160;* eloop_register_signal_reconfig() call)
    </p>
    <p>
      &#160;*/
    </p>
    <p>
      <font color="#ce0000">typedef void (*eloop_signal_handler)(int sig, void *signal_ctx);</font>
    </p>
  </body>
</html></richcontent>
</node>
</node>
</node>
<node CREATED="1509522127764" FOLDED="true" ID="ID_207368653" MODIFIED="1509619867029">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      struct <font color="#090ac5">wpa_ctrl</font>&#160;{
    </p>
    <p>
      #ifdef CONFIG_CTRL_IFACE_UDP
    </p>
    <p>
      &#160;&#160;&#160;&#160;int s;
    </p>
    <p>
      #ifdef CONFIG_CTRL_IFACE_UDP_IPV6
    </p>
    <p>
      &#160;&#160;&#160;&#160;struct sockaddr_in6 local;
    </p>
    <p>
      &#160;&#160;&#160;&#160;struct sockaddr_in6 dest;
    </p>
    <p>
      #else /* CONFIG_CTRL_IFACE_UDP_IPV6 */
    </p>
    <p>
      &#160;&#160;&#160;&#160;struct sockaddr_in local;
    </p>
    <p>
      &#160;&#160;&#160;&#160;struct sockaddr_in dest;
    </p>
    <p>
      #endif /* CONFIG_CTRL_IFACE_UDP_IPV6 */
    </p>
    <p>
      &#160;&#160;&#160;&#160;char *cookie;
    </p>
    <p>
      &#160;&#160;&#160;&#160;char *remote_ifname;
    </p>
    <p>
      &#160;&#160;&#160;&#160;char *remote_ip;
    </p>
    <p>
      #endif /* CONFIG_CTRL_IFACE_UDP */
    </p>
    <p>
      <font color="#d52222">#ifdef CONFIG_CTRL_IFACE_UNIX </font>
    </p>
    <p>
      <font color="#d52222">&#160;&#160;&#160;&#160;int s; </font>
    </p>
    <p>
      <font color="#d52222">&#160;&#160;&#160;&#160;struct sockaddr_un local; </font>
    </p>
    <p>
      <font color="#d52222">&#160;&#160;&#160;&#160;struct sockaddr_un dest; </font>
    </p>
    <p>
      <font color="#d52222">#endif /* CONFIG_CTRL_IFACE_UNIX */</font>
    </p>
    <p>
      #ifdef CONFIG_CTRL_IFACE_NAMED_PIPE
    </p>
    <p>
      &#160;&#160;&#160;&#160;HANDLE pipe;
    </p>
    <p>
      #endif /* CONFIG_CTRL_IFACE_NAMED_PIPE */
    </p>
    <p>
      }
    </p>
  </body>
</html></richcontent>
<node CREATED="1509522213676" FOLDED="true" ID="ID_1791580941" MODIFIED="1509608881375">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      struct sockaddr_un {
    </p>
    <p>
      &#160;&#160;&#160;&#160;sa_family_t sun_family; /*PF_UNIX&#25110;AF_UNIX */
    </p>
    <p>
      &#160;&#160;&#160;&#160;char sun_path[UNIX_PATH_MAX]; /* &#36335;&#24452;&#21517; */
    </p>
    <p>
      };
    </p>
  </body>
</html></richcontent>
<node CREATED="1509522853261" ID="ID_1103778924" MODIFIED="1509523835233">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      socket API&#21407;&#26412;&#26159;&#20026;&#32593;&#32476;&#36890;&#35759;&#35774;&#35745;&#30340;&#65292;&#20294;&#21518;&#26469;&#22312;socket&#30340;&#26694;&#26550;&#19978;&#21457;&#23637;&#20986;&#19968;&#31181;IPC&#26426;&#21046;&#65292;&#23601;&#26159;UNIX Domain Socket&#12290;&#34429;&#28982;&#32593;&#32476;socket&#20063;&#21487;&#29992;&#20110;&#21516;&#19968;&#21488;&#20027;&#26426;&#30340;&#36827;&#31243;&#38388;&#36890;&#35759;&#65288;&#36890;&#36807;loopback&#22320;&#22336;127.0.0.1&#65289;&#65292;&#20294;&#26159;UNIX Domain Socket&#29992;&#20110;IPC&#26356;&#26377;&#25928;&#29575;: &#19981;&#38656;&#35201;&#32463;&#36807;&#32593;&#32476;&#21327;&#35758;&#26632;&#65292;&#19981;&#38656;&#35201;&#25171;&#21253;&#25286;&#21253;&#12289;&#35745;&#31639;&#26657;&#39564;&#21644;&#12289;&#32500;&#25252;&#24207;&#21495;&#21644;&#24212;&#31572;&#31561;&#65292;&#21482;&#26159;&#23558;&#24212;&#29992;&#23618;&#25968;&#25454;&#20174;&#19968;&#20010;&#36827;&#31243;&#25335;&#36125;&#21040;&#21478;&#19968;&#20010;&#36827;&#31243;&#12290; &#36825;&#26159;&#22240;&#20026;&#65292;IPC&#26426;&#21046;&#26412;&#36136;&#19978;&#26159;&#21487;&#38752;&#30340;&#36890;&#35759;&#65292;&#32780;&#32593;&#32476;&#21327;&#35758;&#26159;&#20026;&#19981;&#21487;&#38752;&#30340;&#36890;&#35759;&#35774;&#35745;&#30340;&#12290;
    </p>
    <p>
      UNIX Domain Socket&#20063;&#25552;&#20379;&#38754;&#21521;&#27969;&#21644;&#38754;&#21521;&#25968;&#25454;&#21253;&#20004;&#31181;API&#25509;&#21475;&#65292;&#31867;&#20284;&#20110;TCP&#21644;UDP&#65292;&#20294;&#26159;&#38754;&#21521;&#28040;&#24687;&#30340;UNIX Domain Socket&#20063;&#26159;&#21487;&#38752;&#30340;&#65292;&#28040;&#24687;&#26082;&#19981;&#20250;&#20002;&#22833;&#20063;&#19981;&#20250;&#39034;&#24207;&#38169;&#20081;&#12290;
    </p>
    <p>
      
    </p>
    <p>
      UNIX Domain Socket&#26159;&#20840;&#21452;&#24037;&#30340;&#65292;API&#25509;&#21475;&#35821;&#20041;&#20016;&#23500;&#65292;&#30456;&#27604;&#20854;&#23427;IPC&#26426;&#21046;&#26377;&#26126;&#26174;&#30340;&#20248;&#36234;&#24615;&#65292;&#30446;&#21069;&#24050;&#25104;&#20026;&#20351;&#29992;&#26368;&#24191;&#27867;&#30340;IPC&#26426;&#21046;&#65292;&#27604;&#22914;X Window&#26381;&#21153;&#22120;&#21644;GUI&#31243;&#24207;&#20043;&#38388;&#23601;&#26159;&#36890;&#36807;UNIX Domain Socket&#36890;&#35759;&#30340;&#12290;
    </p>
    <p>
      
    </p>
    <p>
      &#20351; &#29992;UNIX Domain Socket&#30340;&#36807;&#31243;&#21644;&#32593;&#32476;socket&#21313;&#20998;&#30456;&#20284;&#65292;&#20063;&#35201;&#20808;&#35843;&#29992;socket()&#21019;&#24314;&#19968;&#20010;socket&#25991;&#20214;&#25551;&#36848;&#31526;&#65292;address family&#25351;&#23450;&#20026;AF_UNIX&#65292;type&#21487;&#20197;&#36873;&#25321;SOCK_DGRAM&#25110;SOCK_STREAM&#65292;protocol&#21442;&#25968;&#20173;&#28982;&#25351;&#23450;&#20026;0&#21363;&#21487;&#12290;
    </p>
    <p>
      
    </p>
    <p>
      UNIX Domain Socket&#19982;&#32593;&#32476;socket&#32534;&#31243;&#26368;&#26126;&#26174;&#30340;&#19981;&#21516;&#22312;&#20110;&#22320;&#22336;&#26684;&#24335;&#19981;&#21516;&#65292;&#29992;&#32467;&#26500;&#20307;sockaddr_un&#34920;&#31034;&#65292;&#32593;&#32476;&#32534;&#31243;&#30340;socket&#22320;&#22336;&#26159;IP&#22320;&#22336;&#21152;&#31471;&#21475; &#21495;&#65292;&#32780;UNIX Domain Socket&#30340;&#22320;&#22336;&#26159;&#19968;&#20010;socket&#31867;&#22411;&#30340;&#25991;&#20214;&#22312;&#25991;&#20214;&#31995;&#32479;&#20013;&#30340;&#36335;&#24452;&#65292;&#36825;&#20010;socket&#25991;&#20214;&#30001;bind()&#35843;&#29992;&#21019;&#24314;&#65292;&#22914;&#26524;&#35843;&#29992;bind()&#26102;&#35813;&#25991;&#20214;&#24050;&#23384; &#22312;&#65292;&#21017;bind()&#38169;&#35823;&#36820;&#22238;
    </p>
  </body>
</html></richcontent>
</node>
<node CREATED="1509523908079" ID="ID_1989239388" MODIFIED="1509524002638" TEXT="&#x8fd9;&#x4e2a;&#x7ed3;&#x6784;&#x4f53;&#x662f;&#x7528;&#x6765;&#x672c;&#x5730;&#x8fdb;&#x7a0b;&#x95f4;&#x901a;&#x4fe1;&#x7528;&#x7684;&#xff0c;&#x5e76;&#x4e0d;&#x662f;tcp/ip&#x901a;&#x4fe1;&#xff0c;&#x867d;&#x7136;&#x4ee3;&#x7801;&#x6a21;&#x5f0f;&#x4e0a;&#x5f88;&#x76f8;&#x4f3c;&#xff0c;&#x51c6;&#x786e;&#x7684;&#x8bf4;&#x662f;unix Domain &#x7684;&#x901a;&#x4fe1;&#xff0c;&#x4e8c;&#x8005;&#x6709;&#x672c;&#x8d28;&#x4e0a;&#x7684;&#x533a;&#x522b;&#xff0c;&#x90a3;&#x4e2a;sun_path&#x6210;&#x5458;&#x4e5f;&#x5c31;&#x662f;&#x62c5;&#x4efb;&#x8fd9;&#x4e2a;domain&#xff08;&#x57df;&#xff09;&#x7684;&#x89d2;&#x8272;&#x4e86;&#xff0c;&#x6bd4;&#x5982;&#x5b58;&#x50a8;&#x201c;/tmp/mydomain&#x201d;&#x8fd9;&#x6837;&#x7684;&#x4e1c;&#x897f;&#xff0c;&#x518d;&#x6bd4;&#x5982;A&#x548c;B&#x4e4b;&#x95f4;&#x901a;&#x4fe1;&#xff0c;A&#x5e94;&#x8be5;&#x6709;&#x4e00;&#x4e2a;&#x7c7b;&#x4f3c;&quot;/tmp/A&quot;&#xff08;&#x540d;&#x5b57;&#x53ef;&#x4ee5;&#x81ea;&#x5df1;&#x968f;&#x610f;&#x8d77;&#xff09;&#x7684;&#x57df;&#xff0c;B&#x5e94;&#x8be5;&#x6709;&#x4e00;&#x4e2a;&#x7c7b;&#x4f3c;&quot;/tmp/B&quot;&#x7684;&#x57df;&#xff0c;&#x901a;&#x4fe1;&#x65f6;&#x5206;&#x522b;&#x5411;&#x5bf9;&#x65b9;&#x7684;&#x57df;&#x53d1;&#x9001;&#x6d88;&#x606f;&#xff0c;&#x4ece;&#x81ea;&#x5df1;&#x7684;&#x57df;&#x63a5;&#x53d7;&#x6d88;&#x606f;"/>
</node>
</node>
<node CREATED="1509587656527" FOLDED="true" ID="ID_359234295" MODIFIED="1515572791888">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      sruct <font color="#1314e8">wpa_cli_cmd</font>&#160;{
    </p>
    <p>
      &#160;&#160;&#160;&#160;const char *cmd; //&#21629;&#20196;&#21517;&#31216;&#65292;&#22914; status &#31561;&#31561;
    </p>
    <p>
      &#160;&#160;&#160;&#160;int (*handler)(struct wpa_ctrl *ctrl, int argc, char *argv[]); //&#21629;&#20196;&#30340; handler &#20989;&#25968;
    </p>
    <p>
      &#160;&#160;&#160;&#160;char ** (*completion)(const char *str, int pos);
    </p>
    <p>
      &#160;&#160;&#160;&#160;<font color="#c80202">enum wpa_cli_cmd_flags&#160;flags;</font>
    </p>
    <p>
      &#160;&#160;&#160;&#160;const char *usage;
    </p>
    <p>
      }
    </p>
  </body>
</html></richcontent>
<node CREATED="1509594400191" ID="ID_1465767776" MODIFIED="1509594484671">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      enum wpa_cli_cmd_flags {
    </p>
    <p>
      &#160;&#160;&#160;&#160;cli_cmd_flag_none&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;= 0x00,
    </p>
    <p>
      &#160;&#160;&#160;&#160;cli_cmd_flag_sensitive&#160;&#160;= 0x01,
    </p>
    <p>
      }
    </p>
  </body>
</html></richcontent>
</node>
</node>
</node>
<node CREATED="1509538612525" ID="ID_681694974" MODIFIED="1509680376127" POSITION="right" TEXT="&#x4ea4;&#x4e92;&#x6a21;&#x5f0f;&#x4ee3;&#x7801;&#x6d41;&#x7a0b;">
<font BOLD="true" ITALIC="true" NAME="SansSerif" SIZE="18"/>
<node CREATED="1509617036528" ID="ID_687950859" MODIFIED="1509680407354" TEXT="&#x8bf4;&#x660e;: &#x6b64;&#x6a21;&#x5f0f;&#x76f4;&#x63a5;&#x8fd0;&#x884c;wpa_cli&#x8fdb;&#x5165;&#x4ea4;&#x4e92;&#x6a21;&#x5f0f;, wpa_cli&#x7b49;&#x5f85;&#x547d;&#x4ee4;&#x8f93;&#x5165;&#x5e76;&#x6267;&#x884c;">
<font NAME="SansSerif" SIZE="16"/>
</node>
<node CREATED="1509617044682" ID="ID_1050219264" MODIFIED="1515572731067" TEXT="int main(int argc, char *argv[])">
<font NAME="SansSerif" SIZE="16"/>
<node CREATED="1509617203704" ID="ID_1062063982" MODIFIED="1509617745714">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      <font color="#c41313">/** </font>
    </p>
    <p>
      <font color="#c41313">&#160;&#160;* &#19981;&#24102;&#21442;&#25968;&#30452;&#25509;&#36816;&#34892;wpa_cli, </font>
    </p>
    <p>
      <font color="#c41313">&#160;&#160;* argc=optind=1, action_file=NULL, &#24471;interactive=1 </font>
    </p>
    <p>
      <font color="#c41313">&#160;&#160;*/</font>
    </p>
    <p>
      interactive = (argc == optind) &amp;&amp; (action_file == NULL);
    </p>
    <p>
      if (interactive)
    </p>
    <p>
      &#160;&#160;&#160;&#160;printf(&quot;%s\n\n%s\n\n&quot;, wpa_cli_version, cli_license);
    </p>
  </body>
</html></richcontent>
</node>
<node CREATED="1509519063017" FOLDED="true" ID="ID_764015522" MODIFIED="1515572516744">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      <font color="#dd1212">eloop_init</font>();
    </p>
  </body>
</html></richcontent>
<node CREATED="1509519115049" ID="ID_1850570350" MODIFIED="1509673189932">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      int eloop_init(void)
    </p>
    <p>
      {&#160;&#160;&#160;
    </p>
    <p>
      <font color="#cf1010">&#160;&#160;&#160;&#160;os_memset(&amp;eloop, 0, sizeof(eloop));&#160;&#160;//&#28165;&#38646; struct eloop_data</font>
    </p>
    <p>
      <font color="#cf1010">&#160;&#160;&#160;&#160;dl_list_init(&amp;eloop.timeout); //&#21021;&#22987;&#21270;list</font>
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;/**
    </p>
    <p>
      &#160;&#160;&#160;&#160;* &#20197;&#19979;&#23439;&#37117;&#27809;&#26377;&#23450;&#20041;, &#36825;&#27573;&#20195;&#30721;&#19981;&#25191;&#34892;
    </p>
    <p>
      &#160;&#160;&#160;&#160;*/
    </p>
    <p>
      #ifdef CONFIG_ELOOP_EPOLL
    </p>
    <p>
      &#160;&#160;&#160;&#160;eloop.epollfd = epoll_create1(0);
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (eloop.epollfd &lt; 0) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;wpa_printf(MSG_ERROR, &quot;%s: epoll_create1 failed. %s&quot;,
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;__func__, strerror(errno));
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;return -1;
    </p>
    <p>
      &#160;&#160;&#160;&#160;}
    </p>
    <p>
      #endif /* CONFIG_ELOOP_EPOLL */
    </p>
    <p>
      #ifdef CONFIG_ELOOP_KQUEUE
    </p>
    <p>
      &#160;&#160;&#160;&#160;eloop.kqueuefd = kqueue();
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (eloop.kqueuefd &lt; 0) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;wpa_printf(MSG_ERROR, &quot;%s: kqueue failed: %s&quot;,
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;__func__, strerror(errno));
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;return -1;
    </p>
    <p>
      &#160;&#160;&#160;&#160;}
    </p>
    <p>
      #endif /* CONFIG_ELOOP_KQUEUE */
    </p>
    <p>
      #if defined(CONFIG_ELOOP_EPOLL) || defined(CONFIG_ELOOP_KQUEUE)
    </p>
    <p>
      &#160;&#160;&#160;&#160;eloop.readers.type = EVENT_TYPE_READ;
    </p>
    <p>
      &#160;&#160;&#160;&#160;eloop.writers.type = EVENT_TYPE_WRITE;
    </p>
    <p>
      &#160;&#160;&#160;&#160;eloop.exceptions.type = EVENT_TYPE_EXCEPTION;
    </p>
    <p>
      #endif /* CONFIG_ELOOP_EPOLL || CONFIG_ELOOP_KQUEUE */
    </p>
    <p>
      #ifdef WPA_TRACE
    </p>
    <p>
      &#160;&#160;&#160;&#160;signal(SIGSEGV, eloop_sigsegv_handler);
    </p>
    <p>
      #endif /* WPA_TRACE */
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;<font color="#000000">&#160;return 0;</font>
    </p>
    <p>
      }
    </p>
  </body>
</html></richcontent>
</node>
</node>
<node CREATED="1509519259177" FOLDED="true" ID="ID_591542895" MODIFIED="1515572514336">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      <font color="#c20808">eloop_register_signal_terminate </font>(wpa_cli_terminate, NULL);
    </p>
  </body>
</html></richcontent>
<node CREATED="1509519305715" FOLDED="true" ID="ID_1396994377" MODIFIED="1515572512632">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      wpa_cli_terminate(int sig, void *ctx)
    </p>
    <p>
      {
    </p>
    <p>
      &#160;&#160;&#160;&#160;eloop_terminate();
    </p>
    <p>
      }
    </p>
    <p>
      
    </p>
    <p>
      int eloop_register_signal_terminate(eloop_signal_handler handler,
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;void *user_data)
    </p>
    <p>
      {
    </p>
    <p>
      &#160;&#160;&#160;&#160;int ret = eloop_register_signal(<font color="#e60d0d">SIGINT</font>, handler, user_data); //&#27880;&#20876;<font color="#e60d0d">SIGINT&#20449;&#21495;&#30340;&#22788;&#29702;&#20989;&#25968;</font>
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (ret == 0)
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;ret = eloop_register_signal(<font color="#d41e1e">SIGTERM</font>, handler, user_data);
    </p>
    <p>
      &#160;&#160;&#160;&#160;return ret;
    </p>
    <p>
      }
    </p>
  </body>
</html></richcontent>
<node CREATED="1509614772149" ID="ID_3011897" MODIFIED="1509614792871">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      void eloop_terminate(void)
    </p>
    <p>
      {
    </p>
    <p>
      &#160;&#160;&#160;&#160;eloop.terminate = 1;
    </p>
    <p>
      }
    </p>
  </body>
</html></richcontent>
</node>
<node CREATED="1509519717770" ID="ID_117479831" MODIFIED="1509780833730">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      int <font color="#c60c0c">eloop_register_signa</font>l(int sig, eloop_signal_handler handler,
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;void *user_data)
    </p>
    <p>
      {
    </p>
    <p>
      &#160;&#160;&#160;&#160;struct eloop_signal *tmp;
    </p>
    <p>
      
    </p>
    <p>
      <font color="#c41616">&#160;&#160;&#160;&#160;/** </font>
    </p>
    <p>
      <font color="#c41616">&#160;&#160;&#160;&#160;&#160;* os_realloc_array&#20989;&#25968;&#20316;&#29992;&#35828;&#26126; </font>
    </p>
    <p>
      <font color="#c41616">&#160;&#160;&#160;&#160;&#160;* 1.&#22914;&#26524;eloop.signals &#65281;= NULL&#65292; &#37322;&#25918;eloop.signals&#25351;&#21521;&#30340;&#20869;&#23384;&#31354;&#38388;&#65292; </font>
    </p>
    <p>
      <font color="#c41616">&#160;&#160;&#160;&#160;&#160;* 2.&#24182;&#25226;&#36825;&#27573;&#20869;&#23384;&#30340;&#20869;&#23481;&#22797;&#21046;&#21040;&#26032;&#30003;&#35831;&#30340;(eloop.signal_count + 1)*sizeof(struct eloop_signal)&#30340;&#20869;&#23384;&#31354;&#38388; </font>
    </p>
    <p>
      <font color="#c41616">&#160;&#160;&#160;&#160;&#160;*/</font>
    </p>
    <p>
      &#160;&#160;&#160;&#160;tmp = os_realloc_array(eloop.signals, eloop.signal_count + 1,
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;sizeof(struct eloop_signal));
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (tmp == NULL)
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;return -1;
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;tmp[eloop.signal_count].sig = sig;
    </p>
    <p>
      &#160;&#160;&#160;&#160;tmp[eloop.signal_count].user_data = user_data;
    </p>
    <p>
      &#160;&#160;&#160;&#160;tmp[eloop.signal_count].handler = handler;
    </p>
    <p>
      &#160;&#160;&#160;&#160;tmp[eloop.signal_count].signaled = 0;
    </p>
    <p>
      &#160;&#160;&#160;&#160;eloop.signal_count++;
    </p>
    <p>
      &#160;&#160;&#160;&#160;eloop.signals = tmp;
    </p>
    <p>
      &#160;&#160;&#160;&#160;signal(sig, <font color="#3e30e4">eloop_handle_signal</font>); //&#35774;&#32622;&#20449;&#21495;&#30340;&#22788;&#29702;&#20989;&#25968;<font color="#3e30e4">eloop_handle_signal</font>
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;return 0;
    </p>
    <p>
      }
    </p>
    <p>
      &#160;
    </p>
  </body>
</html></richcontent>
<node CREATED="1509676516862" ID="ID_982134641" MODIFIED="1509778967781">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      <font color="#d60808">/** </font>
    </p>
    <p>
      <font color="#d60808">&#160;&#160;* CONFIG_NATIVE_WINDOWS &#27809;&#26377;&#34987;&#23450;&#20041; </font>
    </p>
    <p>
      <font color="#d60808">&#160;&#160;*/</font>
    </p>
    <p>
      #ifndef CONFIG_NATIVE_WINDOWS
    </p>
    <p>
      static void eloop_handle_alarm(int sig)
    </p>
    <p>
      {
    </p>
    <p>
      &#160;&#160;&#160;&#160;wpa_printf(MSG_ERROR, &quot;eloop: could not process SIGINT or SIGTERM in &quot;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&quot;two seconds. Looks like there\n&quot;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&quot;is a bug that ends up in a busy loop that &quot;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&quot;prevents clean shutdown.\n&quot;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&quot;Killing program forcefully.\n&quot;);
    </p>
    <p>
      &#160;&#160;&#160;&#160;exit(1);
    </p>
    <p>
      }
    </p>
    <p>
      #endif /* CONFIG_NATIVE_WINDOWS */
    </p>
    <p>
      
    </p>
    <p>
      <font color="#d90202">/** </font>
    </p>
    <p>
      <font color="#d90202">&#160;* eloop_handle_signal()&#26159;SIGINT&#65288;Ctrl+c&#65289;&#25110;SIGTERM&#65288;kill&#65289;&#20449;&#21495;&#30340;&#22788;&#29702;&#20989;&#25968; </font>
    </p>
    <p>
      <font color="#d90202">&#160;*/</font>
    </p>
    <p>
      static void eloop_handle_signal(int sig)
    </p>
    <p>
      {
    </p>
    <p>
      &#160;&#160;&#160;&#160;int i;
    </p>
    <p>
      
    </p>
    <p>
      #ifndef CONFIG_NATIVE_WINDOWS
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;if ((sig == SIGINT || sig == SIGTERM) &amp;&amp; !eloop.pending_terminate) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;/* Use SIGALRM to break out from potential busy loops that
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;* would not allow the program to be killed. */
    </p>
    <p>
      <font color="#e10a0a">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;/** </font>
    </p>
    <p>
      <font color="#e10a0a">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;* wpa_cli &#39318;&#27425;&#25509;&#25910;&#21040;SIGINT&#65288;Ctrl+c&#65289;&#25110;SIGTERM&#65288;kill&#65289;&#20449;&#21495;: </font>
    </p>
    <p>
      <font color="#e10a0a">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;* 1.&#35774;&#32622;&#31561;&#24453;&#32456;&#27490;&#26465;&#20214; eloop.pending_terminate = 1, </font>
    </p>
    <p>
      <font color="#e10a0a">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;*&#160;&#160;&#160;&#160;&#36825;&#20010;&#26465;&#20214;&#23558;&#22312;&#22788;&#29702;eloop_run()&#20013;&#30340;&#24537;&#24490;&#29615;&#20013;&#26816;&#27979;&#24182;&#20570;&#36864;&#20986;&#21069;&#22788;&#29702; </font>
    </p>
    <p>
      <font color="#e10a0a">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;* 2.&#35774;&#32622;SIGALRM&#20449;&#21495;&#22788;&#29702;&#20989;&#25968; </font>
    </p>
    <p>
      <font color="#e10a0a">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;* 3.&#35843;&#29992;alarm()&#38393;&#38047;&#20989;&#25968;&#35774;&#32622;2&#31186;&#21518;&#37322;&#25918;SIGALRM&#20449;&#21495;&#12290;&#22914;&#26524;&#31561;&#24453;&#32456;&#27490;&#26465;&#20214; </font>
    </p>
    <p>
      <font color="#e10a0a">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;*&#160;&#160;&#160;&#160;&#160;&#22312;&#36825;2&#31186;&#20869;&#24471;&#21040;&#22788;&#29702;, alarm&#20250;&#34987;&#21462;&#28040;, &#31243;&#24207;&#27491;&#24120;&#36864;&#20986;&#65292;&#21542;&#21017;&#24378;&#21046;&#36864;&#20986; </font>
    </p>
    <p>
      <font color="#e10a0a">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;*/</font>
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;eloop.pending_terminate = 1;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;signal(SIGALRM, eloop_handle_alarm);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;alarm(2);
    </p>
    <p>
      &#160;&#160;&#160;&#160;}
    </p>
    <p>
      #endif /* CONFIG_NATIVE_WINDOWS */
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;eloop.signaled++;
    </p>
    <p>
      &#160;&#160;&#160;&#160;for (i = 0; i &lt; eloop.signal_count; i++) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;if (eloop.signals[i].sig == sig) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;eloop.signals[i].signaled++;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;break;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;}
    </p>
    <p>
      &#160;&#160;&#160;&#160;}
    </p>
    <p>
      }
    </p>
  </body>
</html></richcontent>
</node>
</node>
</node>
</node>
<node CREATED="1509520389970" FOLDED="true" ID="ID_669956404" MODIFIED="1515572736801">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      if (ctrl_ifname == NULL)
    </p>
    <p>
      &#160;&#160;&#160;&#160;//&#30001;&#27492;&#24471;ctrl_ifname=&quot;wlan0&quot;
    </p>
    <p>
      &#160;&#160;&#160;&#160;ctrl_ifname = <font color="#b80909">wpa_cli_get_default_ifname</font>();
    </p>
  </body>
</html></richcontent>
<node CREATED="1509520430826" ID="ID_907720174" MODIFIED="1509618330422">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      char * wpa_cli_get_default_ifname(void)
    </p>
    <p>
      {
    </p>
    <p>
      &#160;&#160;&#160; <font color="#c30f0f">char *ifname = NULL;</font>
    </p>
    <p>
      
    </p>
    <p>
      #ifdef CONFIG_CTRL_IFACE_UNIX
    </p>
    <p>
      <font color="#c41616">&#160;&#160;&#160;&#160;/** </font>
    </p>
    <p>
      <font color="#c41616">&#160;&#160;&#160;&#160;&#160;*&#160;&#160;&#27492;&#20195;&#30721;&#27573;&#30340;&#20316;&#29992;&#35828;&#26126;:</font>
    </p>
    <p>
      <font color="#c41616">&#160;&#160;&#160;&#160;&#160;*&#160;&#160;&#25171;&#24320;</font><font color="#da0000">/var/run/wpa_supplicant&#65292;&#26597;&#25214;&#27492;&#30446;&#24405;&#19979;&#38750;&quot;.&quot;&#25110;&quot;..&quot;&#30340;&#25991;&#20214;&#65292;</font>
    </p>
    <p>
      <font color="#c41616">&#160;&#160;&#160;&#160;&#160;*&#160; </font><font color="#da0000">&#28982;&#21518;&#20197;&#27492;&#25991;&#20214;&#21517;&#20316;&#20026;&#40664;&#35748;&#30340;i fname</font>
    </p>
    <p>
      <font color="#c41616">&#160;&#160;&#160;&#160;&#160;*/</font>
    </p>
    <p>
      <font color="#da0000">&#160;&#160;&#160;&#160;struct dirent *dent; </font>
    </p>
    <p>
      <font color="#da0000">&#160;&#160;&#160;&#160;DIR *dir = opendir(ctrl_iface_dir); //ctrl_iface_dir=&quot;/var/run/wpa_supplicant&quot; </font>
    </p>
    <p>
      <font color="#da0000">&#160;&#160;&#160;&#160;if (!dir) { </font>
    </p>
    <p>
      <font color="#da0000">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;return NULL; </font>
    </p>
    <p>
      <font color="#da0000">&#160;&#160;&#160;&#160;} </font>
    </p>
    <p>
      
    </p>
    <p>
      <font color="#da0000">&#160;&#160;&#160;&#160;while ((dent = readdir(dir))) {</font>
    </p>
    <p>
      #ifdef _DIRENT_HAVE_D_TYPE
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;/*
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;* Skip the file if it is not a socket. Also accept
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;* DT_UNKNOWN (0) in case the C library or underlying
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;* file system does not support d_type.
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;*/
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;if (dent-&gt;d_type != DT_SOCK &amp;&amp; dent-&gt;d_type != DT_UNKNOWN)
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;continue;
    </p>
    <p>
      #endif /* _DIRENT_HAVE_D_TYPE */
    </p>
    <p>
      <font color="#b01616">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;if (os_strcmp(dent-&gt;d_name, &quot;.&quot;) == 0 || </font>
    </p>
    <p>
      <font color="#b01616">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;os_strcmp(dent-&gt;d_name, &quot;..&quot;) == 0) </font>
    </p>
    <p>
      <font color="#b01616">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;continue; </font>
    </p>
    <p>
      <font color="#b01616">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;printf(&quot;Selected interface '%s'\n&quot;, dent-&gt;d_name); </font>
    </p>
    <p>
      <font color="#b01616">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;ifname = os_strdup(dent-&gt;d_name); </font>
    </p>
    <p>
      <font color="#b01616">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;break;</font>
    </p>
    <p>
      &#160;&#160;&#160;&#160;}
    </p>
    <p>
      &#160;&#160;&#160; <font color="#da1d1d">closedir(dir);</font>
    </p>
    <p>
      #endif /* CONFIG_CTRL_IFACE_UNIX */
    </p>
    <p>
      }
    </p>
  </body>
</html></richcontent>
</node>
</node>
<node CREATED="1509618396233" FOLDED="true" ID="ID_1004406525" MODIFIED="1515572788673">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      if (interactive) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;<font color="#ce0c0c">wpa_cli_interactive</font>();
    </p>
  </body>
</html></richcontent>
<node CREATED="1509618464361" FOLDED="true" ID="ID_1239028582" MODIFIED="1515572787089">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      static void wpa_cli_interactive(void)
    </p>
    <p>
      {
    </p>
    <p>
      &#160;&#160;&#160;&#160;printf(&quot;\nInteractive mode\n\n&quot;);
    </p>
    <p>
      
    </p>
    <p>
      <font color="#e10a0a">&#160;&#160;&#160;&#160;/** </font>
    </p>
    <p>
      <font color="#e10a0a">&#160;&#160;&#160;&#160;&#160;* &#27880;&#20876;&#36229;&#26102;&#22788;&#29702;, eloop_register_timeout()&#39318;&#27425;&#35843;&#29992; </font>
    </p>
    <p>
      <font color="#e10a0a">&#160;&#160;&#160;&#160;&#160;*/</font>
    </p>
    <p>
      &#160;&#160;&#160;&#160;<font color="#180e0e">eloop_register_timeout(0, 0, try_connection, NULL, NULL); </font>
    </p>
    <p>
      
    </p>
    <p>
      <font color="#d70303">&#160;&#160;&#160;&#160;/** </font>
    </p>
    <p>
      <font color="#d70303">&#160;&#160;&#160;&#160;&#160;* &#20132;&#20114;&#27169;&#24335;&#19979;&#22312;&#27492;&#20989;&#25968;&#20869;&#37096;&#36827;&#34892;&#24537;&#24490;&#29615;, &#30452;&#21040;wpa_cli&#25910;&#21040; </font>
    </p>
    <p>
      <font color="#d70303">&#160;&#160;&#160;&#160;&#160;* SIGINT&#65288;Ctrl+c&#65289;&#25110; SIGTERM&#65288;kill&#65289;&#20449;&#21495;, &#25110;&#36864;&#20986;&#21629;&#20196; </font>
    </p>
    <p>
      <font color="#d70303">&#160;&#160;&#160;&#160;&#160;*/</font>
    </p>
    <p>
      &#160;&#160;&#160;&#160;eloop_run();
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;eloop_cancel_timeout(try_connection, NULL, NULL);
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;cli_txt_list_flush(&amp;p2p_peers);
    </p>
    <p>
      &#160;&#160;&#160;&#160;cli_txt_list_flush(&amp;p2p_groups);
    </p>
    <p>
      &#160;&#160;&#160;&#160;cli_txt_list_flush(&amp;bsses);
    </p>
    <p>
      &#160;&#160;&#160;&#160;cli_txt_list_flush(&amp;ifnames);
    </p>
    <p>
      &#160;&#160;&#160;&#160;cli_txt_list_flush(&amp;networks);
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (edit_started)
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;edit_deinit(hfile, wpa_cli_edit_filter_history_cb);
    </p>
    <p>
      &#160;&#160;&#160;&#160;os_free(hfile);
    </p>
    <p>
      &#160;&#160;&#160;&#160;eloop_cancel_timeout(wpa_cli_ping, NULL, NULL);
    </p>
    <p>
      &#160;&#160;&#160;&#160;wpa_cli_close_connection();
    </p>
    <p>
      }
    </p>
  </body>
</html></richcontent>
<node CREATED="1509618692978" FOLDED="true" ID="ID_1125786286" MODIFIED="1515572783113">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      static void try_connection(void *eloop_ctx, void *timeout_ctx)
    </p>
    <p>
      {
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (ctrl_conn)
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;goto done;
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;/**
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;* &#33719;&#21462;&#40664;&#35748;&#30340;&#25509;&#21475;&#21517;&#31216;, &#22312;main()&#20989;&#25968;&#20013;&#24050;&#32463;&#33719;&#21462;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;*/
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (ctrl_ifname == NULL)
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;ctrl_ifname = wpa_cli_get_default_ifname();
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;/**
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;* &#35843;&#29992;wpa_cli_open_connection()&#20989;&#25968;&#25171;&#24320;&#36890;&#20449;socket
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;*/
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (wpa_cli_open_connection(ctrl_ifname, 1)) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;if (!warning_displayed) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;printf(&quot;Could not connect to wpa_supplicant: &quot;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&quot;%s - re-trying\n&quot;,
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;ctrl_ifname ? ctrl_ifname : &quot;(nil)&quot;);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;warning_displayed = 1;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;}
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;eloop_register_timeout(1, 0, try_connection, NULL, NULL);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;return;
    </p>
    <p>
      &#160;&#160;&#160;&#160;}
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;update_bssid_list(ctrl_conn);
    </p>
    <p>
      &#160;&#160;&#160;&#160;update_networks(ctrl_conn);
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (warning_displayed)
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;printf(&quot;Connection established.\n&quot;);
    </p>
    <p>
      
    </p>
    <p>
      done:
    </p>
    <p>
      &#160;&#160;&#160;&#160;start_edit();
    </p>
    <p>
      }
    </p>
  </body>
</html></richcontent>
<node CREATED="1509521239923" FOLDED="true" ID="ID_65462070" MODIFIED="1515572780976">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      int wpa_cli_open_connection(const char *ifname, int attach)
    </p>
    <p>
      {
    </p>
    <p>
      &#160;&#160;&#160;&#160;char *cfile = NULL;
    </p>
    <p>
      &#160;&#160;&#160;&#160;int flen, res;
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (ifname == NULL)
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;return -1;
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (client_socket_dir &amp;&amp; client_socket_dir[0] &amp;&amp;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;access(client_socket_dir, F_OK) &lt; 0) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;perror(client_socket_dir);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;os_free(cfile);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;return -1;
    </p>
    <p>
      &#160;&#160;&#160;&#160;}
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (cfile == NULL) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;flen = os_strlen(ctrl_iface_dir) + os_strlen(ifname) + 2; <font color="#1219ed">//&quot;/var/run/wpa_supplicant&quot;&quot;+&quot;wlan0&quot;+2</font>
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;cfile = os_malloc(flen);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;if (cfile == NULL)
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;return -1;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;res = os_snprintf(cfile, flen, &quot;%s/%s&quot;, ctrl_iface_dir, ifname); <font color="#1413ef">//cfile=&quot;/var/run/wpa_supplicant/wlan0&quot;</font>
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;if (os_snprintf_error(flen, res)) {&#160;&#160;//if(res &lt; 0 || res &gt;= flen) error
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;os_free(cfile);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;return -1;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;}
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;ctrl_conn = <font color="#cc0101">wpa_ctrl_open2(cfile, client_socket_dir); // client_socket_dir&#21021;&#22987;&#20540;&#20026;NULL</font>
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (ctrl_conn == NULL) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;os_free(cfile);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;return -1;
    </p>
    <p>
      &#160;&#160;&#160;&#160;}
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;/**
    </p>
    <p>
      &#160;&#160;&#160;&#160;* &#20132;&#20114;&#27169;&#24335;&#19979;attach&#21644;interactive&#37117;&#20026;&#30495;
    </p>
    <p>
      &#160;&#160;&#160;&#160;*/
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (attach &amp;&amp; interactive)
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;mon_conn = wpa_ctrl_open2(cfile, client_socket_dir);
    </p>
    <p>
      &#160;&#160;&#160;&#160;else
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160; <font color="#c50d0d">mon_conn = NULL;</font>
    </p>
    <p>
      &#160;&#160;&#160;&#160;os_free(cfile);
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (mon_conn) {
    </p>
    <p>
      <font color="#d71313">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;/** </font>
    </p>
    <p>
      <font color="#d71313">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;* &#21521;wpa_supplicant&#21457;&#36865;ATTACH&#35831;&#27714; </font>
    </p>
    <p>
      <font color="#d71313">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;*/</font>
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;if (wpa_ctrl_attach(mon_conn) == 0) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;wpa_cli_attached = 1;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;if (interactive)
    </p>
    <p>
      <font color="#da0d0d">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;/** </font>
    </p>
    <p>
      <font color="#da0d0d">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;* &#27880;&#20876;&#19968;&#20010;sock&#21040;eloop.readers&#38598;&#20013;, &#20851;&#32852;sockfd&#21644;&#23427;&#30340;handler&#20989;&#25968;&#12289;&#20256;&#32473;handler </font>
    </p>
    <p>
      <font color="#da0d0d">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;* &#20989;&#25968;&#30340;&#21442;&#25968;&#31561;, &#20851;&#32852;&#30340;&#26041;&#27861;&#26159;&#29992;&#23427;&#20204;&#21021;&#22987;&#21270;&#19968;&#20010;&#160;&#160;struct eloop_sock &#32467;&#26500;&#20307;&#12290;</font>
    </p>
    <p>
      <font color="#da0d0d">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;* &#36825;&#20010;eloop.readers&#38598;&#20013;&#30340;&#25551;&#36848;&#31526;&#23558;&#22312;eloop_run()&#20989;&#25968;&#20013;&#35843;&#29992;select()&#20989;&#25968;&#26469;&#30417;&#21548; </font>
    </p>
    <p>
      <font color="#da0d0d">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;*/</font>
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;<font color="#d80a0a">eloop_register_read_sock</font>(
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;wpa_ctrl_get_fd(mon_conn),&#160;&#160;//return mon_conn-&gt;s
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;<font color="#1b16da">wpa_cli_mon_receive</font>, NULL, NULL);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;} else {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;printf(&quot;Warning: Failed to attach to &quot;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&quot;wpa_supplicant.\n&quot;);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;wpa_cli_close_connection();
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;return -1;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;}
    </p>
    <p>
      &#160;&#160;&#160;&#160;}
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;return 0;
    </p>
    <p>
      }
    </p>
  </body>
</html></richcontent>
<node CREATED="1509521972756" ID="ID_892426074" MODIFIED="1515572648357">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      struct wpa_ctrl * wpa_ctrl_open2(const char *ctrl_path,
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;const char *cli_path)
    </p>
    <p>
      {
    </p>
    <p>
      &#160;&#160;&#160;&#160;struct wpa_ctrl *ctrl;
    </p>
    <p>
      &#160;&#160;&#160; <font color="#1514d5">static int counter = 0;</font>
    </p>
    <p>
      &#160;&#160;&#160;&#160;int ret;
    </p>
    <p>
      &#160;&#160;&#160;&#160;size_t res;
    </p>
    <p>
      &#160;&#160;&#160;&#160;int tries = 0;
    </p>
    <p>
      &#160;&#160;&#160;&#160;int flags;
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (ctrl_path == NULL)
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;return NULL;
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;ctrl = os_zalloc(sizeof(*ctrl));
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (ctrl == NULL)
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;return NULL;
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160; <font color="#c70707">ctrl-&gt;s = socket(PF_UNIX, SOCK_DGRAM, 0);</font>
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (ctrl-&gt;s &lt; 0) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;os_free(ctrl);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;return NULL;
    </p>
    <p>
      &#160;&#160;&#160;&#160;}
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;<font color="#ce1111">ctrl-&gt;local.sun_family = AF_UNIX;</font>
    </p>
    <p>
      &#160;&#160;&#160; <font color="#1208ca">counter++; </font>
    </p>
    <p>
      try_again:
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (cli_path &amp;&amp; cli_path[0] == '/') {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;ret = os_snprintf(ctrl-&gt;local.sun_path,
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;sizeof(ctrl-&gt;local.sun_path),
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&quot;%s/&quot; CONFIG_CTRL_IFACE_CLIENT_PREFIX &quot;%d-%d&quot;,
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;cli_path, (int) getpid(), counter);
    </p>
    <p>
      &#160;&#160;&#160;&#160;}<font color="#120808">&#160;else { </font>
    </p>
    <p>
      <font color="#d10606">&#160;&#160;&#160;&#160;&#160;&#160;&#160;/** </font>
    </p>
    <p>
      <font color="#d10606">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;* client_socket_dir=NULL, &#25152;&#20197;&#22312;/tmp/&#30446;&#24405;&#19979; </font>
    </p>
    <p>
      <font color="#d10606">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;* &#21019;&#24314;UNIX domain socket&#25991;&#20214; </font>
    </p>
    <p>
      <font color="#d10606">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;*/ </font>
    </p>
    <p>
      <font color="#d10606">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;ret = os_snprintf(ctrl-&gt;local.sun_path, </font>
    </p>
    <p>
      <font color="#d10606">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;sizeof(ctrl-&gt;local.sun_path), </font>
    </p>
    <p>
      <font color="#d10606">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;CONFIG_CTRL_IFACE_CLIENT_DIR &quot;/&quot; </font>
    </p>
    <p>
      <font color="#d10606">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;CONFIG_CTRL_IFACE_CLIENT_PREFIX &quot;%d-%d&quot;, </font>
    </p>
    <p>
      <font color="#d10606">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;(int) getpid(), counter);</font>
    </p>
    <p>
      <font color="#120808">&#160;&#160;&#160;&#160;}</font>
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (os_snprintf_error(sizeof(ctrl-&gt;local.sun_path), ret)) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;close(ctrl-&gt;s);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;os_free(ctrl);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;return NULL;
    </p>
    <p>
      &#160;&#160;&#160;&#160;}
    </p>
    <p>
      &#160;&#160;&#160;&#160;tries++;
    </p>
    <p>
      <font color="#211ac9">&#160;&#160;&#160;&#160;/** </font>
    </p>
    <p>
      <font color="#211ac9">&#160;&#160;&#160;&#160;&#160;&#160;* &#35843;&#29992;bind()&#21019;&#24314;&#33258;&#24049;&#30340;</font><font color="#1e34da">UNIX domain socket</font><font color="#211ac9">&#65292; </font>
    </p>
    <p>
      <font color="#211ac9">&#160;&#160;&#160;&#160;&#160;&#160;* wpa_cli &#21487;&#20197;&#36890;&#36807;&#27492;socket&#25991;&#20214;&#25509;&#25910;&#25968;&#25454;</font>
    </p>
    <p>
      <font color="#211ac9">&#160;&#160;&#160;&#160;&#160;&#160;* &#22914;&#26524;&#27492;&#25991;&#20214;&#24050;&#32463;&#23384;&#22312;&#65292;&#21017;bind()&#38169;&#35823;&#36820;&#22238; </font>
    </p>
    <p>
      <font color="#211ac9">&#160;&#160;&#160;&#160;&#160;&#160;*/</font>
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (<font color="#b51515">bind(ctrl-&gt;s, (struct sockaddr *) &amp;ctrl-&gt;local, sizeof(ctrl-&gt;local))</font>&#160;&#160;&lt; 0) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;if (errno == EADDRINUSE &amp;&amp; tries &lt; 2) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;/**
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;* getpid() returns unique identifier for this instance
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;* of wpa_ctrl, so the existing socket file must have
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;* been left by unclean termination of an earlier run.
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;* Remove the file and try again.
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;*/
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;unlink(ctrl-&gt;local.sun_path);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;goto try_again;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;}
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;close(ctrl-&gt;s);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;os_free(ctrl);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;return NULL;
    </p>
    <p>
      &#160;&#160;&#160;&#160;}
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;/*********************************************/
    </p>
    <p>
      &#160;&#160;&#160; <font color="#d60d0d">ctrl-&gt;dest.sun_family = AF_UNIX;</font>
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (os_strncmp(ctrl_path, &quot;@abstract:&quot;, 10) == 0) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;ctrl-&gt;dest.sun_path[0] = '\0';
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;os_strlcpy(ctrl-&gt;dest.sun_path + 1, ctrl_path + 10,
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;sizeof(ctrl-&gt;dest.sun_path) - 1);
    </p>
    <p>
      &#160;&#160;&#160;&#160;} else {
    </p>
    <p>
      <font color="#db0b0b">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;/* * </font>
    </p>
    <p>
      <font color="#db0b0b">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;*</font>&#160;<font color="#c91111">ctrl-&gt;dest.sun_path = ctrl_path =&#160;</font><font color="#1413ef">&quot;/var/run/wpa_supplicant/wlan0&quot; </font>
    </p>
    <p>
      <font color="#d71804">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;*/</font>
    </p>
    <p>
      <font color="#c91111">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;res = os_strlcpy(ctrl-&gt;dest.sun_path, ctrl_path, sizeof(ctrl-&gt;dest.sun_path)); </font>
    </p>
    <p>
      <font color="#1b0b0b">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;if (res &gt;= sizeof(ctrl-&gt;dest.sun_path)) { </font>
    </p>
    <p>
      <font color="#1b0b0b">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;close(ctrl-&gt;s); </font>
    </p>
    <p>
      <font color="#1b0b0b">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;os_free(ctrl); </font>
    </p>
    <p>
      <font color="#1b0b0b">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;return NULL; </font>
    </p>
    <p>
      <font color="#1b0b0b">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;}</font>
    </p>
    <p>
      &#160;&#160;&#160;&#160;}
    </p>
    <p>
      <font color="#1e34da">&#160;&#160;&#160;&#160;/** </font>
    </p>
    <p>
      <font color="#1e34da">&#160;&#160;&#160;&#160;&#160;* &#35843;&#29992; connect() &#20989;&#25968;&#38142;&#25509;&#19982; wpa_supplicant &#36890;&#20449;&#30340;UNIX domain socket </font>
    </p>
    <p>
      <font color="#1e34da">&#160;&#160;&#160;&#160;&#160;*/</font>
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (<font color="#e81b1b">connect(ctrl-&gt;s, (struct sockaddr *) &amp;ctrl-&gt;dest, sizeof(ctrl-&gt;dest))</font>&#160;&#160;&lt; 0) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;close(ctrl-&gt;s);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;unlink(ctrl-&gt;local.sun_path);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;os_free(ctrl);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;return NULL;
    </p>
    <p>
      &#160;&#160;&#160;&#160;}
    </p>
    <p>
      
    </p>
    <p>
      <font color="#c91111">&#160;&#160;&#160;&#160;/* </font>
    </p>
    <p>
      <font color="#c91111">&#160;&#160;&#160;&#160;&#160;* Make socket non-blocking so that we don't hang forever if </font>
    </p>
    <p>
      <font color="#c91111">&#160;&#160;&#160;&#160;&#160;* target dies unexpectedly. </font>
    </p>
    <p>
      <font color="#c91111">&#160;&#160;&#160;&#160;&#160;*/ </font>
    </p>
    <p>
      <font color="#c91111">&#160;&#160;&#160; </font><font color="#1a0c0c">flags = fcntl(ctrl-&gt;s, F_GETFL);</font>
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (flags &gt;= 0) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;flags |= O_NONBLOCK;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;if (fcntl(ctrl-&gt;s, F_SETFL, flags) &lt; 0) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;perror(&quot;fcntl(ctrl-&gt;s, O_NONBLOCK)&quot;);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;/* Not fatal, continue on.*/
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;}
    </p>
    <p>
      &#160;&#160;&#160;&#160;}
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;return ctrl;
    </p>
    <p>
      }
    </p>
  </body>
</html>
</richcontent>
</node>
<node CREATED="1509952050799" ID="ID_1415895261" MODIFIED="1509952698339">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      int eloop_register_read_sock(int sock, eloop_sock_handler handler,
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;void *eloop_data, void *user_data)
    </p>
    <p>
      {
    </p>
    <p>
      &#160;&#160;&#160;&#160;return eloop_register_sock(sock, EVENT_TYPE_READ, handler,
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;eloop_data, user_data);
    </p>
    <p>
      }
    </p>
    <p>
      
    </p>
    <p>
      int eloop_register_sock(int sock, eloop_event_type type,
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;eloop_sock_handler handler,
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;void *eloop_data, void *user_data)
    </p>
    <p>
      {
    </p>
    <p>
      &#160;&#160;&#160;&#160;struct eloop_sock_table *table;
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;/**
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;* &#26029;&#35328;sock&#26159;&#21542;&#26377;&#25928;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;*/
    </p>
    <p>
      &#160;&#160;&#160;&#160;assert(sock &gt;= 0);
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;/**
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;* &#20174;eloop&#20013;&#33719;&#21462;&#26576;&#20010;&#31867;&#22411;&#30340;&#160;&#160;sock &#38598;&#30340;&#25351;&#38024;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;*/
    </p>
    <p>
      &#160;&#160;&#160;&#160;table = eloop_get_sock_table(type);
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;/**
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;* &#28155;&#21152;&#19968;&#20010;sock&#21040;&#23545;&#24212;&#31867;&#22411;&#30340;sock&#38598;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;*/
    </p>
    <p>
      &#160;&#160;&#160;&#160;return eloop_sock_table_add_sock(table, sock, handler,
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;eloop_data, user_data);
    </p>
    <p>
      }
    </p>
  </body>
</html></richcontent>
</node>
<node CREATED="1509952878735" ID="ID_1238732696" MODIFIED="1509952922699">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      static void wpa_cli_mon_receive(int sock, void *eloop_ctx, void *sock_ctx)
    </p>
    <p>
      {
    </p>
    <p>
      &#160;&#160;&#160;&#160;wpa_cli_recv_pending(mon_conn, 0);
    </p>
    <p>
      }
    </p>
    <p>
      
    </p>
    <p>
      static void wpa_cli_recv_pending(struct wpa_ctrl *ctrl, int action_monitor)
    </p>
    <p>
      {
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (ctrl_conn == NULL) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;wpa_cli_reconnect();
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;return;
    </p>
    <p>
      &#160;&#160;&#160;&#160;}
    </p>
    <p>
      &#160;&#160;&#160;&#160;while (wpa_ctrl_pending(ctrl) &gt; 0) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;char buf[4096];
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;size_t len = sizeof(buf) - 1;
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;if (wpa_ctrl_recv(ctrl, buf, &amp;len) == 0) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;buf[len] = '\0';
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;if (action_monitor)
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;wpa_cli_action_process(buf);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;else {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;cli_event(buf);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;if (wpa_cli_show_event(buf)) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;edit_clear_line();
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;printf(&quot;\r%s\n&quot;, buf);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;edit_redraw();
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;}
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;if (interactive &amp;&amp; check_terminating(buf) &gt; 0)
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;return;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;}
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;} else {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;printf(&quot;Could not read pending message.\n&quot;);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;break;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;}
    </p>
    <p>
      &#160;&#160;&#160;&#160;}
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (wpa_ctrl_pending(ctrl) &lt; 0) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;printf(&quot;Connection to wpa_supplicant lost - trying to &quot;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&quot;reconnect\n&quot;);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;wpa_cli_reconnect();
    </p>
    <p>
      &#160;&#160;&#160;&#160;}
    </p>
    <p>
      }
    </p>
  </body>
</html></richcontent>
</node>
</node>
<node CREATED="1509953069017" ID="ID_59451495" MODIFIED="1509953220122">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      static DEFINE_DL_LIST(bsses); /* struct cli_txt_entry */
    </p>
    <p>
      
    </p>
    <p>
      static void update_bssid_list(struct wpa_ctrl *ctrl)
    </p>
    <p>
      {
    </p>
    <p>
      &#160;&#160;&#160;&#160;char buf[4096];
    </p>
    <p>
      &#160;&#160;&#160;&#160;size_t len = sizeof(buf);
    </p>
    <p>
      &#160;&#160;&#160;&#160;int ret;
    </p>
    <p>
      &#160;&#160;&#160;&#160;char *cmd = &quot;BSS RANGE=ALL MASK=0x2&quot;;
    </p>
    <p>
      &#160;&#160;&#160;&#160;char *pos, *end;
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (ctrl == NULL)
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;return;
    </p>
    <p>
      &#160;&#160;&#160;&#160;ret = wpa_ctrl_request(ctrl, cmd, os_strlen(cmd), buf, &amp;len, NULL);
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (ret &lt; 0)
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;return;
    </p>
    <p>
      &#160;&#160;&#160;&#160;buf[len] = '\0';
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;pos = buf;
    </p>
    <p>
      &#160;&#160;&#160;&#160;while (pos) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;pos = os_strstr(pos, &quot;bssid=&quot;);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;if (pos == NULL)
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;break;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;pos += 6;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;end = os_strchr(pos, '\n');
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;if (end == NULL)
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;break;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;*end = '\0';
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;cli_txt_list_add(&amp;bsses, pos);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;pos = end + 1;
    </p>
    <p>
      &#160;&#160;&#160;&#160;}
    </p>
    <p>
      }
    </p>
  </body>
</html></richcontent>
</node>
<node CREATED="1509953165600" ID="ID_500777527" MODIFIED="1509953233538">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      static DEFINE_DL_LIST(networks); /* struct cli_txt_entry */
    </p>
    <p>
      
    </p>
    <p>
      static void update_networks(struct wpa_ctrl *ctrl)
    </p>
    <p>
      {
    </p>
    <p>
      &#160;&#160;&#160;&#160;char buf[4096];
    </p>
    <p>
      &#160;&#160;&#160;&#160;size_t len = sizeof(buf);
    </p>
    <p>
      &#160;&#160;&#160;&#160;int ret;
    </p>
    <p>
      &#160;&#160;&#160;&#160;char *cmd = &quot;LIST_NETWORKS&quot;;
    </p>
    <p>
      &#160;&#160;&#160;&#160;char *pos, *end;
    </p>
    <p>
      &#160;&#160;&#160;&#160;int header = 1;
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;cli_txt_list_flush(&amp;networks);
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (ctrl == NULL)
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;return;
    </p>
    <p>
      &#160;&#160;&#160;&#160;ret = wpa_ctrl_request(ctrl, cmd, os_strlen(cmd), buf, &amp;len, NULL);
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (ret &lt; 0)
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;return;
    </p>
    <p>
      &#160;&#160;&#160;&#160;buf[len] = '\0';
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;pos = buf;
    </p>
    <p>
      &#160;&#160;&#160;&#160;while (pos) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;end = os_strchr(pos, '\n');
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;if (end == NULL)
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;break;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;*end = '\0';
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;if (!header)
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;cli_txt_list_add_word(&amp;networks, pos, '\t');
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;header = 0;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;pos = end + 1;
    </p>
    <p>
      &#160;&#160;&#160;&#160;}
    </p>
    <p>
      }
    </p>
  </body>
</html></richcontent>
</node>
<node CREATED="1509953255672" FOLDED="true" ID="ID_264013426" MODIFIED="1515572666761">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      static void start_edit(void)
    </p>
    <p>
      {
    </p>
    <p>
      &#160;&#160;&#160;&#160;char *home;
    </p>
    <p>
      &#160;&#160;&#160;&#160;char *ps = NULL;
    </p>
    <p>
      
    </p>
    <p>
      #ifdef CONFIG_CTRL_IFACE_UDP_REMOTE
    </p>
    <p>
      &#160;&#160;&#160;&#160;ps = wpa_ctrl_get_remote_ifname(ctrl_conn);
    </p>
    <p>
      #endif /* CONFIG_CTRL_IFACE_UDP_REMOTE */
    </p>
    <p>
      
    </p>
    <p>
      #ifdef CONFIG_WPA_CLI_HISTORY_DIR
    </p>
    <p>
      &#160;&#160;&#160;&#160;home = CONFIG_WPA_CLI_HISTORY_DIR;
    </p>
    <p>
      #else /* CONFIG_WPA_CLI_HISTORY_DIR */
    </p>
    <p>
      &#160;&#160;&#160;&#160;home = getenv(&quot;HOME&quot;);
    </p>
    <p>
      #endif /* CONFIG_WPA_CLI_HISTORY_DIR */
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (home) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;const char *fname = &quot;.wpa_cli_history&quot;;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;int hfile_len = os_strlen(home) + 1 + os_strlen(fname) + 1;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;hfile = os_malloc(hfile_len);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;if (hfile)
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;os_snprintf(hfile, hfile_len, &quot;%s/%s&quot;, home, fname);
    </p>
    <p>
      &#160;&#160;&#160;&#160;}
    </p>
    <p>
      
    </p>
    <p>
      <font color="#e11111">&#160;&#160;&#160;&#160;/** </font>
    </p>
    <p>
      <font color="#e11111">&#160;&#160;&#160;&#160;&#160;* &#20132;&#20114;&#27169;&#24335;&#19979;, edit_init()&#20989;&#25968;&#30340;&#20316;&#29992;&#38750;&#24120;&#37325;&#35201;, </font>
    </p>
    <p>
      <font color="#e11111">&#160;&#160;&#160;&#160;&#160;* &#33021;&#33719;&#21462;&#32456;&#31471;&#38190;&#20837;&#30340;&#21629;&#20196;, &#27491;&#26159;&#36825;&#20010;&#20989;&#25968;&#25171;&#30340;&#22522;&#30784; </font>
    </p>
    <p>
      <font color="#e11111">&#160;&#160;&#160;&#160;&#160;*/</font>
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (edit_init(wpa_cli_edit_cmd_cb, wpa_cli_edit_eof_cb,
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;wpa_cli_edit_completion_cb, NULL, hfile, ps) &lt; 0) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;eloop_terminate();
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;return;
    </p>
    <p>
      &#160;&#160;&#160;&#160;}
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;edit_started = 1;
    </p>
    <p>
      
    </p>
    <p>
      <font color="#da0808">&#160;&#160;&#160;&#160;/** </font>
    </p>
    <p>
      <font color="#da0808">&#160;&#160;&#160;&#160;&#160;* ping_interval = 5, &#27880;&#20876;&#19968;&#20010;timeou&#20107;&#20214;, &#21363;5s&#21518;, </font>
    </p>
    <p>
      <font color="#da0808">&#160;&#160;&#160;&#160;&#160;* wpa_cli_ping()&#20989;&#25968;&#23558;&#34987;&#35843;&#29992;&#65288;&#35843;&#29992;&#22320;&#26041;&#22312;eloop_run()&#20013;&#65289;, </font>
    </p>
    <p>
      <font color="#da0808">&#160;&#160;&#160;&#160;&#160;* &#21521;wpa_supplicant&#21457;&#36865;PING&#21629;&#20196;&#65292; </font>
    </p>
    <p>
      <font color="#da0808">&#160;&#160;&#160;&#160;&#160;* &#29992;&#20110;&#21028;&#26029;wpa_cli&#26159;&#21542;&#21644;wpa_supplicant&#26029;&#24320;&#36830;&#25509; </font>
    </p>
    <p>
      <font color="#da0808">&#160;&#160;&#160;&#160;&#160;*/</font>
    </p>
    <p>
      &#160;&#160;&#160;&#160;eloop_register_timeout(ping_interval, 0, wpa_cli_ping, NULL, NULL);
    </p>
    <p>
      }
    </p>
  </body>
</html></richcontent>
<node CREATED="1509953379624" ID="ID_51080385" MODIFIED="1509959214434">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      <font color="#292fd7">/** </font>
    </p>
    <p>
      <font color="#292fd7">&#160;* &#36825;&#20010;&#20989;&#25968;&#22312;edit.c&#12289;edit_readline.c&#20197;&#21450;edit_simple.c&#37117;&#26377;&#23450;&#20041;, &#40664;&#35748;&#26159;edit_simple.c, &#21487;&#22312; .config </font>
    </p>
    <p>
      <font color="#292fd7">&#160;* &#36873;&#25321;, &#22312;&#20132;&#20114;&#27169;&#24335;&#19979;&#19981;&#25903;&#25345;&#21024;&#38500;&#38190;&#20837;&#30340;&#23383;&#31526;, &#21363;&#22914;&#26524;&#21629;&#20196;&#36755;&#20837;&#38169;&#35823;, &#26080;&#27861;&#36890;&#36807; Backspace&#38190;&#20462;&#25913; </font>
    </p>
    <p>
      <font color="#292fd7">&#160;*/</font>
    </p>
    <p>
      int edit_init(void (*cmd_cb)(void *ctx, char *cmd),
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;void (*eof_cb)(void *ctx),
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;char ** (*completion_cb)(void *ctx, const char *cmd, int pos),
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;void *ctx, const char *history_file, const char *ps)
    </p>
    <p>
      {
    </p>
    <p>
      &#160;&#160;&#160;&#160;edit_cb_ctx = ctx;
    </p>
    <p>
      &#160;&#160;&#160;&#160;edit_cmd_cb = cmd_cb;
    </p>
    <p>
      &#160;&#160;&#160;&#160;edit_eof_cb = eof_cb;
    </p>
    <p>
      
    </p>
    <p>
      <font color="#da0d0d">&#160;&#160;&#160;&#160;/** </font>
    </p>
    <p>
      <font color="#da0d0d">&#160;&#160;&#160;&#160;&#160;* &#27880;&#20876;&#19968;&#20010;sock&#21040;eloop.readers&#38598;&#20013;, &#20851;&#32852;&#26631;&#20934;&#36755;&#20837;&#25551;&#36848;&#31526;&#21644;&#23427;&#30340;handler&#20989;&#25968;&#12289;&#20256;&#32473; </font>
    </p>
    <p>
      <font color="#da0d0d">&#160;&#160;&#160;&#160;&#160;* handler&#20989;&#25968;&#30340;&#21442;&#25968;&#31561;, &#20851;&#32852;&#30340;&#26041;&#27861;&#26159;&#29992;&#23427;&#20204;&#21021;&#22987;&#21270;&#19968;&#20010;&#160;&#160;struct eloop_sock &#32467;&#26500;&#20307;&#12290;</font>
    </p>
    <p>
      <font color="#da0d0d">&#160;&#160;&#160;&#160;&#160;* &#36825;&#20010;eloop.readers&#38598;&#20013;&#30340;&#25551;&#36848;&#31526;&#23558;&#22312;eloop_run()&#20989;&#25968;&#20013;&#35843;&#29992;select()&#20989;&#25968;&#26469;&#30417;&#21548;, &#24403; </font>
    </p>
    <p>
      <font color="#da0d0d">&#160;&#160;&#160;&#160;&#160;* &#32456;&#31471;&#38190;&#20837;&#21629;&#20196;&#26159;, handler&#20989;&#25968;&#65288;edit_read_char()&#65289;&#23558;&#34987;&#35843;&#29992;</font>
    </p>
    <p>
      <font color="#da0d0d">&#160;&#160;&#160;&#160;&#160;*/</font>
    </p>
    <p>
      &#160;&#160;&#160;&#160;eloop_register_read_sock(STDIN_FILENO, edit_read_char, NULL, NULL);
    </p>
    <p>
      &#160;&#160;&#160;&#160;ps2 = ps;
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;printf(&quot;%s&gt; &quot;, ps2 ? ps2 : &quot;&quot;);
    </p>
    <p>
      &#160;&#160;&#160;&#160;fflush(stdout);
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;return 0;
    </p>
    <p>
      }
    </p>
  </body>
</html></richcontent>
</node>
<node CREATED="1509959632887" ID="ID_513057512" MODIFIED="1509959648880">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      static void wpa_cli_edit_cmd_cb(void *ctx, char *cmd)
    </p>
    <p>
      {
    </p>
    <p>
      &#160;&#160;&#160;&#160;char *argv[max_args];
    </p>
    <p>
      &#160;&#160;&#160;&#160;int argc;
    </p>
    <p>
      &#160;&#160;&#160;&#160;argc = tokenize_cmd(cmd, argv);
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (argc)
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;wpa_request(ctrl_conn, argc, argv);
    </p>
    <p>
      }
    </p>
  </body>
</html></richcontent>
</node>
<node CREATED="1509959637055" ID="ID_1116348141" MODIFIED="1509959687010">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      static void wpa_cli_edit_eof_cb(void *ctx)
    </p>
    <p>
      {
    </p>
    <p>
      &#160;&#160;&#160;&#160;eloop_terminate();
    </p>
    <p>
      }
    </p>
  </body>
</html></richcontent>
</node>
<node CREATED="1509959634967" ID="ID_1214107754" MODIFIED="1509959665113">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      static char ** wpa_cli_edit_completion_cb(void *ctx, const char *str, int pos)
    </p>
    <p>
      {
    </p>
    <p>
      &#160;&#160;&#160;&#160;char **res;
    </p>
    <p>
      &#160;&#160;&#160;&#160;const char *end;
    </p>
    <p>
      &#160;&#160;&#160;&#160;char *cmd;
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (pos &gt; 7 &amp;&amp; os_strncasecmp(str, &quot;IFNAME=&quot;, 7) == 0) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;end = os_strchr(str, ' ');
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;if (end &amp;&amp; pos &gt; end - str) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;pos -= end - str + 1;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;str = end + 1;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;}
    </p>
    <p>
      &#160;&#160;&#160;&#160;}
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;end = os_strchr(str, ' ');
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (end == NULL || str + pos &lt; end)
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;return wpa_list_cmd_list();
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;cmd = os_malloc(pos + 1);
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (cmd == NULL)
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;return NULL;
    </p>
    <p>
      &#160;&#160;&#160;&#160;os_memcpy(cmd, str, pos);
    </p>
    <p>
      &#160;&#160;&#160;&#160;cmd[end - str] = '\0';
    </p>
    <p>
      &#160;&#160;&#160;&#160;res = wpa_cli_cmd_completion(cmd, str, pos);
    </p>
    <p>
      &#160;&#160;&#160;&#160;os_free(cmd);
    </p>
    <p>
      &#160;&#160;&#160;&#160;return res;
    </p>
    <p>
      }
    </p>
  </body>
</html></richcontent>
</node>
</node>
</node>
<node CREATED="1509620407476" ID="ID_178181821" MODIFIED="1509792504502">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      int eloop_register_timeout(unsigned int secs, unsigned int usecs,
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;eloop_timeout_handler handler,
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;void *eloop_data, void *user_data)
    </p>
    <p>
      {
    </p>
    <p>
      &#160;&#160;&#160;&#160;struct eloop_timeout *timeout, *tmp;
    </p>
    <p>
      &#160;&#160;&#160;&#160;os_time_t now_sec;
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;timeout = os_zalloc(sizeof(*timeout));
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (timeout == NULL)
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;return -1;
    </p>
    <p>
      
    </p>
    <p>
      <font color="#d70707">&#160;&#160;&#160;&#160;/** </font>
    </p>
    <p>
      <font color="#d70707">&#160;&#160;&#160;&#160;&#160;* &#33719;&#21462;&#31995;&#32479;&#23454;&#26102;&#26102;&#38388; </font>
    </p>
    <p>
      <font color="#d70707">&#160;&#160;&#160;&#160;&#160;*/</font>
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (os_get_reltime(&amp;timeout-&gt;time) &lt; 0) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;os_free(timeout);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;return -1;
    </p>
    <p>
      &#160;&#160;&#160;&#160;}
    </p>
    <p>
      &#160;&#160;&#160;&#160;now_sec = timeout-&gt;time.sec;
    </p>
    <p>
      &#160;&#160;&#160;&#160;timeout-&gt;time.sec += secs;
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (timeout-&gt;time.sec &lt; now_sec) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;/*
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;* Integer overflow - assume long enough timeout to be assumed
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;* to be infinite, i.e., the timeout would never happen.
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;*/
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;wpa_printf(MSG_DEBUG, &quot;ELOOP: Too long timeout (secs=%u) to &quot;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&quot;ever happen - ignore it&quot;, secs);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;os_free(timeout);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;return 0;
    </p>
    <p>
      &#160;&#160;&#160;&#160;}
    </p>
    <p>
      &#160;&#160;&#160;&#160;timeout-&gt;time.usec += usecs;
    </p>
    <p>
      &#160;&#160;&#160;&#160;while (timeout-&gt;time.usec &gt;= 1000000) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;timeout-&gt;time.sec++;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;timeout-&gt;time.usec -= 1000000;
    </p>
    <p>
      &#160;&#160;&#160;&#160;}
    </p>
    <p>
      &#160;&#160;&#160;&#160;timeout-&gt;eloop_data = eloop_data;
    </p>
    <p>
      &#160;&#160;&#160;&#160;timeout-&gt;user_data = user_data;
    </p>
    <p>
      &#160;&#160;&#160;&#160;timeout-&gt;handler = handler;
    </p>
    <p>
      
    </p>
    <p>
      <font color="#d70c0c">&#160;&#160;&#160;&#160;/** </font>
    </p>
    <p>
      <font color="#d70c0c">&#160;&#160;&#160;&#160;&#160;* &#30001;&#20110;WPA_TRACE&#27809;&#26377;&#23450;&#20041;, &#20197;&#19979;&#23637;&#24320;&#20026;&#31354; </font>
    </p>
    <p>
      <font color="#d70c0c">&#160;&#160;&#160;&#160;&#160;*/ </font>
    </p>
    <p>
      &#160;&#160;&#160;&#160;wpa_trace_add_ref(timeout, eloop, eloop_data);
    </p>
    <p>
      &#160;&#160;&#160;&#160;wpa_trace_add_ref(timeout, user, user_data);
    </p>
    <p>
      &#160;&#160;&#160;&#160;wpa_trace_record(timeout);
    </p>
    <p>
      
    </p>
    <p>
      <font color="#cd0505">&#160;&#160;&#160;&#160;/** </font>
    </p>
    <p>
      <font color="#cd0505">&#160;&#160;&#160;&#160;&#160;&#160;* Maintain timeouts in order of increasing time. </font>
    </p>
    <p>
      <font color="#cd0505">&#160;&#160;&#160;&#160;&#160;&#160;* &#20445;&#25345;timeout&#38142;&#34920;&#30340;&#26102;&#38388;&#20026;&#22686;&#24207; </font>
    </p>
    <p>
      <font color="#cd0505">&#160;&#160;&#160;&#160;&#160;&#160;*/</font>
    </p>
    <p>
      &#160;&#160;&#160;&#160;dl_list_for_each(tmp, &amp;eloop.timeout, struct eloop_timeout, list) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;if (os_reltime_before(&amp;timeout-&gt;time, &amp;tmp-&gt;time)) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;dl_list_add(tmp-&gt;list.prev, &amp;timeout-&gt;list); //&#28155;&#21152;&#21040;&#38142;&#34920;&#22836;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;return 0;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;}
    </p>
    <p>
      &#160;&#160;&#160;&#160;}
    </p>
    <p>
      &#160;&#160;&#160;&#160;dl_list_add_tail(&amp;eloop.timeout, &amp;timeout-&gt;list); //&#28155;&#21152;&#21040;&#38142;&#34920;&#23614;
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;return 0;
    </p>
    <p>
      }
    </p>
  </body>
</html></richcontent>
</node>
<node CREATED="1509620412428" FOLDED="true" ID="ID_618846240" MODIFIED="1515572672032">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      #if !defined(CONFIG_ELOOP_POLL) &amp;&amp; \
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;!defined(CONFIG_ELOOP_EPOLL) &amp;&amp; \
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;!defined(CONFIG_ELOOP_KQUEUE)
    </p>
    <p>
      #define CONFIG_ELOOP_SELECT
    </p>
    <p>
      #endif
    </p>
    <p>
      /**
    </p>
    <p>
      &#160;* eloop_run()&#20989;&#25968;&#24456;&#38271;&#65292;&#21482;&#36148;&#20986;&#20250;&#25191;&#34892;&#21040;&#30340;&#20195;&#30721;
    </p>
    <p>
      &#160;*/
    </p>
    <p>
      void eloop_run(void)
    </p>
    <p>
      {
    </p>
    <p>
      #ifdef CONFIG_ELOOP_SELECT
    </p>
    <p>
      &#160;&#160;&#160;&#160;fd_set *rfds, *wfds, *efds;
    </p>
    <p>
      &#160;&#160;&#160;&#160;struct timeval _tv;
    </p>
    <p>
      #endif /* CONFIG_ELOOP_SELECT */
    </p>
    <p>
      &#160;&#160;&#160;&#160;int res;
    </p>
    <p>
      &#160;&#160;&#160;&#160;struct os_reltime tv, now;
    </p>
    <p>
      
    </p>
    <p>
      #ifdef CONFIG_ELOOP_SELECT
    </p>
    <p>
      &#160;&#160;&#160;&#160;rfds = os_malloc(sizeof(*rfds));
    </p>
    <p>
      &#160;&#160;&#160;&#160;wfds = os_malloc(sizeof(*wfds));
    </p>
    <p>
      &#160;&#160;&#160;&#160;efds = os_malloc(sizeof(*efds));
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (rfds == NULL || wfds == NULL || efds == NULL)
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;goto out;
    </p>
    <p>
      #endif /* CONFIG_ELOOP_SELECT */
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;while (!eloop.terminate &amp;&amp;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;(!dl_list_empty(&amp;eloop.timeout) || eloop.readers.count &gt; 0 ||
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;eloop.writers.count &gt; 0 || eloop.exceptions.count &gt; 0)) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;struct eloop_timeout *timeout;
    </p>
    <p>
      
    </p>
    <p>
      <font color="#d50101">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;/** </font>
    </p>
    <p>
      <font color="#d50101">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;* eloop.pending_terminate&#32622;1&#65288;eloop_handle_signal()&#20989;&#25968;&#20013;&#65289;, </font>
    </p>
    <p>
      <font color="#d50101">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;* &#34920;&#26126;wpa_cli&#25910;&#21040;SIGINT&#65288;Ctrl+c&#65289;&#25110;SIGTERM&#65288;kill&#65289;&#20449;&#21495; </font>
    </p>
    <p>
      <font color="#d50101">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;*/</font>
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;if (eloop.pending_terminate) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;/*
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;* This may happen in some corner cases where a signal
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;* is received during a blocking operation. We need to
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;* process the pending signals and exit if requested to
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;* avoid hitting the SIGALRM limit if the blocking
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;* operation took more than two seconds.
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;*/
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;<font color="#e60d0d">eloop_process_pending_signals(); //&#22788;&#29702;&#26410;&#22788;&#29702;&#30340;&#20449;&#21495;</font>
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;if (eloop.terminate)
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;break;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;}
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;timeout = dl_list_first(&amp;eloop.timeout, struct eloop_timeout, list);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;if (timeout) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;os_get_reltime(&amp;now);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;if (os_reltime_before(&amp;now, &amp;timeout-&gt;time))
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;os_reltime_sub(&amp;timeout-&gt;time, &amp;now, &amp;tv);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;else
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;tv.sec = tv.usec = 0;
    </p>
    <p>
      
    </p>
    <p>
      #ifdef CONFIG_ELOOP_SELECT
    </p>
    <p>
      <font color="#c70303">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;/** </font>
    </p>
    <p>
      <font color="#c70303">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;* &#35774;&#32622;select()&#36229;&#26102;&#30340;&#26102;&#38388; </font>
    </p>
    <p>
      <font color="#c70303">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;*/ </font>
    </p>
    <p>
      <font color="#c70303">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;_tv.tv_sec = tv.sec; </font>
    </p>
    <p>
      <font color="#c70303">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;_tv.tv_usec = tv.usec;</font>
    </p>
    <p>
      #endif /* CONFIG_ELOOP_SELECT */
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;}
    </p>
    <p>
      
    </p>
    <p>
      #ifdef CONFIG_ELOOP_SELECT
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;/**
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;* &#35774;&#32622;&#30417;&#21548;&#30340;&#25551;&#36848;&#31526;&#38598;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;*/
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;eloop_sock_table_set_fds(&amp;eloop.readers, rfds);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;eloop_sock_table_set_fds(&amp;eloop.writers, wfds);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;eloop_sock_table_set_fds(&amp;eloop.exceptions, efds);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;res = select(eloop.max_sock + 1, rfds, wfds, efds,
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;timeout ? &amp;_tv : NULL);
    </p>
    <p>
      #endif /* CONFIG_ELOOP_SELECT */
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;if (res &lt; 0 &amp;&amp; errno != EINTR &amp;&amp; errno != 0) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;wpa_printf(MSG_ERROR, &quot;eloop: %s: %s&quot;,
    </p>
    <p>
      #ifdef CONFIG_ELOOP_SELECT
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&quot;select&quot;
    </p>
    <p>
      #endif /* CONFIG_ELOOP_SELECT */
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;, strerror(errno));
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;goto out;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;}
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;eloop.readers.changed = 0;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;eloop.writers.changed = 0;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;eloop.exceptions.changed = 0;
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;eloop_process_pending_signals();
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;/* check if some registered timeouts have occurred */
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;timeout = dl_list_first(&amp;eloop.timeout, struct eloop_timeout, list);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;if (timeout) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;os_get_reltime(&amp;now);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;if (!os_reltime_before(&amp;now, &amp;timeout-&gt;time)) {
    </p>
    <p>
      <font color="#d70707">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;/** </font>
    </p>
    <p>
      <font color="#d70707">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;* &#39318;&#27425;&#36827;&#26469;&#36825;&#37324;&#26159;&#22312;wpa_cli_interactive()&#20989;&#25968;&#25191;&#34892;: </font>
    </p>
    <p>
      <font color="#d70707">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;* eloop_register_timeout(0, 0, try_connection, NULL, NULL); </font>
    </p>
    <p>
      <font color="#d70707">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;* &#27880;&#20876;&#20102;&#31532;&#19968;&#20010;timeout&#20043;&#21518;, &#25152;&#20197;&#39318;&#27425;&#36827;&#26469;&#36825;&#37324;</font><font color="#d50101">handler=</font><font color="#d70707">try_connection() </font>
    </p>
    <p>
      <font color="#d70707">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;*/</font>
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;void *eloop_data = timeout-&gt;eloop_data;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;void *user_data = timeout-&gt;user_data;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;eloop_timeout_handler <font color="#d50101">handler&#160; = timeout-&gt;handler</font>;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;eloop_remove_timeout(timeout); //&#20174;timeouts&#160; list&#21024;&#38500;&#36825;&#20010;timeout&#20803;&#32032;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;handler(eloop_data, user_data);&#160;&#160; //&#25191;&#34892;timeout&#20803;&#32032;&#20013;&#30340;handler&#20989;&#25968;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;}
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;}
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;if (res &lt;= 0)
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;continue;
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;if (eloop.readers.changed ||
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;eloop.writers.changed ||
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;eloop.exceptions.changed) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;/*
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;* Sockets may have been closed and reopened with the
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;* same FD in the signal or timeout handlers, so we
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;* must skip the previous results and check again
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;* whether any of the currently registered sockets have
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;* events.
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;*/
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;continue;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;}
    </p>
    <p>
      
    </p>
    <p>
      #ifdef CONFIG_ELOOP_SELECT
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;eloop_sock_table_dispatch(&amp;eloop.readers, rfds);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;eloop_sock_table_dispatch(&amp;eloop.writers, wfds);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;eloop_sock_table_dispatch(&amp;eloop.exceptions, efds);
    </p>
    <p>
      #endif /* CONFIG_ELOOP_SELECT */
    </p>
    <p>
      &#160;&#160;&#160;&#160;}
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;eloop.terminate = 0;
    </p>
    <p>
      out:
    </p>
    <p>
      #ifdef CONFIG_ELOOP_SELECT
    </p>
    <p>
      &#160;&#160;&#160;&#160;os_free(rfds);
    </p>
    <p>
      &#160;&#160;&#160;&#160;os_free(wfds);
    </p>
    <p>
      &#160;&#160;&#160;&#160;os_free(efds);
    </p>
    <p>
      #endif /* CONFIG_ELOOP_SELECT */
    </p>
    <p>
      &#160;&#160;&#160;&#160;return;
    </p>
    <p>
      }
    </p>
  </body>
</html></richcontent>
<node CREATED="1509675935366" ID="ID_1628338209" MODIFIED="1509676475712">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      #ifdef CONFIG_ELOOP_SELECT
    </p>
    <p>
      
    </p>
    <p>
      void eloop_sock_table_set_fds(struct eloop_sock_table *table,
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;fd_set *fds)
    </p>
    <p>
      {
    </p>
    <p>
      &#160;&#160;&#160;&#160;int i;
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;FD_ZERO(fds);
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (table-&gt;table == NULL)
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;return;
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;for (i = 0; i &lt; table-&gt;count; i++) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;assert(table-&gt;table[i].sock &gt;= 0);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;FD_SET(table-&gt;table[i].sock, fds);
    </p>
    <p>
      &#160;&#160;&#160;&#160;}
    </p>
    <p>
      }
    </p>
    <p>
      
    </p>
    <p>
      void eloop_sock_table_dispatch(struct eloop_sock_table *table,
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;fd_set *fds)
    </p>
    <p>
      {
    </p>
    <p>
      &#160;&#160;&#160;&#160;int i;
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (table == NULL || table-&gt;table == NULL)
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;return;
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;table-&gt;changed = 0;
    </p>
    <p>
      &#160;&#160;&#160;&#160;for (i = 0; i &lt; table-&gt;count; i++) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;if (FD_ISSET(table-&gt;table[i].sock, fds)) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;table-&gt;table[i].handler(table-&gt;table[i].sock,
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;table-&gt;table[i].eloop_data,
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;table-&gt;table[i].user_data);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;if (table-&gt;changed)
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;break;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;}
    </p>
    <p>
      &#160;&#160;&#160;&#160;}
    </p>
    <p>
      }
    </p>
    <p>
      
    </p>
    <p>
      #endif
    </p>
  </body>
</html></richcontent>
</node>
<node CREATED="1509780970182" ID="ID_1678222323" MODIFIED="1509781850006">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      static void eloop_process_pending_signals(void)
    </p>
    <p>
      {
    </p>
    <p>
      &#160;&#160;&#160;&#160;int i;
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;/**
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;* &#22914;&#26524;&#27809;&#26377;&#25910;&#21040;&#24453;&#22788;&#29702;&#21040;&#20449;&#21495;&#65292;&#30452;&#25509;&#36864;&#20986;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;*/
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (eloop.signaled == 0)
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;return;
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;eloop.signaled = 0;
    </p>
    <p>
      <font color="#dc0a0a">&#160;&#160;&#160;&#160;&#160;/** </font>
    </p>
    <p>
      <font color="#dc0a0a">&#160;&#160;&#160;&#160;&#160;&#160;* </font><font color="#d50101">wpa_cli&#25910;&#21040;SIGINT&#65288;Ctrl+c&#65289;&#25110;SIGTERM&#65288;kill&#65289;&#20449;&#21495;, </font>
    </p>
    <p>
      <font color="#d50101">&#160;&#160;&#160;&#160;&#160;&#160;* &#19988;</font><font color="#dc0a0a">eloop.pending_terminate&#34987;&#32622;1 </font>
    </p>
    <p>
      <font color="#dc0a0a">&#160;&#160;&#160;&#160;&#160;&#160;*/</font>
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (eloop.pending_terminate) {
    </p>
    <p>
      #ifndef CONFIG_NATIVE_WINDOWS
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;alarm(0); <font color="#da1414">//&#21462;&#28040;alarm()&#35774;&#32622;&#21040;2&#31186;&#20498;&#35745;&#26102;</font>
    </p>
    <p>
      #endif /* CONFIG_NATIVE_WINDOWS */
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;eloop.pending_terminate = 0;
    </p>
    <p>
      &#160;&#160;&#160;&#160;}
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;for (i = 0; i &lt; eloop.signal_count; i++) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;if (eloop.signals[i].signaled) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;eloop.signals[i].signaled = 0;
    </p>
    <p>
      <font color="#cc1212">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;/** </font>
    </p>
    <p>
      <font color="#cc1212">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;* &#35843;&#29992;&#35813;&#20449;&#21495;&#21040;&#22788;&#29702;&#20989;&#25968; </font>
    </p>
    <p>
      <font color="#cc1212">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;*/ </font>
    </p>
    <p>
      <font color="#cc1212">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;eloop.signals[i].handler(eloop.signals[i].sig, </font>
    </p>
    <p>
      <font color="#cc1212">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;eloop.signals[i].user_data);</font>
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;}
    </p>
    <p>
      &#160;&#160;&#160;&#160;}
    </p>
    <p>
      }
    </p>
  </body>
</html></richcontent>
</node>
</node>
</node>
</node>
</node>
</node>
<node CREATED="1509517119862" ID="ID_269161153" MODIFIED="1509680374072" POSITION="right" TEXT="&#x975e;&#x4ea4;&#x4e92;&#x6a21;&#x5f0f;&#x4ee3;&#x7801;&#x6d41;&#x7a0b;">
<font BOLD="true" ITALIC="true" NAME="SansSerif" SIZE="18"/>
<node CREATED="1509538459157" ID="ID_963124314" MODIFIED="1509680429042" TEXT="&#x8bf4;&#x660e;: &#x6b64;&#x6a21;&#x5f0f;&#x76f4;&#x63a5;&#x6267;&#x884c;&#x6307;&#x5b9a;&#x547d;&#x4ee4;&#xff0c;&#x4f8b;&#x5982;: wpa_cli status">
<font NAME="SansSerif" SIZE="16"/>
</node>
<node CREATED="1509517116980" FOLDED="true" ID="ID_1047658560" MODIFIED="1515572727993" TEXT="int main(int argc, char *argv[])">
<font NAME="SansSerif" SIZE="16"/>
<node CREATED="1509519063017" FOLDED="true" ID="ID_20853257" MODIFIED="1515572726618">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      <font color="#dd1212">eloop_init</font>();
    </p>
  </body>
</html></richcontent>
<node CREATED="1509519115049" ID="ID_39968937" MODIFIED="1509673836095">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      int eloop_init(void)
    </p>
    <p>
      {&#160;&#160;&#160;
    </p>
    <p>
      <font color="#cf1010">&#160;&#160;&#160;&#160;os_memset(&amp;eloop, 0, sizeof(eloop));&#160;&#160;//&#28165;&#38646; struct eloop_data</font>
    </p>
    <p>
      <font color="#cf1010">&#160;&#160;&#160;&#160;dl_list_init(&amp;eloop.timeout); //&#21021;&#22987;&#21270;list </font>
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;/**
    </p>
    <p>
      &#160;&#160;&#160;&#160;* &#20197;&#19979;&#23439;&#37117;&#27809;&#26377;&#23450;&#20041;, &#36825;&#27573;&#20195;&#30721;&#19981;&#25191;&#34892;
    </p>
    <p>
      &#160;&#160;&#160;&#160;*/
    </p>
    <p>
      #ifdef CONFIG_ELOOP_EPOLL
    </p>
    <p>
      &#160;&#160;&#160;&#160;eloop.epollfd = epoll_create1(0);
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (eloop.epollfd &lt; 0) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;wpa_printf(MSG_ERROR, &quot;%s: epoll_create1 failed. %s&quot;,
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;__func__, strerror(errno));
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;return -1;
    </p>
    <p>
      &#160;&#160;&#160;&#160;}
    </p>
    <p>
      #endif /* CONFIG_ELOOP_EPOLL */
    </p>
    <p>
      #ifdef CONFIG_ELOOP_KQUEUE
    </p>
    <p>
      &#160;&#160;&#160;&#160;eloop.kqueuefd = kqueue();
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (eloop.kqueuefd &lt; 0) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;wpa_printf(MSG_ERROR, &quot;%s: kqueue failed: %s&quot;,
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;__func__, strerror(errno));
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;return -1;
    </p>
    <p>
      &#160;&#160;&#160;&#160;}
    </p>
    <p>
      #endif /* CONFIG_ELOOP_KQUEUE */
    </p>
    <p>
      #if defined(CONFIG_ELOOP_EPOLL) || defined(CONFIG_ELOOP_KQUEUE)
    </p>
    <p>
      &#160;&#160;&#160;&#160;eloop.readers.type = EVENT_TYPE_READ;
    </p>
    <p>
      &#160;&#160;&#160;&#160;eloop.writers.type = EVENT_TYPE_WRITE;
    </p>
    <p>
      &#160;&#160;&#160;&#160;eloop.exceptions.type = EVENT_TYPE_EXCEPTION;
    </p>
    <p>
      #endif /* CONFIG_ELOOP_EPOLL || CONFIG_ELOOP_KQUEUE */
    </p>
    <p>
      #ifdef WPA_TRACE
    </p>
    <p>
      &#160;&#160;&#160;&#160;signal(SIGSEGV, eloop_sigsegv_handler);
    </p>
    <p>
      #endif /* WPA_TRACE */
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;<font color="#000000">&#160;return 0;</font>
    </p>
    <p>
      }
    </p>
  </body>
</html></richcontent>
</node>
</node>
<node CREATED="1509519259177" FOLDED="true" ID="ID_1768142244" MODIFIED="1510028874921">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      <font color="#c20808">eloop_register_signal_terminate </font>(wpa_cli_terminate, NULL);
    </p>
  </body>
</html></richcontent>
<node CREATED="1509519305715" ID="ID_1413233532" MODIFIED="1509614749543">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      wpa_cli_terminate(int sig, void *ctx)
    </p>
    <p>
      {
    </p>
    <p>
      &#160;&#160;&#160;&#160;eloop_terminate();
    </p>
    <p>
      }
    </p>
    <p>
      
    </p>
    <p>
      int eloop_register_signal_terminate(eloop_signal_handler handler,
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;void *user_data)
    </p>
    <p>
      {
    </p>
    <p>
      &#160;&#160;&#160;&#160;int ret = eloop_register_signal(<font color="#e60d0d">SIGINT</font>, handler, user_data); //&#27880;&#20876;<font color="#e60d0d">SIGINT&#20449;&#21495;&#30340;&#22788;&#29702;&#20989;&#25968;</font>
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (ret == 0)
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;ret = eloop_register_signal(<font color="#d41e1e">SIGTERM</font>, handler, user_data);
    </p>
    <p>
      &#160;&#160;&#160;&#160;return ret;
    </p>
    <p>
      }
    </p>
  </body>
</html></richcontent>
<node CREATED="1509614772149" ID="ID_490912983" MODIFIED="1509614792871">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      void eloop_terminate(void)
    </p>
    <p>
      {
    </p>
    <p>
      &#160;&#160;&#160;&#160;eloop.terminate = 1;
    </p>
    <p>
      }
    </p>
  </body>
</html></richcontent>
</node>
<node CREATED="1509519717770" ID="ID_446793597" MODIFIED="1509520325739">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      int <font color="#c60c0c">eloop_register_signa</font>l(int sig, eloop_signal_handler handler,
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;void *user_data)
    </p>
    <p>
      {
    </p>
    <p>
      &#160;&#160;&#160;&#160;struct eloop_signal *tmp;
    </p>
    <p>
      
    </p>
    <p>
      <font color="#c41616">&#160;&#160;&#160;&#160;/** </font>
    </p>
    <p>
      <font color="#c41616">&#160;&#160;&#160;&#160;&#160;* os_realloc_array&#20989;&#25968;&#20316;&#29992;&#35828;&#26126; </font>
    </p>
    <p>
      <font color="#c41616">&#160;&#160;&#160;&#160;&#160;* 1.&#22914;&#26524;eloop.signals &#65281;= NULL&#65292; &#37322;&#25918;eloop.signals&#25351;&#21521;&#30340;&#20869;&#23384;&#31354;&#38388;&#65292; </font>
    </p>
    <p>
      <font color="#c41616">&#160;&#160;&#160;&#160;&#160;* 2.&#24182;&#25226;&#36825;&#27573;&#20869;&#23384;&#30340;&#20869;&#23481;&#22797;&#21046;&#21040;&#26032;&#30003;&#35831;&#30340;(eloop.signal_count + 1)*sizeof(struct eloop_signal)&#30340;&#20869;&#23384;&#31354;&#38388; </font>
    </p>
    <p>
      <font color="#c41616">&#160;&#160;&#160;&#160;&#160;*/</font>
    </p>
    <p>
      &#160;&#160;&#160;&#160;tmp = os_realloc_array(eloop.signals, eloop.signal_count + 1,
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;sizeof(struct eloop_signal));
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (tmp == NULL)
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;return -1;
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;tmp[eloop.signal_count].sig = sig;
    </p>
    <p>
      &#160;&#160;&#160;&#160;tmp[eloop.signal_count].user_data = user_data;
    </p>
    <p>
      &#160;&#160;&#160;&#160;tmp[eloop.signal_count].handler = handler;
    </p>
    <p>
      &#160;&#160;&#160;&#160;tmp[eloop.signal_count].signaled = 0;
    </p>
    <p>
      &#160;&#160;&#160;&#160;eloop.signal_count++;
    </p>
    <p>
      &#160;&#160;&#160;&#160;eloop.signals = tmp;
    </p>
    <p>
      &#160;&#160;&#160;&#160;signal(sig, eloop_handle_signal); //&#35774;&#32622;&#20449;&#21495;&#30340;&#22788;&#29702;&#20989;&#25968;
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;return 0;
    </p>
    <p>
      }
    </p>
    <p>
      &#160;
    </p>
  </body>
</html></richcontent>
</node>
</node>
</node>
<node CREATED="1509520389970" FOLDED="true" ID="ID_1814001832" MODIFIED="1515572724720">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      if (ctrl_ifname == NULL)
    </p>
    <p>
      &#160;&#160;&#160;&#160;//&#30001;&#27492;&#24471;ctrl_ifname=&quot;wlan0&quot;
    </p>
    <p>
      &#160;&#160;&#160;&#160;ctrl_ifname = <font color="#b80909">wpa_cli_get_default_ifname</font>();
    </p>
  </body>
</html></richcontent>
<node CREATED="1509520430826" ID="ID_1410707748" MODIFIED="1509618356652">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      char * wpa_cli_get_default_ifname(void)
    </p>
    <p>
      {
    </p>
    <p>
      &#160;&#160;&#160; <font color="#c30f0f">char *ifname = NULL;</font>
    </p>
    <p>
      
    </p>
    <p>
      #ifdef CONFIG_CTRL_IFACE_UNIX
    </p>
    <p>
      <font color="#c41616">&#160;&#160;&#160;&#160;/** </font>
    </p>
    <p>
      <font color="#c41616">&#160;&#160;&#160;&#160;&#160;*&#160;&#160;&#27492;&#20195;&#30721;&#27573;&#30340;&#20316;&#29992;&#35828;&#26126;:</font>
    </p>
    <p>
      <font color="#c41616">&#160;&#160;&#160;&#160;&#160;*&#160;&#160;&#25171;&#24320;</font><font color="#da0000">/var/run/wpa_supplicant&#65292;&#26597;&#25214;&#27492;&#30446;&#24405;&#19979;&#38750;&quot;.&quot;&#25110;&quot;..&quot;&#30340;&#25991;&#20214;&#65292;</font>
    </p>
    <p>
      <font color="#c41616">&#160;&#160;&#160;&#160;&#160;*&#160; </font><font color="#da0000">&#28982;&#21518;&#20197;&#27492;&#25991;&#20214;&#21517;&#20316;&#20026;&#40664;&#35748;&#30340;i fname</font>
    </p>
    <p>
      <font color="#c41616">&#160;&#160;&#160;&#160;&#160;*/</font>
    </p>
    <p>
      <font color="#da0000">&#160;&#160;&#160;&#160;struct dirent *dent; </font>
    </p>
    <p>
      <font color="#da0000">&#160;&#160;&#160;&#160;DIR *dir = opendir(ctrl_iface_dir); //ctrl_iface_dir=&quot;/var/run/wpa_supplicant&quot; </font>
    </p>
    <p>
      <font color="#da0000">&#160;&#160;&#160;&#160;if (!dir) { </font>
    </p>
    <p>
      <font color="#da0000">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;return NULL; </font>
    </p>
    <p>
      <font color="#da0000">&#160;&#160;&#160;&#160;} </font>
    </p>
    <p>
      
    </p>
    <p>
      <font color="#da0000">&#160;&#160;&#160;&#160;while ((dent = readdir(dir))) {</font>
    </p>
    <p>
      #ifdef _DIRENT_HAVE_D_TYPE
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;/*
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;* Skip the file if it is not a socket. Also accept
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;* DT_UNKNOWN (0) in case the C library or underlying
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;* file system does not support d_type.
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;*/
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;if (dent-&gt;d_type != DT_SOCK &amp;&amp; dent-&gt;d_type != DT_UNKNOWN)
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;continue;
    </p>
    <p>
      #endif /* _DIRENT_HAVE_D_TYPE */
    </p>
    <p>
      <font color="#b01616">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;if (os_strcmp(dent-&gt;d_name, &quot;.&quot;) == 0 || </font>
    </p>
    <p>
      <font color="#b01616">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;os_strcmp(dent-&gt;d_name, &quot;..&quot;) == 0) </font>
    </p>
    <p>
      <font color="#b01616">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;continue; </font>
    </p>
    <p>
      <font color="#b01616">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;printf(&quot;Selected interface '%s'\n&quot;, dent-&gt;d_name); </font>
    </p>
    <p>
      <font color="#b01616">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;ifname = os_strdup(dent-&gt;d_name); </font>
    </p>
    <p>
      <font color="#b01616">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;break;</font>
    </p>
    <p>
      &#160;&#160;&#160;&#160;}
    </p>
    <p>
      &#160;&#160;&#160; <font color="#da1d1d">closedir(dir);</font>
    </p>
    <p>
      #endif /* CONFIG_CTRL_IFACE_UNIX */
    </p>
    <p>
      }
    </p>
  </body>
</html></richcontent>
</node>
</node>
<node CREATED="1509521125155" FOLDED="true" ID="ID_1920906871" MODIFIED="1515572723233">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      if (interactive) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;<font color="#1f0f0f">wpa_cli_interactive(</font>);
    </p>
    <p>
      } else {
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (!global &amp;&amp;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;<font color="#b30707">wpa_cli_open_connection</font><font color="#241616">(ctrl_ifname, 0)&#160;</font>&lt; 0) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;return -1;
    </p>
    <p>
      &#160;&#160;&#160;&#160;}
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;/**
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;* &#27492;&#22788;&#30465;&#30053;&#38750;&#20132;&#20114;&#27169;&#24335;&#19979;&#19981;&#20250;&#25191;&#34892;&#30340;&#20195;&#30721;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;*/
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (action_file)
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;wpa_cli_action(ctrl_conn);
    </p>
    <p>
      &#160;&#160;&#160;&#160;else
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;ret&#160;=<font color="#aa0c0c">&#160;</font><font color="#c51111">wpa_request</font><font color="#180a0a">(ctrl_conn, argc - optind, &amp;argv[optind]);</font>
    </p>
    <p>
      }
    </p>
  </body>
</html></richcontent>
<node CREATED="1509521239923" FOLDED="true" ID="ID_873321641" MODIFIED="1515572718561">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      int wpa_cli_open_connection(const char *ifname, int attach)
    </p>
    <p>
      {
    </p>
    <p>
      &#160;&#160;&#160;&#160;char *cfile = NULL;
    </p>
    <p>
      &#160;&#160;&#160;&#160;int flen, res;
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (ifname == NULL)
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;return -1;
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (client_socket_dir &amp;&amp; client_socket_dir[0] &amp;&amp;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;access(client_socket_dir, F_OK) &lt; 0) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;perror(client_socket_dir);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;os_free(cfile);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;return -1;
    </p>
    <p>
      &#160;&#160;&#160;&#160;}
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (cfile == NULL) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;flen = os_strlen(ctrl_iface_dir) + os_strlen(ifname) + 2; <font color="#1219ed">//&quot;/var/run/wpa_supplicant&quot;&quot;+&quot;wlan0&quot;+2</font>
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;cfile = os_malloc(flen);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;if (cfile == NULL)
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;return -1;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;res = os_snprintf(cfile, flen, &quot;%s/%s&quot;, ctrl_iface_dir, ifname); <font color="#1413ef">//cfile=&quot;/var/run/wpa_supplicant/wlan0&quot;</font>
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;if (os_snprintf_error(flen, res)) {&#160;&#160;//if(res &lt; 0 || res &gt;= flen) error
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;os_free(cfile);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;return -1;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;}
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;ctrl_conn = <font color="#cc0101">wpa_ctrl_open2(cfile, client_socket_dir); // client_socket_dir&#21021;&#22987;&#20540;&#20026;NULL</font>
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (ctrl_conn == NULL) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;os_free(cfile);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;return -1;
    </p>
    <p>
      &#160;&#160;&#160;&#160;}
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (attach &amp;&amp; interactive)
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;mon_conn = wpa_ctrl_open2(cfile, client_socket_dir);
    </p>
    <p>
      &#160;&#160;&#160;&#160;else
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160; <font color="#c50d0d">mon_conn = NULL;</font>
    </p>
    <p>
      &#160;&#160;&#160;&#160;os_free(cfile);
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;/**
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;* &#38750;&#20132;&#20114;&#27169;&#24335;&#20197;&#19979;&#20195;&#30721;&#19981;&#25191;&#34892;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;*/
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (mon_conn) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;if (wpa_ctrl_attach(mon_conn) == 0) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;wpa_cli_attached = 1;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;if (interactive)
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;eloop_register_read_sock(
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;wpa_ctrl_get_fd(mon_conn),
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;wpa_cli_mon_receive, NULL, NULL);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;} else {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;printf(&quot;Warning: Failed to attach to &quot;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&quot;wpa_supplicant.\n&quot;);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;wpa_cli_close_connection();
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;return -1;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;}
    </p>
    <p>
      &#160;&#160;&#160;&#160;}
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;return 0;
    </p>
    <p>
      }
    </p>
  </body>
</html></richcontent>
<node CREATED="1509521972756" ID="ID_1839503552" MODIFIED="1515572714641">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      struct wpa_ctrl * wpa_ctrl_open2(const char *ctrl_path,
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;const char *cli_path)
    </p>
    <p>
      {
    </p>
    <p>
      &#160;&#160;&#160;&#160;struct wpa_ctrl *ctrl;
    </p>
    <p>
      &#160;&#160;&#160; <font color="#1514d5">static int counter = 0;</font>
    </p>
    <p>
      &#160;&#160;&#160;&#160;int ret;
    </p>
    <p>
      &#160;&#160;&#160;&#160;size_t res;
    </p>
    <p>
      &#160;&#160;&#160;&#160;int tries = 0;
    </p>
    <p>
      &#160;&#160;&#160;&#160;int flags;
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (ctrl_path == NULL)
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;return NULL;
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;ctrl = os_zalloc(sizeof(*ctrl));
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (ctrl == NULL)
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;return NULL;
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160; <font color="#c70707">ctrl-&gt;s = socket(PF_UNIX, SOCK_DGRAM, 0);</font>
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (ctrl-&gt;s &lt; 0) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;os_free(ctrl);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;return NULL;
    </p>
    <p>
      &#160;&#160;&#160;&#160;}
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;<font color="#ce1111">ctrl-&gt;local.sun_family = AF_UNIX;</font>
    </p>
    <p>
      &#160;&#160;&#160; <font color="#1208ca">counter++; </font>
    </p>
    <p>
      try_again:
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (cli_path &amp;&amp; cli_path[0] == '/') {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;ret = os_snprintf(ctrl-&gt;local.sun_path,
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;sizeof(ctrl-&gt;local.sun_path),
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&quot;%s/&quot; CONFIG_CTRL_IFACE_CLIENT_PREFIX &quot;%d-%d&quot;,
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;cli_path, (int) getpid(), counter);
    </p>
    <p>
      &#160;&#160;&#160;&#160;}<font color="#120808">&#160;else { </font>
    </p>
    <p>
      <font color="#d10606">&#160;&#160;&#160;&#160;&#160;&#160;&#160;/** </font>
    </p>
    <p>
      <font color="#d10606">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;* client_socket_dir=NULL, &#25152;&#20197;&#22312;/tmp/&#30446;&#24405;&#19979; </font>
    </p>
    <p>
      <font color="#d10606">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;* &#21019;&#24314;UNIX domain socket&#25991;&#20214; </font>
    </p>
    <p>
      <font color="#d10606">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;*/ </font>
    </p>
    <p>
      <font color="#d21010">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;ret = os_snprintf(ctrl-&gt;local.sun_path, </font>
    </p>
    <p>
      <font color="#d21010">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;sizeof(ctrl-&gt;local.sun_path), </font>
    </p>
    <p>
      <font color="#d21010">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;CONFIG_CTRL_IFACE_CLIENT_DIR &quot;/&quot; </font>
    </p>
    <p>
      <font color="#d21010">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;CONFIG_CTRL_IFACE_CLIENT_PREFIX &quot;%d-%d&quot;, </font>
    </p>
    <p>
      <font color="#d21010">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;(int) getpid(), counter);</font>
    </p>
    <p>
      <font color="#120808">&#160;&#160;&#160;&#160;}</font>
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (os_snprintf_error(sizeof(ctrl-&gt;local.sun_path), ret)) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;close(ctrl-&gt;s);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;os_free(ctrl);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;return NULL;
    </p>
    <p>
      &#160;&#160;&#160;&#160;}
    </p>
    <p>
      &#160;&#160;&#160;&#160;tries++;
    </p>
    <p>
      <font color="#211ac9">&#160;&#160;&#160;&#160;/** </font>
    </p>
    <p>
      <font color="#211ac9">&#160;&#160;&#160;&#160;&#160;&#160;* &#35843;&#29992;bind()&#21019;&#24314;&#33258;&#24049;&#30340;</font><font color="#1e34da">UNIX domain socket</font><font color="#211ac9">&#25991;&#20214;&#65292; </font>
    </p>
    <p>
      <font color="#211ac9">&#160;&#160;&#160;&#160;&#160;&#160;* wpa_cli &#21487;&#20197;&#36890;&#36807;&#27492;socket&#25991;&#20214;&#25509;&#25910;&#25968;&#25454;</font>
    </p>
    <p>
      <font color="#211ac9">&#160;&#160;&#160;&#160;&#160;&#160;* &#22914;&#26524;&#27492;&#25991;&#20214;&#24050;&#32463;&#23384;&#22312;&#65292;&#21017;bind()&#38169;&#35823;&#36820;&#22238; </font>
    </p>
    <p>
      <font color="#211ac9">&#160;&#160;&#160;&#160;&#160;&#160;*/</font>
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (<font color="#b51515">bind(ctrl-&gt;s, (struct sockaddr *) &amp;ctrl-&gt;local, sizeof(ctrl-&gt;local))</font>&#160;&#160;&lt; 0) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;if (errno == EADDRINUSE &amp;&amp; tries &lt; 2) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;/**
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;* getpid() returns unique identifier for this instance
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;* of wpa_ctrl, so the existing socket file must have
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;* been left by unclean termination of an earlier run.
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;* Remove the file and try again.
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;*/
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;unlink(ctrl-&gt;local.sun_path);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;goto try_again;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;}
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;close(ctrl-&gt;s);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;os_free(ctrl);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;return NULL;
    </p>
    <p>
      &#160;&#160;&#160;&#160;}
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;/*********************************************/
    </p>
    <p>
      &#160;&#160;&#160; <font color="#d60d0d">ctrl-&gt;dest.sun_family = AF_UNIX;</font>
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (os_strncmp(ctrl_path, &quot;@abstract:&quot;, 10) == 0) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;ctrl-&gt;dest.sun_path[0] = '\0';
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;os_strlcpy(ctrl-&gt;dest.sun_path + 1, ctrl_path + 10,
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;sizeof(ctrl-&gt;dest.sun_path) - 1);
    </p>
    <p>
      &#160;&#160;&#160;&#160;} else {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;/* *
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;* <font color="#c91111">ctrl-&gt;dest.sun_path = </font><font color="#1413ef">&quot;/var/run/wpa_supplicant/wlan0&quot; </font>
    </p>
    <p>
      <font color="#1413ef">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;*/</font>
    </p>
    <p>
      <font color="#c91111">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;res = os_strlcpy(ctrl-&gt;dest.sun_path, ctrl_path, sizeof(ctrl-&gt;dest.sun_path)); </font>
    </p>
    <p>
      <font color="#1b0b0b">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;if (res &gt;= sizeof(ctrl-&gt;dest.sun_path)) { </font>
    </p>
    <p>
      <font color="#1b0b0b">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;close(ctrl-&gt;s); </font>
    </p>
    <p>
      <font color="#1b0b0b">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;os_free(ctrl); </font>
    </p>
    <p>
      <font color="#1b0b0b">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;return NULL; </font>
    </p>
    <p>
      <font color="#1b0b0b">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;}</font>
    </p>
    <p>
      &#160;&#160;&#160;&#160;}
    </p>
    <p>
      <font color="#1e34da">&#160;&#160;&#160;&#160;/** </font>
    </p>
    <p>
      <font color="#1e34da">&#160;&#160;&#160;&#160;&#160;* &#35843;&#29992; connect() &#20989;&#25968;&#38142;&#25509;&#19982; wpa_supplicant &#36890;&#20449; </font>
    </p>
    <p>
      <font color="#1e34da">&#160;&#160;&#160;&#160;&#160;* &#30340;UNIX Domain Socket </font>
    </p>
    <p>
      <font color="#1e34da">&#160;&#160;&#160;&#160;&#160;*/</font>
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (<font color="#e81b1b">connect(ctrl-&gt;s, (struct sockaddr *) &amp;ctrl-&gt;dest, sizeof(ctrl-&gt;dest))</font>&#160;&#160;&lt; 0) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;close(ctrl-&gt;s);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;unlink(ctrl-&gt;local.sun_path);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;os_free(ctrl);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;return NULL;
    </p>
    <p>
      &#160;&#160;&#160;&#160;}
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;/*
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;* Make socket non-blocking so that we don't hang forever if
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;* target dies unexpectedly.
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;*/
    </p>
    <p>
      &#160;&#160;&#160; <font color="#bb1b1b">flags = fcntl(ctrl-&gt;s, F_GETFL);</font>
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (flags &gt;= 0) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;flags |= O_NONBLOCK;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;if (fcntl(ctrl-&gt;s, F_SETFL, flags) &lt; 0) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;perror(&quot;fcntl(ctrl-&gt;s, O_NONBLOCK)&quot;);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;/* Not fatal, continue on.*/
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;}
    </p>
    <p>
      &#160;&#160;&#160;&#160;}
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;return ctrl;
    </p>
    <p>
      }
    </p>
  </body>
</html>
</richcontent>
</node>
</node>
<node CREATED="1509539097158" ID="ID_1593777076" MODIFIED="1509586987378">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      int wpa_request(struct wpa_ctrl *ctrl, int argc, char *argv[])
    </p>
    <p>
      {
    </p>
    <p>
      &#160;&#160;&#160;&#160;const struct wpa_cli_cmd *cmd, *match = NULL;
    </p>
    <p>
      &#160;&#160;&#160;&#160;int count;
    </p>
    <p>
      &#160;&#160;&#160;&#160;int ret = 0;
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;/**
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;* &#27492;&#22788;&#30340;&#20316;&#29992;&#26242;&#26102;&#27809;&#29702;&#35299;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;*/
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (argc &gt; 1 &amp;&amp; os_strncasecmp(argv[0], &quot;IFNAME=&quot;, 7) == 0) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;ifname_prefix = argv[0] + 7;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;argv = &amp;argv[1];
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;argc--;
    </p>
    <p>
      &#160;&#160;&#160;&#160;} else
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;ifname_prefix = NULL;
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (argc == 0)
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;return -1;
    </p>
    <p>
      
    </p>
    <p>
      <font color="#b11111">&#160;&#160;&#160;&#160;/** </font>
    </p>
    <p>
      <font color="#b11111">&#160;&#160;&#160;&#160;&#160;* &#36941;&#21382;&#21629;&#20196;&#34920;&#26597;&#25214;&#26159;&#21542;&#21305;&#37197;&#36755;&#20837;&#30340;&#21629;&#20196;&#65292;&#21487;&#27169;&#31946;&#21305;&#37197;&#65292;&#20294;&#24517;&#39035;&#26159;&#21807;&#19968;&#21305;&#37197; </font>
    </p>
    <p>
      <font color="#b11111">&#160;&#160;&#160;&#160;&#160;*/ </font>
    </p>
    <p>
      <font color="#b11111">&#160;&#160;&#160;&#160;count = 0; </font>
    </p>
    <p>
      <font color="#b11111">&#160;&#160;&#160;&#160;cmd = wpa_cli_commands;</font>
    </p>
    <p>
      <font color="#ad1818">&#160;&#160;&#160;&#160;while (cmd-&gt;cmd) { </font>
    </p>
    <p>
      <font color="#ad1818">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;if (os_strncasecmp(cmd-&gt;cmd, argv[0], os_strlen(argv[0])) == 0) </font>
    </p>
    <p>
      <font color="#ad1818">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;{ </font>
    </p>
    <p>
      <font color="#ad1818">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;match = cmd; </font>
    </p>
    <p>
      <font color="#ad1818">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;if (os_strcasecmp(cmd-&gt;cmd, argv[0]) == 0) { </font>
    </p>
    <p>
      <font color="#ad1818">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;/* we have an exact match */ </font>
    </p>
    <p>
      <font color="#ad1818">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;count = 1; </font>
    </p>
    <p>
      <font color="#ad1818">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;break; </font>
    </p>
    <p>
      <font color="#ad1818">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;} </font>
    </p>
    <p>
      <font color="#ad1818">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;count++; </font>
    </p>
    <p>
      <font color="#ad1818">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;} </font>
    </p>
    <p>
      <font color="#ad1818">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;cmd++; </font>
    </p>
    <p>
      <font color="#ad1818">&#160;&#160;&#160;&#160;} </font>
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;/**
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;* &#27169;&#31946;&#21305;&#37197;&#21040;&#22810;&#20010;&#21629;&#20196;&#65292;&#25171;&#21360;&#20986;&#21305;&#37197;&#21040;&#30340;&#21629;&#20196;&#65292;&#28982;&#21518;&#36864;&#20986;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;*/
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (count &gt; 1) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;printf(&quot;Ambiguous command '%s'; possible commands:&quot;, argv[0]);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;cmd = wpa_cli_commands;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;while (cmd-&gt;cmd) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;if (os_strncasecmp(cmd-&gt;cmd, argv[0],
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;os_strlen(argv[0])) == 0) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;printf(&quot; %s&quot;, cmd-&gt;cmd);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;}
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;cmd++;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;}
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;printf(&quot;\n&quot;);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;ret = 1;
    </p>
    <p>
      &#160;&#160;&#160;&#160;} else if (count == 0) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;/**
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;* &#21305;&#37197;&#19981;&#21040;&#21629;&#20196;&#65292;&#25171;&#21360;&#20986;&#36755;&#20837;&#30340;&#21629;&#20196;&#65292;&#28982;&#21518;&#36864;&#20986;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;*/
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;printf(&quot;Unknown command '%s'\n&quot;, argv[0]);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;ret = 1;
    </p>
    <p>
      &#160;&#160;&#160;&#160;} else {
    </p>
    <p>
      <font color="#bc0202">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;/** </font>
    </p>
    <p>
      <font color="#bc0202">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;* &#21305;&#37197;&#21040;&#21807;&#19968;&#30340;&#21629;&#20196;&#65292;&#35843;&#29992;&#21629;&#20196;&#30340;handler&#20989;&#25968;&#26469;&#25191;&#34892;&#21629;&#20196; </font>
    </p>
    <p>
      <font color="#bc0202">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;*/</font>
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160; <font color="#b30b0b">ret = match-&gt;handler(ctrl, argc - 1, &amp;argv[1]);</font>
    </p>
    <p>
      &#160;&#160;&#160;&#160;}
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;return ret;
    </p>
    <p>
      }
    </p>
  </body>
</html></richcontent>
</node>
<node CREATED="1509587530751" FOLDED="true" ID="ID_1046905150" MODIFIED="1515572447624">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      &#20197; wpa_cli status &#20026;&#20363;&#20998;&#26512;&#21629;&#20196;&#25191;&#34892;&#36807;&#31243;:
    </p>
    <p>
      static int wpa_cli_cmd_status(struct wpa_ctrl *ctrl, int argc, char *argv[])
    </p>
    <p>
      {
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (argc &gt; 0 &amp;&amp; os_strcmp(argv[0], &quot;verbose&quot;) == 0)
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;return wpa_ctrl_command(ctrl, &quot;STATUS-VERBOSE&quot;);
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (argc &gt; 0 &amp;&amp; os_strcmp(argv[0], &quot;wps&quot;) == 0)
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;return wpa_ctrl_command(ctrl, &quot;STATUS-WPS&quot;);
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (argc &gt; 0 &amp;&amp; os_strcmp(argv[0], &quot;driver&quot;) == 0)
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;return wpa_ctrl_command(ctrl, &quot;STATUS-DRIVER&quot;);
    </p>
    <p>
      #ifdef ANDROID
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (argc &gt; 0 &amp;&amp; os_strcmp(argv[0], &quot;no_events&quot;) == 0)
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;return wpa_ctrl_command(ctrl, &quot;STATUS-NO_EVENTS&quot;);
    </p>
    <p>
      #endif /* ANDROID */
    </p>
    <p>
      &#160;&#160;&#160;&#160;return<font color="#c21818">&#160;wpa_ctrl_command(ctrl, &quot;STATUS&quot;);</font>
    </p>
    <p>
      }
    </p>
  </body>
</html></richcontent>
<node CREATED="1509594894663" FOLDED="true" ID="ID_1681299983" MODIFIED="1515572446872">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      int wpa_ctrl_command(struct wpa_ctrl *ctrl, char *cmd)
    </p>
    <p>
      {
    </p>
    <p>
      &#160;&#160;&#160;&#160;return <font color="#bd1515">_wpa_ctrl_command(ctrl, cmd, 1);</font>
    </p>
    <p>
      }
    </p>
    <p>
      
    </p>
    <p>
      int <font color="#ba0404">_wpa_ctrl_command</font>(struct wpa_ctrl *ctrl, char *cmd, int print)
    </p>
    <p>
      {
    </p>
    <p>
      &#160;&#160;&#160;&#160;char buf[4096];
    </p>
    <p>
      &#160;&#160;&#160;&#160;size_t len;
    </p>
    <p>
      &#160;&#160;&#160;&#160;int ret;
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;/**
    </p>
    <p>
      &#160;&#160;&#160;&#160;* &#22914;&#26524;ctrl_conn&#27809;&#26377;&#21021;&#22987;&#21270;&#65292;&#30452;&#25509;&#36864;&#20986;
    </p>
    <p>
      &#160;&#160;&#160;&#160;*/
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (ctrl_conn == NULL) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;printf(&quot;Not connected to wpa_supplicant - command dropped.\n&quot;);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;return -1;
    </p>
    <p>
      &#160;&#160;&#160;&#160;}
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (ifname_prefix) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;os_snprintf(buf, sizeof(buf), &quot;IFNAME=%s %s&quot;,
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;ifname_prefix, cmd);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;buf[sizeof(buf) - 1] = '\0';
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;cmd = buf;
    </p>
    <p>
      &#160;&#160;&#160;&#160;}
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;len = sizeof(buf) - 1;
    </p>
    <p>
      &#160;&#160;&#160;&#160;/**
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;* <font color="#cd1515">wpa_cli_msg_cb</font>&#160;&#26159;&#22788;&#29702;wpa_supplicant&#30340;&#38750;&#21709;&#24212;&#21629;&#20196;&#20449;&#24687;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;* &#40664;&#35748;&#22788;&#29702;&#26041;&#24335;&#26159;&#30452;&#25509;&#21521;&#32456;&#31471;&#25171;&#21360;&#20986;&#36825;&#20123;&#20449;&#24687;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;*/
    </p>
    <p>
      &#160;&#160;&#160;&#160;ret = <font color="#c90d0d">wpa_ctrl_request</font>(ctrl, cmd, os_strlen(cmd), <font color="#223bec">buf, &amp;len</font>, <font color="#cd1515">wpa_cli_msg_cb</font>);
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (ret == -2) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;printf(&quot;'%s' command timed out.\n&quot;, cmd);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;return -2;
    </p>
    <p>
      &#160;&#160;&#160;&#160;} else if (ret &lt; 0) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;printf(&quot;'%s' command failed.\n&quot;, cmd);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;return -1;
    </p>
    <p>
      &#160;&#160;&#160;&#160;}
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (print) {
    </p>
    <p>
      <font color="#ca0404">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;/** </font>
    </p>
    <p>
      <font color="#ca0404">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;* &#25171;&#21360;wpa_supplicant&#30456;&#24212;&#21629;&#20196;&#35831;&#27714;&#30340;&#32467;&#26524; </font>
    </p>
    <p>
      <font color="#ca0404">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;*/</font>
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;buf[len] = '\0';
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;printf(&quot;%s&quot;, buf);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;if (interactive &amp;&amp; len &gt; 0 &amp;&amp; buf[len - 1] != '\n')
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;printf(&quot;\n&quot;);
    </p>
    <p>
      &#160;&#160;&#160;&#160;}
    </p>
    <p>
      &#160;&#160;&#160;&#160;return 0;
    </p>
    <p>
      }
    </p>
  </body>
</html></richcontent>
<node CREATED="1509596786929" ID="ID_836679300" MODIFIED="1509612205895">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      int wpa_ctrl_request(struct wpa_ctrl *ctrl, const char *cmd, size_t cmd_len,
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;char *reply, size_t *reply_len,
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;void (*msg_cb)(char *msg, size_t len))
    </p>
    <p>
      {
    </p>
    <p>
      &#160;&#160;&#160;&#160;struct timeval tv;
    </p>
    <p>
      &#160;&#160;&#160;&#160;struct os_reltime started_at;
    </p>
    <p>
      &#160;&#160;&#160;&#160;int res;
    </p>
    <p>
      &#160;&#160;&#160;&#160;fd_set rfds;
    </p>
    <p>
      &#160;&#160;&#160;&#160;const char *_cmd;
    </p>
    <p>
      &#160;&#160;&#160;&#160;char *cmd_buf = NULL;
    </p>
    <p>
      &#160;&#160;&#160;&#160;size_t _cmd_len;
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;/**
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;* CONFIG_CTRL_IFACE_UDP&#27809;&#26377;&#23450;&#20041;&#65292;&#20197;&#19979;&#20195;&#30721;&#19981;&#25191;&#34892;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;*/
    </p>
    <p>
      #ifdef CONFIG_CTRL_IFACE_UDP
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (ctrl-&gt;cookie) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;char *pos;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;_cmd_len = os_strlen(ctrl-&gt;cookie) + 1 + cmd_len;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;cmd_buf = os_malloc(_cmd_len);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;if (cmd_buf == NULL)
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;return -1;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;_cmd = cmd_buf;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;pos = cmd_buf;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;os_strlcpy(pos, ctrl-&gt;cookie, _cmd_len);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;pos += os_strlen(ctrl-&gt;cookie);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;*pos++ = ' ';
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;os_memcpy(pos, cmd, cmd_len);
    </p>
    <p>
      &#160;&#160;&#160;&#160;} else
    </p>
    <p>
      #endif /* CONFIG_CTRL_IFACE_UDP */
    </p>
    <p>
      &#160;&#160;&#160;&#160;{
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;_cmd = cmd;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;_cmd_len = cmd_len;
    </p>
    <p>
      &#160;&#160;&#160;&#160;}
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;errno = 0;
    </p>
    <p>
      &#160;&#160;&#160;&#160;started_at.sec = 0;
    </p>
    <p>
      &#160;&#160;&#160;&#160;started_at.usec = 0;
    </p>
    <p>
      
    </p>
    <p>
      <font color="#cf1717">retry_send:</font>
    </p>
    <p>
      <font color="#c30b0b">&#160;&#160;&#160;&#160;/** </font>
    </p>
    <p>
      <font color="#c30b0b">&#160;&#160;&#160;&#160;&#160;* &#35843;&#29992; send() &#20989;&#25968;&#21457;&#36865;&#21629;&#20196;&#65292;&#21629;&#20196;&#30340;&#25509;&#25910;&#32773;&#26159;wpa_supplicant</font>
    </p>
    <p>
      <font color="#c30b0b">&#160;&#160;&#160;&#160;&#160;*/</font>
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (<font color="#cf1010">send(ctrl-&gt;s, _cmd, _cmd_len, 0)</font>&#160;&lt; 0) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;if (errno == EAGAIN || errno == EBUSY || errno == EWOULDBLOCK)
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;{
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;/*
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;* Must be a non-blocking socket... Try for a bit
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;* longer before giving up.
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;*/
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;if (started_at.sec == 0)
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;os_get_reltime(&amp;started_at); //send()&#31532;&#19968;&#27425;&#22833;&#36133;&#65292;&#33719;&#21462;&#31995;&#32479;&#23454;&#26102;&#26102;&#38047;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;else {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;struct os_reltime n;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;os_get_reltime(&amp;n); //send()&#20877;&#27425;&#22833;&#36133;&#65292;&#33719;&#21462;&#31995;&#32479;&#23454;&#26102;&#26102;&#38047;
    </p>
    <p>
      &#160;<font color="#cb0b0b">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;/** </font>
    </p>
    <p>
      <font color="#cb0b0b">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;* Try for a few seconds. </font>
    </p>
    <p>
      <font color="#cb0b0b">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;* &#22914;&#26524;&#36317;&#31532;&#19968;&#27425;send()&#22833;&#36133;&#36229;&#36807;5s&#65292;&#21017;&#36864;&#20986;&#21457;&#36865; </font>
    </p>
    <p>
      <font color="#cb0b0b">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;*/</font>
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;if (os_reltime_expired(&amp;n, &amp;started_at, 5))
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160; <font color="#2e18ec">goto send_err;</font>
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;}
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;os_sleep(1, 0); //&#30561;&#30496;1s&#21518;&#20877;&#23581;&#35797;send()
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160; <font color="#de1515">goto retry_send;</font>
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;}
    </p>
    <p>
      &#160;&#160;&#160; <font color="#1b1fec">send_err</font>:
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;os_free(cmd_buf);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;return -1;
    </p>
    <p>
      &#160;&#160;&#160;&#160;}
    </p>
    <p>
      &#160;&#160;&#160;&#160;os_free(cmd_buf);
    </p>
    <p>
      
    </p>
    <p>
      <font color="#ea1111">&#160;&#160;&#160;&#160;/** </font>
    </p>
    <p>
      <font color="#ea1111">&#160;&#160;&#160;&#160;&#160;* &#25104;&#21151;&#21521;wpa_supplicant&#21457;&#36865;&#21629;&#20196;&#21518;&#65292;&#36827;&#20837;&#25509;&#25910;&#27169;&#24335; </font>
    </p>
    <p>
      <font color="#ea1111">&#160;&#160;&#160;&#160;&#160;*/</font>
    </p>
    <p>
      &#160;&#160;&#160;&#160;for (;;) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;tv.tv_sec = 10;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;tv.tv_usec = 0;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;FD_ZERO(&amp;rfds);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;FD_SET(ctrl-&gt;s, &amp;rfds);
    </p>
    <p>
      <font color="#d80f0f">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;/** </font>
    </p>
    <p>
      <font color="#d80f0f">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;* select()&#31561;&#24453; </font>
    </p>
    <p>
      <font color="#d80f0f">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;*/</font>
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;res = select(ctrl-&gt;s + 1, &amp;rfds, NULL, NULL, &amp;tv);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;if (res &lt; 0 &amp;&amp; errno == EINTR)
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;continue;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;if (res &lt; 0)
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;return res;
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;if (FD_ISSET(ctrl-&gt;s, &amp;rfds)) {
    </p>
    <p>
      <font color="#d80606">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;/** </font>
    </p>
    <p>
      <font color="#d80606">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;* &#35843;&#29992;recv()&#24320;&#22987;&#25509;&#25910;wpa_supplicant&#30340;&#22238;&#24212;&#25968;&#25454;, &#36820;&#22238;&#25509;&#25910;&#30340;&#23383;&#33410;&#25968; </font>
    </p>
    <p>
      <font color="#d80606">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;*/ </font>
    </p>
    <p>
      <font color="#d80606">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;res = recv(ctrl-&gt;s, reply, *reply_len, 0);</font>
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;if (res &lt; 0)
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;return res;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;if (res &gt; 0 &amp;&amp; reply[0] == '&lt;') {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;/* This is an unsolicited message from
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;* wpa_supplicant, not the reply to the request.
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;* Use msg_cb to report this to the caller. */
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;if (msg_cb) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;if ((size_t) res == *reply_len)
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;res = (*reply_len) - 1;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;reply[res] = '\0';
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;<font color="#c90d0d">&#160;msg_cb(reply, res); //&#21521;&#32456;&#31471;&#25171;&#21360;&#20986;wpa_supplicant&#20027;&#21160;&#25552;&#20379;&#30340;&#20449;&#24687;</font>
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;}
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;<font color="#1e2bdf">&#160;continue; //&#32487;&#32493;&#20174;wpa_supplicant&#25509;&#25910;&#21629;&#20196;&#30340;&#22238;&#22797;&#20449;&#24687;</font>
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;}
    </p>
    <p>
      
    </p>
    <p>
      <font color="#c00a0a">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;/** </font>
    </p>
    <p>
      <font color="#c00a0a">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;* &#25104;&#21151;&#25509;&#25910;&#21040;&#21629;&#20196;&#30340;&#22238;&#22797;&#20449;&#24687;&#65292; </font>
    </p>
    <p>
      <font color="#c00a0a">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;* &#36820;&#22238;&#25509;&#25910;&#20449;&#24687;&#30340;&#38271;&#24230;&#65292;&#24182;&#36864;&#20986; </font>
    </p>
    <p>
      <font color="#c00a0a">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;*/ </font>
    </p>
    <p>
      <font color="#c00a0a">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;*reply_len = res; </font>
    </p>
    <p>
      <font color="#c00a0a">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;break;</font>
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;} else {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;return -2;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;}
    </p>
    <p>
      &#160;&#160;&#160;&#160;}
    </p>
    <p>
      &#160;&#160;&#160;&#160;return 0;
    </p>
    <p>
      }
    </p>
  </body>
</html></richcontent>
</node>
</node>
</node>
</node>
<node CREATED="1509539145638" FOLDED="true" ID="ID_1673028899" MODIFIED="1509620068603">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      /**
    </p>
    <p>
      &#160;* wpa_cli &#31243;&#24207;&#36864;&#20986;&#21069;&#30340;&#22788;&#29702;
    </p>
    <p>
      &#160;*/
    </p>
    <p>
      os_free(ctrl_ifname); //&#37322;&#25918; os_strdup() &#20998;&#37197;&#30340;&#20869;&#23384;&#31354;&#38388;
    </p>
    <p>
      eloop_destroy();&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;//&#36825;&#20989;&#25968;&#23545;&#24212;eloop_init()
    </p>
    <p>
      wpa_cli_cleanup();
    </p>
  </body>
</html></richcontent>
<node CREATED="1509608616702" ID="ID_1159964370" MODIFIED="1509614987625">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      void eloop_destroy(void)
    </p>
    <p>
      {
    </p>
    <p>
      &#160;&#160;&#160;&#160;struct eloop_timeout *timeout, *prev;
    </p>
    <p>
      &#160;&#160;&#160;&#160;struct os_reltime now;
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;os_get_reltime(&amp;now);
    </p>
    <p>
      <font color="#cf1717">&#160;&#160;&#160;&#160;/** </font>
    </p>
    <p>
      <font color="#cf1717">&#160;&#160;&#160;&#160;&#160;* &#36941;&#21382; struct eloop_timeout &#38142;&#34920;, &#26597;&#25214;&#36229;&#26102;&#20107;&#20214; </font>
    </p>
    <p>
      <font color="#cf1717">&#160;&#160;&#160;&#160;&#160;* &#22312;&#38750;&#20132;&#20114;&#27169;&#24335;&#19979;, &#36825;&#20010;&#38142;&#34920;&#26159;NULL, &#36825;&#27573;&#20195;&#30721;&#19981;&#25191;&#34892; </font>
    </p>
    <p>
      <font color="#cf1717">&#160;&#160;&#160;&#160;&#160;*/</font>
    </p>
    <p>
      &#160;&#160;&#160;&#160;dl_list_for_each_safe(timeout, prev, &amp;eloop.timeout,
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;struct eloop_timeout, list) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;int sec, usec;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;sec = timeout-&gt;time.sec - now.sec;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;usec = timeout-&gt;time.usec - now.usec;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;if (timeout-&gt;time.usec &lt; now.usec) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;sec--;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;usec += 1000000;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;}
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;wpa_printf(MSG_INFO, &quot;ELOOP: remaining timeout: %d.%06d &quot;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&quot;eloop_data=%p user_data=%p handler=%p&quot;,
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;sec, usec, timeout-&gt;eloop_data, timeout-&gt;user_data,
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;timeout-&gt;handler);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;wpa_trace_dump_funcname(&quot;eloop unregistered timeout handler&quot;,
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;timeout-&gt;handler);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;wpa_trace_dump(&quot;eloop timeout&quot;, timeout);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;eloop_remove_timeout(timeout);
    </p>
    <p>
      &#160;&#160;&#160;&#160;}
    </p>
    <p>
      &#160;&#160;&#160;&#160;eloop_sock_table_destroy(&amp;eloop.readers);
    </p>
    <p>
      &#160;&#160;&#160;&#160;eloop_sock_table_destroy(&amp;eloop.writers);
    </p>
    <p>
      &#160;&#160;&#160;&#160;eloop_sock_table_destroy(&amp;eloop.exceptions);
    </p>
    <p>
      <font color="#bf0b0b">&#160;&#160;&#160;&#160;/** </font>
    </p>
    <p>
      <font color="#bf0b0b">&#160;&#160;&#160;&#160;&#160;* &#37322;&#25918;eloop.signals&#25351;&#21521;&#30340;&#20869;&#23384;&#31354;&#38388;&#65292;&#22312;eloop_register_signal_terminate()&#20013;&#30003;&#35831; </font>
    </p>
    <p>
      <font color="#bf0b0b">&#160;&#160;&#160;&#160;&#160;*/ </font>
    </p>
    <p>
      <font color="#bf0b0b">&#160;&#160;&#160;&#160;os_free(eloop.signals);</font>
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;/**
    </p>
    <p>
      &#160;&#160;&#160;&#160;* &#20197;&#19979;&#23439;&#37117;&#27809;&#26377;&#23450;&#20041;, &#36825;&#27573;&#20195;&#30721;&#19981;&#25191;&#34892;
    </p>
    <p>
      &#160;&#160;&#160;&#160;*/
    </p>
    <p>
      #ifdef CONFIG_ELOOP_POLL
    </p>
    <p>
      &#160;&#160;&#160;&#160;os_free(eloop.pollfds);
    </p>
    <p>
      &#160;&#160;&#160;&#160;os_free(eloop.pollfds_map);
    </p>
    <p>
      #endif /* CONFIG_ELOOP_POLL */
    </p>
    <p>
      #if defined(CONFIG_ELOOP_EPOLL) || defined(CONFIG_ELOOP_KQUEUE)
    </p>
    <p>
      &#160;&#160;&#160;&#160;os_free(eloop.fd_table);
    </p>
    <p>
      #endif /* CONFIG_ELOOP_EPOLL || CONFIG_ELOOP_KQUEUE */
    </p>
    <p>
      #ifdef CONFIG_ELOOP_EPOLL
    </p>
    <p>
      &#160;&#160;&#160;&#160;os_free(eloop.epoll_events);
    </p>
    <p>
      &#160;&#160;&#160;&#160;close(eloop.epollfd);
    </p>
    <p>
      #endif /* CONFIG_ELOOP_EPOLL */
    </p>
    <p>
      #ifdef CONFIG_ELOOP_KQUEUE
    </p>
    <p>
      &#160;&#160;&#160;&#160;os_free(eloop.kqueue_events);
    </p>
    <p>
      &#160;&#160;&#160;&#160;close(eloop.kqueuefd);
    </p>
    <p>
      #endif /* CONFIG_ELOOP_KQUEUE */
    </p>
    <p>
      }
    </p>
  </body>
</html></richcontent>
</node>
<node CREATED="1509608619983" ID="ID_648755181" MODIFIED="1509615030057">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      wpa_cli_cleanup(void)
    </p>
    <p>
      {
    </p>
    <p>
      &#160;&#160;&#160;&#160;wpa_cli_close_connection();
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (pid_file)
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;os_daemonize_terminate(pid_file);
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;os_program_deinit();
    </p>
    <p>
      }
    </p>
  </body>
</html></richcontent>
<node CREATED="1509615033734" ID="ID_878657949" MODIFIED="1509618145123">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      void wpa_cli_close_connection(void)
    </p>
    <p>
      {
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (ctrl_conn == NULL)
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;return;
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;/**
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;* &#38750;&#20132;&#20114;&#27169;&#24335;wpa_cli_attached=0
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;*/
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (wpa_cli_attached) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;wpa_ctrl_detach(interactive ? mon_conn : ctrl_conn);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;wpa_cli_attached = 0;
    </p>
    <p>
      &#160;&#160;&#160;&#160;}
    </p>
    <p>
      
    </p>
    <p>
      <font color="#d31414">&#160;&#160;&#160;&#160;/** </font>
    </p>
    <p>
      <font color="#d31414">&#160;&#160;&#160;&#160;&#160;* &#23545;&#24212;&#20110;wpa_ctrl_open2()&#20989;&#25968;, &#20316;&#29992;:</font>
    </p>
    <p>
      <font color="#d31414">&#160;&#160;&#160;&#160;&#160;* 1.&#21024;&#38500;bind()&#21019;&#24314;&#30340;UNIX Domain Socket&#25991;&#20214; </font>
    </p>
    <p>
      <font color="#d31414">&#160;&#160;&#160;&#160;&#160;* 2.&#20851;&#38381;ctrl_conn&#20013;&#30340;sock&#25991;&#20214; </font>
    </p>
    <p>
      <font color="#d31414">&#160;&#160;&#160;&#160;&#160;* 3.&#37322;&#25918;ctrl_conn&#25351;&#21521;&#30340;&#20869;&#23384;&#31354;&#38388; </font>
    </p>
    <p>
      <font color="#d31414">&#160;&#160;&#160;&#160;&#160;*/ </font>
    </p>
    <p>
      <font color="#d31414">&#160;&#160;&#160;&#160;wpa_ctrl_close(ctrl_conn); </font>
    </p>
    <p>
      <font color="#d31414">&#160;&#160;&#160;&#160;ctrl_conn = NULL;</font>
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;/**
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;* &#38750;&#20132;&#20114;&#27169;&#24335;mon_conn=NULL
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;*/
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (mon_conn) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;eloop_unregister_read_sock(wpa_ctrl_get_fd(mon_conn));
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;wpa_ctrl_close(mon_conn);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;mon_conn = NULL;
    </p>
    <p>
      &#160;&#160;&#160;&#160;}
    </p>
    <p>
      }
    </p>
  </body>
</html></richcontent>
<node CREATED="1509615362046" ID="ID_1851751144" MODIFIED="1509615376583">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      void wpa_ctrl_close(struct wpa_ctrl *ctrl)
    </p>
    <p>
      {
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (ctrl == NULL)
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;return;
    </p>
    <p>
      &#160;&#160;&#160;&#160;unlink(ctrl-&gt;local.sun_path);
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (ctrl-&gt;s &gt;= 0)
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;close(ctrl-&gt;s);
    </p>
    <p>
      &#160;&#160;&#160;&#160;os_free(ctrl);
    </p>
    <p>
      }
    </p>
  </body>
</html></richcontent>
</node>
</node>
<node CREATED="1509616066127" ID="ID_429820278" MODIFIED="1509616146777">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      void os_program_deinit(void)
    </p>
    <p>
      {
    </p>
    <p>
      &#160;&#160;&#160;&#160;/**
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;* WPA_TRACE &#20026;&#23450;&#20041;, &#20197;&#19979;&#20195;&#30721;&#27573;&#19981;&#25191;&#34892;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;*/
    </p>
    <p>
      #ifdef WPA_TRACE
    </p>
    <p>
      &#160;&#160;&#160;&#160;struct os_alloc_trace *a;
    </p>
    <p>
      &#160;&#160;&#160;&#160;unsigned long total = 0;
    </p>
    <p>
      &#160;&#160;&#160;&#160;dl_list_for_each(a, &amp;alloc_list, struct os_alloc_trace, list) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;total += a-&gt;len;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;if (a-&gt;magic != ALLOC_MAGIC) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;wpa_printf(MSG_INFO, &quot;MEMLEAK[%p]: invalid magic 0x%x &quot;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&quot;len %lu&quot;,
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;a, a-&gt;magic, (unsigned long) a-&gt;len);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;continue;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;}
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;wpa_printf(MSG_INFO, &quot;MEMLEAK[%p]: len %lu&quot;,
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;a, (unsigned long) a-&gt;len);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;wpa_trace_dump(&quot;memleak&quot;, a);
    </p>
    <p>
      &#160;&#160;&#160;&#160;}
    </p>
    <p>
      &#160;&#160;&#160;&#160;if (total)
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;wpa_printf(MSG_INFO, &quot;MEMLEAK: total %lu bytes&quot;,
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;(unsigned long) total);
    </p>
    <p>
      &#160;&#160;&#160;&#160;wpa_trace_deinit();
    </p>
    <p>
      #endif /* WPA_TRACE */
    </p>
    <p>
      }
    </p>
  </body>
</html></richcontent>
</node>
</node>
</node>
</node>
</node>
</node>
</map>
