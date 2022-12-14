package bguspl.set.ex;

import java.util.LinkedList;
import java.util.Queue;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.ConcurrentLinkedDeque;
import java.util.concurrent.LinkedBlockingQueue;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

import org.mvel2.asm.Handle;

import bguspl.set.Env;

/**
 * This class manages the players' threads and data
 *
 * @inv id >= 0
 * @inv score >= 0
 */
public class Player implements Runnable {

    /**
     * The game environment object.
     */
    private final Env env;

    /**
     * Game entities.
     */
    private final Table table;

    /**
     * The id of the player (starting from 0).
     */
    public final int id;

    /**
     * The thread representing the current player.
     */
    private Thread playerThread;

    /**
     * The thread of the AI (computer) player (an additional thread used to generate key presses).
     */
    private Thread aiThread;

    /**
     * True iff the player is human (not a computer player).
     */
    private final boolean human;

    /**
     * True iff game should be terminated due to an external event.
     */
    private volatile boolean terminate;

    /**
     * The current score of the player.
     */
    private final Dealer dealer;
    private int score;
    private int tokens;
    protected BlockingQueue<Integer> actions = new LinkedBlockingQueue<Integer>(3);
    protected ReentrantLock lock = new ReentrantLock();

    /**
     * The class constructor.
     *
     * @param env    - the environment object.
     * @param dealer - the dealer object.
     * @param table  - the table object.
     * @param id     - the id of the player.
     * @param human  - true iff the player is a human player (i.e. input is provided manually, via the keyboard).
     */
    public Player(Env env, Dealer dealer, Table table, int id, boolean human) {
        this.env = env;
        this.table = table;
        this.id = id;
        this.human = human;
        this.dealer = dealer;
    }

    /**
     * The main player thread of each player starts here (main loop for the player thread).
     */
    @Override
    public void run() {
        playerThread = Thread.currentThread();
        // lock.unlock();   
        System.out.printf("Info: Thread %s starting.%n", Thread.currentThread().getName());
        if (!human) createArtificialIntelligence();
        while (!terminate) {
            try {
                int i = actions.take();
                handleAction(i);
            } catch (InterruptedException e) {
                // TODO: handle exception
            } 
        }
        if (!human) try { aiThread.join(); } catch (InterruptedException ignored) {}
        System.out.printf("Info: Thread %s terminated.%n", Thread.currentThread().getName());
    }

    /**
     * Creates an additional thread for an AI (computer) player. The main loop of this thread repeatedly generates
     * key presses. If the queue of key presses is full, the thread waits until it is not full.
     */
    private void createArtificialIntelligence() {
        // note: this is a very very smart AI (!)
        aiThread = new Thread(() -> {
            // System.out.printf("Info: Thread %s starting.%n", Thread.currentThread().getName());
            while (!terminate) {
                // TODO implement player key press simulator
    
            }
            System.out.printf("Info: Thread %s terminated.%n", Thread.currentThread().getName());
        }, "computer-" + id);
        aiThread.start();
    }

    /**
     * Called when the game should be terminated due to an external event.
     */
    public void terminate() {
        // TODO implement
        
    }

    /**
     * This method is called when a key is pressed.
     *
     * @param slot - the slot corresponding to the key pressed.
     */
    public void keyPressed(int slot) {
        if(!lock.isLocked())
            actions.offer(slot);
    }

    private void handleAction(int i){
        switch(i){
            case -1:
            point();
            break;
            case -2:
            penalty();
            break;
            default:
            if(!table.removeToken(id, i)){
                table.placeToken(id, i);
                tokens++;
            }
            else{
                tokens--;
            }
            if(tokens == 3){
                lock.lock();
                synchronized(actions){
                     dealer.playersToCheck.add(id);
                }
            }
        }
    }

    /**
     * Award a point to a player and perform other related actions.
     *
     * @post - the player's score is increased by 1.
     * @post - the player's score is updated in the ui.
     */
    public void point() {
        // TODO implement
        synchronized(actions){
        int ignored = table.countCards(); // this part is just for demonstration in the unit tests
        score++;
        env.ui.setScore(id, score);
        long unfreez = System.currentTimeMillis() + env.config.pointFreezeMillis;
        while(unfreez > System.currentTimeMillis()){
            try{
                    env.ui.setFreeze(id, unfreez - System.currentTimeMillis());
                    Thread.sleep(1000);
                }
                catch(InterruptedException e){}
            }
        }
        env.ui.setFreeze(id, 0);
        lock.unlock();
        
    }    

    /**
     * Penalize a player and perform other related actions.
     */
    public void penalty() {
        synchronized(this){
            long unfreez = System.currentTimeMillis() + env.config.penaltyFreezeMillis;
            while(unfreez > System.currentTimeMillis()){
                try{
                        env.ui.setFreeze(id, unfreez - System.currentTimeMillis());
                        Thread.sleep(1000);
                    }
                    catch(InterruptedException e){}
                }
            }
            env.ui.setFreeze(id, 0);
            lock.unlock();

    }

    public int getScore() {
        return score;
    }

    public void resetTokens(){
        tokens = 0;
    }
}
