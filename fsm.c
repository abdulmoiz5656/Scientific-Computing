
 class CoffeeMachine {
  User user;
  state {
    idle {
      coin(int value) [value == 10] -> paidTen; }
    paidTen {
       coffee / {user.cupOfCoffee(new Drink());}  -> idle; }
  }
 }

 
public boolean coffee() {
      boolean wasEventProcessed = false;
      State aState = state;
      switch (aState) {
            case paidTen:
                  user.cupOfCoffee(new Drink());
                  setState(State.idle);
                  wasEventProcessed = true;
                  break;
            }
      return wasEventProcessed;
}

public class Main {
      public static Delivery del = new Delivery();
      public static CoffeeMachine cm =
            new CoffeeMachine(del);
      public static User user = new User(cm, del);
      public static void main ( String[] args ) {
            new Thread(user).start(); }
}

public class Delivery {
      public Drink coffee = null;
      public int returnedCoins = 0;
      public void cupOfCoffee(Drink d) {
            coffee = d; }
}

public class User implements Runnable {
      private CoffeeMachine myCM; Delivery d;
      public User(CoffeeMachine m, Delivery del) {
            myCM = m; d = del; }
      public void run(){
            while (true) {
                  myCM.coin(10);
                  myCM.coffee();
                  try {Thread.sleep(2000);}
                        catch(InterruptedException ie){}
                  if (d.coffee != null){
                        d.coffee = null;
                        System.out.println("got a coffee");
                  } else {System.out.println("there is no drink");}

            }
      }
}

class CoffeeMachine {
  Delivery del;
  state {
    idle {
      coin(int value) [value == 10] -> paidTen;
    }
    paidTen {
       coffee / {del.cupOfCoffee(new Drink());}
         -> idle;
     }
  }
}