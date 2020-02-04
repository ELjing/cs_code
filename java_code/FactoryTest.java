interface Human{
    public void eat();
    public void sleep();
    public void beat();
}

class Male implements Human{
    public void eat() {
        System.out.println("Male can eat.");
    }
    public void sleep() {
        System.out.println("Male can sleep.");
    }
    public void beat() {
        System.out.println("Male can beat.");
    }
}

class Female implements Human{
    public void eat() {
        System.out.println("Female can eat.");
    }
    public void sleep() {
        System.out.println("Female can sleep.");
    }
    public void beat() {
        System.out.println("Female can beat.");
    }
}

class HumanFactory{
    public Human createHuman(String gender) {
        if(gender.equals("male")) {
            return new Male();
        } else if(gender.equals("female")) {
            return new Female();
        } else {
            System.out.println("input type is wrong!");
            return null;
        }
    }
}

public class FactoryTest {
    public static void main(String[] args) {
        HumanFactory factory = new HumanFactory();
        Human male = factory.createHuman("male");
        Human female = factory.createHuman("female");
        male.eat();
        male.sleep();
        male.beat();
        female.eat();
    }
}