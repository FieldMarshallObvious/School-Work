
public class pizzaQueue 
{
    public static void main(String[] args) 
    {
        // Create objects for first and last objects 
        pizzaList queue = new pizzaList();

        queue.enqueue( new pizza("pepperoni", "1234 Bobcat Trail"));
        queue.enqueue(new pizza("sausage", "2345 University Drive"));

        queue.deliver();

        queue.enqueue( new pizza("extra cheese", "3456 Rickster Road"));
        queue.enqueue(new pizza("everything", "4567 King Court"));
        queue.enqueue( new pizza("coffee beans", "5678 Java Circle"));

        queue.deliver();
        queue.deliver();
        queue.deliver();
        queue.deliver();
        queue.deliver();

    }

}

class pizzaList 
{
    // Head and object declarations 
    private pizza head;
    private pizza tail;

    // Initializer with head and tail
    public pizzaList( )
    {
        head = new pizza();
        tail = new pizza();
    }

    // Add an item to the queue 
    public void enqueue( pizza thispizza )
    {
        // If there is no head, create one 
        if ( head.ingredients == " " && head.address == " " ) 
        {
            this.head = thispizza;
        }
        // If there already is a queue append this item to the end of the list 
        else this.tail.next = thispizza;
        this.tail = thispizza;
    }

    // Remove an itme from the queue 
    public pizza dequeue(  )
    {
        // Variable declarations
        pizza pizzaToDeliver = null; // Keep track of the pizza to be delivied 
        
        // If the list is exists then reduce the head by one 
        if ( head != null )
        {
            pizzaToDeliver = head;
            head = head.next;
        }

        // If there is no items in the list then ensure the tail is gone
        if ( head == null ) tail = null;

        // return the pizza that will be delivered
        return pizzaToDeliver;
    }

    // deliver pizzas from the queue 
    public void deliver( )
    {
        // Variable declarations
        pizza thisPizza = dequeue( );

        // If there is no pizza to be delivered
        if( thisPizza == null )
        {
            System.out.print("No deliveries pending \n");
            return;
        }

        // Otherwise print the pizza and the address
        System.out.print("Deliver a pizza with " + thisPizza.ingredients + " to " + thisPizza.address + "\n");
    }
}

class pizza
{
        // Variable declarations
        public String ingredients, address;
        public pizza next;

        public pizza()
        {
            ingredients = " ";
            address = " ";
            next = null;
        }

        // Object initializer with parameters
        public pizza( String inputIngredients, String inputAddress ) 
        {
            ingredients = inputIngredients;
            address = inputAddress;
            next = null;
        }
}