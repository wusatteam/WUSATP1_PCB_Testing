#define XBee      Serial1
#define USB       Serial
#define DEBUG     USB.print
#define DEBUGLN   USB.println
#define NODE      "WUSATBASE"

#define XBEE_RETRIES   1

char xbuf[32];

void setup(){
  // Serial debug
  USB.begin(38400);
  while(!USB){
  }

  //XBee init
  XBee.begin(115200);
  XBee.setTimeout(3000);  
}

void loop(){
  DEBUG("Entering command mode... ");
  if(XBee_enterCommand()){
    DEBUGLN("Success.");
    DEBUG("Discovering ");
    DEBUG(NODE);
    DEBUG("... ");
    if(XBee_discoverNode()){
      DEBUGLN("Success.");
      delay(100);
      XBee.println("Hello?");
    } 
    else {
      DEBUGLN("Error.");
    }
  }
  else
    DEBUGLN("Error.");

  delay(5000);
}

// Enter command mode
boolean XBee_enterCommand() {
  int rcv=0;

  XBee.flush();
  XBee_discardBuffer();  
  
  delay(1100);
  XBee.print("+++");
  XBee.flush();
  delay(1100);
  rcv = XBee.readBytesUntil('\r',xbuf,32);

  return rcv==2 ? true:false;
}

// Exit command mode
boolean XBee_exitCommand(){
  XBee_discardBuffer();
  XBee.print("ATCN\r");
  int rcv = XBee.readBytesUntil('\r',xbuf,32);
  return rcv==2 ? true:false;
}

// Discovers node then exits command mode to allow immediate communication
boolean XBee_discoverNode(){
  XBee_discardBuffer();
  XBee.setTimeout(10000);
  XBee.print("ATDN");
  XBee.print(NODE);
  XBee.print('\r');

  int rcv = XBee.readBytesUntil('\r',xbuf,32);
  DEBUG("ATDN: ");
  DEBUG(rcv,DEC);
  XBee.setTimeout(3000);
  return rcv==2 ? true:false;
}

void XBee_discardBuffer(){
  while(XBee.available())
    XBee.read();
}








