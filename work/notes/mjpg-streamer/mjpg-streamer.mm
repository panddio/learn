<map version="0.9.0">
<!-- To view this file, download free mind mapping software FreeMind from http://freemind.sourceforge.net -->
<node CREATED="1511404396454" ID="ID_382895365" MODIFIED="1511486503488" TEXT="mjpg-streamer">
<font BOLD="true" ITALIC="true" NAME="SansSerif" SIZE="24"/>
<node CREATED="1511404417262" ID="ID_1215395709" MODIFIED="1511410010643" POSITION="right" TEXT="&#x4ee3;&#x7801;&#x6d41;&#x7a0b;">
<font NAME="SansSerif" SIZE="14"/>
<node CREATED="1511405155447" ID="ID_1145621103" MODIFIED="1511405388582" STYLE="fork" TEXT="dlopen&#x6253;&#x5f00;&#x63d2;&#x4ef6;"/>
<node CREATED="1511405158124" ID="ID_174792932" MODIFIED="1511405388582" STYLE="fork" TEXT="dlsym&#x83b7;&#x53d6;&#x76f8;&#x5173;&#x51fd;&#x6570;"/>
<node CREATED="1511405158799" ID="ID_1802419889" MODIFIED="1511405158799" TEXT=""/>
<node CREATED="1511405174398" ID="ID_910287499" MODIFIED="1511405174398" TEXT=""/>
</node>
<node CREATED="1511409847468" ID="ID_461428240" MODIFIED="1511410011909" POSITION="right" TEXT="&#x91cd;&#x8981;&#x6570;&#x636e;&#x7ed3;&#x6784;&#x89e3;&#x8bfb;">
<font NAME="SansSerif" SIZE="14"/>
<node CREATED="1511409892027" ID="ID_1296382900" MODIFIED="1511491877204">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      <font color="#e00b0b">typedef struct _globals globals;</font>
    </p>
    <p>
      struct _globals {
    </p>
    <p>
      &#160;&#160;&#160;&#160;int stop;
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;/* input plugin */
    </p>
    <p>
      &#160;&#160;&#160;&#160;<font color="#1b15df">input</font>&#160;in[MAX_INPUT_PLUGINS];
    </p>
    <p>
      &#160;&#160;&#160;&#160;int incnt;
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;/* output plugin */
    </p>
    <p>
      &#160;&#160;&#160;&#160;<font color="#1415f2">output</font>&#160;out[MAX_OUTPUT_PLUGINS];
    </p>
    <p>
      &#160;&#160;&#160;&#160;int outcnt;
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;/* pointer to control functions */
    </p>
    <p>
      &#160;&#160;&#160;&#160;//int (*control)(int command, char *details);
    </p>
    <p>
      };
    </p>
  </body>
</html></richcontent>
<font NAME="SansSerif" SIZE="12"/>
<node CREATED="1511409945675" ID="ID_1641294463" MODIFIED="1511491940551">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      typedef struct _input input;
    </p>
    <p>
      
    </p>
    <p>
      /* structure to store variables/functions for input plugin */
    </p>
    <p>
      struct _input {
    </p>
    <p>
      &#160;&#160;&#160;&#160;char *plugin;
    </p>
    <p>
      &#160;&#160;&#160;&#160;void *<font color="#f15921">handle</font>;
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;<font color="#e6671c">input_parameter</font>&#160;param; // this holds the command line arguments
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;// input plugin parameters
    </p>
    <p>
      &#160;&#160;&#160;&#160;<font color="#e0510e">struct _control</font>&#160;*in_parameters;
    </p>
    <p>
      &#160;&#160;&#160;&#160;int parametercount;
    </p>
    <p>
      
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;struct v4l2_jpegcompression jpegcomp;
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;/* signal fresh frames */
    </p>
    <p>
      &#160;&#160;&#160;&#160;pthread_mutex_t db;
    </p>
    <p>
      &#160;&#160;&#160;&#160;pthread_cond_t&#160;&#160;db_update;
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;/* global JPG frame, this is more or less the &quot;database&quot; */
    </p>
    <p>
      &#160;&#160;&#160;&#160;unsigned char *buf;
    </p>
    <p>
      &#160;&#160;&#160;&#160;int size;
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;/* v4l2_buffer timestamp */
    </p>
    <p>
      &#160;&#160;&#160;&#160;struct timeval timestamp;
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;<font color="#f95b08">input_format</font>&#160;*in_formats;
    </p>
    <p>
      &#160;&#160;&#160;&#160;int formatCount;
    </p>
    <p>
      &#160;&#160;&#160;&#160;int currentFormat; // holds the current format number
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;int (*init)(input_parameter *, int id);
    </p>
    <p>
      &#160;&#160;&#160;&#160;int (*stop)(int);
    </p>
    <p>
      &#160;&#160;&#160;&#160;int (*run)(int);
    </p>
    <p>
      &#160;&#160;&#160;&#160;int (*cmd)(int plugin, unsigned int control_id, unsigned int group, int value);
    </p>
    <p>
      };
    </p>
  </body>
</html></richcontent>
<node CREATED="1511429635475" ID="ID_612437462" MODIFIED="1511429717723">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      /* parameters for input plugin */
    </p>
    <p>
      typedef struct _input_parameter input_parameter;
    </p>
    <p>
      struct _input_parameter {
    </p>
    <p>
      &#160;&#160;&#160;&#160;int id;
    </p>
    <p>
      &#160;&#160;&#160;&#160;char *parameters;
    </p>
    <p>
      &#160;&#160;&#160;&#160;int argc;
    </p>
    <p>
      &#160;&#160;&#160;&#160;char *argv[MAX_PLUGIN_ARGUMENTS];
    </p>
    <p>
      &#160;&#160;&#160;&#160;<font color="#e44506">struct _globals</font>&#160;*global;
    </p>
    <p>
      };
    </p>
  </body>
</html></richcontent>
</node>
<node CREATED="1511491214702" ID="ID_475169611" MODIFIED="1511491220506">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      typedef struct _control control;
    </p>
    <p>
      struct _control {
    </p>
    <p>
      &#160;&#160;&#160;&#160;struct v4l2_queryctrl ctrl;
    </p>
    <p>
      &#160;&#160;&#160;&#160;int value;
    </p>
    <p>
      &#160;&#160;&#160;&#160;struct v4l2_querymenu *menuitems;
    </p>
    <p>
      &#160;&#160;&#160;&#160;/*&#160;&#160;In the case the control a V4L2 ctrl this variable will specify
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;that the control is a V4L2_CTRL_CLASS_USER control or not.
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;For non V4L2 control it is not acceptable, leave it 0.
    </p>
    <p>
      &#160;&#160;&#160;&#160;*/
    </p>
    <p>
      &#160;&#160;&#160;&#160;int class_id;
    </p>
    <p>
      &#160;&#160;&#160;&#160;int group;
    </p>
    <p>
      };
    </p>
  </body>
</html></richcontent>
</node>
<node CREATED="1511487418531" ID="ID_976072103" MODIFIED="1511491948137">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      typedef struct _input_format input_format;
    </p>
    <p>
      struct _input_format {
    </p>
    <p>
      &#160;&#160;&#160;&#160;struct v4l2_fmtdesc format;
    </p>
    <p>
      &#160;&#160;&#160;&#160;<font color="#eb4910">input_resolution</font>&#160;*supportedResolutions;
    </p>
    <p>
      &#160;&#160;&#160;&#160;int resolutionCount;
    </p>
    <p>
      &#160;&#160;&#160;&#160;char currentResolution;
    </p>
    <p>
      };
    </p>
  </body>
</html></richcontent>
<node CREATED="1511487478458" ID="ID_423355577" MODIFIED="1511487483620">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      typedef struct _input_resolution input_resolution;
    </p>
    <p>
      struct _input_resolution {
    </p>
    <p>
      &#160;&#160;&#160;&#160;unsigned int width;
    </p>
    <p>
      &#160;&#160;&#160;&#160;unsigned int height;
    </p>
    <p>
      };
    </p>
  </body>
</html></richcontent>
</node>
</node>
</node>
<node CREATED="1511410079467" ID="ID_380292413" MODIFIED="1511491878955">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      /* structure to store variables/functions for output plugin */
    </p>
    <p>
      typedef struct _output output;
    </p>
    <p>
      struct _output {
    </p>
    <p>
      &#160;&#160;&#160;&#160;char *plugin;
    </p>
    <p>
      &#160;&#160;&#160;&#160;void *handle;
    </p>
    <p>
      &#160;&#160;&#160;&#160;<font color="#2622e0">output_parameter</font>&#160;param;
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;// input plugin parameters
    </p>
    <p>
      &#160;&#160;&#160;&#160;<font color="#0302e1">struct _control </font>*out_parameters;
    </p>
    <p>
      &#160;&#160;&#160;&#160;int parametercount;
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;int (*init)(output_parameter *param, int id);
    </p>
    <p>
      &#160;&#160;&#160;&#160;int (*stop)(int);
    </p>
    <p>
      &#160;&#160;&#160;&#160;int (*run)(int);
    </p>
    <p>
      &#160;&#160;&#160;&#160;int (*cmd)(int plugin, unsigned int control_id, unsigned int group, int value);
    </p>
    <p>
      };
    </p>
  </body>
</html></richcontent>
<node CREATED="1511410139291" ID="ID_768244179" MODIFIED="1511429731291">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      /* parameters for output plugin */
    </p>
    <p>
      typedef struct _output_parameter output_parameter;
    </p>
    <p>
      struct _output_parameter {
    </p>
    <p>
      &#160;&#160;&#160;&#160;int id;
    </p>
    <p>
      &#160;&#160;&#160;&#160;char *parameters;
    </p>
    <p>
      &#160;&#160;&#160;&#160;int argc;
    </p>
    <p>
      &#160;&#160;&#160;&#160;char *argv[MAX_PLUGIN_ARGUMENTS];
    </p>
    <p>
      &#160;&#160;&#160;<font color="#1b13e7">&#160;struct _globals</font>&#160;*global;
    </p>
    <p>
      };
    </p>
  </body>
</html></richcontent>
</node>
<node CREATED="1511491214702" ID="ID_1350610482" MODIFIED="1511491220506">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      typedef struct _control control;
    </p>
    <p>
      struct _control {
    </p>
    <p>
      &#160;&#160;&#160;&#160;struct v4l2_queryctrl ctrl;
    </p>
    <p>
      &#160;&#160;&#160;&#160;int value;
    </p>
    <p>
      &#160;&#160;&#160;&#160;struct v4l2_querymenu *menuitems;
    </p>
    <p>
      &#160;&#160;&#160;&#160;/*&#160;&#160;In the case the control a V4L2 ctrl this variable will specify
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;that the control is a V4L2_CTRL_CLASS_USER control or not.
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;For non V4L2 control it is not acceptable, leave it 0.
    </p>
    <p>
      &#160;&#160;&#160;&#160;*/
    </p>
    <p>
      &#160;&#160;&#160;&#160;int class_id;
    </p>
    <p>
      &#160;&#160;&#160;&#160;int group;
    </p>
    <p>
      };
    </p>
  </body>
</html></richcontent>
</node>
</node>
</node>
<node CREATED="1511409895500" ID="ID_1878562139" MODIFIED="1511491940552">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      <font color="#db1010">typedef struct _control control;</font>
    </p>
    <p>
      struct _control {
    </p>
    <p>
      &#160;&#160;&#160;&#160;struct v4l2_queryctrl ctrl;
    </p>
    <p>
      &#160;&#160;&#160;&#160;int value;
    </p>
    <p>
      &#160;&#160;&#160;&#160;struct v4l2_querymenu *menuitems;
    </p>
    <p>
      &#160;&#160;&#160;&#160;/*&#160;&#160;In the case the control a V4L2 ctrl this variable will specify
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;that the control is a V4L2_CTRL_CLASS_USER control or not.
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;For non V4L2 control it is not acceptable, leave it 0.
    </p>
    <p>
      &#160;&#160;&#160;&#160;*/
    </p>
    <p>
      &#160;&#160;&#160;&#160;int class_id;
    </p>
    <p>
      &#160;&#160;&#160;&#160;int group;
    </p>
    <p>
      };
    </p>
  </body>
</html></richcontent>
</node>
<node CREATED="1511492734567" ID="ID_1027773445" MODIFIED="1511492740058">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      /* context of each camera thread */
    </p>
    <p>
      typedef struct {
    </p>
    <p>
      &#160;&#160;&#160;&#160;int id;
    </p>
    <p>
      &#160;&#160;&#160;&#160;globals *pglobal;
    </p>
    <p>
      &#160;&#160;&#160;&#160;pthread_t threadID;
    </p>
    <p>
      &#160;&#160;&#160;&#160;pthread_mutex_t controls_mutex;
    </p>
    <p>
      &#160;&#160;&#160;&#160;struct vdIn *videoIn;
    </p>
    <p>
      } context;
    </p>
  </body>
</html>
</richcontent>
<node CREATED="1511492775967" ID="ID_1362853158" MODIFIED="1511492780183">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      struct vdIn {
    </p>
    <p>
      &#160;&#160;&#160;&#160;int fd;
    </p>
    <p>
      &#160;&#160;&#160;&#160;char *videodevice;
    </p>
    <p>
      &#160;&#160;&#160;&#160;char *status;
    </p>
    <p>
      &#160;&#160;&#160;&#160;char *pictName;
    </p>
    <p>
      &#160;&#160;&#160;&#160;struct v4l2_capability cap;
    </p>
    <p>
      &#160;&#160;&#160;&#160;struct v4l2_format fmt;
    </p>
    <p>
      &#160;&#160;&#160;&#160;struct v4l2_buffer buf;
    </p>
    <p>
      &#160;&#160;&#160;&#160;struct v4l2_requestbuffers rb;
    </p>
    <p>
      &#160;&#160;&#160;&#160;void *mem[NB_BUFFER];
    </p>
    <p>
      &#160;&#160;&#160;&#160;unsigned char *tmpbuffer;
    </p>
    <p>
      &#160;&#160;&#160;&#160;unsigned char *framebuffer;
    </p>
    <p>
      &#160;&#160;&#160;&#160;streaming_state streamingState;
    </p>
    <p>
      &#160;&#160;&#160;&#160;int grabmethod;
    </p>
    <p>
      &#160;&#160;&#160;&#160;int width;
    </p>
    <p>
      &#160;&#160;&#160;&#160;int height;
    </p>
    <p>
      &#160;&#160;&#160;&#160;int fps;
    </p>
    <p>
      &#160;&#160;&#160;&#160;int formatIn;
    </p>
    <p>
      &#160;&#160;&#160;&#160;int formatOut;
    </p>
    <p>
      &#160;&#160;&#160;&#160;int framesizeIn;
    </p>
    <p>
      &#160;&#160;&#160;&#160;int signalquit;
    </p>
    <p>
      &#160;&#160;&#160;&#160;int toggleAvi;
    </p>
    <p>
      &#160;&#160;&#160;&#160;int getPict;
    </p>
    <p>
      &#160;&#160;&#160;&#160;int rawFrameCapture;
    </p>
    <p>
      &#160;&#160;&#160;&#160;/* raw frame capture */
    </p>
    <p>
      &#160;&#160;&#160;&#160;unsigned int fileCounter;
    </p>
    <p>
      &#160;&#160;&#160;&#160;/* raw frame stream capture */
    </p>
    <p>
      &#160;&#160;&#160;&#160;unsigned int rfsFramesWritten;
    </p>
    <p>
      &#160;&#160;&#160;&#160;unsigned int rfsBytesWritten;
    </p>
    <p>
      &#160;&#160;&#160;&#160;/* raw stream capture */
    </p>
    <p>
      &#160;&#160;&#160;&#160;FILE *captureFile;
    </p>
    <p>
      &#160;&#160;&#160;&#160;unsigned int framesWritten;
    </p>
    <p>
      &#160;&#160;&#160;&#160;unsigned int bytesWritten;
    </p>
    <p>
      &#160;&#160;&#160;&#160;int framecount;
    </p>
    <p>
      &#160;&#160;&#160;&#160;int recordstart;
    </p>
    <p>
      &#160;&#160;&#160;&#160;int recordtime;
    </p>
    <p>
      };
    </p>
  </body>
</html>
</richcontent>
</node>
</node>
</node>
<node CREATED="1511404419393" ID="ID_456763078" MODIFIED="1511420968830" POSITION="right">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      <font color="#e80303">mjpg_streamer -i &quot;input_uvc.so -f 10 -r 320*240&quot; -o &quot;output_http.so -w www&quot;</font><font color="#000000">&#30340;&#25191;&#34892;&#27969;&#31243;</font>
    </p>
  </body>
</html></richcontent>
<font NAME="SansSerif" SIZE="14"/>
<node CREATED="1511420987607" ID="ID_1696839536" MODIFIED="1511421524842">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      &#21442;&#25968;&#35828;&#26126;:
    </p>
    <p>
      -i &quot;input_uvc.so -f 10 -r 320*240&quot;: &#25351;&#23450;&#36755;&#20837;&#35774;&#22791;&#20197;&#21450;&#20256;&#32473;&#36755;&#20837;&#35774;&#22791;&#30340;&#21442;&#25968;
    </p>
    <p>
      -o &quot;output_http.so -w www&quot;: &#25351;&#23450;&#36755;&#20986;&#35774;&#22791;&#20197;&#21450;&#20256;&#32473;&#36755;&#20986;&#35774;&#22791;&#30340;&#21442;&#25968;
    </p>
  </body>
</html></richcontent>
</node>
<node CREATED="1511411498421" ID="ID_1296736769" MODIFIED="1511428607633" TEXT="&#x4e3b;&#x7a0b;&#x5e8f;int main(int argc, char *argv[])">
<node CREATED="1511411563005" ID="ID_708735848" MODIFIED="1511411864192">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      /**
    </p>
    <p>
      &#160;*&#160;&#160;&#24490;&#29615;&#35299;&#26512;&#36816;&#34892; mjpg_streaner&#20256;&#20837;&#30340;&#21442;&#25968;
    </p>
    <p>
      &#160;*/
    </p>
    <p>
      while(1) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;...
    </p>
    <p>
      &#160;&#160;&#160;&#160;getopt_long_only(argc, argv, &quot;&quot;, long_options, &amp;option_index);
    </p>
    <p>
      &#160;&#160;&#160;&#160;...
    </p>
    <p>
      }
    </p>
  </body>
</html></richcontent>
</node>
<node CREATED="1511411564961" ID="ID_22707507" MODIFIED="1511420948901">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      <font color="#e30c0c">/** </font>
    </p>
    <p>
      <font color="#e30c0c">&#160;* openlog()&#25171;&#24320;&#19968;&#20010;&#31243;&#24207;&#30340;&#31995;&#32479;&#26085;&#35760;&#35774;&#22791;&#30340;&#36830;&#25509;, &#21442;&#25968;: </font>
    </p>
    <p>
      <font color="#e30c0c">&#160;* @&quot;MJPG-streamer &quot;: &#23558;&#22266;&#23450;&#22841;&#22312;&#27599;&#34892;&#26085;&#35760;&#30340;&#21069;&#38754;&#19968;&#26631;&#35782;&#36825;&#26465;&#26085;&#35760; </font>
    </p>
    <p>
      <font color="#e30c0c">&#160;* @LOG_PID | LOG_CONS: </font>
    </p>
    <p>
      <font color="#e30c0c">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;LOG_PID &#27599;&#20010;&#28040;&#24687;&#37117;&#21253;&#21547;&#36827;&#31243;&#30340;PID </font>
    </p>
    <p>
      <font color="#e30c0c">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;LOG_CONS &#30452;&#25509;&#20889;&#20837;&#31995;&#32479;&#25511;&#21046;&#21488;, &#22914;&#26524;&#26377;&#19968;&#20010;&#38169;&#35823;, &#21516;&#26102;&#21457;&#36865;&#21040;&#31995;&#32479;&#26085;&#24535;&#35760;&#24405; </font>
    </p>
    <p>
      <font color="#e30c0c">&#160;* @LOG_USER: &#36825;&#20010;&#21442;&#25968;&#25351;&#23450;&#28040;&#24687;&#30340;&#31867;&#22411;, LOG_USER&#34920;&#31034;: generic user-level messages </font>
    </p>
    <p>
      <font color="#e30c0c">&#160;* &#27880;&#24847;, &#26080;&#39035;&#22312;&#35843;&#29992; syslog() &#20043;&#21069;&#35843;&#29992; openlog() , &#36825;&#26159;&#22240;&#20026;&#22914;&#26524;&#26377;&#38656;&#35201;&#30340;&#35805; syslog() &#20063;&#20250; </font>
    </p>
    <p>
      <font color="#e30c0c">&#160;* &#25171;&#24320;&#26085;&#24535;&#21151;&#33021;&#12290; </font>
    </p>
    <p>
      <font color="#e30c0c">&#160;*/</font>
    </p>
    <p>
      openlog(&quot;MJPG-streamer &quot;, LOG_PID | LOG_CONS, LOG_USER);
    </p>
    <p>
      
    </p>
    <p>
      <font color="#ec0707">/** </font>
    </p>
    <p>
      <font color="#ec0707">&#160;* &#35843;&#29992;syslog()&#20989;&#25968;&#21521;&#31995;&#32479;&#26085;&#35760;&#35774;&#22791;&#21457;&#36865;&#26085;&#35760;&#28040;&#24687; </font>
    </p>
    <p>
      <font color="#ec0707">&#160;* &#31532;&#19968;&#20010;&#21442;&#25968;&#25351;&#23450;&#28040;&#24687;&#30340;&#31561;&#32423;, LOG_INFO&#34920;&#31034;&#36825;&#26159;&#19968;&#26465;&#36890;&#30693;&#24615;&#30340;&#28040;&#24687; </font>
    </p>
    <p>
      <font color="#ec0707">&#160;*/</font>
    </p>
    <p>
      syslog(LOG_INFO, &quot;starting application&quot;);
    </p>
  </body>
</html></richcontent>
</node>
<node CREATED="1511411565508" ID="ID_643539760" MODIFIED="1511421277977">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      /**
    </p>
    <p>
      &#160;* &#26159;&#21542;&#35201;&#20197;&#21518;&#21488;&#31243;&#24207;&#27169;&#24335;&#36816;&#34892;&#65292;daemon &#23454;&#38469;&#20026;0
    </p>
    <p>
      &#160;*/
    </p>
    <p>
      if(daemon) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;LOG(&quot;enabling daemon mode&quot;);
    </p>
    <p>
      &#160;&#160;&#160;&#160;daemon_mode();
    </p>
    <p>
      }
    </p>
  </body>
</html></richcontent>
</node>
<node CREATED="1511411565909" ID="ID_1035847934" MODIFIED="1511421332387">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      /**
    </p>
    <p>
      *&#160;&#160;ignore SIGPIPE (send by OS if transmitting to closed TCP sockets)
    </p>
    <p>
      &#160;*/
    </p>
    <p>
      signal(SIGPIPE, SIG_IGN);
    </p>
    <p>
      
    </p>
    <p>
      /* register signal handler for &lt;CTRL&gt;+C in order to clean up */
    </p>
    <p>
      if(signal(SIGINT, signal_handler) == SIG_ERR) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;LOG(&quot;could not register signal handler\n&quot;);
    </p>
    <p>
      &#160;&#160;&#160;&#160;closelog();
    </p>
    <p>
      &#160;&#160;&#160;&#160;exit(EXIT_FAILURE);
    </p>
    <p>
      }
    </p>
  </body>
</html></richcontent>
</node>
<node CREATED="1511411566694" ID="ID_1015180595" MODIFIED="1511422126778">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      /* open input plugin */
    </p>
    <p>
      for(i = 0; i &lt; global.incnt; i++) {&#160;&#160;... }
    </p>
  </body>
</html></richcontent>
<node CREATED="1511422129720" ID="ID_86258205" MODIFIED="1511422348524">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      <font color="#db0b0b">/** </font>
    </p>
    <p>
      <font color="#db0b0b">&#160;*&#160;This mutex and the conditional variable are used to </font>
    </p>
    <p>
      <font color="#db0b0b">&#160;* synchronize access to the global picture buffer. </font>
    </p>
    <p>
      <font color="#db0b0b">&#160;*/</font>
    </p>
    <p>
      if(pthread_mutex_init(&amp;global.in[i].db, NULL) != 0) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;LOG(&quot;could not initialize mutex variable\n&quot;);
    </p>
    <p>
      &#160;&#160;&#160;&#160;closelog(); //&#23545;&#24212;openlog()&#20989;&#25968;
    </p>
    <p>
      &#160;&#160;&#160;&#160;exit(EXIT_FAILURE);
    </p>
    <p>
      }
    </p>
    <p>
      if(pthread_cond_init(&amp;global.in[i].db_update, NULL) != 0) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;LOG(&quot;could not initialize condition variable\n&quot;);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;closelog();
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;exit(EXIT_FAILURE);
    </p>
    <p>
      }
    </p>
  </body>
</html></richcontent>
</node>
<node CREATED="1511422132512" ID="ID_1663771233" MODIFIED="1511425524930">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      <font color="#e50e0e">/** </font>
    </p>
    <p>
      <font color="#e50e0e">&#160;* &#20174;&#20256;&#20837;&#30340;&#21442;&#25968;&#65288;input[i] = &quot;input_uvc.so -f 10 -r 320*240&quot;&#65289;&#25552;&#21462;&#36755;&#20837;&#35774;&#22791; </font>
    </p>
    <p>
      <font color="#e50e0e">&#160;* strchr(input[i], ' ') &#36820;&#22238;&#20986;&#29616;&#31532;&#19968;&#20010;&#31354;&#26684;&#31526;&#30340;&#20301;&#32622;, &#20877;&#20943;&#21435;input[i], &#30001;&#27492;&#24471;&#21040; </font>
    </p>
    <p>
      <font color="#e50e0e">&#160;* &#36755;&#20837;&#35774;&#22791;&#21517;&#31216;&#22823;&#23567; </font>
    </p>
    <p>
      <font color="#e50e0e">&#160;*/</font>
    </p>
    <p>
      tmp = (size_t)(strchr(input[i], ' ') - input[i]);
    </p>
    <p>
      
    </p>
    <p>
      global.in[i].stop&#160;&#160;&#160;&#160;&#160;&#160;= 0;
    </p>
    <p>
      global.in[i].buf&#160;&#160;&#160;&#160;&#160;&#160;&#160;= NULL;
    </p>
    <p>
      global.in[i].size&#160;&#160;&#160;&#160;&#160;&#160;= 0;
    </p>
    <p>
      <font color="#d30808">/** </font>
    </p>
    <p>
      <font color="#d30808">&#160;* &#36890;&#36807;global.in[i].plugin&#20445;&#23384;&#36755;&#20837;&#35774;&#22791;&#21517;&#31216;, &#23454;&#38469;&#26159;&#19968;&#20010;&#21160;&#24577;&#38142;&#25509;&#24211;, &#30456;&#24403;&#26159; </font>
    </p>
    <p>
      <font color="#d30808">&#160;* &#20027;&#31243;&#24207;&#30340;&#19968;&#20010;&#25554;&#20214;, &#36825;&#26679;&#20570;&#30340;&#22909;&#22788;&#26159;&#20445;&#25345;&#20027;&#31243;&#24207;&#30340;&#36923;&#36753;&#19981;&#21464;, &#23558;&#21508;&#20010;&#25554;&#20214;&#20197; </font>
    </p>
    <p>
      <font color="#d30808">&#160;* &#21160;&#24577;&#38142;&#25509;&#24211;&#30340;&#24418;&#24335;&#21152;&#36733;&#36827;&#26469;</font>
    </p>
    <p>
      <font color="#d30808">&#160;*/</font>
    </p>
    <p>
      global.in[i].plugin = (tmp &gt; 0) ? strndup(input[i], tmp) : strdup(input[i]);
    </p>
    <p>
      
    </p>
    <p>
      <font color="#e01313">/** </font>
    </p>
    <p>
      <font color="#e01313">&#160;* dlopen()&#20197;&#25351;&#23450;&#27169;&#24335;&#25171;&#24320;&#25351;&#23450;&#30340;&#21160;&#24577;&#36830;&#25509;&#24211;&#25991;&#20214;, &#24182;&#36820;&#22238;&#19968;&#20010;&#21477;&#26564;&#32473;&#35843;&#29992; </font>
    </p>
    <p>
      <font color="#e01313">&#160;* &#36827;&#31243;, dlsym()&#20989;&#25968;&#36890;&#36807;&#21477;&#26564;&#21644;&#36830;&#25509;&#31526;&#21517;&#31216;&#33719;&#21462;&#20989;&#25968;&#21517;&#25110;&#32773;&#21464;&#37327;&#21517; ,dlopen() </font>
    </p>
    <p>
      <font color="#e01313">&#160;* &#25171;&#24320;&#27169;&#24335;&#22914;&#19979;&#65306; </font>
    </p>
    <p>
      <font color="#e01313">&#12288;&#12288;RTLD_LAZY &#26242;&#32531;&#20915;&#23450;, &#31561;&#26377;&#38656;&#35201;&#26102;&#20877;&#35299;&#20986;&#31526;&#21495; </font>
    </p>
    <p>
      <font color="#e01313">&#12288;&#12288;RTLD_NOW &#31435;&#21363;&#20915;&#23450;, &#36820;&#22238;&#21069;&#35299;&#38500;&#25152;&#26377;&#26410;&#20915;&#23450;&#30340;&#31526;&#21495;&#12290;</font>
    </p>
    <p>
      <font color="#e01313">&#160;*/</font>
    </p>
    <p>
      global.in[i].handle = dlopen(global.in[i].plugin, RTLD_LAZY);
    </p>
    <p>
      if(!global.in[i].handle) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;LOG(&quot;ERROR: could not find input plugin\n&quot;);
    </p>
    <p>
      &#160;&#160;&#160;&#160;LOG(&quot;&#160;&#160;&#160;&#160;&#160;&#160;&#160;Perhaps you want to adjust the search path with:\n&quot;);
    </p>
    <p>
      &#160;&#160;&#160;&#160;LOG(&quot;&#160;&#160;&#160;&#160;&#160;&#160;&#160;# export LD_LIBRARY_PATH=/path/to/plugin/folder\n&quot;);
    </p>
    <p>
      &#160;&#160;&#160;&#160;LOG(&quot;&#160;&#160;&#160;&#160;&#160;&#160;&#160;dlopen: %s\n&quot;, dlerror());
    </p>
    <p>
      &#160;&#160;&#160;&#160;closelog();
    </p>
    <p>
      &#160;&#160;&#160;&#160;exit(EXIT_FAILURE);
    </p>
    <p>
      }
    </p>
  </body>
</html></richcontent>
</node>
<node CREATED="1511422132929" ID="ID_536748718" MODIFIED="1511425341495">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      <font color="#e71818">/** </font>
    </p>
    <p>
      <font color="#e71818">&#160;* &#36890;&#36807;dlopen()&#20989;&#25968;&#36820;&#22238;&#26469;&#30340;&#21477;&#26564;&#21644;&#36830;&#25509;&#31526;, &#35843;&#29992;dlsym() &#33719; </font>
    </p>
    <p>
      <font color="#e71818">&#160;* &#21462;&#36755;&#20837;&#35774;&#22791;&#30340;&#25805;&#20316;&#20989;&#25968; </font>
    </p>
    <p>
      <font color="#e71818">&#160;*/</font>
    </p>
    <p>
      global.in[i].init = dlsym(global.in[i].handle, &quot;input_init&quot;);
    </p>
    <p>
      if(global.in[i].init == NULL) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;LOG(&quot;%s\n&quot;, dlerror());
    </p>
    <p>
      &#160;&#160;&#160;&#160;exit(EXIT_FAILURE);
    </p>
    <p>
      }
    </p>
    <p>
      global.in[i].stop = dlsym(global.in[i].handle, &quot;input_stop&quot;);
    </p>
    <p>
      if(global.in[i].stop == NULL) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;LOG(&quot;%s\n&quot;, dlerror());
    </p>
    <p>
      &#160;&#160;&#160;&#160;exit(EXIT_FAILURE);
    </p>
    <p>
      }
    </p>
    <p>
      global.in[i].run = dlsym(global.in[i].handle, &quot;input_run&quot;);
    </p>
    <p>
      if(global.in[i].run == NULL) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;LOG(&quot;%s\n&quot;, dlerror());
    </p>
    <p>
      &#160;&#160;&#160;&#160;exit(EXIT_FAILURE);
    </p>
    <p>
      }
    </p>
    <p>
      
    </p>
    <p>
      /* try to find optional command */
    </p>
    <p>
      global.in[i].cmd = dlsym(global.in[i].handle, &quot;input_cmd&quot;);
    </p>
  </body>
</html></richcontent>
</node>
<node CREATED="1511422133544" ID="ID_34293201" MODIFIED="1511429808070">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      <font color="#ea0505">/** </font>
    </p>
    <p>
      <font color="#ea0505">&#160;* &#20174;&#20256;&#20837;&#30340;&#21442;&#25968;&#65288;input[i] = &quot;input_uvc.so -f 10 -r 320*240&quot;&#65289;&#25214;&#21040;&#20256; </font>
    </p>
    <p>
      <font color="#ea0505">&#160;* &#32473;&#36755;&#20837;&#35774;&#22791;&#30340;&#21442;&#25968;&#30340;&#20301;&#32622;, &#20445;&#23384;&#21040;global.in[i].param.parameters, </font>
    </p>
    <p>
      <font color="#ea0505">&#160;* &#20877;&#30001;split_parameters()&#20998;&#31163;&#20986;&#21508;&#20010;&#21442;&#25968; </font>
    </p>
    <p>
      <font color="#ea0505">&#160;*/</font>
    </p>
    <p>
      global.in[i].param.parameters = strchr(input[i], ' ');
    </p>
    <p>
      <font color="#0d0ee2">split_parameters</font>(global.in[i].param.parameters,
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&amp;global.in[i].param.argc,
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;global.in[i].param.argv);
    </p>
    <p>
      
    </p>
    <p>
      global.in[i].param.global = &amp;global;
    </p>
    <p>
      global.in[i].param.id = i;
    </p>
    <p>
      
    </p>
    <p>
      <font color="#ec0707">/** </font>
    </p>
    <p>
      <font color="#ec0707">&#160;* &#35843;&#29992;&#36755;&#20837;&#35774;&#22791;&#30340;&#21021;&#22987;&#21270;&#20989;&#25968; </font>
    </p>
    <p>
      <font color="#ec0707">&#160;*/</font>
    </p>
    <p>
      if(global.in[i].init(&amp;global.in[i].param, i)) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;LOG(&quot;input_init() return value signals to exit\n&quot;);
    </p>
    <p>
      &#160;&#160;&#160;&#160;closelog();
    </p>
    <p>
      &#160;&#160;&#160;&#160;exit(0);
    </p>
    <p>
      }
    </p>
  </body>
</html></richcontent>
<node CREATED="1511425257012" ID="ID_132935516" MODIFIED="1511427025306">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      int split_parameters(char *parameter_string, int *argc, char **argv)
    </p>
    <p>
      {
    </p>
    <p>
      &#160;&#160;&#160;&#160;int count = 1;
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;argv[0] = NULL; // the plugin may set it to 'INPUT_PLUGIN_NAME'
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;if(parameter_string != NULL &amp;&amp; strlen(parameter_string) != 0) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;char *arg = NULL, *saveptr = NULL, *token = NULL;
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;arg = strdup(parameter_string);
    </p>
    <p>
      
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;if(strchr(arg, ' ') != NULL) {
    </p>
    <p>
      <font color="#e20909">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;/** </font>
    </p>
    <p>
      <font color="#e20909">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;* strtok_r() &#26159;strtok() &#30340;&#21487;&#37325;&#20837;&#29256;&#26412;(&#32447;&#31243;&#23433;&#20840;), &#29992;&#20110;&#20998;&#21106;&#23383;&#31526;&#20018; </font>
    </p>
    <p>
      <font color="#e20909">&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;*/</font>
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;token = strtok_r(arg, &quot; &quot;, &amp;saveptr);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;if(token != NULL) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;argv[count] = strdup(token);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;count++;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;while((token = strtok_r(NULL, &quot; &quot;, &amp;saveptr)) != NULL) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;argv[count] = strdup(token);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;count++;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;if(count &gt;= MAX_PLUGIN_ARGUMENTS) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;IPRINT(&quot;ERROR: too many arguments to input plugin\n&quot;);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;return 0;
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;}
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;}
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;}
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
      &#160;&#160;&#160;&#160;*argc = count;
    </p>
    <p>
      &#160;&#160;&#160;&#160;return 1;
    </p>
    <p>
      }
    </p>
  </body>
</html></richcontent>
</node>
</node>
</node>
<node CREATED="1511421992642" ID="ID_1766454789" MODIFIED="1511422160562">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      /* open output plugin */
    </p>
    <p>
      for(i = 0; i &lt; global.outcnt; i++) { ... }
    </p>
  </body>
</html></richcontent>
<node CREATED="1511422163089" ID="ID_67380711" MODIFIED="1511427867868">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      <font color="#e40b0b">/** </font>
    </p>
    <p>
      <font color="#e40b0b">&#160;* &#20174;&#20256;&#20837;&#30340;&#21442;&#25968;&#65288;output[i] = &quot;output_http.so -w www&#65289;&#25552;&#21462;&#36755;&#20986;&#35774;&#22791;&#30340;&#21517; </font>
    </p>
    <p>
      <font color="#e40b0b">&#160;* &#31216;, strchr(input[i], ' ') &#36820;&#22238;&#20986;&#29616;&#31532;&#19968;&#20010;&#31354;&#26684;&#31526;&#30340;&#20301;&#32622;, &#20877;&#20943;&#21435;input[i], &#30001;&#27492; </font>
    </p>
    <p>
      <font color="#e40b0b">&#160;* &#24471;&#21040;&#36755;&#20986;&#35774;&#22791;&#21517;&#31216;&#22823;&#23567; </font>
    </p>
    <p>
      <font color="#e40b0b">&#160;*/</font>
    </p>
    <p>
      tmp = (size_t)(strchr(output[i], ' ') - output[i]);
    </p>
    <p>
      <font color="#d30808">/** </font>
    </p>
    <p>
      <font color="#d30808">&#160;* &#36890;&#36807;global.out[i].plugin&#20445;&#23384;&#36755;&#20986;&#35774;&#22791;&#21517;&#31216;, &#23454;&#38469;&#26159;&#19968;&#20010;&#21160;&#24577;&#38142;&#25509;&#24211;</font>
    </p>
    <p>
      <font color="#d30808">&#160;*/</font>
    </p>
    <p>
      global.out[i].plugin = (tmp &gt; 0) ? strndup(output[i], tmp) : strdup(output[i]);
    </p>
    <p>
      
    </p>
    <p>
      <font color="#e01313">&#160;* dlopen()&#20197;&#25351;&#23450;&#27169;&#24335;&#25171;&#24320;&#25351;&#23450;&#30340;&#21160;&#24577;&#36830;&#25509;&#24211;&#25991;&#20214;, &#24182;&#36820;&#22238;&#19968;&#20010;&#21477;&#26564;&#32473;&#35843;&#29992; </font>
    </p>
    <p>
      <font color="#e01313">&#160;* &#36827;&#31243;, dlsym()&#20989;&#25968;&#36890;&#36807;&#21477;&#26564;&#21644;&#36830;&#25509;&#31526;&#21517;&#31216;&#33719;&#21462;&#20989;&#25968;&#21517;&#25110;&#32773;&#21464;&#37327;&#21517; ,dlopen() </font>
    </p>
    <p>
      <font color="#e01313">&#160;* &#25171;&#24320;&#27169;&#24335;&#22914;&#19979;&#65306; </font>
    </p>
    <p>
      <font color="#e01313">&#12288;&#12288;RTLD_LAZY &#26242;&#32531;&#20915;&#23450;, &#31561;&#26377;&#38656;&#35201;&#26102;&#20877;&#35299;&#20986;&#31526;&#21495; </font>
    </p>
    <p>
      <font color="#e01313">&#12288;&#12288;RTLD_NOW &#31435;&#21363;&#20915;&#23450;, &#36820;&#22238;&#21069;&#35299;&#38500;&#25152;&#26377;&#26410;&#20915;&#23450;&#30340;&#31526;&#21495;&#12290;</font>
    </p>
    <p>
      <font color="#e01313">&#160;*/</font>
    </p>
    <p>
      global.out[i].handle = dlopen(global.out[i].plugin, RTLD_LAZY);
    </p>
    <p>
      if(!global.out[i].handle) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;LOG(&quot;ERROR: could not find output plugin %s\n&quot;, global.out[i].plugin);
    </p>
    <p>
      &#160;&#160;&#160;&#160;LOG(&quot;&#160;&#160;&#160;&#160;&#160;&#160;&#160;Perhaps you want to adjust the search path with:\n&quot;);
    </p>
    <p>
      &#160;&#160;&#160;&#160;LOG(&quot;&#160;&#160;&#160;&#160;&#160;&#160;&#160;# export LD_LIBRARY_PATH=/path/to/plugin/folder\n&quot;);
    </p>
    <p>
      &#160;&#160;&#160;&#160;LOG(&quot;&#160;&#160;&#160;&#160;&#160;&#160;&#160;dlopen: %s\n&quot;, dlerror());
    </p>
    <p>
      &#160;&#160;&#160;&#160;closelog();
    </p>
    <p>
      &#160;&#160;&#160;&#160;exit(EXIT_FAILURE);
    </p>
    <p>
      }
    </p>
  </body>
</html></richcontent>
</node>
<node CREATED="1511422164598" ID="ID_1851532153" MODIFIED="1511428337926">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      <font color="#e71818">/** </font>
    </p>
    <p>
      <font color="#e71818">&#160;* &#36890;&#36807;dlopen()&#20989;&#25968;&#36820;&#22238;&#26469;&#30340;&#21477;&#26564;&#21644;&#36830;&#25509;&#31526;, &#35843;&#29992;dlsym() &#33719; </font>
    </p>
    <p>
      <font color="#e71818">&#160;* &#21462;&#36755;&#20986;&#35774;&#22791;&#30340;&#25805;&#20316;&#20989;&#25968; </font>
    </p>
    <p>
      <font color="#e71818">&#160;*/</font>
    </p>
    <p>
      global.out[i].init = dlsym(global.out[i].handle, &quot;output_init&quot;);
    </p>
    <p>
      if(global.out[i].init == NULL) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;LOG(&quot;%s\n&quot;, dlerror());
    </p>
    <p>
      &#160;&#160;&#160;&#160;exit(EXIT_FAILURE);
    </p>
    <p>
      }
    </p>
    <p>
      global.out[i].stop = dlsym(global.out[i].handle, &quot;output_stop&quot;);
    </p>
    <p>
      if(global.out[i].stop == NULL) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;LOG(&quot;%s\n&quot;, dlerror());
    </p>
    <p>
      &#160;&#160;&#160;&#160;exit(EXIT_FAILURE);
    </p>
    <p>
      }
    </p>
    <p>
      global.out[i].run = dlsym(global.out[i].handle, &quot;output_run&quot;);
    </p>
    <p>
      if(global.out[i].run == NULL) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;LOG(&quot;%s\n&quot;, dlerror());
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;exit(EXIT_FAILURE);
    </p>
    <p>
      }
    </p>
    <p>
      
    </p>
    <p>
      /* try to find optional command */
    </p>
    <p>
      global.out[i].cmd = dlsym(global.out[i].handle, &quot;output_cmd&quot;);
    </p>
  </body>
</html></richcontent>
</node>
<node CREATED="1511422164978" ID="ID_608071764" MODIFIED="1511428547563">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      <font color="#ea0505">/** </font>
    </p>
    <p>
      <font color="#ea0505">&#160;* &#20174;&#20256;&#20837;&#30340;&#21442;&#25968;&#65288;output[i] = &quot;output_http.so -w www&#65289;&#25214;&#21040;&#20256;&#32473;&#160;</font>
    </p>
    <p>
      <font color="#ea0505">&#160;* &#36755;&#20986;&#35774;&#22791;&#30340;&#21442;&#25968;&#30340;&#20301;&#32622;, &#20445;&#23384;&#21040;global.in[i].param.parameters, </font>
    </p>
    <p>
      <font color="#ea0505">&#160;* &#20877;&#30001;split_parameters()&#20998;&#31163;&#20986;&#21508;&#20010;&#21442;&#25968; </font>
    </p>
    <p>
      <font color="#ea0505">&#160;*/</font>
    </p>
    <p>
      global.out[i].param.parameters = strchr(output[i], ' ');
    </p>
    <p>
      split_parameters(global.out[i].param.parameters,
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&amp;global.out[i].param.argc,
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;global.out[i].param.argv);
    </p>
    <p>
      
    </p>
    <p>
      global.out[i].param.global = &amp;global;
    </p>
    <p>
      global.out[i].param.id = i;
    </p>
    <p>
      
    </p>
    <p>
      <font color="#ec0707">/** </font>
    </p>
    <p>
      <font color="#ec0707">&#160;* &#35843;&#29992;&#36755;&#20986;&#35774;&#22791;&#30340;&#21021;&#22987;&#21270;&#20989;&#25968; </font>
    </p>
    <p>
      <font color="#ec0707">&#160;*/</font>
    </p>
    <p>
      if(global.out[i].init(&amp;global.out[i].param, i)) {
    </p>
    <p>
      &#160;&#160;&#160;LOG(&quot;output_init() return value signals to exit\n&quot;);
    </p>
    <p>
      &#160;&#160;&#160;closelog();
    </p>
    <p>
      &#160;&#160;&#160;exit(0);
    </p>
    <p>
      }
    </p>
  </body>
</html></richcontent>
</node>
</node>
<node CREATED="1511421993320" ID="ID_1830261633" MODIFIED="1511428726644">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      /**
    </p>
    <p>
      &#160;* start to read the input, push pictures into global buffer
    </p>
    <p>
      &#160;*/
    </p>
    <p>
      DBG(&quot;starting %d input plugin\n&quot;, global.incnt);
    </p>
    <p>
      for(i = 0; i &lt; global.incnt; i++) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;syslog(LOG_INFO, &quot;starting input plugin %s&quot;, global.in[i].plugin);
    </p>
    <p>
      &#160;&#160;&#160;&#160;if(global.in[i].run(i)) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;LOG(&quot;can not run input plugin %d: %s\n&quot;, i, global.in[i].plugin);
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;closelog();
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;return 1;
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
      DBG(&quot;starting %d output plugin(s)\n&quot;, global.outcnt);
    </p>
    <p>
      for(i = 0; i &lt; global.outcnt; i++) {
    </p>
    <p>
      &#160;&#160;&#160;&#160;syslog(LOG_INFO, &quot;starting output plugin: %s (ID: %02d)&quot;,
    </p>
    <p>
      &#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;global.out[i].plugin, global.out[i].param.id);
    </p>
    <p>
      &#160;&#160;&#160;&#160;global.out[i].run(global.out[i].param.id);
    </p>
    <p>
      }
    </p>
  </body>
</html></richcontent>
</node>
<node CREATED="1511421993972" ID="ID_611141769" MODIFIED="1511428742281">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      /* wait for signals */
    </p>
    <p>
      pause();
    </p>
  </body>
</html></richcontent>
</node>
</node>
<node CREATED="1511428618001" ID="ID_174982252" MODIFIED="1511428981409" TEXT="input_uvc">
<node CREATED="1511428985545" ID="ID_1514548452" MODIFIED="1511428985545" TEXT=""/>
<node CREATED="1511428987513" ID="ID_1491283442" MODIFIED="1511428987513" TEXT=""/>
<node CREATED="1511428987926" ID="ID_1385384158" MODIFIED="1511428987926" TEXT=""/>
<node CREATED="1511428988670" ID="ID_1901194655" MODIFIED="1511428988670" TEXT=""/>
</node>
<node CREATED="1511428996944" ID="ID_1962287936" MODIFIED="1511429004122" TEXT="output_http">
<node CREATED="1511429006768" ID="ID_846713579" MODIFIED="1511429006768" TEXT=""/>
<node CREATED="1511429008273" ID="ID_524881219" MODIFIED="1511429008273" TEXT=""/>
<node CREATED="1511429008650" ID="ID_1478801754" MODIFIED="1511429008650" TEXT=""/>
<node CREATED="1511429008975" ID="ID_375376455" MODIFIED="1511429008975" TEXT=""/>
</node>
</node>
<node CREATED="1511404419925" ID="ID_1058528739" MODIFIED="1511405100838" POSITION="right" TEXT=""/>
<node CREATED="1511404420038" ID="ID_1496037315" MODIFIED="1511405100838" POSITION="right" TEXT=""/>
</node>
</map>
