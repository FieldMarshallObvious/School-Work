
public class pizzaQueue 
{
    public static void main(String[] args) 
    {
        // Create objects for first and last objects 
        pizza queue = new pizza(); pizza first = new pizza(); pizza last = new pizza();

        queue.enqueue( first, last, new pizza("pepperoni", "1234 Bobcat Trail"));
        queue.enqueue(first, last, new pizza("sausage", "2345 University Drive"));

        queue.deliver(first, last);

        queue.enqueue(first, last, new pizza("extra cheese", "3456 Rickster Road"));
        queue.enqueue(first, last, new pizza("everything", "4567 King Court"));
        queue.enqueue(first, last, new pizza("coffee beans", "5678 Java Circle"));

        queue.deliver(first, last);
        queue.deliver(first, last);
        queue.deliver(first, last);
        queue.deliver(first, last);
        queue.deliver(first, last);

    }

}

class pizza 
{
    // Variable declarations
    public String ingredients, address;
    public pizza next;

    // default initializer 
    public pizza( )
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
    }

    // Add an item to the queue 
    public void enqueue( pizza head, pizza tail, pizza thispizza )
    {
        // If there is no head, create one 
        if ( head.ingredients == " " && head.address == " " ) 
        {
            // modify individual items 
            head.ingredients = thispizza.ingredients;
            head.address = thispizza.address;
            head.next = thispizza;
        }
        // If there already is a queue append this item to the end of the list 
        else tail.next = new pizza( thispizza.ingredients, thispizza.address);
        tail = thispizza;
    }

    // Remove an itme from the queue 
    public pizza dequeue( pizza head, pizza tail )
    {
        // Variable declarations
        pizza pizzaToDeliver = new pizza(); // Keep track of the pizza to be delivied 
        
        // If the list is exists then reduce the head by one 
        if ( head != null )
        {
            // Get the pizza data to the pizza delivery 
            pizzaToDeliver.ingredients = head.ingredients;
            pizzaToDeliver.address = head.address;
            
            if( head.next == null )
            {
                // Set the head to next 
                head.ingredients = head.next.ingredients;
                head.address = head.next.address;
                head.next = head.next.next;
            }
        }

        // If there is no items in the list then ensure the tail is gone
        if ( head == null ) tail = null;

        // return the pizza that will be delivered
        return pizzaToDeliver;
    }

    // deliver pizzas from the queue 
    public void deliver( pizza head, pizza tail )
    {
        // Variable declarations
        pizza thisPizza = dequeue(head, tail);

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