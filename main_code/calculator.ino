// calculator 
const int LEN = 20;

// Size of the stack
const int MAX = 40;

class Stack {
private:
  // Stack: array of characters
  char st[MAX];

  // Number at top of the stack
  int top;

public:
  Stack()
  {
    top = 0;
  }

  // Function to put a character in stack
  void push(char var)
  {
    st[++top] = var;
  }

  // Function to return a character off stack
  char pop()
  {
    return st[top--];
  }

  // Function to get the top of the stack
  int gettop()
  {
    return top;
  }
};

// Expression class
class Express {
private:
  // Stack for analysis
  Stack s;

  // Pointer to input string
  char* pStr;

  // Length of the input string
  int len;

public:
  Express(char* ptr)
  {
    pStr = ptr;
    len = strlen(pStr);
  }

  // Parse the input string
  void parse();

  // Evaluate the stack
  int solve();
};

void Express::parse()
{

  // Character from the input string
  char ch;

  // Last value
  char lastval;

  // Last operator
  char lastop;

  // For each input character
  for (int j = 0; j < len; j++) {
    ch = pStr[j];

    // If it's a digit then save
    // the numerical value
    if (ch >= '0' && ch <= '9')
      s.push(ch - '0');

    // If it's an operator
    else if (ch == '+' || ch == '-'
        || ch == '*' || ch == '/') {

      // If it is the first operator
      // then put it in the stack
      if (s.gettop() == 1)

        s.push(ch);

      // Not the first operator
      else {
        lastval = s.pop();
        lastop = s.pop();

        // If it is either '*' or '/' and the
        // last operator was either '+' or '-'
        if ((ch == '*' || ch == '/')
          && (lastop == '+' || lastop == '-')) {

          // Restore the last two pops
          s.push(lastop);
          s.push(lastval);
        }

        // In all the other cases
        else {

          // Perform the last operation
          switch (lastop) {

          // Push the result in the stack
          case '+':
            s.push(s.pop() + lastval);
            break;
          case '-':
            s.push(s.pop() - lastval);
            break;
          case '*':
            s.push(s.pop() * lastval);
            break;
          case '/':
            s.push(s.pop() / lastval);
            break;
          default:
            Serial.println("\nUnknown oper");
            exit(1);
          }
        }
        s.push(ch);
      }
    }
    else {
      Serial.println("\nUnknown input character");
      exit(1);
    }
  }
}

int Express::solve()
{
  // Remove the items from stack
  char lastval;
  while (s.gettop() > 1) {
    lastval = s.pop();
    switch (s.pop()) {

    // Perform operation, push answer
    case '+':
      s.push(s.pop() + lastval);
      break;
    case '-':
      s.push(s.pop() - lastval);
      break;
    case '*':
      s.push(s.pop() * lastval);
      break;
    case '/':
      s.push(s.pop() / lastval);
      break;
    default:
      Serial.println("\nUnknown operator");
      exit(1);
    }
  }
  return int(s.pop());
}


// -------------------------------------------calculator -----------------------------------------------

String expression = "";
int len = 0;

void calculator(){
  drawSdJpeg(screen[CurrentStatus] , 0 , 0 );
  
   while(true){
      if(isBackPressed()){
        CurrentStatus = 1;
        drawSdJpeg(screen[CurrentStatus] , 0 , 0 );
        expression = "";
        return;
      }

      expressionSolver();

       
      
    
      
    }     
 }


 void expressionSolver(){

       if(touch.touched() && !touch.bufferEmpty()){
      if(p.x > 26  && p.x < 155  && p.y > 206 && p.y < 233){
          expression += "0";  len++;
      }

      else if(p.x > 163  && p.x < 223  && p.y > 206 && p.y < 233){
        expression += "."; len++;
      }

      else if(p.x > 239 && p.x < 299 && p.y > 208 && p.y < 233){

//        const char *Expressn = expression.c_str();
        char buf[30];
        expression += "*";
        expression.toCharArray(buf , expression.length());
        Express* eptr = new Express(buf);
        eptr->parse();
        int res = eptr->solve();
        refreshScreen(30,41, 25);
        tft.setTextSize(2);
        tft.setTextColor(TFT_WHITE , TFT_BLACK);
        tft.setCursor(30,41);
        expression = String(res);
        tft.print(expression);
//        expression = "";
      }


      else if(p.x > 27 && p.x <87 && p.y > 173 && p.y < 200){
        expression += "1"; len++;
      }

      else if(p.x > 95 && p.x < 155 && p.y > 173 && p.y <200){
        expression += "2"; len++;
      }

      else if(p.x > 163 && p.x < 223 && p.y > 173 && p.y < 200){
        expression += "3"; len++;
      }

      else if(p.x > 235 && p.x < 295 && p.y > 173 && p.y <200){
        expression += "+"; len++;
      }


      else if(p.x > 27 && p.x <87 && p.y > 143 && p.y < 170){
        expression += "4"; len++;
      }

      else if(p.x > 95 && p.x < 155 && p.y > 143 && p.y <170){
        expression += "5"; len++;
      }

      else if(p.x > 163 && p.x < 223 && p.y > 143 && p.y < 170){
        expression += "6"; len++;
      }

      else if(p.x > 235 && p.x < 295 && p.y > 143 && p.y <170){
        expression += "-"; len++;
      }

      else if(p.x > 27 && p.x <87 && p.y > 111 && p.y < 138){
        expression += "7"; len++;
      }

      else if(p.x > 95 && p.x < 155 && p.y > 111 && p.y <138){
        expression += "8"; len++;
      }

      else if(p.x > 163 && p.x < 223 && p.y > 111 && p.y < 138){
        expression += "9"; len++;
      }

      else if(p.x > 235 && p.x < 295 && p.y > 111 && p.y <138){
        expression += "*"; len++;
      }


      else if(p.x > 27 && p.x < 87 && p.y > 78 && p.y < 104){
//        expression += "7"; 
          expression = "";
           // clear();
      }

      else if(p.x > 95 && p.x < 155 && p.y > 78 && p.y <104){
//        expression += "8";
//        modulo;
      }

      else if(p.x > 163 && p.x < 223 && p.y > 78 && p.y < 104){
//        expression += "9";
      }

      else if(p.x > 235 && p.x < 295 && p.y > 78 && p.y <104){
//        expression += "*";
          expression += "/";
      }

      refreshScreen(30,41, 25);
      tft.setTextSize(2);
        tft.setTextColor(TFT_WHITE , TFT_BLACK);
      tft.setCursor(30,41);
      tft.print(expression);
      delay(500);
     
       }    
 }
